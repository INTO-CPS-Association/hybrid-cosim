import logging

from units.StatechartSimulationUnit import StatechartSimulationUnit


l = logging.getLogger()

class EnvironmentStatechartFMU(StatechartSimulationUnit):
    """
    This is a simple environment for the power window case study.
    It has the states
        Neutral    (initial)
        Up
        Down
    And the transitions are self explanatory.
    """
    
    def __init__(self, name, num_rtol, num_atol):
        
        def state_transition(current_state, input_event, elapsed):
            l.debug(">%s.state_transition(%s, %s, %f)", self._name, current_state, input_event, elapsed)
            # Check for after transitions
            if current_state=="Neutral":
                if self._biggerThan(elapsed, 0.5):
                    return ("dup","Up",True,StatechartSimulationUnit.TRIGGER_AFTER)
            # No transition taken
            return ("", current_state, False, None)
            l.debug("<%s.state_transition(%s, %s, %f)", self._name, current_state, input_event, elapsed)
            
        
        StatechartSimulationUnit.__init__(self, name, num_rtol, num_atol, state_transition, autonomous=True)
        