/* Main Simulation File */
#include "PW_PowerSystem_model.h"


/* dummy VARINFO and FILEINFO */
const FILE_INFO dummyFILE_INFO = omc_dummyFileInfo;
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;
#if defined(__cplusplus)
extern "C" {
#endif

int PW_PowerSystem_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->localData[0]->realVars[14] /* down_input variable */ = data->simulationInfo->inputVars[0];
  data->localData[0]->realVars[26] /* input_torque variable */ = data->simulationInfo->inputVars[1];
  data->localData[0]->realVars[102] /* up_input variable */ = data->simulationInfo->inputVars[2];
  
  TRACE_POP
  return 0;
}

int PW_PowerSystem_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[14].attribute.start;
  data->simulationInfo->inputVars[1] = data->modelData->realVarsData[26].attribute.start;
  data->simulationInfo->inputVars[2] = data->modelData->realVarsData[102].attribute.start;
  
  TRACE_POP
  return 0;
}

int PW_PowerSystem_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[14].attribute.start = data->simulationInfo->inputVars[0];
  data->modelData->realVarsData[26].attribute.start = data->simulationInfo->inputVars[1];
  data->modelData->realVarsData[102].attribute.start = data->simulationInfo->inputVars[2];
  
  TRACE_POP
  return 0;
}

int PW_PowerSystem_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[14].info.name;
  names[1] = (char *) data->modelData->realVarsData[26].info.name;
  names[2] = (char *) data->modelData->realVarsData[102].info.name;
  
  TRACE_POP
  return 0;
}

int PW_PowerSystem_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = data->localData[0]->realVars[12] /* arm_current variable */;
  data->simulationInfo->outputVars[1] = data->localData[0]->realVars[96] /* speed variable */;
  
  TRACE_POP
  return 0;
}


/*
 equation index: 121
 type: SIMPLE_ASSIGN
 motor._inertiaStator._flange_a._tau = 0.0
 */
void PW_PowerSystem_eqFunction_121(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,121};
  data->localData[0]->realVars[54] /* motor._inertiaStator._flange_a._tau variable */ = 0.0;
  TRACE_POP
}
/*
 equation index: 122
 type: SIMPLE_ASSIGN
 motor._core._wLimit = max(abs(motor.inertiaRotor.w), motor.core.coreParameters.wMin)
 */
void PW_PowerSystem_eqFunction_122(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,122};
  data->localData[0]->realVars[43] /* motor._core._wLimit variable */ = fmax(fabs(data->localData[0]->realVars[1] /* motor._inertiaRotor._w STATE(1,motor.inertiaRotor.a) */),data->simulationInfo->realParameter[39] /* motor._core._coreParameters._wMin PARAM */);
  TRACE_POP
}
/*
 equation index: 123
 type: SIMPLE_ASSIGN
 motor._airGapDC._vai = motor.airGapDC.turnsRatio * motor.airGapDC.psi_e * motor.inertiaRotor.w
 */
void PW_PowerSystem_eqFunction_123(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,123};
  data->localData[0]->realVars[28] /* motor._airGapDC._vai variable */ = (data->simulationInfo->realParameter[27] /* motor._airGapDC._turnsRatio PARAM */) * ((data->localData[0]->realVars[0] /* motor._airGapDC._psi_e STATE(1,motor.airGapDC.vei) */) * (data->localData[0]->realVars[1] /* motor._inertiaRotor._w STATE(1,motor.inertiaRotor.a) */));
  TRACE_POP
}
/*
 equation index: 124
 type: SIMPLE_ASSIGN
 motor._tauElectrical = motor.airGapDC.turnsRatio * motor.airGapDC.psi_e * motor.la.i
 */
void PW_PowerSystem_eqFunction_124(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,124};
  data->localData[0]->realVars[85] /* motor._tauElectrical variable */ = (data->simulationInfo->realParameter[27] /* motor._airGapDC._turnsRatio PARAM */) * ((data->localData[0]->realVars[0] /* motor._airGapDC._psi_e STATE(1,motor.airGapDC.vei) */) * (data->localData[0]->realVars[2] /* motor._la._i STATE(1) */));
  TRACE_POP
}
/*
 equation index: 125
 type: SIMPLE_ASSIGN
 convertToBoolean._y = up_input > convertToBoolean.threshold
 */
void PW_PowerSystem_eqFunction_125(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,125};
  modelica_boolean tmp240;
  RELATIONHYSTERESIS(tmp240, data->localData[0]->realVars[102] /* up_input variable */, data->simulationInfo->realParameter[0] /* convertToBoolean._threshold PARAM */, 1, Greater);
  data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */ = tmp240;
  TRACE_POP
}
/*
 equation index: 136
 type: LINEAR
 
 <var>idealCommutingSwitch2._s1</var>
 <var>idealCommutingSwitch2._s2</var>
 <row>

 </row>
 <matrix>
 </matrix>
 */
void PW_PowerSystem_eqFunction_136(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,136};
  /* Linear equation system */
  int retValue;
  if(ACTIVE_STREAM(LOG_DT))
      {
        infoStreamPrint(LOG_DT, 1, "Solving linear system 136 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
        messageClose(LOG_DT);
      }
  data->simulationInfo->linearSystemData[3].x[0] = data->localData[1]->realVars[24] /* idealCommutingSwitch2._s1 variable */;
  data->simulationInfo->linearSystemData[3].x[1] = data->localData[1]->realVars[25] /* idealCommutingSwitch2._s2 variable */;
  retValue = solve_linear_system(data, threadData, 3);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,136};
    throwStreamPrintWithEquationIndexes(threadData, indexes, "Solving linear system 136 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  data->localData[0]->realVars[24] /* idealCommutingSwitch2._s1 variable */ = data->simulationInfo->linearSystemData[3].x[0];
  data->localData[0]->realVars[25] /* idealCommutingSwitch2._s2 variable */ = data->simulationInfo->linearSystemData[3].x[1];
  TRACE_POP
}
/*
 equation index: 137
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._LossPower = motor.la.i * idealCommutingSwitch2.p.v + idealCommutingSwitch2.n1.i * up_voltage.V
 */
