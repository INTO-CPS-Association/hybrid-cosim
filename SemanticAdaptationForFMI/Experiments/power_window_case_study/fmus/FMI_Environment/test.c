#include <stdio.h>
#include <stdlib.h>
#include "fmi2.h"
#include "sim_support.h"

#define START_TIME 0.0
#define STOP_TIME 6.0
#define STEP_SIZE 0.01

FMU fmu_env;

int main(void) {

	puts("Loading Dlls\n");
	/* loading */
    loadDll("libFMI_Environment.dll", &fmu_env, "PW_ENV_");

    puts("instantiating fmus\n");
    fmi2Component c_env;

    char *fmuResourceLocation_env = "libFMI_Environment.dll";

    fmi2CallbackFunctions callbacks_env= {fmuLogger, calloc, free, NULL, &fmu_env};

    c_env = fmu_env.instantiate("env", fmi2CoSimulation, "1", fmuResourceLocation_env, &callbacks_env, fmi2False, fmi2False);

    fmi2Boolean toleranceDefined = fmi2False;  // true if model description define tolerance
    fmi2Real tolerance = 0;                    // used in setting up the experiment

    puts("FMU component instantiated, setting up experiments\n");
    fmi2Status fmi2Flag[4];
    fmi2Flag[0] = fmu_env.setupExperiment(c_env, toleranceDefined, tolerance, START_TIME, fmi2True, STOP_TIME);
    if (fmi2Flag[0] == fmi2Error){
    	return -1;
    }

    puts("Experiment setup, entering init mode\n");
    fmi2Flag[0] = fmu_env.enterInitializationMode(c_env);
    if (fmi2Flag[0] == fmi2Error){
    	return -1;
    }

    puts("Experiment setup, exiting init mode\n");
    fmi2Flag[0] = fmu_env.exitInitializationMode(c_env);
    if (fmi2Flag[0] == fmi2Error){
    	return -1;
    }

    fmi2ValueReference vr_out_env[9]={0,1,2,3,4,5,6,7,8};
    fmi2Boolean b_out_env[9];

    double currentTime = START_TIME;

    while(currentTime <= STOP_TIME){
    	printf("\n----master new loop, ct:%f, h:%f\n",currentTime,STEP_SIZE);

    	/* do step*/
    	fflush(stdout);
    	fmi2Flag[0] = fmu_env.doStep(c_env, currentTime, STEP_SIZE, fmi2True);
    	if (fmu_env.getBoolean(c_env, vr_out_env, 9, &b_out_env[0]) != fmi2OK){
    		return 1;
    	}

    	printf("%f,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
    			currentTime,
				b_out_env[0],
				b_out_env[1],
				b_out_env[2],
				b_out_env[3],
				b_out_env[4],
				b_out_env[5],
				b_out_env[6],
				b_out_env[7],
				b_out_env[8]);

    	currentTime += STEP_SIZE;

    	fflush(stdout);

    }
	return EXIT_SUCCESS;
}
