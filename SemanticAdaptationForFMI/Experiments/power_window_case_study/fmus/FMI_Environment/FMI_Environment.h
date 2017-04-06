/*
 * PW_Controller.h
 *
 *  Created on: Jan 25, 2017
 *      Author: Joachim
 */

#ifndef FMI_ENVIRONMENT_H_
#define FMI_ENVIRONMENT_H_


 double relativeError(double a, double b);
 double absoluteError(double a, double b);
 int is_close(double a, double b, double REL_TOL, double ABS_TOL);


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
} FMUInstance; // At the moment, most of the variables not really used since multiple instances of an FMU are not supported at the moment (performance issues)




#endif /* FMI_ENVIRONMENT_H_ */