void PW_PowerSystem_eqFunction_137(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,137};
  data->localData[0]->realVars[20] /* idealCommutingSwitch2._LossPower variable */ = (data->localData[0]->realVars[2] /* motor._la._i STATE(1) */) * (data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */) + (data->localData[0]->realVars[21] /* idealCommutingSwitch2._n1._i variable */) * (data->simulationInfo->realParameter[103] /* up_voltage._V PARAM */);
  TRACE_POP
}
/*
 equation index: 138
 type: SIMPLE_ASSIGN
 motor._airGapDC._pin_ap._v = motor.airGapDC.vai + idealCommutingSwitch2.p.v
 */
void PW_PowerSystem_eqFunction_138(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,138};
  data->localData[0]->realVars[27] /* motor._airGapDC._pin_ap._v variable */ = data->localData[0]->realVars[28] /* motor._airGapDC._vai variable */ + data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */;
  TRACE_POP
}
/*
 equation index: 139
 type: SIMPLE_ASSIGN
 greaterThreshold1._y = down_input > greaterThreshold1.threshold
 */
void PW_PowerSystem_eqFunction_139(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,139};
  modelica_boolean tmp241;
  RELATIONHYSTERESIS(tmp241, data->localData[0]->realVars[14] /* down_input variable */, data->simulationInfo->realParameter[2] /* greaterThreshold1._threshold PARAM */, 0, Greater);
  data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */ = tmp241;
  TRACE_POP
}
/*
 equation index: 140
 type: SIMPLE_ASSIGN
 speed = motor.inertiaRotor.w
 */
void PW_PowerSystem_eqFunction_140(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,140};
  data->localData[0]->realVars[96] /* speed variable */ = data->localData[0]->realVars[1] /* motor._inertiaRotor._w STATE(1,motor.inertiaRotor.a) */;
  TRACE_POP
}
/*
 equation index: 141
 type: SIMPLE_ASSIGN
 motor._friction._tau = -smooth(1, if speed >= motor.friction.frictionParameters.wLinear then motor.friction.frictionParameters.tauRef * DIVISION(speed, motor.friction.frictionParameters.wRef) ^ motor.friction.frictionParameters.power_w else if speed <= (-motor.friction.frictionParameters.wLinear) then (-motor.friction.frictionParameters.tauRef) * DIVISION(-speed, motor.friction.frictionParameters.wRef) ^ motor.friction.frictionParameters.power_w else motor.friction.frictionParameters.tauLinear * DIVISION(speed, motor.friction.frictionParameters.wLinear))
 */
void PW_PowerSystem_eqFunction_141(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,141};
  modelica_boolean tmp242;
  modelica_real tmp243;
  modelica_real tmp244;
  modelica_real tmp245;
  modelica_real tmp246;
  modelica_real tmp247;
  modelica_real tmp248;
  modelica_real tmp249;
  modelica_boolean tmp250;
  modelica_real tmp251;
  modelica_real tmp252;
  modelica_real tmp253;
  modelica_real tmp254;
  modelica_real tmp255;
  modelica_real tmp256;
  modelica_real tmp257;
  modelica_boolean tmp258;
  modelica_real tmp259;
  modelica_boolean tmp260;
  modelica_real tmp261;
  tmp242 = GreaterEq(data->localData[0]->realVars[96] /* speed variable */,data->simulationInfo->realParameter[53] /* motor._friction._frictionParameters._wLinear PARAM */);
  tmp260 = (modelica_boolean)tmp242;
  if(tmp260)
  {
    tmp243 = DIVISION_SIM(data->localData[0]->realVars[96] /* speed variable */,data->simulationInfo->realParameter[54] /* motor._friction._frictionParameters._wRef PARAM */,"motor.friction.frictionParameters.wRef",equationIndexes);
    tmp244 = data->simulationInfo->realParameter[50] /* motor._friction._frictionParameters._power_w PARAM */;
    if(tmp243 < 0.0 && tmp244 != 0.0)
    {
      tmp246 = modf(tmp244, &tmp247);
      
      if(tmp246 > 0.5)
      {
        tmp246 -= 1.0;
        tmp247 += 1.0;
      }
      else if(tmp246 < -0.5)
      {
        tmp246 += 1.0;
        tmp247 -= 1.0;
      }
      
      if(fabs(tmp246) < 1e-10)
        tmp245 = pow(tmp243, tmp247);
      else
      {
        tmp249 = modf(1.0/tmp244, &tmp248);
        if(tmp249 > 0.5)
        {
          tmp249 -= 1.0;
          tmp248 += 1.0;
        }
        else if(tmp249 < -0.5)
        {
          tmp249 += 1.0;
          tmp248 -= 1.0;
        }
        if(fabs(tmp249) < 1e-10 && ((unsigned long)tmp248 & 1))
        {
          tmp245 = -pow(-tmp243, tmp246)*pow(tmp243, tmp247);
        }
        else
        {
          throwStreamPrint(threadData, "Invalid root: (%g)^(%g)", tmp243, tmp244);
        }
      }
    }
    else
    {
      tmp245 = pow(tmp243, tmp244);
    }
    if(isnan(tmp245) || isinf(tmp245))
    {
      throwStreamPrint(threadData, "Invalid root: (%g)^(%g)", tmp243, tmp244);
    }
    tmp261 = (data->simulationInfo->realParameter[52] /* motor._friction._frictionParameters._tauRef PARAM */) * (tmp245);
  }
  else
  {
    tmp250 = LessEq(data->localData[0]->realVars[96] /* speed variable */,(-data->simulationInfo->realParameter[53] /* motor._friction._frictionParameters._wLinear PARAM */));
    tmp258 = (modelica_boolean)tmp250;
    if(tmp258)
    {
      tmp251 = DIVISION_SIM((-data->localData[0]->realVars[96] /* speed variable */),data->simulationInfo->realParameter[54] /* motor._friction._frictionParameters._wRef PARAM */,"motor.friction.frictionParameters.wRef",equationIndexes);
      tmp252 = data->simulationInfo->realParameter[50] /* motor._friction._frictionParameters._power_w PARAM */;
      if(tmp251 < 0.0 && tmp252 != 0.0)
      {
        tmp254 = modf(tmp252, &tmp255);
        
        if(tmp254 > 0.5)
        {
          tmp254 -= 1.0;
          tmp255 += 1.0;
        }
        else if(tmp254 < -0.5)
        {
          tmp254 += 1.0;
          tmp255 -= 1.0;
        }
        
        if(fabs(tmp254) < 1e-10)
          tmp253 = pow(tmp251, tmp255);
        else
        {
          tmp257 = modf(1.0/tmp252, &tmp256);
          if(tmp257 > 0.5)
          {
            tmp257 -= 1.0;
            tmp256 += 1.0;
          }
          else if(tmp257 < -0.5)
          {
            tmp257 += 1.0;
            tmp256 -= 1.0;
          }
          if(fabs(tmp257) < 1e-10 && ((unsigned long)tmp256 & 1))
          {
            tmp253 = -pow(-tmp251, tmp254)*pow(tmp251, tmp255);
          }
          else
          {
            throwStreamPrint(threadData, "Invalid root: (%g)^(%g)", tmp251, tmp252);
          }
        }
      }
      else
      {
        tmp253 = pow(tmp251, tmp252);
      }
      if(isnan(tmp253) || isinf(tmp253))
      {
        throwStreamPrint(threadData, "Invalid root: (%g)^(%g)", tmp251, tmp252);
      }
      tmp259 = ((-data->simulationInfo->realParameter[52] /* motor._friction._frictionParameters._tauRef PARAM */)) * (tmp253);
    }
    else
    {
      tmp259 = (data->simulationInfo->realParameter[51] /* motor._friction._frictionParameters._tauLinear PARAM */) * (DIVISION_SIM(data->localData[0]->realVars[96] /* speed variable */,data->simulationInfo->realParameter[53] /* motor._friction._frictionParameters._wLinear PARAM */,"motor.friction.frictionParameters.wLinear",equationIndexes));
    }
    tmp261 = tmp259;
  }
  data->localData[0]->realVars[46] /* motor._friction._tau variable */ = (-tmp261);
  TRACE_POP
}
/*
 equation index: 142
 type: SIMPLE_ASSIGN
 motor._inertiaRotor._flange_b._tau = motor.friction.tau + input_torque
 */
