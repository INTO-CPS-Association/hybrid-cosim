'''
Created on Mar 5, 2016

@author: claudio gomes
'''
import logging

import numpy

from abstract_units.AbstractSimulationUnit import AbstractSimulationUnit, \
    STEP_ACCEPT


l = logging.getLogger()

class StatechartSimulationUnit_Event(AbstractSimulationUnit):
    
    TRIGGER_AFTER = "After"
    TRIGGER_INPUT = "Input"
    TRIGGER_DEFAULT = "Default"
    
    """
    Represents the controller FMU in a statechart form.
    It has a single string input and a single string output, denoted event_in/out.
    The string can be None, to denote that no event occurs.
    When an event occurs, the input gets the string representation of the event.
    When no event occurs, it simply updated its internal time counters.
    Due to after(x) transitions, there can be events produced after a doStep is performed.
    Also, if an event occurs and its time does not coincide exactly with the next co-sim time, 
        then the FMU rejects the step size and returns the step that he actually did.
        
    This class is generic and is meant to be subclassed by concrete implementations of statecharts.
    
    It currently does not support rejecting the step size in order to precisely hit an event time.
    The cosim step size will just have to divide every after transition threshold.
    
    Example interaction:_______________
    sFMU = StatechartFMU(...)
        At this point, the sFMU is not even in the initial state
    sFMU.enterInitMode()
    sFMU.setValues(...,"someEvent", "InitialState")
        This tells the FMU that there is an event to be processed (can be None)
            and what the initial state is.
        Even if it is "", it needs to be called with "".
    "" = sFMU.getValues(...)
        Because there was no doStep call in between, the event returned here can only be None.
    sFMU.exitInitMode()
    
    sFMU.setValues(..., "SomeInEvent")
    sFMU.doStep(..., H)
        The sFMU will check if there are input events and compute any output event that may be due, 
            possibly making ALL state transitions that are enabled by None.
            This computation is part of the output functions.
            Also, if multiple events are produced, then only the last one will be taken into account.
        When no transitions are enable, the sFMU advances its elapsed time.
    
    "someReaction" = sFMU.getValues(...)
        The last event processed is in the output variable, ready to be collected.
    ______________________________
    """
    
    def __init__(self, name, num_rtol, num_atol, state_transition_function, autonomous):
        """
        The state transition functions hold the encoding of the statechart.
        They are called with the current state and the elapsed time on that state.
        """
        
        self._state_transition_function = state_transition_function

        self._num_rtol = num_rtol
        self._num_atol = num_atol
        
        self.in_event = "__in_event"
        self.out_event = "__out_event"
        self.__current_state = "state"
        
        self.__last_transition_time = 0.0
        
        self.__autonomous = autonomous
        
        input_vars = [self.in_event] if not autonomous else []
        
        AbstractSimulationUnit.__init__(self, name, {}, [self.__current_state, self.out_event], input_vars)
    
    def _isClose(self, a, b):
        return numpy.isclose(a,b, self._num_rtol, self._num_atol)
    
    def _biggerThan(self, a, b):
        return not numpy.isclose(a,b, self._num_rtol, self._num_atol) and a > b
    
    """
    The _doStepFunction function will compute state transitions as long as they are enable
        and place the events that each transition taken may produce in the self.__outputEvent.
    """
    def _doStepFunction(self, time, state, inputs):
        """
        state is {self.__current_state : __current_state}
        input is {self.input : input}
        """
        l.debug(">%s._doStepFunction(%f, %s, %s)", self._name, time, state, inputs)
        
        transition_taken = True
        old_state = state[self.__current_state]
        inputToConsume = inputs[self.in_event] if not self.__autonomous else ""
        output_event = ""
        while transition_taken:
            elapsed = time - self.__last_transition_time
            (out_event, new_state, transition_taken, trigger) = self._state_transition_function(old_state, inputToConsume, elapsed)
            if transition_taken:
                l.debug("Transition taken from %s to %s because of %s. Produced event: %s.", 
                                old_state, new_state, trigger, out_event)
                output_event = out_event if out_event != "" else output_event
                old_state = new_state
                self.__last_transition_time = time
                if trigger==StatechartSimulationUnit_Event.TRIGGER_INPUT:
                    inputToConsume = ""
            else:
                l.debug("No transition taken.")
        l.debug("Finished all enabled transitions.")
        
        l.debug("%s.state=%s", self._name, old_state)
        l.debug("%s.output_event=%s", self._name, output_event)
        
        l.debug("<%s._doStepFunction()", self._name)
        return (old_state, output_event)
    
    
    def _doInternalSteps(self, time, step, iteration, cosim_step_size):
        l.debug(">%s._doInternalSteps(%f, %d, %d, %f)", 
                self._name, time, step, iteration, cosim_step_size)
        
        assert self._biggerThan(cosim_step_size, 0), "cosim_step_size too small: {0}".format(cosim_step_size)
        assert iteration == 0, "Fixed point iterations involving this component are not supported."
        
        state_snapshot = self.getValues(step-1, iteration, [self.__current_state])
        input_snapshot = self.getValues(step, iteration, self._getInputVars())
        
        (next_state, output_event) = self._doStepFunction(time+cosim_step_size, state_snapshot, input_snapshot)
        
        # Commit the new state
        self.setValues(step, iteration, {self.__current_state : next_state, self.out_event : output_event})
        
        l.debug("<%s._doInternalSteps() = (%s, %d)", self._name, STEP_ACCEPT, cosim_step_size)
        return (STEP_ACCEPT, cosim_step_size)

                