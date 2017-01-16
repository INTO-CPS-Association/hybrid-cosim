/* Initialization */
#include "StategraphSample_model.h"
#include "StategraphSample_11mix.h"
#include "StategraphSample_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void StategraphSample_functionInitialEquations_0(DATA *data, threadData_t *threadData);


/*
 equation index: 1
 type: SIMPLE_ASSIGN
 stateGraphRoot._resume = false
 */
void StategraphSample_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  data->localData[0]->booleanVars[5] /* stateGraphRoot._resume DISCRETE */ = 0;
  TRACE_POP
}

/*
 equation index: 2
 type: SIMPLE_ASSIGN
 stateGraphRoot._suspend = false
 */
void StategraphSample_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  data->localData[0]->booleanVars[6] /* stateGraphRoot._suspend DISCRETE */ = 0;
  TRACE_POP
}

/*
 equation index: 3
 type: SIMPLE_ASSIGN
 realExpression2._y = 1.0
 */
void StategraphSample_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  data->localData[0]->realVars[1] /* realExpression2._y variable */ = 1.0;
  TRACE_POP
}

/*
 equation index: 4
 type: SIMPLE_ASSIGN
 realExpression1._y = 0.0
 */
void StategraphSample_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  data->localData[0]->realVars[0] /* realExpression1._y variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 5
 type: SIMPLE_ASSIGN
 t2._condition = true
 */
void StategraphSample_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  data->localData[0]->booleanVars[13] /* t2._condition DISCRETE */ = 1;
  TRACE_POP
}

/*
 equation index: 6
 type: SIMPLE_ASSIGN
 stateGraphRoot._subgraphStatePort._activeStepsDummy = 0.0
 */
void StategraphSample_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  data->localData[0]->realVars[4] /* stateGraphRoot._subgraphStatePort._activeStepsDummy variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 7
 type: SIMPLE_ASSIGN
 t1._t = 0.0
 */
void StategraphSample_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  data->localData[0]->realVars[6] /* t1._t variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 8
 type: SIMPLE_ASSIGN
 t1._t_dummy = 0.0
 */
void StategraphSample_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  data->localData[0]->realVars[7] /* t1._t_dummy variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 9
 type: SIMPLE_ASSIGN
 t1._t_start = 0.0
 */
void StategraphSample_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  data->localData[0]->realVars[8] /* t1._t_start variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 10
 type: SIMPLE_ASSIGN
 t1._condition = u > 0.5
 */
void StategraphSample_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  modelica_boolean tmp0;
  tmp0 = Greater(data->localData[0]->realVars[11] /* u variable */,0.5);
  data->localData[0]->booleanVars[11] /* t1._condition DISCRETE */ = tmp0;
  TRACE_POP
}

/*
 equation index: 11
 type: SIMPLE_ASSIGN
 step1._active = false
 */
void StategraphSample_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  data->localData[0]->booleanVars[7] /* step1._active DISCRETE */ = 0;
  TRACE_POP
}

/*
 equation index: 12
 type: SIMPLE_ASSIGN
 step1._localActive = step1.active
 */
void StategraphSample_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  data->localData[0]->booleanVars[8] /* step1._localActive DISCRETE */ = data->localData[0]->booleanVars[7] /* step1._active DISCRETE */;
  TRACE_POP
}

/*
 equation index: 13
 type: SIMPLE_ASSIGN
 $PRE._step1._newActive = step1.localActive
 */
void StategraphSample_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  data->simulationInfo->booleanVarsPre[9] /* step1._newActive DISCRETE */ = data->localData[0]->booleanVars[8] /* step1._localActive DISCRETE */;
  TRACE_POP
}

/*
 equation index: 14
 type: SIMPLE_ASSIGN
 $PRE._step1._localActive = $PRE.step1.newActive
 */
void StategraphSample_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  data->simulationInfo->booleanVarsPre[8] /* step1._localActive DISCRETE */ = data->simulationInfo->booleanVarsPre[9] /* step1._newActive DISCRETE */;
  TRACE_POP
}

/*
 equation index: 15
 type: SIMPLE_ASSIGN
 $PRE._step1._oldActive = $PRE.step1.localActive
 */
void StategraphSample_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  data->simulationInfo->booleanVarsPre[10] /* step1._oldActive DISCRETE */ = data->simulationInfo->booleanVarsPre[8] /* step1._localActive DISCRETE */;
  TRACE_POP
}

/*
 equation index: 16
 type: SIMPLE_ASSIGN
 step1._oldActive = $PRE.step1.oldActive
 */