void PW_PowerSystem_eqFunction_142(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,142};
  data->localData[0]->realVars[52] /* motor._inertiaRotor._flange_b._tau variable */ = data->localData[0]->realVars[46] /* motor._friction._tau variable */ + data->localData[0]->realVars[26] /* input_torque variable */;
  TRACE_POP
}
/*
 equation index: 143
 type: SIMPLE_ASSIGN
 motor._inertiaRotor._a = DIVISION(motor.tauElectrical + motor.inertiaRotor.flange_b.tau, motor.inertiaRotor.J)
 */
void PW_PowerSystem_eqFunction_143(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,143};
  data->localData[0]->realVars[51] /* motor._inertiaRotor._a variable */ = DIVISION_SIM(data->localData[0]->realVars[85] /* motor._tauElectrical variable */ + data->localData[0]->realVars[52] /* motor._inertiaRotor._flange_b._tau variable */,data->simulationInfo->realParameter[62] /* motor._inertiaRotor._J PARAM */,"motor.inertiaRotor.J",equationIndexes);
  TRACE_POP
}
/*
 equation index: 144
 type: SIMPLE_ASSIGN
 motor._powerBalance._powerInertiaRotor = motor.inertiaRotor.J * motor.inertiaRotor.a * motor.inertiaRotor.w
 */
void PW_PowerSystem_eqFunction_144(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,144};
  data->localData[0]->realVars[71] /* motor._powerBalance._powerInertiaRotor variable */ = (data->simulationInfo->realParameter[62] /* motor._inertiaRotor._J PARAM */) * ((data->localData[0]->realVars[51] /* motor._inertiaRotor._a variable */) * (data->localData[0]->realVars[1] /* motor._inertiaRotor._w STATE(1,motor.inertiaRotor.a) */));
  TRACE_POP
}
/*
 equation index: 145
 type: SIMPLE_ASSIGN
 der(motor._inertiaRotor._w) = motor.inertiaRotor.a
 */
void PW_PowerSystem_eqFunction_145(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,145};
  data->localData[0]->realVars[5] /* der(motor._inertiaRotor._w) STATE_DER */ = data->localData[0]->realVars[51] /* motor._inertiaRotor._a variable */;
  TRACE_POP
}
/*
 equation index: 146
 type: SIMPLE_ASSIGN
 motor._fixed._flange._tau = (-motor.friction.tau) - motor.tauElectrical
 */
void PW_PowerSystem_eqFunction_146(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,146};
  data->localData[0]->realVars[44] /* motor._fixed._flange._tau variable */ = (-data->localData[0]->realVars[46] /* motor._friction._tau variable */) - data->localData[0]->realVars[85] /* motor._tauElectrical variable */;
  TRACE_POP
}
/*
 equation index: 147
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._Q_flowFriction = (-motor.friction.tau) * speed
 */
void PW_PowerSystem_eqFunction_147(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,147};
  data->localData[0]->realVars[88] /* motor._thermalAmbient._Q_flowFriction variable */ = ((-data->localData[0]->realVars[46] /* motor._friction._tau variable */)) * (data->localData[0]->realVars[96] /* speed variable */);
  TRACE_POP
}
/*
 equation index: 148
 type: SIMPLE_ASSIGN
 der(motor._phiMechanical) = speed
 */
void PW_PowerSystem_eqFunction_148(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,148};
  data->localData[0]->realVars[7] /* der(motor._phiMechanical) STATE_DER */ = data->localData[0]->realVars[96] /* speed variable */;
  TRACE_POP
}
/*
 equation index: 149
 type: SIMPLE_ASSIGN
 motor._powerBalance._powerMechanical = (-speed) * input_torque
 */
