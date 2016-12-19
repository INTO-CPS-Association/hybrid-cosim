/* ---------------------------------------------------------------------------*
 * Mass spring damper test FMU.
 * ---------------------------------------------------------------------------*/

// define class name and unique id
#define MODEL_IDENTIFIER mass_spring_damper_hierarchical
#define MODEL_GUID "{ae8ba062-ad27-4bfb-8ce5-54c82e9d7e35}"

// define model size
// This FMU, since it is a wrapper, does not have any real state even though its model description says so.
#define NUMBER_OF_REALS 0
#define NUMBER_OF_INTEGERS 0
#define NUMBER_OF_BOOLEANS 0
#define NUMBER_OF_STRINGS 0
#define NUMBER_OF_STATES 0
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
#define STATES { }

// called by fmi2Instantiate
// Set values for all variables that define a start value
void setStartValues(ModelInstance *comp) {
    // does nothing for now.
}

// called by fmi2Instantiate
// In the case of hierarchical co-simulation, this will instantiate the (compiled) mass-spring-damper FMU.
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

fmi2Status doStep(ModelInstance *comp, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint){
	
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "doStep: "
        "currentCommunicationPoint = %g, "
        "communicationStepSize = %g, "
        "noSetFMUStatePriorToCurrentPoint = fmi2%s",
        currentCommunicationPoint, communicationStepSize, noSetFMUStatePriorToCurrentPoint ? "True" : "False")
	
    comp->time = currentCommunicationPoint + communicationStepSize;
	
	return fmi2OK;
}

// called by fmi2GetReal, fmi2GetInteger, fmi2GetBoolean, fmi2GetString, fmi2ExitInitialization
// if setStartValues or environment set new values through fmi2SetXXX.
// Lazy set values for all variable that are computed from other variables.
void calculateValues(ModelInstance *comp) {
	// do nothing
}

// called by fmi2GetReal, fmi2GetContinuousStates and fmi2GetDerivatives
fmi2Real getReal(ModelInstance* comp, fmi2ValueReference vr){
	// does nothing for now.
	return 0.0f;
}

// used to set the next time event, if any.
void eventUpdate(ModelInstance *comp, fmi2EventInfo *eventInfo, int isTimeEvent, int isNewEventIteration) {
	// do nothing
}

// include code that implements the FMI based on the above definitions
#include "fmuTemplate.c"


