
// define class name and unique id
#define MODEL_IDENTIFIER StategraphSample
#define MODEL_GUID "{1bbd4064-0ef0-405e-a6e3-a61a868199f5}"

// include fmu header files, typedefs and macros
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "openmodelica.h"
#include "openmodelica_func.h"
#include "simulation_data.h"
#include "util/omc_error.h"
#include "StategraphSample_functions.h"
#include "simulation/solver/initialization/initialization.h"
#include "simulation/solver/events.h"
#include "fmu2_model_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

void setStartValues(ModelInstance *comp);
void setDefaultStartValues(ModelInstance *comp);
void eventUpdate(ModelInstance* comp, fmi2EventInfo* eventInfo);
fmi2Real getReal(ModelInstance* comp, const fmi2ValueReference vr);
fmi2Status setReal(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Real value);
fmi2Integer getInteger(ModelInstance* comp, const fmi2ValueReference vr);
fmi2Status setInteger(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Integer value);
fmi2Boolean getBoolean(ModelInstance* comp, const fmi2ValueReference vr);
fmi2Status setBoolean(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Boolean value);
fmi2String getString(ModelInstance* comp, const fmi2ValueReference vr);
fmi2Status setString(ModelInstance* comp, const fmi2ValueReference vr, fmi2String value);
fmi2Status setExternalFunction(ModelInstance* c, const fmi2ValueReference vr, const void* value);

// define model size
#define NUMBER_OF_STATES 0
#define NUMBER_OF_EVENT_INDICATORS 3
#define NUMBER_OF_REALS 21
#define NUMBER_OF_INTEGERS 5
#define NUMBER_OF_STRINGS 0
#define NUMBER_OF_BOOLEANS 44
#define NUMBER_OF_EXTERNALFUNCTIONS 0

