from abstract_units.StatechartSimulationUnit_Event import StatechartSimulationUnit_Event


class DriverControllerStatechartFMU_Event(StatechartSimulationUnit_Event):
    """
    This is a simple controller for the power window case study.
    It takes input events (dup, ddown, dstop, obj) representing the wishes of the driver 
        and whether an object has been detected,
        and produces *output events* (up, down, stop), 
        representing instructions for the power system.
    It has the states
        Neutral    (initial)
        Up
        Down
        Object
    And transitions
        Neutral --dup/up--> Up
        Neutral --ddown/down--> Down
        Up --dstop/stop--> Neutral
        Up --ddown/down--> Down
        Up --obj/down--> Object
        Down --dstop/stop--> Neutral
        Down --dup/up--> Up 
        Object --after(1)/stop--> Neutral
    """
    
    def __init__(self, name, num_rtol, num_atol):
        
        def state_transition(current_state, input_event, elapsed):
            # Check for transitions enabled by input_event
            if input_event != None:
                if current_state=="Neutral":
                    if input_event == "dup":
                        return ("up","Up",True,StatechartSimulationUnit_Event.TRIGGER_INPUT)
                    if input_event == "ddown":
                        return ("down","Down",True,StatechartSimulationUnit_Event.TRIGGER_INPUT)
                if current_state=="Up":
                    if input_event == "dstop":
                        return ("stop","Neutral",True,StatechartSimulationUnit_Event.TRIGGER_INPUT)
                    if input_event == "ddown":
                        return ("down","Down",True,StatechartSimulationUnit_Event.TRIGGER_INPUT)
                    if input_event == "obj":
                        return ("down","Object",True,StatechartSimulationUnit_Event.TRIGGER_INPUT)
                if current_state=="Down":
                    if input_event == "dstop":
                        return ("stop","Neutral",True,StatechartSimulationUnit_Event.TRIGGER_INPUT)
                    if input_event == "dup":
                        return ("up","Up",True,StatechartSimulationUnit_Event.TRIGGER_INPUT)
            # Check for after transitions
            if current_state=="Object":
                if self._biggerThan(elapsed, 1.0):
                    return ("stop","Neutral",True,StatechartSimulationUnit_Event.TRIGGER_AFTER)
            # No transition taken
            return (None, current_state, False, None)
        
        StatechartSimulationUnit_Event.__init__(self, name, num_rtol, num_atol, state_transition, autonomous=False)