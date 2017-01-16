/* Main Simulation File */
#include "StategraphSample_model.h"


/* dummy VARINFO and FILEINFO */
const FILE_INFO dummyFILE_INFO = omc_dummyFileInfo;
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;
#if defined(__cplusplus)
extern "C" {
#endif

int StategraphSample_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->localData[0]->realVars[11] /* u variable */ = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int StategraphSample_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[11].attribute.start;
  
  TRACE_POP
  return 0;
}

int StategraphSample_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[11].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int StategraphSample_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[11].info.name;
  
  TRACE_POP
  return 0;
}

int StategraphSample_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = data->localData[0]->realVars[12] /* y variable */;
  
  TRACE_POP
  return 0;
}


/*
 equation index: 40
 type: SIMPLE_ASSIGN
 step1._active = pre(step1.newActive)
 */
void StategraphSample_eqFunction_40(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,40};
  data->localData[0]->booleanVars[7] /* step1._active DISCRETE */ = data->simulationInfo->booleanVarsPre[9] /* step1._newActive DISCRETE */;
  TRACE_POP
}
/*
 equation index: 41
 type: SIMPLE_ASSIGN
 step1._outerStatePort._subgraphStatePort._activeSteps = if step1.active then 1.0 else 0.0
 */
void StategraphSample_eqFunction_41(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,41};
  data->localData[0]->realVars[5] /* step1._outerStatePort._subgraphStatePort._activeSteps variable */ = (data->localData[0]->booleanVars[7] /* step1._active DISCRETE */?1.0:0.0);
  TRACE_POP
}
/*
 equation index: 42
 type: WHEN
 
 when {} then
   step1._oldActive = step1.active;
 end when;
 */
void StategraphSample_eqFunction_42(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,42};
  if(0)
  {
    data->localData[0]->booleanVars[10] /* step1._oldActive DISCRETE */ = data->localData[0]->booleanVars[7] /* step1._active DISCRETE */;
  }
  TRACE_POP
}
/*
 equation index: 43
 type: SIMPLE_ASSIGN
 step1._localActive = step1.active
 */
void StategraphSample_eqFunction_43(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,43};
  data->localData[0]->booleanVars[8] /* step1._localActive DISCRETE */ = data->localData[0]->booleanVars[7] /* step1._active DISCRETE */;
  TRACE_POP
}
/*
 equation index: 44
 type: SIMPLE_ASSIGN
 t1._condition = u > 0.5
 */
void StategraphSample_eqFunction_44(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,44};
  modelica_boolean tmp25;
  RELATIONHYSTERESIS(tmp25, data->localData[0]->realVars[11] /* u variable */, 0.5, 0, Greater);
  data->localData[0]->booleanVars[11] /* t1._condition DISCRETE */ = tmp25;
  TRACE_POP
}
/*
 equation index: 45
 type: SIMPLE_ASSIGN
 s1._active = pre(s1.newActive)
 */
void StategraphSample_eqFunction_45(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,45};
  data->localData[0]->booleanVars[1] /* s1._active DISCRETE */ = data->simulationInfo->booleanVarsPre[3] /* s1._newActive DISCRETE */;
  TRACE_POP
}
/*
 equation index: 46
 type: SIMPLE_ASSIGN
 s1._outerStatePort._subgraphStatePort._activeSteps = if s1.active then 1.0 else 0.0
 */
void StategraphSample_eqFunction_46(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,46};
  data->localData[0]->realVars[2] /* s1._outerStatePort._subgraphStatePort._activeSteps variable */ = (data->localData[0]->booleanVars[1] /* s1._active DISCRETE */?1.0:0.0);
  TRACE_POP
}
/*
 equation index: 47
 type: SIMPLE_ASSIGN
 stateGraphRoot._subgraphStatePort._activeSteps = (-s1.outerStatePort.subgraphStatePort.activeSteps) - step1.outerStatePort.subgraphStatePort.activeSteps
 */
void StategraphSample_eqFunction_47(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,47};
  data->localData[0]->realVars[3] /* stateGraphRoot._subgraphStatePort._activeSteps variable */ = (-data->localData[0]->realVars[2] /* s1._outerStatePort._subgraphStatePort._activeSteps variable */) - data->localData[0]->realVars[5] /* step1._outerStatePort._subgraphStatePort._activeSteps variable */;
  TRACE_POP
}
/*
 equation index: 48
 type: SIMPLE_ASSIGN
 stateGraphRoot._activeSteps = -integer(stateGraphRoot.subgraphStatePort.activeSteps, 0)
 */
