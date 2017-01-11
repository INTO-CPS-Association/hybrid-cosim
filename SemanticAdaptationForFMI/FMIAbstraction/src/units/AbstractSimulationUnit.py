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
    
    def __init__(self, name, algebraic_functions, state_vars, input_vars):
        l.debug(">AbstractSimulationUnit(%s, %s, %s, %s)", name, algebraic_functions, state_vars, input_vars)
        
        self._name = name
        self.__state = {}
        self.__alg_value_dirty = {}
        self.__computed_time = []
        self._mode = INSTANTIATED_MODE
        
        self.__algebraic_functions = algebraic_functions
        self.__state_vars = state_vars
        self.__input_vars = input_vars
        self.__algebraic_vars = algebraic_functions.keys()
        self.__state_and_input_vars = list(state_vars)
        self.__state_and_input_vars.extend(input_vars)
        
        assert len(self.__state_and_input_vars) == len(self.__input_vars) + len(self.__state_vars)
        
        for var in state_vars:
            self.__state[var] = []
        for var in self.__algebraic_vars:
            self.__state[var] = []
            self.__alg_value_dirty[var] = False
        for var in input_vars:
            self.__state[var] = []
        
        l.debug("<AbstractSimulationUnit()")
    
    def _getInputAndStateVars(self):
        return self.__state_and_input_vars
    
    def _getStateVars(self):
        return self.__state_vars
    
    def _getInputVars(self):
        return self.__input_vars
    
    def rollback(self, toStep):
        # Cleans the computed_time from toStep onwards.
        assert toStep <= len(self.__computed_time), "Cannot rollback to a future step"
        Utils.trimList(self.__computed_time, toStep)
        raise "To be finished"
    
    def __recordTime(self, current_time, step, current_iteration, step_size):
        if current_iteration == 0:
            assert step == len(self.__computed_time)
            self.__computed_time.append([current_time + step_size])
        else:
            assert step == len(self.__computed_time) - 1
            assert current_iteration == len(self.__computed_time[step])
            self.__computed_time[step].append(current_time + step_size)
       
    def doStep(self, time, step, current_iteration, step_size):
        l.debug(">%s.doStep(t=%f, s=%d, i=%d, H=%f)", self._name,  time, step, current_iteration, step_size)
        assert self._mode == STEP_MODE
        assert step_size > 0
        
        """ This is not done here because it may not be possible to do it for 
                the current step as it has not been computed.
        if self.__alg_value_dirty:
            self.__computeOutputs(step, current_iteration)
            self.__alg_value_dirty = False
        """
        
        # Record time, even if the step is not accepted.
        self.__recordTime(time, step, current_iteration, step_size)
        
        result = self._doInternalSteps(time, step, current_iteration, step_size)
        l.debug("<%s.doStep()=%s", self._name, result)
    
    def _doInternalSteps(self, time, step, iteration, cosim_step_size):
        raise "Must be implemented in subclasses"

    def __computeOutputs(self, step, iteration):
        l.debug(">__computeOutputs(%d, %d)", step, iteration)
        # This does not support algebraic loops.
        
        # Get the state and input vars to be used for the computation of the values
        # Only up-to-date values go in the calculations.
        # If a calcfunction crashes, it's because this FMU is not being used correctly
        current_state_snaptshot = Utils.getValuesUpToDate(self.__state, self._getStateVars(), step, iteration)
        current_input_snaptshot = Utils.getValuesUpToDate(self.__state, self._getInputVars(), step, iteration)
        
        l.debug("current_state_snaptshot = %s", current_state_snaptshot)
        l.debug("current_input_snaptshot = %s", current_input_snaptshot)
        
        l.debug("outputs to update = %s", self.__algebraic_vars)
        
        for var in self.__algebraic_vars:
            new_value = self.__algebraic_functions[var](current_state_snaptshot, current_input_snaptshot)
            Utils.copyValueToStateTrace(self.__state, var, step, iteration, new_value)
        
        l.debug("Updated portion of the state:\n%s", 
                    self._printState(step, iteration, self.__algebraic_functions.keys()))
        
        l.debug("<__computeOutputs()")
        
    def __setDefaultValues(self, values):
        Utils.copyMapToStateTrace(self.__state, 0, 0, values)
    
    def _printState(self,step, iteration, varNames=None):
        varsToPrint = varNames if varNames != None else self.__state.keys()
        strState = ""
        for var in varsToPrint:
            strState += var + "=" + str(self.__state[var][step][iteration]) + "\n"
        return strState
    
    def __markAlgVars(self, step, iteration, dirty, whichOnes=None):
        algebraic_vars = self.__algebraic_vars if whichOnes==None else whichOnes
        for out_var in algebraic_vars:
            if self.__alg_value_dirty.has_key(out_var):
                self.__alg_value_dirty[out_var] = dirty
            
    def __areAlgVarsDirty(self, step, iteration, whichOnes=None):
        var_names = self.__algebraic_vars if whichOnes==None else whichOnes
        for out_var in var_names:
            if self.__alg_value_dirty.has_key(out_var):
                if self.__alg_value_dirty[out_var]:
                    return True
        return False
        
    def setValues(self, step, iteration, values):
        l.debug(">%s.setValues(%d, %d, %s)", self._name, step, iteration, values)
        Utils.copyMapToStateTrace(self.__state, step, iteration, values)
        
        self.__markAlgVars(step, iteration, dirty=True);
        
        l.debug("New state: \n%s", self._printState(step,iteration, values.keys()))
        l.debug("<%s.setValues()", self._name)
        
    
    def getValues(self, step, iteration, var_names):
        l.debug(">%s.getValues(%d, %d, %s)", self._name, step, iteration, var_names)
        if self.__areAlgVarsDirty(step, iteration, var_names):
            self.__computeOutputs(step, iteration)
            self.__markAlgVars(step, iteration, dirty=False, whichOnes=var_names);
        
        values = {}
        for var in var_names:
            assert self.__state.has_key(var)
            assert step < len(self.__state[var]), "State is not initialized: " + str(self.__state)
            assert iteration < len(self.__state[var][step])
            values[var] = self.__state[var][step][iteration]
        
        l.debug("<%s.getValues()=%s", self._name, values)
        return values
        
    def enterInitMode(self):
        l.debug(">%s.enterInitMode()", self._name)
        assert len(self.__computed_time) == 0
        self.__computed_time.append([0.0])
        
        self._mode = INIT_MODE
        l.debug("<%s.enterInitMode()", self._name)
        
    def exitInitMode(self):
        l.debug(">%s.exitInitMode()", self._name)
        if self.__areAlgVarsDirty(0,0):
            self.__computeOutputs(0,0)
            self.__markAlgVars(0,0, dirty=False)
        self._mode = STEP_MODE
        l.debug("<%s.exitInitMode()", self._name)
        
    