void StategraphSample_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  data->localData[0]->booleanVars[10] /* step1._oldActive DISCRETE */ = data->simulationInfo->booleanVarsPre[10] /* step1._oldActive DISCRETE */;
  TRACE_POP
}

/*
 equation index: 17
 type: SIMPLE_ASSIGN
 step1._outerStatePort._subgraphStatePort._activeSteps = if step1.localActive then 1.0 else 0.0
 */
void StategraphSample_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  data->localData[0]->realVars[5] /* step1._outerStatePort._subgraphStatePort._activeSteps variable */ = (data->localData[0]->booleanVars[8] /* step1._localActive DISCRETE */?1.0:0.0);
  TRACE_POP
}

/*
 equation index: 18
 type: SIMPLE_ASSIGN
 $PRE._t2._t_start = time
 */
void StategraphSample_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  data->simulationInfo->realVarsPre[13] /* t2._t_start DISCRETE */ = data->localData[0]->timeValue;
  TRACE_POP
}

/*
 equation index: 19
 type: SIMPLE_ASSIGN
 t2._t_start = $PRE.t2.t_start
 */
void StategraphSample_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  data->localData[0]->realVars[13] /* t2._t_start DISCRETE */ = data->simulationInfo->realVarsPre[13] /* t2._t_start DISCRETE */;
  TRACE_POP
}

/*
 equation index: 20
 type: SIMPLE_ASSIGN
 t2._t_dummy = time - t2.t_start
 */
void StategraphSample_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  data->localData[0]->realVars[10] /* t2._t_dummy variable */ = data->localData[0]->timeValue - data->localData[0]->realVars[13] /* t2._t_start DISCRETE */;
  TRACE_POP
}

/*
 equation index: 21
 type: SIMPLE_ASSIGN
 s1._active = true
 */
void StategraphSample_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  data->localData[0]->booleanVars[1] /* s1._active DISCRETE */ = 1;
  TRACE_POP
}

/*
 equation index: 22
 type: SIMPLE_ASSIGN
 s1._localActive = s1.active
 */
void StategraphSample_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  data->localData[0]->booleanVars[2] /* s1._localActive DISCRETE */ = data->localData[0]->booleanVars[1] /* s1._active DISCRETE */;
  TRACE_POP
}

/*
 equation index: 23
 type: SIMPLE_ASSIGN
 $PRE._s1._newActive = s1.localActive
 */
void StategraphSample_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  data->simulationInfo->booleanVarsPre[3] /* s1._newActive DISCRETE */ = data->localData[0]->booleanVars[2] /* s1._localActive DISCRETE */;
  TRACE_POP
}

/*
 equation index: 24
 type: SIMPLE_ASSIGN
 $PRE._s1._localActive = $PRE.s1.newActive
 */
void StategraphSample_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  data->simulationInfo->booleanVarsPre[2] /* s1._localActive DISCRETE */ = data->simulationInfo->booleanVarsPre[3] /* s1._newActive DISCRETE */;
  TRACE_POP
}

/*
 equation index: 25
 type: SIMPLE_ASSIGN
 $PRE._s1._oldActive = $PRE.s1.localActive
 */
void StategraphSample_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  data->simulationInfo->booleanVarsPre[4] /* s1._oldActive DISCRETE */ = data->simulationInfo->booleanVarsPre[2] /* s1._localActive DISCRETE */;
  TRACE_POP
}

/*
 equation index: 26
 type: SIMPLE_ASSIGN
 s1._oldActive = $PRE.s1.oldActive
 */
void StategraphSample_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  data->localData[0]->booleanVars[4] /* s1._oldActive DISCRETE */ = data->simulationInfo->booleanVarsPre[4] /* s1._oldActive DISCRETE */;
  TRACE_POP
}

/*
 equation index: 27
 type: SIMPLE_ASSIGN
 s1._outerStatePort._subgraphStatePort._activeSteps = if s1.localActive then 1.0 else 0.0
 */
void StategraphSample_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  data->localData[0]->realVars[2] /* s1._outerStatePort._subgraphStatePort._activeSteps variable */ = (data->localData[0]->booleanVars[2] /* s1._localActive DISCRETE */?1.0:0.0);
  TRACE_POP
}

/*
 equation index: 28
 type: SIMPLE_ASSIGN
 stateGraphRoot._subgraphStatePort._activeSteps = (-s1.outerStatePort.subgraphStatePort.activeSteps) - step1.outerStatePort.subgraphStatePort.activeSteps
 */
