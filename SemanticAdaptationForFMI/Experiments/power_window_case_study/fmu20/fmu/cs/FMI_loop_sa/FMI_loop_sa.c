/* ---------------------------------------------------------------------------*
 * Sample implementation of an generic master FMU -
 * ---------------------------------------------------------------------------*/
/*
Template for a  FMU
 */

#define MODEL_IDENTIFIER GM
#define MODEL_GUID "{41f87101-edf2-4eef-90f3-42db56d4565f}"
#define FMI2_FUNCTION_PREFIX LOOP_SA


#include <stdio.h>
#include "string.h"
#include "fmi2Functions.h"
#include <float.h>
#include "FMI_loop_sa.h"
#include <math.h>
#include "fmi2.h"
#include "sim_support.h"


#define MAX 100000

#define NUMBER_OF_REALS 3
#define NUMBER_OF_STRINGS 0
#define NUMBER_OF_BOOLEANS 0
#define NUMBER_OF_INTEGERS 0

#define MAXITER 10
#define REL_TOL 1e-05
#define ABS_TOL 1e-05

#define _out_tau 0
#define _in_speed 1
#define _in_displacement 2


#define _window_sa 0
#define _obstacle 1

double relativeError(double a, double b){
	if (a == 0){
		return 0;
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
int is_close(double a, double b, double rel_tol, double abs_tol){
	return ((absoluteError(a,b)<abs_tol) && (relativeError(a,b)<rel_tol));
}

fmi2Status fmi2SetDebugLogging(fmi2Component fc, fmi2Boolean loggingOn, size_t nCategories, const fmi2String categories[])
{
	return fmi2OK;
}

fmi2Status fmi2SetString(fmi2Component fc, const fmi2ValueReference vr[], size_t nvr, const fmi2String value[])
{
	FMUInstance*  comp = (FMUInstance *)fc;

	memset(comp->out_conditions_executed,0,sizeof(fmi2Boolean)*_NR_OF_OUT_CONDITIONS);
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
	//out_condition_executed := empty map
	memset(comp->out_conditions_executed,0,sizeof(fmi2Boolean)*_NR_OF_OUT_CONDITIONS);
	return fmi2OK;
}

fmi2Status fmi2GetReal(fmi2Component fc, const fmi2ValueReference vr[], size_t nvr, fmi2Real value[])
{

	FMUInstance* comp = (FMUInstance *)fc;

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

	if (isEmpty){
		for(int i=0; i<_NR_OF_OUT_CONDITIONS;i++){
			if(comp->out_conditions_executed[i]){

			}
		}
	}
	for (int i = 0; i < nvr; i++)
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
	/*Generated: */
		fmi2Boolean in_condition[_NR_OF_IN_CONDITIONS];
		/*Condition checking:*/
		// true
		in_condition[0] = 1;

		if(in_condition[0]){
			/* If mealy do update_in and recursive call */
		}
		return fmi2OK;

	//out_condition_executed := empty map
	memset(comp->out_conditions_executed,0,sizeof(fmi2Boolean)*_NR_OF_OUT_CONDITIONS);
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

	loadDll("libFMI_Window_sa.dll", &(fi->fmu[_window_sa]), "WINDOW_SA");
	fi->fmuResourceLocation[_window_sa] = "libFMI_Window_sa";
	loadDll("Obstacle.dll", &(fi->fmu[_obstacle]),"");
	fi->fmuResourceLocation[_obstacle] = "Obstacle.dll";

	fi->fmu_guid[_window_sa]= functions->allocateMemory(1 + strlen("1"), sizeof(char));
	fi->fmu_guid[_obstacle] = functions->allocateMemory(1 + strlen("{c6327117-e5f2-4e48-abcd-318439d1e7c4}"), sizeof(char));
	strcpy(fi->fmu_guid[_window_sa], "1");
	strcpy(fi->fmu_guid[_obstacle], "{8de5bd74-8d30-4a72-9170-0e4bf874b6a8}");

	/*Instantiate inner components*/

	fi->c_fmu[_window_sa] = fi->fmu[_window_sa].instantiate("window_sa", fmi2CoSimulation, fi->fmu_guid[_window_sa], fi->fmuResourceLocation[_window_sa] , fi->functions, visible, 0);
	fi->c_fmu[_obstacle] = fi->fmu[_obstacle].instantiate("obstacle", fmi2CoSimulation, fi->fmu_guid[_obstacle], fi->fmuResourceLocation[_obstacle] , fi->functions, visible, 0);

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
	/*
	 * setup inner
	 */
	fmi2Status fmi2Flag = fmi2OK;
	fi->state = fmuExperimentSettedUp;
	for(int i=0; i<_NR_OF_FMUS; i++){
		fmi2Flag = fi->fmu[i].setupExperiment(fi->c_fmu[i], toleranceDefined, tolerance, startTime, fmi2True, stopTime);
		if (fmi2Flag == fmi2Error){
			fi->state = fmuError;
		}
	}

	fi->prev_disp = 0;

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
	for(int i=0; i<_NR_OF_FMUS; i++){
		fmi2Flag = fi->fmu[i].enterInitializationMode(fi->c_fmu[i]);
		if (fmi2Flag == fmi2Error){
			return fi->state = fmuError;
		}
	}
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
	for(int i=0; i<_NR_OF_FMUS;i++){
		fmi2Flag = fi->fmu[i].exitInitializationMode(fi->c_fmu[i]);
		if (fmi2Flag == fmi2Error){
			return fi->state = fmuError;
		}
	}
	return fmi2Flag;
}

static fmi2Status DoInnerStep(fmi2Component fc, int index, fmi2Real currentCommPoint, fmi2Real commStepSize){
	fmi2Status status = fmi2OK;
	FMUInstance* fi = (FMUInstance *)fc;

	fmi2Real dt =currentCommPoint - fi->time_last_fmu[index];
	fmi2Real h = commStepSize + dt;
	int repeat = 0;

	fmi2Component obstacle_temp, window_sa_temp;
	fmi2ValueReference vr_to_window_sa[3]={2,3,4};
	fmi2ValueReference vr_disp[1] = {2};
	fmi2ValueReference vr_F_obstacle[1] = {0};
	fmi2ValueReference vr_from_window[2] = {0,1};
	fmi2Real toWindowSA[3];
	fmi2Real fromWindow[2];
	for (int iter= 0; iter< MAXITER; iter++) {
		fi->fmu[_obstacle].getFMUstate(fi->c_fmu[_obstacle], &obstacle_temp);
		fi->fmu[_window_sa].getFMUstate(fi->c_fmu[_window_sa], &window_sa_temp);

		fi->fmu[_obstacle].setReal(fi->c_fmu[_obstacle], vr_disp,1, &fi->prev_disp);
		fi->fmu[_obstacle].doStep(fi->c_fmu[_obstacle], currentCommPoint, commStepSize, fmi2True);
		fi->fmu[_obstacle].getReal(fi->c_fmu[_obstacle],vr_F_obstacle,1,&toWindowSA[0]);

		toWindowSA[1] = fi->r[_in_displacement];
		toWindowSA[2] = fi->r[_in_speed];
		fi->fmu[_window_sa].setReal(fi->c_fmu[_window_sa], vr_to_window_sa, 3, &toWindowSA[0]);
		fi->fmu[_window_sa].doStep(fi->c_fmu[_window_sa], currentCommPoint, commStepSize, fmi2True);
		fi->fmu[_window_sa].getReal(fi->c_fmu[_window_sa], vr_from_window, 2, &fromWindow[0]);

		repeat = is_close(fi->prev_disp, fromWindow[1], REL_TOL, ABS_TOL);
		fi->prev_disp = fromWindow[1];
		if (repeat) {
			break;
		} else {
			//rollback(obstacle);
			fi->fmu[_obstacle].setFMUstate(fi->c_fmu[_obstacle], obstacle_temp);
			fi->fmu[_window_sa].setFMUstate(fi->c_fmu[_window_sa], window_sa_temp);

			//rollback(window_sa);
		}
		fi->fmu[_obstacle].freeInstance(obstacle_temp);
		fi->fmu[_window_sa].freeInstance(window_sa_temp);
		if(1){
			fi->r[_out_tau] = fromWindow[0];
		}
	}
	return status;
}
fmi2Status fmi2DoStep(fmi2Component fc , fmi2Real currentCommPoint, fmi2Real commStepSize, fmi2Boolean noPrevFMUState)
{
	FMUInstance* fi = (FMUInstance *)fc;
	fmi2Status simStatus = fmi2OK;
	printf("%s in fmiDoStep(), ct:%f, h:%f\n",fi->instanceName,currentCommPoint,commStepSize);
	memset(fi->out_conditions_executed,0,sizeof(fmi2Boolean)*_NR_OF_OUT_CONDITIONS);


	/*
	Calculate the elapsed time since the last transition
	*/
	fmi2Real e = MAX;
	fmi2Real elapsed_fmu[_NR_OF_FMUS];
	for (int i=0; i<_NR_OF_FMUS; i++){
		elapsed_fmu[i] = currentCommPoint - fi->time_last_fmu[i];
		e = (elapsed_fmu[i]<e)? elapsed_fmu[i]:e;
	}

	if(1){
		simStatus= DoInnerStep(fc,0,currentCommPoint,commStepSize);
	}

	memset(fi->in_condition_executed, 0, sizeof(fmi2Boolean)*_NR_OF_IN_CONDITIONS);
	return simStatus;
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
	FMUInstance * comp = (FMUInstance*) fc;
	printf("Function fmiSetInteger not supported\n");
	memset(comp->out_conditions_executed,0,sizeof(fmi2Boolean)*_NR_OF_OUT_CONDITIONS);
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
	fi->prev_disp = orig->prev_disp;

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
	fi->prev_disp = orig->prev_disp;

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
