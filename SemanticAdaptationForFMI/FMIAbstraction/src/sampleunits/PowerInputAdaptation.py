import logging

from units.AbstractSimulationUnit import AbstractSimulationUnit, STEP_ACCEPT

l = logging.getLogger()

class PowerInputAdaptation(AbstractSimulationUnit):
    """
    This is the adaptation of the events coming out of the Controller Statechart.
    It gets as input an event, and output two signals, to be coupled to the power system.
    Whenever it gets an input, it stores the appropriate signals for the output until another event comes along.
    It's basically a ZOH.
    
    Example interaction:_______________
    f = PowerInputAdaptation(...)
    f.enterInitMode()
    f.setValues(...,"SomeInEvent")
        This tells the FMU what the input is.
        The sFMU will record this input (if not "") to the internal state. 
        and initial input ("SomeInEvent").
    (up,down) = f.getValues(...)
        The values that can be returned are initial_up and initial_down
    f.exitInitMode()
    
    f.setValues(..., "SomeInEvent")
        The definition of a new event gets recorded by the fmu
    f.doStep(..., H)
        The internal state gets updated according to the new input event.
        Or kept the same if the new event is ""
    (up,down) = f.getValues(...)
        The last event processed is in the output variable, ready to be collected.
    ______________________________
    
    """
    
    def __init__(self, name):
        
        self.in_event = "in_event"
        self.out_down = "out_down"
        self.out_up = "out_up"
        input_vars = [self.in_event]
        state_vars = [self.out_down, self.out_up]
        
        algebraic_functions = {}
        
        AbstractSimulationUnit.__init__(self, name, algebraic_functions, state_vars, input_vars)
    
    def _doInternalSteps(self, time, step, iteration, cosim_step_size):
        l.debug(">%s._doInternalSteps(%f, %d, %d, %f)", self._name, time, step, iteration, cosim_step_size)
        
        assert iteration == 0, "Fixed point iterations not supported yet."
        
        previous_output = self.getValues(step-1, iteration, self._getStateVars())
        current_input = self.getValues(step, iteration, self._getInputVars())
        
        l.debug("%s.previous_output=%s", self._name, previous_output)
        l.debug("%s.current_input=%s", self._name, current_input)
        
        next_output = previous_output
        in_ev = current_input[self.in_event]
        if in_ev != "":
            l.debug("Updating internal state due to input %s...", in_ev)
            next_out_up = 1.0 if in_ev=="up" else 0.0
            next_out_down = 1.0 if in_ev=="down" else 0.0
            next_output = {self.out_down: next_out_down, self.out_up: next_out_up}
            
        # Store the values into the state
        self.setValues(step, iteration, {self.out_down: next_output[self.out_down],
                                         self.out_up: next_output[self.out_up] })
        
        
        l.debug("<%s._doInternalSteps() = (%s, %d)", self._name, STEP_ACCEPT, cosim_step_size)
        return (STEP_ACCEPT, cosim_step_size)