void StategraphSample_eqFunction_48(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,48};
  data->localData[0]->integerVars[0] /* stateGraphRoot._activeSteps DISCRETE */ = (-(_event_integer(data->localData[0]->realVars[3] /* stateGraphRoot._subgraphStatePort._activeSteps variable */, ((modelica_integer) 0), data)));
  TRACE_POP
}
/*
 equation index: 49
 type: SIMPLE_ASSIGN
 y = if s1.active then 0.0 else 1.0
 */
void StategraphSample_eqFunction_49(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,49};
  data->localData[0]->realVars[12] /* y variable */ = (data->localData[0]->booleanVars[1] /* s1._active DISCRETE */?0.0:1.0);
  TRACE_POP
}
/*
 equation index: 50
 type: SIMPLE_ASSIGN
 $whenCondition1 = step1.active and not s1.active
 */
void StategraphSample_eqFunction_50(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,50};
  data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ = (data->localData[0]->booleanVars[7] /* step1._active DISCRETE */ && (!data->localData[0]->booleanVars[1] /* s1._active DISCRETE */));
  TRACE_POP
}
/*
 equation index: 51
 type: WHEN
 
 when {$whenCondition1} then
   t2._t_start = time;
 end when;
 */
void StategraphSample_eqFunction_51(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,51};
  if((data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ && !data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */ /* edge */))
  {
    data->localData[0]->realVars[13] /* t2._t_start DISCRETE */ = data->localData[0]->timeValue;
  }
  TRACE_POP
}
/*
 equation index: 52
 type: SIMPLE_ASSIGN
 t2._t_dummy = time - t2.t_start
 */
void StategraphSample_eqFunction_52(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,52};
  data->localData[0]->realVars[10] /* t2._t_dummy variable */ = data->localData[0]->timeValue - data->localData[0]->realVars[13] /* t2._t_start DISCRETE */;
  TRACE_POP
}
/*
 equation index: 53
 type: SIMPLE_ASSIGN
 t2._fire = $whenCondition1 and time >= t2.t_start + t2.waitTime
 */
void StategraphSample_eqFunction_53(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,53};
  modelica_boolean tmp26;
  RELATIONHYSTERESIS(tmp26, data->localData[0]->timeValue, data->localData[0]->realVars[13] /* t2._t_start DISCRETE */ + data->simulationInfo->realParameter[1] /* t2._waitTime PARAM */, 1, GreaterEq);
  data->localData[0]->booleanVars[15] /* t2._fire DISCRETE */ = (data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ && tmp26);
  TRACE_POP
}
/*
 equation index: 54
 type: SIMPLE_ASSIGN
 t2._t = if $whenCondition1 then t2.t_dummy else 0.0
 */
void StategraphSample_eqFunction_54(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,54};
  data->localData[0]->realVars[9] /* t2._t variable */ = (data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */?data->localData[0]->realVars[10] /* t2._t_dummy variable */:0.0);
  TRACE_POP
}
/*
 equation index: 55
 type: SIMPLE_ASSIGN
 t2._enableFire = $whenCondition1
 */
void StategraphSample_eqFunction_55(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,55};
  data->localData[0]->booleanVars[14] /* t2._enableFire DISCRETE */ = data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */;
  TRACE_POP
}
/*
 equation index: 56
 type: SIMPLE_ASSIGN
 t1._enableFire = t1.condition and s1.active and not step1.active
 */
void StategraphSample_eqFunction_56(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,56};
  data->localData[0]->booleanVars[12] /* t1._enableFire DISCRETE */ = ((data->localData[0]->booleanVars[11] /* t1._condition DISCRETE */ && data->localData[0]->booleanVars[1] /* s1._active DISCRETE */) && (!data->localData[0]->booleanVars[7] /* step1._active DISCRETE */));
  TRACE_POP
}
/*
 equation index: 57
 type: SIMPLE_ASSIGN
 step1._newActive = Modelica.StateGraph.Temporary.anyTrue({t1.enableFire}) or step1.active and not Modelica.StateGraph.Temporary.anyTrue({t2.fire})
 */
