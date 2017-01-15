import logging

import numpy

from abstract_units.AbstractSimulationUnit import AbstractSimulationUnit, \
    STEP_ACCEPT


l = logging.getLogger()

class InacurateControllerArmatureAdaptation_CT(AbstractSimulationUnit):
    """
    This is the adaptation of the armature signal coming from the power system and into the controller statechart.
    The input will be the armature continuous signal.
    The output will be a pulse signal obj that can either be 0, or 1 whenever the absolute value of 
        the armature signal exceeds a certain threshold.
    
    Note that we could have coded a generic signal crossing adaptation unit 
        and there is a whole range of pathological cases that we are not dealing with now.
        For these, see the implementation of the AbstractZeroCrossingBlock 
        of the DiracCBD Simulator
        
    The detailed behaviour of this block is as follows:
    ______________________________
    f = InacurateControllerArmatureAdaptation_CT(...)
    f.enterInitMode()
    f.setValues(...,armature)
        The FMU records this value in its internal state.
    v = f.getValues(...)
        v is zero at this point because there can be no crossing at time 0. 
    f.exitInitMode()
    
    f.setValues(t,..., armature)
        The FMU records the value as the input at time t.
    f.doStep(..., H)
        The FMU checks whether the current input has crossed the given threshold, 
            taking into account the previous value of the input, 
            already stored in the internal state.
        The output value is then calculated and the current input moved into the internal state.
    v = f.getValues(...)
        Gets the output event. Can either be 0, or 1.
    ______________________________
    
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
        
        assert self._biggerThan(step_size, 0), "step_size too small: {0}".format(step_size)
        assert iteration == 0, "Fixed point iterations not supported yet."
        
        current_input = self.getValues(step, iteration, self._getInputVars())[self.armature_current]
        previous_input = self.getValues(step-1, iteration, self._getInputVars())[self.armature_current]
        
        output_value = 0
        
        l.debug("%s.previous_input=%f", self._name, previous_input)
        l.debug("%s.current_input=%f", self._name, current_input)
        
        if (not self._biggerThan(previous_input, self.__threshold)) \
                and self._biggerThan(current_input, self.__threshold) \
                and self.__crossUpward:
            output_value = 1
        
        l.debug("%s.output_value=%s", self._name, output_value)
        self.setValues(step, iteration, {self.out_obj: output_value})
        
        l.debug("<%s._doInternalSteps() = (%s, %d)", self._name, STEP_ACCEPT, step_size)
        return (STEP_ACCEPT, step_size)
    
    