
#include <stdlib.h>
#include <string.h>
#include "sc_types.h"
#include "Powerwindow.h"
#include "PowerwindowRequired.h"
/*! \file Implementation of the state machine 'powerwindow'
*/

/* prototypes of all internal functions */
static sc_boolean powerwindow_check_main_region_Normal_operation_tr0_tr0(const Powerwindow* handle);
static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_tr0_tr0(const Powerwindow* handle);
static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_tr1_tr1(const Powerwindow* handle);
static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr0_tr0(const Powerwindow* handle);
static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr1_tr1(const Powerwindow* handle);
static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down_tr0_tr0(const Powerwindow* handle);
static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_down_tr0_tr0(const Powerwindow* handle);
static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_up_tr0_tr0(const Powerwindow* handle);
static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Passenger_up_tr0_tr0(const Powerwindow* handle);
static sc_boolean powerwindow_check_main_region_Emergency_operation_tr0_tr0(const Powerwindow* handle);
static void powerwindow_effect_main_region_Normal_operation_tr0(Powerwindow* handle);
static void powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_tr0(Powerwindow* handle);
static void powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_tr1(Powerwindow* handle);
static void powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr0(Powerwindow* handle);
static void powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr1(Powerwindow* handle);
static void powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down_tr0(Powerwindow* handle);
static void powerwindow_effect_main_region_Normal_operation_r1_Driver_down_tr0(Powerwindow* handle);
static void powerwindow_effect_main_region_Normal_operation_r1_Driver_up_tr0(Powerwindow* handle);
static void powerwindow_effect_main_region_Normal_operation_r1_Passenger_up_tr0(Powerwindow* handle);
static void powerwindow_effect_main_region_Emergency_operation_tr0(Powerwindow* handle);
static void powerwindow_enact_main_region_Emergency_operation(Powerwindow* handle);
static void powerwindow_exact_main_region_Emergency_operation(Powerwindow* handle);
static void powerwindow_enseq_main_region_Normal_operation_default(Powerwindow* handle);
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_default(Powerwindow* handle);
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_default(Powerwindow* handle);
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down_default(Powerwindow* handle);
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_down_default(Powerwindow* handle);
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_up_default(Powerwindow* handle);
static void powerwindow_enseq_main_region_Normal_operation_r1_Passenger_up_default(Powerwindow* handle);
static void powerwindow_enseq_main_region_Emergency_operation_default(Powerwindow* handle);
static void powerwindow_enseq_main_region_default(Powerwindow* handle);
static void powerwindow_enseq_main_region_Normal_operation_r1_default(Powerwindow* handle);
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_r1_default(Powerwindow* handle);
static void powerwindow_exseq_main_region_Normal_operation(Powerwindow* handle);
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral(Powerwindow* handle);
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation(Powerwindow* handle);
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down(Powerwindow* handle);
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_down(Powerwindow* handle);
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_up(Powerwindow* handle);
static void powerwindow_exseq_main_region_Normal_operation_r1_Passenger_up(Powerwindow* handle);
static void powerwindow_exseq_main_region_Emergency_operation(Powerwindow* handle);
static void powerwindow_exseq_main_region(Powerwindow* handle);
static void powerwindow_exseq_main_region_Normal_operation_r1(Powerwindow* handle);
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1(Powerwindow* handle);
static void powerwindow_react_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation(Powerwindow* handle);
static void powerwindow_react_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down(Powerwindow* handle);
static void powerwindow_react_main_region_Normal_operation_r1_Driver_down(Powerwindow* handle);
static void powerwindow_react_main_region_Normal_operation_r1_Driver_up(Powerwindow* handle);
static void powerwindow_react_main_region_Normal_operation_r1_Passenger_up(Powerwindow* handle);
static void powerwindow_react_main_region_Emergency_operation(Powerwindow* handle);
static void powerwindow_react_main_region__entry_Default(Powerwindow* handle);
static void powerwindow_react_main_region_Normal_operation_r1__entry_Default(Powerwindow* handle);
static void powerwindow_react_main_region_Normal_operation_r1_Driver_neutral_r1__entry_Default(Powerwindow* handle);
static void powerwindow_clearInEvents(Powerwindow* handle);
static void powerwindow_clearOutEvents(Powerwindow* handle);	

