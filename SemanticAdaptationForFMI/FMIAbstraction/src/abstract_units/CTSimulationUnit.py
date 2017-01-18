'''
Created on Mar 5, 2016

@author: claudio gomes
'''
import logging

import numpy

from abstract_units.AbstractSimulationUnit import AbstractSimulationUnit, \
    STEP_ACCEPT
from sympy.parsing.maxima import var_name


l = logging.getLogger()

class CTSimulationUnit(AbstractSimulationUnit):
    """
    Represents a continuous time simulation unit.
    To be subclassed by concrete implementations
    """
    
    def __init__(self, name, num_rtol, num_atol, 
                                  state_derivatives, algebraic_functions, 
                                  input_vars):
        AbstractSimulationUnit.__init__(self, name, algebraic_functions, state_derivatives.keys(), input_vars)
        
        self._num_rtol = num_rtol
        self._num_atol = num_atol
        
        self._state_derivatives = state_derivatives
    
    def _isClose(self, a, b):
        return numpy.isclose(a,b, self._num_rtol, self._num_atol)
    
    def _biggerThan(self, a, b):
        return not numpy.isclose(a,b, self._num_rtol, self._num_atol) and a > b
    
    def _doNumericalStep(self, next_x, previous_x, inputs, time, step, iteration, next_cosim_time):
        raise "To be implemented by subclasses"
    
    def _doInternalSteps(self, time, step, iteration, step_size):
        l.debug(">%s._doInternalSteps(%f, %d, %d, %f)", self._name, time, step, iteration, step_size)
        
        assert step_size > 0.0, "step_size too small: {0}".format(step_size)
        #assert self._biggerThan(step_size, 0), "step_size too small: {0}".format(step_size)
        assert iteration == 0, "Fixed point iterations not supported yet."
        
        # Use double buffering in the internal steps. 
        # This ensures that any computation in the state derivatives use consistent values
        l.debug("Initialising state double buffer...")
        state_buffers = [self.getValues(step-1, iteration, self._getStateVars()), {}]
        next_state_idx = 0;
        previous_state_idx = 1;
        l.debug("Initialising input buffer...")
        # This tolerates both Jacobi and Gauss Seidel iteration.
        input_buffer = self.getValues(step, iteration, self._getInputVars(), zoh=True)
        
        next_cosim_time = time+step_size
        
        internal_time = time;
        
        (do_next_step, micro_step_size) = (True, 0.0)
        
        while do_next_step:
            # TODO Any input extrapolation would be done here by changing the input_buffer
            
            # flip the buffers
            l.debug("next_state_idx = %d, previous_state_idx = %d", next_state_idx, previous_state_idx)
            next_state_idx = (next_state_idx+1) % 2
            previous_state_idx = (previous_state_idx+1) % 2
            l.debug("next_state_idx = %d, previous_state_idx = %d", next_state_idx, previous_state_idx)
            previous_state = state_buffers[previous_state_idx]
            next_state = state_buffers[next_state_idx]
            
            (do_next_step, micro_step_size) = self._doNumericalStep(next_state, previous_state, input_buffer, internal_time, step, iteration, next_cosim_time)
            
            internal_time += micro_step_size
            l.debug("internal_time=%f", internal_time)
            
        
        # Commit the new state
        self.setValues(step, iteration, state_buffers[next_state_idx])
        
        l.debug("<%s._doInternalSteps() = (%s, %d)", self._name, STEP_ACCEPT, step_size)
        return (STEP_ACCEPT, step_size)

                