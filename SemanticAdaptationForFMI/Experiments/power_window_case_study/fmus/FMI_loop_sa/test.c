#include <stdio.h>
#include <stdlib.h>
#include "fmi2.h"
#include "sim_support.h"

#define START_TIME 0.0
#define STOP_TIME 6.0
#define STEP_SIZE 0.01

FMU fmu_loop_sa;

int main(void) {

	puts("Loading Dlls\n");
	/* loading */
    loadDll("libFMI_loop_sa.dll", &fmu_loop_sa, "LOOP_SA");

    puts("instantiating fmus\n");
    fmi2Component c_loop_sa;

    char *fmuResourceLocation_window_sa = "libFMI_loop_sa.dll";

    fmi2CallbackFunctions callbacks_loop_sa = {fmuLogger, calloc, free, NULL, &fmu_loop_sa};

    c_loop_sa = fmu_loop_sa.instantiate("loop_sa",fmi2CoSimulation, "1", fmuResourceLocation_window_sa, &callbacks_loop_sa, fmi2False, fmi2False );

    fmi2Boolean toleranceDefined = fmi2True;  // true if model description define tolerance
    fmi2Real tolerance = 1e-1;                    // used in setting up the experiment

    puts("FMU components instantiated, setting up experiments\n");
    fmi2Status fmi2Flag;

    fmi2Flag = fmu_loop_sa.setupExperiment(c_loop_sa, toleranceDefined, tolerance, START_TIME, fmi2True, STOP_TIME);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    puts("Experiment setup, entering init mode\n");

    fmi2Flag = fmu_loop_sa.enterInitializationMode(c_loop_sa);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    puts("Experiment setup, exiting init mode\n");

    fmi2Flag = fmu_loop_sa.exitInitializationMode(c_loop_sa);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    fmi2ValueReference vr_out_loop_sa[1] = {0};
    fmi2Real r_out_loop_sa[1];
    fmi2ValueReference vr_toLoop[2] = {1,2}; // speed, displacement
	fmi2Real toLoop[2];

    double currentTime = START_TIME;

    while(currentTime <= STOP_TIME){
    	printf("\n----master new loop, ct:%f, h:%f\n",currentTime,STEP_SIZE);

    	toLoop[0] = 1.0f;
    	toLoop[1] = currentTime;

    	if (fmu_loop_sa.setReal(c_loop_sa, vr_toLoop, 2, &toLoop[0]) != fmi2OK){
    		return 1;
		}
    	fmi2Flag = fmu_loop_sa.doStep(c_loop_sa, currentTime, STEP_SIZE, fmi2True);
    	fflush(stdout);
    	if (fmu_loop_sa.getReal(c_loop_sa, vr_out_loop_sa, 1, &r_out_loop_sa[0]) != fmi2OK){
    		return 1;
		}

    	printf("%f,%f\n",
						currentTime,
						r_out_loop_sa[0]
						);

    	currentTime += STEP_SIZE;

    	fflush(stdout);

    }
	return EXIT_SUCCESS;
}
