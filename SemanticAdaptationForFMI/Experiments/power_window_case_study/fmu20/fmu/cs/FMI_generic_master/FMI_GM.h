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
	fmi2Real stepSize;
    fmi2Real startTime;
    fmi2Real stopTime;
	fmi2Real currentTime;
    fmi2Boolean stopTimeDefined;
    fmi2Real tolerance;
    fmi2Boolean toleranceDefined;
    FMU fmu_order[3];
    char *fmuResourceLocation_order[3];
    fmi2Component c_order[3];
    fmi2Real accumulator;
    fmi2Real nextTimerEvent;
} FMUInstance; // At the moment, most of the variables not really used since multiple instances of an FMU are not supported at the moment (performance issues)




#endif /* FMI_GM_H_ */
