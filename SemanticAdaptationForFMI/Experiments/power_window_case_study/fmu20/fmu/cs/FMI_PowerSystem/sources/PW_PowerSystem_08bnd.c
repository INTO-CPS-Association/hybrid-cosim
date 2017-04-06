/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "PW_PowerSystem_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

int PW_PowerSystem_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  /* min ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating min-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* max ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating max-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* nominal **************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating nominal-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* start ****************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating start-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  TRACE_POP
  return 0;
}


/*
 equation index: 199
 type: SIMPLE_ASSIGN
 motor._useSupport = false
 */
void PW_PowerSystem_eqFunction_199(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,199};
  data->simulationInfo->booleanParameter[12] /* motor._useSupport PARAM */ = 0;
  TRACE_POP
}

/*
 equation index: 200
 type: SIMPLE_ASSIGN
 motor._useThermalPort = false
 */
void PW_PowerSystem_eqFunction_200(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,200};
  data->simulationInfo->booleanParameter[13] /* motor._useThermalPort PARAM */ = 0;
  TRACE_POP
}

/*
 equation index: 201
 type: SIMPLE_ASSIGN
 motor._frictionParameters._PRef = 1.0
 */
void PW_PowerSystem_eqFunction_201(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,201};
  data->simulationInfo->realParameter[55] /* motor._frictionParameters._PRef PARAM */ = 1.0;
  TRACE_POP
}

/*
 equation index: 202
 type: SIMPLE_ASSIGN
 motor._frictionParameters._wRef = motor_frictionParameters.wRef
 */
void PW_PowerSystem_eqFunction_202(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,202};
  data->simulationInfo->realParameter[61] /* motor._frictionParameters._wRef PARAM */ = data->simulationInfo->realParameter[102] /* motor_frictionParameters._wRef PARAM */;
  TRACE_POP
}

/*
 equation index: 203
 type: SIMPLE_ASSIGN
 motor._frictionParameters._power_w = motor_frictionParameters.power_w
 */
void PW_PowerSystem_eqFunction_203(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,203};
  data->simulationInfo->realParameter[57] /* motor._frictionParameters._power_w PARAM */ = data->simulationInfo->realParameter[98] /* motor_frictionParameters._power_w PARAM */;
  TRACE_POP
}

/*
 equation index: 204
 type: SIMPLE_ASSIGN
 motor_frictionParameters._tauRef = DIVISION(1.0, motor_frictionParameters.wRef)
 */
void PW_PowerSystem_eqFunction_204(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,204};
  data->simulationInfo->realParameter[100] /* motor_frictionParameters._tauRef PARAM */ = DIVISION_SIM(1.0,data->simulationInfo->realParameter[102] /* motor_frictionParameters._wRef PARAM */,"motor_frictionParameters.wRef",equationIndexes);
  TRACE_POP
}

/*
 equation index: 205
 type: SIMPLE_ASSIGN
 motor._frictionParameters._tauRef = motor_frictionParameters.tauRef
 */
void PW_PowerSystem_eqFunction_205(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,205};
  data->simulationInfo->realParameter[59] /* motor._frictionParameters._tauRef PARAM */ = data->simulationInfo->realParameter[100] /* motor_frictionParameters._tauRef PARAM */;
  TRACE_POP
}

/*
 equation index: 206
 type: SIMPLE_ASSIGN
 motor._frictionParameters._linear = 0.001
 */
void PW_PowerSystem_eqFunction_206(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,206};
  data->simulationInfo->realParameter[56] /* motor._frictionParameters._linear PARAM */ = 0.001;
  TRACE_POP
}

/*
 equation index: 207
 type: SIMPLE_ASSIGN
 motor_frictionParameters._wLinear = 0.001 * motor_frictionParameters.wRef
 */
void PW_PowerSystem_eqFunction_207(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,207};
  data->simulationInfo->realParameter[101] /* motor_frictionParameters._wLinear PARAM */ = (0.001) * (data->simulationInfo->realParameter[102] /* motor_frictionParameters._wRef PARAM */);
  TRACE_POP
}

/*
 equation index: 208
 type: SIMPLE_ASSIGN
 motor._frictionParameters._wLinear = motor_frictionParameters.wLinear
 */
void PW_PowerSystem_eqFunction_208(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,208};
  data->simulationInfo->realParameter[60] /* motor._frictionParameters._wLinear PARAM */ = data->simulationInfo->realParameter[101] /* motor_frictionParameters._wLinear PARAM */;
  TRACE_POP
}

/*
 equation index: 209
 type: SIMPLE_ASSIGN
 motor_frictionParameters._tauLinear = motor_frictionParameters.tauRef * DIVISION(motor_frictionParameters.wLinear, motor_frictionParameters.wRef) ^ motor_frictionParameters.power_w
 */
void PW_PowerSystem_eqFunction_209(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,209};
  modelica_real tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_real tmp6;
  tmp0 = DIVISION_SIM(data->simulationInfo->realParameter[101] /* motor_frictionParameters._wLinear PARAM */,data->simulationInfo->realParameter[102] /* motor_frictionParameters._wRef PARAM */,"motor_frictionParameters.wRef",equationIndexes);
  tmp1 = data->simulationInfo->realParameter[98] /* motor_frictionParameters._power_w PARAM */;
  if(tmp0 < 0.0 && tmp1 != 0.0)
  {
    tmp3 = modf(tmp1, &tmp4);
    
    if(tmp3 > 0.5)
    {
      tmp3 -= 1.0;
      tmp4 += 1.0;
    }
    else if(tmp3 < -0.5)
    {
      tmp3 += 1.0;
      tmp4 -= 1.0;
    }
    
    if(fabs(tmp3) < 1e-10)
      tmp2 = pow(tmp0, tmp4);
    else
    {
      tmp6 = modf(1.0/tmp1, &tmp5);
      if(tmp6 > 0.5)
      {
        tmp6 -= 1.0;
        tmp5 += 1.0;
      }
      else if(tmp6 < -0.5)
      {
        tmp6 += 1.0;
        tmp5 -= 1.0;
      }
      if(fabs(tmp6) < 1e-10 && ((unsigned long)tmp5 & 1))
      {
        tmp2 = -pow(-tmp0, tmp3)*pow(tmp0, tmp4);
      }
      else
      {
        throwStreamPrint(threadData, "Invalid root: (%g)^(%g)", tmp0, tmp1);
      }
    }
  }
  else
  {
    tmp2 = pow(tmp0, tmp1);
  }
  if(isnan(tmp2) || isinf(tmp2))
  {
    throwStreamPrint(threadData, "Invalid root: (%g)^(%g)", tmp0, tmp1);
  }
  data->simulationInfo->realParameter[99] /* motor_frictionParameters._tauLinear PARAM */ = (data->simulationInfo->realParameter[100] /* motor_frictionParameters._tauRef PARAM */) * (tmp2);
  TRACE_POP
}

/*
 equation index: 210
 type: SIMPLE_ASSIGN
 motor._frictionParameters._tauLinear = motor_frictionParameters.tauLinear
 */
void PW_PowerSystem_eqFunction_210(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,210};
  data->simulationInfo->realParameter[58] /* motor._frictionParameters._tauLinear PARAM */ = data->simulationInfo->realParameter[99] /* motor_frictionParameters._tauLinear PARAM */;
  TRACE_POP
}

/*
 equation index: 211
 type: SIMPLE_ASSIGN
 motor._inertiaRotor._J = motor.Jr
 */
void PW_PowerSystem_eqFunction_211(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,211};
  data->simulationInfo->realParameter[62] /* motor._inertiaRotor._J PARAM */ = data->simulationInfo->realParameter[11] /* motor._Jr PARAM */;
  TRACE_POP
}

/*
 equation index: 212
 type: SIMPLE_ASSIGN
 motor._inertiaRotor._stateSelect = StateSelect.default
 */
void PW_PowerSystem_eqFunction_212(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,212};
  data->simulationInfo->integerParameter[2] /* motor._inertiaRotor._stateSelect PARAM */ = 3;
  TRACE_POP
}

/*
 equation index: 213
 type: SIMPLE_ASSIGN
 motor._inertiaStator._J = motor.Js
 */
void PW_PowerSystem_eqFunction_213(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,213};
  data->simulationInfo->realParameter[63] /* motor._inertiaStator._J PARAM */ = data->simulationInfo->realParameter[12] /* motor._Js PARAM */;
  TRACE_POP
}

/*
 equation index: 214
 type: SIMPLE_ASSIGN
 motor._inertiaStator._stateSelect = StateSelect.default
 */
void PW_PowerSystem_eqFunction_214(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,214};
  data->simulationInfo->integerParameter[3] /* motor._inertiaStator._stateSelect PARAM */ = 3;
  TRACE_POP
}

/*
 equation index: 215
 type: SIMPLE_ASSIGN
 motor._friction._useHeatPort = true
 */
void PW_PowerSystem_eqFunction_215(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,215};
  data->simulationInfo->booleanParameter[5] /* motor._friction._useHeatPort PARAM */ = 1;
  TRACE_POP
}

/*
 equation index: 216
 type: SIMPLE_ASSIGN
 motor._friction._frictionParameters._PRef = 1.0
 */
void PW_PowerSystem_eqFunction_216(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,216};
  data->simulationInfo->realParameter[48] /* motor._friction._frictionParameters._PRef PARAM */ = 1.0;
  TRACE_POP
}

/*
 equation index: 217
 type: SIMPLE_ASSIGN
 motor._friction._frictionParameters._wRef = motor.frictionParameters.wRef
 */
void PW_PowerSystem_eqFunction_217(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,217};
  data->simulationInfo->realParameter[54] /* motor._friction._frictionParameters._wRef PARAM */ = data->simulationInfo->realParameter[61] /* motor._frictionParameters._wRef PARAM */;
  TRACE_POP
}

/*
 equation index: 218
 type: SIMPLE_ASSIGN
 motor._friction._frictionParameters._power_w = motor.frictionParameters.power_w
 */
void PW_PowerSystem_eqFunction_218(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,218};
  data->simulationInfo->realParameter[50] /* motor._friction._frictionParameters._power_w PARAM */ = data->simulationInfo->realParameter[57] /* motor._frictionParameters._power_w PARAM */;
  TRACE_POP
}

/*
 equation index: 219
 type: SIMPLE_ASSIGN
 motor._friction._frictionParameters._tauRef = motor.frictionParameters.tauRef
 */
void PW_PowerSystem_eqFunction_219(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,219};
  data->simulationInfo->realParameter[52] /* motor._friction._frictionParameters._tauRef PARAM */ = data->simulationInfo->realParameter[59] /* motor._frictionParameters._tauRef PARAM */;
  TRACE_POP
}

/*
 equation index: 220
 type: SIMPLE_ASSIGN
 motor._friction._frictionParameters._linear = 0.001
 */
void PW_PowerSystem_eqFunction_220(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,220};
  data->simulationInfo->realParameter[49] /* motor._friction._frictionParameters._linear PARAM */ = 0.001;
  TRACE_POP
}

/*
 equation index: 221
 type: SIMPLE_ASSIGN
 motor._friction._frictionParameters._wLinear = motor.frictionParameters.wLinear
 */
void PW_PowerSystem_eqFunction_221(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,221};
  data->simulationInfo->realParameter[53] /* motor._friction._frictionParameters._wLinear PARAM */ = data->simulationInfo->realParameter[60] /* motor._frictionParameters._wLinear PARAM */;
  TRACE_POP
}

/*
 equation index: 222
 type: SIMPLE_ASSIGN
 motor._friction._frictionParameters._tauLinear = motor.frictionParameters.tauLinear
 */
void PW_PowerSystem_eqFunction_222(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,222};
  data->simulationInfo->realParameter[51] /* motor._friction._frictionParameters._tauLinear PARAM */ = data->simulationInfo->realParameter[58] /* motor._frictionParameters._tauLinear PARAM */;
  TRACE_POP
}

