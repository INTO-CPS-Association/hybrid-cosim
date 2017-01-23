import logging

import numpy

from abstract_units.AbstractSimulationUnit import AbstractSimulationUnit, \
    STEP_ACCEPT
from master.GaussSeidelMaster import GaussSeidelMaster

l = logging.getLogger()

class MultiRateAdaptationUnit(AbstractSimulationUnit):
    
    def __init__(self, name, num_rtol, num_atol, 
                                  order, units, coupling, external_coupling, start_rate, initial_state):
        
        algebraic_functions = {}
        
        state_vars = []
        
        input_vars = []
        
        AbstractSimulationUnit.__init__(self, name, algebraic_functions, state_vars, input_vars)
        
        self._num_rtol = num_rtol
        self._num_atol = num_atol
        
        self._start_rate = start_rate
        
        self._initial_state = initial_state
        self._units = units
        self._coupling = coupling
        self._external_coupling = external_coupling
        self._order = order
        
        self._y = None
        
        self._inputs = None
    
    def _isClose(self, a, b):
        return numpy.isclose(a,b, self._num_rtol, self._num_atol)
    
    def _biggerThan(self, a, b):
        return not numpy.isclose(a,b, self._num_rtol, self._num_atol) and a > b
    
    def setValues(self, step, iteration, values):
        l.debug(">%s.MultiRateAdaptationUnit.setValues(%d, %d, %s)", self._name, step, iteration, values)
        
        self._inputs = values
        
        l.debug("<%s.MultiRateAdaptationUnit.setValues()", self._name)
    
    def getValues(self, step, iteration, var_names=None, zoh=False):
        l.debug(">%s.MultiRateAdaptationUnit.getValues(%d, %d, %s)", self._name, step, iteration, var_names)
        
        u = []
        for _ in self._units:
            u.append(None)
        
        GaussSeidelMaster.compute_outputs(self._step, 
                                          self._units, self._order, self._coupling, 
                                          self._y, u)
        
        output_values = self._external_coupling(self._y)
        
        l.debug("<%s.MultiRateAdaptationUnit.getValues()=%s", self._name, output_values)
        return output_values
    
    def enterInitMode(self):
        l.debug(">%s.MultiRateAdaptationUnit.enterInitMode()", self._name)
        
        AbstractSimulationUnit.enterInitMode(self)
        
        self._y = []
        for _ in self._units:
            self._y.append(None)
        
        self._step = 0
        self._last_commited_step = 0
        
        GaussSeidelMaster.start_initialize(self._order, self._units)
        
        GaussSeidelMaster.set_initial_states(self._units, self._order, self._initial_state)
        
        l.debug("<%s.MultiRateAdaptationUnit.enterInitMode()", self._name)
    
    def exitInitMode(self):
        l.debug(">%s.MultiRateAdaptationUnit.exitInitMode()", self._name)
        
        AbstractSimulationUnit.exitInitMode(self)
        
        GaussSeidelMaster.finish_initialize(self._order, self._units)

        l.debug("<%s.MultiRateAdaptationUnit.exitInitMode()", self._name)
    
    def rollback(self, toStep):
        l.debug(">%s.MultiRateAdaptationUnit.rollback()", self._name)
        AbstractSimulationUnit.rollback(self, toStep)
        
        for unit in self._units:
            unit.rollback(self._last_commited_step)
        
        self._step = self._last_commited_step
        
        l.debug("<%s.MultiRateAdaptationUnit.rollback()", self._name)
    
    def commit(self, step):
        l.debug(">%s.MultiRateAdaptationUnit.commit()", self._name)
        self._last_commited_step = self._step
        
        for unit in self._units:
            unit.commit(self._step)
        
        l.debug("<%s.MultiRateAdaptationUnit.commit()", self._name)
        
    
    def _doInternalSteps(self, time, step, iteration, step_size):
        l.debug(">%s._doInternalSteps(%f, %d, %d, %f)", self._name, time, step, iteration, step_size)
        
        assert step_size > 0.0, "step_size too small: {0}".format(step_size)
        assert iteration == 0, "Fixed point iterations not supported yet."
        
        next_external_cosim_time = time+step_size
        
        l.debug("%s: Next cosim synch time=%f", self._name, next_external_cosim_time)
        
        max_step_size = step_size/self._start_rate
        
        H = max_step_size
        
        l.debug("max_step_size=%f", max_step_size)
        
        internal_time = time;
        
        u = []
        H_proposed = []
        
        for _ in self._units:
            u.append(None)
            H_proposed.append(None)
        
        do_next_step = True
        while do_next_step:
            
            last_rollback_step = self._step
            min_steps_before_increase = 1e5 # Never increase the step
            
            self._step = self._step + 1
            
            if (internal_time + H) > next_external_cosim_time:
                H = next_external_cosim_time - internal_time
                l.debug("Adjusting step size to meet synch point: H=%f", H)
            
            assert H > 0.0
            
            (H,_) = GaussSeidelMaster.do_cosim_step(internal_time, self._step, self._order, self._units, self._coupling, 
                                            u, self._y, H_proposed, 
                                            H, last_rollback_step,
                                            min_steps_before_increase, max_step_size, 0.0)
            
            l.debug("step size taken by internal units=%f", H)
            internal_time = internal_time + H
            l.debug("internal_time=%f", internal_time)
            if internal_time > next_external_cosim_time or \
                    self._isClose(internal_time, next_external_cosim_time):
                do_next_step = False
                l.debug("Finished step: %d.", self._step)
            
            
        l.debug("<%s._doInternalSteps() = (%s, %f)", self._name, STEP_ACCEPT, step_size)
        return (STEP_ACCEPT, step_size)

                