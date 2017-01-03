/* -------------------------------------------------------------------------
 * Author: Claudio Gomes (claudio.gomes@uantwerp.be)
 * -------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fmi2.h"
#include "sim_support.h"

// The paths to the FMUs to be simulated.
#define OBSTACLE_FMU_PATH "fmu20\\fmu\\cs\\Obstacle.fmu"
#define OBSTACLE_TARGET_DIR "obstacle\\"
#define OBSTACLE_RESULTS "obstacle_results.csv"
#define POWERSYSTEM_FMU_PATH "fmu20\\fmu\\cs\\PW_PowerSystem.fmu"
#define POWERSYSTEM_TARGET_DIR "power_system\\"
#define POWERSYSTEM_RESULTS "power_system_results.csv"
#define WINDOW_FMU_PATH "fmu20\\fmu\\cs\\PW_Window.fmu"
#define WINDOW_TARGET_DIR "window\\"
#define WINDOW_RESULTS "window_results.csv"

#define MSD_FMU_PATH "fmu20\\fmu\\cs\\mass_spring_damper.fmu"
#define MSD_TARGET_DIR "mass_spring_damper\\"
#define MSD_RESULTS "mass_spring_damper_results.csv"

static int instantiateFMU(fmi2Component* c, FMU* fmu, const char* fmuTargetDir, fmi2Boolean loggingOn, const fmi2CallbackFunctions* callbacks){
	const fmi2Boolean visible = fmi2False;
	
	printf("Instantiating fmu...\n");
	const char *guid = getAttributeValue((Element *)fmu->modelDescription, att_guid);
	printf("guid = %s\n", guid);
	const char *instanceName = getAttributeValue((Element *)getCoSimulation(fmu->modelDescription), att_modelIdentifier);
	printf("instanceName = %s\n", instanceName);
	char *fmuResourceDir = getTempResourcesLocation(fmuTargetDir);
	printf("fmuResourceDir = %s\n", fmuResourceDir);
	*c = fmu->instantiate(instanceName, fmi2CoSimulation, guid, fmuResourceDir,
                    callbacks, visible, loggingOn);
	free(fmuResourceDir);
	
	if (!c)
		return error("Could not instantiate fmu.");
	
	printf("Fmu instantiated\n");
	
	return 1; // success
}

static fmi2Status setupExperimentFMU(fmi2Component c, FMU* fmu, double start_time, double tEnd){
	fmi2Boolean toleranceDefined = fmi2False; // Default value: false
	fmi2Real tolerance;
	ValueStatus xmlParserValueState;
	Element * defaultExp;
	
	defaultExp = getDefaultExperiment(fmu->modelDescription);
    if (defaultExp)
		tolerance = getAttributeDouble(defaultExp, att_tolerance, &xmlParserValueState);
    if (xmlParserValueState == valueDefined) {
        toleranceDefined = fmi2True;
    }
	
	return fmu->setupExperiment(c, toleranceDefined, tolerance, start_time, fmi2True, tEnd);
}

static int simulate(FMU* MSD, FMU* Obstacle, FMU* PW_PowerSystem, FMU* PW_Window, double tEnd, double H, fmi2Boolean loggingOn, char separator) {
	// co simulation time vars
	double time;
    double start_time = 0;
	int cosim_step_counter;
	
	// aux vars for intermediate results
	fmi2Status returnCodeFmiFunctions;	
	
	// FMU results file
    FILE* obstacle_results;
    FILE* power_results;
    FILE* window_results;
    FILE* msd_results;
	
	// FMU instance data
	fmi2Component obstacle_instance;
	const fmi2CallbackFunctions obstacle_callbacks = {fmuLogger, calloc, free, NULL, Obstacle};
	fmi2Component power_instance;
	const fmi2CallbackFunctions power_callbacks = {fmuLogger, calloc, free, NULL, PW_PowerSystem};
	fmi2Component window_instance;
	const fmi2CallbackFunctions window_callbacks = {fmuLogger, calloc, free, NULL, PW_Window};
	fmi2Component msd_instance;
	const fmi2CallbackFunctions msd_callbacks = {fmuLogger, calloc, free, NULL, MSD};
	
	// Instantiate FMUS
	printf("Instantiating obstacle fmu...\n");
	instantiateFMU(&obstacle_instance, Obstacle, OBSTACLE_TARGET_DIR, loggingOn, &obstacle_callbacks);
	
	printf("Instantiating msd fmu...\n");
	instantiateFMU(&msd_instance, MSD, MSD_TARGET_DIR, loggingOn, &msd_callbacks);
	
	printf("Instantiating window fmu...\n");
	instantiateFMU(&window_instance, PW_Window, WINDOW_TARGET_DIR, loggingOn, &window_callbacks);
	
	printf("Instantiating power fmu...\n");
	instantiateFMU(&power_instance, PW_PowerSystem, POWERSYSTEM_TARGET_DIR, loggingOn, &power_callbacks);
	
	// Setup experiments
	
	printf("Setting up default experiment for obstacle_instance fmu...\n");
	returnCodeFmiFunctions = setupExperimentFMU(obstacle_instance, Obstacle, start_time, tEnd); 
    if (returnCodeFmiFunctions > fmi2Warning) {
        return error("Could not set up experiment for obstacle_instance fmu.");
    }
	
	printf("Setting up default experiment for msd_instance fmu...\n");
	returnCodeFmiFunctions = setupExperimentFMU(msd_instance, MSD, start_time, tEnd); 
    if (returnCodeFmiFunctions > fmi2Warning) {
        return error("Could not set up experiment for msd_instance fmu.");
    }
	
	printf("Setting up default experiment for window_instance fmu...\n");
	returnCodeFmiFunctions = setupExperimentFMU(window_instance, PW_Window, start_time, tEnd); 
    if (returnCodeFmiFunctions > fmi2Warning) {
		printf("Could not set up experiment for window_instance fmu.\n");
        return error("Could not set up experiment for window_instance fmu.");
    }
	
	printf("Setting up default experiment for power_instance fmu...\n");
	returnCodeFmiFunctions = setupExperimentFMU(power_instance, PW_PowerSystem, start_time, tEnd); 
    if (returnCodeFmiFunctions > fmi2Warning) {
        return error("Could not set up experiment for power_instance fmu.");
    }
	
	// Init FMUs
	
	printf("Entering initialization mode for obstacle_instance fmu...\n");
	returnCodeFmiFunctions = Obstacle->enterInitializationMode(obstacle_instance);
    if (returnCodeFmiFunctions > fmi2Warning) {
		printf("Could not enter initialization mode for obstacle_instance fmu.\n");
        return error("Could not enter initialization mode for obstacle_instance fmu");
    }
	
	printf("Entering initialization mode msd_instance fmu...\n");
	returnCodeFmiFunctions = MSD->enterInitializationMode(msd_instance);
    if (returnCodeFmiFunctions > fmi2Warning) {
		printf("Could not enter initialization msd_instance for power fmu.\n");
        return error("Could not enter initialization msd_instance for power fmu");
    }
	
	printf("Entering initialization mode for power_instance fmu...\n");
	returnCodeFmiFunctions = PW_PowerSystem->enterInitializationMode(power_instance);
	printf("Entering initialization mode for power_instance fmu... DONE\n");
    if (returnCodeFmiFunctions > fmi2Warning) {
        printf("Could not enter initialization mode for power_instance fmu.\n");
		return error("Could not enter initialization mode for power_instance fmu");
    }
	
	printf("Entering initialization mode window_instance fmu...\n");
	returnCodeFmiFunctions = PW_Window->enterInitializationMode(window_instance);
    if (returnCodeFmiFunctions > fmi2Warning) {
		printf("Could not enter initialization window_instance for power fmu.\n");
        return error("Could not enter initialization window_instance for power fmu");
    }
	
	
	
	// Finish Init FMUs
	
	printf("Exiting initialization mode for obstacle_instance fmu...\n");
	returnCodeFmiFunctions = Obstacle->exitInitializationMode(obstacle_instance);
    if (returnCodeFmiFunctions > fmi2Warning) {
		printf("Could not exit initialization mode for obstacle_instance fmu.\n");
        return error("Could not exit initialization mode for obstacle_instance fmu");
    }
	
	printf("Exiting initialization mode msd_instance fmu...\n");
	returnCodeFmiFunctions = MSD->exitInitializationMode(msd_instance);
    if (returnCodeFmiFunctions > fmi2Warning) {
        return error("Could not exit initialization msd_instance for power fmu");
    }
	
	printf("Exiting initialization mode window_instance fmu...\n");
	returnCodeFmiFunctions = PW_Window->exitInitializationMode(window_instance);
    if (returnCodeFmiFunctions > fmi2Warning) {
        return error("Could not exit initialization window_instance for power fmu");
    }
	
	printf("Exiting initialization mode for power_instance fmu...\n");
	returnCodeFmiFunctions = PW_PowerSystem->exitInitializationMode(power_instance);
    if (returnCodeFmiFunctions > fmi2Warning) {
        return error("Could not exit initialization mode for power_instance fmu");
    }
	
	// open result file
	printf("Creating results files...\n");
	
	if (!(obstacle_results = fopen(OBSTACLE_RESULTS, "w"))) {
        printf("could not write %s because:\n", OBSTACLE_RESULTS);
        printf("    %s\n", strerror(errno));
        return 0; // failure
    }
	if (!(msd_results = fopen(MSD_RESULTS, "w"))) {
        printf("could not write %s because:\n", MSD_RESULTS);
        printf("    %s\n", strerror(errno));
        return 0; // failure
    }
	if (!(window_results = fopen(WINDOW_RESULTS, "w"))) {
        printf("could not write %s because:\n", WINDOW_RESULTS);
        printf("    %s\n", strerror(errno));
        return 0; // failure
    }
	if (!(power_results = fopen(POWERSYSTEM_RESULTS, "w"))) {
        printf("could not write %s because:\n", POWERSYSTEM_RESULTS);
        printf("    %s\n", strerror(errno));
        return 0; // failure
    }
    
	// output solution for time t0
    printf("Writting headers...\n");
	outputRow(Obstacle, obstacle_instance, start_time, obstacle_results, separator, fmi2True);
    outputRow(MSD, msd_instance, start_time, msd_results, separator, fmi2True);
    outputRow(PW_PowerSystem, power_results, start_time, power_results, separator, fmi2True);
    outputRow(PW_Window, window_instance, start_time, window_results, separator, fmi2True);
	
	printf("Writting first row of obstacle_instance...\n");
	outputRow(Obstacle, obstacle_instance, start_time, obstacle_results, separator, fmi2False); // output values
	printf("Writting first row of msd_instance...\n");
    outputRow(MSD, msd_instance, start_time, msd_results, separator, fmi2False);
	printf("Writting first row of power_instance...\n");
	outputRow(PW_PowerSystem, power_instance, start_time, power_results, separator, fmi2False);
	printf("Writting first row of window_instance...\n");
    outputRow(PW_Window, window_instance, start_time, window_results, separator, fmi2False);
	
	// end simulation
    printf("Terminating FMUs...\n");
	Obstacle->terminate(obstacle_instance);
	MSD->terminate(msd_instance);
	PW_PowerSystem->terminate(power_results);
	PW_Window->terminate(window_instance);
	
	printf("Releasing FMUs...\n");
	Obstacle->freeInstance(obstacle_instance);
    MSD->freeInstance(msd_instance);
	PW_PowerSystem->freeInstance(power_results);
	PW_Window->freeInstance(window_instance);
    
	printf("Closing files...\n");
	fclose(obstacle_results);
    fclose(msd_results);
    fclose(power_results);
    fclose(window_results);
	
	printf("Simulation done.\n");
	
	return 1; // success
}

int main(int argc, char *argv[]) {
	// The fmus to be loaded and simulated.
	FMU Obstacle; 
	FMU PW_PowerSystem; 
	FMU PW_Window; 
	FMU MSD; 
	
	setbuf(stdout, NULL); // disable buffering on the stdout.
	
    double tEnd = 1.0;
    double H=0.1;
    fmi2Boolean loggingOn = fmi2True;
    char csv_separator = ',';
	
	printf("Attempting to delete previously unzipped temp files...\n");
    deleteUnzippedFiles();
	
	printf("Loading FMUs...\n");
	
	loadFMU(OBSTACLE_FMU_PATH, OBSTACLE_TARGET_DIR, &Obstacle);
	loadFMU(MSD_FMU_PATH, MSD_TARGET_DIR, &MSD);
	loadFMU(POWERSYSTEM_FMU_PATH, POWERSYSTEM_TARGET_DIR, &PW_PowerSystem);
	loadFMU(WINDOW_FMU_PATH, WINDOW_TARGET_DIR, &PW_Window);
	
	printf("Simulating FMUs...\n");
	
	simulate(&MSD,&Obstacle,&PW_PowerSystem, &PW_Window, tEnd, H, loggingOn, csv_separator);
	
	// release FMU
    
	printf("Releasing FMU dlls...\n");
	
	if (!FreeLibrary(Obstacle.dllHandle)){
		printf("Error unloading Obstacle.dllHandle.\n");
	}
    freeModelDescription(Obstacle.modelDescription);
	
	if (!FreeLibrary(MSD.dllHandle)){
		printf("Error unloading MSD.dllHandle.\n");
	}
	freeModelDescription(MSD.modelDescription);
	
	if (!FreeLibrary(PW_Window.dllHandle)){
		printf("Error unloading PW_Window.dllHandle.\n");
	}
    freeModelDescription(PW_Window.modelDescription);
	
	if (!FreeLibrary(PW_PowerSystem.dllHandle)){
		printf("Error unloading PW_PowerSystem.dllHandle.\n");
	}
    freeModelDescription(PW_PowerSystem.modelDescription);
    
	// delete temp files obtained by unzipping the FMU
    printf("Attempting to delete unzipped files...\n");
    deleteUnzippedFiles();
	
	printf("All done.\n");
	
    return EXIT_SUCCESS;
}