void PW_PowerSystem_eqFunction_149(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,149};
  data->localData[0]->realVars[73] /* motor._powerBalance._powerMechanical variable */ = ((-data->localData[0]->realVars[96] /* speed variable */)) * (data->localData[0]->realVars[26] /* input_torque variable */);
  TRACE_POP
}
/*
 equation index: 150
 type: SIMPLE_ASSIGN
 der(speedSensor1._flange._phi) = speed
 */
void PW_PowerSystem_eqFunction_150(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,150};
  data->localData[0]->realVars[11] /* der(speedSensor1._flange._phi) DUMMY_DER */ = data->localData[0]->realVars[96] /* speed variable */;
  TRACE_POP
}
/*
 equation index: 151
 type: SIMPLE_ASSIGN
 motor._strayLoad._w = speed
 */
void PW_PowerSystem_eqFunction_151(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,151};
  data->localData[0]->realVars[84] /* motor._strayLoad._w variable */ = data->localData[0]->realVars[96] /* speed variable */;
  TRACE_POP
}
/*
 equation index: 152
 type: SIMPLE_ASSIGN
 der(motor._strayLoad._phi) = speed
 */
void PW_PowerSystem_eqFunction_152(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,152};
  data->localData[0]->realVars[10] /* der(motor._strayLoad._phi) DUMMY_DER */ = data->localData[0]->realVars[96] /* speed variable */;
  TRACE_POP
}
/*
 equation index: 153
 type: SIMPLE_ASSIGN
 motor._friction._w = speed
 */
void PW_PowerSystem_eqFunction_153(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,153};
  data->localData[0]->realVars[47] /* motor._friction._w variable */ = data->localData[0]->realVars[96] /* speed variable */;
  TRACE_POP
}
/*
 equation index: 154
 type: SIMPLE_ASSIGN
 der(motor._friction._phi) = speed
 */
void PW_PowerSystem_eqFunction_154(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,154};
  data->localData[0]->realVars[8] /* der(motor._friction._phi) DUMMY_DER */ = data->localData[0]->realVars[96] /* speed variable */;
  TRACE_POP
}
/*
 equation index: 155
 type: SIMPLE_ASSIGN
 motor._wMechanical = speed
 */
void PW_PowerSystem_eqFunction_155(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,155};
  data->localData[0]->realVars[95] /* motor._wMechanical variable */ = data->localData[0]->realVars[96] /* speed variable */;
  TRACE_POP
}
/*
 equation index: 156
 type: SIMPLE_ASSIGN
 arm_current = -motor.la.i
 */
void PW_PowerSystem_eqFunction_156(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,156};
  data->localData[0]->realVars[12] /* arm_current variable */ = (-data->localData[0]->realVars[2] /* motor._la._i STATE(1) */);
  TRACE_POP
}
/*
 equation index: 166
 type: LINEAR
 
 <var>idealCommutingSwitch1._s2</var>
 <var>idealCommutingSwitch1._s1</var>
 <row>

 </row>
 <matrix>
 </matrix>
 */
void PW_PowerSystem_eqFunction_166(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,166};
  /* Linear equation system */
  int retValue;
  if(ACTIVE_STREAM(LOG_DT))
      {
        infoStreamPrint(LOG_DT, 1, "Solving linear system 166 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
        messageClose(LOG_DT);
      }
  data->simulationInfo->linearSystemData[4].x[0] = data->localData[1]->realVars[19] /* idealCommutingSwitch1._s2 variable */;
  data->simulationInfo->linearSystemData[4].x[1] = data->localData[1]->realVars[18] /* idealCommutingSwitch1._s1 variable */;
  retValue = solve_linear_system(data, threadData, 4);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,166};
    throwStreamPrintWithEquationIndexes(threadData, indexes, "Solving linear system 166 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  data->localData[0]->realVars[19] /* idealCommutingSwitch1._s2 variable */ = data->simulationInfo->linearSystemData[4].x[0];
  data->localData[0]->realVars[18] /* idealCommutingSwitch1._s1 variable */ = data->simulationInfo->linearSystemData[4].x[1];
  TRACE_POP
}
/*
 equation index: 167
 type: SIMPLE_ASSIGN
 up_voltage._i = (-idealCommutingSwitch1.n1.i) - idealCommutingSwitch2.n1.i
 */
void PW_PowerSystem_eqFunction_167(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,167};
  data->localData[0]->realVars[103] /* up_voltage._i variable */ = (-data->localData[0]->realVars[16] /* idealCommutingSwitch1._n1._i variable */) - data->localData[0]->realVars[21] /* idealCommutingSwitch2._n1._i variable */;
  TRACE_POP
}
/*
 equation index: 168
 type: SIMPLE_ASSIGN
 motor._va = arm_sensor.p.v - idealCommutingSwitch2.p.v
 */
void PW_PowerSystem_eqFunction_168(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,168};
  data->localData[0]->realVars[94] /* motor._va variable */ = data->localData[0]->realVars[13] /* arm_sensor._p._v variable */ - data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */;
  TRACE_POP
}
/*
 equation index: 169
 type: SIMPLE_ASSIGN
 up_ground._p._i = up_voltage.i - (idealCommutingSwitch1.n2.i + idealCommutingSwitch2.n2.i)
 */
void PW_PowerSystem_eqFunction_169(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,169};
  data->localData[0]->realVars[100] /* up_ground._p._i variable */ = data->localData[0]->realVars[103] /* up_voltage._i variable */ - (data->localData[0]->realVars[17] /* idealCommutingSwitch1._n2._i variable */ + data->localData[0]->realVars[22] /* idealCommutingSwitch2._n2._i variable */);
  TRACE_POP
}
/*
 equation index: 170
 type: SIMPLE_ASSIGN
 idealCommutingSwitch1._LossPower = arm_current * arm_sensor.p.v + idealCommutingSwitch1.n1.i * up_voltage.V
 */
