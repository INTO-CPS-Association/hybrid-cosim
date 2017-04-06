/* Linear Systems */
#include "PW_PowerSystem_model.h"
#include "PW_PowerSystem_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* initial linear systems */

/*
 equation index: 37
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._n2._i = (-idealCommutingSwitch2.s2) * (if convertToBoolean.y then 1.0 else idealCommutingSwitch2.Goff)
 */
void PW_PowerSystem_eqFunction_37(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,37};
  data->localData[0]->realVars[22] /* idealCommutingSwitch2._n2._i variable */ = ((-data->localData[0]->realVars[25] /* idealCommutingSwitch2._s2 variable */)) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?1.0:data->simulationInfo->realParameter[6] /* idealCommutingSwitch2._Goff PARAM */));
  TRACE_POP
}
/*
 equation index: 38
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._n1._i = (-idealCommutingSwitch2.s1) * (if convertToBoolean.y then idealCommutingSwitch2.Goff else 1.0)
 */
void PW_PowerSystem_eqFunction_38(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,38};
  data->localData[0]->realVars[21] /* idealCommutingSwitch2._n1._i variable */ = ((-data->localData[0]->realVars[24] /* idealCommutingSwitch2._s1 variable */)) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?data->simulationInfo->realParameter[6] /* idealCommutingSwitch2._Goff PARAM */:1.0));
  TRACE_POP
}
/*
 equation index: 39
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._p._v = idealCommutingSwitch2.s1 * (if convertToBoolean.y then 1.0 else idealCommutingSwitch2.Ron) + up_voltage.V
 */
void PW_PowerSystem_eqFunction_39(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,39};
  data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */ = (data->localData[0]->realVars[24] /* idealCommutingSwitch2._s1 variable */) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?1.0:data->simulationInfo->realParameter[7] /* idealCommutingSwitch2._Ron PARAM */)) + data->simulationInfo->realParameter[103] /* up_voltage._V PARAM */;
  TRACE_POP
}

void residualFunc47(void** dataIn, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = (DATA*) ((void**)dataIn[0]);
  threadData_t *threadData = (threadData_t*) ((void**)dataIn[1]);
  const int equationIndexes[2] = {1,47};
  data->localData[0]->realVars[24] /* idealCommutingSwitch2._s1 variable */ = xloc[0];
  data->localData[0]->realVars[25] /* idealCommutingSwitch2._s2 variable */ = xloc[1];
  PW_PowerSystem_eqFunction_37(data, threadData);

  PW_PowerSystem_eqFunction_38(data, threadData);

  PW_PowerSystem_eqFunction_39(data, threadData);
  res[0] = (data->localData[0]->realVars[25] /* idealCommutingSwitch2._s2 variable */) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?data->simulationInfo->realParameter[7] /* idealCommutingSwitch2._Ron PARAM */:1.0)) - data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */;

  res[1] = data->localData[0]->realVars[21] /* idealCommutingSwitch2._n1._i variable */ + data->localData[0]->realVars[22] /* idealCommutingSwitch2._n2._i variable */ + data->localData[0]->realVars[2] /* motor._la._i STATE(1) */;
  TRACE_POP
}
void initializeStaticLSData47(void *inData, threadData_t *threadData, void *systemData)
{
  DATA* data = (DATA*) inData;
  LINEAR_SYSTEM_DATA* linearSystemData = (LINEAR_SYSTEM_DATA*) systemData;
  int i=0;
  /* static ls data for idealCommutingSwitch2.s1 */
  linearSystemData->nominal[i] = data->modelData->realVarsData[24].attribute /* idealCommutingSwitch2._s1 */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[24].attribute /* idealCommutingSwitch2._s1 */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[24].attribute /* idealCommutingSwitch2._s1 */.max;
  /* static ls data for idealCommutingSwitch2.s2 */
  linearSystemData->nominal[i] = data->modelData->realVarsData[25].attribute /* idealCommutingSwitch2._s2 */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[25].attribute /* idealCommutingSwitch2._s2 */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[25].attribute /* idealCommutingSwitch2._s2 */.max;
}


/*
 equation index: 67
 type: SIMPLE_ASSIGN
 idealCommutingSwitch1._n2._i = (-idealCommutingSwitch1.s2) * (if greaterThreshold1.y then 1.0 else idealCommutingSwitch1.Goff)
 */
