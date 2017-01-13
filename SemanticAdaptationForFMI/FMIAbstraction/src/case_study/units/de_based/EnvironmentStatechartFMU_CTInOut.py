import logging

from abstract_units.StatechartSimulationUnit_CTInOut import StatechartSimulationUnit_CTInOut

l = logging.getLogger()

class EnvironmentStatechartFMU_CTInOut(StatechartSimulationUnit_CTInOut):
    """
    This is a simple environment for the power window case study.
    It has the states
        Neutral    (initial)
        Up
        Down
    And the outputs are: up, down, valued at either 0 or 1.
    """
    
    def __init__(self, name, num_rtol, num_atol):
        
        input_vars = []
        self.out_up = "out_up"
        self.out_down = "out_down"
        
        output_vars = [self.out_up , self.out_down]
        
        initial_state = "Initial"
                
        def state_transition(current_state, inputs, previous_inputs, elapsed, inputs_available):
            l.debug(">%s.state_transition(%s, %s, %f)", self._name, current_state, inputs, elapsed)
            
            output_assignment = {}
            target_state = ""
            transition_taken = False
            trigger = StatechartSimulationUnit_CTInOut.TRIGGER_DEFAULT
            
            if current_state == "Initial":
                target_state = "Neutral"
                transition_taken = True
                trigger = StatechartSimulationUnit_CTInOut.TRIGGER_DEFAULT
                output_assignment[self.out_up] = 0
                output_assignment[self.out_down] = 0
            elif current_state == "Neutral":
                if self._biggerThan(elapsed, 0.5):
                    target_state = "Up"
                    transition_taken = True
                    trigger = StatechartSimulationUnit_CTInOut.TRIGGER_AFTER
                    output_assignment[self.out_up] = 1
                
            l.debug("<%s.state_transition(%s, %s, %s, %s)", self._name, output_assignment, target_state, transition_taken, trigger)
            return (output_assignment, target_state, transition_taken, trigger)
        
        StatechartSimulationUnit_CTInOut.__init__(self, name, 
                                                  num_rtol, num_atol, 
                                                  state_transition, initial_state, 
                                                  input_vars, output_vars)
        
