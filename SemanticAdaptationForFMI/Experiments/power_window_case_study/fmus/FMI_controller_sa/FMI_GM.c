/* ---------------------------------------------------------------------------*
 * Sample implementation of an generic master FMU -
 * ---------------------------------------------------------------------------*/
/*
Template for a  FMU
 */

#define MODEL_IDENTIFIER GM
#define MODEL_GUID "1"
#define FMI2_FUNCTION_PREFIX PW_CONTROLLER_SA_

#define MAX 10000

#include <stdio.h>
#include "string.h"
#include "fmi2Functions.h"
#include <float.h>
#include "FMI_GM.h"
#include <math.h>
#include "fmi2.h"
#include "sim_support.h"



#define NUMBER_OF_REALS 1
#define NUMBER_OF_STRINGS 0
#define NUMBER_OF_BOOLEANS 11
#define NUMBER_OF_INTEGERS 0
/*
 * The input
 */

#define _in_armature_current 0

#define _in_driver_up 0
#define _in_driver_up_stop 1
#define _in_driver_down 2
#define _in_driver_down_stop 3
#define _in_passenger_up 4
#define _in_passenger_up_stop 5
#define _in_passenger_down 6
#define _in_passenger_down_stop 7


/*
 * The output:
 */

#define _out_u 9
#define _out_d 10


double relativeError(double a, double b){
	if(a==0){
		return  0;
	}
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
		comp->r[vr[i]] = value[i];
	}

	/*Generated: */
	fmi2Boolean in_condition[_NR_OF_IN_CONDITIONS];
	/*Condition checking:*/
	// get_next_step ->
	in_condition[0] = comp->get_next_step;
	//true
	in_condition[1] = 1;

	if(in_condition[0]){
		printf("%s: Calculating max allowed step size... \n",comp->instanceName);

		fmi2Component fmu0_temp;
		comp->fmu[0].getFMUstate(comp->c_fmu[0],&fmu0_temp);
		fmi2Status status;
		status = comp->fmu[0].doStep(comp->c_fmu[0],comp->time_last_fmu[0], MAX, fmi2False);
		if(status == fmi2Discard){
			fmi2Real nextTime;
			comp->fmu[0].getRealStatus(comp->c_fmu[0],fmi2LastSuccessfulTime, &nextTime);
			comp->next_time_step = nextTime;
		}else{
			comp->next_time_step = -1;
		}
		printf("%s: Step size max = %f... \n",comp->instanceName, comp->next_time_step);
		comp->fmu[0].setFMUstate(comp->c_fmu[0],fmu0_temp);
		comp->fmu[0].freeInstance(fmu0_temp); // TODO: should be fmi2FreeFMUState
	}
	if(in_condition[1]){
		comp->stored_arm_current = comp->r[_in_armature_current];
		printf("%s: comp->stored_arm_current = %f... \n",comp->instanceName, comp->stored_arm_current);
		printf("%s: comp->previous_arm_current = %f... \n",comp->instanceName, comp->previous_arm_current);
		/* If mealy do update_in and recursive call */
	}

	//out_condition_executed := empty map
	memset(comp->out_conditions_executed,0,sizeof(fmi2Boolean)*_NR_OF_OUT_CONDITIONS);
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

	int isEmpty = 1;
	for (int i=0; i<_NR_OF_OUT_CONDITIONS;i++){
		if(comp->out_conditions_executed[i] !=0){
			isEmpty = 0;
			break;
		}
	}

	/*Eval conditions:*/
		if(1){
			comp->out_conditions_executed[0] = 1;
		}
	/*Set correct values */
	if (isEmpty){
		for(int i=0; i<_NR_OF_OUT_CONDITIONS;i++){
			if(comp->out_conditions_executed[i]){
				comp->b[_out_u] = comp->stored_up;
				comp->b[_out_d] = comp->stored_down;
			}
		}
	}

	/*
	 Copy to given array */
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
	/* Load the inner FMUs:*/

	loadDll("libFMI_controller.dll", &(fi->fmu[0]), "PW_Controller");
	fi->fmuResourceLocation[0] = "libpw_controller";

	/*Instantiate inner components*/
	for (int i=0; i<1; i++){
		fi->c_fmu[i] = fi->fmu[i].instantiate("inner", fmi2CoSimulation, "1", fi->fmuResourceLocation[i] , fi->functions, visible, 0);
	}
	return fi;
}

