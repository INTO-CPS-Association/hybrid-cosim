import logging

from abstract_units.AbstractSimulationUnit import AbstractSimulationUnit, \
    STEP_ACCEPT

l = logging.getLogger()

class ZOHAdaptation(AbstractSimulationUnit):
    
    def __init__(self, name, input_var, output_var):
        
        self.input_var = "in_v"
        self.output_var = "out_v"
        
        self.__value_to_hold = 0.0
        
        input_vars = []
        state_vars = []
        
        algebraic_functions = {}
        
        AbstractSimulationUnit.__init__(self, name, algebraic_functions, state_vars, input_vars)
    
    def setValues(self, step, iteration, values, ensureExists=True):
        l.debug(">%s.ZOHAdaptation.setValues(%d, %d, %s)", self._name, step, iteration, values)
        
        if values.has_key(self.input_var):
            self.__value_to_hold = values[self.input_var]
        
        l.debug("New state: \n%s", self.__value_to_hold)
        l.debug("<%s.ZOHAdaptation.setValues()", self._name)
        
    
    def getValues(self, step, iteration, var_names=None, zoh=False, ensureExists=False):
        l.debug(">%s.ZOHAdaptation.getValues(%d, %d, %s)", self._name, step, iteration, var_names)
        
        values = {
                  self.output_var : self.__value_to_hold
                  }
        
        l.debug("<%s.ZOHAdaptation.getValues()=%s", self._name, values)
        return values
    
    
    def _doInternalSteps(self, time, step, iteration, step_size):
        l.debug(">%s._doInternalSteps(%f, %d, %d, %f)", self._name, time, step, iteration, step_size)
        
        l.debug("<%s._doInternalSteps() = (%s, %d)", self._name, STEP_ACCEPT, step_size)
        return (STEP_ACCEPT, step_size)
    
    