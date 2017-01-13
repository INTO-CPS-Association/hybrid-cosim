import logging

from abstract_units.StatechartSimulationUnit_CTInOut import StatechartSimulationUnit_CTInOut


l = logging.getLogger()

class DriverControllerStatechartFMU_CTInOut(StatechartSimulationUnit_CTInOut):
    """
    This is a simple controller for the power window case study. It takes input
    signals (dup, ddown, obj) representing the wishes of the driver and whether
    an object has been detected. These are piece wise constant values (0, or 1).
    The outputs are up or down, representing the instructions to be power system.
    
    It has the states
        Neutral    (initial)
        Up
        Down
        Object
    And transitions
        Neutral --dup/up=1--> Up
        Neutral --ddown/down=1--> Down
        Up --dstop/up=0--> Neutral
        Up --ddown/up=0,down=1--> Down
        Up --obj/up=0,down=1--> Object
        Down --dstop/down=0--> Neutral
        Down --dup/down=0,up=1--> Up 
        Object --after(1)/down=0--> Neutral
    """
    
    def __init__(self, name, num_rtol, num_atol):
        
        self.in_dup = "in_dup"
        self.in_ddown = "in_ddown"
        self.in_obj = "in_obj"
        input_vars = [self.in_dup, self.in_ddown, self.in_obj]
        
        self.out_up = "out_up"
        self.out_down = "out_down"
        output_vars = [self.out_up , self.out_down]
        
        initial_state = "Initial"
        
        def state_transition(current_state, inputs, previous_inputs, elapsed):
            l.debug(">%s.state_transition(%s, %s, %f)", self._name, current_state, inputs, elapsed)
            
            output_assignment = {}
            target_state = ""
            transition_taken = False
            trigger = StatechartSimulationUnit_CTInOut.TRIGGER_DEFAULT
            
            if current_state=="Initial":
                target_state = "Neutral"
                transition_taken = True
                trigger = StatechartSimulationUnit_CTInOut.TRIGGER_DEFAULT
                output_assignment[self.out_up] = 0
                output_assignment[self.out_down] = 0
            elif current_state=="Neutral":
                if inputs[self.in_dup] == 1:
                    target_state = "Up"
                    transition_taken = True
                    trigger = StatechartSimulationUnit_CTInOut.TRIGGER_INPUT
                    output_assignment[self.out_up] = 1
                elif inputs[self.in_ddown] == 1:
                    target_state = "Down"
                    transition_taken = True
                    trigger = StatechartSimulationUnit_CTInOut.TRIGGER_INPUT
                    output_assignment[self.out_down] = 1
            elif current_state=="Up":
                if inputs[self.in_obj] == 1:
                    target_state = "Object"
                    transition_taken = True
                    trigger = StatechartSimulationUnit_CTInOut.TRIGGER_INPUT
                    output_assignment[self.out_up] = 0
                    output_assignment[self.out_down] = 1
                elif inputs[self.in_ddown] == 1:
                    assert inputs[self.in_dup] == 0
                    target_state = "Down"
                    transition_taken = True
                    trigger = StatechartSimulationUnit_CTInOut.TRIGGER_INPUT
                    output_assignment[self.out_up] = 0
                    output_assignment[self.out_down] = 1
                elif inputs[self.in_dup] == 0:
                    target_state = "Neutral"
                    transition_taken = True
                    trigger = StatechartSimulationUnit_CTInOut.TRIGGER_INPUT
                    output_assignment[self.out_up] = 0
            elif current_state=="Down":
                if inputs[self.in_dup] == 1:
                    assert inputs[self.in_ddown] == 0
                    target_state = "Up"
                    transition_taken = True
                    trigger = StatechartSimulationUnit_CTInOut.TRIGGER_INPUT
                    output_assignment[self.out_up] = 1
                    output_assignment[self.out_down] = 0
                elif inputs[self.in_ddown] == 0:
                    target_state = "Neutral"
                    transition_taken = True
                    trigger = StatechartSimulationUnit_CTInOut.TRIGGER_INPUT
                    output_assignment[self.out_down] = 0
            elif current_state=="Object":
                if self._biggerThan(elapsed, 1.0):
                    target_state = "Neutral"
                    transition_taken = True
                    trigger = StatechartSimulationUnit_CTInOut.TRIGGER_AFTER
                    output_assignment[self.out_up] = 0
                    output_assignment[self.out_down] = 0
            
            l.debug("<%s.state_transition(%s, %s, %s, %s)", self._name, 
                    output_assignment, target_state, transition_taken, trigger)
            return (output_assignment, target_state, transition_taken, trigger)
            
        
        StatechartSimulationUnit_CTInOut.__init__(self, name, 
                                                  num_rtol, num_atol, 
                                                  state_transition, initial_state, 
                                                  input_vars, output_vars)