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
#define POWERSYSTEM_FMU_PATH "fmu20\\fmu\\cs\\PW_PowerSystem.fmu"
#define WINDOW_FMU_PATH "fmu20\\fmu\\cs\\PW_Window.fmu"

int main(int argc, char *argv[]) {
    int i;
	
	// The fmus to be loaded and simulated.
	FMU Obstacle; 
	FMU PW_PowerSystem; 
	FMU PW_Window; 
	
    // parse command line arguments and load the FMU
    // default arguments value
    double tEnd = 1.0;
    double h=0.1;
    int loggingOn = 1;
    char csv_separator = ',';
    char **categories = NULL;
    int nCategories = 0;
	
	printf("Loading FMUs...\n");
	
	// TODO: The fmus need to be loaded onto separate directories.
    loadFMU(OBSTACLE_FMU_PATH, &Obstacle);
	loadFMU(POWERSYSTEM_FMU_PATH, &PW_PowerSystem);
	loadFMU(WINDOW_FMU_PATH, &PW_Window);
	
	printf("FMUs loaded.\n");
	
    return EXIT_SUCCESS;
}