void PW_PowerSystem_eqFunction_170(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,170};
  data->localData[0]->realVars[15] /* idealCommutingSwitch1._LossPower variable */ = (data->localData[0]->realVars[12] /* arm_current variable */) * (data->localData[0]->realVars[13] /* arm_sensor._p._v variable */) + (data->localData[0]->realVars[16] /* idealCommutingSwitch1._n1._i variable */) * (data->simulationInfo->realParameter[103] /* up_voltage._V PARAM */);
  TRACE_POP
}
/*
 equation index: 171
 type: SIMPLE_ASSIGN
 motor._ra._v = (-motor.ra.R_actual) * arm_current
 */
void PW_PowerSystem_eqFunction_171(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,171};
  data->localData[0]->realVars[75] /* motor._ra._v variable */ = ((-data->localData[0]->realVars[74] /* motor._ra._R_actual variable */)) * (data->localData[0]->realVars[12] /* arm_current variable */);
  TRACE_POP
}
/*
 equation index: 172
 type: SIMPLE_ASSIGN
 motor._core._p._v = arm_sensor.p.v - motor.ra.v
 */
void PW_PowerSystem_eqFunction_172(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,172};
  data->localData[0]->realVars[41] /* motor._core._p._v variable */ = data->localData[0]->realVars[13] /* arm_sensor._p._v variable */ - data->localData[0]->realVars[75] /* motor._ra._v variable */;
  TRACE_POP
}
/*
 equation index: 173
 type: SIMPLE_ASSIGN
 motor._la._v = motor.core.p.v - motor.airGapDC.pin_ap.v
 */
void PW_PowerSystem_eqFunction_173(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,173};
  data->localData[0]->realVars[64] /* motor._la._v variable */ = data->localData[0]->realVars[41] /* motor._core._p._v variable */ - data->localData[0]->realVars[27] /* motor._airGapDC._pin_ap._v variable */;
  TRACE_POP
}
/*
 equation index: 174
 type: SIMPLE_ASSIGN
 der(motor._la._i) = DIVISION(motor.la.v, motor.la.L)
 */
void PW_PowerSystem_eqFunction_174(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,174};
  data->localData[0]->realVars[6] /* der(motor._la._i) STATE_DER */ = DIVISION_SIM(data->localData[0]->realVars[64] /* motor._la._v variable */,data->simulationInfo->realParameter[64] /* motor._la._L PARAM */,"motor.la.L",equationIndexes);
  TRACE_POP
}
/*
 equation index: 175
 type: SIMPLE_ASSIGN
 motor._core._v = motor.core.p.v - idealCommutingSwitch2.p.v
 */
void PW_PowerSystem_eqFunction_175(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,175};
  data->localData[0]->realVars[42] /* motor._core._v variable */ = data->localData[0]->realVars[41] /* motor._core._p._v variable */ - data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */;
  TRACE_POP
}
/*
 equation index: 176
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._Q_flowArmature = (-motor.ra.v) * arm_current
 */
void PW_PowerSystem_eqFunction_176(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,176};
  data->localData[0]->realVars[86] /* motor._thermalAmbient._Q_flowArmature variable */ = ((-data->localData[0]->realVars[75] /* motor._ra._v variable */)) * (data->localData[0]->realVars[12] /* arm_current variable */);
  TRACE_POP
}
/*
 equation index: 177
 type: SIMPLE_ASSIGN
 motor._powerBalance._powerArmature = (-motor.va) * arm_current
 */
void PW_PowerSystem_eqFunction_177(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,177};
  data->localData[0]->realVars[69] /* motor._powerBalance._powerArmature variable */ = ((-data->localData[0]->realVars[94] /* motor._va variable */)) * (data->localData[0]->realVars[12] /* arm_current variable */);
  TRACE_POP
}
/*
 equation index: 178
 type: SIMPLE_ASSIGN
 motor._lesigma._i = 0.3125 * motor.airGapDC.psi_e
 */
void PW_PowerSystem_eqFunction_178(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,178};
  data->localData[0]->realVars[65] /* motor._lesigma._i DUMMY_STATE */ = (0.3125) * (data->localData[0]->realVars[0] /* motor._airGapDC._psi_e STATE(1,motor.airGapDC.vei) */);
  TRACE_POP
}
/*
 equation index: 179
 type: SIMPLE_ASSIGN
 motor._re._v = motor.re.R_actual * motor.lesigma.i
 */
void PW_PowerSystem_eqFunction_179(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,179};
  data->localData[0]->realVars[77] /* motor._re._v variable */ = (data->localData[0]->realVars[76] /* motor._re._R_actual variable */) * (data->localData[0]->realVars[65] /* motor._lesigma._i DUMMY_STATE */);
  TRACE_POP
}
/*
 equation index: 180
 type: SIMPLE_ASSIGN
 motor._lesigma._p._v = dc_motor_power.V - motor.re.v
 */
void PW_PowerSystem_eqFunction_180(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,180};
  data->localData[0]->realVars[66] /* motor._lesigma._p._v variable */ = data->simulationInfo->realParameter[1] /* dc_motor_power._V PARAM */ - data->localData[0]->realVars[77] /* motor._re._v variable */;
  TRACE_POP
}
/*
 equation index: 186
 type: LINEAR
 
 <var>motor._lesigma._v</var>
 <row>

 </row>
 <matrix>
 </matrix>
 */
void PW_PowerSystem_eqFunction_186(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,186};
  /* Linear equation system */
  int retValue;
  if(ACTIVE_STREAM(LOG_DT))
      {
        infoStreamPrint(LOG_DT, 1, "Solving linear system 186 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
        messageClose(LOG_DT);
      }
  data->simulationInfo->linearSystemData[5].x[0] = data->localData[1]->realVars[67] /* motor._lesigma._v variable */;
  retValue = solve_linear_system(data, threadData, 5);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,186};
    throwStreamPrintWithEquationIndexes(threadData, indexes, "Solving linear system 186 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  data->localData[0]->realVars[67] /* motor._lesigma._v variable */ = data->simulationInfo->linearSystemData[5].x[0];
  TRACE_POP
}
/*
 equation index: 187
 type: SIMPLE_ASSIGN
 der(motor._airGapDC._psi_e) = motor.airGapDC.vei
 */