fmi2Status fmi2SetupExperiment(fmi2Component fc, fmi2Boolean toleranceDefined, fmi2Real tolerance,
		fmi2Real startTime, fmi2Boolean stopTimeDefined, fmi2Real stopTime) {


	FMUInstance* fi = (FMUInstance*) fc;
	printf("%s in fmiSetupExperiment\n",fi->instanceName);
	if (fi->state != fmuInstantiated)
	{
		printf("fmu: %s was not instantiated before calling fmiSetupExperiment\n", fi->instanceName);
		return fmi2Error;
	}
	fi->currentTime = startTime;
	fi->stopTimeDefined = stopTimeDefined;
	fi->toleranceDefined = toleranceDefined;
	if (stopTimeDefined)
	{
		fi->stopTime = stopTime;
	}
	/*
	 * setup inner
	 */
	fmi2Status fmi2Flag = fmi2OK;
	fi->state = fmuExperimentSettedUp;
	for(int i=0; i<1; i++){
		fmi2Flag = fi->fmu[i].setupExperiment(fi->c_fmu[i], toleranceDefined, tolerance, startTime, fmi2True, stopTime);
		if (fmi2Flag == fmi2Error){
			fi->state = fmuError;
		}
	}
	return fmi2Flag;
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
	fmi2Status fmi2Flag = fmi2OK;
	for(int i=0; i<1; i++){
		fmi2Flag = fi->fmu[i].enterInitializationMode(fi->c_fmu[i]);
		if (fmi2Flag == fmi2Error){
			return fi->state = fmuError;
		}
	}

	fi->ABS_TOLERANCE = 1e-08;
	fi->REL_TOLERANCE = 0.0001;
	fi->CROSSING = 5;
	fi->init_armature_current = fi->CROSSING;
	fi->init_down = 0;
	fi->init_up = 0;
	fi->next_time_step = INFINITY;
	fi->stored_arm_current = fi->CROSSING;
	fi->aux_obj_detected = 0;
	fi->get_next_step = 1;
	fi->previous_arm_current = fi->CROSSING;

	return fmi2Flag;
}

fmi2Status fmi2ExitInitializationMode(fmi2Component fc)
{
	FMUInstance* fi = (FMUInstance*) fc;
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
	fmi2Status fmi2Flag = fmi2OK;
	for(int i=0; i<1;i++){
		fmi2Flag = fi->fmu[i].exitInitializationMode(fi->c_fmu[i]);
		if (fmi2Flag == fmi2Error){
			return fi->state = fmuError;
		}
	}
	return fmi2Flag;
}

