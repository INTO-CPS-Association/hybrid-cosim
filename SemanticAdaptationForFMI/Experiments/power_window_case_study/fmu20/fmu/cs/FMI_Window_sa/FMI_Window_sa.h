/*
 * PW_Controller.h
 *
 *  Created on: Jan 25, 2017
 *      Author: Joachim
 */

#ifndef FMI_WINDOW_SA_H_
#define FMI_WINDOW_SA_H_

#include "fmi2.h"

typedef enum {
    fmuInstantiated = 0,
    fmuInitMode  = 1,
	fmuInitialized = 2,
    fmuTerminated   = 3,
    fmuError        = 4,
    fmuExperimentSettedUp = 5
} FMUState;

#define _NR_OF_FMUS 1
#define _NR_OF_IN_CONDITIONS 1
#define _NR_OF_OUT_CONDITIONS 1

typedef struct {
	fmi2Real    *r;
    fmi2Integer *i;
    fmi2Boolean *b;
    fmi2String  *s;
    fmi2Boolean isVisible;
    fmi2String instanceName;
    fmi2String GUID;
    const fmi2CallbackFunctions* functions;
    fmi2Boolean loggingOn;
    FMUState state;
    fmi2Real startTime;
    fmi2Real stopTime;
	fmi2Real currentTime;
    fmi2Boolean stopTimeDefined;
    fmi2Boolean toleranceDefined;
    /* for generic algo*/
    FMU fmu[_NR_OF_FMUS];
    char *fmuResourceLocation[_NR_OF_FMUS];
    fmi2Component c_fmu[_NR_OF_FMUS];
    fmi2Boolean in_condition_executed[_NR_OF_IN_CONDITIONS];
    fmi2Boolean out_conditions_executed[_NR_OF_OUT_CONDITIONS];
    fmi2Real time_last_fmu[_NR_OF_FMUS];
    /* Generated */
    fmi2Real stored_windowsa_reaction_force;
    fmi2Real stored_windowsa_displacement;
    fmi2Real stored_windowsa_speed;
    fmi2Real stored_window_reaction_torque;
    fmi2Real stored_window_height;

} FMUInstance; // At the moment, most of the variables not really used since multiple instances of an FMU are not supported at the moment (performance issues)




#endif /* FMI_WINDOW_SA_H_ */