void PW_PowerSystem_eqFunction_67(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,67};
  data->localData[0]->realVars[17] /* idealCommutingSwitch1._n2._i variable */ = ((-data->localData[0]->realVars[19] /* idealCommutingSwitch1._s2 variable */)) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?1.0:data->simulationInfo->realParameter[3] /* idealCommutingSwitch1._Goff PARAM */));
  TRACE_POP
}
/*
 equation index: 68
 type: SIMPLE_ASSIGN
 arm_sensor._p._v = idealCommutingSwitch1.s2 * (if greaterThreshold1.y then idealCommutingSwitch1.Ron else 1.0)
 */
void PW_PowerSystem_eqFunction_68(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,68};
  data->localData[0]->realVars[13] /* arm_sensor._p._v variable */ = (data->localData[0]->realVars[19] /* idealCommutingSwitch1._s2 variable */) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?data->simulationInfo->realParameter[4] /* idealCommutingSwitch1._Ron PARAM */:1.0));
  TRACE_POP
}
/*
 equation index: 69
 type: SIMPLE_ASSIGN
 idealCommutingSwitch1._n1._i = (-arm_current) - idealCommutingSwitch1.n2.i
 */
void PW_PowerSystem_eqFunction_69(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,69};
  data->localData[0]->realVars[16] /* idealCommutingSwitch1._n1._i variable */ = (-data->localData[0]->realVars[12] /* arm_current variable */) - data->localData[0]->realVars[17] /* idealCommutingSwitch1._n2._i variable */;
  TRACE_POP
}

void residualFunc76(void** dataIn, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = (DATA*) ((void**)dataIn[0]);
  threadData_t *threadData = (threadData_t*) ((void**)dataIn[1]);
  const int equationIndexes[2] = {1,76};
  data->localData[0]->realVars[19] /* idealCommutingSwitch1._s2 variable */ = xloc[0];
  data->localData[0]->realVars[18] /* idealCommutingSwitch1._s1 variable */ = xloc[1];
  PW_PowerSystem_eqFunction_67(data, threadData);

  PW_PowerSystem_eqFunction_68(data, threadData);

  PW_PowerSystem_eqFunction_69(data, threadData);
  res[0] = ((-data->localData[0]->realVars[18] /* idealCommutingSwitch1._s1 variable */)) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?data->simulationInfo->realParameter[3] /* idealCommutingSwitch1._Goff PARAM */:1.0)) - data->localData[0]->realVars[16] /* idealCommutingSwitch1._n1._i variable */;

  res[1] = data->localData[0]->realVars[13] /* arm_sensor._p._v variable */ + (-data->simulationInfo->realParameter[103] /* up_voltage._V PARAM */) - ((data->localData[0]->realVars[18] /* idealCommutingSwitch1._s1 variable */) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?1.0:data->simulationInfo->realParameter[4] /* idealCommutingSwitch1._Ron PARAM */)));
  TRACE_POP
}
void initializeStaticLSData76(void *inData, threadData_t *threadData, void *systemData)
{
  DATA* data = (DATA*) inData;
  LINEAR_SYSTEM_DATA* linearSystemData = (LINEAR_SYSTEM_DATA*) systemData;
  int i=0;
  /* static ls data for idealCommutingSwitch1.s2 */
  linearSystemData->nominal[i] = data->modelData->realVarsData[19].attribute /* idealCommutingSwitch1._s2 */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[19].attribute /* idealCommutingSwitch1._s2 */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[19].attribute /* idealCommutingSwitch1._s2 */.max;
  /* static ls data for idealCommutingSwitch1.s1 */
  linearSystemData->nominal[i] = data->modelData->realVarsData[18].attribute /* idealCommutingSwitch1._s1 */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[18].attribute /* idealCommutingSwitch1._s1 */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[18].attribute /* idealCommutingSwitch1._s1 */.max;
}


/*
 equation index: 91
 type: SIMPLE_ASSIGN
 motor._lesigma._v = motor.lesigma.p.v - motor.airGapDC.vei
 */
void PW_PowerSystem_eqFunction_91(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,91};
  data->localData[0]->realVars[67] /* motor._lesigma._v variable */ = data->localData[0]->realVars[66] /* motor._lesigma._p._v variable */ - data->localData[0]->realVars[29] /* motor._airGapDC._vei variable */;
  TRACE_POP
}
/*
 equation index: 92
 type: SIMPLE_ASSIGN
 der(motor._lesigma._i) = 0.3125 * motor.airGapDC.vei
 */
