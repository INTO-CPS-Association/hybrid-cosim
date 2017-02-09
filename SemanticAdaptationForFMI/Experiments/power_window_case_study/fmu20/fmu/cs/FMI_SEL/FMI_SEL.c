/* ---------------------------------------------------------------------------*
 * Sample implementation of an FMU - a power window controller
 * The code is generated from a Yakindu SC
 * ---------------------------------------------------------------------------*/
/*
Template for a sc FMU
*/

#define MODEL_IDENTIFIER SEL
#define MODEL_GUID "{41f87101-edf2-4eef-90f3-42db56d4565f}"
#define FMI2_FUNCTION_PREFIX PW_SEL


#include <stdio.h>
#include "string.h"
#include "fmi2Functions.h"
#include <float.h>
#include "FMI_SEL.h"
#include <math.h>


#define NUMBER_OF_REALS 2
#define NUMBER_OF_STRINGS 0
#define NUMBER_OF_BOOLEANS 17
#define NUMBER_OF_INTEGERS 0
/*
 * The input Signals (Real)
 */
#define _in_armature_current 0

/*
 * The input events
 */
#define _in_driver_up 0
#define _in_driver_up_stop 1
#define _in_driver_down 2
#define _in_driver_down_stop 3
#define _in_passenger_up 4
#define _in_passenger_up_stop 5
#define _in_passenger_down 6
#define _in_passenger_down_stop 7

/*
 * The store
 */
#define _stored_armature_current 1

/*
 * The output events:
 * */

#define _out_obj_detected 8
#define _out_driver_up 9
#define _out_driver_up_stop 10
#define _out_driver_down 11
#define _out_driver_down_stop 12
#define _out_passenger_up 13
#define _out_passenger_up_stop 14
#define _out_passenger_down 15
#define _out_passenger_down_stop 16
/*
 * Control Signal
 */
#define _out_control 17

/*
 * Helper function for relative error
 */
 double relativeError(double a, double b){
	return fabs((a - b) / a);
}

/*
 * Helper function for absolute error
 */
 double absoluteError(double a, double b){
	return fabs(a - b);
}

/*
 * is_close function for double comparison
 */
 int is_close(double a, double b, double REL_TOL, double ABS_TOL){
	return ((absoluteError(a,b)<ABS_TOL) && (relativeError(a,b)<REL_TOL));
}


fmi2Status fmi2SetDebugLogging(fmi2Component fc, fmi2Boolean loggingOn, size_t nCategories, const fmi2String categories[])
{
    return fmi2OK;
}

fmi2Status fmi2SetString(fmi2Component fc, const fmi2ValueReference vr[], size_t nvr, const fmi2String value[])
{
    return fmi2Error;
}

fmi2Status fmi2GetString(fmi2Component fc, const fmi2ValueReference vr[], size_t nvr, fmi2String value[])
{
    return fmi2Error;
}

fmi2Status fmi2SetReal(fmi2Component fc, const fmi2ValueReference vr[], size_t nvr, const fmi2Real value[])
{
	FMUInstance* comp = (FMUInstance *)fc;
		int i;
	    for (i = 0; i < nvr; i++)
		{
	    	if(vr[i]>=5){
	    		printf("Value reference: %d, cannot be set, it is a store element\n", vr[i]);
	    	}else{
	    		 printf("Value reference: %d\n", vr[i]);
	    		 comp->r[vr[i]] = value[i];
	    	}

	        //setExposedReal(vr[i], value[i]);
	        //comp->r[vr[i]] = value[i];
	    }
	    return fmi2OK;
}

fmi2Status fmi2GetReal(fmi2Component fc, const fmi2ValueReference vr[], size_t nvr, fmi2Real value[])
{

    FMUInstance* comp = (FMUInstance *)fc;
	int i;
    for (i = 0; i < nvr; i++)
	{
        value[i] = comp->r[(vr[i])];
    }
    return fmi2OK;
}

fmi2Status fmi2SetBoolean(fmi2Component fc, const fmi2ValueReference vr[], size_t nvr, const fmi2Boolean value[])
{
	FMUInstance* comp = (FMUInstance *)fc;
	int i;
	for (i = 0; i < nvr; i++)
	{
		comp->b[vr[i]] = value[i];
	}
    return fmi2OK;
}

