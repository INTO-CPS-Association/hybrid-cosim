'''
Created on Mar 5, 2016

@author: claudio gomes
'''

import logging

from abstract_units.Utils import Utils


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
        self.__output_vars = list(state_vars)
        self.__output_vars.extend(self.__algebraic_vars)
        
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
        l.debug(">%s.rollback(%d)", self._name, toStep)
        # Cleans the computed_time from toStep onwards.
        assert toStep <= len(self.__computed_time), "Cannot rollback to a future step"
        
        Utils.trimList(self.__computed_time, toStep+1)
        
        for var in self.__state.keys():
            l.debug("Rolling back %s...", var)
            Utils.trimList(self.__state[var], toStep+1)
            l.debug("len(self.__state[var])=%d", len(self.__state[var]))
        
        
        l.debug("<%s.rollback()", self._name)
    
    def commit(self, step):
        pass
    
    def __recordTime(self, time, step, iteration, step_size):
        assert step <= len(self.__computed_time), "step = " + str(step) + " len(self.__computed_time)=" + str(len(self.__computed_time))
        if step == len(self.__computed_time):
            assert iteration == 0
            self.__computed_time.append([time + step_size])
        elif step < len(self.__computed_time):
            assert step == len(self.__computed_time) -1, "Makes no sense to rewrite past times, without rolling back first."
            if iteration == len(self.__computed_time[step]):
                self.__computed_time[step].append(time + step_size)
            elif iteration < len(self.__computed_time[step]):
                assert iteration == len(self.__computed_time[step]) - 1, "Weird use of the iteration records. Either rewrite the last iteration, or keep tracking them."
                self.__computed_time[step][iteration] = time + step_size
                
       
    def doStep(self, time, step, current_iteration, step_size):
        l.debug(">%s.doStep(t=%f, s=%d, i=%d, H=%f)", self._name,  time, step, current_iteration, step_size)
        assert self._mode == STEP_MODE, "Wrong mode: " + self._mode
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
        return result
    
    def _doInternalSteps(self, time, step, iteration, step_size):
        raise "Must be implemented in subclasses"

    def __computeOutputs(self, step, iteration, whichOnes=None):
        l.debug(">__computeOutputs(%d, %d, %s)", step, iteration, whichOnes)
        
        var_names = self.__algebraic_vars if whichOnes==None else whichOnes
        
        # This does not support algebraic loops.
        
        # Get the state and input vars to be used for the computation of the values
        # Only up-to-date values go in the calculations.
        # If a calcfunction crashes, it's because this FMU is not being used correctly
        current_state_snaptshot = Utils.getValuesUpToDate(self.__state, self._getStateVars(), step, iteration)
        current_input_snaptshot = Utils.getValuesUpToDate(self.__state, self._getInputVars(), step, iteration)
        
        l.debug("current_state_snaptshot = %s", current_state_snaptshot)
        l.debug("current_input_snaptshot = %s", current_input_snaptshot)
        
        l.debug("outputs to update = %s", self.__algebraic_vars)
        
        for var in var_names:
            new_value = self.__algebraic_functions[var](current_state_snaptshot, current_input_snaptshot)
            Utils.copyValueToStateTrace(self.__state, var, step, iteration, new_value, ensureExists=True)
        
        l.debug("Updated portion of the state:\n%s", 
                    self._printState(step, iteration, var_names))
        
        l.debug("<__computeOutputs()")
    
    def _ZOHOldValues(self, step, iteration):
        l.debug(">_ZOHOldValues(%d, %d)", step, iteration)
        assert iteration == 0, "Not supported yet."
        for state_var in self._getStateVars():
            if step == len(self.__state[state_var]):
                l.debug("Applying ZOH to %s...", state_var)
                self.__state[state_var].append([self.__state[state_var][step-1][-1]])
            else:
                l.debug("No need to ZOH %s.", state_var)
        l.debug("<_ZOHOldValues(%d, %d)", step, iteration)
        
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
        
    def setValues(self, step, iteration, values, ensureExists=True):
        l.debug(">%s.setValues(%d, %d, %s)", self._name, step, iteration, values)
        
        if values != None:
            Utils.copyMapToStateTrace(self.__state, step, iteration, values, ensureExists)
            
            self.__markAlgVars(step, iteration, dirty=True);
            
            l.debug("New state: \n%s", self._printState(step,iteration, values.keys()))
        else:
            l.debug("No values to set.")
        l.debug("<%s.setValues()", self._name)
        
    
    def getValues(self, step, iteration, var_names=None, zoh=False, ensureExists=False):
        var_names = self.__output_vars if var_names==None else var_names
        l.debug(">%s.getValues(%d, %d, %s)", self._name, step, iteration, var_names)
        if self.__areAlgVarsDirty(step, iteration, var_names):
            self.__computeOutputs(step, iteration, whichOnes=var_names)
            self.__markAlgVars(step, iteration, dirty=False, whichOnes=var_names);
        
        values = {}
        for var in var_names:
            if ensureExists:
                assert self.__state.has_key(var)
            
            if self.__state.has_key(var):
                stepToAccess = step
                iterationToAccess = iteration
                if stepToAccess >= len(self.__state[var]) and zoh:
                    assert stepToAccess == len(self.__state[var]), "Inconsistent state at step %d.".format(step)
                    stepToAccess = step-1
                    iterationToAccess = -1
                    l.debug("Getting old value for %s at step %d.", var, stepToAccess)
                    
                assert stepToAccess < len(self.__state[var]), "State is not initialized: " + str(self.__state)
                assert iterationToAccess < len(self.__state[var][stepToAccess])
                values[var] = self.__state[var][stepToAccess][iterationToAccess]
        
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
        
    
