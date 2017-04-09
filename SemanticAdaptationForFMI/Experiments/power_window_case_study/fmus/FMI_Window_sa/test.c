/*
 ============================================================================
 Name        : pw_case.c
 Author      : Joachim Denil
 Version     :
 Copyright   : Your copyright notice
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "fmi2.h"
#include "sim_support.h"

#define START_TIME 0.0
#define STOP_TIME 6.0
#define STEP_SIZE 0.01

FMU fmu_win;

int main(void) {

	puts("Loading Dlls\n");
	/* loading */
    loadDll("libFMI_Window_sa.dll", &fmu_win, "WINDOW_SA");

    puts("instantiating fmus\n");
    fmi2Component c_win;

    char *fmuResourceLocation_win = "libFMI_Window_sa.dll";

    fmi2CallbackFunctions callbacks_win= {fmuLogger, calloc, free, NULL, &fmu_win};

    fflush(stdout);

    c_win = fmu_win.instantiate("win", fmi2CoSimulation, "1", fmuResourceLocation_win, &callbacks_win, fmi2False, fmi2False);

    fmi2Boolean toleranceDefined = fmi2False;  // true if model description define tolerance
    fmi2Real tolerance = 0;                    // used in setting up the experiment

    puts("FMU components instantiated, setting up experiments\n");
    fmi2Status fmi2Flag;
    fmi2Flag = fmu_win.setupExperiment(c_win, toleranceDefined, tolerance, START_TIME, fmi2True, STOP_TIME);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    puts("Experiment setup, entering init mode\n");
    fmi2Flag = fmu_win.enterInitializationMode(c_win);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    puts("Experiment setup, exiting init mode\n");
    fmi2Flag = fmu_win.exitInitializationMode(c_win);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    fmi2ValueReference vr_in_window[3] = {2,3,4};
    fmi2Real r_in_window[3] = {0.0f, 0.0f, 1.0f}; // reaction force, displacement, speed

    fmi2ValueReference vr_out_window[2] = {0,1};
    fmi2Real r_out_window[2]; // tau, height

    double currentTime = START_TIME;

    while(currentTime <= STOP_TIME){
    	printf("\n----master new loop, ct:%f, h:%f\n",currentTime,STEP_SIZE);

    	fflush(stdout);

		if(fmu_win.setReal(c_win,vr_in_window,3, &r_in_window[0]) != fmi2OK){
					return 1;
		}

    	fmi2Flag = fmu_win.doStep(c_win, currentTime, STEP_SIZE, fmi2True);

    	if (fmu_win.getReal(c_win, vr_out_window, 2, &r_out_window[0]) != fmi2OK){
    		return 1;
    	}

    	printf("%f,%f,%f\n",
    			currentTime,
				r_out_window[0],
				r_out_window[1]);

    	currentTime += STEP_SIZE;

    	r_in_window[0] = 0.0f;
    	r_in_window[1] = currentTime;
    	r_in_window[2] = 1.0f;

    	fflush(stdout);

    }
	return EXIT_SUCCESS;
}