void PW_PowerSystem_eqFunction_187(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,187};
  data->localData[0]->realVars[4] /* der(motor._airGapDC._psi_e) STATE_DER */ = data->localData[0]->realVars[29] /* motor._airGapDC._vei variable */;
  TRACE_POP
}
/*
 equation index: 188
 type: SIMPLE_ASSIGN
 motor._compoundDCExcitation._vse = motor.airGapDC.vei * motor.compoundDCExcitation.excitationTurnsRatio
 */
void PW_PowerSystem_eqFunction_188(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,188};
  data->localData[0]->realVars[35] /* motor._compoundDCExcitation._vse variable */ = (data->localData[0]->realVars[29] /* motor._airGapDC._vei variable */) * (data->simulationInfo->realParameter[34] /* motor._compoundDCExcitation._excitationTurnsRatio PARAM */);
  TRACE_POP
}
/*
 equation index: 189
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._Q_flowExcitation = motor.re.v * motor.lesigma.i
 */
void PW_PowerSystem_eqFunction_189(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,189};
  data->localData[0]->realVars[87] /* motor._thermalAmbient._Q_flowExcitation variable */ = (data->localData[0]->realVars[77] /* motor._re._v variable */) * (data->localData[0]->realVars[65] /* motor._lesigma._i DUMMY_STATE */);
  TRACE_POP
}
/*
 equation index: 190
 type: SIMPLE_ASSIGN
 motor._powerBalance._lossPowerTotal = motor.thermalAmbient.Q_flowArmature + motor.thermalAmbient.Q_flowFriction + motor.thermalAmbient.Q_flowExcitation
 */
void PW_PowerSystem_eqFunction_190(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,190};
  data->localData[0]->realVars[68] /* motor._powerBalance._lossPowerTotal variable */ = data->localData[0]->realVars[86] /* motor._thermalAmbient._Q_flowArmature variable */ + data->localData[0]->realVars[88] /* motor._thermalAmbient._Q_flowFriction variable */ + data->localData[0]->realVars[87] /* motor._thermalAmbient._Q_flowExcitation variable */;
  TRACE_POP
}
/*
 equation index: 191
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._Q_flowTotal = motor.thermalAmbient.Q_flowArmature + motor.thermalAmbient.Q_flowFriction + motor.thermalAmbient.Q_flowExcitation
 */
void PW_PowerSystem_eqFunction_191(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,191};
  data->localData[0]->realVars[89] /* motor._thermalAmbient._Q_flowTotal variable */ = data->localData[0]->realVars[86] /* motor._thermalAmbient._Q_flowArmature variable */ + data->localData[0]->realVars[88] /* motor._thermalAmbient._Q_flowFriction variable */ + data->localData[0]->realVars[87] /* motor._thermalAmbient._Q_flowExcitation variable */;
  TRACE_POP
}
/*
 equation index: 192
 type: SIMPLE_ASSIGN
 motor._powerBalance._powerExcitation = dc_motor_power.V * motor.lesigma.i
 */
void PW_PowerSystem_eqFunction_192(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,192};
  data->localData[0]->realVars[70] /* motor._powerBalance._powerExcitation variable */ = (data->simulationInfo->realParameter[1] /* dc_motor_power._V PARAM */) * (data->localData[0]->realVars[65] /* motor._lesigma._i DUMMY_STATE */);
  TRACE_POP
}
/*
 equation index: 193
 type: SIMPLE_ASSIGN
 speedSensor1._flange._phi = motor.phiMechanical + motor.fixed.phi0
 */
void PW_PowerSystem_eqFunction_193(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,193};
  data->localData[0]->realVars[97] /* speedSensor1._flange._phi DUMMY_STATE */ = data->localData[0]->realVars[3] /* motor._phiMechanical STATE(1,speed) */ + data->simulationInfo->realParameter[47] /* motor._fixed._phi0 PARAM */;
  TRACE_POP
}
/*
 equation index: 194
 type: SIMPLE_ASSIGN
 motor._friction._phi = speedSensor1.flange.phi - motor.fixed.phi0
 */
void PW_PowerSystem_eqFunction_194(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,194};
  data->localData[0]->realVars[45] /* motor._friction._phi DUMMY_STATE */ = data->localData[0]->realVars[97] /* speedSensor1._flange._phi DUMMY_STATE */ - data->simulationInfo->realParameter[47] /* motor._fixed._phi0 PARAM */;
  TRACE_POP
}
/*
 equation index: 195
 type: SIMPLE_ASSIGN
 motor._strayLoad._phi = speedSensor1.flange.phi - motor.fixed.phi0
 */
void PW_PowerSystem_eqFunction_195(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,195};
  data->localData[0]->realVars[81] /* motor._strayLoad._phi DUMMY_STATE */ = data->localData[0]->realVars[97] /* speedSensor1._flange._phi DUMMY_STATE */ - data->simulationInfo->realParameter[47] /* motor._fixed._phi0 PARAM */;
  TRACE_POP
}
/*
 equation index: 198
 type: ALGORITHM
 
   assert(motor.ViNominal > 1e-015, "VaNominal has to be > (Ra[+Rse])*IaNominal");
 */
void PW_PowerSystem_eqFunction_198(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,198};
  modelica_boolean tmp262;
  static const MMC_DEFSTRINGLIT(tmp263,42,"VaNominal has to be > (Ra[+Rse])*IaNominal");
  static int tmp264 = 0;
  {
    tmp262 = Greater(data->simulationInfo->realParameter[25] /* motor._ViNominal PARAM */,1e-015);
    if(!tmp262)
    {
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",13653,7,13654,54,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.ViNominal > 1e-015", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_withEquationIndexes(threadData, info, equationIndexes, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp263)));
      }
    }
  }
  TRACE_POP
}
/*
 equation index: 197
 type: ALGORITHM
 
   assert(1.0 + motor.re.alpha * (motor.thermalAmbient.constTe.k - motor.re.T_ref) >= 1e-015, "Temperature outside scope of model!");
 */
