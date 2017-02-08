
#ifndef POWERWINDOW_H_
#define POWERWINDOW_H_

#include "sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'powerwindow'.
*/

/*! Enumeration of all states */ 
typedef enum {
	Powerwindow_main_region_Normal_operation,
	Powerwindow_main_region_Normal_operation_r1_Driver_neutral,
	Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_operation,
	Powerwindow_main_region_Normal_operation_r1_Driver_neutral_r1_Passenger_down,
	Powerwindow_main_region_Normal_operation_r1_Driver_down,
	Powerwindow_main_region_Normal_operation_r1_Driver_up,
	Powerwindow_main_region_Normal_operation_r1_Passenger_up,
	Powerwindow_main_region_Emergency_operation,
	Powerwindow_last_state
} PowerwindowStates;

/*! Type definition of the data structure for the PowerwindowIfaceOutput interface scope. */
typedef struct {
	sc_boolean up;
	sc_boolean down;
} PowerwindowIfaceOutput;

/*! Type definition of the data structure for the PowerwindowIfaceInput interface scope. */
typedef struct {
	sc_boolean obj_detected_raised;
	sc_boolean passenger_up_raised;
	sc_boolean passenger_down_raised;
	sc_boolean driver_up_raised;
	sc_boolean driver_down_raised;
	sc_boolean stop_raised;
} PowerwindowIfaceInput;

/*! Type definition of the data structure for the PowerwindowTimeEvents interface scope. */
typedef struct {
	sc_boolean powerwindow_main_region_Emergency_operation_tev0_raised;
} PowerwindowTimeEvents;


/*! Define dimension of the state configuration vector for orthogonal states. */
#define POWERWINDOW_MAX_ORTHOGONAL_STATES 1

/*! 
 * Type definition of the data structure for the Powerwindow state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct {
	PowerwindowStates stateConfVector[POWERWINDOW_MAX_ORTHOGONAL_STATES];
	sc_ushort stateConfVectorPosition; 
	
	PowerwindowIfaceOutput ifaceOutput;
	PowerwindowIfaceInput ifaceInput;
	PowerwindowTimeEvents timeEvents;
} Powerwindow;

void powerwindow_copy(Powerwindow* original, Powerwindow* copy);

/*! Initializes the Powerwindow state machine data structures. Must be called before first usage.*/
extern void powerwindow_init(Powerwindow* handle);

/*! Activates the state machine */
extern void powerwindow_enter(Powerwindow* handle);

/*! Deactivates the state machine */
extern void powerwindow_exit(Powerwindow* handle);

/*! Performs a 'run to completion' step. */
extern void powerwindow_runCycle(Powerwindow* handle);

/*! Raises a time event. */
extern void powerwindow_raiseTimeEvent(const Powerwindow* handle, sc_eventid evid);

/*! Gets the value of the variable 'up' that is defined in the interface scope 'output'. */ 
extern sc_boolean powerwindowIfaceOutput_get_up(const Powerwindow* handle);
/*! Gets the value of the variable 'down' that is defined in the interface scope 'output'. */ 
extern sc_boolean powerwindowIfaceOutput_get_down(const Powerwindow* handle);
/*! Raises the in event 'obj_detected' that is defined in the interface scope 'input'. */ 
extern void powerwindowIfaceInput_raise_obj_detected(Powerwindow* handle);

/*! Raises the in event 'passenger_up' that is defined in the interface scope 'input'. */ 
extern void powerwindowIfaceInput_raise_passenger_up(Powerwindow* handle);

/*! Raises the in event 'passenger_down' that is defined in the interface scope 'input'. */ 
extern void powerwindowIfaceInput_raise_passenger_down(Powerwindow* handle);

/*! Raises the in event 'driver_up' that is defined in the interface scope 'input'. */ 
extern void powerwindowIfaceInput_raise_driver_up(Powerwindow* handle);

/*! Raises the in event 'driver_down' that is defined in the interface scope 'input'. */ 
extern void powerwindowIfaceInput_raise_driver_down(Powerwindow* handle);

/*! Raises the in event 'stop' that is defined in the interface scope 'input'. */ 
extern void powerwindowIfaceInput_raise_stop(Powerwindow* handle);


/*!
 * Checks if the statemachine is active (until 2.4.1 this method was used for states).
 * A statemachine is active if it was entered. It is inactive if it has not been entered at all or if it was exited.
 */
extern sc_boolean powerwindow_isActive(const Powerwindow* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the statemachine is considered as inactive and this method returns false.
 */
extern sc_boolean powerwindow_isFinal(const Powerwindow* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
extern sc_boolean powerwindow_isStateActive(const Powerwindow* handle, PowerwindowStates state);

#ifdef __cplusplus
}
#endif 

#endif /* POWERWINDOW_H_ */