/*
 equation index: 223
 type: SIMPLE_ASSIGN
 motor._coreParameters._PRef = 0.0
 */
void PW_PowerSystem_eqFunction_223(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,223};
  data->simulationInfo->realParameter[42] /* motor._coreParameters._PRef PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 224
 type: SIMPLE_ASSIGN
 motor._brushParameters._ILinear = 0.01 * motor.IaNominal
 */
void PW_PowerSystem_eqFunction_224(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,224};
  data->simulationInfo->realParameter[32] /* motor._brushParameters._ILinear PARAM */ = (0.01) * (data->simulationInfo->realParameter[9] /* motor._IaNominal PARAM */);
  TRACE_POP
}

/*
 equation index: 225
 type: SIMPLE_ASSIGN
 motor._ViNominal = motor.VaNominal + (-motor.Ra) * (1.0 + motor.alpha20a * DIVISION(motor.TaNominal - motor.TaRef, 1.0 + motor.alpha20a * (-293.15 + motor.TaRef))) * motor.IaNominal - Modelica.Electrical.Machines.Losses.DCMachines.brushVoltageDrop(Modelica.Electrical.Machines.Losses.BrushParameters(0.0, motor.brushParameters.ILinear), motor.IaNominal)
 */
void PW_PowerSystem_eqFunction_225(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,225};
  data->simulationInfo->realParameter[25] /* motor._ViNominal PARAM */ = data->simulationInfo->realParameter[24] /* motor._VaNominal PARAM */ + ((-data->simulationInfo->realParameter[17] /* motor._Ra PARAM */)) * ((1.0 + (data->simulationInfo->realParameter[28] /* motor._alpha20a PARAM */) * (DIVISION_SIM(data->simulationInfo->realParameter[19] /* motor._TaNominal PARAM */ - data->simulationInfo->realParameter[21] /* motor._TaRef PARAM */,1.0 + (data->simulationInfo->realParameter[28] /* motor._alpha20a PARAM */) * (-293.15 + data->simulationInfo->realParameter[21] /* motor._TaRef PARAM */),"1.0 + motor.alpha20a * (-293.15 + motor.TaRef)",equationIndexes))) * (data->simulationInfo->realParameter[9] /* motor._IaNominal PARAM */)) - omc_Modelica_Electrical_Machines_Losses_DCMachines_brushVoltageDrop(threadData, omc_Modelica_Electrical_Machines_Losses_BrushParameters(threadData, 0.0, data->simulationInfo->realParameter[32] /* motor._brushParameters._ILinear PARAM */), data->simulationInfo->realParameter[9] /* motor._IaNominal PARAM */);
  TRACE_POP
}

/*
 equation index: 226
 type: SIMPLE_ASSIGN
 motor._coreParameters._VRef = motor.ViNominal
 */
void PW_PowerSystem_eqFunction_226(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,226};
  data->simulationInfo->realParameter[43] /* motor._coreParameters._VRef PARAM */ = data->simulationInfo->realParameter[25] /* motor._ViNominal PARAM */;
  TRACE_POP
}

/*
 equation index: 227
 type: SIMPLE_ASSIGN
 motor._coreParameters._wRef = motor.wNominal
 */
void PW_PowerSystem_eqFunction_227(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,227};
  data->simulationInfo->realParameter[46] /* motor._coreParameters._wRef PARAM */ = data->simulationInfo->realParameter[95] /* motor._wNominal PARAM */;
  TRACE_POP
}

/*
 equation index: 228
 type: SIMPLE_ASSIGN
 motor._coreParameters._ratioHysteresis = 0.0
 */
void PW_PowerSystem_eqFunction_228(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,228};
  data->simulationInfo->realParameter[44] /* motor._coreParameters._ratioHysteresis PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 229
 type: SIMPLE_ASSIGN
 motor._coreParameters._GcRef = 0.0
 */
void PW_PowerSystem_eqFunction_229(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,229};
  data->simulationInfo->realParameter[41] /* motor._coreParameters._GcRef PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 230
 type: SIMPLE_ASSIGN
 motor._coreParameters._wMin = 1e-006 * motor.coreParameters.wRef
 */
void PW_PowerSystem_eqFunction_230(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,230};
  data->simulationInfo->realParameter[45] /* motor._coreParameters._wMin PARAM */ = (1e-006) * (data->simulationInfo->realParameter[46] /* motor._coreParameters._wRef PARAM */);
  TRACE_POP
}

/*
 equation index: 231
 type: SIMPLE_ASSIGN
 motor._strayLoadParameters._PRef = 0.0
 */
void PW_PowerSystem_eqFunction_231(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,231};
  data->simulationInfo->realParameter[82] /* motor._strayLoadParameters._PRef PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 232
 type: SIMPLE_ASSIGN
 motor._strayLoadParameters._IRef = motor.IaNominal
 */
void PW_PowerSystem_eqFunction_232(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,232};
  data->simulationInfo->realParameter[81] /* motor._strayLoadParameters._IRef PARAM */ = data->simulationInfo->realParameter[9] /* motor._IaNominal PARAM */;
  TRACE_POP
}

/*
 equation index: 233
 type: SIMPLE_ASSIGN
 motor._strayLoadParameters._wRef = motor.wNominal
 */
void PW_PowerSystem_eqFunction_233(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,233};
  data->simulationInfo->realParameter[85] /* motor._strayLoadParameters._wRef PARAM */ = data->simulationInfo->realParameter[95] /* motor._wNominal PARAM */;
  TRACE_POP
}

/*
 equation index: 234
 type: SIMPLE_ASSIGN
 motor._strayLoadParameters._tauRef = 0.0
 */
void PW_PowerSystem_eqFunction_234(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,234};
  data->simulationInfo->realParameter[84] /* motor._strayLoadParameters._tauRef PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 235
 type: SIMPLE_ASSIGN
 motor._brushParameters._V = 0.0
 */
void PW_PowerSystem_eqFunction_235(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,235};
  data->simulationInfo->realParameter[33] /* motor._brushParameters._V PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 236
 type: SIMPLE_ASSIGN
 motor._ra._useHeatPort = true
 */
void PW_PowerSystem_eqFunction_236(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,236};
  data->simulationInfo->booleanParameter[8] /* motor._ra._useHeatPort PARAM */ = 1;
  TRACE_POP
}

/*
 equation index: 237
 type: SIMPLE_ASSIGN
 motor._ra._T = motor.TaRef
 */
void PW_PowerSystem_eqFunction_237(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,237};
  data->simulationInfo->realParameter[68] /* motor._ra._T PARAM */ = data->simulationInfo->realParameter[21] /* motor._TaRef PARAM */;
  TRACE_POP
}

/*
 equation index: 238
 type: SIMPLE_ASSIGN
 motor._ra._R = motor.Ra
 */
void PW_PowerSystem_eqFunction_238(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,238};
  data->simulationInfo->realParameter[67] /* motor._ra._R PARAM */ = data->simulationInfo->realParameter[17] /* motor._Ra PARAM */;
  TRACE_POP
}

/*
 equation index: 239
 type: SIMPLE_ASSIGN
 motor._ra._T_ref = motor.TaRef
 */
void PW_PowerSystem_eqFunction_239(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,239};
  data->simulationInfo->realParameter[69] /* motor._ra._T_ref PARAM */ = data->simulationInfo->realParameter[21] /* motor._TaRef PARAM */;
  TRACE_POP
}

/*
 equation index: 240
 type: SIMPLE_ASSIGN
 motor._ra._alpha = DIVISION(motor.alpha20a, 1.0 + motor.alpha20a * (-293.15 + motor.TaRef))
 */
void PW_PowerSystem_eqFunction_240(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,240};
  data->simulationInfo->realParameter[70] /* motor._ra._alpha PARAM */ = DIVISION_SIM(data->simulationInfo->realParameter[28] /* motor._alpha20a PARAM */,1.0 + (data->simulationInfo->realParameter[28] /* motor._alpha20a PARAM */) * (-293.15 + data->simulationInfo->realParameter[21] /* motor._TaRef PARAM */),"1.0 + motor.alpha20a * (-293.15 + motor.TaRef)",equationIndexes);
  TRACE_POP
}

/*
 equation index: 241
 type: SIMPLE_ASSIGN
 motor._la._L = motor.La
 */
void PW_PowerSystem_eqFunction_241(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,241};
  data->simulationInfo->realParameter[64] /* motor._la._L PARAM */ = data->simulationInfo->realParameter[13] /* motor._La PARAM */;
  TRACE_POP
}

/*
 equation index: 242
 type: SIMPLE_ASSIGN
 motor._la._quasiStationary = false
 */
void PW_PowerSystem_eqFunction_242(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,242};
  data->simulationInfo->booleanParameter[6] /* motor._la._quasiStationary PARAM */ = 0;
  TRACE_POP
}

/*
 equation index: 243
 type: SIMPLE_ASSIGN
 motor._brush._useHeatPort = true
 */
void PW_PowerSystem_eqFunction_243(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,243};
  data->simulationInfo->booleanParameter[3] /* motor._brush._useHeatPort PARAM */ = 1;
  TRACE_POP
}

/*
 equation index: 244
 type: SIMPLE_ASSIGN
 motor._brush._brushParameters._V = 0.0
 */
void PW_PowerSystem_eqFunction_244(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,244};
  data->simulationInfo->realParameter[31] /* motor._brush._brushParameters._V PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 245
 type: SIMPLE_ASSIGN
 motor._brush._brushParameters._ILinear = motor.brushParameters.ILinear
 */
void PW_PowerSystem_eqFunction_245(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,245};
  data->simulationInfo->realParameter[30] /* motor._brush._brushParameters._ILinear PARAM */ = data->simulationInfo->realParameter[32] /* motor._brushParameters._ILinear PARAM */;
  TRACE_POP
}

/*
 equation index: 246
 type: SIMPLE_ASSIGN
 motor._core._useHeatPort = true
 */
void PW_PowerSystem_eqFunction_246(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,246};
  data->simulationInfo->booleanParameter[4] /* motor._core._useHeatPort PARAM */ = 1;
  TRACE_POP
}

/*
 equation index: 247
 type: SIMPLE_ASSIGN
 motor._core._coreParameters._m = motor.coreParameters.m
 */
void PW_PowerSystem_eqFunction_247(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,247};
  data->simulationInfo->integerParameter[0] /* motor._core._coreParameters._m PARAM */ = (modelica_integer)data->simulationInfo->integerParameter[1] /* motor._coreParameters._m PARAM */;
  TRACE_POP
}

/*
 equation index: 248
 type: SIMPLE_ASSIGN
 motor._core._coreParameters._PRef = 0.0
 */
void PW_PowerSystem_eqFunction_248(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,248};
  data->simulationInfo->realParameter[36] /* motor._core._coreParameters._PRef PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 249
 type: SIMPLE_ASSIGN
 motor._core._coreParameters._VRef = motor.coreParameters.VRef
 */
void PW_PowerSystem_eqFunction_249(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,249};
  data->simulationInfo->realParameter[37] /* motor._core._coreParameters._VRef PARAM */ = data->simulationInfo->realParameter[43] /* motor._coreParameters._VRef PARAM */;
  TRACE_POP
}

/*
 equation index: 250
 type: SIMPLE_ASSIGN
 motor._core._coreParameters._wRef = motor.coreParameters.wRef
 */
void PW_PowerSystem_eqFunction_250(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,250};
  data->simulationInfo->realParameter[40] /* motor._core._coreParameters._wRef PARAM */ = data->simulationInfo->realParameter[46] /* motor._coreParameters._wRef PARAM */;
  TRACE_POP
}

/*
 equation index: 251
 type: SIMPLE_ASSIGN
 motor._core._coreParameters._ratioHysteresis = 0.0
 */
void PW_PowerSystem_eqFunction_251(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,251};
  data->simulationInfo->realParameter[38] /* motor._core._coreParameters._ratioHysteresis PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 252
 type: SIMPLE_ASSIGN
 motor._core._coreParameters._GcRef = 0.0
 */
