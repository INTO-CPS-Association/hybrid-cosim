/*
 * PW_Controller.h
 *
 *  Created on: Jan 25, 2017
 *      Author: Joachim
 */

#ifndef FMI_GM_H_
#define FMI_GM_H_

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
#define _NR_OF_IN_CONDITIONS 2
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
    FMU fmu[1];
    char *fmuResourceLocation[_NR_OF_FMUS];
    fmi2Component c_fmu[_NR_OF_FMUS];
    fmi2Boolean in_condition_executed[_NR_OF_IN_CONDITIONS];
    fmi2Boolean out_conditions_executed[_NR_OF_OUT_CONDITIONS];
    fmi2Real time_last_fmu[_NR_OF_FMUS];
    /* Generated */
    fmi2Real REL_TOLERANCE;
    fmi2Real ABS_TOLERANCE;
    fmi2Real CROSSING;
    fmi2Real init_up;
    fmi2Real init_down;
    fmi2Real init_armature_current;
    fmi2Real next_time_step;
    fmi2Real stored_arm_current;
    fmi2Real step_size;
    fmi2Boolean aux_obj_detected;
    fmi2Boolean get_next_step;
    fmi2Real previous_arm_current;
    fmi2Boolean stored_up;
    fmi2Boolean stored_down;
} FMUInstance; // At the moment, most of the variables not really used since multiple instances of an FMU are not supported at the moment (performance issues)




#endif /* FMI_GM_H_ */