// define variable data for model
#define $PrealExpression1$Py_vr 0 // "Value of Real output"
#define $PrealExpression2$Py_vr 1 // "Value of Real output"
#define $Ps1$PouterStatePort$PsubgraphStatePort$PactiveSteps_vr 2 // "Number of active steps in the CompositeStep"
#define $PstateGraphRoot$PsubgraphStatePort$PactiveSteps_vr 3 // "Number of active steps in the CompositeStep"
#define $PstateGraphRoot$PsubgraphStatePort$PactiveStepsDummy_vr 4 // "Dummy variable in order that connector fulfills restriction of connector"
#define $Pstep1$PouterStatePort$PsubgraphStatePort$PactiveSteps_vr 5 // "Number of active steps in the CompositeStep"
#define $Pt1$Pt_vr 6 // "= actual waiting time (transition will fire when t > waitTime)"
#define $Pt1$Pt_dummy_vr 7 
#define $Pt1$Pt_start_vr 8 // "Time instant at which the transition would fire, if waitTime would be zero"
#define $Pt2$Pt_vr 9 // "= actual waiting time (transition will fire when t > waitTime)"
#define $Pt2$Pt_dummy_vr 10 
#define $Pu_vr 11 
#define $Py_vr 12 
#define $Pt2$Pt_start_vr 13 // "Time instant at which the transition would fire, if waitTime would be zero"
#define $Pt1$PwaitTime_vr 14 // "Wait time before transition fires"
#define $Pt2$PwaitTime_vr 15 // "Wait time before transition fires"
#define $Ps1$PouterStatePort$PsubgraphStatePort$PactiveStepsDummy_vr 16 // "Dummy variable in order that connector fulfills restriction of connector"
#define $Pstep1$PouterStatePort$PsubgraphStatePort$PactiveStepsDummy_vr 17 // "Dummy variable in order that connector fulfills restriction of connector"
#define $Pswitch1$Pu1_vr 18 // "Connector of first Real input signal"
#define $Pswitch1$Pu3_vr 19 // "Connector of second Real input signal"
#define $Pswitch1$Py_vr 20 // "Connector of Real output signal"
#define $PstateGraphRoot$PactiveSteps_vr 0 // "Number of active steps within the stategraph"
#define $Ps1$PnIn_vr 1 // "Number of input connections"
#define $Ps1$PnOut_vr 2 // "Number of output connections"
#define $Pstep1$PnIn_vr 3 // "Number of input connections"
#define $Pstep1$PnOut_vr 4 // "Number of output connections"
#define $P$whenCondition1_vr 0 
#define $Ps1$Pactive_vr 1 
#define $Ps1$PlocalActive_vr 2 // "= true if step is active, otherwise the step is not active"
#define $Ps1$PnewActive_vr 3 // "Value of active in the next iteration"
#define $Ps1$PoldActive_vr 4 // "Value of active when CompositeStep was aborted"
#define $PstateGraphRoot$Presume_vr 5 
#define $PstateGraphRoot$Psuspend_vr 6 
#define $Pstep1$Pactive_vr 7 // "= true if step is active, otherwise the step is not active"
#define $Pstep1$PlocalActive_vr 8 // "= true if step is active, otherwise the step is not active"
#define $Pstep1$PnewActive_vr 9 // "Value of active in the next iteration"
#define $Pstep1$PoldActive_vr 10 // "Value of active when CompositeStep was aborted"
#define $Pt1$Pcondition_vr 11 // "= true, if transition may fire (time varying expression)"
#define $Pt1$PenableFire_vr 12 // "= true, if all firing conditions are true"
#define $Pt2$Pcondition_vr 13 // "= true, if transition may fire (time varying expression)"
#define $Pt2$PenableFire_vr 14 // "= true, if all firing conditions are true"
#define $Pt2$Pfire_vr 15 // "= true, if transition fires"
#define $Pt1$PenableTimer_vr 16 // "= true, if timer is enabled"
#define $Pt2$PenableTimer_vr 17 // "= true, if timer is enabled"
#define $Ps1$PinPort$lB1$rB$Poccupied_vr 18 // "true, if step is active"
#define $Ps1$PinPort$lB1$rB$Pset_vr 19 // "true, if transition fires and step is activated"
#define $Ps1$PoutPort$lB1$rB$Pavailable_vr 20 // "true, if step is active"
#define $Ps1$PoutPort$lB1$rB$Preset_vr 21 // "true, if transition fires and step is deactivated"
#define $Ps1$PouterStatePort$PsubgraphStatePort$Presume_vr 22 // "= true, if resume transition of CompositeStep fires"
#define $Ps1$PouterStatePort$PsubgraphStatePort$Psuspend_vr 23 // "= true, if suspend transition of CompositeStep fires"
#define $PstateGraphRoot$PsubgraphStatePort$Presume_vr 24 // "= true, if resume transition of CompositeStep fires"
#define $PstateGraphRoot$PsubgraphStatePort$Psuspend_vr 25 // "= true, if suspend transition of CompositeStep fires"
#define $Pstep1$PinPort$lB1$rB$Poccupied_vr 26 // "true, if step is active"
#define $Pstep1$PinPort$lB1$rB$Pset_vr 27 // "true, if transition fires and step is activated"
#define $Pstep1$PoutPort$lB1$rB$Pavailable_vr 28 // "true, if step is active"
#define $Pstep1$PoutPort$lB1$rB$Preset_vr 29 // "true, if transition fires and step is deactivated"
#define $Pstep1$PouterStatePort$PsubgraphStatePort$Presume_vr 30 // "= true, if resume transition of CompositeStep fires"
#define $Pstep1$PouterStatePort$PsubgraphStatePort$Psuspend_vr 31 // "= true, if suspend transition of CompositeStep fires"
#define $Pswitch1$Pu2_vr 32 // "Connector of Boolean input signal"
#define $Pt1$Pfire_vr 33 // "= true, if transition fires"
#define $Pt1$PinPort$Pavailable_vr 34 // "true, if step connected to the transition input is active"
#define $Pt1$PinPort$Preset_vr 35 // "true, if transition fires and the step connected to the transition input is deactivated"
#define $Pt1$PlocalCondition_vr 36 // "= true, if transition may fire"
#define $Pt1$PoutPort$Poccupied_vr 37 // "true, if step connected to the transition output is active"
#define $Pt1$PoutPort$Pset_vr 38 // "true, if transition fires and step connected to the transition output becomes active"
#define $Pt2$PinPort$Pavailable_vr 39 // "true, if step connected to the transition input is active"
#define $Pt2$PinPort$Preset_vr 40 // "true, if transition fires and the step connected to the transition input is deactivated"
#define $Pt2$PlocalCondition_vr 41 // "= true, if transition may fire"
#define $Pt2$PoutPort$Poccupied_vr 42 // "true, if step connected to the transition output is active"
#define $Pt2$PoutPort$Pset_vr 43 // "true, if transition fires and step connected to the transition output becomes active"


