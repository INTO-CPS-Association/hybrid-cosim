import logging

from units.AbstractSimulationUnit import AbstractSimulationUnit, STEP_ACCEPT

l = logging.getLogger()

class PowerInputAdaptation(AbstractSimulationUnit):
    """
    This is the adaptation of the events coming out of the Controller Statechart.
    It gets as input an event, and output two signals, to be coupled to the power system.
    Whenever it gets an input, it stores the appropriate signals for the output until another event comes along.
    It's basically a ZOH.
    """
    
    def __init__(self, name):
        
        self.out_down = "out_down"
        self.out_up = "out_up"
        self.in_event = "in_event"
        self.__current_down = "__current_down"
        self.__current_up = "__current_up"
        input_vars = [self.in_event]
        state_vars = [self.__current_down, self.__current_up]
        
        def calc_up(x, u):
            in_ev = x[self.in_event]
            output = x[self.__current_up]
            if in_ev != "":
                output = 1.0 if in_ev=="up" else 0.0
            return output
        
        def calc_down(x, u):
            in_ev = x[self.in_event]
            output = x[self.__current_down]
            if in_ev != "":
                output = 1.0 if in_ev=="down" else 0.0
            return output
        
        algebraic_functions = {self.out_up : calc_up, self.out_down: calc_down}
        
        AbstractSimulationUnit.__init__(self, name, algebraic_functions, state_vars, input_vars)
    
    def _doInternalSteps(self, time, step, iteration, cosim_step_size):
        l.debug(">%s._doInternalSteps(%f, %d, %d, %f)", self._name, time, step, iteration, cosim_step_size)
        
        assert iteration == 0, "Fixed point iterations not supported yet."
        
        current_output = self.getValues(step, iteration, [self.out_up, self.out_down])
        
        l.debug("current_output=%f", current_output)
        
        # Store the values into the state
        self.setValues(step, iteration, {self.__current_down: current_output[self.out_down],
                                         self.__current_up: current_output[self.out_up] })
        
        
        l.debug("<%s._doInternalSteps() = (%s, %d)", self._name, STEP_ACCEPT, cosim_step_size)
        return (STEP_ACCEPT, cosim_step_size)