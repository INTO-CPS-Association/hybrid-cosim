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
#define STOP_TIME 4.5
#define STEP_SIZE 0.00001

FMU fmu_env, fmu_control_sa, fmu_power_sa, fmu_loop_sa;

int main(void) {
	FILE *fp_fmu_env;
	fp_fmu_env = fopen("result_ENV.csv", "w");
	FILE *fp_fmu_control_sa;
	fp_fmu_control_sa = fopen("result_Control_sa.csv", "w");
	FILE *fp_fmu_power_sa;
	fp_fmu_power_sa = fopen("result_power_sa.csv","w");
	FILE *fp_fmu_loop_sa;
	fp_fmu_loop_sa = fopen("result_loop_sa.csv", "w");

	fprintf(fp_fmu_env,"t,dup,dup_stop,ddown,ddown_stop,pup,pup_stop,pdown,pdown_stop,obj\n");
	fprintf(fp_fmu_control_sa,"t,u,d\n");
	fprintf(fp_fmu_power_sa,"t,i,omega,theta\n");
	fprintf(fp_fmu_loop_sa,"t,tau,height\n");

	puts("Loading Dlls\n");

    loadDll("libFMI_Environment.dll", &fmu_env, "PW_ENV_");
    fflush(stdout);
    loadDll("libFMI_controller_sa.dll", &fmu_control_sa, "PW_CONTROLLER_SA_");
    fflush(stdout);
    loadDll("libFMI_power_sa.dll", &fmu_power_sa, "POWER_SA_");
    fflush(stdout);
    loadDll("libFMI_loop_sa.dll", &fmu_loop_sa, "LOOP_SA_");
    fflush(stdout);

    puts("instantiating fmus\n");
    fmi2Component c_env, c_control_sa, c_power_sa, c_loop_sa;

    char *fmuResourceLocation_env = "libFMI_Environment.dll";
    char *fmuResourceLocation_control_sa = "libFMI_controller_sa.dll";
    char *fmuResourceLocation_power_sa = "libFMI_power_sa.dll";
    char *fmuResourceLocation_loop_sa = "libFMI_loop_sa.dll";

    fmi2CallbackFunctions callbacks_env= {fmuLogger, calloc, free, NULL, &fmu_env};
    fmi2CallbackFunctions callbacks_control_sa = {fmuLogger, calloc, free, NULL, &fmu_control_sa};
    fmi2CallbackFunctions callbacks_power_sa = {fmuLogger, calloc, free, NULL, &fmu_power_sa};
    fmi2CallbackFunctions callbacks_loop_sa = {fmuLogger, calloc, free, NULL, &fmu_loop_sa};

    c_env = fmu_env.instantiate("env", fmi2CoSimulation, "1", fmuResourceLocation_env, &callbacks_env, fmi2False, fmi2False);
    c_control_sa = fmu_control_sa.instantiate("control_sa", fmi2CoSimulation, "1", fmuResourceLocation_control_sa, &callbacks_control_sa, fmi2False, fmi2False);
    c_power_sa = fmu_power_sa.instantiate("power_sa", fmi2CoSimulation, "1", fmuResourceLocation_power_sa, &callbacks_power_sa, fmi2False, fmi2False);
    c_loop_sa = fmu_loop_sa.instantiate("loop_sa",fmi2CoSimulation, "1", fmuResourceLocation_loop_sa, &callbacks_loop_sa, fmi2False, fmi2False );

    fmi2Boolean toleranceDefined = fmi2False;  // Disables accurate zero crossing
    fmi2Real tolerance = 0;                    // used in setting up the experiment

    puts("FMU components instantiated, setting up experiments\n");
    fmi2Status auxFlag;
    auxFlag = fmu_env.setupExperiment(c_env, toleranceDefined, tolerance, START_TIME, fmi2True, STOP_TIME);
    if (auxFlag == fmi2Error){
    	printf("Failed setupExperiment\n");
		fflush(stdout);
		return -1;
    }
    auxFlag = fmu_control_sa.setupExperiment(c_control_sa, toleranceDefined, tolerance, START_TIME, fmi2True, STOP_TIME);
    if (auxFlag == fmi2Error){
    	printf("Failed setupExperiment\n");
		fflush(stdout);
		return -1;
    }
    auxFlag = fmu_power_sa.setupExperiment(c_power_sa, toleranceDefined, tolerance, START_TIME, fmi2True, STOP_TIME);
    if (auxFlag == fmi2Error){
    	printf("Failed setupExperiment\n");
		fflush(stdout);
		return -1;
    }
    auxFlag = fmu_loop_sa.setupExperiment(c_loop_sa, toleranceDefined, tolerance, START_TIME, fmi2True, STOP_TIME);
    if (auxFlag == fmi2Error){
    	printf("Failed setupExperiment\n");
		fflush(stdout);
		return -1;
    }

    puts("Experiment setup, entering init mode\n");

    auxFlag = fmu_env.enterInitializationMode(c_env);
    if (auxFlag == fmi2Error){
    	printf("Failed enterInitializationMode\n");
		fflush(stdout);
		return -1;
    }
    auxFlag = fmu_control_sa.enterInitializationMode(c_control_sa);
    if (auxFlag == fmi2Error){
    	printf("Failed enterInitializationMode\n");
		fflush(stdout);
		return -1;
    }
    auxFlag = fmu_power_sa.enterInitializationMode(c_power_sa);
    if (auxFlag == fmi2Error){
    	printf("Failed enterInitializationMode\n");
		fflush(stdout);
		return -1;
    }
    auxFlag = fmu_loop_sa.enterInitializationMode(c_loop_sa);
    if (auxFlag == fmi2Error){
    	printf("Failed enterInitializationMode\n");
		fflush(stdout);
		return -1;
    }

    puts("Experiment setup, exiting init mode\n");
    auxFlag = fmu_env.exitInitializationMode(c_env);
    if (auxFlag == fmi2Error){
    	printf("Failed exitInitializationMode\n");
		fflush(stdout);
		return -1;
    }
    auxFlag = fmu_control_sa.exitInitializationMode(c_control_sa);
    if (auxFlag == fmi2Error){
    	printf("Failed exitInitializationMode\n");
		fflush(stdout);
		return -1;
    }
    auxFlag = fmu_power_sa.exitInitializationMode(c_power_sa);
    if (auxFlag == fmi2Error){
    	printf("Failed exitInitializationMode\n");
		fflush(stdout);
		return -1;
    }
    auxFlag = fmu_loop_sa.exitInitializationMode(c_loop_sa);
    if (auxFlag == fmi2Error){
    	printf("Failed exitInitializationMode\n");
		fflush(stdout);
		return -1;
    }

    fmi2ValueReference vr_out_env[9]={0,1,2,3,4,5,6,7,8};
    fmi2Boolean b_out_env[9];
    fmi2ValueReference vr_in_control_sa_from_env[8]={0,1,2,3,4,5,6,7};
    fmi2ValueReference vr_in_control_sa_from_power[1] = {0};
    fmi2ValueReference vr_out_control_sa[2]={9,10};
    fmi2ValueReference vr_in_power_sa_u_d[2] = {5,3};
    fmi2ValueReference vr_in_power_sa_tau[1] = {4};
    fmi2ValueReference vr_out_loop_sa[2] = {0,3}; // tau, height
    fmi2ValueReference vr_out_power_sa[3] = {0,1,2};
    fmi2Real r_in_power_from_control[2] = {0,0};
    fmi2Real r_in_power_from_loop[1]={0};
    fmi2Real r_out_power[3];
    fmi2Real r_out_loop_sa[2];

    fmi2Boolean b_out_control_sa[2];
    double currentTime = START_TIME;
    //const fmi2StatusKind lst = fmi2LastSuccessfulTime;

    while(currentTime <= STOP_TIME){
    	printf("\n----master new loop, ct:%f, h:%f\n",currentTime,STEP_SIZE);
    	//double next_step_size = STEP_SIZE;

    	// do step
    	auxFlag = fmu_power_sa.setReal(c_power_sa,vr_in_power_sa_u_d,2, &r_in_power_from_control[0]);
    	if(auxFlag != fmi2OK){
    		printf("Failed setReal\n");
			fflush(stdout);
			return 1;
    	}
    	auxFlag = fmu_power_sa.setReal(c_power_sa,vr_in_power_sa_tau,1, &r_in_power_from_loop[0]);
    	if(auxFlag != fmi2OK){
    		printf("Failed setReal\n");
			fflush(stdout);
			return 1;
    	}

    	auxFlag = fmu_power_sa.doStep(c_power_sa, currentTime, STEP_SIZE, fmi2True);

    	if (fmu_power_sa.getReal(c_power_sa, vr_out_power_sa, 3, &r_out_power[0]) != fmi2OK){
    		printf("Failed getReal\n");
			fflush(stdout);
			return 1;
    	}

    	auxFlag = fmu_env.doStep(c_env, currentTime, STEP_SIZE, fmi2True);

    	if (auxFlag != fmi2OK){
			printf("Failed fmu_env.doStep\n");
			fflush(stdout);
			return 1;
		}

    	if (fmu_env.getBoolean(c_env, vr_out_env, 9, &b_out_env[0]) != fmi2OK){
    		printf("Failed fmu_env.getBoolean\n");
			fflush(stdout);
			return 1;
    	}

    	fprintf(fp_fmu_env,"%f,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
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

    	auxFlag = fmu_control_sa.setBoolean(c_control_sa,vr_in_control_sa_from_env,8,&b_out_env[0]);
    	if(auxFlag != fmi2OK){
    		printf("Failed fmu_control_sa.setBoolean\n");
			fflush(stdout);
			return 1;
    	}
    	auxFlag = fmu_control_sa.setReal(c_control_sa,vr_in_control_sa_from_power,1, &r_out_power[0]);
    	if(auxFlag != fmi2OK){
    		printf("Failed fmu_control_sa.setReal\n");
			fflush(stdout);
			return 1;
    	}

    	auxFlag = fmu_control_sa.doStep(c_control_sa, currentTime, STEP_SIZE, fmi2True);

    	if(auxFlag != fmi2OK){
			printf("Failed fmu_control_sa.doStep\n");
			fflush(stdout);
			return 1;
		}

    	if (fmu_control_sa.getBoolean(c_control_sa, vr_out_control_sa, 2, &b_out_control_sa[0]) != fmi2OK){
    		printf("Failed getBoolean\n");
			fflush(stdout);
			return 1;
		}

    	fprintf(fp_fmu_control_sa,"%f,%d,%d\n",
    			currentTime,
				b_out_control_sa[0],
				b_out_control_sa[1]);

    	r_in_power_from_control[0] = (int)b_out_control_sa[0];
    	r_in_power_from_control[1] = (int)b_out_control_sa[1];

    	fprintf(fp_fmu_power_sa,"%f,%f,%f,%f\n",
    	    			currentTime,
    					r_out_power[0],
    					r_out_power[1],
						r_out_power[2]);

    	fmi2ValueReference vr_toLoop[2] = {1,2};
    	fmi2Real toLoop[2];
    	toLoop[0] = r_out_power[1];
    	toLoop[1] = r_out_power[2];

    	if (fmu_loop_sa.setReal(c_loop_sa, vr_toLoop, 2, &toLoop[0]) != fmi2OK){
    		printf("Failed fmu_loop_sa.setReal\n");
			fflush(stdout);
			return 1;
		}

    	auxFlag = fmu_loop_sa.doStep(c_loop_sa, currentTime, STEP_SIZE, fmi2True);

    	if(auxFlag != fmi2OK){
			printf("Failed fmu_loop_sa.doStep\n");
			fflush(stdout);
			return 1;
		}

    	if (fmu_loop_sa.getReal(c_loop_sa, vr_out_loop_sa, 2, &r_out_loop_sa[0]) != fmi2OK){
    		printf("Failed getReal\n");
			fflush(stdout);
			return 1;
		}

    	fprintf(fp_fmu_loop_sa,"%f,%f,%f\n",
    	    	    			currentTime,
    	    					r_out_loop_sa[0],
    	    					r_out_loop_sa[1]
    	    					);

    	r_in_power_from_loop[0] = r_out_loop_sa[0];

    	currentTime += STEP_SIZE;

    	fflush(stdout);

    }
    fclose(fp_fmu_env);
    fclose(fp_fmu_power_sa);
    fclose(fp_fmu_control_sa);

	return EXIT_SUCCESS;
}
