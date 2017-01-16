/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "StategraphSample_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void StategraphSample_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *StategraphSample_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"u > 0.5",
  "integer(stateGraphRoot.subgraphStatePort.activeSteps, 0)",
  "$whenCondition1 and time >= t2.t_start + t2.waitTime"};
  static const int occurEqs0[] = {1,44};
  static const int occurEqs1[] = {1,48};
  static const int occurEqs2[] = {1,53};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void StategraphSample_eqFunction_40(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_41(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_45(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_46(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_47(DATA* data, threadData_t *threadData);
extern void StategraphSample_eqFunction_50(DATA* data, threadData_t *threadData);

int StategraphSample_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  StategraphSample_eqFunction_40(data, threadData);

  StategraphSample_eqFunction_41(data, threadData);

  StategraphSample_eqFunction_45(data, threadData);

  StategraphSample_eqFunction_46(data, threadData);

  StategraphSample_eqFunction_47(data, threadData);

  StategraphSample_eqFunction_50(data, threadData);
  
  TRACE_POP
  return 0;
}

int StategraphSample_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  modelica_boolean tmp1;
  modelica_boolean tmp2;
  
  data->simulationInfo->callStatistics.functionZeroCrossings++;
  
  tmp1 = GreaterZC(data->localData[0]->realVars[11] /* u variable */, 0.5, data->simulationInfo->storedRelations[0]);
  gout[0] = (tmp1) ? 1 : -1;
  gout[1] = (floor(data->localData[0]->realVars[3] /* stateGraphRoot._subgraphStatePort._activeSteps variable */) != floor(data->simulationInfo->mathEventsValuePre[((modelica_integer) 0)])) ? 1 : -1;
  tmp2 = GreaterEqZC(data->localData[0]->timeValue, data->localData[0]->realVars[13] /* t2._t_start DISCRETE */ + data->simulationInfo->realParameter[1] /* t2._waitTime PARAM */, data->simulationInfo->storedRelations[1]);
  gout[2] = ((data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ && tmp2)) ? 1 : -1;
  
  TRACE_POP
  return 0;
}

const char *StategraphSample_relationDescription(int i)
{
  const char *res[] = {"u > 0.5",
  "time >= t2.t_start + t2.waitTime"};
  return res[i];
}

int StategraphSample_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  modelica_boolean tmp3;
  modelica_boolean tmp4;
  
  if(evalforZeroCross) {
    tmp3 = GreaterZC(data->localData[0]->realVars[11] /* u variable */, 0.5, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[0] = tmp3;
    tmp4 = GreaterEqZC(data->localData[0]->timeValue, data->localData[0]->realVars[13] /* t2._t_start DISCRETE */ + data->simulationInfo->realParameter[1] /* t2._waitTime PARAM */, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[1] = tmp4;
  } else {
    data->simulationInfo->relations[0] = (data->localData[0]->realVars[11] /* u variable */ > 0.5);
    data->simulationInfo->relations[1] = (data->localData[0]->timeValue >= data->localData[0]->realVars[13] /* t2._t_start DISCRETE */ + data->simulationInfo->realParameter[1] /* t2._waitTime PARAM */);
  }
  
  TRACE_POP
  return 0;
}

int StategraphSample_checkForDiscreteChanges(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int needToIterate = 0;

  infoStreamPrint(LOG_EVENTS_V, 1, "check for discrete changes at time=%.12g", data->localData[0]->timeValue);
  if(data->localData[0]->booleanVars[8] /* step1._localActive DISCRETE */ != data->simulationInfo->booleanVarsPre[8] /* step1._localActive DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: step1._localActive from %d to %d", data->simulationInfo->booleanVarsPre[8] /* step1._localActive DISCRETE */, data->localData[0]->booleanVars[8] /* step1._localActive DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[14] /* t2._enableFire DISCRETE */ != data->simulationInfo->booleanVarsPre[14] /* t2._enableFire DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: t2._enableFire from %d to %d", data->simulationInfo->booleanVarsPre[14] /* t2._enableFire DISCRETE */, data->localData[0]->booleanVars[14] /* t2._enableFire DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[2] /* s1._localActive DISCRETE */ != data->simulationInfo->booleanVarsPre[2] /* s1._localActive DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: s1._localActive from %d to %d", data->simulationInfo->booleanVarsPre[2] /* s1._localActive DISCRETE */, data->localData[0]->booleanVars[2] /* s1._localActive DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ != data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: $whenCondition1 from %d to %d", data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */, data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[3] /* s1._newActive DISCRETE */ != data->simulationInfo->booleanVarsPre[3] /* s1._newActive DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: s1._newActive from %d to %d", data->simulationInfo->booleanVarsPre[3] /* s1._newActive DISCRETE */, data->localData[0]->booleanVars[3] /* s1._newActive DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[4] /* s1._oldActive DISCRETE */ != data->simulationInfo->booleanVarsPre[4] /* s1._oldActive DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: s1._oldActive from %d to %d", data->simulationInfo->booleanVarsPre[4] /* s1._oldActive DISCRETE */, data->localData[0]->booleanVars[4] /* s1._oldActive DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[1] /* s1._active DISCRETE */ != data->simulationInfo->booleanVarsPre[1] /* s1._active DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: s1._active from %d to %d", data->simulationInfo->booleanVarsPre[1] /* s1._active DISCRETE */, data->localData[0]->booleanVars[1] /* s1._active DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[12] /* t1._enableFire DISCRETE */ != data->simulationInfo->booleanVarsPre[12] /* t1._enableFire DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: t1._enableFire from %d to %d", data->simulationInfo->booleanVarsPre[12] /* t1._enableFire DISCRETE */, data->localData[0]->booleanVars[12] /* t1._enableFire DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[11] /* t1._condition DISCRETE */ != data->simulationInfo->booleanVarsPre[11] /* t1._condition DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: t1._condition from %d to %d", data->simulationInfo->booleanVarsPre[11] /* t1._condition DISCRETE */, data->localData[0]->booleanVars[11] /* t1._condition DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[15] /* t2._fire DISCRETE */ != data->simulationInfo->booleanVarsPre[15] /* t2._fire DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: t2._fire from %d to %d", data->simulationInfo->booleanVarsPre[15] /* t2._fire DISCRETE */, data->localData[0]->booleanVars[15] /* t2._fire DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->realVars[13] /* t2._t_start DISCRETE */ != data->simulationInfo->realVarsPre[13] /* t2._t_start DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: t2._t_start from %g to %g", data->simulationInfo->realVarsPre[13] /* t2._t_start DISCRETE */, data->localData[0]->realVars[13] /* t2._t_start DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->integerVars[0] /* stateGraphRoot._activeSteps DISCRETE */ != data->simulationInfo->integerVarsPre[0] /* stateGraphRoot._activeSteps DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: stateGraphRoot._activeSteps from %ld to %ld", data->simulationInfo->integerVarsPre[0] /* stateGraphRoot._activeSteps DISCRETE */, data->localData[0]->integerVars[0] /* stateGraphRoot._activeSteps DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[9] /* step1._newActive DISCRETE */ != data->simulationInfo->booleanVarsPre[9] /* step1._newActive DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: step1._newActive from %d to %d", data->simulationInfo->booleanVarsPre[9] /* step1._newActive DISCRETE */, data->localData[0]->booleanVars[9] /* step1._newActive DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[10] /* step1._oldActive DISCRETE */ != data->simulationInfo->booleanVarsPre[10] /* step1._oldActive DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: step1._oldActive from %d to %d", data->simulationInfo->booleanVarsPre[10] /* step1._oldActive DISCRETE */, data->localData[0]->booleanVars[10] /* step1._oldActive DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[7] /* step1._active DISCRETE */ != data->simulationInfo->booleanVarsPre[7] /* step1._active DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: step1._active from %d to %d", data->simulationInfo->booleanVarsPre[7] /* step1._active DISCRETE */, data->localData[0]->booleanVars[7] /* step1._active DISCRETE */);
    needToIterate = 1;
  }
  if (ACTIVE_STREAM(LOG_EVENTS_V)) messageClose(LOG_EVENTS_V);
  
  TRACE_POP
  return needToIterate;
}

#if defined(__cplusplus)
}
#endif