fmi2Status fmi2DoStep(fmi2Component fc , fmi2Real currentCommPoint, fmi2Real commStepSize, fmi2Boolean noPrevFMUState)
{
	FMUInstance* fi = (FMUInstance *)fc;
	fmi2Status externalSimStatus = fmi2OK;
	fmi2Status internalSimStatus = fmi2OK;
	memset(fi->out_conditions_executed,0,sizeof(fmi2Boolean)*_NR_OF_OUT_CONDITIONS);
	fmi2Boolean b_temp_out[2];

	printf("%s in fmiDoStep(), ct:%f, h:%f\n",fi->instanceName,currentCommPoint,commStepSize);
	fi->aux_obj_detected = 0;
	fi->step_size = commStepSize;

	if (fi->toleranceDefined){
		printf("%s: Accurate checking for threshold crossing...\n",fi->instanceName);
		if( (
					(!is_close(fi->previous_arm_current, fi->CROSSING , fi->REL_TOLERANCE, fi->ABS_TOLERANCE))
					&& fi->previous_arm_current < fi->CROSSING
				)
				&&
				(
					(!is_close(fi->stored_arm_current,fi->CROSSING,fi->REL_TOLERANCE,fi->ABS_TOLERANCE))
					&& fi->stored_arm_current > fi->CROSSING
				)
			   ){
				double negative_value = fi->previous_arm_current - fi->CROSSING;
				double positive_value = fi->stored_arm_current - fi->CROSSING;
				fi->step_size = (commStepSize * (-negative_value)) / (positive_value - negative_value);
				fi->currentTime = currentCommPoint + fi->step_size;
				externalSimStatus = fmi2Discard;
				printf("%s: crossed too far, rejecting step size %f and proposing %f... \n",fi->instanceName, commStepSize, fi->step_size);
				printf("%s: fi->previous_arm_current = %f \n",fi->instanceName, fi->previous_arm_current);
				printf("%s: fi->stored_arm_current = %f \n",fi->instanceName, fi->stored_arm_current);
			} else if((
						(!is_close(fi->previous_arm_current, fi->CROSSING , fi->REL_TOLERANCE, fi->ABS_TOLERANCE))
						&& fi->previous_arm_current < fi->CROSSING
					)
					&&
					(
						is_close(fi->stored_arm_current,fi->CROSSING,fi->REL_TOLERANCE,fi->ABS_TOLERANCE)
					)
				  ){
					fi->aux_obj_detected = 1;
					printf("%s: crossed just right... \n",fi->instanceName);
			}
	} else {
		printf("%s: Non-accurate checking for threshold crossing...\n",fi->instanceName);
		if( (
				(!is_close(fi->previous_arm_current, fi->CROSSING , fi->REL_TOLERANCE, fi->ABS_TOLERANCE))
				&& fi->previous_arm_current < fi->CROSSING
			)
			&&
			(
				(!is_close(fi->stored_arm_current,fi->CROSSING,fi->REL_TOLERANCE,fi->ABS_TOLERANCE))
				&& fi->stored_arm_current > fi->CROSSING
			)
		   ){
			fi->aux_obj_detected = 1;
			printf("%s: crossed just right... \n",fi->instanceName);
		}
	}

	if (externalSimStatus == fmi2OK){ // only do the internal step if the current step is OK
		if (((fi->next_time_step != -1 && currentCommPoint > fi->next_time_step ) || 1)){
			fmi2ValueReference vr_in_star[8] = {1,2,3,4,5,6,7,8};
			fi->fmu[0].setBoolean(fi->c_fmu[0], vr_in_star,8, &(fi->b[0]));
			fmi2ValueReference vr_aux_obj_detected[1] = {0};
			fi->fmu[0].setBoolean(fi->c_fmu[0], vr_aux_obj_detected,1, &(fi->aux_obj_detected));
			internalSimStatus = fi->fmu[0].doStep(fi->c_fmu[0], currentCommPoint, commStepSize, fmi2True);
			fmi2ValueReference vr_out_star[2]={9,10};
			fi->fmu[0].getBoolean(fi->c_fmu[0],vr_out_star,2,&b_temp_out[0]);
			fi->get_next_step = 1;
		} else {
			fi->get_next_step = 0;
		}

		if(internalSimStatus == fmi2Discard){
			externalSimStatus = fmi2Discard;
			fmi2Real theNextTime = currentCommPoint + fi->step_size;
			for(int i=0; i<1; i++){
				fmi2Real theFMUtime;
				fi->fmu[i].getRealStatus(fi->c_fmu[i], fmi2LastSuccessfulTime, &theFMUtime);
				if(theFMUtime<theNextTime){
					theNextTime = theFMUtime;
				}
			}
			fi->currentTime = theNextTime;
		}
	}



	if(externalSimStatus == fmi2OK){
		printf("%s: Step accepted, committing arm current... \n",fi->instanceName);
		fi->currentTime = currentCommPoint + commStepSize;
		fi->time_last_fmu[0] = currentCommPoint + commStepSize;
		fi->previous_arm_current = fi->stored_arm_current;
	}

	/* do out functions*/
	if(b_temp_out[0]){
		fi->stored_up = 1;
	}
	if(!b_temp_out[0]){
		fi->stored_up = 0;
	}
	if(b_temp_out[1]){
		fi->stored_down = 1;
	}
	if(!b_temp_out[1]){
		fi->stored_down = 0;
	}

	memset(fi->in_condition_executed, 0, sizeof(fmi2Boolean)*_NR_OF_IN_CONDITIONS);
	return externalSimStatus;
}