void PW_PowerSystem_eqFunction_197(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,197};
  modelica_boolean tmp265;
  static const MMC_DEFSTRINGLIT(tmp266,35,"Temperature outside scope of model!");
  static int tmp267 = 0;
  {
    tmp265 = GreaterEq(1.0 + (data->simulationInfo->realParameter[74] /* motor._re._alpha PARAM */) * (data->simulationInfo->realParameter[89] /* motor._thermalAmbient._constTe._k PARAM */ - data->simulationInfo->realParameter[73] /* motor._re._T_ref PARAM */),1e-015);
    if(!tmp265)
    {
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Basic.mo",66,5,67,45,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\n1.0 + motor.re.alpha * (motor.thermalAmbient.constTe.k - motor.re.T_ref) >= 1e-015", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_withEquationIndexes(threadData, info, equationIndexes, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp266)));
      }
    }
  }
  TRACE_POP
}
/*
 equation index: 196
 type: ALGORITHM
 
   assert(1.0 + motor.ra.alpha * (motor.thermalAmbient.constTa.k - motor.ra.T_ref) >= 1e-015, "Temperature outside scope of model!");
 */
void PW_PowerSystem_eqFunction_196(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,196};
  modelica_boolean tmp268;
  static const MMC_DEFSTRINGLIT(tmp269,35,"Temperature outside scope of model!");
  static int tmp270 = 0;
  {
    tmp268 = GreaterEq(1.0 + (data->simulationInfo->realParameter[70] /* motor._ra._alpha PARAM */) * (data->simulationInfo->realParameter[88] /* motor._thermalAmbient._constTa._k PARAM */ - data->simulationInfo->realParameter[69] /* motor._ra._T_ref PARAM */),1e-015);
    if(!tmp268)
    {
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Basic.mo",66,5,67,45,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\n1.0 + motor.ra.alpha * (motor.thermalAmbient.constTa.k - motor.ra.T_ref) >= 1e-015", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_withEquationIndexes(threadData, info, equationIndexes, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp269)));
      }
    }
  }
  TRACE_POP
}


