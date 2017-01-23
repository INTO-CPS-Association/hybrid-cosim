import logging

from abstract_units.AbstractSimulationUnit import AbstractSimulationUnit, \
    STEP_ACCEPT

l = logging.getLogger()

class DecoupleAdaptation(AbstractSimulationUnit):
    
    def __init__(self, name):
        
        self.in_v = "in_v"
        self.out_v = "out_v"
        input_vars = [self.in_v]
        state_vars = [self.out_v]
        
        algebraic_functions = {}
        
        AbstractSimulationUnit.__init__(self, name, algebraic_functions, state_vars, input_vars)
    
    def _doInternalSteps(self, time, step, iteration, step_size):
        l.debug(">%s._doInternalSteps(%f, %d, %d, %f)", self._name, time, step, iteration, step_size)
        
        assert step_size > 0.0, "step_size too small: {0}".format(step_size)
        assert iteration == 0, "Fixed point iterations not supported yet."
        
        previous_input = self.getValues(step, iteration, self._getInputVars())[self.in_v]
        
        l.debug("%s.previous_input=%f", self._name, previous_input)
        
        l.debug("%s.output_value=%s", self._name, previous_input)
        self.setValues(step, iteration, {self.out_v: previous_input})
        
        l.debug("<%s._doInternalSteps() = (%s, %d)", self._name, STEP_ACCEPT, step_size)
        return (STEP_ACCEPT, step_size)
    
    def enterInitMode(self):
        l.debug(">%s.DecoupleAdaptation.enterInitMode()", self._name)
        AbstractSimulationUnit.enterInitMode(self)
        
        # Add a dummy value at time 0, just to fill in the array
        self.setValues(0, 0, {self.in_v: 0.0})
        
        l.debug("<%s.DecoupleAdaptation.enterInitMode()", self._name)
    