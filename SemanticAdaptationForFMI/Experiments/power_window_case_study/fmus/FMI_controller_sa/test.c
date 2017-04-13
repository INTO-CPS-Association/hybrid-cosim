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
#define STOP_TIME 9.0
#define STEP_SIZE 0.1

#define _in_armature_current 0

#define _in_driver_up 0
#define _in_driver_up_stop 1
#define _in_driver_down 2
#define _in_driver_down_stop 3
#define _in_passenger_up 4
#define _in_passenger_up_stop 5
#define _in_passenger_down 6
#define _in_passenger_down_stop 7

#define _out_u 9
#define _out_d 10

FMU fmu_control_sa;

int main(void) {

	puts("FMI_controller_sa: Loading Dlls\n");
	/* loading */
    loadDll("libFMI_controller_sa.dll", &fmu_control_sa, "PW_CONTROLLER_SA_");

    puts("instantiating fmus\n");
    fmi2Component  c_control_sa;

    char *fmuResourceLocation_control_sa = "libFMI_controller_sa.dll";

    fmi2CallbackFunctions callbacks_control_sa = {fmuLogger, calloc, free, NULL, &fmu_control_sa};

    c_control_sa = fmu_control_sa.instantiate("control_sa", fmi2CoSimulation, "1", fmuResourceLocation_control_sa, &callbacks_control_sa, fmi2False, fmi2False);

    fmi2Boolean toleranceDefined = fmi2True;  // Enables zero crossing location
    fmi2Real tolerance = 0;                    // used in setting up the experiment

    puts("FMU components instantiated, setting up experiments\n");
    fmi2Status fmi2Flag;
    fmi2Flag = fmu_control_sa.setupExperiment(c_control_sa, toleranceDefined, tolerance, START_TIME, fmi2True, STOP_TIME);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    puts("Experiment setup, entering init mode\n");
    fmi2Flag = fmu_control_sa.enterInitializationMode(c_control_sa);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    puts("Experiment setup, exiting init mode\n");
    fmi2Flag = fmu_control_sa.exitInitializationMode(c_control_sa);
    if (fmi2Flag == fmi2Error){
    	return -1;
    }

    fmi2ValueReference vr_in_control_sa_from_env[8]={0,1,2,3,4,5,6,7};
    fmi2Boolean b_out_env[9];
    fmi2ValueReference vr_out_control_sa[2]={9,10};
    fmi2Boolean b_out_control_sa[2];
    fmi2ValueReference vr_in_control_sa_from_window[1] = {0};
    fmi2Real r_out_power[3];

    double currentTime = START_TIME;
	double next_step_size = STEP_SIZE;

    while(currentTime <= STOP_TIME){
    	printf("\n----master new loop, ct:%f, h:%f\n",currentTime,next_step_size);

		fmi2Component ctemp_control_sa;

		fmu_control_sa.getFMUstate(c_control_sa, &ctemp_control_sa);

    	if(currentTime < 0.01){
    		r_out_power[_in_armature_current] = 0.0f;
			b_out_env[_in_driver_up] = 0;
			b_out_env[_in_driver_up_stop] = 0;
			b_out_env[_in_driver_down] = 0;
			b_out_env[_in_driver_down_stop] = 0;
			b_out_env[_in_passenger_up] = 0;
			b_out_env[_in_passenger_up_stop] = 0;
			b_out_env[_in_passenger_down] = 0;
			b_out_env[_in_passenger_down_stop] = 0;
		}else if(currentTime < 4){
    		r_out_power[_in_armature_current] = 1.44*(currentTime + next_step_size); // crossing occurs at 3.47...
			b_out_env[_in_driver_up] = 1;
			b_out_env[_in_driver_up_stop] = 0;
			b_out_env[_in_driver_down] = 0;
			b_out_env[_in_driver_down_stop] = 0;
			b_out_env[_in_passenger_up] = 0;
			b_out_env[_in_passenger_up_stop] = 0;
			b_out_env[_in_passenger_down] = 0;
			b_out_env[_in_passenger_down_stop] = 0;
		} else {
			r_out_power[_in_armature_current] = 1.44*3.47 - (currentTime + next_step_size - 3.47);
			b_out_env[_in_driver_up] = 1;
			b_out_env[_in_driver_up_stop] = 0;
			b_out_env[_in_driver_down] = 0;
			b_out_env[_in_driver_down_stop] = 0;
			b_out_env[_in_passenger_up] = 0;
			b_out_env[_in_passenger_up_stop] = 0;
			b_out_env[_in_passenger_down] = 0;
			b_out_env[_in_passenger_down_stop] = 0;
		}

    	fmi2Flag = fmu_control_sa.setBoolean(c_control_sa,vr_in_control_sa_from_env,8,&b_out_env[0]);
    	if(fmi2Flag != fmi2OK){
    		printf("Failed setBoolean\n");
			fflush(stdout);
    		return 1;
    	}
    	fmi2Flag = fmu_control_sa.setReal(c_control_sa,vr_in_control_sa_from_window,1, &r_out_power[0]);
    	if(fmi2Flag != fmi2OK){
    		printf("Failed setReal\n");
    		fflush(stdout);
    	    return 1;
    	}
    	fmi2Flag = fmu_control_sa.doStep(c_control_sa, currentTime, next_step_size, fmi2True);

    	if (fmu_control_sa.getBoolean(c_control_sa, vr_out_control_sa, 2, &b_out_control_sa[0]) != fmi2OK){
    		printf("Failed getBoolean\n");
    		fflush(stdout);
			return 1;
		}

		printf("%f,%d,%d\n",
				currentTime,
				b_out_control_sa[0],
				b_out_control_sa[1]);

    	if (fmi2Flag == fmi2Discard){
    		printf("Discard occurred!\n");

			fmi2Real newtime;

			fmu_control_sa.getRealStatus(c_control_sa, fmi2LastSuccessfulTime, &newtime);
			fmi2Real the_FMU_new_step = newtime - currentTime;
			if(the_FMU_new_step < next_step_size){
				printf("Control_sa simulated partially with a step size of %f!\n", the_FMU_new_step);
				next_step_size = the_FMU_new_step;

				printf("Rolling back Control_sa...\n");
				fmu_control_sa.setFMUstate(c_control_sa, ctemp_control_sa);
			}
		} else {
			printf("Step accepted, advancing time and adjusting next step size...\n");
			currentTime += next_step_size;
			next_step_size = STEP_SIZE;
		}

    	fflush(stdout);

    }
	return EXIT_SUCCESS;
}