void PW_PowerSystem_eqFunction_252(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,252};
  data->simulationInfo->realParameter[35] /* motor._core._coreParameters._GcRef PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 253
 type: SIMPLE_ASSIGN
 motor._core._coreParameters._wMin = motor.coreParameters.wMin
 */
void PW_PowerSystem_eqFunction_253(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,253};
  data->simulationInfo->realParameter[39] /* motor._core._coreParameters._wMin PARAM */ = data->simulationInfo->realParameter[45] /* motor._coreParameters._wMin PARAM */;
  TRACE_POP
}

/*
 equation index: 254
 type: SIMPLE_ASSIGN
 motor._strayLoad._useHeatPort = true
 */
void PW_PowerSystem_eqFunction_254(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,254};
  data->simulationInfo->booleanParameter[10] /* motor._strayLoad._useHeatPort PARAM */ = 1;
  TRACE_POP
}

/*
 equation index: 255
 type: SIMPLE_ASSIGN
 motor._strayLoad._strayLoadParameters._PRef = 0.0
 */
void PW_PowerSystem_eqFunction_255(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,255};
  data->simulationInfo->realParameter[77] /* motor._strayLoad._strayLoadParameters._PRef PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 256
 type: SIMPLE_ASSIGN
 motor._strayLoad._strayLoadParameters._IRef = motor.strayLoadParameters.IRef
 */
void PW_PowerSystem_eqFunction_256(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,256};
  data->simulationInfo->realParameter[76] /* motor._strayLoad._strayLoadParameters._IRef PARAM */ = data->simulationInfo->realParameter[81] /* motor._strayLoadParameters._IRef PARAM */;
  TRACE_POP
}

/*
 equation index: 257
 type: SIMPLE_ASSIGN
 motor._strayLoad._strayLoadParameters._wRef = motor.strayLoadParameters.wRef
 */
void PW_PowerSystem_eqFunction_257(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,257};
  data->simulationInfo->realParameter[80] /* motor._strayLoad._strayLoadParameters._wRef PARAM */ = data->simulationInfo->realParameter[85] /* motor._strayLoadParameters._wRef PARAM */;
  TRACE_POP
}

/*
 equation index: 258
 type: SIMPLE_ASSIGN
 motor._strayLoad._strayLoadParameters._power_w = motor.strayLoadParameters.power_w
 */
void PW_PowerSystem_eqFunction_258(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,258};
  data->simulationInfo->realParameter[78] /* motor._strayLoad._strayLoadParameters._power_w PARAM */ = data->simulationInfo->realParameter[83] /* motor._strayLoadParameters._power_w PARAM */;
  TRACE_POP
}

/*
 equation index: 259
 type: SIMPLE_ASSIGN
 motor._strayLoad._strayLoadParameters._tauRef = 0.0
 */
void PW_PowerSystem_eqFunction_259(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,259};
  data->simulationInfo->realParameter[79] /* motor._strayLoad._strayLoadParameters._tauRef PARAM */ = 0.0;
  TRACE_POP
}

/*
 equation index: 260
 type: SIMPLE_ASSIGN
 motor._psi_eNominal = 3.2 * motor.IeNominal
 */
void PW_PowerSystem_eqFunction_260(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,260};
  data->simulationInfo->realParameter[66] /* motor._psi_eNominal PARAM */ = (3.2) * (data->simulationInfo->realParameter[10] /* motor._IeNominal PARAM */);
  TRACE_POP
}

/*
 equation index: 261
 type: SIMPLE_ASSIGN
 motor._turnsRatio = DIVISION(motor.ViNominal, motor.psi_eNominal * motor.wNominal)
 */
void PW_PowerSystem_eqFunction_261(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,261};
  data->simulationInfo->realParameter[94] /* motor._turnsRatio PARAM */ = DIVISION_SIM(data->simulationInfo->realParameter[25] /* motor._ViNominal PARAM */,(data->simulationInfo->realParameter[66] /* motor._psi_eNominal PARAM */) * (data->simulationInfo->realParameter[95] /* motor._wNominal PARAM */),"motor.psi_eNominal * motor.wNominal",equationIndexes);
  TRACE_POP
}

/*
 equation index: 262
 type: SIMPLE_ASSIGN
 motor._Le = 4.0
 */
void PW_PowerSystem_eqFunction_262(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,262};
  data->simulationInfo->realParameter[14] /* motor._Le PARAM */ = 4.0;
  TRACE_POP
}

/*
 equation index: 263
 type: SIMPLE_ASSIGN
 motor._sigmae = 0.2
 */
void PW_PowerSystem_eqFunction_263(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,263};
  data->simulationInfo->realParameter[75] /* motor._sigmae PARAM */ = 0.2;
  TRACE_POP
}

/*
 equation index: 264
 type: SIMPLE_ASSIGN
 motor._airGapDC._quasiStationary = false
 */
void PW_PowerSystem_eqFunction_264(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,264};
  data->simulationInfo->booleanParameter[2] /* motor._airGapDC._quasiStationary PARAM */ = 0;
  TRACE_POP
}

/*
 equation index: 265
 type: SIMPLE_ASSIGN
 motor._airGapDC._turnsRatio = motor.turnsRatio
 */
void PW_PowerSystem_eqFunction_265(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,265};
  data->simulationInfo->realParameter[27] /* motor._airGapDC._turnsRatio PARAM */ = data->simulationInfo->realParameter[94] /* motor._turnsRatio PARAM */;
  TRACE_POP
}

/*
 equation index: 266
 type: SIMPLE_ASSIGN
 motor._airGapDC._Le = 3.2
 */
void PW_PowerSystem_eqFunction_266(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,266};
  data->simulationInfo->realParameter[26] /* motor._airGapDC._Le PARAM */ = 3.2;
  TRACE_POP
}

/*
 equation index: 267
 type: SIMPLE_ASSIGN
 motor._re._useHeatPort = true
 */
void PW_PowerSystem_eqFunction_267(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,267};
  data->simulationInfo->booleanParameter[9] /* motor._re._useHeatPort PARAM */ = 1;
  TRACE_POP
}

/*
 equation index: 268
 type: SIMPLE_ASSIGN
 motor._re._T = motor.TeRef
 */
void PW_PowerSystem_eqFunction_268(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,268};
  data->simulationInfo->realParameter[72] /* motor._re._T PARAM */ = data->simulationInfo->realParameter[23] /* motor._TeRef PARAM */;
  TRACE_POP
}

/*
 equation index: 269
 type: SIMPLE_ASSIGN
 motor._re._R = motor.Re
 */
void PW_PowerSystem_eqFunction_269(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,269};
  data->simulationInfo->realParameter[71] /* motor._re._R PARAM */ = data->simulationInfo->realParameter[18] /* motor._Re PARAM */;
  TRACE_POP
}

/*
 equation index: 270
 type: SIMPLE_ASSIGN
 motor._re._T_ref = motor.TeRef
 */
void PW_PowerSystem_eqFunction_270(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,270};
  data->simulationInfo->realParameter[73] /* motor._re._T_ref PARAM */ = data->simulationInfo->realParameter[23] /* motor._TeRef PARAM */;
  TRACE_POP
}

/*
 equation index: 271
 type: SIMPLE_ASSIGN
 motor._re._alpha = DIVISION(motor.alpha20e, 1.0 + motor.alpha20e * (-293.15 + motor.TeRef))
 */
void PW_PowerSystem_eqFunction_271(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,271};
  data->simulationInfo->realParameter[74] /* motor._re._alpha PARAM */ = DIVISION_SIM(data->simulationInfo->realParameter[29] /* motor._alpha20e PARAM */,1.0 + (data->simulationInfo->realParameter[29] /* motor._alpha20e PARAM */) * (-293.15 + data->simulationInfo->realParameter[23] /* motor._TeRef PARAM */),"1.0 + motor.alpha20e * (-293.15 + motor.TeRef)",equationIndexes);
  TRACE_POP
}

/*
 equation index: 272
 type: SIMPLE_ASSIGN
 motor._lesigma._L = 0.8
 */
void PW_PowerSystem_eqFunction_272(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,272};
  data->simulationInfo->realParameter[65] /* motor._lesigma._L PARAM */ = 0.8;
  TRACE_POP
}

/*
 equation index: 273
 type: SIMPLE_ASSIGN
 motor._lesigma._quasiStationary = false
 */
void PW_PowerSystem_eqFunction_273(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,273};
  data->simulationInfo->booleanParameter[7] /* motor._lesigma._quasiStationary PARAM */ = 0;
  TRACE_POP
}

/*
 equation index: 274
 type: SIMPLE_ASSIGN
 motor._Lme = 3.2
 */
void PW_PowerSystem_eqFunction_274(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,274};
  data->simulationInfo->realParameter[16] /* motor._Lme PARAM */ = 3.2;
  TRACE_POP
}

/*
 equation index: 275
 type: SIMPLE_ASSIGN
 motor._Lesigma = 0.8
 */
void PW_PowerSystem_eqFunction_275(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,275};
  data->simulationInfo->realParameter[15] /* motor._Lesigma PARAM */ = 0.8;
  TRACE_POP
}

/*
 equation index: 276
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._useTemperatureInputs = false
 */
void PW_PowerSystem_eqFunction_276(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,276};
  data->simulationInfo->booleanParameter[11] /* motor._thermalAmbient._useTemperatureInputs PARAM */ = 0;
  TRACE_POP
}

/*
 equation index: 277
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._Ta = motor.TaOperational
 */
void PW_PowerSystem_eqFunction_277(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,277};
  data->simulationInfo->realParameter[86] /* motor._thermalAmbient._Ta PARAM */ = data->simulationInfo->realParameter[20] /* motor._TaOperational PARAM */;
  TRACE_POP
}

/*
 equation index: 278
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._temperatureCore._T = 293.15
 */
void PW_PowerSystem_eqFunction_278(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,278};
  data->simulationInfo->realParameter[91] /* motor._thermalAmbient._temperatureCore._T PARAM */ = 293.15;
  TRACE_POP
}

/*
 equation index: 279
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._temperatureStrayLoad._T = 293.15
 */
void PW_PowerSystem_eqFunction_279(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,279};
  data->simulationInfo->realParameter[93] /* motor._thermalAmbient._temperatureStrayLoad._T PARAM */ = 293.15;
  TRACE_POP
}

/*
 equation index: 280
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._temperatureFriction._T = 293.15
 */
void PW_PowerSystem_eqFunction_280(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,280};
  data->simulationInfo->realParameter[92] /* motor._thermalAmbient._temperatureFriction._T PARAM */ = 293.15;
  TRACE_POP
}

/*
 equation index: 281
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._temperatureBrush._T = 293.15
 */
void PW_PowerSystem_eqFunction_281(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,281};
  data->simulationInfo->realParameter[90] /* motor._thermalAmbient._temperatureBrush._T PARAM */ = 293.15;
  TRACE_POP
}

/*
 equation index: 282
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._Te = motor.TeOperational
 */
void PW_PowerSystem_eqFunction_282(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,282};
  data->simulationInfo->realParameter[87] /* motor._thermalAmbient._Te PARAM */ = data->simulationInfo->realParameter[22] /* motor._TeOperational PARAM */;
  TRACE_POP
}

/*
 equation index: 283
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._constTa._k = motor.thermalAmbient.Ta
 */
void PW_PowerSystem_eqFunction_283(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,283};
  data->simulationInfo->realParameter[88] /* motor._thermalAmbient._constTa._k PARAM */ = data->simulationInfo->realParameter[86] /* motor._thermalAmbient._Ta PARAM */;
  TRACE_POP
}

/*
 equation index: 284
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._constTe._k = motor.thermalAmbient.Te
 */
