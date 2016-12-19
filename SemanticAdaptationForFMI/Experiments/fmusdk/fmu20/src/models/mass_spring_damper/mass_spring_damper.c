/* ---------------------------------------------------------------------------*
 * Mass spring damper test FMU.
 * ---------------------------------------------------------------------------*/

// define class name and unique id
#define MODEL_IDENTIFIER mass_spring_damper
#define MODEL_GUID "{8c4e810f-3df3-4a00-8276-176fa3c9f000}"

// define model size
#define NUMBER_OF_REALS 7
#define NUMBER_OF_INTEGERS 0
#define NUMBER_OF_BOOLEANS 0
#define NUMBER_OF_STRINGS 0
#define NUMBER_OF_STATES 2
#define NUMBER_OF_EVENT_INDICATORS 0

// include fmu header files, typedefs and macros
#include "fmuTemplate.h"

// define all model variables and their value references
// conventions used here:
// - if x is a variable, then macro x_ is its variable reference
// - the vr of a variable is its index in array  r, i, b or s
// - if k is the vr of a real state, then k+1 is the vr of its derivative
#define x_     		0
#define der_x_ 		1
#define der_der_x_ 	2
#define F_in_ 		3
#define k_     		4
#define c_     		5
#define m_     		6

// define state vector as vector of value references
#define STATES { x_ , der_x_ }

// array of value references of states
#if NUMBER_OF_STATES>0
fmi2ValueReference vrStates[NUMBER_OF_STATES] = STATES;
#endif

// called by fmi2Instantiate
// Set values for all variables that define a start value
// Settings used unless changed by fmi2SetX before fmi2EnterInitializationMode
void setStartValues(ModelInstance *comp) {
    r(x_) = 1;
    r(der_x_) = 0;
    r(der_der_x_) = 0;
    r(F_in_) = 0;
    r(k_) = 1;
    r(c_) = 1;
    r(m_) = 1;
}

// called by fmi2GetReal, fmi2GetInteger, fmi2GetBoolean, fmi2GetString, fmi2ExitInitialization
// if setStartValues or environment set new values through fmi2SetXXX.
// Lazy set values for all variable that are computed from other variables.
void calculateValues(ModelInstance *comp) {
	r(der_der_x_) =  r(F_in_) - r(k_) * r(x_) - r(k_) * r(der_x_);
}

void instantiate(ModelInstance *comp) {
    // does nothing for now.
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "instantiate")
}

fmi2Status setupExperiment(ModelInstance *comp, fmi2Boolean toleranceDefined, fmi2Real tolerance,
                            fmi2Real startTime, fmi2Boolean stopTimeDefined, fmi2Real stopTime){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "setupExperiment: toleranceDefined=%d tolerance=%g",
        toleranceDefined, tolerance)
	return fmi2OK;
}

fmi2Status enterInitializationMode(ModelInstance *comp){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "enterInitializationMode")
	return fmi2OK;
}

fmi2Status exitInitializationMode(ModelInstance *comp){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "exitInitializationMode")
	return fmi2OK;
}

fmi2Status terminate(ModelInstance *comp){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "terminate")
	return fmi2OK;
}

fmi2Status reset(ModelInstance *comp){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "reset")
	return fmi2OK;
}

fmi2Status freeInstance(ModelInstance *comp){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "freeInstance")
	return fmi2OK;
}

// called by fmi2GetReal, fmi2GetContinuousStates and fmi2GetDerivatives
fmi2Real getReal(ModelInstance* comp, fmi2ValueReference vr){
    switch (vr) {
        case x_     	: return r(x_);
        case der_x_ 	: return r(der_x_);
        case der_der_x_ : return r(F_in_) - r(k_) * r(x_) - r(k_) * r(der_x_);
        default: return 0;
    }
}

// used to set the next time event, if any.
void eventUpdate(ModelInstance *comp, fmi2EventInfo *eventInfo, int isTimeEvent, int isNewEventIteration) {
} 

fmi2Status doStep(ModelInstance *comp, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint){
	
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "doStep: "
        "currentCommunicationPoint = %g, "
        "communicationStepSize = %g, "
        "noSetFMUStatePriorToCurrentPoint = fmi2%s",
        currentCommunicationPoint, communicationStepSize, noSetFMUStatePriorToCurrentPoint ? "True" : "False")
	
	double h = communicationStepSize / 10;
    int k,i;
    const int n = 10; // how many Euler steps to perform for one do step
    double prevState[max(NUMBER_OF_STATES, 1)];
    double prevEventIndicators[max(NUMBER_OF_EVENT_INDICATORS, 1)];
    int stateEvent = 0;
    int timeEvent = 0;
	
#if NUMBER_OF_EVENT_INDICATORS>0
    // initialize previous event indicators with current values
    for (i = 0; i < NUMBER_OF_EVENT_INDICATORS; i++) {
        prevEventIndicators[i] = getEventIndicator(comp, i);
    }
#endif

    // break the step into n steps and do forward Euler.
    comp->time = currentCommunicationPoint;
    for (k = 0; k < n; k++) {
        comp->time += h;

#if NUMBER_OF_REALS>0
        for (i = 0; i < NUMBER_OF_STATES; i++) {
            prevState[i] = r(vrStates[i]);
        }
        for (i = 0; i < NUMBER_OF_STATES; i++) {
            fmi2ValueReference vr = vrStates[i];
            r(vr) += h * getReal(comp, vr + 1); // forward Euler step
        }
#endif

#if NUMBER_OF_EVENT_INDICATORS>0
        // check for state event
        for (i = 0; i < NUMBER_OF_EVENT_INDICATORS; i++) {
            double ei = getEventIndicator(comp, i);
            if (ei * prevEventIndicators[i] < 0) {
                FILTERED_LOG(comp, fmi2OK, LOG_EVENT,
                    "fmi2DoStep: state event at %g, z%d crosses zero -%c-", comp->time, i, ei < 0 ? '\\' : '/')
                stateEvent++;
            }
            prevEventIndicators[i] = ei;
        }
#endif
        // check for time event
        if (comp->eventInfo.nextEventTimeDefined && ((comp->time - comp->eventInfo.nextEventTime) > -0.0000000001)) {
            FILTERED_LOG(comp, fmi2OK, LOG_EVENT, "fmi2DoStep: time event detected at %g", comp->time)
            timeEvent = 1;
        }

        if (stateEvent || timeEvent) {
            eventUpdate(comp, &comp->eventInfo, timeEvent, fmi2True);
            timeEvent = 0;
            stateEvent = 0;
        }

        // terminate simulation, if requested by the model in the previous step
        if (comp->eventInfo.terminateSimulation) {
            FILTERED_LOG(comp, fmi2Discard, LOG_ALL, "fmi2DoStep: model requested termination at t=%g", comp->time)
            comp->state = modelStepFailed;
            return fmi2Discard; // enforce termination of the simulation loop
        }
    }
	
	return fmi2OK;
}

// include code that implements the FMI based on the above definitions
#include "fmuTemplate.c"


