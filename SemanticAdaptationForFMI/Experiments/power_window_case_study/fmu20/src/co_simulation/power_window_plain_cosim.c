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
#define POWERSYSTEM_FMU_PATH "fmu20\\fmu\\cs\\PW_PowerSystem.fmu"
#define POWERSYSTEM_TARGET_DIR "power_system\\"
#define WINDOW_FMU_PATH "fmu20\\fmu\\cs\\PW_Window.fmu"
#define WINDOW_TARGET_DIR "window\\"

static int instantiateFMU(fmi2Component* c, FMU* fmu, const char* fmuTargetDir, fmi2Boolean loggingOn, fmi2CallbackFunctions* callbacks){
	fmi2Boolean visible = fmi2False;
	char *guid;
    char *instanceName;
	char *fmuResourceDir;
	
	printf("Instantiating fmu...\n");
	guid = getAttributeValue((Element *)fmu->modelDescription, att_guid);
	printf("guid = %s\n", guid);
	instanceName = getAttributeValue((Element *)getCoSimulation(fmu->modelDescription), att_modelIdentifier);
	printf("instanceName = %s\n", instanceName);
	fmuResourceDir = getTempResourcesLocation(fmuTargetDir);
	printf("fmuResourceDir = %s\n", fmuResourceDir);
	*c = fmu->instantiate(instanceName, fmi2CoSimulation, guid, fmuResourceDir,
                    callbacks, visible, loggingOn);
	free(guid);
	free(instanceName);
	free(fmuResourceDir);
	
	if (!c) 
			return error("Could not instantiate fmu.");
	printf("Fmu instantiated\n");
	
	return 1; // success
}

static int simulate(FMU* Obstacle, FMU* PW_PowerSystem, FMU* PW_Window, double tEnd, double H, fmi2Boolean loggingOn, char separator) {
	
	// co simulation time vars
	double time;
    double start_time = 0;
	int cosim_step_counter;
	
	// aux vars for intermediate results
	fmi2Status returnCodeFmiFunctions;	
	fmi2Boolean toleranceDefined = fmi2False; // Default value: false
	fmi2Real tolerance;
	ValueStatus xmlParserValueState;
	Element *xmlParserElement;
    FILE* results_file;
	
	
	// FMU instance data
	fmi2Component obstacle_instance;
	fmi2CallbackFunctions obstacle_callbacks = {fmuLogger, calloc, free, NULL, Obstacle};
	fmi2Component power_instance;
	fmi2CallbackFunctions power_callbacks = {fmuLogger, calloc, free, NULL, PW_PowerSystem};
	fmi2Component window_instance;
	fmi2CallbackFunctions window_callbacks = {fmuLogger, calloc, free, NULL, PW_Window};
	
	// Instantiate FMUS
	printf("Instantiating obstacle fmu...\n");
	instantiateFMU(&obstacle_instance, Obstacle, OBSTACLE_TARGET_DIR, loggingOn, &obstacle_callbacks);
	
	printf("Instantiating power fmu...\n");
	instantiateFMU(&power_instance, PW_PowerSystem, POWERSYSTEM_TARGET_DIR, loggingOn, &power_callbacks);
	
	printf("Instantiating window fmu...\n");
	instantiateFMU(&window_instance, PW_Window, WINDOW_TARGET_DIR, loggingOn, &window_callbacks);
	
	return 1; // success
}

int main(int argc, char *argv[]) {
    int i;
	
	// The fmus to be loaded and simulated.
	FMU Obstacle; 
	FMU PW_PowerSystem; 
	FMU PW_Window; 
	
    // parse command line arguments and load the FMU
    // default arguments value
    double tEnd = 1.0;
    double H=0.1;
    fmi2Boolean loggingOn = fmi2True;
    char csv_separator = ',';
	
	printf("Loading FMUs...\n");
	
    loadFMU(OBSTACLE_FMU_PATH, OBSTACLE_TARGET_DIR, &Obstacle);
	loadFMU(POWERSYSTEM_FMU_PATH, POWERSYSTEM_TARGET_DIR, &PW_PowerSystem);
	loadFMU(WINDOW_FMU_PATH, WINDOW_TARGET_DIR, &PW_Window);
	
	printf("Simulating FMUs...\n");
	
	simulate(&Obstacle,&PW_PowerSystem, &PW_Window, tEnd, H, loggingOn, csv_separator);
	
	// release FMU
    printf("Releasing FMUs...\n");
	FreeLibrary(Obstacle.dllHandle);
    freeModelDescription(Obstacle.modelDescription);
	
	FreeLibrary(PW_PowerSystem.dllHandle);
    freeModelDescription(PW_PowerSystem.modelDescription);
	
	FreeLibrary(PW_Window.dllHandle);
    freeModelDescription(PW_Window.modelDescription);
	
    // delete temp files obtained by unzipping the FMU
    printf("Attempting to delete unzipped files...\n");
    deleteUnzippedFiles();
	
	printf("All done.\n");
	
    return EXIT_SUCCESS;
}