void PW_PowerSystem_eqFunction_92(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,92};
  data->localData[0]->realVars[9] /* der(motor._lesigma._i) DUMMY_DER */ = (0.3125) * (data->localData[0]->realVars[29] /* motor._airGapDC._vei variable */);
  TRACE_POP
}

void residualFunc96(void** dataIn, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = (DATA*) ((void**)dataIn[0]);
  threadData_t *threadData = (threadData_t*) ((void**)dataIn[1]);
  const int equationIndexes[2] = {1,96};
  data->localData[0]->realVars[29] /* motor._airGapDC._vei variable */ = xloc[0];
  PW_PowerSystem_eqFunction_91(data, threadData);

  PW_PowerSystem_eqFunction_92(data, threadData);
  res[0] = (0.8) * (data->localData[0]->realVars[9] /* der(motor._lesigma._i) DUMMY_DER */) - data->localData[0]->realVars[67] /* motor._lesigma._v variable */;
  TRACE_POP
}
void initializeStaticLSData96(void *inData, threadData_t *threadData, void *systemData)
{
  DATA* data = (DATA*) inData;
  LINEAR_SYSTEM_DATA* linearSystemData = (LINEAR_SYSTEM_DATA*) systemData;
  int i=0;
  /* static ls data for motor.airGapDC.vei */
  linearSystemData->nominal[i] = data->modelData->realVarsData[29].attribute /* motor._airGapDC._vei */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[29].attribute /* motor._airGapDC._vei */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[29].attribute /* motor._airGapDC._vei */.max;
}
/* initial_lambda0 linear systems */
/* parameter linear systems */
/* model linear systems */

/*
 equation index: 126
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._n1._i = (-idealCommutingSwitch2.s1) * (if convertToBoolean.y then idealCommutingSwitch2.Goff else 1.0)
 */
void PW_PowerSystem_eqFunction_126(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,126};
  data->localData[0]->realVars[21] /* idealCommutingSwitch2._n1._i variable */ = ((-data->localData[0]->realVars[24] /* idealCommutingSwitch2._s1 variable */)) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?data->simulationInfo->realParameter[6] /* idealCommutingSwitch2._Goff PARAM */:1.0));
  TRACE_POP
}
/*
 equation index: 127
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._p._v = idealCommutingSwitch2.s1 * (if convertToBoolean.y then 1.0 else idealCommutingSwitch2.Ron) + up_voltage.V
 */
void PW_PowerSystem_eqFunction_127(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,127};
  data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */ = (data->localData[0]->realVars[24] /* idealCommutingSwitch2._s1 variable */) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?1.0:data->simulationInfo->realParameter[7] /* idealCommutingSwitch2._Ron PARAM */)) + data->simulationInfo->realParameter[103] /* up_voltage._V PARAM */;
  TRACE_POP
}
/*
 equation index: 128
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._n2._i = (-idealCommutingSwitch2.s2) * (if convertToBoolean.y then 1.0 else idealCommutingSwitch2.Goff)
 */
void PW_PowerSystem_eqFunction_128(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,128};
  data->localData[0]->realVars[22] /* idealCommutingSwitch2._n2._i variable */ = ((-data->localData[0]->realVars[25] /* idealCommutingSwitch2._s2 variable */)) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?1.0:data->simulationInfo->realParameter[6] /* idealCommutingSwitch2._Goff PARAM */));
  TRACE_POP
}