void PW_PowerSystem_eqFunction_284(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,284};
  data->simulationInfo->realParameter[89] /* motor._thermalAmbient._constTe._k PARAM */ = data->simulationInfo->realParameter[87] /* motor._thermalAmbient._Te PARAM */;
  TRACE_POP
}

/*
 equation index: 285
 type: SIMPLE_ASSIGN
 torque1._useSupport = false
 */
void PW_PowerSystem_eqFunction_285(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,285};
  data->simulationInfo->booleanParameter[14] /* torque1._useSupport PARAM */ = 0;
  TRACE_POP
}

/*
 equation index: 286
 type: SIMPLE_ASSIGN
 motor_frictionParameters._PRef = 1.0
 */
void PW_PowerSystem_eqFunction_286(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,286};
  data->simulationInfo->realParameter[96] /* motor_frictionParameters._PRef PARAM */ = 1.0;
  TRACE_POP
}

/*
 equation index: 287
 type: SIMPLE_ASSIGN
 motor_frictionParameters._linear = 0.001
 */
void PW_PowerSystem_eqFunction_287(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,287};
  data->simulationInfo->realParameter[97] /* motor_frictionParameters._linear PARAM */ = 0.001;
  TRACE_POP
}

/*
 equation index: 288
 type: SIMPLE_ASSIGN
 idealCommutingSwitch1._useHeatPort = false
 */
void PW_PowerSystem_eqFunction_288(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,288};
  data->simulationInfo->booleanParameter[0] /* idealCommutingSwitch1._useHeatPort PARAM */ = 0;
  TRACE_POP
}

/*
 equation index: 289
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._useHeatPort = false
 */
void PW_PowerSystem_eqFunction_289(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,289};
  data->simulationInfo->booleanParameter[1] /* idealCommutingSwitch2._useHeatPort PARAM */ = 0;
  TRACE_POP
}

/*
 equation index: 290
 type: ALGORITHM
 
   assert(motor.TaOperational >= 0.0, "Variable violating min constraint: 0.0 <= motor.TaOperational, has value: " + String(motor.TaOperational, "g"));
 */