void StategraphSample_eqFunction_57(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,57};
  boolean_array tmp27;
  boolean_array tmp28;
  array_alloc_scalar_boolean_array(&tmp27, 1, (modelica_boolean)data->localData[0]->booleanVars[12] /* t1._enableFire DISCRETE */);
  array_alloc_scalar_boolean_array(&tmp28, 1, (modelica_boolean)data->localData[0]->booleanVars[15] /* t2._fire DISCRETE */);
  data->localData[0]->booleanVars[9] /* step1._newActive DISCRETE */ = (omc_Modelica_StateGraph_Temporary_anyTrue(threadData, tmp27) || (data->localData[0]->booleanVars[7] /* step1._active DISCRETE */ && (!omc_Modelica_StateGraph_Temporary_anyTrue(threadData, tmp28))));
  TRACE_POP
}
/*
 equation index: 58
 type: SIMPLE_ASSIGN
 s1._newActive = Modelica.StateGraph.Temporary.anyTrue({t2.fire}) or s1.active and not Modelica.StateGraph.Temporary.anyTrue({t1.enableFire})
 */
void StategraphSample_eqFunction_58(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,58};
  boolean_array tmp29;
  boolean_array tmp30;
  array_alloc_scalar_boolean_array(&tmp29, 1, (modelica_boolean)data->localData[0]->booleanVars[15] /* t2._fire DISCRETE */);
  array_alloc_scalar_boolean_array(&tmp30, 1, (modelica_boolean)data->localData[0]->booleanVars[12] /* t1._enableFire DISCRETE */);
  data->localData[0]->booleanVars[3] /* s1._newActive DISCRETE */ = (omc_Modelica_StateGraph_Temporary_anyTrue(threadData, tmp29) || (data->localData[0]->booleanVars[1] /* s1._active DISCRETE */ && (!omc_Modelica_StateGraph_Temporary_anyTrue(threadData, tmp30))));
  TRACE_POP
}
/*
 equation index: 59
 type: WHEN
 
 when {} then
   s1._oldActive = s1.active;
 end when;
 */
void StategraphSample_eqFunction_59(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,59};
  if(0)
  {
    data->localData[0]->booleanVars[4] /* s1._oldActive DISCRETE */ = data->localData[0]->booleanVars[1] /* s1._active DISCRETE */;
  }
  TRACE_POP
}
/*
 equation index: 60
 type: SIMPLE_ASSIGN
 s1._localActive = s1.active
 */
void StategraphSample_eqFunction_60(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,60};
  data->localData[0]->booleanVars[2] /* s1._localActive DISCRETE */ = data->localData[0]->booleanVars[1] /* s1._active DISCRETE */;
  TRACE_POP
}


int StategraphSample_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
  
  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  StategraphSample_functionLocalKnownVars(data, threadData);
  StategraphSample_eqFunction_40(data, threadData);

  StategraphSample_eqFunction_41(data, threadData);

  StategraphSample_eqFunction_42(data, threadData);

  StategraphSample_eqFunction_43(data, threadData);

  StategraphSample_eqFunction_44(data, threadData);

  StategraphSample_eqFunction_45(data, threadData);

  StategraphSample_eqFunction_46(data, threadData);

  StategraphSample_eqFunction_47(data, threadData);

  StategraphSample_eqFunction_48(data, threadData);

  StategraphSample_eqFunction_49(data, threadData);

  StategraphSample_eqFunction_50(data, threadData);

  StategraphSample_eqFunction_51(data, threadData);

  StategraphSample_eqFunction_52(data, threadData);

  StategraphSample_eqFunction_53(data, threadData);

  StategraphSample_eqFunction_54(data, threadData);

  StategraphSample_eqFunction_55(data, threadData);

  StategraphSample_eqFunction_56(data, threadData);

  StategraphSample_eqFunction_57(data, threadData);

  StategraphSample_eqFunction_58(data, threadData);

  StategraphSample_eqFunction_59(data, threadData);

  StategraphSample_eqFunction_60(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int StategraphSample_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int StategraphSample_symEulerUpdate(DATA *data, modelica_real dt)
{
  return -1;
}



int StategraphSample_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  data->simulationInfo->callStatistics.functionODE++;
  
  StategraphSample_functionLocalKnownVars(data, threadData);
  /* no ODE systems */

  
  TRACE_POP
  return 0;
}

