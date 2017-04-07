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

#define _out_driver_up 0
#define _out_driver_up_stop 1
#define _out_driver_down 2
#define _out_driver_down_stop 3
#define _out_passenger_up 4
#define _out_passenger_up_stop 5
#define _out_passenger_down 6
#define _out_passenger_down_stop 7
#define _out_object 8

#define START_TIME 0.0
#define STOP_TIME 9.0
#define STEP_SIZE 0.01

FMU fmu_control;

int main(void) {
	puts("Loading Dlls\n");
	/* loading */
    loadDll("libFMI_controller.dll", &fmu_control, "PW_Controller");

    puts("instantiating fmus\n");
    fmi2Component c_control;

    char *fmuResourceLocation_control = "libFMI_controller.dll";

    fmi2CallbackFunctions callbacks_control = {fmuLogger, calloc, free, NULL, &fmu_control};

    c_control = fmu_control.instantiate("control", fmi2CoSimulation, "1", fmuResourceLocation_control, &callbacks_control, fmi2False, fmi2False);

    fmi2Boolean toleranceDefined = fmi2False;  // true if model description define tolerance
    fmi2Real tolerance = 0;                    // used in setting up the experiment

    puts("FMU components instantiated, setting up experiments\n");
    fmi2Status fmi2Flag;
    fmi2Flag = fmu_control.setupExperiment(c_control, toleranceDefined, tolerance, START_TIME, fmi2True, STOP_TIME);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    puts("Experiment setup, entering init mode\n");
    fmi2Flag = fmu_control.enterInitializationMode(c_control);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    fmi2Flag = fmu_control.exitInitializationMode(c_control);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    fmi2ValueReference vr_in_control_sa_from_env[8]={0,1,2,3,4,5,6,7};
    fmi2Boolean b_out_env[9];
    fmi2ValueReference vr_in_control_sa_from_power[1] = {0};
    fmi2Real in_control_sa_from_power[1] = {0.0f};
    fmi2ValueReference vr_out_control_sa[2]={9,10};
    fmi2Boolean b_out_control_sa[2];

    double currentTime = START_TIME;

    while(currentTime <= STOP_TIME){
    	printf("\n----master new loop, ct:%f, h:%f\n",currentTime,STEP_SIZE);

    	if(currentTime < 0.01){
			b_out_env[_out_driver_up] = 0;
			b_out_env[_out_driver_up_stop] = 0;
			b_out_env[_out_driver_down] = 0;
			b_out_env[_out_driver_down_stop] = 0;
			b_out_env[_out_passenger_up] = 0;
			b_out_env[_out_passenger_up_stop] = 0;
			b_out_env[_out_passenger_down] = 0;
			b_out_env[_out_passenger_down_stop] = 0;
			b_out_env[_out_object] = 0;
		}else if(currentTime < 4.59){
			b_out_env[_out_driver_up] = 1;
			b_out_env[_out_driver_up_stop] = 0;
			b_out_env[_out_driver_down] = 0;
			b_out_env[_out_driver_down_stop] = 0;
			b_out_env[_out_passenger_up] = 0;
			b_out_env[_out_passenger_up_stop] = 0;
			b_out_env[_out_passenger_down] = 0;
			b_out_env[_out_passenger_down_stop] = 0;
			b_out_env[_out_object] = 0;
		}else if(currentTime < 5){
			b_out_env[_out_driver_up] = 0;
			b_out_env[_out_driver_up_stop] = 1;
			b_out_env[_out_driver_down] = 0;
			b_out_env[_out_driver_down_stop] = 0;
			b_out_env[_out_passenger_up] = 0;
			b_out_env[_out_passenger_up_stop] = 0;
			b_out_env[_out_passenger_down] = 0;
			b_out_env[_out_passenger_down_stop] = 0;
			b_out_env[_out_object] = 0;
		}else if(currentTime < 5.01){
			b_out_env[_out_driver_up] = 0;
			b_out_env[_out_driver_up_stop] = 0;
			b_out_env[_out_driver_down] = 0;
			b_out_env[_out_driver_down_stop] = 0;
			b_out_env[_out_passenger_up] = 0;
			b_out_env[_out_passenger_up_stop] = 0;
			b_out_env[_out_passenger_down] = 0;
			b_out_env[_out_passenger_down_stop] = 0;
			b_out_env[_out_object] = 0;
		}else if(currentTime < 6.7){
			b_out_env[_out_driver_up] = 0;
			b_out_env[_out_driver_up_stop] = 0;
			b_out_env[_out_driver_down] = 0;
			b_out_env[_out_driver_down_stop] = 0;
			b_out_env[_out_passenger_up] = 0;
			b_out_env[_out_passenger_up_stop] = 0;
			b_out_env[_out_passenger_down] = 0;
			b_out_env[_out_passenger_down_stop] = 0;
			b_out_env[_out_object] = 0;
		}else if(currentTime < 7.1){
			b_out_env[_out_driver_up] = 0;
			b_out_env[_out_driver_up_stop] = 0;
			b_out_env[_out_driver_down] = 1;
			b_out_env[_out_driver_down_stop] = 0;
			b_out_env[_out_passenger_up] = 0;
			b_out_env[_out_passenger_up_stop] = 0;
			b_out_env[_out_passenger_down] = 0;
			b_out_env[_out_passenger_down_stop] = 0;
			b_out_env[_out_object] = 0;
		}else if(currentTime < 8.5){
			b_out_env[_out_driver_up] = 0;
			b_out_env[_out_driver_up_stop] = 0;
			b_out_env[_out_driver_down] = 0;
			b_out_env[_out_driver_down_stop] = 0;
			b_out_env[_out_passenger_up] = 0;
			b_out_env[_out_passenger_up_stop] = 0;
			b_out_env[_out_passenger_down] = 0;
			b_out_env[_out_passenger_down_stop] = 0;
			b_out_env[_out_object] = 0;
		}

    	/* do step*/
    	fmi2Flag = fmu_control.setBoolean(c_control,vr_in_control_sa_from_env,8,&b_out_env[0]);
    	if(fmi2Flag != fmi2OK){
    		return 1;
    	}
    	fmi2Flag = fmu_control.setReal(c_control,vr_in_control_sa_from_power,1, &in_control_sa_from_power[0]);
    	if(fmi2Flag != fmi2OK){
    		return 1;
    	}
    	fflush(stdout);
    	fmi2Flag = fmu_control.doStep(c_control, currentTime, STEP_SIZE, fmi2True);

    	if (fmu_control.getBoolean(c_control, vr_out_control_sa, 2, &b_out_control_sa[0]) != fmi2OK){
    		return 1;
		}

    	if(fmi2Flag == fmi2Discard){
    		printf("Controller simulated partially!\n");
    		fmi2Real stepTaken = STEP_SIZE;
			fmi2Real simulatedTime = currentTime + STEP_SIZE;
			for(int i=0; i<1; i++){
				fmi2Real theFMUtime;
				fmu_control.getRealStatus(c_control, fmi2LastSuccessfulTime, &theFMUtime);
				stepTaken = simulatedTime - theFMUtime;
				simulatedTime = theFMUtime;
			}
			currentTime = simulatedTime;
			printf("Step taken %f instead of requested %f\n", stepTaken, STEP_SIZE);
			fflush(stdout);
		} else {
			currentTime += STEP_SIZE;
		}

    	printf("%f,%d,%d\n",
    			currentTime,
				b_out_control_sa[0],
				b_out_control_sa[1]);
    	fflush(stdout);
    }
	return EXIT_SUCCESS;
}