void residualFunc136(void** dataIn, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = (DATA*) ((void**)dataIn[0]);
  threadData_t *threadData = (threadData_t*) ((void**)dataIn[1]);
  const int equationIndexes[2] = {1,136};
  data->localData[0]->realVars[24] /* idealCommutingSwitch2._s1 variable */ = xloc[0];
  data->localData[0]->realVars[25] /* idealCommutingSwitch2._s2 variable */ = xloc[1];
  PW_PowerSystem_eqFunction_126(data, threadData);

  PW_PowerSystem_eqFunction_127(data, threadData);

  PW_PowerSystem_eqFunction_128(data, threadData);
  res[0] = data->localData[0]->realVars[21] /* idealCommutingSwitch2._n1._i variable */ + data->localData[0]->realVars[22] /* idealCommutingSwitch2._n2._i variable */ + data->localData[0]->realVars[2] /* motor._la._i STATE(1) */;

  res[1] = (data->localData[0]->realVars[25] /* idealCommutingSwitch2._s2 variable */) * ((data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */?data->simulationInfo->realParameter[7] /* idealCommutingSwitch2._Ron PARAM */:1.0)) - data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */;
  TRACE_POP
}
void initializeStaticLSData136(void *inData, threadData_t *threadData, void *systemData)
{
  DATA* data = (DATA*) inData;
  LINEAR_SYSTEM_DATA* linearSystemData = (LINEAR_SYSTEM_DATA*) systemData;
  int i=0;
  /* static ls data for idealCommutingSwitch2.s1 */
  linearSystemData->nominal[i] = data->modelData->realVarsData[24].attribute /* idealCommutingSwitch2._s1 */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[24].attribute /* idealCommutingSwitch2._s1 */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[24].attribute /* idealCommutingSwitch2._s1 */.max;
  /* static ls data for idealCommutingSwitch2.s2 */
  linearSystemData->nominal[i] = data->modelData->realVarsData[25].attribute /* idealCommutingSwitch2._s2 */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[25].attribute /* idealCommutingSwitch2._s2 */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[25].attribute /* idealCommutingSwitch2._s2 */.max;
}


/*
 equation index: 157
 type: SIMPLE_ASSIGN
 idealCommutingSwitch1._n2._i = (-idealCommutingSwitch1.s2) * (if greaterThreshold1.y then 1.0 else idealCommutingSwitch1.Goff)
 */
void PW_PowerSystem_eqFunction_157(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,157};
  data->localData[0]->realVars[17] /* idealCommutingSwitch1._n2._i variable */ = ((-data->localData[0]->realVars[19] /* idealCommutingSwitch1._s2 variable */)) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?1.0:data->simulationInfo->realParameter[3] /* idealCommutingSwitch1._Goff PARAM */));
  TRACE_POP
}
/*
 equation index: 158
 type: SIMPLE_ASSIGN
 arm_sensor._p._v = idealCommutingSwitch1.s2 * (if greaterThreshold1.y then idealCommutingSwitch1.Ron else 1.0)
 */
void PW_PowerSystem_eqFunction_158(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,158};
  data->localData[0]->realVars[13] /* arm_sensor._p._v variable */ = (data->localData[0]->realVars[19] /* idealCommutingSwitch1._s2 variable */) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?data->simulationInfo->realParameter[4] /* idealCommutingSwitch1._Ron PARAM */:1.0));
  TRACE_POP
}
/*
 equation index: 159
 type: SIMPLE_ASSIGN
 idealCommutingSwitch1._n1._i = (-arm_current) - idealCommutingSwitch1.n2.i
 */
void PW_PowerSystem_eqFunction_159(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,159};
  data->localData[0]->realVars[16] /* idealCommutingSwitch1._n1._i variable */ = (-data->localData[0]->realVars[12] /* arm_current variable */) - data->localData[0]->realVars[17] /* idealCommutingSwitch1._n2._i variable */;
  TRACE_POP
}

void residualFunc166(void** dataIn, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = (DATA*) ((void**)dataIn[0]);
  threadData_t *threadData = (threadData_t*) ((void**)dataIn[1]);
  const int equationIndexes[2] = {1,166};
  data->localData[0]->realVars[19] /* idealCommutingSwitch1._s2 variable */ = xloc[0];
  data->localData[0]->realVars[18] /* idealCommutingSwitch1._s1 variable */ = xloc[1];
  PW_PowerSystem_eqFunction_157(data, threadData);

  PW_PowerSystem_eqFunction_158(data, threadData);

  PW_PowerSystem_eqFunction_159(data, threadData);
  res[0] = ((-data->localData[0]->realVars[18] /* idealCommutingSwitch1._s1 variable */)) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?data->simulationInfo->realParameter[3] /* idealCommutingSwitch1._Goff PARAM */:1.0)) - data->localData[0]->realVars[16] /* idealCommutingSwitch1._n1._i variable */;

  res[1] = data->localData[0]->realVars[13] /* arm_sensor._p._v variable */ + (-data->simulationInfo->realParameter[103] /* up_voltage._V PARAM */) - ((data->localData[0]->realVars[18] /* idealCommutingSwitch1._s1 variable */) * ((data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */?1.0:data->simulationInfo->realParameter[4] /* idealCommutingSwitch1._Ron PARAM */)));
  TRACE_POP
}
void initializeStaticLSData166(void *inData, threadData_t *threadData, void *systemData)
{
  DATA* data = (DATA*) inData;
  LINEAR_SYSTEM_DATA* linearSystemData = (LINEAR_SYSTEM_DATA*) systemData;
  int i=0;
  /* static ls data for idealCommutingSwitch1.s2 */
  linearSystemData->nominal[i] = data->modelData->realVarsData[19].attribute /* idealCommutingSwitch1._s2 */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[19].attribute /* idealCommutingSwitch1._s2 */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[19].attribute /* idealCommutingSwitch1._s2 */.max;
  /* static ls data for idealCommutingSwitch1.s1 */
  linearSystemData->nominal[i] = data->modelData->realVarsData[18].attribute /* idealCommutingSwitch1._s1 */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[18].attribute /* idealCommutingSwitch1._s1 */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[18].attribute /* idealCommutingSwitch1._s1 */.max;
}


