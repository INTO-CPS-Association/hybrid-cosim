'''
Created on Jan 13, 2016

@author: claudio gomes
'''
import logging

import numpy

from abstract_units.AbstractSimulationUnit import AbstractSimulationUnit, \
    STEP_ACCEPT, INIT_MODE


l = logging.getLogger()

class StatechartSimulationUnit_CTInOut(AbstractSimulationUnit):
    
    TRIGGER_AFTER = "After"
    TRIGGER_INPUT = "Input"
    TRIGGER_DEFAULT = "Default"
    
    """
    This class represents a generic statechart FMU which receives a continuous
    signal as input and outputs a continuous signal.
    
    The output signal is defined according to values that are computed from the
    current state, just like the modelica Stategraph library.
    
    The transitions can be taken according to conditions evaluated on the value
    of the input signals. For now, the only condition allowed is a crossing of
    the signal in the upward direction.
    
    The transitions have assignment actions that change the values of the
    output. It is not possible for a transition to affect a signal that is used
    as a trigger condition in some other transition. There are input variables
    for that. The outputs that are not assignment by the transitions keep the
    same value as before.
    
    Example interaction:_______________
    sFMU = StatechartSimulationUnit_CTInOut(...)
        At this point, the sFMU is not even in the initial state
    sFMU.enterInitMode()
        At this point the statechart moves into the initial state. If there are
        default transitions to be taken at this stage, they are taken. Any
        values that are assigned by these transitions will also be defined, so
        that in the next move, values can already be taken out of the
        statechart.
    sFMU.setValues(t=0, ...,x=v)
        This tells the FMU that signal x has value v at time 0.
    v = sFMU.getValues(t=0, ...)
        At time 0 there can be no crossings so no transition of that kind is taken. 
        If there are other kinds of     conditions on signals, then these would be evaluated here and possibly
        taken.
        If transitions set the output values, then at this point they can
        already be read.
    sFMU.exitInitMode()
    
    sFMU.setValues(t>0, ..., x=v)
        This tells the FMU that the signal x(t) = v. As with the initialisation
        model, transitions will be marked to be taken at time t, is not NOT the current time of the FMU.
    sFMU.doStep(t>0..., H)
        Notice that the FMU is still at time t, and that this functions tells
        him to move to t+H. If there is any after transition that happens
        between t an t+H, then that transition is taken. This includes the
        recursive computation of executing all default transitions and other
        after transitions that may be enabled in between. Then, if there are no
        more after transitions that happen between t and t+H, the internal clock
        is advanced to t+H and all the transitions that become enabled by the
        input values are taken, as well as any default transitions until nothing
        else remains to be computed.
    v = sFMU.getValues(t>0...)
        
    ______________________________
    """
    
    def __init__(self, name, num_rtol, num_atol, state_transition_function, initial_state, input_vars, output_vars):
        """
        The state transition functions hold the encoding of the statechart.
        They are called with the current state and the elapsed time on that state.
        """
        
        self._state_transition_function = state_transition_function
        
        self._num_rtol = num_rtol
        self._num_atol = num_atol
        
        self.__current_state = "state"
        
        self.__initial_state = initial_state
        
        self.__last_transition_time = 0.0
        
        state_vars = [self.__current_state] + output_vars
        
        AbstractSimulationUnit.__init__(self, name, {}, state_vars, input_vars)
    
    def _isClose(self, a, b):
        return numpy.isclose(a,b, self._num_rtol, self._num_atol)
    
    def _biggerThan(self, a, b):
        return not numpy.isclose(a,b, self._num_rtol, self._num_atol) and a > b
    
    def enterInitMode(self):
        l.debug(">%s.StatechartSimulationUnit_CTInOut.enterInitMode()", self._name)
        
        self.setValues(0, 0, {self.__current_state: self.__initial_state})
        
        # Compute all default transitions at this point
        state_snapshot = self.getValues(0, 0, [self.__current_state])
        input_snapshot = {}
        previous_input_snaptshop =  {}
        
        (next_state, output_assignments) = self._doStepFunction(0.0, 
                                                state_snapshot, input_snapshot, previous_input_snaptshop)
        
        # Commit the new state and outputs.
        AbstractSimulationUnit.setValues(self, 0, 0, {self.__current_state : next_state})
        AbstractSimulationUnit.setValues(self, 0, 0, output_assignments)
        
        AbstractSimulationUnit.enterInitMode(self)
        
        l.debug("<%s.StatechartSimulationUnit_CTInOut.enterInitMode()", self._name)
    
    def setValues(self, step, iteration, values):
        l.debug(">%s.StatechartSimulationUnit_CTInOut.setValues(%d, %d, %s)", self._name, step, iteration, values)
        
        AbstractSimulationUnit.setValues(self, step, iteration, values)
        
        if self._mode == INIT_MODE:
            assert step == 0
            state_snapshot = self.getValues(step, iteration, [self.__current_state])
            input_snapshot = self.getValues(step, iteration, self._getInputVars())
            previous_input_snaptshop =  {}
            
            (next_state, output_assignments) = self._doStepFunction(0.0, 
                                                    state_snapshot, input_snapshot, previous_input_snaptshop)
            
            # Commit the new state and outputs.
            AbstractSimulationUnit.setValues(self, step, iteration, {self.__current_state : next_state})
            AbstractSimulationUnit.setValues(self, step, iteration, output_assignments)
                
        l.debug("<%s.StatechartSimulationUnit_CTInOut.setValues()", self._name)
    
    
    def _doStepFunction(self, time, state, inputs, previous_inputs):
        """
        Runs all transitions that are enabled, or become enabled at time time with the inputs 
            valued *at that time*.
        """
        l.debug(">%s._doStepFunction(%f, %s, %s)", self._name, time, state, inputs)
        
        l.debug(">%s._runAllEnabledTransitions(%f, %s, %s)", self._name, time, state, inputs)
        
        inputs_available = len(inputs) > 0
        
        transition_taken = True
        statechart_state = state[self.__current_state]
        output_assignments = {}
        while transition_taken:
            elapsed = time - self.__last_transition_time
            """
            The state transition function is responsible for prioritising any simultaneously enabled transitions.
            The out_values is a map of assignments to the output variables.
            It will be merged with output_assignments
            """
            (out_values, new_state, transition_taken, trigger) = \
                self._state_transition_function(statechart_state, inputs, previous_inputs, elapsed, inputs_available)
            if transition_taken:
                l.debug("Transition taken from %s to %s because of %s. Produced assignments: %s.", 
                                statechart_state, new_state, trigger, out_values)
                
                output_assignments.update(out_values)
                l.debug("Merged assignments: %s", output_assignments)
                statechart_state = new_state
                self.__last_transition_time = time
            
        l.debug("Finished all enabled transitions.")
        
        l.debug("%s.state=%s", self._name, statechart_state)
        l.debug("%s.Merged assignments: %s", self._name, output_assignments)
        
        l.debug("<%s._doStepFunction()", self._name)
        return (statechart_state, output_assignments)
    
    
    def _doInternalSteps(self, time, step, iteration, cosim_step_size):
        l.debug(">%s._doInternalSteps(%f, %d, %d, %f)", 
                self._name, time, step, iteration, cosim_step_size)
        
        assert self._biggerThan(cosim_step_size, 0), "cosim_step_size too small: {0}".format(cosim_step_size)
        assert iteration == 0, "Fixed point iterations involving this component are not supported."
        
        state_snapshot = self.getValues(step-1, iteration, [self.__current_state])
        input_snapshot = self.getValues(step, iteration, self._getInputVars())
        previous_input_snaptshop = self.getValues(step-1, -1, self._getInputVars())
        
        (next_state, output_assignments) = self._doStepFunction(time+cosim_step_size, state_snapshot, input_snapshot, previous_input_snaptshop)
        
        # Commit the new state and outputs.
        self.setValues(step, iteration, {self.__current_state : next_state})
        self.setValues(step, iteration, output_assignments)
        # TODO Zero order hold the remaining outputs.
        self._ZOHOldValues(step, iteration)
        
        l.debug("<%s._doInternalSteps() = (%s, %d)", self._name, STEP_ACCEPT, cosim_step_size)
        return (STEP_ACCEPT, cosim_step_size)

          