#ifdef FMU_EXPERIMENTAL
#endif
/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "StategraphSample_12jac.h"
#include "StategraphSample_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks StategraphSample_callback = {
   NULL,
   NULL,
   NULL,
   StategraphSample_callExternalObjectConstructors,
   StategraphSample_callExternalObjectDestructors,
   NULL,
   NULL,
   NULL,
   #if !defined(OMC_NO_STATESELECTION)
   StategraphSample_initializeStateSets,
   #else
   NULL,
   #endif
   StategraphSample_initializeDAEmodeData,
   StategraphSample_functionODE,
   StategraphSample_functionAlgebraics,
   StategraphSample_functionDAE,
   StategraphSample_functionLocalKnownVars,
   StategraphSample_input_function,
   StategraphSample_input_function_init,
   StategraphSample_input_function_updateStartValues,
   StategraphSample_output_function,
   StategraphSample_function_storeDelayed,
   StategraphSample_updateBoundVariableAttributes,
   0 /* useHomotopy */,
   StategraphSample_functionInitialEquations,
   StategraphSample_functionInitialEquations_lambda0,
   StategraphSample_functionRemovedInitialEquations,
   StategraphSample_updateBoundParameters,
   StategraphSample_checkForAsserts,
   StategraphSample_function_ZeroCrossingsEquations,
   StategraphSample_function_ZeroCrossings,
   StategraphSample_function_updateRelations,
   StategraphSample_checkForDiscreteChanges,
   StategraphSample_zeroCrossingDescription,
   StategraphSample_relationDescription,
   StategraphSample_function_initSample,
   StategraphSample_INDEX_JAC_A,
   StategraphSample_INDEX_JAC_B,
   StategraphSample_INDEX_JAC_C,
   StategraphSample_INDEX_JAC_D,
   StategraphSample_initialAnalyticJacobianA,
   StategraphSample_initialAnalyticJacobianB,
   StategraphSample_initialAnalyticJacobianC,
   StategraphSample_initialAnalyticJacobianD,
   StategraphSample_functionJacA_column,
   StategraphSample_functionJacB_column,
   StategraphSample_functionJacC_column,
   StategraphSample_functionJacD_column,
   StategraphSample_linear_model_frame,
   StategraphSample_linear_model_datarecovery_frame,
   StategraphSample_mayer,
   StategraphSample_lagrange,
   StategraphSample_pickUpBoundsForInputsInOptimization,
   StategraphSample_setInputData,
   StategraphSample_getTimeGrid,
   StategraphSample_symEulerUpdate,
   StategraphSample_function_initSynchronous,
   StategraphSample_function_updateSynchronous,
   StategraphSample_function_equationsSynchronous,
   StategraphSample_read_input_fmu
   #ifdef FMU_EXPERIMENTAL
   ,StategraphSample_functionODE_Partial
   ,StategraphSample_functionFMIJacobian
   #endif
   ,StategraphSample_inputNames


};

void StategraphSample_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  data->callback = &StategraphSample_callback;
  data->modelData->modelName = "StategraphSample";
  data->modelData->modelFilePrefix = "StategraphSample";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/Users/clagms/Source Control/Git_HybridCosimulation/ModelicaModels";
  data->modelData->modelGUID = "{1bbd4064-0ef0-405e-a6e3-a61a868199f5}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData =
  #if defined(OMC_MINIMAL_METADATA)
    NULL;
  #else
  #include "StategraphSample_info.c"
  #endif
  ;
  
  data->modelData->nStates = 0;
  data->modelData->nVariablesReal = 14;
  data->modelData->nDiscreteReal = 1;
  data->modelData->nVariablesInteger = 1;
  data->modelData->nVariablesBoolean = 16;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 2;
  data->modelData->nParametersInteger = 4;
  data->modelData->nParametersBoolean = 2;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 1;
  data->modelData->nOutputVars = 1;
  
  data->modelData->nAliasReal = 5;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 26;
  data->modelData->nAliasString = 0;
  
  data->modelData->nZeroCrossings = 3;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 2;
  data->modelData->nMathEvents = 1;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.fileName = "StategraphSample_info.json";
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 1;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 73;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 0;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 4;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  
  data->modelData->nDelayExpressions = 0;
  
  data->modelData->nClocks = 0;
  data->modelData->nSubClocks = 0;
  
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
}

#ifdef __cplusplus
}
#endif

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}