void PW_PowerSystem_eqFunction_290(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,290};
  modelica_boolean tmp7;
  static const MMC_DEFSTRINGLIT(tmp8,74,"Variable violating min constraint: 0.0 <= motor.TaOperational, has value: ");
  modelica_string tmp9;
  static int tmp10 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp10)
  {
    tmp7 = GreaterEq(data->simulationInfo->realParameter[20] /* motor._TaOperational PARAM */,0.0);
    if(!tmp7)
    {
      tmp9 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[20] /* motor._TaOperational PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp8),tmp9);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",13546,7,13548,70,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.TaOperational >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp10 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 291
 type: ALGORITHM
 
   assert(motor.TaNominal >= 0.0, "Variable violating min constraint: 0.0 <= motor.TaNominal, has value: " + String(motor.TaNominal, "g"));
 */
void PW_PowerSystem_eqFunction_291(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,291};
  modelica_boolean tmp11;
  static const MMC_DEFSTRINGLIT(tmp12,70,"Variable violating min constraint: 0.0 <= motor.TaNominal, has value: ");
  modelica_string tmp13;
  static int tmp14 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp14)
  {
    tmp11 = GreaterEq(data->simulationInfo->realParameter[19] /* motor._TaNominal PARAM */,0.0);
    if(!tmp11)
    {
      tmp13 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[19] /* motor._TaNominal PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp12),tmp13);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",13557,7,13559,54,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.TaNominal >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp14 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 292
 type: ALGORITHM
 
   assert(motor.TaRef >= 0.0, "Variable violating min constraint: 0.0 <= motor.TaRef, has value: " + String(motor.TaRef, "g"));
 */
void PW_PowerSystem_eqFunction_292(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,292};
  modelica_boolean tmp15;
  static const MMC_DEFSTRINGLIT(tmp16,66,"Variable violating min constraint: 0.0 <= motor.TaRef, has value: ");
  modelica_string tmp17;
  static int tmp18 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp18)
  {
    tmp15 = GreaterEq(data->simulationInfo->realParameter[21] /* motor._TaRef PARAM */,0.0);
    if(!tmp15)
    {
      tmp17 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[21] /* motor._TaRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp16),tmp17);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",13563,7,13565,71,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.TaRef >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp18 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 293
 type: ALGORITHM
 
   assert(motor.frictionParameters.PRef >= 0.0, "Variable violating min constraint: 0.0 <= motor.frictionParameters.PRef, has value: " + String(motor.frictionParameters.PRef, "g"));
 */
void PW_PowerSystem_eqFunction_293(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,293};
  modelica_boolean tmp19;
  static const MMC_DEFSTRINGLIT(tmp20,84,"Variable violating min constraint: 0.0 <= motor.frictionParameters.PRef, has value: ");
  modelica_string tmp21;
  static int tmp22 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp22)
  {
    tmp19 = GreaterEq(data->simulationInfo->realParameter[55] /* motor._frictionParameters._PRef PARAM */,0.0);
    if(!tmp19)
    {
      tmp21 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[55] /* motor._frictionParameters._PRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp20),tmp21);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11050,7,11051,44,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.frictionParameters.PRef >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp22 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 294
 type: ALGORITHM
 
   assert(motor_frictionParameters.wRef >= 1e-060, "Variable violating min constraint: 1e-060 <= motor_frictionParameters.wRef, has value: " + String(motor_frictionParameters.wRef, "g"));
 */
void PW_PowerSystem_eqFunction_294(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,294};
  modelica_boolean tmp23;
  static const MMC_DEFSTRINGLIT(tmp24,87,"Variable violating min constraint: 1e-060 <= motor_frictionParameters.wRef, has value: ");
  modelica_string tmp25;
  static int tmp26 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp26)
  {
    tmp23 = GreaterEq(data->simulationInfo->realParameter[102] /* motor_frictionParameters._wRef PARAM */,1e-060);
    if(!tmp23)
    {
      tmp25 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[102] /* motor_frictionParameters._wRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp24),tmp25);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11052,7,11054,60,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor_frictionParameters.wRef >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp26 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 295
 type: ALGORITHM
 
   assert(motor.frictionParameters.wRef >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.frictionParameters.wRef, has value: " + String(motor.frictionParameters.wRef, "g"));
 */
void PW_PowerSystem_eqFunction_295(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,295};
  modelica_boolean tmp27;
  static const MMC_DEFSTRINGLIT(tmp28,87,"Variable violating min constraint: 1e-060 <= motor.frictionParameters.wRef, has value: ");
  modelica_string tmp29;
  static int tmp30 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp30)
  {
    tmp27 = GreaterEq(data->simulationInfo->realParameter[61] /* motor._frictionParameters._wRef PARAM */,1e-060);
    if(!tmp27)
    {
      tmp29 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[61] /* motor._frictionParameters._wRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp28),tmp29);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11052,7,11054,60,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.frictionParameters.wRef >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp30 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 296
 type: ALGORITHM
 
   assert(motor_frictionParameters.power_w >= 1e-060, "Variable violating min constraint: 1e-060 <= motor_frictionParameters.power_w, has value: " + String(motor_frictionParameters.power_w, "g"));
 */
void PW_PowerSystem_eqFunction_296(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,296};
  modelica_boolean tmp31;
  static const MMC_DEFSTRINGLIT(tmp32,90,"Variable violating min constraint: 1e-060 <= motor_frictionParameters.power_w, has value: ");
  modelica_string tmp33;
  static int tmp34 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp34)
  {
    tmp31 = GreaterEq(data->simulationInfo->realParameter[98] /* motor_frictionParameters._power_w PARAM */,1e-060);
    if(!tmp31)
    {
      tmp33 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[98] /* motor_frictionParameters._power_w PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp32),tmp33);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11055,7,11056,62,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor_frictionParameters.power_w >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp34 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 297
 type: ALGORITHM
 
   assert(motor.frictionParameters.power_w >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.frictionParameters.power_w, has value: " + String(motor.frictionParameters.power_w, "g"));
 */
void PW_PowerSystem_eqFunction_297(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,297};
  modelica_boolean tmp35;
  static const MMC_DEFSTRINGLIT(tmp36,90,"Variable violating min constraint: 1e-060 <= motor.frictionParameters.power_w, has value: ");
  modelica_string tmp37;
  static int tmp38 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp38)
  {
    tmp35 = GreaterEq(data->simulationInfo->realParameter[57] /* motor._frictionParameters._power_w PARAM */,1e-060);
    if(!tmp35)
    {
      tmp37 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[57] /* motor._frictionParameters._power_w PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp36),tmp37);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11055,7,11056,62,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.frictionParameters.power_w >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp38 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 298
 type: ALGORITHM
 
   assert(motor.inertiaRotor.J >= 0.0, "Variable violating min constraint: 0.0 <= motor.inertiaRotor.J, has value: " + String(motor.inertiaRotor.J, "g"));
 */
void PW_PowerSystem_eqFunction_298(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,298};
  modelica_boolean tmp39;
  static const MMC_DEFSTRINGLIT(tmp40,75,"Variable violating min constraint: 0.0 <= motor.inertiaRotor.J, has value: ");
  modelica_string tmp41;
  static int tmp42 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp42)
  {
    tmp39 = GreaterEq(data->simulationInfo->realParameter[62] /* motor._inertiaRotor._J PARAM */,0.0);
    if(!tmp39)
    {
      tmp41 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[62] /* motor._inertiaRotor._J PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp40),tmp41);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Mechanics/Rotational.mo",2410,7,2410,65,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.inertiaRotor.J >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp42 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 299
 type: ALGORITHM
 
   assert(motor.inertiaRotor.stateSelect >= StateSelect.never and motor.inertiaRotor.stateSelect <= StateSelect.always, "Variable violating min/max constraint: StateSelect.never <= motor.inertiaRotor.stateSelect <= StateSelect.always, has value: " + String(motor.inertiaRotor.stateSelect, "d"));
 */
void PW_PowerSystem_eqFunction_299(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,299};
  modelica_boolean tmp43;
  modelica_boolean tmp44;
  static const MMC_DEFSTRINGLIT(tmp45,125,"Variable violating min/max constraint: StateSelect.never <= motor.inertiaRotor.stateSelect <= StateSelect.always, has value: ");
  modelica_string tmp46;
  static int tmp47 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp47)
  {
    tmp43 = GreaterEq((modelica_integer)data->simulationInfo->integerParameter[2] /* motor._inertiaRotor._stateSelect PARAM */,1);
    tmp44 = LessEq((modelica_integer)data->simulationInfo->integerParameter[2] /* motor._inertiaRotor._stateSelect PARAM */,5);
    if(!(tmp43 && tmp44))
    {
      tmp46 = modelica_integer_to_modelica_string_format((modelica_integer)data->simulationInfo->integerParameter[2] /* motor._inertiaRotor._stateSelect PARAM */, (modelica_string) mmc_strings_len1[100]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp45),tmp46);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Mechanics/Rotational.mo",2411,7,2413,61,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.inertiaRotor.stateSelect >= StateSelect.never and motor.inertiaRotor.stateSelect <= StateSelect.always", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp47 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 300
 type: ALGORITHM
 
   assert(motor.inertiaStator.J >= 0.0, "Variable violating min constraint: 0.0 <= motor.inertiaStator.J, has value: " + String(motor.inertiaStator.J, "g"));
 */
void PW_PowerSystem_eqFunction_300(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,300};
  modelica_boolean tmp48;
  static const MMC_DEFSTRINGLIT(tmp49,76,"Variable violating min constraint: 0.0 <= motor.inertiaStator.J, has value: ");
  modelica_string tmp50;
  static int tmp51 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp51)
  {
    tmp48 = GreaterEq(data->simulationInfo->realParameter[63] /* motor._inertiaStator._J PARAM */,0.0);
    if(!tmp48)
    {
      tmp50 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[63] /* motor._inertiaStator._J PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp49),tmp50);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Mechanics/Rotational.mo",2410,7,2410,65,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.inertiaStator.J >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp51 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 301
 type: ALGORITHM
 
   assert(motor.inertiaStator.stateSelect >= StateSelect.never and motor.inertiaStator.stateSelect <= StateSelect.always, "Variable violating min/max constraint: StateSelect.never <= motor.inertiaStator.stateSelect <= StateSelect.always, has value: " + String(motor.inertiaStator.stateSelect, "d"));
 */
void PW_PowerSystem_eqFunction_301(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,301};
  modelica_boolean tmp52;
  modelica_boolean tmp53;
  static const MMC_DEFSTRINGLIT(tmp54,126,"Variable violating min/max constraint: StateSelect.never <= motor.inertiaStator.stateSelect <= StateSelect.always, has value: ");
  modelica_string tmp55;
  static int tmp56 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp56)
  {
    tmp52 = GreaterEq((modelica_integer)data->simulationInfo->integerParameter[3] /* motor._inertiaStator._stateSelect PARAM */,1);
    tmp53 = LessEq((modelica_integer)data->simulationInfo->integerParameter[3] /* motor._inertiaStator._stateSelect PARAM */,5);
    if(!(tmp52 && tmp53))
    {
      tmp55 = modelica_integer_to_modelica_string_format((modelica_integer)data->simulationInfo->integerParameter[3] /* motor._inertiaStator._stateSelect PARAM */, (modelica_string) mmc_strings_len1[100]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp54),tmp55);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Mechanics/Rotational.mo",2411,7,2413,61,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.inertiaStator.stateSelect >= StateSelect.never and motor.inertiaStator.stateSelect <= StateSelect.always", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp56 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 302
 type: ALGORITHM
 
   assert(motor.friction.frictionParameters.PRef >= 0.0, "Variable violating min constraint: 0.0 <= motor.friction.frictionParameters.PRef, has value: " + String(motor.friction.frictionParameters.PRef, "g"));
 */
void PW_PowerSystem_eqFunction_302(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,302};
  modelica_boolean tmp57;
  static const MMC_DEFSTRINGLIT(tmp58,93,"Variable violating min constraint: 0.0 <= motor.friction.frictionParameters.PRef, has value: ");
  modelica_string tmp59;
  static int tmp60 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp60)
  {
    tmp57 = GreaterEq(data->simulationInfo->realParameter[48] /* motor._friction._frictionParameters._PRef PARAM */,0.0);
    if(!tmp57)
    {
      tmp59 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[48] /* motor._friction._frictionParameters._PRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp58),tmp59);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11050,7,11051,44,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.friction.frictionParameters.PRef >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp60 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 303
 type: ALGORITHM
 
   assert(motor.friction.frictionParameters.wRef >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.friction.frictionParameters.wRef, has value: " + String(motor.friction.frictionParameters.wRef, "g"));
 */
void PW_PowerSystem_eqFunction_303(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,303};
  modelica_boolean tmp61;
  static const MMC_DEFSTRINGLIT(tmp62,96,"Variable violating min constraint: 1e-060 <= motor.friction.frictionParameters.wRef, has value: ");
  modelica_string tmp63;
  static int tmp64 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp64)
  {
    tmp61 = GreaterEq(data->simulationInfo->realParameter[54] /* motor._friction._frictionParameters._wRef PARAM */,1e-060);
    if(!tmp61)
    {
      tmp63 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[54] /* motor._friction._frictionParameters._wRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp62),tmp63);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11052,7,11054,60,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.friction.frictionParameters.wRef >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp64 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 304
 type: ALGORITHM
 
   assert(motor.friction.frictionParameters.power_w >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.friction.frictionParameters.power_w, has value: " + String(motor.friction.frictionParameters.power_w, "g"));
 */
void PW_PowerSystem_eqFunction_304(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,304};
  modelica_boolean tmp65;
  static const MMC_DEFSTRINGLIT(tmp66,99,"Variable violating min constraint: 1e-060 <= motor.friction.frictionParameters.power_w, has value: ");
  modelica_string tmp67;
  static int tmp68 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp68)
  {
    tmp65 = GreaterEq(data->simulationInfo->realParameter[50] /* motor._friction._frictionParameters._power_w PARAM */,1e-060);
    if(!tmp65)
    {
      tmp67 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[50] /* motor._friction._frictionParameters._power_w PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp66),tmp67);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11055,7,11056,62,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.friction.frictionParameters.power_w >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp68 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 305
 type: ALGORITHM
 
   assert(motor.coreParameters.PRef >= 0.0, "Variable violating min constraint: 0.0 <= motor.coreParameters.PRef, has value: " + String(motor.coreParameters.PRef, "g"));
 */
void PW_PowerSystem_eqFunction_305(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,305};
  modelica_boolean tmp69;
  static const MMC_DEFSTRINGLIT(tmp70,80,"Variable violating min constraint: 0.0 <= motor.coreParameters.PRef, has value: ");
  modelica_string tmp71;
  static int tmp72 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp72)
  {
    tmp69 = GreaterEq(data->simulationInfo->realParameter[42] /* motor._coreParameters._PRef PARAM */,0.0);
    if(!tmp69)
    {
      tmp71 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[42] /* motor._coreParameters._PRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp70),tmp71);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11114,7,11115,64,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.coreParameters.PRef >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp72 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 306
 type: ALGORITHM
 
   assert(motor.coreParameters.VRef >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.coreParameters.VRef, has value: " + String(motor.coreParameters.VRef, "g"));
 */
void PW_PowerSystem_eqFunction_306(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,306};
  modelica_boolean tmp73;
  static const MMC_DEFSTRINGLIT(tmp74,83,"Variable violating min constraint: 1e-060 <= motor.coreParameters.VRef, has value: ");
  modelica_string tmp75;
  static int tmp76 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp76)
  {
    tmp73 = GreaterEq(data->simulationInfo->realParameter[43] /* motor._coreParameters._VRef PARAM */,1e-060);
    if(!tmp73)
    {
      tmp75 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[43] /* motor._coreParameters._VRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp74),tmp75);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11116,7,11117,79,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.coreParameters.VRef >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp76 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 307
 type: ALGORITHM
 
   assert(motor.coreParameters.wRef >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.coreParameters.wRef, has value: " + String(motor.coreParameters.wRef, "g"));
 */
void PW_PowerSystem_eqFunction_307(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,307};
  modelica_boolean tmp77;
  static const MMC_DEFSTRINGLIT(tmp78,83,"Variable violating min constraint: 1e-060 <= motor.coreParameters.wRef, has value: ");
  modelica_string tmp79;
  static int tmp80 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp80)
  {
    tmp77 = GreaterEq(data->simulationInfo->realParameter[46] /* motor._coreParameters._wRef PARAM */,1e-060);
    if(!tmp77)
    {
      tmp79 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[46] /* motor._coreParameters._wRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp78),tmp79);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11118,7,11119,78,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.coreParameters.wRef >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp80 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 308
 type: ALGORITHM
 
   assert(motor.coreParameters.ratioHysteresis >= 0.0 and motor.coreParameters.ratioHysteresis <= 1.0, "Variable violating min/max constraint: 0.0 <= motor.coreParameters.ratioHysteresis <= 1.0, has value: " + String(motor.coreParameters.ratioHysteresis, "g"));
 */
void PW_PowerSystem_eqFunction_308(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,308};
  modelica_boolean tmp81;
  modelica_boolean tmp82;
  static const MMC_DEFSTRINGLIT(tmp83,102,"Variable violating min/max constraint: 0.0 <= motor.coreParameters.ratioHysteresis <= 1.0, has value: ");
  modelica_string tmp84;
  static int tmp85 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp85)
  {
    tmp81 = GreaterEq(data->simulationInfo->realParameter[44] /* motor._coreParameters._ratioHysteresis PARAM */,0.0);
    tmp82 = LessEq(data->simulationInfo->realParameter[44] /* motor._coreParameters._ratioHysteresis PARAM */,1.0);
    if(!(tmp81 && tmp82))
    {
      tmp84 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[44] /* motor._coreParameters._ratioHysteresis PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp83),tmp84);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11121,7,11125,92,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.coreParameters.ratioHysteresis >= 0.0 and motor.coreParameters.ratioHysteresis <= 1.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp85 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 309
 type: ALGORITHM
 
   assert(motor.strayLoadParameters.PRef >= 0.0, "Variable violating min constraint: 0.0 <= motor.strayLoadParameters.PRef, has value: " + String(motor.strayLoadParameters.PRef, "g"));
 */
void PW_PowerSystem_eqFunction_309(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,309};
  modelica_boolean tmp86;
  static const MMC_DEFSTRINGLIT(tmp87,85,"Variable violating min constraint: 0.0 <= motor.strayLoadParameters.PRef, has value: ");
  modelica_string tmp88;
  static int tmp89 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp89)
  {
    tmp86 = GreaterEq(data->simulationInfo->realParameter[82] /* motor._strayLoadParameters._PRef PARAM */,0.0);
    if(!tmp86)
    {
      tmp88 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[82] /* motor._strayLoadParameters._PRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp87),tmp88);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11090,7,11091,55,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.strayLoadParameters.PRef >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp89 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 310
 type: ALGORITHM
 
   assert(motor.strayLoadParameters.IRef >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.strayLoadParameters.IRef, has value: " + String(motor.strayLoadParameters.IRef, "g"));
 */
void PW_PowerSystem_eqFunction_310(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,310};
  modelica_boolean tmp90;
  static const MMC_DEFSTRINGLIT(tmp91,88,"Variable violating min constraint: 1e-060 <= motor.strayLoadParameters.IRef, has value: ");
  modelica_string tmp92;
  static int tmp93 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp93)
  {
    tmp90 = GreaterEq(data->simulationInfo->realParameter[81] /* motor._strayLoadParameters._IRef PARAM */,1e-060);
    if(!tmp90)
    {
      tmp92 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[81] /* motor._strayLoadParameters._IRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp91),tmp92);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11092,7,11093,52,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.strayLoadParameters.IRef >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp93 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 311
 type: ALGORITHM
 
   assert(motor.strayLoadParameters.wRef >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.strayLoadParameters.wRef, has value: " + String(motor.strayLoadParameters.wRef, "g"));
 */
void PW_PowerSystem_eqFunction_311(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,311};
  modelica_boolean tmp94;
  static const MMC_DEFSTRINGLIT(tmp95,88,"Variable violating min constraint: 1e-060 <= motor.strayLoadParameters.wRef, has value: ");
  modelica_string tmp96;
  static int tmp97 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp97)
  {
    tmp94 = GreaterEq(data->simulationInfo->realParameter[85] /* motor._strayLoadParameters._wRef PARAM */,1e-060);
    if(!tmp94)
    {
      tmp96 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[85] /* motor._strayLoadParameters._wRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp95),tmp96);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11094,7,11096,57,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.strayLoadParameters.wRef >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp97 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 312
 type: ALGORITHM
 
   assert(motor.strayLoadParameters.power_w >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.strayLoadParameters.power_w, has value: " + String(motor.strayLoadParameters.power_w, "g"));
 */
void PW_PowerSystem_eqFunction_312(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,312};
  modelica_boolean tmp98;
  static const MMC_DEFSTRINGLIT(tmp99,91,"Variable violating min constraint: 1e-060 <= motor.strayLoadParameters.power_w, has value: ");
  modelica_string tmp100;
  static int tmp101 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp101)
  {
    tmp98 = GreaterEq(data->simulationInfo->realParameter[83] /* motor._strayLoadParameters._power_w PARAM */,1e-060);
    if(!tmp98)
    {
      tmp100 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[83] /* motor._strayLoadParameters._power_w PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp99),tmp100);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11097,7,11098,69,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.strayLoadParameters.power_w >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp101 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 313
 type: ALGORITHM
 
   assert(motor.ra.T >= 0.0, "Variable violating min constraint: 0.0 <= motor.ra.T, has value: " + String(motor.ra.T, "g"));
 */
void PW_PowerSystem_eqFunction_313(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,313};
  modelica_boolean tmp102;
  static const MMC_DEFSTRINGLIT(tmp103,65,"Variable violating min constraint: 0.0 <= motor.ra.T, has value: ");
  modelica_string tmp104;
  static int tmp105 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp105)
  {
    tmp102 = GreaterEq(data->simulationInfo->realParameter[68] /* motor._ra._T PARAM */,0.0);
    if(!tmp102)
    {
      tmp104 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[68] /* motor._ra._T PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp103),tmp104);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Interfaces.mo",309,5,310,99,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.ra.T >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp105 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 314
 type: ALGORITHM
 
   assert(motor.ra.T_ref >= 0.0, "Variable violating min constraint: 0.0 <= motor.ra.T_ref, has value: " + String(motor.ra.T_ref, "g"));
 */
void PW_PowerSystem_eqFunction_314(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,314};
  modelica_boolean tmp106;
  static const MMC_DEFSTRINGLIT(tmp107,69,"Variable violating min constraint: 0.0 <= motor.ra.T_ref, has value: ");
  modelica_string tmp108;
  static int tmp109 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp109)
  {
    tmp106 = GreaterEq(data->simulationInfo->realParameter[69] /* motor._ra._T_ref PARAM */,0.0);
    if(!tmp106)
    {
      tmp108 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[69] /* motor._ra._T_ref PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp107),tmp108);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Basic.mo",56,5,56,66,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.ra.T_ref >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp109 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 315
 type: ALGORITHM
 
   assert(motor.core.coreParameters.PRef >= 0.0, "Variable violating min constraint: 0.0 <= motor.core.coreParameters.PRef, has value: " + String(motor.core.coreParameters.PRef, "g"));
 */
void PW_PowerSystem_eqFunction_315(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,315};
  modelica_boolean tmp110;
  static const MMC_DEFSTRINGLIT(tmp111,85,"Variable violating min constraint: 0.0 <= motor.core.coreParameters.PRef, has value: ");
  modelica_string tmp112;
  static int tmp113 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp113)
  {
    tmp110 = GreaterEq(data->simulationInfo->realParameter[36] /* motor._core._coreParameters._PRef PARAM */,0.0);
    if(!tmp110)
    {
      tmp112 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[36] /* motor._core._coreParameters._PRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp111),tmp112);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11114,7,11115,64,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.core.coreParameters.PRef >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp113 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 316
 type: ALGORITHM
 
   assert(motor.core.coreParameters.VRef >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.core.coreParameters.VRef, has value: " + String(motor.core.coreParameters.VRef, "g"));
 */
void PW_PowerSystem_eqFunction_316(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,316};
  modelica_boolean tmp114;
  static const MMC_DEFSTRINGLIT(tmp115,88,"Variable violating min constraint: 1e-060 <= motor.core.coreParameters.VRef, has value: ");
  modelica_string tmp116;
  static int tmp117 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp117)
  {
    tmp114 = GreaterEq(data->simulationInfo->realParameter[37] /* motor._core._coreParameters._VRef PARAM */,1e-060);
    if(!tmp114)
    {
      tmp116 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[37] /* motor._core._coreParameters._VRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp115),tmp116);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11116,7,11117,79,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.core.coreParameters.VRef >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp117 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 317
 type: ALGORITHM
 
   assert(motor.core.coreParameters.wRef >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.core.coreParameters.wRef, has value: " + String(motor.core.coreParameters.wRef, "g"));
 */
void PW_PowerSystem_eqFunction_317(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,317};
  modelica_boolean tmp118;
  static const MMC_DEFSTRINGLIT(tmp119,88,"Variable violating min constraint: 1e-060 <= motor.core.coreParameters.wRef, has value: ");
  modelica_string tmp120;
  static int tmp121 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp121)
  {
    tmp118 = GreaterEq(data->simulationInfo->realParameter[40] /* motor._core._coreParameters._wRef PARAM */,1e-060);
    if(!tmp118)
    {
      tmp120 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[40] /* motor._core._coreParameters._wRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp119),tmp120);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11118,7,11119,78,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.core.coreParameters.wRef >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp121 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 318
 type: ALGORITHM
 
   assert(motor.core.coreParameters.ratioHysteresis >= 0.0 and motor.core.coreParameters.ratioHysteresis <= 1.0, "Variable violating min/max constraint: 0.0 <= motor.core.coreParameters.ratioHysteresis <= 1.0, has value: " + String(motor.core.coreParameters.ratioHysteresis, "g"));
 */
void PW_PowerSystem_eqFunction_318(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,318};
  modelica_boolean tmp122;
  modelica_boolean tmp123;
  static const MMC_DEFSTRINGLIT(tmp124,107,"Variable violating min/max constraint: 0.0 <= motor.core.coreParameters.ratioHysteresis <= 1.0, has value: ");
  modelica_string tmp125;
  static int tmp126 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp126)
  {
    tmp122 = GreaterEq(data->simulationInfo->realParameter[38] /* motor._core._coreParameters._ratioHysteresis PARAM */,0.0);
    tmp123 = LessEq(data->simulationInfo->realParameter[38] /* motor._core._coreParameters._ratioHysteresis PARAM */,1.0);
    if(!(tmp122 && tmp123))
    {
      tmp125 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[38] /* motor._core._coreParameters._ratioHysteresis PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp124),tmp125);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11121,7,11125,92,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.core.coreParameters.ratioHysteresis >= 0.0 and motor.core.coreParameters.ratioHysteresis <= 1.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp126 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 319
 type: ALGORITHM
 
   assert(motor.strayLoad.strayLoadParameters.PRef >= 0.0, "Variable violating min constraint: 0.0 <= motor.strayLoad.strayLoadParameters.PRef, has value: " + String(motor.strayLoad.strayLoadParameters.PRef, "g"));
 */
void PW_PowerSystem_eqFunction_319(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,319};
  modelica_boolean tmp127;
  static const MMC_DEFSTRINGLIT(tmp128,95,"Variable violating min constraint: 0.0 <= motor.strayLoad.strayLoadParameters.PRef, has value: ");
  modelica_string tmp129;
  static int tmp130 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp130)
  {
    tmp127 = GreaterEq(data->simulationInfo->realParameter[77] /* motor._strayLoad._strayLoadParameters._PRef PARAM */,0.0);
    if(!tmp127)
    {
      tmp129 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[77] /* motor._strayLoad._strayLoadParameters._PRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp128),tmp129);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11090,7,11091,55,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.strayLoad.strayLoadParameters.PRef >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp130 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 320
 type: ALGORITHM
 
   assert(motor.strayLoad.strayLoadParameters.IRef >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.strayLoad.strayLoadParameters.IRef, has value: " + String(motor.strayLoad.strayLoadParameters.IRef, "g"));
 */
void PW_PowerSystem_eqFunction_320(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,320};
  modelica_boolean tmp131;
  static const MMC_DEFSTRINGLIT(tmp132,98,"Variable violating min constraint: 1e-060 <= motor.strayLoad.strayLoadParameters.IRef, has value: ");
  modelica_string tmp133;
  static int tmp134 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp134)
  {
    tmp131 = GreaterEq(data->simulationInfo->realParameter[76] /* motor._strayLoad._strayLoadParameters._IRef PARAM */,1e-060);
    if(!tmp131)
    {
      tmp133 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[76] /* motor._strayLoad._strayLoadParameters._IRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp132),tmp133);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11092,7,11093,52,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.strayLoad.strayLoadParameters.IRef >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp134 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 321
 type: ALGORITHM
 
   assert(motor.strayLoad.strayLoadParameters.wRef >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.strayLoad.strayLoadParameters.wRef, has value: " + String(motor.strayLoad.strayLoadParameters.wRef, "g"));
 */
void PW_PowerSystem_eqFunction_321(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,321};
  modelica_boolean tmp135;
  static const MMC_DEFSTRINGLIT(tmp136,98,"Variable violating min constraint: 1e-060 <= motor.strayLoad.strayLoadParameters.wRef, has value: ");
  modelica_string tmp137;
  static int tmp138 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp138)
  {
    tmp135 = GreaterEq(data->simulationInfo->realParameter[80] /* motor._strayLoad._strayLoadParameters._wRef PARAM */,1e-060);
    if(!tmp135)
    {
      tmp137 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[80] /* motor._strayLoad._strayLoadParameters._wRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp136),tmp137);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11094,7,11096,57,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.strayLoad.strayLoadParameters.wRef >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp138 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 322
 type: ALGORITHM
 
   assert(motor.strayLoad.strayLoadParameters.power_w >= 1e-060, "Variable violating min constraint: 1e-060 <= motor.strayLoad.strayLoadParameters.power_w, has value: " + String(motor.strayLoad.strayLoadParameters.power_w, "g"));
 */
void PW_PowerSystem_eqFunction_322(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,322};
  modelica_boolean tmp139;
  static const MMC_DEFSTRINGLIT(tmp140,101,"Variable violating min constraint: 1e-060 <= motor.strayLoad.strayLoadParameters.power_w, has value: ");
  modelica_string tmp141;
  static int tmp142 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp142)
  {
    tmp139 = GreaterEq(data->simulationInfo->realParameter[78] /* motor._strayLoad._strayLoadParameters._power_w PARAM */,1e-060);
    if(!tmp139)
    {
      tmp141 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[78] /* motor._strayLoad._strayLoadParameters._power_w PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp140),tmp141);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11097,7,11098,69,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.strayLoad.strayLoadParameters.power_w >= 1e-060", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp142 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 323
 type: ALGORITHM
 
   assert(motor.TeRef >= 0.0, "Variable violating min constraint: 0.0 <= motor.TeRef, has value: " + String(motor.TeRef, "g"));
 */
void PW_PowerSystem_eqFunction_323(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,323};
  modelica_boolean tmp143;
  static const MMC_DEFSTRINGLIT(tmp144,66,"Variable violating min constraint: 0.0 <= motor.TeRef, has value: ");
  modelica_string tmp145;
  static int tmp146 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp146)
  {
    tmp143 = GreaterEq(data->simulationInfo->realParameter[23] /* motor._TeRef PARAM */,0.0);
    if(!tmp143)
    {
      tmp145 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[23] /* motor._TeRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp144),tmp145);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",6806,9,6808,48,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.TeRef >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp146 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 324
 type: ALGORITHM
 
   assert(motor.sigmae >= 0.0 and motor.sigmae <= 0.99, "Variable violating min/max constraint: 0.0 <= motor.sigmae <= 0.99, has value: " + String(motor.sigmae, "g"));
 */
void PW_PowerSystem_eqFunction_324(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,324};
  modelica_boolean tmp147;
  modelica_boolean tmp148;
  static const MMC_DEFSTRINGLIT(tmp149,79,"Variable violating min/max constraint: 0.0 <= motor.sigmae <= 0.99, has value: ");
  modelica_string tmp150;
  static int tmp151 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp151)
  {
    tmp147 = GreaterEq(data->simulationInfo->realParameter[75] /* motor._sigmae PARAM */,0.0);
    tmp148 = LessEq(data->simulationInfo->realParameter[75] /* motor._sigmae PARAM */,0.99);
    if(!(tmp147 && tmp148))
    {
      tmp150 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[75] /* motor._sigmae PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp149),tmp150);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",6815,9,6819,48,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.sigmae >= 0.0 and motor.sigmae <= 0.99", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp151 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 325
 type: ALGORITHM
 
   assert(motor.TeOperational >= 0.0, "Variable violating min constraint: 0.0 <= motor.TeOperational, has value: " + String(motor.TeOperational, "g"));
 */
void PW_PowerSystem_eqFunction_325(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,325};
  modelica_boolean tmp152;
  static const MMC_DEFSTRINGLIT(tmp153,74,"Variable violating min constraint: 0.0 <= motor.TeOperational, has value: ");
  modelica_string tmp154;
  static int tmp155 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp155)
  {
    tmp152 = GreaterEq(data->simulationInfo->realParameter[22] /* motor._TeOperational PARAM */,0.0);
    if(!tmp152)
    {
      tmp154 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[22] /* motor._TeOperational PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp153),tmp154);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",6820,9,6822,71,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.TeOperational >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp155 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 326
 type: ALGORITHM
 
   assert(motor.re.T >= 0.0, "Variable violating min constraint: 0.0 <= motor.re.T, has value: " + String(motor.re.T, "g"));
 */
void PW_PowerSystem_eqFunction_326(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,326};
  modelica_boolean tmp156;
  static const MMC_DEFSTRINGLIT(tmp157,65,"Variable violating min constraint: 0.0 <= motor.re.T, has value: ");
  modelica_string tmp158;
  static int tmp159 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp159)
  {
    tmp156 = GreaterEq(data->simulationInfo->realParameter[72] /* motor._re._T PARAM */,0.0);
    if(!tmp156)
    {
      tmp158 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[72] /* motor._re._T PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp157),tmp158);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Interfaces.mo",309,5,310,99,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.re.T >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp159 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 327
 type: ALGORITHM
 
   assert(motor.re.T_ref >= 0.0, "Variable violating min constraint: 0.0 <= motor.re.T_ref, has value: " + String(motor.re.T_ref, "g"));
 */
void PW_PowerSystem_eqFunction_327(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,327};
  modelica_boolean tmp160;
  static const MMC_DEFSTRINGLIT(tmp161,69,"Variable violating min constraint: 0.0 <= motor.re.T_ref, has value: ");
  modelica_string tmp162;
  static int tmp163 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp163)
  {
    tmp160 = GreaterEq(data->simulationInfo->realParameter[73] /* motor._re._T_ref PARAM */,0.0);
    if(!tmp160)
    {
      tmp162 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[73] /* motor._re._T_ref PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp161),tmp162);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Basic.mo",56,5,56,66,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.re.T_ref >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp163 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 328
 type: ALGORITHM
 
   assert(motor.thermalAmbient.Ta >= 0.0, "Variable violating min constraint: 0.0 <= motor.thermalAmbient.Ta, has value: " + String(motor.thermalAmbient.Ta, "g"));
 */
void PW_PowerSystem_eqFunction_328(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,328};
  modelica_boolean tmp164;
  static const MMC_DEFSTRINGLIT(tmp165,78,"Variable violating min constraint: 0.0 <= motor.thermalAmbient.Ta, has value: ");
  modelica_string tmp166;
  static int tmp167 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp167)
  {
    tmp164 = GreaterEq(data->simulationInfo->realParameter[86] /* motor._thermalAmbient._Ta PARAM */,0.0);
    if(!tmp164)
    {
      tmp166 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[86] /* motor._thermalAmbient._Ta PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp165),tmp166);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",13755,9,13757,63,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.thermalAmbient.Ta >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp167 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 329
 type: ALGORITHM
 
   assert(motor.thermalAmbient.temperatureCore.T >= 0.0, "Variable violating min constraint: 0.0 <= motor.thermalAmbient.temperatureCore.T, has value: " + String(motor.thermalAmbient.temperatureCore.T, "g"));
 */
void PW_PowerSystem_eqFunction_329(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,329};
  modelica_boolean tmp168;
  static const MMC_DEFSTRINGLIT(tmp169,93,"Variable violating min constraint: 0.0 <= motor.thermalAmbient.temperatureCore.T, has value: ");
  modelica_string tmp170;
  static int tmp171 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp171)
  {
    tmp168 = GreaterEq(data->simulationInfo->realParameter[91] /* motor._thermalAmbient._temperatureCore._T PARAM */,0.0);
    if(!tmp168)
    {
      tmp170 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[91] /* motor._thermalAmbient._temperatureCore._T PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp169),tmp170);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Thermal/HeatTransfer.mo",1363,7,1363,75,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.thermalAmbient.temperatureCore.T >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp171 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 330
 type: ALGORITHM
 
   assert(motor.thermalAmbient.temperatureStrayLoad.T >= 0.0, "Variable violating min constraint: 0.0 <= motor.thermalAmbient.temperatureStrayLoad.T, has value: " + String(motor.thermalAmbient.temperatureStrayLoad.T, "g"));
 */
void PW_PowerSystem_eqFunction_330(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,330};
  modelica_boolean tmp172;
  static const MMC_DEFSTRINGLIT(tmp173,98,"Variable violating min constraint: 0.0 <= motor.thermalAmbient.temperatureStrayLoad.T, has value: ");
  modelica_string tmp174;
  static int tmp175 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp175)
  {
    tmp172 = GreaterEq(data->simulationInfo->realParameter[93] /* motor._thermalAmbient._temperatureStrayLoad._T PARAM */,0.0);
    if(!tmp172)
    {
      tmp174 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[93] /* motor._thermalAmbient._temperatureStrayLoad._T PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp173),tmp174);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Thermal/HeatTransfer.mo",1363,7,1363,75,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.thermalAmbient.temperatureStrayLoad.T >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp175 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 331
 type: ALGORITHM
 
   assert(motor.thermalAmbient.temperatureFriction.T >= 0.0, "Variable violating min constraint: 0.0 <= motor.thermalAmbient.temperatureFriction.T, has value: " + String(motor.thermalAmbient.temperatureFriction.T, "g"));
 */
void PW_PowerSystem_eqFunction_331(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,331};
  modelica_boolean tmp176;
  static const MMC_DEFSTRINGLIT(tmp177,97,"Variable violating min constraint: 0.0 <= motor.thermalAmbient.temperatureFriction.T, has value: ");
  modelica_string tmp178;
  static int tmp179 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp179)
  {
    tmp176 = GreaterEq(data->simulationInfo->realParameter[92] /* motor._thermalAmbient._temperatureFriction._T PARAM */,0.0);
    if(!tmp176)
    {
      tmp178 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[92] /* motor._thermalAmbient._temperatureFriction._T PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp177),tmp178);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Thermal/HeatTransfer.mo",1363,7,1363,75,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.thermalAmbient.temperatureFriction.T >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp179 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 332
 type: ALGORITHM
 
   assert(motor.thermalAmbient.temperatureBrush.T >= 0.0, "Variable violating min constraint: 0.0 <= motor.thermalAmbient.temperatureBrush.T, has value: " + String(motor.thermalAmbient.temperatureBrush.T, "g"));
 */
void PW_PowerSystem_eqFunction_332(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,332};
  modelica_boolean tmp180;
  static const MMC_DEFSTRINGLIT(tmp181,94,"Variable violating min constraint: 0.0 <= motor.thermalAmbient.temperatureBrush.T, has value: ");
  modelica_string tmp182;
  static int tmp183 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp183)
  {
    tmp180 = GreaterEq(data->simulationInfo->realParameter[90] /* motor._thermalAmbient._temperatureBrush._T PARAM */,0.0);
    if(!tmp180)
    {
      tmp182 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[90] /* motor._thermalAmbient._temperatureBrush._T PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp181),tmp182);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Thermal/HeatTransfer.mo",1363,7,1363,75,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.thermalAmbient.temperatureBrush.T >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp183 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 333
 type: ALGORITHM
 
   assert(motor.thermalAmbient.Te >= 0.0, "Variable violating min constraint: 0.0 <= motor.thermalAmbient.Te, has value: " + String(motor.thermalAmbient.Te, "g"));
 */
void PW_PowerSystem_eqFunction_333(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,333};
  modelica_boolean tmp184;
  static const MMC_DEFSTRINGLIT(tmp185,78,"Variable violating min constraint: 0.0 <= motor.thermalAmbient.Te, has value: ");
  modelica_string tmp186;
  static int tmp187 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp187)
  {
    tmp184 = GreaterEq(data->simulationInfo->realParameter[87] /* motor._thermalAmbient._Te PARAM */,0.0);
    if(!tmp184)
    {
      tmp186 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[87] /* motor._thermalAmbient._Te PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp185),tmp186);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",12421,9,12423,63,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.thermalAmbient.Te >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp187 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 334
 type: ALGORITHM
 
   assert(motor_frictionParameters.PRef >= 0.0, "Variable violating min constraint: 0.0 <= motor_frictionParameters.PRef, has value: " + String(motor_frictionParameters.PRef, "g"));
 */
void PW_PowerSystem_eqFunction_334(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,334};
  modelica_boolean tmp188;
  static const MMC_DEFSTRINGLIT(tmp189,84,"Variable violating min constraint: 0.0 <= motor_frictionParameters.PRef, has value: ");
  modelica_string tmp190;
  static int tmp191 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp191)
  {
    tmp188 = GreaterEq(data->simulationInfo->realParameter[96] /* motor_frictionParameters._PRef PARAM */,0.0);
    if(!tmp188)
    {
      tmp190 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[96] /* motor_frictionParameters._PRef PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp189),tmp190);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",11050,7,11051,44,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor_frictionParameters.PRef >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp191 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 335
 type: ALGORITHM
 
   assert(idealCommutingSwitch1.T >= 0.0, "Variable violating min constraint: 0.0 <= idealCommutingSwitch1.T, has value: " + String(idealCommutingSwitch1.T, "g"));
 */
void PW_PowerSystem_eqFunction_335(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,335};
  modelica_boolean tmp192;
  static const MMC_DEFSTRINGLIT(tmp193,78,"Variable violating min constraint: 0.0 <= idealCommutingSwitch1.T, has value: ");
  modelica_string tmp194;
  static int tmp195 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp195)
  {
    tmp192 = GreaterEq(data->simulationInfo->realParameter[5] /* idealCommutingSwitch1._T PARAM */,0.0);
    if(!tmp192)
    {
      tmp194 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[5] /* idealCommutingSwitch1._T PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp193),tmp194);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Interfaces.mo",309,5,310,99,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nidealCommutingSwitch1.T >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp195 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 336
 type: ALGORITHM
 
   assert(idealCommutingSwitch1.Ron >= 0.0, "Variable violating min constraint: 0.0 <= idealCommutingSwitch1.Ron, has value: " + String(idealCommutingSwitch1.Ron, "g"));
 */
void PW_PowerSystem_eqFunction_336(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,336};
  modelica_boolean tmp196;
  static const MMC_DEFSTRINGLIT(tmp197,80,"Variable violating min constraint: 0.0 <= idealCommutingSwitch1.Ron, has value: ");
  modelica_string tmp198;
  static int tmp199 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp199)
  {
    tmp196 = GreaterEq(data->simulationInfo->realParameter[4] /* idealCommutingSwitch1._Ron PARAM */,0.0);
    if(!tmp196)
    {
      tmp198 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[4] /* idealCommutingSwitch1._Ron PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp197),tmp198);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Ideal.mo",145,5,145,80,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nidealCommutingSwitch1.Ron >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp199 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 337
 type: ALGORITHM
 
   assert(idealCommutingSwitch1.Goff >= 0.0, "Variable violating min constraint: 0.0 <= idealCommutingSwitch1.Goff, has value: " + String(idealCommutingSwitch1.Goff, "g"));
 */
void PW_PowerSystem_eqFunction_337(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,337};
  modelica_boolean tmp200;
  static const MMC_DEFSTRINGLIT(tmp201,81,"Variable violating min constraint: 0.0 <= idealCommutingSwitch1.Goff, has value: ");
  modelica_string tmp202;
  static int tmp203 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp203)
  {
    tmp200 = GreaterEq(data->simulationInfo->realParameter[3] /* idealCommutingSwitch1._Goff PARAM */,0.0);
    if(!tmp200)
    {
      tmp202 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[3] /* idealCommutingSwitch1._Goff PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp201),tmp202);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Ideal.mo",146,5,147,34,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nidealCommutingSwitch1.Goff >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp203 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 338
 type: ALGORITHM
 
   assert(idealCommutingSwitch2.T >= 0.0, "Variable violating min constraint: 0.0 <= idealCommutingSwitch2.T, has value: " + String(idealCommutingSwitch2.T, "g"));
 */
void PW_PowerSystem_eqFunction_338(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,338};
  modelica_boolean tmp204;
  static const MMC_DEFSTRINGLIT(tmp205,78,"Variable violating min constraint: 0.0 <= idealCommutingSwitch2.T, has value: ");
  modelica_string tmp206;
  static int tmp207 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp207)
  {
    tmp204 = GreaterEq(data->simulationInfo->realParameter[8] /* idealCommutingSwitch2._T PARAM */,0.0);
    if(!tmp204)
    {
      tmp206 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[8] /* idealCommutingSwitch2._T PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp205),tmp206);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Interfaces.mo",309,5,310,99,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nidealCommutingSwitch2.T >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp207 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 339
 type: ALGORITHM
 
   assert(idealCommutingSwitch2.Ron >= 0.0, "Variable violating min constraint: 0.0 <= idealCommutingSwitch2.Ron, has value: " + String(idealCommutingSwitch2.Ron, "g"));
 */
void PW_PowerSystem_eqFunction_339(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,339};
  modelica_boolean tmp208;
  static const MMC_DEFSTRINGLIT(tmp209,80,"Variable violating min constraint: 0.0 <= idealCommutingSwitch2.Ron, has value: ");
  modelica_string tmp210;
  static int tmp211 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp211)
  {
    tmp208 = GreaterEq(data->simulationInfo->realParameter[7] /* idealCommutingSwitch2._Ron PARAM */,0.0);
    if(!tmp208)
    {
      tmp210 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[7] /* idealCommutingSwitch2._Ron PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp209),tmp210);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Ideal.mo",145,5,145,80,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nidealCommutingSwitch2.Ron >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp211 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 340
 type: ALGORITHM
 
   assert(idealCommutingSwitch2.Goff >= 0.0, "Variable violating min constraint: 0.0 <= idealCommutingSwitch2.Goff, has value: " + String(idealCommutingSwitch2.Goff, "g"));
 */
void PW_PowerSystem_eqFunction_340(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,340};
  modelica_boolean tmp212;
  static const MMC_DEFSTRINGLIT(tmp213,81,"Variable violating min constraint: 0.0 <= idealCommutingSwitch2.Goff, has value: ");
  modelica_string tmp214;
  static int tmp215 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp215)
  {
    tmp212 = GreaterEq(data->simulationInfo->realParameter[6] /* idealCommutingSwitch2._Goff PARAM */,0.0);
    if(!tmp212)
    {
      tmp214 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[6] /* idealCommutingSwitch2._Goff PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp213),tmp214);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Analog/Ideal.mo",146,5,147,34,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nidealCommutingSwitch2.Goff >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp215 = 1;
    }
  }
  TRACE_POP
}
int PW_PowerSystem_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  PW_PowerSystem_eqFunction_199(data, threadData);

  PW_PowerSystem_eqFunction_200(data, threadData);

  PW_PowerSystem_eqFunction_201(data, threadData);

  PW_PowerSystem_eqFunction_202(data, threadData);

  PW_PowerSystem_eqFunction_203(data, threadData);

  PW_PowerSystem_eqFunction_204(data, threadData);

  PW_PowerSystem_eqFunction_205(data, threadData);

  PW_PowerSystem_eqFunction_206(data, threadData);

  PW_PowerSystem_eqFunction_207(data, threadData);

  PW_PowerSystem_eqFunction_208(data, threadData);

  PW_PowerSystem_eqFunction_209(data, threadData);

  PW_PowerSystem_eqFunction_210(data, threadData);

  PW_PowerSystem_eqFunction_211(data, threadData);

  PW_PowerSystem_eqFunction_212(data, threadData);

  PW_PowerSystem_eqFunction_213(data, threadData);

  PW_PowerSystem_eqFunction_214(data, threadData);

  PW_PowerSystem_eqFunction_215(data, threadData);

  PW_PowerSystem_eqFunction_216(data, threadData);

  PW_PowerSystem_eqFunction_217(data, threadData);

  PW_PowerSystem_eqFunction_218(data, threadData);

  PW_PowerSystem_eqFunction_219(data, threadData);

  PW_PowerSystem_eqFunction_220(data, threadData);

  PW_PowerSystem_eqFunction_221(data, threadData);

  PW_PowerSystem_eqFunction_222(data, threadData);

  PW_PowerSystem_eqFunction_223(data, threadData);

  PW_PowerSystem_eqFunction_224(data, threadData);

  PW_PowerSystem_eqFunction_225(data, threadData);

  PW_PowerSystem_eqFunction_226(data, threadData);

  PW_PowerSystem_eqFunction_227(data, threadData);

  PW_PowerSystem_eqFunction_228(data, threadData);

  PW_PowerSystem_eqFunction_229(data, threadData);

  PW_PowerSystem_eqFunction_230(data, threadData);

  PW_PowerSystem_eqFunction_231(data, threadData);

  PW_PowerSystem_eqFunction_232(data, threadData);

  PW_PowerSystem_eqFunction_233(data, threadData);

  PW_PowerSystem_eqFunction_234(data, threadData);

  PW_PowerSystem_eqFunction_235(data, threadData);

  PW_PowerSystem_eqFunction_236(data, threadData);

  PW_PowerSystem_eqFunction_237(data, threadData);

  PW_PowerSystem_eqFunction_238(data, threadData);

  PW_PowerSystem_eqFunction_239(data, threadData);

  PW_PowerSystem_eqFunction_240(data, threadData);

  PW_PowerSystem_eqFunction_241(data, threadData);

  PW_PowerSystem_eqFunction_242(data, threadData);

  PW_PowerSystem_eqFunction_243(data, threadData);

  PW_PowerSystem_eqFunction_244(data, threadData);

  PW_PowerSystem_eqFunction_245(data, threadData);

  PW_PowerSystem_eqFunction_246(data, threadData);

  PW_PowerSystem_eqFunction_247(data, threadData);

  PW_PowerSystem_eqFunction_248(data, threadData);

  PW_PowerSystem_eqFunction_249(data, threadData);

  PW_PowerSystem_eqFunction_250(data, threadData);

  PW_PowerSystem_eqFunction_251(data, threadData);

  PW_PowerSystem_eqFunction_252(data, threadData);

  PW_PowerSystem_eqFunction_253(data, threadData);

  PW_PowerSystem_eqFunction_254(data, threadData);

  PW_PowerSystem_eqFunction_255(data, threadData);

  PW_PowerSystem_eqFunction_256(data, threadData);

  PW_PowerSystem_eqFunction_257(data, threadData);

  PW_PowerSystem_eqFunction_258(data, threadData);

  PW_PowerSystem_eqFunction_259(data, threadData);

  PW_PowerSystem_eqFunction_260(data, threadData);

  PW_PowerSystem_eqFunction_261(data, threadData);

  PW_PowerSystem_eqFunction_262(data, threadData);

  PW_PowerSystem_eqFunction_263(data, threadData);

  PW_PowerSystem_eqFunction_264(data, threadData);

  PW_PowerSystem_eqFunction_265(data, threadData);

  PW_PowerSystem_eqFunction_266(data, threadData);

  PW_PowerSystem_eqFunction_267(data, threadData);

  PW_PowerSystem_eqFunction_268(data, threadData);

  PW_PowerSystem_eqFunction_269(data, threadData);

  PW_PowerSystem_eqFunction_270(data, threadData);

  PW_PowerSystem_eqFunction_271(data, threadData);

  PW_PowerSystem_eqFunction_272(data, threadData);

  PW_PowerSystem_eqFunction_273(data, threadData);

  PW_PowerSystem_eqFunction_274(data, threadData);

  PW_PowerSystem_eqFunction_275(data, threadData);

  PW_PowerSystem_eqFunction_276(data, threadData);

  PW_PowerSystem_eqFunction_277(data, threadData);

  PW_PowerSystem_eqFunction_278(data, threadData);

  PW_PowerSystem_eqFunction_279(data, threadData);

  PW_PowerSystem_eqFunction_280(data, threadData);

  PW_PowerSystem_eqFunction_281(data, threadData);

  PW_PowerSystem_eqFunction_282(data, threadData);

  PW_PowerSystem_eqFunction_283(data, threadData);

  PW_PowerSystem_eqFunction_284(data, threadData);

  PW_PowerSystem_eqFunction_285(data, threadData);

  PW_PowerSystem_eqFunction_286(data, threadData);

  PW_PowerSystem_eqFunction_287(data, threadData);

  PW_PowerSystem_eqFunction_288(data, threadData);

  PW_PowerSystem_eqFunction_289(data, threadData);

  PW_PowerSystem_eqFunction_290(data, threadData);

  PW_PowerSystem_eqFunction_291(data, threadData);

  PW_PowerSystem_eqFunction_292(data, threadData);

  PW_PowerSystem_eqFunction_293(data, threadData);

  PW_PowerSystem_eqFunction_294(data, threadData);

  PW_PowerSystem_eqFunction_295(data, threadData);

  PW_PowerSystem_eqFunction_296(data, threadData);

  PW_PowerSystem_eqFunction_297(data, threadData);

  PW_PowerSystem_eqFunction_298(data, threadData);

  PW_PowerSystem_eqFunction_299(data, threadData);

  PW_PowerSystem_eqFunction_300(data, threadData);

  PW_PowerSystem_eqFunction_301(data, threadData);

  PW_PowerSystem_eqFunction_302(data, threadData);

  PW_PowerSystem_eqFunction_303(data, threadData);

  PW_PowerSystem_eqFunction_304(data, threadData);

  PW_PowerSystem_eqFunction_305(data, threadData);

  PW_PowerSystem_eqFunction_306(data, threadData);

  PW_PowerSystem_eqFunction_307(data, threadData);

  PW_PowerSystem_eqFunction_308(data, threadData);

  PW_PowerSystem_eqFunction_309(data, threadData);

  PW_PowerSystem_eqFunction_310(data, threadData);

  PW_PowerSystem_eqFunction_311(data, threadData);

  PW_PowerSystem_eqFunction_312(data, threadData);

  PW_PowerSystem_eqFunction_313(data, threadData);

  PW_PowerSystem_eqFunction_314(data, threadData);

  PW_PowerSystem_eqFunction_315(data, threadData);

  PW_PowerSystem_eqFunction_316(data, threadData);

  PW_PowerSystem_eqFunction_317(data, threadData);

  PW_PowerSystem_eqFunction_318(data, threadData);

  PW_PowerSystem_eqFunction_319(data, threadData);

  PW_PowerSystem_eqFunction_320(data, threadData);

  PW_PowerSystem_eqFunction_321(data, threadData);

  PW_PowerSystem_eqFunction_322(data, threadData);

  PW_PowerSystem_eqFunction_323(data, threadData);

  PW_PowerSystem_eqFunction_324(data, threadData);

  PW_PowerSystem_eqFunction_325(data, threadData);

  PW_PowerSystem_eqFunction_326(data, threadData);

  PW_PowerSystem_eqFunction_327(data, threadData);

  PW_PowerSystem_eqFunction_328(data, threadData);

  PW_PowerSystem_eqFunction_329(data, threadData);

  PW_PowerSystem_eqFunction_330(data, threadData);

  PW_PowerSystem_eqFunction_331(data, threadData);

  PW_PowerSystem_eqFunction_332(data, threadData);

  PW_PowerSystem_eqFunction_333(data, threadData);

  PW_PowerSystem_eqFunction_334(data, threadData);

  PW_PowerSystem_eqFunction_335(data, threadData);

  PW_PowerSystem_eqFunction_336(data, threadData);

  PW_PowerSystem_eqFunction_337(data, threadData);

  PW_PowerSystem_eqFunction_338(data, threadData);

  PW_PowerSystem_eqFunction_339(data, threadData);

  PW_PowerSystem_eqFunction_340(data, threadData);
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

