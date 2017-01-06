'''
Created on Mar 5, 2016

@author: claudio gomes
'''

from units.AbstractSimulationUnit import STEP_ACCEPT
from units.CTSimulationUnit import CTSimulationUnit
import logging
l = logging.getLogger()


class CTSimulationUnit_Euler(CTSimulationUnit):
    """
    Represents a continuous time simulation unit that does internal forward euler steps 
        and does constant input extrapolation
    To be subclassed by concrete implementations
    """
    
    def __init__(self, num_rtol, num_atol, internal_step_size, 
                 state_derivatives, calc_functions, 
                 state_vars, input_vars):
        CTSimulationUnit.__init__(self,num_rtol, num_atol, calc_functions, state_vars, input_vars)
        
        self.__state_derivatives = state_derivatives
        self.__internal_step_size = internal_step_size
    
    def _doNumericalSteps(self, current_time, step, current_iteration, step_size, iteration_running):
        l.debug(">doNumericalSteps(%f, %d, %d, %f, %s)", current_time, step, current_iteration, step_size, iteration_running)
        
        assert not iteration_running, "Not supported"
        
        num_steps = int(round(step_size / self.__internal_step_size));
        actual_step_size = step_size / num_steps; # Takes care of internal step size not dividing the co-sim step size.
        
        l.debug("num_steps = %d", num_steps)
        l.debug("actual_step_size = %f", actual_step_size)
        
        # Use double buffering in the internal steps. 
        # This ensures that any computation in the state derivatives use consistent values
        state_buffers = [self.getValues(step-1, current_iteration, self._getStateVars()), {}]
        next_state_idx = 1;
        previous_state_idx = 0;
        input_buffer = self.getValues(step, current_iteration, self._getInputVars())
        
        for microstep in range(num_steps):
            l.debug("microstep = %d", microstep)
            l.debug("state = %s", state_buffers[previous_state_idx])
            for state_var in self.__state_derivatives.keys():
                state_derivative_function = self.__state_derivatives[state_var]
                previous_state = state_buffers[previous_state_idx]
                der_state_var = state_derivative_function(previous_state, input_buffer)
                state_buffers[next_state_idx][state_var] = previous_state[state_var] + der_state_var * actual_step_size
            # TODO Any input extrapolation would be done here by changing the input_buffer
            
            # flip the buffers
            l.debug("next_state_idx = %d, previous_state_idx = %d", next_state_idx, previous_state_idx)
            next_state_idx = (next_state_idx+1) % 2
            previous_state_idx = (previous_state_idx+1) % 2
            l.debug("next_state_idx = %d, previous_state_idx = %d", next_state_idx, previous_state_idx)
        
        # Commit the new state
        self.setValues(step, current_iteration, state_buffers[previous_state_idx])
        
        l.debug("<doNumericalSteps() = (%s, %d)", STEP_ACCEPT, step_size)
        return (STEP_ACCEPT, step_size)