int PW_PowerSystem_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
  
  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  PW_PowerSystem_functionLocalKnownVars(data, threadData);
  PW_PowerSystem_eqFunction_121(data, threadData);

  PW_PowerSystem_eqFunction_122(data, threadData);

  PW_PowerSystem_eqFunction_123(data, threadData);

  PW_PowerSystem_eqFunction_124(data, threadData);

  PW_PowerSystem_eqFunction_125(data, threadData);

  PW_PowerSystem_eqFunction_136(data, threadData);

  PW_PowerSystem_eqFunction_137(data, threadData);

  PW_PowerSystem_eqFunction_138(data, threadData);

  PW_PowerSystem_eqFunction_139(data, threadData);

  PW_PowerSystem_eqFunction_140(data, threadData);

  PW_PowerSystem_eqFunction_141(data, threadData);

  PW_PowerSystem_eqFunction_142(data, threadData);

  PW_PowerSystem_eqFunction_143(data, threadData);

  PW_PowerSystem_eqFunction_144(data, threadData);

  PW_PowerSystem_eqFunction_145(data, threadData);

  PW_PowerSystem_eqFunction_146(data, threadData);

  PW_PowerSystem_eqFunction_147(data, threadData);

  PW_PowerSystem_eqFunction_148(data, threadData);

  PW_PowerSystem_eqFunction_149(data, threadData);

  PW_PowerSystem_eqFunction_150(data, threadData);

  PW_PowerSystem_eqFunction_151(data, threadData);

  PW_PowerSystem_eqFunction_152(data, threadData);

  PW_PowerSystem_eqFunction_153(data, threadData);

  PW_PowerSystem_eqFunction_154(data, threadData);

  PW_PowerSystem_eqFunction_155(data, threadData);

  PW_PowerSystem_eqFunction_156(data, threadData);

  PW_PowerSystem_eqFunction_166(data, threadData);

  PW_PowerSystem_eqFunction_167(data, threadData);

  PW_PowerSystem_eqFunction_168(data, threadData);

  PW_PowerSystem_eqFunction_169(data, threadData);

  PW_PowerSystem_eqFunction_170(data, threadData);

  PW_PowerSystem_eqFunction_171(data, threadData);

  PW_PowerSystem_eqFunction_172(data, threadData);

  PW_PowerSystem_eqFunction_173(data, threadData);

  PW_PowerSystem_eqFunction_174(data, threadData);

  PW_PowerSystem_eqFunction_175(data, threadData);

  PW_PowerSystem_eqFunction_176(data, threadData);

  PW_PowerSystem_eqFunction_177(data, threadData);

  PW_PowerSystem_eqFunction_178(data, threadData);

  PW_PowerSystem_eqFunction_179(data, threadData);

  PW_PowerSystem_eqFunction_180(data, threadData);

  PW_PowerSystem_eqFunction_186(data, threadData);

  PW_PowerSystem_eqFunction_187(data, threadData);

  PW_PowerSystem_eqFunction_188(data, threadData);

  PW_PowerSystem_eqFunction_189(data, threadData);

  PW_PowerSystem_eqFunction_190(data, threadData);

  PW_PowerSystem_eqFunction_191(data, threadData);

  PW_PowerSystem_eqFunction_192(data, threadData);

  PW_PowerSystem_eqFunction_193(data, threadData);

  PW_PowerSystem_eqFunction_194(data, threadData);

  PW_PowerSystem_eqFunction_195(data, threadData);

  PW_PowerSystem_eqFunction_198(data, threadData);

  PW_PowerSystem_eqFunction_197(data, threadData);

  PW_PowerSystem_eqFunction_196(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int PW_PowerSystem_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int PW_PowerSystem_symEulerUpdate(DATA *data, modelica_real dt)
{
  return -1;
}



/* forwarded equations */
extern void PW_PowerSystem_eqFunction_123(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_124(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_125(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_136(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_138(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_139(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_140(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_141(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_142(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_143(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_145(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_148(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_156(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_166(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_171(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_172(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_173(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_174(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_178(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_179(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_180(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_186(DATA* data, threadData_t *threadData);
extern void PW_PowerSystem_eqFunction_187(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  PW_PowerSystem_eqFunction_123(data, threadData);

  PW_PowerSystem_eqFunction_124(data, threadData);

  PW_PowerSystem_eqFunction_125(data, threadData);

  PW_PowerSystem_eqFunction_136(data, threadData);

  PW_PowerSystem_eqFunction_138(data, threadData);

  PW_PowerSystem_eqFunction_139(data, threadData);

  PW_PowerSystem_eqFunction_140(data, threadData);

  PW_PowerSystem_eqFunction_141(data, threadData);

  PW_PowerSystem_eqFunction_142(data, threadData);

  PW_PowerSystem_eqFunction_143(data, threadData);

  PW_PowerSystem_eqFunction_145(data, threadData);

  PW_PowerSystem_eqFunction_148(data, threadData);

  PW_PowerSystem_eqFunction_156(data, threadData);

  PW_PowerSystem_eqFunction_166(data, threadData);

  PW_PowerSystem_eqFunction_171(data, threadData);

  PW_PowerSystem_eqFunction_172(data, threadData);

  PW_PowerSystem_eqFunction_173(data, threadData);

  PW_PowerSystem_eqFunction_174(data, threadData);

  PW_PowerSystem_eqFunction_178(data, threadData);

  PW_PowerSystem_eqFunction_179(data, threadData);

  PW_PowerSystem_eqFunction_180(data, threadData);

  PW_PowerSystem_eqFunction_186(data, threadData);

  PW_PowerSystem_eqFunction_187(data, threadData);
}

int PW_PowerSystem_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  data->simulationInfo->callStatistics.functionODE++;
  
  PW_PowerSystem_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

  
  TRACE_POP
  return 0;
}

#ifdef FMU_EXPERIMENTAL
#endif
/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "PW_PowerSystem_12jac.h"
#include "PW_PowerSystem_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks PW_PowerSystem_callback = {
   NULL,
   NULL,
   NULL,
   PW_PowerSystem_callExternalObjectConstructors,
   PW_PowerSystem_callExternalObjectDestructors,
   NULL,
   PW_PowerSystem_initialLinearSystem,
   NULL,
   #if !defined(OMC_NO_STATESELECTION)
   PW_PowerSystem_initializeStateSets,
   #else
   NULL,
   #endif
   PW_PowerSystem_initializeDAEmodeData,
   PW_PowerSystem_functionODE,
   PW_PowerSystem_functionAlgebraics,
   PW_PowerSystem_functionDAE,
   PW_PowerSystem_functionLocalKnownVars,
   PW_PowerSystem_input_function,
   PW_PowerSystem_input_function_init,
   PW_PowerSystem_input_function_updateStartValues,
   PW_PowerSystem_output_function,
   PW_PowerSystem_function_storeDelayed,
   PW_PowerSystem_updateBoundVariableAttributes,
   0 /* useHomotopy */,
   PW_PowerSystem_functionInitialEquations,
   PW_PowerSystem_functionInitialEquations_lambda0,
   PW_PowerSystem_functionRemovedInitialEquations,
   PW_PowerSystem_updateBoundParameters,
   PW_PowerSystem_checkForAsserts,
   PW_PowerSystem_function_ZeroCrossingsEquations,
   PW_PowerSystem_function_ZeroCrossings,
   PW_PowerSystem_function_updateRelations,
   PW_PowerSystem_checkForDiscreteChanges,
   PW_PowerSystem_zeroCrossingDescription,
   PW_PowerSystem_relationDescription,
   PW_PowerSystem_function_initSample,
   PW_PowerSystem_INDEX_JAC_A,
   PW_PowerSystem_INDEX_JAC_B,
   PW_PowerSystem_INDEX_JAC_C,
   PW_PowerSystem_INDEX_JAC_D,
   PW_PowerSystem_initialAnalyticJacobianA,
   PW_PowerSystem_initialAnalyticJacobianB,
   PW_PowerSystem_initialAnalyticJacobianC,
   PW_PowerSystem_initialAnalyticJacobianD,
   PW_PowerSystem_functionJacA_column,
   PW_PowerSystem_functionJacB_column,
   PW_PowerSystem_functionJacC_column,
   PW_PowerSystem_functionJacD_column,
   PW_PowerSystem_linear_model_frame,
   PW_PowerSystem_linear_model_datarecovery_frame,
   PW_PowerSystem_mayer,
   PW_PowerSystem_lagrange,
   PW_PowerSystem_pickUpBoundsForInputsInOptimization,
   PW_PowerSystem_setInputData,
   PW_PowerSystem_getTimeGrid,
   PW_PowerSystem_symEulerUpdate,
   PW_PowerSystem_function_initSynchronous,
   PW_PowerSystem_function_updateSynchronous,
   PW_PowerSystem_function_equationsSynchronous,
   PW_PowerSystem_read_input_fmu
   #ifdef FMU_EXPERIMENTAL
   ,PW_PowerSystem_functionODE_Partial
   ,PW_PowerSystem_functionFMIJacobian
   #endif
   ,PW_PowerSystem_inputNames


};

void PW_PowerSystem_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  data->callback = &PW_PowerSystem_callback;
  data->modelData->modelName = "PW_PowerSystem";
  data->modelData->modelFilePrefix = "PW_PowerSystem";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/Users/clagms/Source Control/Git_HybridCosimulation/ModelicaModels";
  data->modelData->modelGUID = "{4d380cc7-cc74-4e83-9726-8f0ae3e20528}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData =
  #if defined(OMC_MINIMAL_METADATA)
    NULL;
  #else
  #include "PW_PowerSystem_info.c"
  #endif
  ;
  
  data->modelData->nStates = 4;
  data->modelData->nVariablesReal = 106;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 2;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 104;
  data->modelData->nParametersInteger = 4;
  data->modelData->nParametersBoolean = 15;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 3;
  data->modelData->nOutputVars = 2;
  
  data->modelData->nAliasReal = 174;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 2;
  data->modelData->nAliasString = 0;
  
  data->modelData->nZeroCrossings = 2;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 2;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.fileName = "PW_PowerSystem_info.json";
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 11;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 341;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 6;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 10;
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

