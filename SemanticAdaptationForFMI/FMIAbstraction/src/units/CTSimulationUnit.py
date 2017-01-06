'''
Created on Mar 5, 2016

@author: claudio gomes
'''
import numpy

from units.AbstractSimulationUnit import AbstractSimulationUnit

class CTSimulationUnit(AbstractSimulationUnit):
    """
    Represents a continuous time simulation unit.
    To be subclassed by concrete implementations
    """
    
    def __init__(self, num_rtol, num_atol, calc_functions, state_vars, input_vars):
        AbstractSimulationUnit.__init__(self, calc_functions, state_vars, input_vars)
        
        self._num_rtol = num_rtol
        self._num_atol = num_atol
    
    
    def _isClose(self, a, b):
        return numpy.isclose(a,b, self._num_rtol, self._num_atol)
    
    def _biggerThan(self, a, b):
        return not numpy.isclose(a,b, self._num_rtol, self._num_atol) and a > b
    
    def _doNumericalSteps(self, current_time, step, current_iteration, step_size, iteration_running):
        raise("To be implemented by subclasses")
    
    def _doInternalSteps(self, current_time, step, current_iteration, step_size, iteration_running):
        assert self._biggerThan(step_size, 0), "step_size too small: {0}".format(step_size)
        assert current_iteration >= 0
        
        iteration_running = current_iteration > 0
        
        return self._doNumericalSteps(current_time, step, current_iteration, step_size, iteration_running)
                
                
                
                