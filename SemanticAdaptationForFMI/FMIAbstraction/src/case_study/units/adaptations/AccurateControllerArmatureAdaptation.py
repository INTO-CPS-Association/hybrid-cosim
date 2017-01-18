import logging

import numpy

from abstract_units.AbstractSimulationUnit import AbstractSimulationUnit, \
    STEP_ACCEPT, STEP_DISCARD


l = logging.getLogger()

class AccurateControllerArmatureAdaptation(AbstractSimulationUnit):
    """
    This is the adaptation of the armature signal coming from the power system and into the controller statechart.
    The input will be the armature continuous signal.
    The output will be a pulse signal obj that can either be 0, or 1 whenever the absolute value of 
        the armature signal exceeds a certain threshold.
    The discontinuity is accurately located by rejecting the step size whenever it is larger than a given tolerance.
    
    """
    
    def __init__(self, name, num_rtol, num_atol, threshold, upward):
        
        self._num_rtol = num_rtol
        self._num_atol = num_atol
        
        assert upward, "Not implemented yet."
        
        self.__crossUpward = upward
        
        self.__threshold = threshold
        
        self.armature_current = "armature_current"
        self.out_obj = "out_obj"
        input_vars = [self.armature_current]
        state_vars = [self.out_obj]
        
        algebraic_functions = {}
        AbstractSimulationUnit.__init__(self, name, algebraic_functions, state_vars, input_vars)
    
    def _isClose(self, a, b):
        return numpy.isclose(a,b, self._num_rtol, self._num_atol)
    
    def _biggerThan(self, a, b):
        return not numpy.isclose(a,b, self._num_rtol, self._num_atol) and a > b
    
    def _doInternalSteps(self, time, step, iteration, step_size):
        l.debug(">%s._doInternalSteps(%f, %d, %d, %f)", self._name, time, step, iteration, step_size)
        
        assert step_size > 0.0, "step_size too small: {0}".format(step_size)
        #assert self._biggerThan(step_size, 0), "step_size too small: {0}".format(step_size)
        assert iteration == 0, "Fixed point iterations not supported yet."
        
        current_input = self.getValues(step, iteration, 
                                       self._getInputVars())[self.armature_current]
        previous_input = self.getValues(step-1, iteration, 
                                        self._getInputVars())[self.armature_current]
        
        output_value = 0
        
        l.debug("%s.previous_input=%f", self._name, previous_input)
        l.debug("%s.current_input=%f", self._name, current_input)
        
        step_info = STEP_ACCEPT
        proposed_step_size = step_size
        
        if self.__crossUpward:
            if (not self._biggerThan(previous_input, self.__threshold)) \
                    and self._biggerThan(current_input, self.__threshold):
                l.debug("Crossing detected from %f to %f", 
                        previous_input, current_input)
                l.debug("But step too large.")
                step_info = STEP_DISCARD
                 
                # Convert this into a zero crossing problem
                negative_value = previous_input - self.__threshold
                positive_value = current_input - self.__threshold
                
                # Estimate the step size by regula-falsi
                proposed_step_size = (step_size * (- negative_value)) / (positive_value - negative_value)
                assert proposed_step_size > 0.0, "Problem with the signals and tolerances. All hope is lost."
                
            elif (not self._biggerThan(previous_input, self.__threshold))\
                and self._isClose(current_input, self.__threshold):
                l.debug("Crossing detected from %f to %f", 
                        previous_input, current_input)
                l.debug("And step size is acceptable.")
                output_value = 1
                
        
        l.debug("%s.output_value=%s", self._name, output_value)
        self.setValues(step, iteration, {self.out_obj: output_value})
        
        l.debug("<%s._doInternalSteps() = (%s, %d)", 
                self._name, step_info, proposed_step_size)
        return (step_info, proposed_step_size)
    
    