fmi2Status fmi2Terminate(fmi2Component fc)
{
	FMUInstance* fi = (FMUInstance *)fc;
	printf("%s in fmiTerminate\n",fi->instanceName);
	// do check if fi may be terminated
	for (int i=0;i<1;i++){
		fi->fmu[i].terminate(fi->c_fmu[i]);
	}

	fi->state = fmuTerminated;
	return fmi2OK;
}


void fmi2FreeInstance(fmi2Component fc)
{

	FMUInstance* fi = (FMUInstance*) fc;
	printf("%s in fmiFreeInstance\n",fi->instanceName);
	for(int i=0;i<1;i++){
		fi->fmu[i].freeInstance(fi->c_fmu[i]);
	}

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
	*FMUstate = fi;
	fi = orig->functions->allocateMemory(1, sizeof(FMUInstance));
	*FMUstate = fi;
	fi->functions = orig->functions;

	if (fi) {
		// Think about what to do with variable values. Using these structs and pointers slows down simulation computations. Maybe only necessary for input, output and tunable parameters??
		fi->r = fi->functions->allocateMemory(NUMBER_OF_REALS, sizeof(fmi2Real));
		fi->i = fi->functions->allocateMemory(NUMBER_OF_INTEGERS, sizeof(fmi2Integer));
		fi->b = fi->functions->allocateMemory(NUMBER_OF_BOOLEANS, sizeof(fmi2Boolean));
		fi->s = fi->functions->allocateMemory(NUMBER_OF_STRINGS,  sizeof(fmi2String));

	} // variables in predefined arrays (performance issue) --> makes multiple instances of fmu impossible
	fi->instanceName = orig->functions->allocateMemory(1 + strlen(orig->instanceName), sizeof(char));
	fi->GUID = orig->functions->allocateMemory(1 + strlen(orig->GUID), sizeof(char));

	strcpy((char *)fi->instanceName, (char *)orig->instanceName);
	strcpy((char *)fi->GUID, (char *)orig->GUID);
	fi->functions = orig->functions;
	fi->loggingOn = orig->loggingOn;
	fi->isVisible = orig->isVisible;
	fi->state = orig->state;
	fi->startTime = orig->startTime;
	fi->stopTime = orig->stopTime;
	fi->currentTime = orig->currentTime;
	/* TODO: Store all the rest here.*/
	fi->fmu[0] = orig->fmu[0];
	fi->c_fmu[0] = orig->c_fmu[0];
	for(int i=0; i<_NR_OF_IN_CONDITIONS;i++){
		fi->in_condition_executed[i] = orig->in_condition_executed[i];
	}
	for(int i=0; i<_NR_OF_OUT_CONDITIONS;i++){
		fi->out_conditions_executed[i] = orig->out_conditions_executed[i];
	}
	for(int i=0;i<_NR_OF_FMUS;i++){
		fi->time_last_fmu[i] = orig->time_last_fmu[i];
	}

	/* Generated */
	fi->REL_TOLERANCE = orig->REL_TOLERANCE;
	fi->ABS_TOLERANCE = orig->ABS_TOLERANCE;
	fi->CROSSING = orig->CROSSING;
	fi->init_up = orig->init_up;
	fi->init_down = orig->init_down;
	fi->init_armature_current = orig->init_armature_current;
	fi->next_time_step = orig->next_time_step;
	fi->stored_arm_current = orig->stored_arm_current;
	fi->step_size = orig->step_size;
	fi->aux_obj_detected = orig->aux_obj_detected;
	fi->get_next_step = orig->get_next_step;
	fi->previous_arm_current = orig->previous_arm_current;
	fi->stored_up = orig->stored_up;
	fi->stored_down = orig->stored_down;

	fi->toleranceDefined = orig->toleranceDefined;
	/*
	 * This is a hierarchical call. First let the lower FMUs do their state saving
	 * We will store the saved fmu state in the fi->c_order[i]
	 */
	for(int i=0;i<1;i++){
		fi->fmu[i]=orig->fmu[i];
		orig->fmu[i].getFMUstate(orig->c_fmu[i],fi->c_fmu[i]);
		fi->fmuResourceLocation[i] = fi->functions->allocateMemory(1+strlen(orig->fmuResourceLocation[i]), sizeof(char));
		strcpy((char *)fi->fmuResourceLocation[i],(char *)orig->fmuResourceLocation[i]);
		/*make shallow copies of the stored fmus*/
	}
	//copy r
	int i=0;
	for (i=0; i< NUMBER_OF_REALS;i++){
		printf("Setting real: %i %f\n", i, orig->r[i]);
		fi->r[i] = orig->r[i];
		printf("Setted real: %i %f\n", i, fi->r[i]);
	}
	//copy s
	for (i=0; i< NUMBER_OF_STRINGS;i++){
		//fi->s[i] = orig->s[i]; // why are this not deep copies?
		fi->s[i] = fi->functions->allocateMemory(1+strlen(orig->s[i]),sizeof(char));
		strcpy((char *)fi->s[i],(char *)orig->s[i]);
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
	/*
	 * First restore the hierarchical fmus.
	 */
	for(int i=0;i<1;i++){
		fi->fmu[i].setFMUstate(fi->c_fmu[i],orig->c_fmu[i]);
		fi->fmuResourceLocation[i] = orig->functions->allocateMemory(1+strlen(orig->fmuResourceLocation[i]), sizeof(char));
		strcpy((char *)fi->fmuResourceLocation[i],(char *)orig->fmuResourceLocation[i]);
	}

	//set time etc correct, name and GUID should still be ok ;-)
	printf("setting time values from %f to %f\n", fi->currentTime, orig->currentTime);
	fi->state = orig->state;
	fi->startTime = orig->startTime;
	fi->stopTime = orig->stopTime;
	fi->currentTime = orig->currentTime;

	fi->fmu[0] = orig->fmu[0];
	fi->c_fmu[0] = orig->c_fmu[0];
	for(int i=0; i<_NR_OF_IN_CONDITIONS;i++){
		fi->in_condition_executed[i] = orig->in_condition_executed[i];
	}
	for(int i=0; i<_NR_OF_OUT_CONDITIONS;i++){
		fi->out_conditions_executed[i] = orig->out_conditions_executed[i];
	}
	for(int i=0;i<_NR_OF_FMUS;i++){
		fi->time_last_fmu[i] = orig->time_last_fmu[i];
	}

	/* Generated */
	fi->REL_TOLERANCE = orig->REL_TOLERANCE;
	fi->ABS_TOLERANCE = orig->ABS_TOLERANCE;
	fi->CROSSING = orig->CROSSING;
	fi->init_up = orig->init_up;
	fi->init_down = orig->init_down;
	fi->init_armature_current = orig->init_armature_current;
	fi->next_time_step = orig->next_time_step;
	fi->stored_arm_current = orig->stored_arm_current;
	fi->step_size = orig->step_size;
	fi->aux_obj_detected = orig->aux_obj_detected;
	fi->get_next_step = orig->get_next_step;
	fi->previous_arm_current = orig->previous_arm_current;
	fi->stored_up = orig->stored_up;
	fi->stored_down = orig->stored_down;

	fi->toleranceDefined = orig->toleranceDefined;

	fi->toleranceDefined = orig->toleranceDefined;
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
