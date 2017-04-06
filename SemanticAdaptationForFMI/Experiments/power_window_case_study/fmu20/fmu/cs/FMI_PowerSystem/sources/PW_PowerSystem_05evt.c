/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "PW_PowerSystem_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void PW_PowerSystem_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *PW_PowerSystem_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"down_input > greaterThreshold1.threshold",
  "up_input > convertToBoolean.threshold"};
  static const int occurEqs0[] = {1,139};
  static const int occurEqs1[] = {1,125};
  static const int *occurEqs[] = {occurEqs0,occurEqs1};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */

int PW_PowerSystem_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  
  TRACE_POP
  return 0;
}

int PW_PowerSystem_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  modelica_boolean tmp5;
  modelica_boolean tmp6;
  
  data->simulationInfo->callStatistics.functionZeroCrossings++;
  
  tmp5 = GreaterZC(data->localData[0]->realVars[14] /* down_input variable */, data->simulationInfo->realParameter[2] /* greaterThreshold1._threshold PARAM */, data->simulationInfo->storedRelations[0]);
  gout[0] = (tmp5) ? 1 : -1;
  tmp6 = GreaterZC(data->localData[0]->realVars[102] /* up_input variable */, data->simulationInfo->realParameter[0] /* convertToBoolean._threshold PARAM */, data->simulationInfo->storedRelations[1]);
  gout[1] = (tmp6) ? 1 : -1;
  
  TRACE_POP
  return 0;
}

const char *PW_PowerSystem_relationDescription(int i)
{
  const char *res[] = {"down_input > greaterThreshold1.threshold",
  "up_input > convertToBoolean.threshold"};
  return res[i];
}

int PW_PowerSystem_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  modelica_boolean tmp7;
  modelica_boolean tmp8;
  
  if(evalforZeroCross) {
    tmp7 = GreaterZC(data->localData[0]->realVars[14] /* down_input variable */, data->simulationInfo->realParameter[2] /* greaterThreshold1._threshold PARAM */, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[0] = tmp7;
    tmp8 = GreaterZC(data->localData[0]->realVars[102] /* up_input variable */, data->simulationInfo->realParameter[0] /* convertToBoolean._threshold PARAM */, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[1] = tmp8;
  } else {
    data->simulationInfo->relations[0] = (data->localData[0]->realVars[14] /* down_input variable */ > data->simulationInfo->realParameter[2] /* greaterThreshold1._threshold PARAM */);
    data->simulationInfo->relations[1] = (data->localData[0]->realVars[102] /* up_input variable */ > data->simulationInfo->realParameter[0] /* convertToBoolean._threshold PARAM */);
  }
  
  TRACE_POP
  return 0;
}

int PW_PowerSystem_checkForDiscreteChanges(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int needToIterate = 0;

  infoStreamPrint(LOG_EVENTS_V, 1, "check for discrete changes at time=%.12g", data->localData[0]->timeValue);
  if(data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */ != data->simulationInfo->booleanVarsPre[0] /* convertToBoolean._y DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: convertToBoolean._y from %d to %d", data->simulationInfo->booleanVarsPre[0] /* convertToBoolean._y DISCRETE */, data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */ != data->simulationInfo->booleanVarsPre[1] /* greaterThreshold1._y DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: greaterThreshold1._y from %d to %d", data->simulationInfo->booleanVarsPre[1] /* greaterThreshold1._y DISCRETE */, data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */);
    needToIterate = 1;
  }
  if (ACTIVE_STREAM(LOG_EVENTS_V)) messageClose(LOG_EVENTS_V);
  
  TRACE_POP
  return needToIterate;
}

#if defined(__cplusplus)
}
#endif