/*Created this myself... -> please */
void powerwindow_copy(Powerwindow* original, Powerwindow* copy){
	for (int i = 0; i<POWERWINDOW_MAX_ORTHOGONAL_STATES; i++){
		copy->stateConfVector[i] =  original->stateConfVector[i];
	}
	copy->stateConfVectorPosition = original->stateConfVectorPosition;
	copy->timeEvents.powerwindow_main_region_Emergency_operation_tev0_raised = original ->timeEvents.powerwindow_main_region_Emergency_operation_tev0_raised;
	copy->ifaceInput = original->ifaceInput;
	copy->ifaceOutput = original->ifaceOutput;

}

void powerwindow_init(Powerwindow* handle)
{
	sc_integer i;

	for (i = 0; i < POWERWINDOW_MAX_ORTHOGONAL_STATES; ++i) {
		handle->stateConfVector[i] = Powerwindow_last_state;
	}
	
	
	handle->stateConfVectorPosition = 0;

	powerwindow_clearInEvents(handle);
	powerwindow_clearOutEvents(handle);

	/* Default init sequence for statechart powerwindow */
	handle->ifaceOutput.up = bool_false;
	handle->ifaceOutput.down = bool_false;

}

void powerwindow_enter(Powerwindow* handle)
{
	/* Default enter sequence for statechart powerwindow */
	powerwindow_enseq_main_region_default(handle);
}

void powerwindow_exit(Powerwindow* handle)
{
	/* Default exit sequence for statechart powerwindow */
	powerwindow_exseq_main_region(handle);
}