fmi2Status fmi2GetBoolean(fmi2Component fc, const fmi2ValueReference vr[], size_t nvr, fmi2Boolean value[])
{
	FMUInstance* comp = (FMUInstance *)fc;
	int i;
	for (i = 0; i < nvr; i++)
	{
		value[i] = comp->b[vr[i]];
	}
    return fmi2OK;
}

fmi2Component fmi2Instantiate(fmi2String instanceName, fmi2Type fmuType, fmi2String fmuGUID, fmi2String fmuLocation, const fmi2CallbackFunctions* functions, fmi2Boolean visible, fmi2Boolean loggingOn)
{

	//Declare data structure for fmu instance
    FMUInstance* fi;
	printf("%s in fmiInstantiate\n",instanceName);

    //Perform checks on passed callback functions
    if (loggingOn) {

        if (!functions->logger);
        //return NULL;
	}
    //Check for instanceName
    if (!instanceName || strlen(instanceName)==0) {

        // print (and/or log) instanceName is missing
        //return NULL;
    }
    //Check passed GUID to defined model GUID
    if (strcmp(fmuGUID, MODEL_GUID))
	{
        // print (and/or log) GUID doesn't match
        //return NULL;
    }

    //Allocate fmu instance Memory
    // TODO check if "canNotUseMemoryManagementFunctions == true/false". If false memory allocation not possible
    fi = (FMUInstance *)functions->allocateMemory(1, sizeof(FMUInstance));
    fi->functions = functions;
    if (fi) {
        // Think about what to do with variable values. Using these structs and pointers slows down simulation computations. Maybe only necessary for input, output and tunable parameters??
        fi->r = functions->allocateMemory(NUMBER_OF_REALS, sizeof(fmi2Real));
        fi->i = functions->allocateMemory(NUMBER_OF_INTEGERS, sizeof(fmi2Integer));
        fi->b = functions->allocateMemory(NUMBER_OF_BOOLEANS, sizeof(fmi2Boolean));
        fi->s = functions->allocateMemory(NUMBER_OF_STRINGS,  sizeof(fmi2String));
    } // variables in predefined arrays (performance issue) --> makes multiple instances of fmu impossible


    fi->instanceName = functions->allocateMemory(1 + strlen(instanceName), sizeof(char));
    fi->GUID = functions->allocateMemory(1 + strlen(fmuGUID), sizeof(char));

    strcpy((char*)fi->instanceName, instanceName);
    strcpy((char*)fi->GUID, fmuGUID);
    fi->functions = functions;
    fi->loggingOn = loggingOn;
    fi->isVisible = visible;
    fi->state = fmuInstantiated;
    return fi;
}

fmi2Status fmi2SetupExperiment(fmi2Component fc, fmi2Boolean toleranceDefined, fmi2Real tolerance,
                            fmi2Real startTime, fmi2Boolean stopTimeDefined, fmi2Real stopTime) {


    FMUInstance* fi = (FMUInstance*) fc;
	printf("%s in fmiSetupExperiment\n",fi->instanceName);
	if (fi->state != fmuInstantiated)
	{
		printf("fmu: %s was not instatiated before calling fmiSetupExperiment\n", fi->instanceName);
		return fmi2Error;
	}
	fi->currentTime = startTime;
	fi->stopTimeDefined = stopTimeDefined;
	fi->toleranceDefined = toleranceDefined;
	if (stopTimeDefined)
	{
		fi->stopTime = stopTime;
	}

	if (toleranceDefined)
	{
		fi->tolerance = tolerance;
	}
	//TODO
	//fi->stepSize = getStepSize();
	fi->state = fmuExperimentSettedUp;
    return fmi2OK;
}

fmi2Status fmi2EnterInitializationMode(fmi2Component fc)
{
	FMUInstance* fi = (FMUInstance*) fc;
	printf("%s in fmiEnterInitializationMode\n",fi->instanceName);
	if (fi->state != fmuExperimentSettedUp)
	{
		printf("fmu: %s experiment was not set-up before calling fmiEnterInitializationMode\n", fi->instanceName);
		return fmi2Error;
	}

    fi->state = fmuInitMode;
    return fmi2OK;
}