void StategraphSample_eqFunction_28(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,28};
  data->localData[0]->realVars[3] /* stateGraphRoot._subgraphStatePort._activeSteps variable */ = (-data->localData[0]->realVars[2] /* s1._outerStatePort._subgraphStatePort._activeSteps variable */) - data->localData[0]->realVars[5] /* step1._outerStatePort._subgraphStatePort._activeSteps variable */;
  TRACE_POP
}

/*
 equation index: 29
 type: SIMPLE_ASSIGN
 stateGraphRoot._activeSteps = -integer(stateGraphRoot.subgraphStatePort.activeSteps)
 */
void StategraphSample_eqFunction_29(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,29};
  data->localData[0]->integerVars[0] /* stateGraphRoot._activeSteps DISCRETE */ = (-((modelica_integer)floor(data->localData[0]->realVars[3] /* stateGraphRoot._subgraphStatePort._activeSteps variable */)));
  TRACE_POP
}

/*
 equation index: 30
 type: SIMPLE_ASSIGN
 t1._enableFire = t1.condition and s1.localActive and not step1.localActive
 */
void StategraphSample_eqFunction_30(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,30};
  data->localData[0]->booleanVars[12] /* t1._enableFire DISCRETE */ = ((data->localData[0]->booleanVars[11] /* t1._condition DISCRETE */ && data->localData[0]->booleanVars[2] /* s1._localActive DISCRETE */) && (!data->localData[0]->booleanVars[8] /* step1._localActive DISCRETE */));
  TRACE_POP
}

/*
 equation index: 31
 type: SIMPLE_ASSIGN
 t2._enableFire = step1.localActive and not s1.localActive
 */
void StategraphSample_eqFunction_31(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,31};
  data->localData[0]->booleanVars[14] /* t2._enableFire DISCRETE */ = (data->localData[0]->booleanVars[8] /* step1._localActive DISCRETE */ && (!data->localData[0]->booleanVars[2] /* s1._localActive DISCRETE */));
  TRACE_POP
}

/*
 equation index: 32
 type: SIMPLE_ASSIGN
 $whenCondition1 = t2.enableFire
 */
void StategraphSample_eqFunction_32(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,32};
  data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ = data->localData[0]->booleanVars[14] /* t2._enableFire DISCRETE */;
  TRACE_POP
}

/*
 equation index: 33
 type: SIMPLE_ASSIGN
 t2._t = if t2.enableFire then t2.t_dummy else 0.0
 */
void StategraphSample_eqFunction_33(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,33};
  data->localData[0]->realVars[9] /* t2._t variable */ = (data->localData[0]->booleanVars[14] /* t2._enableFire DISCRETE */?data->localData[0]->realVars[10] /* t2._t_dummy variable */:0.0);
  TRACE_POP
}

/*
 equation index: 34
 type: SIMPLE_ASSIGN
 t2._fire = t2.enableFire and time >= t2.t_start + t2.waitTime
 */
void StategraphSample_eqFunction_34(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,34};
  modelica_boolean tmp1;
  tmp1 = GreaterEq(data->localData[0]->timeValue,data->localData[0]->realVars[13] /* t2._t_start DISCRETE */ + data->simulationInfo->realParameter[1] /* t2._waitTime PARAM */);
  data->localData[0]->booleanVars[15] /* t2._fire DISCRETE */ = (data->localData[0]->booleanVars[14] /* t2._enableFire DISCRETE */ && tmp1);
  TRACE_POP
}

/*
 equation index: 35
 type: SIMPLE_ASSIGN
 s1._newActive = Modelica.StateGraph.Temporary.anyTrue({t2.fire}) or s1.localActive and not Modelica.StateGraph.Temporary.anyTrue({t1.enableFire})
 */
void StategraphSample_eqFunction_35(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,35};
  boolean_array tmp2;
  boolean_array tmp3;
  array_alloc_scalar_boolean_array(&tmp2, 1, (modelica_boolean)data->localData[0]->booleanVars[15] /* t2._fire DISCRETE */);
  array_alloc_scalar_boolean_array(&tmp3, 1, (modelica_boolean)data->localData[0]->booleanVars[12] /* t1._enableFire DISCRETE */);
  data->localData[0]->booleanVars[3] /* s1._newActive DISCRETE */ = (omc_Modelica_StateGraph_Temporary_anyTrue(threadData, tmp2) || (data->localData[0]->booleanVars[2] /* s1._localActive DISCRETE */ && (!omc_Modelica_StateGraph_Temporary_anyTrue(threadData, tmp3))));
  TRACE_POP
}

