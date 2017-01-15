import logging

import numpy

from abstract_units.AbstractSimulationUnit import AbstractSimulationUnit, \
    STEP_ACCEPT, INIT_MODE
from case_study.units.ct_based.ObstacleFMU import ObstacleFMU
from case_study.units.ct_based.PowerFMU import PowerFMU
from case_study.units.ct_based.WindowFMU import WindowFMU

l = logging.getLogger()

class AlgebraicAdaptation_Power_Window_Obstacle(AbstractSimulationUnit):
    """
    This is the adaptation that realizes the strong coupling between the power,
    window, and obstacle units.
    """
    
    def __init__(self, name, num_rtol, num_atol, cosim_step_size, num_internal_steps):
        
        self._num_rtol = num_rtol
        self._num_atol = num_atol
        
        self._max_iterations = 100
        
        self._power = PowerFMU("power", num_rtol, num_atol, cosim_step_size/num_internal_steps, 
                     J=0.085, 
                     b=5, 
                     K=7.45, 
                     R=0.15, 
                     L=0.036,
                     V_a=12)
        
        self.omega = self._power.omega
        self.theta= self._power.theta
        
        
        self._window = WindowFMU("window", num_rtol, num_atol, cosim_step_size/num_internal_steps,
                     r=0.11, 
                     b = 10)
        
        self._obstacle = ObstacleFMU("obstacle", num_rtol, num_atol, cosim_step_size/num_internal_steps, 
                     c=1e5, 
                     fixed_x=0.45)
        
        self.up = self._power.up
        self.down = self._power.down
        
        input_vars = [self.down, self.up]
        
        self.i = self._power.i
        self.omega = self._power.omega
        self.theta = self._power.theta
        self.x = self._window.x
        self.F = self._obstacle.F
        
        state_vars = [self.i, self.omega, self.theta, self.x, self.F]
        
        algebraic_functions = {}
        
        AbstractSimulationUnit.__init__(self, name, algebraic_functions, state_vars, input_vars)
    
    def _isClose(self, a, b):
        return numpy.isclose(a,b, self._num_rtol, self._num_atol)
    
    def _biggerThan(self, a, b):
        return not numpy.isclose(a,b, self._num_rtol, self._num_atol) and a > b
    
    def _doInternalSteps(self, time, step, iteration, cosim_step_size):
        l.debug(">%s._doInternalSteps(%f, %d, %d, %f)", self._name, time, step, iteration, cosim_step_size)
        
        assert self._biggerThan(cosim_step_size, 0), "cosim_step_size too small: {0}".format(cosim_step_size)
        assert iteration == 0, "Fixed point iterations not supported outside of this component."
        
        converged = False
        internal_iteration = 0
        
        cOut = self.getValues(step, iteration, [self.up, self.down])
        wOut = self._window.getValues(step-1, iteration, [self._window.x, self._window.tau])
        pOut = None
        
        while not converged and internal_iteration < self._max_iterations:
            self._power.setValues(step, iteration, {
                                     self._power.tau: wOut[self._window.tau], # Delayed input
                                     self._power.up: cOut[self.up],
                                     self._power.down: cOut[self.down]
                                     })
            self._power.doStep(time, step, iteration, cosim_step_size)
            pOut = self._power.getValues(step, iteration, [self._power.omega, 
                                                           self._power.theta, 
                                                           self._power.i])
            
            self._obstacle.setValues(step, iteration, {self._obstacle.x: wOut[self._window.x]}) # Delayed input
            self._obstacle.doStep(time, step, iteration, cosim_step_size)
            oOut = self._obstacle.getValues(step, iteration, [self._obstacle.F])
            
            self._window.setValues(step, iteration, {self._window.omega_input: pOut[self._power.omega],
                                        self._window.theta_input: pOut[self._power.theta],
                                        self._window.F_obj: oOut[self._obstacle.F]
                                        })
            self._window.doStep(time, step, iteration, cosim_step_size)
            wOut_corrected = self._window.getValues(step, iteration, [self._window.x, self._window.tau])
            
            l.debug("Iteration step completed:")
            l.debug("wOut=%s;", wOut)
            l.debug("wOut_corrected=%s.", wOut_corrected)
            
            
            if self._isClose(wOut[self._window.x], wOut_corrected[self._window.x]) \
                and self._isClose(wOut[self._window.tau], wOut_corrected[self._window.tau]):
                converged = True
            
            internal_iteration = internal_iteration + 1
            wOut = wOut_corrected
                
        if converged:
            l.debug("Fixed point found after %d iterations", internal_iteration)
        else:
            l.debug("Fixed point not found after %d iterations", internal_iteration)
            raise RuntimeError("Fixed point not found")
        
        AbstractSimulationUnit.setValues(self, step, iteration, 
                                         {
                                         self.i: pOut[self._power.i],
                                         self.theta: pOut[self._power.theta],
                                         self.omega: pOut[self._power.omega],
                                         self.x: wOut[self._window.x],
                                         self.F: oOut[self._obstacle.F]
                                         });
        
        l.debug("<%s._doInternalSteps() = (%s, %d)", self._name, STEP_ACCEPT, cosim_step_size)
        return (STEP_ACCEPT, cosim_step_size)
    
    def setValues(self, step, iteration, values):
        l.debug(">%s.AlgebraicAdaptation_Power_Window_Obstacle.setValues(%d, %d, %s)", self._name, step, iteration, values)
        
        # Filter just the inputs.
        inputs = {
                  self.up: values[self.up],
                  self.down: values[self.down]
                  }
        
        AbstractSimulationUnit.setValues(self, step, iteration, inputs);
        
        if self._mode == INIT_MODE:
            # Initialize the internal FMUs and compute the value of the armature.
            
            l.debug("Initializing strong component...")
            
            step = iteration = 0
            
            wOut_tau_delayed =  0.0;
            wOut_x_delayed = 0.0;
            
            # Set power inputs (or initial state, given by values)
            self._power.setValues(step, iteration, values)
            self._power.setValues(step, iteration, {
                                             self._power.tau: wOut_tau_delayed    
                                             })
            
            # Get power initial outputs
            pOut = self._power.getValues(step, iteration, [self._power.omega, self._power.theta, self._power.i])
            
            # Set obstacle initial inputs
            # Assume they are zero because the outputs of the window are delayed.
            self._obstacle.setValues(step, iteration, {self._obstacle.x: wOut_x_delayed})
            # Get obstacle outputs
            oOut = self._obstacle.getValues(step, iteration, [self._obstacle.F])
            
            # Set window inputs
            self._window.setValues(step, iteration, {self._window.omega_input: pOut[self._power.omega],
                                        self._window.theta_input: pOut[self._power.theta],
                                        self._window.F_obj: oOut[self._obstacle.F]
                                        })
            # Get window outputs
            wOut = self._window.getValues(step, iteration, [self._window.x, self._window.tau])
            
            # Set corrected power windows
            self._power.setValues(step, iteration, {
                                             self._power.tau: wOut[self._window.tau] # Delayed input from window
                                             })
            
            # We know that convergence is easily achieved for this initialisation
            assert self._isClose(wOut[self._window.tau], wOut_tau_delayed)
            assert self._isClose(wOut[self._window.x], wOut_x_delayed)
            
            # Record the outputs
            AbstractSimulationUnit.setValues(self, step, iteration, {
                                                                     self.i: pOut[self._power.i],
                                                                     self.theta: pOut[self._power.theta],
                                                                     self.omega: pOut[self._power.omega],
                                                                     self.x: wOut[self._window.x],
                                                                     self.F: oOut[self._obstacle.F]
                                                                     });
            
            l.debug("Strong component initialized.")
            
        l.debug("<%s.AlgebraicAdaptation_Power_Window_Obstacle.setValues()", self._name)
    
    
    def enterInitMode(self):
        l.debug(">%s.AlgebraicAdaptation_Power_Window_Obstacle.enterInitMode()", self._name)
        
        AbstractSimulationUnit.enterInitMode(self);
        
        self._power.enterInitMode()
        self._window.enterInitMode()
        self._obstacle.enterInitMode()
        
        l.debug("<%s.AlgebraicAdaptation_Power_Window_Obstacle.enterInitMode()", self._name)
    
    def exitInitMode(self):
        l.debug(">%s.AlgebraicAdaptation_Power_Window_Obstacle.exitInitMode()", self._name)
        
        AbstractSimulationUnit.exitInitMode(self);
        
        self._power.exitInitMode()
        self._window.exitInitMode()
        self._obstacle.exitInitMode()
        
        l.debug("<%s.AlgebraicAdaptation_Power_Window_Obstacle.exitInitMode()", self._name)