fmi2Status fmi2ExitInitializationMode(fmi2Component fc)
{
	FMUInstance* fi = (FMUInstance*) fc;
	fmi2Status initStatus = fmi2OK;
	printf("%s in fmiExitInitializationMode\n",fi->instanceName);
	if (fi->state != fmuInitMode)
	{
		printf("fmu: %s did not enter Initialization Mode before calling fmiExitInitializationMode\n", fi->instanceName);
		return fmi2Error;
	}
	// TODO
	//initStatus = calculateInitialUnknownValues();
	//initialize();
    fi->state = fmuInitialized;
    return initStatus;
}

fmi2Status fmi2DoStep(fmi2Component fc , fmi2Real currentCommPoint, fmi2Real commStepSize, fmi2Boolean noPrevFMUState)
{
	FMUInstance* fi = (FMUInstance *)fc;
	fmi2Status simStatus = fmi2OK;
    printf("%s in fmiDoStep()\n",fi->instanceName);

    /*
     * true -> {
		obj_detected := ""; // or null value or something else
		if (not
			(not is_close(stored_armature_current, 5, REL_TOL, ABS_TOL) and stored_armature_current > 5)
					and (not is_close(armature_current, 5, REL_TOL, ABS_TOL) and armature_current > 5)) {
			var negative_value := stored_armature_current - 5;
			var positive_value := armature_current - 5;
			var new_step_size := (h * (- negative_value)) / (positive_value - negative_value);
			discard(new_step_size);
		} else {
			if (not (not is_close(stored_armature_current, 5, REL_TOL, ABS_TOL) and stored_armature_current > 5)
						and is_close(armature_current, 5, REL_TOL, ABS_TOL)) { // crossing found
				obj_detected := "obj";
			}
		}
		stored_armature_current := armature_current; // as there exists a target port obj_detected, the source port armature_current is used. If ports would have the same name (and thus same type), the value resulting from the crossing would be stored
	} --> {
	};*/
    fi->b[_out_obj_detected] = 0;
    if(!(! is_close(fi->r[_stored_armature_current], 5 , 0.0001, 1e-8) && fi->r[_stored_armature_current] > 5)
    		&& (!is_close(fi->r[_in_armature_current],5, 0.0001, 1e-8) && fi->r[_in_armature_current] > 5)){ // should this be <
    		double negative_value = fi->r[_stored_armature_current] - 5;
    		double positive_value = fi->r[_in_armature_current] - 5;
    		double new_step_size = (commStepSize * (-negative_value)) / (positive_value - negative_value);
    		fi->currentTime = currentCommPoint + new_step_size;
    		simStatus = fmi2Discard;

    }else{
    	if(!(! is_close(fi->r[_stored_armature_current],5,0.0001,1e-8) && fi->r[_stored_armature_current] > 5)
    			&& is_close(fi->r[_in_armature_current],5, 0.0001, 1e-8)){
    			fi->b[_out_obj_detected] = 1;
    	}
    }
    /* Set out:*/
    fi->b[_out_driver_down] = fi->b[_in_driver_down];
    fi->b[_out_driver_down_stop] = fi->b[_in_driver_down_stop];
    fi->b[_out_driver_up] = fi->b[_in_driver_up];
    fi->b[_out_driver_up_stop] = fi->b[_in_driver_up_stop];
    fi->b[_out_passenger_down] = fi->b[_in_passenger_down];
    fi->b[_out_passenger_down_stop] = fi->b[_in_passenger_down_stop];
    fi->b[_out_passenger_up] = fi->b[_in_passenger_up];
    fi->b[_out_passenger_up_stop] = fi->b[_in_passenger_up_stop];

    /*Control signal*/
    if(fi->b[_out_driver_down] || fi->b[_out_driver_down_stop]|| fi->b[_out_driver_up] ||
    		 fi->b[_out_driver_up_stop] || fi->b[_out_obj_detected] ||
			 fi->b[_out_passenger_down] || fi->b[_out_passenger_down_stop] ||
			 fi->b[_out_passenger_up] || fi->b[_out_passenger_up_stop]){
    	fi->b[_out_control] = 1;
    }
	return simStatus;
}

fmi2Status fmi2Terminate(fmi2Component fc)
{
	FMUInstance* fi = (FMUInstance *)fc;
	printf("%s in fmiTerminate\n",fi->instanceName);
	// do check if fi may be terminated
	fi->state = fmuTerminated;
    return fmi2OK;
}


