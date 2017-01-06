'''
Created on Mar 5, 2016

@author: claudio gomes
'''
from units.Utils import Utils

import logging
l = logging.getLogger()

INIT_MODE = "Initialization"
INSTANTIATED_MODE = "Instantiated"
STEP_MODE = "Stepping"
STEP_DISCARD = "Step_Discard"
STEP_ACCEPT = "Step_Accept"

class AbstractSimulationUnit(object):
    """
    Represents an abstraction simulation unit.
    Each simulation unit stores the following traces:
        - State trace: a map of vars to lists (string -> list(list(float)))
            The first list represents a co-simulation step.
            In each co-simulation step, due to fixed point iterations, one can have many computations of states.
            This is important to keep track of to later analyze divergence.
        - Computed time trace: a list of lists.
            Each list represents the times computed at a specific step, through many iterations.
    The computed time trace stores the times (as a float) indexed by the step performed by this simulation unit.
    The same index is used to access the Input, Output and State traces.
    It is important to keep the times at which simulation was performed 
    because, internally, different simulation units might compute 
    at different rates even when they agree on the external 
    communication step size.
    """
    
    def __init__(self, calc_functions, state_vars, input_vars):
        l.debug(">AbstractSimulationUnit(%s, %s, %s)", calc_functions, state_vars, input_vars)
        
        self.__state = {}
        self.__computed_time = []
        self.__calc_functions = calc_functions
        self.__mode = INSTANTIATED_MODE
        self.__values_dirty = False
        
        self.__state_vars = state_vars
        self.__input_vars = input_vars
        self.__non_output_vars = list(state_vars)
        self.__non_output_vars.extend(input_vars)
        
        assert len(self.__non_output_vars) == len(self.__input_vars) + len(self.__state_vars)
        
        for var in state_vars:
            self.__state[var] = []
        
        for var in input_vars:
            self.__state[var] = []
        
        l.debug("<AbstractSimulationUnit()")
    
    def _getNonOutputVars(self):
        return self.__non_output_vars
    
    def _getInputVars(self):
        return self.__input_vars
    
    def _getStateVars(self):
        return self.__state_vars
    
    def rollback(self, toStep):
        # Cleans the computed_time from toStep onwards.
        assert toStep <= len(self.__computed_time), "Cannot rollback to a future step"
        Utils.trimList(self.__computed_time, toStep)
        raise "To be finished"
        
    def doStep(self, current_time, step, current_iteration, step_size):
        l.debug(">doStep(t=%f, s=%d, i=%d, H=%f)", current_time, step, current_iteration, step_size)
        assert self.__mode == STEP_MODE
        assert step_size > 0
        
        if self.__values_dirty:
            self.__calculateValues(step, current_iteration)
            self.__values_dirty = False
        
        iteration_running = current_iteration > 0
        
        # Record time, even if the step is not accepted.
        if not iteration_running:
            assert step == len(self.__computed_time)
            self.__computed_time.append([current_time + step_size])
        else:
            assert step == len(self.__computed_time) - 1
            assert current_iteration == len(self.__computed_time[step])
            self.__computed_time[step].append(current_time + step_size)
        
        result = self._doInternalSteps(current_time, step, current_iteration, step_size, iteration_running)
        l.debug("<doStep()=%s", result)
    
    def _doInternalSteps(self, current_time, step, current_iteration, step_size, iteration_running):
        raise "Must be implemented in subclasses"

    def __calculateValues(self, current_step, current_iteration):
        l.debug(">__calculateValues(%d, %d)", current_step, current_iteration)
        # This does not support algebraic loops.
        
        # Get the state and input vars to be used for the computation of the values
        current_state_snaptshot = {}
        for var in self.__non_output_vars:
            # Only up-to-date values go in the calculations.
            # If a calcfunction crash, it's because this FMU is not being used correctly
            if current_step < len(self.__state[var]):
                if current_iteration < self.__state[var][current_step]:
                    current_state_snaptshot[var] = self.__state[var][current_step][current_iteration]
        
        l.debug("current_state_snaptshot = %s", current_state_snaptshot)
        
        for var in self.__calc_functions:
            assert self.__state.has_key(var)
            new_value = self.__calc_functions[var](current_state_snaptshot)
            if current_iteration==0:
                assert current_step == len(self.__state[var])
                self.__state[var].append([new_value])
            else:
                assert current_step == len(self.__state[var])-1
                assert current_iteration == len(self.__state[var][current_step])
                self.__state[var][current_step].append(new_value)
        
        l.debug("Updated portion of the state:\n%s", self._printState(current_step, current_iteration, self.__calc_functions.keys()))
        
        l.debug("<__calculateValues()")
        
    def __setDefaultValues(self, values):
        Utils.copyMapToStateTrace(self.__state, 0, 0, values)
    
    def _printState(self,step,iteration, varNames=None):
        varsToPrint = varNames if varNames != None else self.__state.keys()
        strState = ""
        for var in varsToPrint:
            strState += var + "=" + str(self.__state[var][step][iteration]) + "\n"
        return strState
        
    def setValues(self, current_step, current_iteration, values):
        l.debug(">setValues(%d, %d, %s)", current_step, current_iteration, values)
        Utils.copyMapToStateTrace(self.__state, current_step, current_iteration, values)
        self.__values_dirty = True
        l.debug("New state: \n%s", self._printState(current_step,current_iteration, values.keys()))
        l.debug("<setValues()")
        
    
    def getValues(self, current_step, current_iteration, var_names):
        l.debug(">getValues(%d, %d, %s)", current_step, current_iteration, var_names)
        if self.__values_dirty:
            self.__calculateValues(current_step, current_iteration)
            self.__values_dirty = True
        
        values = {}
        for var in var_names:
            assert self.__state.has_key(var)
            assert current_step < len(self.__state[var]), "State is not initialized: " + str(self.__state)
            assert current_iteration < len(self.__state[var][current_step])
            values[var] = self.__state[var][current_step][current_iteration]
        
        l.debug("<getValues()=%s", values)
        return values
        
    def enterInitMode(self):
        l.debug(">enterInitMode()")
        assert len(self.__computed_time) == 0
        self.__computed_time.append([0.0])
        
        self.__mode = INIT_MODE
        l.debug("<enterInitMode()")
        
    def exitInitMode(self):
        l.debug(">exitInitMode()")
        if self.__values_dirty:
            self.__calculateValues(0, 0)
            self.__values_dirty = False
        self.__mode = STEP_MODE
        l.debug("<exitInitMode()")
        
    