/*
 equation index: 181
 type: SIMPLE_ASSIGN
 motor._airGapDC._vei = motor.lesigma.p.v - motor.lesigma.v
 */
void PW_PowerSystem_eqFunction_181(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,181};
  data->localData[0]->realVars[29] /* motor._airGapDC._vei variable */ = data->localData[0]->realVars[66] /* motor._lesigma._p._v variable */ - data->localData[0]->realVars[67] /* motor._lesigma._v variable */;
  TRACE_POP
}
/*
 equation index: 182
 type: SIMPLE_ASSIGN
 der(motor._lesigma._i) = 1.25 * motor.lesigma.v
 */
void PW_PowerSystem_eqFunction_182(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,182};
  data->localData[0]->realVars[9] /* der(motor._lesigma._i) DUMMY_DER */ = (1.25) * (data->localData[0]->realVars[67] /* motor._lesigma._v variable */);
  TRACE_POP
}

void residualFunc186(void** dataIn, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = (DATA*) ((void**)dataIn[0]);
  threadData_t *threadData = (threadData_t*) ((void**)dataIn[1]);
  const int equationIndexes[2] = {1,186};
  data->localData[0]->realVars[67] /* motor._lesigma._v variable */ = xloc[0];
  PW_PowerSystem_eqFunction_181(data, threadData);

  PW_PowerSystem_eqFunction_182(data, threadData);
  res[0] = (3.2) * (data->localData[0]->realVars[9] /* der(motor._lesigma._i) DUMMY_DER */) - data->localData[0]->realVars[29] /* motor._airGapDC._vei variable */;
  TRACE_POP
}
void initializeStaticLSData186(void *inData, threadData_t *threadData, void *systemData)
{
  DATA* data = (DATA*) inData;
  LINEAR_SYSTEM_DATA* linearSystemData = (LINEAR_SYSTEM_DATA*) systemData;
  int i=0;
  /* static ls data for motor.lesigma.v */
  linearSystemData->nominal[i] = data->modelData->realVarsData[67].attribute /* motor._lesigma._v */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[67].attribute /* motor._lesigma._v */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[67].attribute /* motor._lesigma._v */.max;
}
/* jacobians linear systems */

/* function initialize linear systems */