void fmi2FreeInstance(fmi2Component fc)
{

	FMUInstance* fi = (FMUInstance*) fc;
	printf("%s in fmiFreeInstance\n",fi->instanceName);

    if (fi) {

        fi->functions->freeMemory(fi->r);
        fi->functions->freeMemory(fi->i);
        fi->functions->freeMemory(fi->b);
        fi->functions->freeMemory(fi->s);// TODO has to be done with loop
		fi->functions->freeMemory((void*)fi->instanceName);
		fi->functions->freeMemory((void*)fi->GUID);
		fi->functions->freeMemory((void*)fi);

    }
}

//To be implemented

const char* fmi2GetVersion() {
	printf("Function fmiGetVersion not supported\n");
    return NULL;
}

const char* fmi2GetTypesPlatform() {
	printf("Function fmiGetTypesPlatform not supported\n");
    return NULL;
}

fmi2Status fmi2Reset(fmi2Component fc)
{
	printf("Function fmiReset not supported\n");
    return fmi2Error;
}

fmi2Status fmi2SetInteger(fmi2Component fc, const fmi2ValueReference vr[], size_t nvr, const fmi2Integer value[])
{
    printf("Function fmiSetInteger not supported\n");
    return fmi2Error;
}

fmi2Status fmi2GetInteger(fmi2Component fc, const fmi2ValueReference vr[], size_t nvr, fmi2Integer value[])
{
    printf("Function fmiGetInteger not supported\n");
    return fmi2Error;
}


/*******OWN IMPLEMENTATION OF Get/Set FMU state*******/
fmi2Status fmi2GetFMUstate (fmi2Component c, fmi2FMUstate* FMUstate) {
    FMUInstance* orig = (FMUInstance*)c;
    FMUInstance* fi = (FMUInstance *)FMUstate;
    fi = orig->functions->allocateMemory(1, sizeof(FMUInstance));
    *FMUstate = fi;
    if (fi) {
        // Think about what to do with variable values. Using these structs and pointers slows down simulation computations. Maybe only necessary for input, output and tunable parameters??
        fi->r = orig->functions->allocateMemory(NUMBER_OF_REALS, sizeof(fmi2Real));
        fi->i = orig->functions->allocateMemory(NUMBER_OF_INTEGERS, sizeof(fmi2Integer));
        fi->b = orig->functions->allocateMemory(NUMBER_OF_BOOLEANS, sizeof(fmi2Boolean));
        fi->s = orig->functions->allocateMemory(NUMBER_OF_STRINGS,  sizeof(fmi2String));

    } // variables in predefined arrays (performance issue) --> makes multiple instances of fmu impossible
    fi->instanceName = orig->functions->allocateMemory(1 + strlen(orig->instanceName), sizeof(char));
    fi->GUID = orig->functions->allocateMemory(1 + strlen(orig->GUID), sizeof(char));

    strcpy((char *)fi->instanceName, (char *)orig->instanceName);
    strcpy((char *)fi->GUID, (char *)orig->GUID);
    fi->functions = orig->functions;
    fi->loggingOn = orig->loggingOn;
    fi->isVisible = orig->isVisible;
    fi->state = orig->state;
    fi->stepSize = orig->stepSize;
    fi->startTime = orig->startTime;
    fi->stopTime = orig->stopTime;
	fi->currentTime = orig->currentTime;
	//copy r
	int i=0;
	for (i=0; i< NUMBER_OF_REALS;i++){
	    printf("Setting real: %i %f\n", i, orig->r[i]);
        fi->r[i] = orig->r[i];
        printf("Setted real: %i %f\n", i, fi->r[i]);
	}
	//copy s
	for (i=0; i< NUMBER_OF_STRINGS;i++){
        fi->s[i] = orig->s[i];
	}
	//copy i
    for (i=0; i< NUMBER_OF_INTEGERS;i++){
        fi->i[i] = orig->i[i];
	}
	//copy b
	for (i=0; i< NUMBER_OF_BOOLEANS;i++){
        fi->b[i] = orig->b[i];
	}
    return fmi2OK;
}


