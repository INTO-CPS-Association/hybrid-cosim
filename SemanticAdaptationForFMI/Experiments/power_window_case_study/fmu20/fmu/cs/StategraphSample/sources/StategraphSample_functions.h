#ifndef StategraphSample__H
#define StategraphSample__H
#include "meta/meta_modelica.h"
#include "util/modelica.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "simulation/simulation_runtime.h"
#ifdef __cplusplus
extern "C" {
#endif


DLLExport
modelica_boolean omc_Modelica_StateGraph_Temporary_anyTrue(threadData_t *threadData, boolean_array _b);
DLLExport
modelica_metatype boxptr_Modelica_StateGraph_Temporary_anyTrue(threadData_t *threadData, modelica_metatype _b);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Modelica_StateGraph_Temporary_anyTrue,2,0) {(void*) boxptr_Modelica_StateGraph_Temporary_anyTrue,0}};
#define boxvar_Modelica_StateGraph_Temporary_anyTrue MMC_REFSTRUCTLIT(boxvar_lit_Modelica_StateGraph_Temporary_anyTrue)
#include "StategraphSample_model.h"


#ifdef __cplusplus
}
#endif
#endif

