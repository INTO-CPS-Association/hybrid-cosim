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
#define STEP_SIZE 0.001

FMU fmu_power_sa;

int main(void) {

	puts("Loading Dlls\n");
	/* loading */
    loadDll("libFMI_power_sa.dll", &fmu_power_sa, "POWER_SA_");

    puts("instantiating fmus\n");
    fmi2Component c_power_sa;

    char *fmuResourceLocation_power_sa = "libFMI_power_sa.dll";

    fmi2CallbackFunctions callbacks_power_sa = {fmuLogger, calloc, free, NULL, &fmu_power_sa};

    c_power_sa = fmu_power_sa.instantiate("power_sa", fmi2CoSimulation, "1", fmuResourceLocation_power_sa, &callbacks_power_sa, fmi2False, fmi2False);

    fmi2Boolean toleranceDefined = fmi2False;  // true if model description define tolerance
    fmi2Real tolerance = 0;                    // used in setting up the experiment

    fmi2Status fmi2Flag;

    fmi2Flag = fmu_power_sa.setupExperiment(c_power_sa, toleranceDefined, tolerance, START_TIME, fmi2True, STOP_TIME);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    puts("Experiment setup, entering init mode\n");
    fmi2Flag = fmu_power_sa.enterInitializationMode(c_power_sa);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }
    fmi2Flag = fmu_power_sa.exitInitializationMode(c_power_sa);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    fmi2ValueReference vr_in_power_sa_u_d[2] = {3,5};
    fmi2ValueReference vr_in_power_sa_tau[1] = {4};
    fmi2Real r_in_power_from_control[2] = {0.0f,1.0f}; //down, up
    fmi2Real r_in_power_from_loop[1]={0.0f}; // tau
    fmi2ValueReference vr_out_power_sa[3] = {0,1,2};
    fmi2Real r_out_power[3];

    double currentTime = START_TIME;

    while(currentTime <= STOP_TIME){
    	printf("\n----master new loop, ct:%f, h:%f\n",currentTime,STEP_SIZE);

    	fmi2Flag = fmu_power_sa.setReal(c_power_sa,vr_in_power_sa_u_d,2, &r_in_power_from_control[0]);
    	if(fmi2Flag != fmi2OK){
    		return 1;
    	}
    	fmi2Flag = fmu_power_sa.setReal(c_power_sa,vr_in_power_sa_tau,1, &r_in_power_from_loop[0]);
    	if(fmi2Flag != fmi2OK){
    		return 1;
    	}

    	fmi2Flag = fmu_power_sa.doStep(c_power_sa, currentTime, STEP_SIZE, fmi2True);

    	if (fmu_power_sa.getReal(c_power_sa, vr_out_power_sa, 3, &r_out_power[0]) != fmi2OK){
    		return 1;
    	}
    	fflush(stdout);

    	r_in_power_from_control[0] = 0.0f;
    	r_in_power_from_control[1] = 1.0f;
    	fflush(stdout);
    	printf("%f,%f,%f,%f\n",
    	    			currentTime,
    					r_out_power[0],
    					r_out_power[1],
						r_out_power[2]);

    	r_in_power_from_loop[0] = 0.0f;

    	currentTime += STEP_SIZE;

    	fflush(stdout);

    }
	return EXIT_SUCCESS;
}
