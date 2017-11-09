/*
 * PowerwindowRequired.c
 *
 *  Created on: Jan 26, 2017
 *      Author: Joachim
 */


#include "PowerwindowRequired.h"
#include <math.h>

/*
 * I only check on the bigger than compare with the double
 * This should be changed
 */

 double relativeError(double a, double b){
	double rv = fabs((a - b) / a);
	return rv;
}

/*
 * Helper function for absolute error
 */
 double absoluteError(double a, double b){
	double rv=fabs(a - b);
	return rv;
}

/*
 * is_close function for double comparison
 */
 int is_close(double a, double b, double REL_TOL, double ABS_TOL){
	 int ae = absoluteError(a,b)<ABS_TOL;
	 int re = relativeError(a,b)<REL_TOL;
	return (ae && re);
}

void powerwindow_timeradvance(fmi_timer *theTimer, double currentTime){
	theTimer->currentTime = currentTime;
	if (theTimer->active && is_close(theTimer->nextTime, theTimer->currentTime,1e-4,1e-8)){
		/* We have a timer event */
		theTimer->callback(theTimer->handle, theTimer->evid);
		if(theTimer->isPeriodic){
			theTimer->nextTime = currentTime + theTimer->period;
		}else{
			theTimer->active = 0;
		}
	}
}

void powerwindow_initTimer(fmi_timer *timer){
	thePWTimer = timer;
}

void powerwindow_setTimer(Powerwindow* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic){
	thePWTimer->active = 1;
	thePWTimer->handle = handle;
	thePWTimer->evid = evid;
	thePWTimer->period = time_ms;
	thePWTimer->nextTime = thePWTimer->currentTime + time_ms;
	thePWTimer->isPeriodic = periodic;
}

void powerwindow_unsetTimer(Powerwindow* handle, const sc_eventid evid){
	thePWTimer->active = 0;
}