sc_boolean powerwindow_isActive(const Powerwindow* handle) {
	sc_boolean result;
	if (handle->stateConfVector[0] != Powerwindow_last_state)
	{
		result =  bool_true;
	}
	else
	{
		result = bool_false;
	}
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean powerwindow_isFinal(const Powerwindow* handle){
   return bool_false;
}

static void powerwindow_clearInEvents(Powerwindow* handle) {
	handle->ifaceInput.obj_detected_raised = bool_false;
	handle->ifaceInput.passenger_up_raised = bool_false;
	handle->ifaceInput.passenger_down_raised = bool_false;
	handle->ifaceInput.driver_up_raised = bool_false;
	handle->ifaceInput.driver_down_raised = bool_false;
	handle->ifaceInput.stop_raised = bool_false;
	handle->timeEvents.powerwindow_main_region_Emergency_operation_tev0_raised = bool_false; 
}

static void powerwindow_clearOutEvents(Powerwindow* handle) {
}

void powerwindow_runCycle(Powerwindow* handle) {
	
	powerwindow_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < POWERWINDOW_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++) {
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition]) {
		case Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation : {
			powerwindow_react_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down : {
			powerwindow_react_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Driver_down : {
			powerwindow_react_main_region_Normal_operation_r1_Driver_down(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Driver_up : {
			powerwindow_react_main_region_Normal_operation_r1_Driver_up(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Passenger_up : {
			powerwindow_react_main_region_Normal_operation_r1_Passenger_up(handle);
			break;
		}
		case Powerwindow_main_region_Emergency_operation : {
			powerwindow_react_main_region_Emergency_operation(handle);
			break;
		}
		default:
			break;
		}
	}
	
	powerwindow_clearInEvents(handle);
}

void powerwindow_raiseTimeEvent(const Powerwindow* handle, sc_eventid evid) {
	if ( ((sc_intptr_t)evid) >= ((sc_intptr_t)&(handle->timeEvents))
		&&  ((sc_intptr_t)evid) < ((sc_intptr_t)&(handle->timeEvents)) + sizeof(PowerwindowTimeEvents)) {
		*(sc_boolean*)evid = bool_true;
	}		
}

sc_boolean powerwindow_isStateActive(const Powerwindow* handle, PowerwindowStates state) {
	sc_boolean result = bool_false;
	switch (state) {
		case Powerwindow_main_region_Normal_operation : 
			result = (sc_boolean) (handle->stateConfVector[0] >= Powerwindow_main_region_Normal_operation
				&& handle->stateConfVector[0] <= Powerwindow_main_region_Normal_operation_r1_Passenger_up);
			break;
		case Powerwindow_main_region_Normal_operation_r1_Driver_neutral : 
			result = (sc_boolean) (handle->stateConfVector[0] >= Powerwindow_main_region_Normal_operation_r1_Driver_neutral
				&& handle->stateConfVector[0] <= Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down);
			break;
		case Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation : 
			result = (sc_boolean) (handle->stateConfVector[0] == Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation
			);
			break;
		case Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down : 
			result = (sc_boolean) (handle->stateConfVector[0] == Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down
			);
			break;
		case Powerwindow_main_region_Normal_operation_r1_Driver_down : 
			result = (sc_boolean) (handle->stateConfVector[0] == Powerwindow_main_region_Normal_operation_r1_Driver_down
			);
			break;
		case Powerwindow_main_region_Normal_operation_r1_Driver_up : 
			result = (sc_boolean) (handle->stateConfVector[0] == Powerwindow_main_region_Normal_operation_r1_Driver_up
			);
			break;
		case Powerwindow_main_region_Normal_operation_r1_Passenger_up : 
			result = (sc_boolean) (handle->stateConfVector[0] == Powerwindow_main_region_Normal_operation_r1_Passenger_up
			);
			break;
		case Powerwindow_main_region_Emergency_operation : 
			result = (sc_boolean) (handle->stateConfVector[0] == Powerwindow_main_region_Emergency_operation
			);
			break;
		default: 
			result = bool_false;
			break;
	}
	return result;
}



sc_boolean powerwindowIfaceOutput_get_up(const Powerwindow* handle) {
	return handle->ifaceOutput.up;
}
sc_boolean powerwindowIfaceOutput_get_down(const Powerwindow* handle) {
	return handle->ifaceOutput.down;
}
void powerwindowIfaceInput_raise_obj_detected(Powerwindow* handle) {
	handle->ifaceInput.obj_detected_raised = bool_true;
}
void powerwindowIfaceInput_raise_passenger_up(Powerwindow* handle) {
	handle->ifaceInput.passenger_up_raised = bool_true;
}
void powerwindowIfaceInput_raise_passenger_down(Powerwindow* handle) {
	handle->ifaceInput.passenger_down_raised = bool_true;
}
void powerwindowIfaceInput_raise_driver_up(Powerwindow* handle) {
	handle->ifaceInput.driver_up_raised = bool_true;
}
void powerwindowIfaceInput_raise_driver_down(Powerwindow* handle) {
	handle->ifaceInput.driver_down_raised = bool_true;
}
void powerwindowIfaceInput_raise_stop(Powerwindow* handle) {
	handle->ifaceInput.stop_raised = bool_true;
}



/* implementations of all internal functions */

static sc_boolean powerwindow_check_main_region_Normal_operation_tr0_tr0(const Powerwindow* handle) {
	return handle->ifaceInput.obj_detected_raised;
}

static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_tr0_tr0(const Powerwindow* handle) {
	return handle->ifaceInput.driver_down_raised;
}

static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_tr1_tr1(const Powerwindow* handle) {
	return handle->ifaceInput.driver_up_raised;
}

static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr0_tr0(const Powerwindow* handle) {
	return handle->ifaceInput.passenger_down_raised;
}

static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr1_tr1(const Powerwindow* handle) {
	return handle->ifaceInput.passenger_up_raised;
}

static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down_tr0_tr0(const Powerwindow* handle) {
	return handle->ifaceInput.stop_raised;
}

static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_down_tr0_tr0(const Powerwindow* handle) {
	return handle->ifaceInput.stop_raised;
}

static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Driver_up_tr0_tr0(const Powerwindow* handle) {
	return handle->ifaceInput.stop_raised;
}

static sc_boolean powerwindow_check_main_region_Normal_operation_r1_Passenger_up_tr0_tr0(const Powerwindow* handle) {
	return handle->ifaceInput.stop_raised;
}

static sc_boolean powerwindow_check_main_region_Emergency_operation_tr0_tr0(const Powerwindow* handle) {
	return handle->timeEvents.powerwindow_main_region_Emergency_operation_tev0_raised;
}

static void powerwindow_effect_main_region_Normal_operation_tr0(Powerwindow* handle) {
	powerwindow_exseq_main_region_Normal_operation(handle);
	handle->ifaceOutput.down = bool_true;
	powerwindow_enseq_main_region_Emergency_operation_default(handle);
}

static void powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_tr0(Powerwindow* handle) {
	powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral(handle);
	handle->ifaceOutput.down = bool_true;
	powerwindow_enseq_main_region_Normal_operation_r1_Driver_down_default(handle);
}

static void powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_tr1(Powerwindow* handle) {
	powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral(handle);
	handle->ifaceOutput.up = bool_true;
	powerwindow_enseq_main_region_Normal_operation_r1_Driver_up_default(handle);
}

static void powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr0(Powerwindow* handle) {
	powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation(handle);
	handle->ifaceOutput.down = bool_true;
	powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down_default(handle);
}

static void powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr1(Powerwindow* handle) {
	powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral(handle);
	handle->ifaceOutput.up = bool_true;
	powerwindow_enseq_main_region_Normal_operation_r1_Passenger_up_default(handle);
}

static void powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down_tr0(Powerwindow* handle) {
	powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down(handle);
	handle->ifaceOutput.down = bool_true;
	powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_default(handle);
}

static void powerwindow_effect_main_region_Normal_operation_r1_Driver_down_tr0(Powerwindow* handle) {
	powerwindow_exseq_main_region_Normal_operation_r1_Driver_down(handle);
	handle->ifaceOutput.down = bool_false;
	powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_default(handle);
}

static void powerwindow_effect_main_region_Normal_operation_r1_Driver_up_tr0(Powerwindow* handle) {
	powerwindow_exseq_main_region_Normal_operation_r1_Driver_up(handle);
	handle->ifaceOutput.up = bool_false;
	powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_default(handle);
}

static void powerwindow_effect_main_region_Normal_operation_r1_Passenger_up_tr0(Powerwindow* handle) {
	powerwindow_exseq_main_region_Normal_operation_r1_Passenger_up(handle);
	handle->ifaceOutput.up = bool_false;
	powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_default(handle);
}

static void powerwindow_effect_main_region_Emergency_operation_tr0(Powerwindow* handle) {
	powerwindow_exseq_main_region_Emergency_operation(handle);
	handle->ifaceOutput.down = bool_false;
	powerwindow_enseq_main_region_Normal_operation_default(handle);
}

/* Entry action for state 'Emergency_operation'. */
static void powerwindow_enact_main_region_Emergency_operation(Powerwindow* handle) {
	/* Entry action for state 'Emergency_operation'. */
	powerwindow_setTimer(handle, (sc_eventid) &(handle->timeEvents.powerwindow_main_region_Emergency_operation_tev0_raised) , 1 * 1000, bool_false);
}

/* Exit action for state 'Emergency_operation'. */
static void powerwindow_exact_main_region_Emergency_operation(Powerwindow* handle) {
	/* Exit action for state 'Emergency_operation'. */
	powerwindow_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.powerwindow_main_region_Emergency_operation_tev0_raised) );		
}

/* 'default' enter sequence for state Normal_operation */
static void powerwindow_enseq_main_region_Normal_operation_default(Powerwindow* handle) {
	/* 'default' enter sequence for state Normal_operation */
	powerwindow_enseq_main_region_Normal_operation_r1_default(handle);
}

/* 'default' enter sequence for state Driver_neutral */
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_default(Powerwindow* handle) {
	/* 'default' enter sequence for state Driver_neutral */
	powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_r1_default(handle);
}

/* 'default' enter sequence for state Passenger_operation */
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_default(Powerwindow* handle) {
	/* 'default' enter sequence for state Passenger_operation */
	handle->stateConfVector[0] = Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Passenger_down */
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down_default(Powerwindow* handle) {
	/* 'default' enter sequence for state Passenger_down */
	handle->stateConfVector[0] = Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Driver_down */
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_down_default(Powerwindow* handle) {
	/* 'default' enter sequence for state Driver_down */
	handle->stateConfVector[0] = Powerwindow_main_region_Normal_operation_r1_Driver_down;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Driver_up */
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_up_default(Powerwindow* handle) {
	/* 'default' enter sequence for state Driver_up */
	handle->stateConfVector[0] = Powerwindow_main_region_Normal_operation_r1_Driver_up;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Passenger_up */
static void powerwindow_enseq_main_region_Normal_operation_r1_Passenger_up_default(Powerwindow* handle) {
	/* 'default' enter sequence for state Passenger_up */
	handle->stateConfVector[0] = Powerwindow_main_region_Normal_operation_r1_Passenger_up;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Emergency_operation */
static void powerwindow_enseq_main_region_Emergency_operation_default(Powerwindow* handle) {
	/* 'default' enter sequence for state Emergency_operation */
	powerwindow_enact_main_region_Emergency_operation(handle);
	handle->stateConfVector[0] = Powerwindow_main_region_Emergency_operation;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void powerwindow_enseq_main_region_default(Powerwindow* handle) {
	/* 'default' enter sequence for region main region */
	powerwindow_react_main_region__entry_Default(handle);
}

/* 'default' enter sequence for region r1 */
static void powerwindow_enseq_main_region_Normal_operation_r1_default(Powerwindow* handle) {
	/* 'default' enter sequence for region r1 */
	powerwindow_react_main_region_Normal_operation_r1__entry_Default(handle);
}

/* 'default' enter sequence for region r1 */
static void powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_r1_default(Powerwindow* handle) {
	/* 'default' enter sequence for region r1 */
	powerwindow_react_main_region_Normal_operation_r1_Driver_neutral_r1__entry_Default(handle);
}

/* Default exit sequence for state Normal_operation */
static void powerwindow_exseq_main_region_Normal_operation(Powerwindow* handle) {
	/* Default exit sequence for state Normal_operation */
	powerwindow_exseq_main_region_Normal_operation_r1(handle);
}

/* Default exit sequence for state Driver_neutral */
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral(Powerwindow* handle) {
	/* Default exit sequence for state Driver_neutral */
	powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1(handle);
}

/* Default exit sequence for state Passenger_operation */
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation(Powerwindow* handle) {
	/* Default exit sequence for state Passenger_operation */
	handle->stateConfVector[0] = Powerwindow_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Passenger_down */
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down(Powerwindow* handle) {
	/* Default exit sequence for state Passenger_down */
	handle->stateConfVector[0] = Powerwindow_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Driver_down */
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_down(Powerwindow* handle) {
	/* Default exit sequence for state Driver_down */
	handle->stateConfVector[0] = Powerwindow_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Driver_up */
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_up(Powerwindow* handle) {
	/* Default exit sequence for state Driver_up */
	handle->stateConfVector[0] = Powerwindow_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Passenger_up */
static void powerwindow_exseq_main_region_Normal_operation_r1_Passenger_up(Powerwindow* handle) {
	/* Default exit sequence for state Passenger_up */
	handle->stateConfVector[0] = Powerwindow_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Emergency_operation */
static void powerwindow_exseq_main_region_Emergency_operation(Powerwindow* handle) {
	/* Default exit sequence for state Emergency_operation */
	handle->stateConfVector[0] = Powerwindow_last_state;
	handle->stateConfVectorPosition = 0;
	powerwindow_exact_main_region_Emergency_operation(handle);
}

/* Default exit sequence for region main region */
static void powerwindow_exseq_main_region(Powerwindow* handle) {
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of powerwindow.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ]) {
		case Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation : {
			powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down : {
			powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Driver_down : {
			powerwindow_exseq_main_region_Normal_operation_r1_Driver_down(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Driver_up : {
			powerwindow_exseq_main_region_Normal_operation_r1_Driver_up(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Passenger_up : {
			powerwindow_exseq_main_region_Normal_operation_r1_Passenger_up(handle);
			break;
		}
		case Powerwindow_main_region_Emergency_operation : {
			powerwindow_exseq_main_region_Emergency_operation(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void powerwindow_exseq_main_region_Normal_operation_r1(Powerwindow* handle) {
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of powerwindow.main_region.Normal_operation.r1) at position 0... */
	switch(handle->stateConfVector[ 0 ]) {
		case Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation : {
			powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down : {
			powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Driver_down : {
			powerwindow_exseq_main_region_Normal_operation_r1_Driver_down(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Driver_up : {
			powerwindow_exseq_main_region_Normal_operation_r1_Driver_up(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Passenger_up : {
			powerwindow_exseq_main_region_Normal_operation_r1_Passenger_up(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region r1 */
static void powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1(Powerwindow* handle) {
	/* Default exit sequence for region r1 */
	/* Handle exit of all possible states (of powerwindow.main_region.Normal_operation.r1.Driver_neutral.r1) at position 0... */
	switch(handle->stateConfVector[ 0 ]) {
		case Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation : {
			powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation(handle);
			break;
		}
		case Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down : {
			powerwindow_exseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state Passenger_operation. */
static void powerwindow_react_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation(Powerwindow* handle) {
	/* The reactions of state Passenger_operation. */
	if (powerwindow_check_main_region_Normal_operation_tr0_tr0(handle)) { 
		powerwindow_effect_main_region_Normal_operation_tr0(handle);
	}  else {
		if (powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_tr0_tr0(handle)) { 
			powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_tr0(handle);
		}  else {
			if (powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_tr1_tr1(handle)) { 
				powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_tr1(handle);
			}  else {
				if (powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr0_tr0(handle)) { 
					powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr0(handle);
				}  else {
					if (powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr1_tr1(handle)) { 
						powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_tr1(handle);
					} 
				}
			}
		}
	}
}

/* The reactions of state Passenger_down. */
static void powerwindow_react_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down(Powerwindow* handle) {
	/* The reactions of state Passenger_down. */
	if (powerwindow_check_main_region_Normal_operation_tr0_tr0(handle)) { 
		powerwindow_effect_main_region_Normal_operation_tr0(handle);
	}  else {
		if (powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_tr0_tr0(handle)) { 
			powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_tr0(handle);
		}  else {
			if (powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_tr1_tr1(handle)) { 
				powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_tr1(handle);
			}  else {
				if (powerwindow_check_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down_tr0_tr0(handle)) { 
					powerwindow_effect_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down_tr0(handle);
				} 
			}
		}
	}
}

/* The reactions of state Driver_down. */
static void powerwindow_react_main_region_Normal_operation_r1_Driver_down(Powerwindow* handle) {
	/* The reactions of state Driver_down. */
	if (powerwindow_check_main_region_Normal_operation_tr0_tr0(handle)) { 
		powerwindow_effect_main_region_Normal_operation_tr0(handle);
	}  else {
		if (powerwindow_check_main_region_Normal_operation_r1_Driver_down_tr0_tr0(handle)) { 
			powerwindow_effect_main_region_Normal_operation_r1_Driver_down_tr0(handle);
		} 
	}
}

/* The reactions of state Driver_up. */
static void powerwindow_react_main_region_Normal_operation_r1_Driver_up(Powerwindow* handle) {
	/* The reactions of state Driver_up. */
	if (powerwindow_check_main_region_Normal_operation_tr0_tr0(handle)) { 
		powerwindow_effect_main_region_Normal_operation_tr0(handle);
	}  else {
		if (powerwindow_check_main_region_Normal_operation_r1_Driver_up_tr0_tr0(handle)) { 
			powerwindow_effect_main_region_Normal_operation_r1_Driver_up_tr0(handle);
		} 
	}
}

/* The reactions of state Passenger_up. */
static void powerwindow_react_main_region_Normal_operation_r1_Passenger_up(Powerwindow* handle) {
	/* The reactions of state Passenger_up. */
	if (powerwindow_check_main_region_Normal_operation_tr0_tr0(handle)) { 
		powerwindow_effect_main_region_Normal_operation_tr0(handle);
	}  else {
		if (powerwindow_check_main_region_Normal_operation_r1_Passenger_up_tr0_tr0(handle)) { 
			powerwindow_effect_main_region_Normal_operation_r1_Passenger_up_tr0(handle);
		} 
	}
}

/* The reactions of state Emergency_operation. */
static void powerwindow_react_main_region_Emergency_operation(Powerwindow* handle) {
	/* The reactions of state Emergency_operation. */
	if (powerwindow_check_main_region_Emergency_operation_tr0_tr0(handle)) { 
		powerwindow_effect_main_region_Emergency_operation_tr0(handle);
	} 
}

/* Default react sequence for initial entry  */
static void powerwindow_react_main_region__entry_Default(Powerwindow* handle) {
	/* Default react sequence for initial entry  */
	powerwindow_enseq_main_region_Normal_operation_default(handle);
}

/* Default react sequence for initial entry  */
static void powerwindow_react_main_region_Normal_operation_r1__entry_Default(Powerwindow* handle) {
	/* Default react sequence for initial entry  */
	powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_default(handle);
}

/* Default react sequence for initial entry  */
static void powerwindow_react_main_region_Normal_operation_r1_Driver_neutral_r1__entry_Default(Powerwindow* handle) {
	/* Default react sequence for initial entry  */
	powerwindow_enseq_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation_default(handle);
}