void PW_PowerSystem_initialLinearSystem(int nLinearSystems, LINEAR_SYSTEM_DATA* linearSystemData)
{
  /* initial linear systems */
  assertStreamPrint(NULL, nLinearSystems > 0, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[0].equationIndex = 47;
  linearSystemData[0].size = 2;
  linearSystemData[0].nnz = 0;
  linearSystemData[0].method = 1;
  linearSystemData[0].residualFunc = residualFunc47;
  linearSystemData[0].strictTearingFunctionCall = NULL;
  linearSystemData[0].analyticalJacobianColumn = PW_PowerSystem_functionJacLSJac48_column;
  linearSystemData[0].initialAnalyticalJacobian = PW_PowerSystem_initialAnalyticJacobianLSJac48;
  linearSystemData[0].jacobianIndex = 0;
  linearSystemData[0].setA = NULL;//setLinearMatrixA47;
  linearSystemData[0].setb = NULL; //setLinearVectorb47;
  linearSystemData[0].initializeStaticLSData = initializeStaticLSData47;
  
  assertStreamPrint(NULL, nLinearSystems > 1, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[1].equationIndex = 76;
  linearSystemData[1].size = 2;
  linearSystemData[1].nnz = 0;
  linearSystemData[1].method = 1;
  linearSystemData[1].residualFunc = residualFunc76;
  linearSystemData[1].strictTearingFunctionCall = NULL;
  linearSystemData[1].analyticalJacobianColumn = PW_PowerSystem_functionJacLSJac49_column;
  linearSystemData[1].initialAnalyticalJacobian = PW_PowerSystem_initialAnalyticJacobianLSJac49;
  linearSystemData[1].jacobianIndex = 1;
  linearSystemData[1].setA = NULL;//setLinearMatrixA76;
  linearSystemData[1].setb = NULL; //setLinearVectorb76;
  linearSystemData[1].initializeStaticLSData = initializeStaticLSData76;
  
  assertStreamPrint(NULL, nLinearSystems > 2, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[2].equationIndex = 96;
  linearSystemData[2].size = 1;
  linearSystemData[2].nnz = 0;
  linearSystemData[2].method = 1;
  linearSystemData[2].residualFunc = residualFunc96;
  linearSystemData[2].strictTearingFunctionCall = NULL;
  linearSystemData[2].analyticalJacobianColumn = PW_PowerSystem_functionJacLSJac50_column;
  linearSystemData[2].initialAnalyticalJacobian = PW_PowerSystem_initialAnalyticJacobianLSJac50;
  linearSystemData[2].jacobianIndex = 2;
  linearSystemData[2].setA = NULL;//setLinearMatrixA96;
  linearSystemData[2].setb = NULL; //setLinearVectorb96;
  linearSystemData[2].initializeStaticLSData = initializeStaticLSData96;
  /* initial_lambda0 linear systems */
  /* parameter linear systems */
  /* model linear systems */
  assertStreamPrint(NULL, nLinearSystems > 3, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[3].equationIndex = 136;
  linearSystemData[3].size = 2;
  linearSystemData[3].nnz = 0;
  linearSystemData[3].method = 1;
  linearSystemData[3].residualFunc = residualFunc136;
  linearSystemData[3].strictTearingFunctionCall = NULL;
  linearSystemData[3].analyticalJacobianColumn = PW_PowerSystem_functionJacLSJac51_column;
  linearSystemData[3].initialAnalyticalJacobian = PW_PowerSystem_initialAnalyticJacobianLSJac51;
  linearSystemData[3].jacobianIndex = 3;
  linearSystemData[3].setA = NULL;//setLinearMatrixA136;
  linearSystemData[3].setb = NULL; //setLinearVectorb136;
  linearSystemData[3].initializeStaticLSData = initializeStaticLSData136;
  
  assertStreamPrint(NULL, nLinearSystems > 4, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[4].equationIndex = 166;
  linearSystemData[4].size = 2;
  linearSystemData[4].nnz = 0;
  linearSystemData[4].method = 1;
  linearSystemData[4].residualFunc = residualFunc166;
  linearSystemData[4].strictTearingFunctionCall = NULL;
  linearSystemData[4].analyticalJacobianColumn = PW_PowerSystem_functionJacLSJac52_column;
  linearSystemData[4].initialAnalyticalJacobian = PW_PowerSystem_initialAnalyticJacobianLSJac52;
  linearSystemData[4].jacobianIndex = 4;
  linearSystemData[4].setA = NULL;//setLinearMatrixA166;
  linearSystemData[4].setb = NULL; //setLinearVectorb166;
  linearSystemData[4].initializeStaticLSData = initializeStaticLSData166;
  
  assertStreamPrint(NULL, nLinearSystems > 5, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[5].equationIndex = 186;
  linearSystemData[5].size = 1;
  linearSystemData[5].nnz = 0;
  linearSystemData[5].method = 1;
  linearSystemData[5].residualFunc = residualFunc186;
  linearSystemData[5].strictTearingFunctionCall = NULL;
  linearSystemData[5].analyticalJacobianColumn = PW_PowerSystem_functionJacLSJac53_column;
  linearSystemData[5].initialAnalyticalJacobian = PW_PowerSystem_initialAnalyticJacobianLSJac53;
  linearSystemData[5].jacobianIndex = 5;
  linearSystemData[5].setA = NULL;//setLinearMatrixA186;
  linearSystemData[5].setb = NULL; //setLinearVectorb186;
  linearSystemData[5].initializeStaticLSData = initializeStaticLSData186;
  /* jacobians linear systems */
}

#if defined(__cplusplus)
}
#endif