fmi2Status fmi2SetFMUstate (fmi2Component c, fmi2FMUstate FMUstate) {
    FMUInstance* orig = (FMUInstance*)FMUstate;
    FMUInstance* fi = (FMUInstance*)c;
    //set time etc correct, name and GUID should still be ok ;-)
    printf("setting time values from %f to %f\n", fi->currentTime, orig->currentTime);
    fi->state = orig->state;
    fi->stepSize = orig->stepSize;
    fi->startTime = orig->startTime;
    fi->stopTime = orig->stopTime;
	fi->currentTime = orig->currentTime;
	printf("setting real values\n");
	//copy r
	int i=0;
	for (i=0; i< NUMBER_OF_REALS;i++){
        fi->r[i] = orig->r[i];
	}
	printf("setting string values\n");
	//copy s
	for (i=0; i< NUMBER_OF_STRINGS;i++){

        fi->s[i] = orig->s[i];
	}
	//copy i
    for (i=0; i< NUMBER_OF_INTEGERS;i++){
        fi->i[i] = orig->i[i];
	}
	//copy b
	for (i=0; i< NUMBER_OF_BOOLEANS;i++){
        fi->b[i] = orig->b[i];
	}
    return fmi2OK;


}
/****************************************************/

fmi2Status fmi2FreeFMUstate(fmi2Component c, fmi2FMUstate* FMUstate) {
    printf("Function fmiFreeFMUstate not supported\n");
    return fmi2Error;
}
fmi2Status fmi2SerializedFMUstateSize(fmi2Component c, fmi2FMUstate FMUstate, size_t *size) {
    printf("Function fmiSerializedFMUstateSize not supported\n");
    return fmi2Error;
}
fmi2Status fmi2SerializeFMUstate (fmi2Component c, fmi2FMUstate FMUstate, fmi2Byte serializedState[], size_t size) {
    printf("Function fmiSerializeFMUstate not supported\n");
    return fmi2Error;
}
fmi2Status fmi2DeSerializeFMUstate (fmi2Component c, const fmi2Byte serializedState[], size_t size, fmi2FMUstate* FMUstate) {
    printf("Function fmiDeSerializeFMUstate not supported\n");
    return fmi2Error;
}

fmi2Status fmi2GetDirectionalDerivative(fmi2Component c, const fmi2ValueReference vUnknown_ref[], size_t nUnknown,
                const fmi2ValueReference vKnown_ref[] , size_t nKnown, const fmi2Real dvKnown[], fmi2Real dvUnknown[]) {
    printf("Function fmiGetDirectionalDerivative not supported\n");
    return fmi2Error;
}


fmi2Status fmi2SetRealInputDerivatives(fmi2Component c, const fmi2ValueReference vr[], size_t nvr,
                                     const fmi2Integer order[], const fmi2Real value[]) {
    printf("Function fmiGetDirectionalDerivative not supported\n");
    return fmi2Error;
}

fmi2Status fmi2GetRealOutputDerivatives(fmi2Component c, const fmi2ValueReference vr[], size_t nvr,
                                      const fmi2Integer order[], fmi2Real value[]) {
    printf("Function fmiGetDirectionalDerivative not supported\n");
    return fmi2Error;
}

fmi2Status fmi2CancelStep(fmi2Component c) {
    printf("Function fmiGetDirectionalDerivative not supported\n");
    return fmi2Error;
}

fmi2Status fmi2GetStatus(fmi2Component c, const fmi2StatusKind s, fmi2Status *value) {
    printf("Function fmiGetStatus not supported\n");
    return fmi2Error;
}

fmi2Status fmi2GetRealStatus(fmi2Component c, const fmi2StatusKind s, fmi2Real *value) {
    if(s == fmi2LastSuccessfulTime){
        FMUInstance* comp = (FMUInstance*) c;
        *value = comp->currentTime;
        return fmi2OK;
    }
    printf("Function fmiGetRealStatus not supported\n");
    return fmi2Error;
}

fmi2Status fmi2GetIntegerStatus(fmi2Component c, const fmi2StatusKind s, fmi2Integer *value) {
    printf("Function fmiGetIntegerStatus not supported\n");
    return fmi2Error;
}

fmi2Status fmi2GetBooleanStatus(fmi2Component c, const fmi2StatusKind s, fmi2Boolean *value) {
    printf("Function fmiGetBooleanStatus not supported\n");
    return fmi2Error;
}

fmi2Status fmi2GetStringStatus(fmi2Component c, const fmi2StatusKind s, fmi2String *value) {
    printf("Function fmiGetStringStatus not supported\n");
    return fmi2Error;
}