/*
 equation index: 36
 type: SIMPLE_ASSIGN
 step1._newActive = Modelica.StateGraph.Temporary.anyTrue({t1.enableFire}) or step1.localActive and not Modelica.StateGraph.Temporary.anyTrue({t2.fire})
 */
void StategraphSample_eqFunction_36(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,36};
  boolean_array tmp4;
  boolean_array tmp5;
  array_alloc_scalar_boolean_array(&tmp4, 1, (modelica_boolean)data->localData[0]->booleanVars[12] /* t1._enableFire DISCRETE */);
  array_alloc_scalar_boolean_array(&tmp5, 1, (modelica_boolean)data->localData[0]->booleanVars[15] /* t2._fire DISCRETE */);
  data->localData[0]->booleanVars[9] /* step1._newActive DISCRETE */ = (omc_Modelica_StateGraph_Temporary_anyTrue(threadData, tmp4) || (data->localData[0]->booleanVars[8] /* step1._localActive DISCRETE */ && (!omc_Modelica_StateGraph_Temporary_anyTrue(threadData, tmp5))));
  TRACE_POP
}

/*
 equation index: 37
 type: SIMPLE_ASSIGN
 y = if s1.localActive then 0.0 else 1.0
 */
void StategraphSample_eqFunction_37(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,37};
  data->localData[0]->realVars[12] /* y variable */ = (data->localData[0]->booleanVars[2] /* s1._localActive DISCRETE */?0.0:1.0);
  TRACE_POP
}

/*
 equation index: 38
 type: SIMPLE_ASSIGN
 $PRE._t2._enableFire = false
 */
void StategraphSample_eqFunction_38(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,38};
  data->simulationInfo->booleanVarsPre[14] /* t2._enableFire DISCRETE */ = 0;
  TRACE_POP
}

/*
 equation index: 39
 type: SIMPLE_ASSIGN
 $PRE._t1._enableFire = false
 */
void StategraphSample_eqFunction_39(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,39};
  data->simulationInfo->booleanVarsPre[12] /* t1._enableFire DISCRETE */ = 0;
  TRACE_POP
}
void StategraphSample_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  StategraphSample_eqFunction_1(data, threadData);
  StategraphSample_eqFunction_2(data, threadData);
  StategraphSample_eqFunction_3(data, threadData);
  StategraphSample_eqFunction_4(data, threadData);
  StategraphSample_eqFunction_5(data, threadData);
  StategraphSample_eqFunction_6(data, threadData);
  StategraphSample_eqFunction_7(data, threadData);
  StategraphSample_eqFunction_8(data, threadData);
  StategraphSample_eqFunction_9(data, threadData);
  StategraphSample_eqFunction_10(data, threadData);
  StategraphSample_eqFunction_11(data, threadData);
  StategraphSample_eqFunction_12(data, threadData);
  StategraphSample_eqFunction_13(data, threadData);
  StategraphSample_eqFunction_14(data, threadData);
  StategraphSample_eqFunction_15(data, threadData);
  StategraphSample_eqFunction_16(data, threadData);
  StategraphSample_eqFunction_17(data, threadData);
  StategraphSample_eqFunction_18(data, threadData);
  StategraphSample_eqFunction_19(data, threadData);
  StategraphSample_eqFunction_20(data, threadData);
  StategraphSample_eqFunction_21(data, threadData);
  StategraphSample_eqFunction_22(data, threadData);
  StategraphSample_eqFunction_23(data, threadData);
  StategraphSample_eqFunction_24(data, threadData);
  StategraphSample_eqFunction_25(data, threadData);
  StategraphSample_eqFunction_26(data, threadData);
  StategraphSample_eqFunction_27(data, threadData);
  StategraphSample_eqFunction_28(data, threadData);
  StategraphSample_eqFunction_29(data, threadData);
  StategraphSample_eqFunction_30(data, threadData);
  StategraphSample_eqFunction_31(data, threadData);
  StategraphSample_eqFunction_32(data, threadData);
  StategraphSample_eqFunction_33(data, threadData);
  StategraphSample_eqFunction_34(data, threadData);
  StategraphSample_eqFunction_35(data, threadData);
  StategraphSample_eqFunction_36(data, threadData);
  StategraphSample_eqFunction_37(data, threadData);
  StategraphSample_eqFunction_38(data, threadData);
  StategraphSample_eqFunction_39(data, threadData);
  TRACE_POP
}


int StategraphSample_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  StategraphSample_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int StategraphSample_functionInitialEquations_lambda0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}
int StategraphSample_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif

