'''
Created on Mar 5, 2016

@author: claudio gomes
'''

from units.CTSimulationUnit import CTSimulationUnit
import logging
l = logging.getLogger()


class CTSimulationUnit_Euler(CTSimulationUnit):
    """
    Represents a continuous time simulation unit that does internal forward euler steps 
        and does constant input extrapolation
    To be subclassed by concrete implementations
    """
    
    def __init__(self, name, num_rtol, num_atol, internal_step_size,
                 state_derivatives, algebraic_functions, 
                 input_vars):
        CTSimulationUnit.__init__(self, name, num_rtol, num_atol,
                                  state_derivatives, algebraic_functions,
                                  input_vars)
        
        self.__internal_step_size = internal_step_size
    
    def _doNumericalStep(self, next_x, previous_x, inputs, time, step, iteration, stop_time):
        l.debug(">%s._doNumericalStep(%s, %s, %s, %f, %d, %d, %f)", 
                self._name, next_x, previous_x, inputs, time, step, iteration, stop_time)
        
        hit_stop_time = self._biggerThan(time + self.__internal_step_size, stop_time)
        step_size = stop_time - time if hit_stop_time else self.__internal_step_size
        for state_var in self._state_derivatives.keys():
            state_derivative_function = self._state_derivatives[state_var]
            der_state_var = state_derivative_function(previous_x, inputs)
            next_x[state_var] = previous_x[state_var] + der_state_var * step_size
        
        l.debug("<%s._doNumericalStep()=(%s, %f)", 
                self._name, not hit_stop_time, step_size)
        return (not hit_stop_time, step_size)
    