// define initial state vector as vector of value references
#define STATES {  }
#define STATESDERIVATIVES {  }


// implementation of the Model Exchange functions
  extern void StategraphSample_setupDataStruc(DATA *data);
  #define fmu2_model_interface_setupDataStruc StategraphSample_setupDataStruc
  #include "fmu2_model_interface.c"

// Set values for all variables that define a start value
void setDefaultStartValues(ModelInstance *comp) {

comp->fmuData->modelData->realVarsData[0].attribute.start = 0;
comp->fmuData->modelData->realVarsData[1].attribute.start = 0;
comp->fmuData->modelData->realVarsData[2].attribute.start = 0;
comp->fmuData->modelData->realVarsData[3].attribute.start = 0;
comp->fmuData->modelData->realVarsData[4].attribute.start = 0;
comp->fmuData->modelData->realVarsData[5].attribute.start = 0;
comp->fmuData->modelData->realVarsData[6].attribute.start = 0;
comp->fmuData->modelData->realVarsData[7].attribute.start = 0;
comp->fmuData->modelData->realVarsData[8].attribute.start = 0;
comp->fmuData->modelData->realVarsData[9].attribute.start = 0;
comp->fmuData->modelData->realVarsData[10].attribute.start = 0;
comp->fmuData->modelData->realVarsData[11].attribute.start = 0;
comp->fmuData->modelData->realVarsData[12].attribute.start = 0;
comp->fmuData->modelData->realVarsData[13].attribute.start = 0;
comp->fmuData->modelData->integerVarsData[0].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[0].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[1].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[2].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[3].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[4].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[5].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[6].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[7].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[8].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[9].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[10].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[11].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[12].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[13].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[14].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[15].attribute.start = 0;
comp->fmuData->modelData->realParameterData[0].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[1].attribute.start = 1.0;
comp->fmuData->modelData->integerParameterData[0].attribute.start = 1;
comp->fmuData->modelData->integerParameterData[1].attribute.start = 1;
comp->fmuData->modelData->integerParameterData[2].attribute.start = 1;
comp->fmuData->modelData->integerParameterData[3].attribute.start = 1;
comp->fmuData->modelData->booleanParameterData[0].attribute.start = 0;
comp->fmuData->modelData->booleanParameterData[1].attribute.start = 1;
}
// Set values for all variables that define a start value
void setStartValues(ModelInstance *comp) {

  comp->fmuData->modelData->realVarsData[0].attribute.start =  comp->fmuData->localData[0]->realVars[0];
  comp->fmuData->modelData->realVarsData[1].attribute.start =  comp->fmuData->localData[0]->realVars[1];
  comp->fmuData->modelData->realVarsData[2].attribute.start =  comp->fmuData->localData[0]->realVars[2];
  comp->fmuData->modelData->realVarsData[3].attribute.start =  comp->fmuData->localData[0]->realVars[3];
  comp->fmuData->modelData->realVarsData[4].attribute.start =  comp->fmuData->localData[0]->realVars[4];
  comp->fmuData->modelData->realVarsData[5].attribute.start =  comp->fmuData->localData[0]->realVars[5];
  comp->fmuData->modelData->realVarsData[6].attribute.start =  comp->fmuData->localData[0]->realVars[6];
  comp->fmuData->modelData->realVarsData[7].attribute.start =  comp->fmuData->localData[0]->realVars[7];
  comp->fmuData->modelData->realVarsData[8].attribute.start =  comp->fmuData->localData[0]->realVars[8];
  comp->fmuData->modelData->realVarsData[9].attribute.start =  comp->fmuData->localData[0]->realVars[9];
  comp->fmuData->modelData->realVarsData[10].attribute.start =  comp->fmuData->localData[0]->realVars[10];
  comp->fmuData->modelData->realVarsData[11].attribute.start =  comp->fmuData->localData[0]->realVars[11];
  comp->fmuData->modelData->realVarsData[12].attribute.start =  comp->fmuData->localData[0]->realVars[12];
  comp->fmuData->modelData->realVarsData[13].attribute.start =  comp->fmuData->localData[0]->realVars[13];
  comp->fmuData->modelData->integerVarsData[0].attribute.start =  comp->fmuData->localData[0]->integerVars[0];
  comp->fmuData->modelData->booleanVarsData[0].attribute.start =  comp->fmuData->localData[0]->booleanVars[0];
  comp->fmuData->modelData->booleanVarsData[1].attribute.start =  comp->fmuData->localData[0]->booleanVars[1];
  comp->fmuData->modelData->booleanVarsData[2].attribute.start =  comp->fmuData->localData[0]->booleanVars[2];
  comp->fmuData->modelData->booleanVarsData[3].attribute.start =  comp->fmuData->localData[0]->booleanVars[3];
  comp->fmuData->modelData->booleanVarsData[4].attribute.start =  comp->fmuData->localData[0]->booleanVars[4];
  comp->fmuData->modelData->booleanVarsData[5].attribute.start =  comp->fmuData->localData[0]->booleanVars[5];
  comp->fmuData->modelData->booleanVarsData[6].attribute.start =  comp->fmuData->localData[0]->booleanVars[6];
  comp->fmuData->modelData->booleanVarsData[7].attribute.start =  comp->fmuData->localData[0]->booleanVars[7];
  comp->fmuData->modelData->booleanVarsData[8].attribute.start =  comp->fmuData->localData[0]->booleanVars[8];
  comp->fmuData->modelData->booleanVarsData[9].attribute.start =  comp->fmuData->localData[0]->booleanVars[9];
  comp->fmuData->modelData->booleanVarsData[10].attribute.start =  comp->fmuData->localData[0]->booleanVars[10];
  comp->fmuData->modelData->booleanVarsData[11].attribute.start =  comp->fmuData->localData[0]->booleanVars[11];
  comp->fmuData->modelData->booleanVarsData[12].attribute.start =  comp->fmuData->localData[0]->booleanVars[12];
  comp->fmuData->modelData->booleanVarsData[13].attribute.start =  comp->fmuData->localData[0]->booleanVars[13];
  comp->fmuData->modelData->booleanVarsData[14].attribute.start =  comp->fmuData->localData[0]->booleanVars[14];
  comp->fmuData->modelData->booleanVarsData[15].attribute.start =  comp->fmuData->localData[0]->booleanVars[15];
comp->fmuData->modelData->realParameterData[0].attribute.start = comp->fmuData->simulationInfo->realParameter[0];
comp->fmuData->modelData->realParameterData[1].attribute.start = comp->fmuData->simulationInfo->realParameter[1];
comp->fmuData->modelData->integerParameterData[0].attribute.start = comp->fmuData->simulationInfo->integerParameter[0];
comp->fmuData->modelData->integerParameterData[1].attribute.start = comp->fmuData->simulationInfo->integerParameter[1];
comp->fmuData->modelData->integerParameterData[2].attribute.start = comp->fmuData->simulationInfo->integerParameter[2];
comp->fmuData->modelData->integerParameterData[3].attribute.start = comp->fmuData->simulationInfo->integerParameter[3];
comp->fmuData->modelData->booleanParameterData[0].attribute.start = comp->fmuData->simulationInfo->booleanParameter[0];
comp->fmuData->modelData->booleanParameterData[1].attribute.start = comp->fmuData->simulationInfo->booleanParameter[1];
}
  // Used to set the next time event, if any.
  void eventUpdate(ModelInstance* comp, fmi2EventInfo* eventInfo) {
  }
  
  fmi2Real getReal(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        case $PrealExpression1$Py_vr : return comp->fmuData->localData[0]->realVars[0]; break;
        case $PrealExpression2$Py_vr : return comp->fmuData->localData[0]->realVars[1]; break;
        case $Ps1$PouterStatePort$PsubgraphStatePort$PactiveSteps_vr : return comp->fmuData->localData[0]->realVars[2]; break;
        case $PstateGraphRoot$PsubgraphStatePort$PactiveSteps_vr : return comp->fmuData->localData[0]->realVars[3]; break;
        case $PstateGraphRoot$PsubgraphStatePort$PactiveStepsDummy_vr : return comp->fmuData->localData[0]->realVars[4]; break;
        case $Pstep1$PouterStatePort$PsubgraphStatePort$PactiveSteps_vr : return comp->fmuData->localData[0]->realVars[5]; break;
        case $Pt1$Pt_vr : return comp->fmuData->localData[0]->realVars[6]; break;
        case $Pt1$Pt_dummy_vr : return comp->fmuData->localData[0]->realVars[7]; break;
        case $Pt1$Pt_start_vr : return comp->fmuData->localData[0]->realVars[8]; break;
        case $Pt2$Pt_vr : return comp->fmuData->localData[0]->realVars[9]; break;
        case $Pt2$Pt_dummy_vr : return comp->fmuData->localData[0]->realVars[10]; break;
        case $Pu_vr : return comp->fmuData->localData[0]->realVars[11]; break;
        case $Py_vr : return comp->fmuData->localData[0]->realVars[12]; break;
        case $Pt2$Pt_start_vr : return comp->fmuData->localData[0]->realVars[13]; break;
        case $Pt1$PwaitTime_vr : return comp->fmuData->simulationInfo->realParameter[0]; break;
        case $Pt2$PwaitTime_vr : return comp->fmuData->simulationInfo->realParameter[1]; break;
        case $Ps1$PouterStatePort$PsubgraphStatePort$PactiveStepsDummy_vr : return getReal(comp, $PstateGraphRoot$PsubgraphStatePort$PactiveStepsDummy_vr); break;
        case $Pstep1$PouterStatePort$PsubgraphStatePort$PactiveStepsDummy_vr : return getReal(comp, $PstateGraphRoot$PsubgraphStatePort$PactiveStepsDummy_vr); break;
        case $Pswitch1$Pu1_vr : return getReal(comp, $PrealExpression1$Py_vr); break;
        case $Pswitch1$Pu3_vr : return getReal(comp, $PrealExpression2$Py_vr); break;
        case $Pswitch1$Py_vr : return getReal(comp, $Py_vr); break;
        default:
            return 0;
    }
  }
  
  fmi2Status setReal(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Real value) {
    switch (vr) {
        case $PrealExpression1$Py_vr : comp->fmuData->localData[0]->realVars[0] = value; break;
        case $PrealExpression2$Py_vr : comp->fmuData->localData[0]->realVars[1] = value; break;
        case $Ps1$PouterStatePort$PsubgraphStatePort$PactiveSteps_vr : comp->fmuData->localData[0]->realVars[2] = value; break;
        case $PstateGraphRoot$PsubgraphStatePort$PactiveSteps_vr : comp->fmuData->localData[0]->realVars[3] = value; break;
        case $PstateGraphRoot$PsubgraphStatePort$PactiveStepsDummy_vr : comp->fmuData->localData[0]->realVars[4] = value; break;
        case $Pstep1$PouterStatePort$PsubgraphStatePort$PactiveSteps_vr : comp->fmuData->localData[0]->realVars[5] = value; break;
        case $Pt1$Pt_vr : comp->fmuData->localData[0]->realVars[6] = value; break;
        case $Pt1$Pt_dummy_vr : comp->fmuData->localData[0]->realVars[7] = value; break;
        case $Pt1$Pt_start_vr : comp->fmuData->localData[0]->realVars[8] = value; break;
        case $Pt2$Pt_vr : comp->fmuData->localData[0]->realVars[9] = value; break;
        case $Pt2$Pt_dummy_vr : comp->fmuData->localData[0]->realVars[10] = value; break;
        case $Pu_vr : comp->fmuData->localData[0]->realVars[11] = value; break;
        case $Py_vr : comp->fmuData->localData[0]->realVars[12] = value; break;
        case $Pt2$Pt_start_vr : comp->fmuData->localData[0]->realVars[13] = value; break;
        case $Pt1$PwaitTime_vr : comp->fmuData->simulationInfo->realParameter[0] = value; break;
        case $Pt2$PwaitTime_vr : comp->fmuData->simulationInfo->realParameter[1] = value; break;
        case $Ps1$PouterStatePort$PsubgraphStatePort$PactiveStepsDummy_vr : return setReal(comp, $PstateGraphRoot$PsubgraphStatePort$PactiveStepsDummy_vr, value); break;
        case $Pstep1$PouterStatePort$PsubgraphStatePort$PactiveStepsDummy_vr : return setReal(comp, $PstateGraphRoot$PsubgraphStatePort$PactiveStepsDummy_vr, value); break;
        case $Pswitch1$Pu1_vr : return setReal(comp, $PrealExpression1$Py_vr, value); break;
        case $Pswitch1$Pu3_vr : return setReal(comp, $PrealExpression2$Py_vr, value); break;
        case $Pswitch1$Py_vr : return setReal(comp, $Py_vr, value); break;
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  
  fmi2Integer getInteger(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        case $PstateGraphRoot$PactiveSteps_vr : return comp->fmuData->localData[0]->integerVars[0]; break;
        case $Ps1$PnIn_vr : return comp->fmuData->simulationInfo->integerParameter[0]; break;
        case $Ps1$PnOut_vr : return comp->fmuData->simulationInfo->integerParameter[1]; break;
        case $Pstep1$PnIn_vr : return comp->fmuData->simulationInfo->integerParameter[2]; break;
        case $Pstep1$PnOut_vr : return comp->fmuData->simulationInfo->integerParameter[3]; break;
        default:
            return 0;
    }
  }
  fmi2Status setInteger(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Integer value) {
    switch (vr) {
        case $PstateGraphRoot$PactiveSteps_vr : comp->fmuData->localData[0]->integerVars[0] = value; break;
        case $Ps1$PnIn_vr : comp->fmuData->simulationInfo->integerParameter[0] = value; break;
        case $Ps1$PnOut_vr : comp->fmuData->simulationInfo->integerParameter[1] = value; break;
        case $Pstep1$PnIn_vr : comp->fmuData->simulationInfo->integerParameter[2] = value; break;
        case $Pstep1$PnOut_vr : comp->fmuData->simulationInfo->integerParameter[3] = value; break;
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  fmi2Boolean getBoolean(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        case $P$whenCondition1_vr : return comp->fmuData->localData[0]->booleanVars[0]; break;
        case $Ps1$Pactive_vr : return comp->fmuData->localData[0]->booleanVars[1]; break;
        case $Ps1$PlocalActive_vr : return comp->fmuData->localData[0]->booleanVars[2]; break;
        case $Ps1$PnewActive_vr : return comp->fmuData->localData[0]->booleanVars[3]; break;
        case $Ps1$PoldActive_vr : return comp->fmuData->localData[0]->booleanVars[4]; break;
        case $PstateGraphRoot$Presume_vr : return comp->fmuData->localData[0]->booleanVars[5]; break;
        case $PstateGraphRoot$Psuspend_vr : return comp->fmuData->localData[0]->booleanVars[6]; break;
        case $Pstep1$Pactive_vr : return comp->fmuData->localData[0]->booleanVars[7]; break;
        case $Pstep1$PlocalActive_vr : return comp->fmuData->localData[0]->booleanVars[8]; break;
        case $Pstep1$PnewActive_vr : return comp->fmuData->localData[0]->booleanVars[9]; break;
        case $Pstep1$PoldActive_vr : return comp->fmuData->localData[0]->booleanVars[10]; break;
        case $Pt1$Pcondition_vr : return comp->fmuData->localData[0]->booleanVars[11]; break;
        case $Pt1$PenableFire_vr : return comp->fmuData->localData[0]->booleanVars[12]; break;
        case $Pt2$Pcondition_vr : return comp->fmuData->localData[0]->booleanVars[13]; break;
        case $Pt2$PenableFire_vr : return comp->fmuData->localData[0]->booleanVars[14]; break;
        case $Pt2$Pfire_vr : return comp->fmuData->localData[0]->booleanVars[15]; break;
        case $Pt1$PenableTimer_vr : return comp->fmuData->simulationInfo->booleanParameter[0]; break;
        case $Pt2$PenableTimer_vr : return comp->fmuData->simulationInfo->booleanParameter[1]; break;
        case $Ps1$PinPort$lB1$rB$Poccupied_vr : return getBoolean(comp, $Ps1$Pactive_vr); break;
        case $Ps1$PinPort$lB1$rB$Pset_vr : return getBoolean(comp, $Pt2$Pfire_vr); break;
        case $Ps1$PoutPort$lB1$rB$Pavailable_vr : return getBoolean(comp, $Ps1$Pactive_vr); break;
        case $Ps1$PoutPort$lB1$rB$Preset_vr : return getBoolean(comp, $Pt1$PenableFire_vr); break;
        case $Ps1$PouterStatePort$PsubgraphStatePort$Presume_vr : return getBoolean(comp, $PstateGraphRoot$Presume_vr); break;
        case $Ps1$PouterStatePort$PsubgraphStatePort$Psuspend_vr : return getBoolean(comp, $PstateGraphRoot$Psuspend_vr); break;
        case $PstateGraphRoot$PsubgraphStatePort$Presume_vr : return getBoolean(comp, $PstateGraphRoot$Presume_vr); break;
        case $PstateGraphRoot$PsubgraphStatePort$Psuspend_vr : return getBoolean(comp, $PstateGraphRoot$Psuspend_vr); break;
        case $Pstep1$PinPort$lB1$rB$Poccupied_vr : return getBoolean(comp, $Pstep1$Pactive_vr); break;
        case $Pstep1$PinPort$lB1$rB$Pset_vr : return getBoolean(comp, $Pt1$PenableFire_vr); break;
        case $Pstep1$PoutPort$lB1$rB$Pavailable_vr : return getBoolean(comp, $Pstep1$Pactive_vr); break;
        case $Pstep1$PoutPort$lB1$rB$Preset_vr : return getBoolean(comp, $Pt2$Pfire_vr); break;
        case $Pstep1$PouterStatePort$PsubgraphStatePort$Presume_vr : return getBoolean(comp, $PstateGraphRoot$Presume_vr); break;
        case $Pstep1$PouterStatePort$PsubgraphStatePort$Psuspend_vr : return getBoolean(comp, $PstateGraphRoot$Psuspend_vr); break;
        case $Pswitch1$Pu2_vr : return getBoolean(comp, $Ps1$Pactive_vr); break;
        case $Pt1$Pfire_vr : return getBoolean(comp, $Pt1$PenableFire_vr); break;
        case $Pt1$PinPort$Pavailable_vr : return getBoolean(comp, $Ps1$Pactive_vr); break;
        case $Pt1$PinPort$Preset_vr : return getBoolean(comp, $Pt1$PenableFire_vr); break;
        case $Pt1$PlocalCondition_vr : return getBoolean(comp, $Pt1$Pcondition_vr); break;
        case $Pt1$PoutPort$Poccupied_vr : return getBoolean(comp, $Pstep1$Pactive_vr); break;
        case $Pt1$PoutPort$Pset_vr : return getBoolean(comp, $Pt1$PenableFire_vr); break;
        case $Pt2$PinPort$Pavailable_vr : return getBoolean(comp, $Pstep1$Pactive_vr); break;
        case $Pt2$PinPort$Preset_vr : return getBoolean(comp, $Pt2$Pfire_vr); break;
        case $Pt2$PlocalCondition_vr : return getBoolean(comp, $Pt2$Pcondition_vr); break;
        case $Pt2$PoutPort$Poccupied_vr : return getBoolean(comp, $Ps1$Pactive_vr); break;
        case $Pt2$PoutPort$Pset_vr : return getBoolean(comp, $Pt2$Pfire_vr); break;
        default:
            return fmi2False;
    }
  }
  
  fmi2Status setBoolean(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Boolean value) {
    switch (vr) {
        case $P$whenCondition1_vr : comp->fmuData->localData[0]->booleanVars[0] = value; break;
        case $Ps1$Pactive_vr : comp->fmuData->localData[0]->booleanVars[1] = value; break;
        case $Ps1$PlocalActive_vr : comp->fmuData->localData[0]->booleanVars[2] = value; break;
        case $Ps1$PnewActive_vr : comp->fmuData->localData[0]->booleanVars[3] = value; break;
        case $Ps1$PoldActive_vr : comp->fmuData->localData[0]->booleanVars[4] = value; break;
        case $PstateGraphRoot$Presume_vr : comp->fmuData->localData[0]->booleanVars[5] = value; break;
        case $PstateGraphRoot$Psuspend_vr : comp->fmuData->localData[0]->booleanVars[6] = value; break;
        case $Pstep1$Pactive_vr : comp->fmuData->localData[0]->booleanVars[7] = value; break;
        case $Pstep1$PlocalActive_vr : comp->fmuData->localData[0]->booleanVars[8] = value; break;
        case $Pstep1$PnewActive_vr : comp->fmuData->localData[0]->booleanVars[9] = value; break;
        case $Pstep1$PoldActive_vr : comp->fmuData->localData[0]->booleanVars[10] = value; break;
        case $Pt1$Pcondition_vr : comp->fmuData->localData[0]->booleanVars[11] = value; break;
        case $Pt1$PenableFire_vr : comp->fmuData->localData[0]->booleanVars[12] = value; break;
        case $Pt2$Pcondition_vr : comp->fmuData->localData[0]->booleanVars[13] = value; break;
        case $Pt2$PenableFire_vr : comp->fmuData->localData[0]->booleanVars[14] = value; break;
        case $Pt2$Pfire_vr : comp->fmuData->localData[0]->booleanVars[15] = value; break;
        case $Pt1$PenableTimer_vr : comp->fmuData->simulationInfo->booleanParameter[0] = value; break;
        case $Pt2$PenableTimer_vr : comp->fmuData->simulationInfo->booleanParameter[1] = value; break;
        case $Ps1$PinPort$lB1$rB$Poccupied_vr : return setBoolean(comp, $Ps1$Pactive_vr, value); break;
        case $Ps1$PinPort$lB1$rB$Pset_vr : return setBoolean(comp, $Pt2$Pfire_vr, value); break;
        case $Ps1$PoutPort$lB1$rB$Pavailable_vr : return setBoolean(comp, $Ps1$Pactive_vr, value); break;
        case $Ps1$PoutPort$lB1$rB$Preset_vr : return setBoolean(comp, $Pt1$PenableFire_vr, value); break;
        case $Ps1$PouterStatePort$PsubgraphStatePort$Presume_vr : return setBoolean(comp, $PstateGraphRoot$Presume_vr, value); break;
        case $Ps1$PouterStatePort$PsubgraphStatePort$Psuspend_vr : return setBoolean(comp, $PstateGraphRoot$Psuspend_vr, value); break;
        case $PstateGraphRoot$PsubgraphStatePort$Presume_vr : return setBoolean(comp, $PstateGraphRoot$Presume_vr, value); break;
        case $PstateGraphRoot$PsubgraphStatePort$Psuspend_vr : return setBoolean(comp, $PstateGraphRoot$Psuspend_vr, value); break;
        case $Pstep1$PinPort$lB1$rB$Poccupied_vr : return setBoolean(comp, $Pstep1$Pactive_vr, value); break;
        case $Pstep1$PinPort$lB1$rB$Pset_vr : return setBoolean(comp, $Pt1$PenableFire_vr, value); break;
        case $Pstep1$PoutPort$lB1$rB$Pavailable_vr : return setBoolean(comp, $Pstep1$Pactive_vr, value); break;
        case $Pstep1$PoutPort$lB1$rB$Preset_vr : return setBoolean(comp, $Pt2$Pfire_vr, value); break;
        case $Pstep1$PouterStatePort$PsubgraphStatePort$Presume_vr : return setBoolean(comp, $PstateGraphRoot$Presume_vr, value); break;
        case $Pstep1$PouterStatePort$PsubgraphStatePort$Psuspend_vr : return setBoolean(comp, $PstateGraphRoot$Psuspend_vr, value); break;
        case $Pswitch1$Pu2_vr : return setBoolean(comp, $Ps1$Pactive_vr, value); break;
        case $Pt1$Pfire_vr : return setBoolean(comp, $Pt1$PenableFire_vr, value); break;
        case $Pt1$PinPort$Pavailable_vr : return setBoolean(comp, $Ps1$Pactive_vr, value); break;
        case $Pt1$PinPort$Preset_vr : return setBoolean(comp, $Pt1$PenableFire_vr, value); break;
        case $Pt1$PlocalCondition_vr : return setBoolean(comp, $Pt1$Pcondition_vr, value); break;
        case $Pt1$PoutPort$Poccupied_vr : return setBoolean(comp, $Pstep1$Pactive_vr, value); break;
        case $Pt1$PoutPort$Pset_vr : return setBoolean(comp, $Pt1$PenableFire_vr, value); break;
        case $Pt2$PinPort$Pavailable_vr : return setBoolean(comp, $Pstep1$Pactive_vr, value); break;
        case $Pt2$PinPort$Preset_vr : return setBoolean(comp, $Pt2$Pfire_vr, value); break;
        case $Pt2$PlocalCondition_vr : return setBoolean(comp, $Pt2$Pcondition_vr, value); break;
        case $Pt2$PoutPort$Poccupied_vr : return setBoolean(comp, $Ps1$Pactive_vr, value); break;
        case $Pt2$PoutPort$Pset_vr : return setBoolean(comp, $Pt2$Pfire_vr, value); break;
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  
  fmi2String getString(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        default:
            return "";
    }
  }
  
  fmi2Status setString(ModelInstance* comp, const fmi2ValueReference vr, fmi2String value) {
    switch (vr) {
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  
  fmi2Status setExternalFunction(ModelInstance* c, const fmi2ValueReference vr, const void* value){
    switch (vr) {
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  

#ifdef __cplusplus
}
#endif

