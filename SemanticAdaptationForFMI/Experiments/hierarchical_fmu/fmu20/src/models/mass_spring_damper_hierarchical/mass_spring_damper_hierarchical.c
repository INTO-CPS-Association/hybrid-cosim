/* ---------------------------------------------------------------------------*
 * Mass spring damper test FMU.
 * ---------------------------------------------------------------------------*/

// define class name and unique id
#define MODEL_IDENTIFIER mass_spring_damper_hierarchical
#define MODEL_GUID "{ae8ba062-ad27-4bfb-8ce5-54c82e9d7e35}"

// define model size
// This FMU, since it is a wrapper, does not have any real state even though its model description says so.
#define NUMBER_OF_REALS 7
#define NUMBER_OF_INTEGERS 0
#define NUMBER_OF_BOOLEANS 0
#define NUMBER_OF_STRINGS 0
#define NUMBER_OF_STATES 0
#define NUMBER_OF_EVENT_INDICATORS 0

// These libraries are needed to load FMUs
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fmi2.h"
#include "sim_support.h"

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

// This is used by the loadFMU function, in the sim_support library, to load the FMU dll.
FMU fmu; // the fmu to simulate
FMU* childFMU; // pointer to the above FMU
fmi2Component childFMUInstance;                        // instance of the above fmu

// called by fmi2Instantiate
// Set values for all variables that define a start value
void setStartValues(ModelInstance *comp) {
    // does nothing for now.
}

// called by fmi2Instantiate
// In the case of hierarchical co-simulation, this will instantiate the (compiled) mass-spring-damper FMU.
void instantiate(ModelInstance *comp) {
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, ">instantiate")
	
	const char* fmuFileName = "fmu20\\fmu\\cs\\mass_spring_damper.fmu";
	ModelDescription* md; 					// handle to the parsed XML file
	const char *guid;                       // global unique id of the fmu
	const char *instanceName;               // instance name
    childFMU = &fmu;
	fmi2Status fmi2Flag;                    // return code of the fmu functions
    char *fmuResourceLocation = getTempResourcesLocation(); // path to the fmu resources as URL, "file://C:\QTronic\sales"
    fmi2Boolean visible = fmi2False;        // no simulator user interface
	fmi2Boolean loggingOn = fmi2True;  // TODO : this should be a parameter
	
	// TODO: Reuse categories given by instantiation
	char **categories = NULL;
	int nCategories = 0;
	
	loadFMU(fmuFileName);
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "Mass Spring Damper FMU Loaded")
	
	md = childFMU->modelDescription;
    guid = getAttributeValue((Element *)md, att_guid);
    instanceName = getAttributeValue((Element *)getCoSimulation(md), att_modelIdentifier);
    childFMUInstance = childFMU->instantiate(instanceName, fmi2CoSimulation, guid, fmuResourceLocation,
                    comp->functions, visible, comp->loggingOn);
    free(fmuResourceLocation);
	
    if (!childFMUInstance){
		FILTERED_LOG(comp, fmi2Error, LOG_ERROR, "Could not instantiate mass spring damper model")
		return;
	}
	
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "Mass Spring Damper FMU Instantiated: fmu %u ; instance %u", childFMU, childFMUInstance)
	
    if (nCategories > 0) {
        fmi2Flag = childFMU->setDebugLogging(childFMUInstance, fmi2True, nCategories, categories);
        if (fmi2Flag > fmi2Warning) {
			FILTERED_LOG(comp, fmi2Error, LOG_ERROR, "Could not initialize mass spring damper model - failed FMI set debug logging")
			return;
        }
    }
	
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "<instantiate")
}

fmi2Status setupExperiment(ModelInstance *comp, fmi2Boolean toleranceDefined, fmi2Real tolerance,
                            fmi2Real startTime, fmi2Boolean stopTimeDefined, fmi2Real stopTime){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, ">setupExperiment: toleranceDefined=%d tolerance=%g",
        toleranceDefined, tolerance)
	
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "Setting up experiment in child: fmu %u ; instance %u", childFMU, childFMUInstance)
	
	fmi2Status fmi2Flag = childFMU->setupExperiment(childFMUInstance, toleranceDefined, tolerance, startTime, stopTimeDefined, stopTime);
    
	FILTERED_LOG(comp, fmi2Flag, LOG_FMI_CALL, "<setupExperiment")
	
	return fmi2Flag;
}

fmi2Status enterInitializationMode(ModelInstance *comp){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, ">enterInitializationMode")
	
	fmi2Status fmi2Flag = childFMU->enterInitializationMode(childFMUInstance);
    
	FILTERED_LOG(comp, fmi2Flag, LOG_FMI_CALL, "<enterInitializationMode")
	return fmi2Flag;
}

fmi2Status exitInitializationMode(ModelInstance *comp){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, ">exitInitializationMode")
	
	fmi2Status fmi2Flag = childFMU->exitInitializationMode(childFMUInstance);
    
	FILTERED_LOG(comp, fmi2Flag, LOG_FMI_CALL, "<exitInitializationMode")
	return fmi2Flag;
}

fmi2Status terminate(ModelInstance *comp){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, ">terminate")
	
	fmi2Status fmi2Flag = childFMU->terminate(childFMUInstance);
    
	FILTERED_LOG(comp, fmi2Flag, LOG_FMI_CALL, "<terminate")
	
	return fmi2Flag;
}

fmi2Status reset(ModelInstance *comp){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "reset")
	return fmi2OK;
}

fmi2Status freeInstance(ModelInstance *comp){
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, ">freeInstance")
	
	childFMU->freeInstance(childFMUInstance);
    
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "<freeInstance")
	
	return fmi2OK;
}

fmi2Status doStep(ModelInstance *comp, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint){
	
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "doStep: "
        "currentCommunicationPoint = %g, "
        "communicationStepSize = %g, "
        "noSetFMUStatePriorToCurrentPoint = fmi2%s",
        currentCommunicationPoint, communicationStepSize, noSetFMUStatePriorToCurrentPoint ? "True" : "False")
	
	int n_steps = 10;
	double h = communicationStepSize / n_steps;
    int k;
	fmi2Status fmi2Flag;
    
    comp->time = currentCommunicationPoint;
	
	for (k = 0; k < n_steps; k++){
		fmi2Flag = childFMU->doStep(childFMUInstance, comp->time, h, fmi2True);
		FILTERED_LOG(comp, fmi2Flag, LOG_FMI_CALL, "doStep of child completed to time %g", comp->time)
		comp->time += h;
	}
	
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
	FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, ">getReal")
	
	// passing the address is a cheap way of conforming to the vector.
	fmi2Real val;
	fmi2Status fmi2flag = childFMU->getReal(childFMUInstance, &vr, 1, &val);
    
	FILTERED_LOG(comp, fmi2flag, LOG_FMI_CALL, "<getReal = %g", val)
	return val;
}

// used to set the next time event, if any.
void eventUpdate(ModelInstance *comp, fmi2EventInfo *eventInfo, int isTimeEvent, int isNewEventIteration) {
	// do nothing
}

// include code that implements the FMI based on the above definitions
#include "fmuTemplate.c"


