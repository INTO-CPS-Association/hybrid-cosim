
#ifndef POWERWINDOWREQUIRED_H_
#define POWERWINDOWREQUIRED_H_

#include "sc_types.h"
#include "Powerwindow.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*! \file This header defines prototypes for all functions that are required by the state machine implementation.

This is a state machine uses time events which require access to a timing service. Thus the function prototypes:
	- powerwindow_setTimer and
	- powerwindow_unsetTimer
are defined.

These functions will be called during a 'run to completion step' (runCycle) of the statechart. 
There are some constraints that have to be considered for the implementation of these functions:
	- never call the statechart API functions from within these functions.
	- make sure that the execution time is as short as possible.
 
*/

/*
 * This is a simple hack; for a real FMI code gen for Yakindu, make this a bit more generic
 */


double relativeError(double a, double b);

/*
* Helper function for absolute error
*/
double absoluteError(double a, double b);

/*
* is_close function for double comparison
*/
int is_close(double a, double b, double REL_TOL, double ABS_TOL);

typedef struct{
	double nextTime;
	double currentTime;
	Powerwindow * handle;
	sc_eventid evid;
	int period;
	int isPeriodic;
	int active;
	void (*callback) (Powerwindow*, sc_eventid evid);
}fmi_timer;

fmi_timer *thePWTimer;

void powerwindow_timeradvance(fmi_timer *theTimer, double currentTime);
void powerwindow_initTimer(fmi_timer *timer);
/*!
 * This is a timed state machine that requires timer services
 */ 

/*! This function has to set up timers for the time events that are required by the state machine. */
/*! 
	This function will be called for each time event that is relevant for a state when a state will be entered.
	\param evid An unique identifier of the event.
	\time_ms The time in milli seconds
	\periodic Indicates the the time event must be raised periodically until the timer is unset 
*/
extern void powerwindow_setTimer(Powerwindow* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic);

/*! This function has to unset timers for the time events that are required by the state machine. */
/*! 
	This function will be called for each time event taht is relevant for a state when a state will be left.
	\param evid An unique identifier of the event.
*/
extern void powerwindow_unsetTimer(Powerwindow* handle, const sc_eventid evid);

#ifdef __cplusplus
}
#endif 

#endif /* POWERWINDOWREQUIRED_H_ */
