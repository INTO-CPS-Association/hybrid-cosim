/* Initialization */
#include "PW_PowerSystem_model.h"
#include "PW_PowerSystem_11mix.h"
#include "PW_PowerSystem_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void PW_PowerSystem_functionInitialEquations_0(DATA *data, threadData_t *threadData);


/*
 equation index: 1
 type: SIMPLE_ASSIGN
 motor._brush._heatPort._Q_flow = 0.0
 */
void PW_PowerSystem_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  data->localData[0]->realVars[30] /* motor._brush._heatPort._Q_flow variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 2
 type: SIMPLE_ASSIGN
 motor._core._heatPort._Q_flow = 0.0
 */
void PW_PowerSystem_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  data->localData[0]->realVars[37] /* motor._core._heatPort._Q_flow variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 3
 type: SIMPLE_ASSIGN
 motor._core._n._i = 0.0
 */
void PW_PowerSystem_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  data->localData[0]->realVars[40] /* motor._core._n._i variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 4
 type: SIMPLE_ASSIGN
 motor._strayLoad._heatPort._Q_flow = 0.0
 */
void PW_PowerSystem_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  data->localData[0]->realVars[79] /* motor._strayLoad._heatPort._Q_flow variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 5
 type: SIMPLE_ASSIGN
 motor._strayLoad._flange._tau = 0.0
 */
void PW_PowerSystem_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  data->localData[0]->realVars[78] /* motor._strayLoad._flange._tau variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 6
 type: SIMPLE_ASSIGN
 motor._compoundDCExcitation._pin_sen._i = 0.0
 */
void PW_PowerSystem_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  data->localData[0]->realVars[33] /* motor._compoundDCExcitation._pin_sen._i variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 7
 type: SIMPLE_ASSIGN
 voltage_ground._p._v = 0.0
 */
void PW_PowerSystem_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  data->localData[0]->realVars[105] /* voltage_ground._p._v variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 8
 type: SIMPLE_ASSIGN
 up_ground._p._v = 0.0
 */
void PW_PowerSystem_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  data->localData[0]->realVars[101] /* up_ground._p._v variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 9
 type: SIMPLE_ASSIGN
 motor._groundSE._p._v = 0.0
 */
void PW_PowerSystem_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  data->localData[0]->realVars[50] /* motor._groundSE._p._v variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 10
 type: SIMPLE_ASSIGN
 motor._ground._p._v = 0.0
 */
void PW_PowerSystem_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  data->localData[0]->realVars[49] /* motor._ground._p._v variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 11
 type: SIMPLE_ASSIGN
 motor._inertiaStator._flange_b._tau = 0.0
 */
void PW_PowerSystem_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  data->localData[0]->realVars[55] /* motor._inertiaStator._flange_b._tau variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 12
 type: SIMPLE_ASSIGN
 motor._compoundDCExcitation._pin_sep._i = 0.0
 */
void PW_PowerSystem_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  data->localData[0]->realVars[34] /* motor._compoundDCExcitation._pin_sep._i variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 13
 type: SIMPLE_ASSIGN
 motor._internalThermalPort._heatPortExcitation._Q_flow = 0.0
 */
void PW_PowerSystem_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  data->localData[0]->realVars[61] /* motor._internalThermalPort._heatPortExcitation._Q_flow variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 14
 type: SIMPLE_ASSIGN
 motor._internalThermalPort._heatPortBrush._Q_flow = 0.0
 */
void PW_PowerSystem_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  data->localData[0]->realVars[59] /* motor._internalThermalPort._heatPortBrush._Q_flow variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 15
 type: SIMPLE_ASSIGN
 motor._internalThermalPort._heatPortFriction._Q_flow = 0.0
 */
void PW_PowerSystem_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  data->localData[0]->realVars[62] /* motor._internalThermalPort._heatPortFriction._Q_flow variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 16
 type: SIMPLE_ASSIGN
 motor._internalThermalPort._heatPortStrayLoad._Q_flow = 0.0
 */
void PW_PowerSystem_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  data->localData[0]->realVars[63] /* motor._internalThermalPort._heatPortStrayLoad._Q_flow variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 17
 type: SIMPLE_ASSIGN
 motor._internalThermalPort._heatPortCore._Q_flow = 0.0
 */
void PW_PowerSystem_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  data->localData[0]->realVars[60] /* motor._internalThermalPort._heatPortCore._Q_flow variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 18
 type: SIMPLE_ASSIGN
 motor._internalThermalPort._heatPortArmature._Q_flow = 0.0
 */
void PW_PowerSystem_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  data->localData[0]->realVars[58] /* motor._internalThermalPort._heatPortArmature._Q_flow variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 19
 type: SIMPLE_ASSIGN
 motor._internalSupport._tau = 0.0
 */
void PW_PowerSystem_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  data->localData[0]->realVars[57] /* motor._internalSupport._tau variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 20
 type: SIMPLE_ASSIGN
 speedSensor1._flange._tau = 0.0
 */
void PW_PowerSystem_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  data->localData[0]->realVars[98] /* speedSensor1._flange._tau variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 21
 type: SIMPLE_ASSIGN
 motor._strayLoad._tau = 0.0
 */
void PW_PowerSystem_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  data->localData[0]->realVars[82] /* motor._strayLoad._tau variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 22
 type: SIMPLE_ASSIGN
 motor._strayLoad._v = 0.0
 */
void PW_PowerSystem_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  data->localData[0]->realVars[83] /* motor._strayLoad._v variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 23
 type: SIMPLE_ASSIGN
 motor._core._i = 0.0
 */
void PW_PowerSystem_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  data->localData[0]->realVars[38] /* motor._core._i variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 24
 type: SIMPLE_ASSIGN
 motor._brush._v = 0.0
 */
void PW_PowerSystem_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  data->localData[0]->realVars[32] /* motor._brush._v variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 25
 type: SIMPLE_ASSIGN
 motor._inertiaStator._w = 0.0
 */
void PW_PowerSystem_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  data->localData[0]->realVars[56] /* motor._inertiaStator._w DUMMY_STATE */ = 0.0;
  TRACE_POP
}

/*
 equation index: 26
 type: SIMPLE_ASSIGN
 motor._airGapDC._psi_e = $_start(motor.airGapDC.psi_e)
 */
void PW_PowerSystem_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  data->localData[0]->realVars[0] /* motor._airGapDC._psi_e STATE(1,motor.airGapDC.vei) */ = data->modelData->realVarsData[0].attribute /* motor._airGapDC._psi_e */.start;
  TRACE_POP
}

/*
 equation index: 27
 type: SIMPLE_ASSIGN
 motor._la._i = $_start(motor.la.i)
 */
void PW_PowerSystem_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  data->localData[0]->realVars[2] /* motor._la._i STATE(1) */ = data->modelData->realVarsData[2].attribute /* motor._la._i */.start;
  TRACE_POP
}

/*
 equation index: 28
 type: SIMPLE_ASSIGN
 motor._inertiaRotor._w = $_start(motor.inertiaRotor.w)
 */
void PW_PowerSystem_eqFunction_28(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,28};
  data->localData[0]->realVars[1] /* motor._inertiaRotor._w STATE(1,motor.inertiaRotor.a) */ = data->modelData->realVarsData[1].attribute /* motor._inertiaRotor._w */.start;
  TRACE_POP
}

/*
 equation index: 29
 type: SIMPLE_ASSIGN
 motor._ra._R_actual = motor.ra.R * (1.0 + motor.ra.alpha * (motor.thermalAmbient.constTa.k - motor.ra.T_ref))
 */
void PW_PowerSystem_eqFunction_29(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,29};
  data->localData[0]->realVars[74] /* motor._ra._R_actual variable */ = (data->simulationInfo->realParameter[67] /* motor._ra._R PARAM */) * (1.0 + (data->simulationInfo->realParameter[70] /* motor._ra._alpha PARAM */) * (data->simulationInfo->realParameter[88] /* motor._thermalAmbient._constTa._k PARAM */ - data->simulationInfo->realParameter[69] /* motor._ra._T_ref PARAM */));
  TRACE_POP
}

/*
 equation index: 30
 type: SIMPLE_ASSIGN
 motor._re._R_actual = motor.re.R * (1.0 + motor.re.alpha * (motor.thermalAmbient.constTe.k - motor.re.T_ref))
 */
void PW_PowerSystem_eqFunction_30(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,30};
  data->localData[0]->realVars[76] /* motor._re._R_actual variable */ = (data->simulationInfo->realParameter[71] /* motor._re._R PARAM */) * (1.0 + (data->simulationInfo->realParameter[74] /* motor._re._alpha PARAM */) * (data->simulationInfo->realParameter[89] /* motor._thermalAmbient._constTe._k PARAM */ - data->simulationInfo->realParameter[73] /* motor._re._T_ref PARAM */));
  TRACE_POP
}

/*
 equation index: 31
 type: SIMPLE_ASSIGN
 motor._inertiaStator._flange_a._tau = -0.0
 */
void PW_PowerSystem_eqFunction_31(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,31};
  data->localData[0]->realVars[54] /* motor._inertiaStator._flange_a._tau variable */ = -0.0;
  TRACE_POP
}

/*
 equation index: 32
 type: SIMPLE_ASSIGN
 motor._core._wLimit = max(abs(motor.inertiaRotor.w), motor.core.coreParameters.wMin)
 */
void PW_PowerSystem_eqFunction_32(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,32};
  data->localData[0]->realVars[43] /* motor._core._wLimit variable */ = fmax(fabs(data->localData[0]->realVars[1] /* motor._inertiaRotor._w STATE(1,motor.inertiaRotor.a) */),data->simulationInfo->realParameter[39] /* motor._core._coreParameters._wMin PARAM */);
  TRACE_POP
}

/*
 equation index: 33
 type: SIMPLE_ASSIGN
 motor._airGapDC._vai = motor.airGapDC.turnsRatio * motor.airGapDC.psi_e * motor.inertiaRotor.w
 */
void PW_PowerSystem_eqFunction_33(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,33};
  data->localData[0]->realVars[28] /* motor._airGapDC._vai variable */ = (data->simulationInfo->realParameter[27] /* motor._airGapDC._turnsRatio PARAM */) * ((data->localData[0]->realVars[0] /* motor._airGapDC._psi_e STATE(1,motor.airGapDC.vei) */) * (data->localData[0]->realVars[1] /* motor._inertiaRotor._w STATE(1,motor.inertiaRotor.a) */));
  TRACE_POP
}

/*
 equation index: 34
 type: SIMPLE_ASSIGN
 motor._tauElectrical = motor.airGapDC.turnsRatio * motor.airGapDC.psi_e * motor.la.i
 */
void PW_PowerSystem_eqFunction_34(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,34};
  data->localData[0]->realVars[85] /* motor._tauElectrical variable */ = (data->simulationInfo->realParameter[27] /* motor._airGapDC._turnsRatio PARAM */) * ((data->localData[0]->realVars[0] /* motor._airGapDC._psi_e STATE(1,motor.airGapDC.vei) */) * (data->localData[0]->realVars[2] /* motor._la._i STATE(1) */));
  TRACE_POP
}

/*
 equation index: 35
 type: SIMPLE_ASSIGN
 convertToBoolean._y = up_input > convertToBoolean.threshold
 */
void PW_PowerSystem_eqFunction_35(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,35};
  modelica_boolean tmp0;
  tmp0 = Greater(data->localData[0]->realVars[102] /* up_input variable */,data->simulationInfo->realParameter[0] /* convertToBoolean._threshold PARAM */);
  data->localData[0]->booleanVars[0] /* convertToBoolean._y DISCRETE */ = tmp0;
  TRACE_POP
}

/*
 equation index: 36
 type: SIMPLE_ASSIGN
 greaterThreshold1._y = down_input > greaterThreshold1.threshold
 */
void PW_PowerSystem_eqFunction_36(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,36};
  modelica_boolean tmp1;
  tmp1 = Greater(data->localData[0]->realVars[14] /* down_input variable */,data->simulationInfo->realParameter[2] /* greaterThreshold1._threshold PARAM */);
  data->localData[0]->booleanVars[1] /* greaterThreshold1._y DISCRETE */ = tmp1;
  TRACE_POP
}

/*
 equation index: 47
 type: LINEAR
 
 <var>idealCommutingSwitch2._s1</var>
 <var>idealCommutingSwitch2._s2</var>
 <row>

 </row>
 <matrix>
 </matrix>
 */
void PW_PowerSystem_eqFunction_47(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,47};
  /* Linear equation system */
  int retValue;
  if(ACTIVE_STREAM(LOG_DT))
      {
        infoStreamPrint(LOG_DT, 1, "Solving linear system 47 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
        messageClose(LOG_DT);
      }
  data->simulationInfo->linearSystemData[0].x[0] = data->localData[1]->realVars[24] /* idealCommutingSwitch2._s1 variable */;
  data->simulationInfo->linearSystemData[0].x[1] = data->localData[1]->realVars[25] /* idealCommutingSwitch2._s2 variable */;
  retValue = solve_linear_system(data, threadData, 0);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,47};
    throwStreamPrintWithEquationIndexes(threadData, indexes, "Solving linear system 47 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  data->localData[0]->realVars[24] /* idealCommutingSwitch2._s1 variable */ = data->simulationInfo->linearSystemData[0].x[0];
  data->localData[0]->realVars[25] /* idealCommutingSwitch2._s2 variable */ = data->simulationInfo->linearSystemData[0].x[1];
  TRACE_POP
}

/*
 equation index: 48
 type: SIMPLE_ASSIGN
 motor._airGapDC._pin_ap._v = motor.airGapDC.vai + idealCommutingSwitch2.p.v
 */
void PW_PowerSystem_eqFunction_48(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,48};
  data->localData[0]->realVars[27] /* motor._airGapDC._pin_ap._v variable */ = data->localData[0]->realVars[28] /* motor._airGapDC._vai variable */ + data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */;
  TRACE_POP
}

/*
 equation index: 49
 type: SIMPLE_ASSIGN
 idealCommutingSwitch2._LossPower = motor.la.i * idealCommutingSwitch2.p.v + idealCommutingSwitch2.n1.i * up_voltage.V
 */
void PW_PowerSystem_eqFunction_49(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,49};
  data->localData[0]->realVars[20] /* idealCommutingSwitch2._LossPower variable */ = (data->localData[0]->realVars[2] /* motor._la._i STATE(1) */) * (data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */) + (data->localData[0]->realVars[21] /* idealCommutingSwitch2._n1._i variable */) * (data->simulationInfo->realParameter[103] /* up_voltage._V PARAM */);
  TRACE_POP
}

/*
 equation index: 50
 type: SIMPLE_ASSIGN
 speed = motor.inertiaRotor.w
 */
void PW_PowerSystem_eqFunction_50(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,50};
  data->localData[0]->realVars[96] /* speed variable */ = data->localData[0]->realVars[1] /* motor._inertiaRotor._w STATE(1,motor.inertiaRotor.a) */;
  TRACE_POP
}

/*
 equation index: 51
 type: SIMPLE_ASSIGN
 der(speedSensor1._flange._phi) = speed
 */
void PW_PowerSystem_eqFunction_51(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,51};
  data->localData[0]->realVars[11] /* der(speedSensor1._flange._phi) DUMMY_DER */ = data->localData[0]->realVars[96] /* speed variable */;
  TRACE_POP
}

/*
 equation index: 52
 type: SIMPLE_ASSIGN
 motor._strayLoad._w = speed
 */
void PW_PowerSystem_eqFunction_52(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,52};
  data->localData[0]->realVars[84] /* motor._strayLoad._w variable */ = data->localData[0]->realVars[96] /* speed variable */;
  TRACE_POP
}

/*
 equation index: 53
 type: SIMPLE_ASSIGN
 der(motor._strayLoad._phi) = motor.strayLoad.w
 */
void PW_PowerSystem_eqFunction_53(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,53};
  data->localData[0]->realVars[10] /* der(motor._strayLoad._phi) DUMMY_DER */ = data->localData[0]->realVars[84] /* motor._strayLoad._w variable */;
  TRACE_POP
}

/*
 equation index: 54
 type: SIMPLE_ASSIGN
 motor._friction._w = speed
 */
void PW_PowerSystem_eqFunction_54(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,54};
  data->localData[0]->realVars[47] /* motor._friction._w variable */ = data->localData[0]->realVars[96] /* speed variable */;
  TRACE_POP
}

/*
 equation index: 55
 type: SIMPLE_ASSIGN
 der(motor._friction._phi) = motor.friction.w
 */
void PW_PowerSystem_eqFunction_55(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,55};
  data->localData[0]->realVars[8] /* der(motor._friction._phi) DUMMY_DER */ = data->localData[0]->realVars[47] /* motor._friction._w variable */;
  TRACE_POP
}

/*
 equation index: 56
 type: SIMPLE_ASSIGN
 motor._friction._tau = -smooth(1, if motor.friction.w >= motor.friction.frictionParameters.wLinear then motor.friction.frictionParameters.tauRef * DIVISION(motor.friction.w, motor.friction.frictionParameters.wRef) ^ motor.friction.frictionParameters.power_w else if motor.friction.w <= (-motor.friction.frictionParameters.wLinear) then (-motor.friction.frictionParameters.tauRef) * DIVISION(-motor.friction.w, motor.friction.frictionParameters.wRef) ^ motor.friction.frictionParameters.power_w else motor.friction.frictionParameters.tauLinear * DIVISION(motor.friction.w, motor.friction.frictionParameters.wLinear))
 */
void PW_PowerSystem_eqFunction_56(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,56};
  modelica_boolean tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_real tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  modelica_real tmp9;
  modelica_boolean tmp10;
  modelica_real tmp11;
  modelica_real tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  modelica_real tmp15;
  modelica_real tmp16;
  modelica_real tmp17;
  modelica_boolean tmp18;
  modelica_real tmp19;
  modelica_boolean tmp20;
  modelica_real tmp21;
  tmp2 = GreaterEq(data->localData[0]->realVars[47] /* motor._friction._w variable */,data->simulationInfo->realParameter[53] /* motor._friction._frictionParameters._wLinear PARAM */);
  tmp20 = (modelica_boolean)tmp2;
  if(tmp20)
  {
    tmp3 = DIVISION_SIM(data->localData[0]->realVars[47] /* motor._friction._w variable */,data->simulationInfo->realParameter[54] /* motor._friction._frictionParameters._wRef PARAM */,"motor.friction.frictionParameters.wRef",equationIndexes);
    tmp4 = data->simulationInfo->realParameter[50] /* motor._friction._frictionParameters._power_w PARAM */;
    if(tmp3 < 0.0 && tmp4 != 0.0)
    {
      tmp6 = modf(tmp4, &tmp7);
      
      if(tmp6 > 0.5)
      {
        tmp6 -= 1.0;
        tmp7 += 1.0;
      }
      else if(tmp6 < -0.5)
      {
        tmp6 += 1.0;
        tmp7 -= 1.0;
      }
      
      if(fabs(tmp6) < 1e-10)
        tmp5 = pow(tmp3, tmp7);
      else
      {
        tmp9 = modf(1.0/tmp4, &tmp8);
        if(tmp9 > 0.5)
        {
          tmp9 -= 1.0;
          tmp8 += 1.0;
        }
        else if(tmp9 < -0.5)
        {
          tmp9 += 1.0;
          tmp8 -= 1.0;
        }
        if(fabs(tmp9) < 1e-10 && ((unsigned long)tmp8 & 1))
        {
          tmp5 = -pow(-tmp3, tmp6)*pow(tmp3, tmp7);
        }
        else
        {
          throwStreamPrint(threadData, "Invalid root: (%g)^(%g)", tmp3, tmp4);
        }
      }
    }
    else
    {
      tmp5 = pow(tmp3, tmp4);
    }
    if(isnan(tmp5) || isinf(tmp5))
    {
      throwStreamPrint(threadData, "Invalid root: (%g)^(%g)", tmp3, tmp4);
    }
    tmp21 = (data->simulationInfo->realParameter[52] /* motor._friction._frictionParameters._tauRef PARAM */) * (tmp5);
  }
  else
  {
    tmp10 = LessEq(data->localData[0]->realVars[47] /* motor._friction._w variable */,(-data->simulationInfo->realParameter[53] /* motor._friction._frictionParameters._wLinear PARAM */));
    tmp18 = (modelica_boolean)tmp10;
    if(tmp18)
    {
      tmp11 = DIVISION_SIM((-data->localData[0]->realVars[47] /* motor._friction._w variable */),data->simulationInfo->realParameter[54] /* motor._friction._frictionParameters._wRef PARAM */,"motor.friction.frictionParameters.wRef",equationIndexes);
      tmp12 = data->simulationInfo->realParameter[50] /* motor._friction._frictionParameters._power_w PARAM */;
      if(tmp11 < 0.0 && tmp12 != 0.0)
      {
        tmp14 = modf(tmp12, &tmp15);
        
        if(tmp14 > 0.5)
        {
          tmp14 -= 1.0;
          tmp15 += 1.0;
        }
        else if(tmp14 < -0.5)
        {
          tmp14 += 1.0;
          tmp15 -= 1.0;
        }
        
        if(fabs(tmp14) < 1e-10)
          tmp13 = pow(tmp11, tmp15);
        else
        {
          tmp17 = modf(1.0/tmp12, &tmp16);
          if(tmp17 > 0.5)
          {
            tmp17 -= 1.0;
            tmp16 += 1.0;
          }
          else if(tmp17 < -0.5)
          {
            tmp17 += 1.0;
            tmp16 -= 1.0;
          }
          if(fabs(tmp17) < 1e-10 && ((unsigned long)tmp16 & 1))
          {
            tmp13 = -pow(-tmp11, tmp14)*pow(tmp11, tmp15);
          }
          else
          {
            throwStreamPrint(threadData, "Invalid root: (%g)^(%g)", tmp11, tmp12);
          }
        }
      }
      else
      {
        tmp13 = pow(tmp11, tmp12);
      }
      if(isnan(tmp13) || isinf(tmp13))
      {
        throwStreamPrint(threadData, "Invalid root: (%g)^(%g)", tmp11, tmp12);
      }
      tmp19 = ((-data->simulationInfo->realParameter[52] /* motor._friction._frictionParameters._tauRef PARAM */)) * (tmp13);
    }
    else
    {
      tmp19 = (data->simulationInfo->realParameter[51] /* motor._friction._frictionParameters._tauLinear PARAM */) * (DIVISION_SIM(data->localData[0]->realVars[47] /* motor._friction._w variable */,data->simulationInfo->realParameter[53] /* motor._friction._frictionParameters._wLinear PARAM */,"motor.friction.frictionParameters.wLinear",equationIndexes));
    }
    tmp21 = tmp19;
  }
  data->localData[0]->realVars[46] /* motor._friction._tau variable */ = (-tmp21);
  TRACE_POP
}

/*
 equation index: 57
 type: SIMPLE_ASSIGN
 motor._fixed._flange._tau = (-motor.friction.tau) - motor.inertiaStator.flange_a.tau - motor.tauElectrical
 */
void PW_PowerSystem_eqFunction_57(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,57};
  data->localData[0]->realVars[44] /* motor._fixed._flange._tau variable */ = (-data->localData[0]->realVars[46] /* motor._friction._tau variable */) - data->localData[0]->realVars[54] /* motor._inertiaStator._flange_a._tau variable */ - data->localData[0]->realVars[85] /* motor._tauElectrical variable */;
  TRACE_POP
}

/*
 equation index: 58
 type: SIMPLE_ASSIGN
 motor._inertiaRotor._flange_b._tau = motor.friction.tau + input_torque
 */
void PW_PowerSystem_eqFunction_58(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,58};
  data->localData[0]->realVars[52] /* motor._inertiaRotor._flange_b._tau variable */ = data->localData[0]->realVars[46] /* motor._friction._tau variable */ + data->localData[0]->realVars[26] /* input_torque variable */;
  TRACE_POP
}

/*
 equation index: 59
 type: SIMPLE_ASSIGN
 motor._inertiaRotor._a = DIVISION(motor.tauElectrical + motor.inertiaRotor.flange_b.tau, motor.inertiaRotor.J)
 */
void PW_PowerSystem_eqFunction_59(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,59};
  data->localData[0]->realVars[51] /* motor._inertiaRotor._a variable */ = DIVISION_SIM(data->localData[0]->realVars[85] /* motor._tauElectrical variable */ + data->localData[0]->realVars[52] /* motor._inertiaRotor._flange_b._tau variable */,data->simulationInfo->realParameter[62] /* motor._inertiaRotor._J PARAM */,"motor.inertiaRotor.J",equationIndexes);
  TRACE_POP
}

/*
 equation index: 60
 type: SIMPLE_ASSIGN
 motor._powerBalance._powerInertiaRotor = motor.inertiaRotor.J * motor.inertiaRotor.a * motor.inertiaRotor.w
 */
void PW_PowerSystem_eqFunction_60(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,60};
  data->localData[0]->realVars[71] /* motor._powerBalance._powerInertiaRotor variable */ = (data->simulationInfo->realParameter[62] /* motor._inertiaRotor._J PARAM */) * ((data->localData[0]->realVars[51] /* motor._inertiaRotor._a variable */) * (data->localData[0]->realVars[1] /* motor._inertiaRotor._w STATE(1,motor.inertiaRotor.a) */));
  TRACE_POP
}

/*
 equation index: 61
 type: SIMPLE_ASSIGN
 der(motor._inertiaRotor._w) = motor.inertiaRotor.a
 */
void PW_PowerSystem_eqFunction_61(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,61};
  data->localData[0]->realVars[5] /* der(motor._inertiaRotor._w) STATE_DER */ = data->localData[0]->realVars[51] /* motor._inertiaRotor._a variable */;
  TRACE_POP
}

/*
 equation index: 62
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._Q_flowFriction = (-motor.friction.tau) * motor.friction.w
 */
void PW_PowerSystem_eqFunction_62(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,62};
  data->localData[0]->realVars[88] /* motor._thermalAmbient._Q_flowFriction variable */ = ((-data->localData[0]->realVars[46] /* motor._friction._tau variable */)) * (data->localData[0]->realVars[47] /* motor._friction._w variable */);
  TRACE_POP
}

/*
 equation index: 63
 type: SIMPLE_ASSIGN
 motor._wMechanical = speed
 */
void PW_PowerSystem_eqFunction_63(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,63};
  data->localData[0]->realVars[95] /* motor._wMechanical variable */ = data->localData[0]->realVars[96] /* speed variable */;
  TRACE_POP
}

/*
 equation index: 64
 type: SIMPLE_ASSIGN
 motor._powerBalance._powerMechanical = (-motor.wMechanical) * input_torque
 */
void PW_PowerSystem_eqFunction_64(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,64};
  data->localData[0]->realVars[73] /* motor._powerBalance._powerMechanical variable */ = ((-data->localData[0]->realVars[95] /* motor._wMechanical variable */)) * (data->localData[0]->realVars[26] /* input_torque variable */);
  TRACE_POP
}

/*
 equation index: 65
 type: SIMPLE_ASSIGN
 der(motor._phiMechanical) = motor.wMechanical
 */
void PW_PowerSystem_eqFunction_65(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,65};
  data->localData[0]->realVars[7] /* der(motor._phiMechanical) STATE_DER */ = data->localData[0]->realVars[95] /* motor._wMechanical variable */;
  TRACE_POP
}

/*
 equation index: 66
 type: SIMPLE_ASSIGN
 arm_current = -motor.la.i
 */
void PW_PowerSystem_eqFunction_66(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,66};
  data->localData[0]->realVars[12] /* arm_current variable */ = (-data->localData[0]->realVars[2] /* motor._la._i STATE(1) */);
  TRACE_POP
}

/*
 equation index: 76
 type: LINEAR
 
 <var>idealCommutingSwitch1._s2</var>
 <var>idealCommutingSwitch1._s1</var>
 <row>

 </row>
 <matrix>
 </matrix>
 */
void PW_PowerSystem_eqFunction_76(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,76};
  /* Linear equation system */
  int retValue;
  if(ACTIVE_STREAM(LOG_DT))
      {
        infoStreamPrint(LOG_DT, 1, "Solving linear system 76 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
        messageClose(LOG_DT);
      }
  data->simulationInfo->linearSystemData[1].x[0] = data->localData[1]->realVars[19] /* idealCommutingSwitch1._s2 variable */;
  data->simulationInfo->linearSystemData[1].x[1] = data->localData[1]->realVars[18] /* idealCommutingSwitch1._s1 variable */;
  retValue = solve_linear_system(data, threadData, 1);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,76};
    throwStreamPrintWithEquationIndexes(threadData, indexes, "Solving linear system 76 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  data->localData[0]->realVars[19] /* idealCommutingSwitch1._s2 variable */ = data->simulationInfo->linearSystemData[1].x[0];
  data->localData[0]->realVars[18] /* idealCommutingSwitch1._s1 variable */ = data->simulationInfo->linearSystemData[1].x[1];
  TRACE_POP
}

/*
 equation index: 77
 type: SIMPLE_ASSIGN
 up_voltage._i = (-idealCommutingSwitch1.n1.i) - idealCommutingSwitch2.n1.i
 */
void PW_PowerSystem_eqFunction_77(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,77};
  data->localData[0]->realVars[103] /* up_voltage._i variable */ = (-data->localData[0]->realVars[16] /* idealCommutingSwitch1._n1._i variable */) - data->localData[0]->realVars[21] /* idealCommutingSwitch2._n1._i variable */;
  TRACE_POP
}

/*
 equation index: 78
 type: SIMPLE_ASSIGN
 up_ground._p._i = up_voltage.i - (idealCommutingSwitch1.n2.i + idealCommutingSwitch2.n2.i)
 */
void PW_PowerSystem_eqFunction_78(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,78};
  data->localData[0]->realVars[100] /* up_ground._p._i variable */ = data->localData[0]->realVars[103] /* up_voltage._i variable */ - (data->localData[0]->realVars[17] /* idealCommutingSwitch1._n2._i variable */ + data->localData[0]->realVars[22] /* idealCommutingSwitch2._n2._i variable */);
  TRACE_POP
}

/*
 equation index: 79
 type: SIMPLE_ASSIGN
 idealCommutingSwitch1._LossPower = arm_current * arm_sensor.p.v + idealCommutingSwitch1.n1.i * up_voltage.V
 */
void PW_PowerSystem_eqFunction_79(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,79};
  data->localData[0]->realVars[15] /* idealCommutingSwitch1._LossPower variable */ = (data->localData[0]->realVars[12] /* arm_current variable */) * (data->localData[0]->realVars[13] /* arm_sensor._p._v variable */) + (data->localData[0]->realVars[16] /* idealCommutingSwitch1._n1._i variable */) * (data->simulationInfo->realParameter[103] /* up_voltage._V PARAM */);
  TRACE_POP
}

/*
 equation index: 80
 type: SIMPLE_ASSIGN
 motor._va = arm_sensor.p.v - idealCommutingSwitch2.p.v
 */
void PW_PowerSystem_eqFunction_80(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,80};
  data->localData[0]->realVars[94] /* motor._va variable */ = data->localData[0]->realVars[13] /* arm_sensor._p._v variable */ - data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */;
  TRACE_POP
}

/*
 equation index: 81
 type: SIMPLE_ASSIGN
 motor._ra._v = (-motor.ra.R_actual) * arm_current
 */
void PW_PowerSystem_eqFunction_81(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,81};
  data->localData[0]->realVars[75] /* motor._ra._v variable */ = ((-data->localData[0]->realVars[74] /* motor._ra._R_actual variable */)) * (data->localData[0]->realVars[12] /* arm_current variable */);
  TRACE_POP
}

/*
 equation index: 82
 type: SIMPLE_ASSIGN
 motor._core._p._v = arm_sensor.p.v - motor.ra.v
 */
void PW_PowerSystem_eqFunction_82(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,82};
  data->localData[0]->realVars[41] /* motor._core._p._v variable */ = data->localData[0]->realVars[13] /* arm_sensor._p._v variable */ - data->localData[0]->realVars[75] /* motor._ra._v variable */;
  TRACE_POP
}

/*
 equation index: 83
 type: SIMPLE_ASSIGN
 motor._core._v = motor.core.p.v - idealCommutingSwitch2.p.v
 */
void PW_PowerSystem_eqFunction_83(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,83};
  data->localData[0]->realVars[42] /* motor._core._v variable */ = data->localData[0]->realVars[41] /* motor._core._p._v variable */ - data->localData[0]->realVars[23] /* idealCommutingSwitch2._p._v variable */;
  TRACE_POP
}

/*
 equation index: 84
 type: SIMPLE_ASSIGN
 motor._la._v = motor.core.p.v - motor.airGapDC.pin_ap.v
 */
void PW_PowerSystem_eqFunction_84(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,84};
  data->localData[0]->realVars[64] /* motor._la._v variable */ = data->localData[0]->realVars[41] /* motor._core._p._v variable */ - data->localData[0]->realVars[27] /* motor._airGapDC._pin_ap._v variable */;
  TRACE_POP
}

/*
 equation index: 85
 type: SIMPLE_ASSIGN
 der(motor._la._i) = DIVISION(motor.la.v, motor.la.L)
 */
void PW_PowerSystem_eqFunction_85(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,85};
  data->localData[0]->realVars[6] /* der(motor._la._i) STATE_DER */ = DIVISION_SIM(data->localData[0]->realVars[64] /* motor._la._v variable */,data->simulationInfo->realParameter[64] /* motor._la._L PARAM */,"motor.la.L",equationIndexes);
  TRACE_POP
}

/*
 equation index: 86
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._Q_flowArmature = (-motor.ra.v) * arm_current
 */
void PW_PowerSystem_eqFunction_86(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,86};
  data->localData[0]->realVars[86] /* motor._thermalAmbient._Q_flowArmature variable */ = ((-data->localData[0]->realVars[75] /* motor._ra._v variable */)) * (data->localData[0]->realVars[12] /* arm_current variable */);
  TRACE_POP
}

/*
 equation index: 87
 type: SIMPLE_ASSIGN
 motor._powerBalance._powerArmature = (-motor.va) * arm_current
 */
void PW_PowerSystem_eqFunction_87(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,87};
  data->localData[0]->realVars[69] /* motor._powerBalance._powerArmature variable */ = ((-data->localData[0]->realVars[94] /* motor._va variable */)) * (data->localData[0]->realVars[12] /* arm_current variable */);
  TRACE_POP
}

/*
 equation index: 88
 type: SIMPLE_ASSIGN
 motor._lesigma._i = 0.3125 * motor.airGapDC.psi_e
 */
void PW_PowerSystem_eqFunction_88(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,88};
  data->localData[0]->realVars[65] /* motor._lesigma._i DUMMY_STATE */ = (0.3125) * (data->localData[0]->realVars[0] /* motor._airGapDC._psi_e STATE(1,motor.airGapDC.vei) */);
  TRACE_POP
}

/*
 equation index: 89
 type: SIMPLE_ASSIGN
 motor._re._v = motor.re.R_actual * motor.lesigma.i
 */
void PW_PowerSystem_eqFunction_89(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,89};
  data->localData[0]->realVars[77] /* motor._re._v variable */ = (data->localData[0]->realVars[76] /* motor._re._R_actual variable */) * (data->localData[0]->realVars[65] /* motor._lesigma._i DUMMY_STATE */);
  TRACE_POP
}

/*
 equation index: 90
 type: SIMPLE_ASSIGN
 motor._lesigma._p._v = dc_motor_power.V - motor.re.v
 */
void PW_PowerSystem_eqFunction_90(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,90};
  data->localData[0]->realVars[66] /* motor._lesigma._p._v variable */ = data->simulationInfo->realParameter[1] /* dc_motor_power._V PARAM */ - data->localData[0]->realVars[77] /* motor._re._v variable */;
  TRACE_POP
}

/*
 equation index: 96
 type: LINEAR
 
 <var>motor._airGapDC._vei</var>
 <row>

 </row>
 <matrix>
 </matrix>
 */
void PW_PowerSystem_eqFunction_96(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,96};
  /* Linear equation system */
  int retValue;
  if(ACTIVE_STREAM(LOG_DT))
      {
        infoStreamPrint(LOG_DT, 1, "Solving linear system 96 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
        messageClose(LOG_DT);
      }
  data->simulationInfo->linearSystemData[2].x[0] = data->localData[1]->realVars[29] /* motor._airGapDC._vei variable */;
  retValue = solve_linear_system(data, threadData, 2);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,96};
    throwStreamPrintWithEquationIndexes(threadData, indexes, "Solving linear system 96 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  data->localData[0]->realVars[29] /* motor._airGapDC._vei variable */ = data->simulationInfo->linearSystemData[2].x[0];
  TRACE_POP
}

/*
 equation index: 97
 type: SIMPLE_ASSIGN
 motor._compoundDCExcitation._vse = motor.airGapDC.vei * motor.compoundDCExcitation.excitationTurnsRatio
 */
void PW_PowerSystem_eqFunction_97(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,97};
  data->localData[0]->realVars[35] /* motor._compoundDCExcitation._vse variable */ = (data->localData[0]->realVars[29] /* motor._airGapDC._vei variable */) * (data->simulationInfo->realParameter[34] /* motor._compoundDCExcitation._excitationTurnsRatio PARAM */);
  TRACE_POP
}

/*
 equation index: 98
 type: SIMPLE_ASSIGN
 der(motor._airGapDC._psi_e) = motor.airGapDC.vei
 */
void PW_PowerSystem_eqFunction_98(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,98};
  data->localData[0]->realVars[4] /* der(motor._airGapDC._psi_e) STATE_DER */ = data->localData[0]->realVars[29] /* motor._airGapDC._vei variable */;
  TRACE_POP
}

/*
 equation index: 99
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._Q_flowExcitation = motor.re.v * motor.lesigma.i
 */
void PW_PowerSystem_eqFunction_99(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,99};
  data->localData[0]->realVars[87] /* motor._thermalAmbient._Q_flowExcitation variable */ = (data->localData[0]->realVars[77] /* motor._re._v variable */) * (data->localData[0]->realVars[65] /* motor._lesigma._i DUMMY_STATE */);
  TRACE_POP
}

/*
 equation index: 100
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._Q_flowTotal = motor.thermalAmbient.Q_flowArmature + motor.thermalAmbient.Q_flowFriction + motor.thermalAmbient.Q_flowExcitation
 */
void PW_PowerSystem_eqFunction_100(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,100};
  data->localData[0]->realVars[89] /* motor._thermalAmbient._Q_flowTotal variable */ = data->localData[0]->realVars[86] /* motor._thermalAmbient._Q_flowArmature variable */ + data->localData[0]->realVars[88] /* motor._thermalAmbient._Q_flowFriction variable */ + data->localData[0]->realVars[87] /* motor._thermalAmbient._Q_flowExcitation variable */;
  TRACE_POP
}

/*
 equation index: 101
 type: SIMPLE_ASSIGN
 motor._powerBalance._lossPowerTotal = motor.thermalAmbient.Q_flowArmature + motor.thermalAmbient.Q_flowFriction + motor.thermalAmbient.Q_flowExcitation
 */
void PW_PowerSystem_eqFunction_101(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,101};
  data->localData[0]->realVars[68] /* motor._powerBalance._lossPowerTotal variable */ = data->localData[0]->realVars[86] /* motor._thermalAmbient._Q_flowArmature variable */ + data->localData[0]->realVars[88] /* motor._thermalAmbient._Q_flowFriction variable */ + data->localData[0]->realVars[87] /* motor._thermalAmbient._Q_flowExcitation variable */;
  TRACE_POP
}

/*
 equation index: 102
 type: SIMPLE_ASSIGN
 motor._powerBalance._powerExcitation = dc_motor_power.V * motor.lesigma.i
 */
void PW_PowerSystem_eqFunction_102(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,102};
  data->localData[0]->realVars[70] /* motor._powerBalance._powerExcitation variable */ = (data->simulationInfo->realParameter[1] /* dc_motor_power._V PARAM */) * (data->localData[0]->realVars[65] /* motor._lesigma._i DUMMY_STATE */);
  TRACE_POP
}

/*
 equation index: 103
 type: SIMPLE_ASSIGN
 motor._brush._lossPower = 0.0
 */
void PW_PowerSystem_eqFunction_103(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,103};
  data->localData[0]->realVars[31] /* motor._brush._lossPower variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 104
 type: SIMPLE_ASSIGN
 motor._core._lossPower = 0.0
 */
void PW_PowerSystem_eqFunction_104(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,104};
  data->localData[0]->realVars[39] /* motor._core._lossPower variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 105
 type: SIMPLE_ASSIGN
 motor._strayLoad._lossPower = 0.0
 */
void PW_PowerSystem_eqFunction_105(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,105};
  data->localData[0]->realVars[80] /* motor._strayLoad._lossPower variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 106
 type: SIMPLE_ASSIGN
 voltage_ground._p._i = 0.0
 */
void PW_PowerSystem_eqFunction_106(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,106};
  data->localData[0]->realVars[104] /* voltage_ground._p._i variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 107
 type: SIMPLE_ASSIGN
 motor._ground._p._i = 0.0
 */
void PW_PowerSystem_eqFunction_107(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,107};
  data->localData[0]->realVars[48] /* motor._ground._p._i variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 108
 type: SIMPLE_ASSIGN
 motor._powerBalance._powerInertiaStator = 0.0
 */
void PW_PowerSystem_eqFunction_108(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,108};
  data->localData[0]->realVars[72] /* motor._powerBalance._powerInertiaStator variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 109
 type: SIMPLE_ASSIGN
 motor._inertiaStator._a = 0.0
 */
void PW_PowerSystem_eqFunction_109(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,109};
  data->localData[0]->realVars[53] /* motor._inertiaStator._a variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 110
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._temperatureFriction._port._T = 293.15
 */
void PW_PowerSystem_eqFunction_110(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,110};
  data->localData[0]->realVars[92] /* motor._thermalAmbient._temperatureFriction._port._T variable */ = 293.15;
  TRACE_POP
}

/*
 equation index: 111
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._temperatureStrayLoad._port._T = 293.15
 */
void PW_PowerSystem_eqFunction_111(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,111};
  data->localData[0]->realVars[93] /* motor._thermalAmbient._temperatureStrayLoad._port._T variable */ = 293.15;
  TRACE_POP
}

/*
 equation index: 112
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._temperatureBrush._port._T = 293.15
 */
void PW_PowerSystem_eqFunction_112(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,112};
  data->localData[0]->realVars[90] /* motor._thermalAmbient._temperatureBrush._port._T variable */ = 293.15;
  TRACE_POP
}

/*
 equation index: 113
 type: SIMPLE_ASSIGN
 motor._thermalAmbient._temperatureCore._port._T = 293.15
 */
void PW_PowerSystem_eqFunction_113(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,113};
  data->localData[0]->realVars[91] /* motor._thermalAmbient._temperatureCore._port._T variable */ = 293.15;
  TRACE_POP
}

/*
 equation index: 114
 type: SIMPLE_ASSIGN
 torque1._phi_support = 0.0
 */
void PW_PowerSystem_eqFunction_114(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,114};
  data->localData[0]->realVars[99] /* torque1._phi_support variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 115
 type: SIMPLE_ASSIGN
 motor._core._Gc = 0.0
 */
void PW_PowerSystem_eqFunction_115(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,115};
  data->localData[0]->realVars[36] /* motor._core._Gc variable */ = 0.0;
  TRACE_POP
}

/*
 equation index: 116
 type: SIMPLE_ASSIGN
 motor._phiMechanical = $_start(motor.phiMechanical)
 */
void PW_PowerSystem_eqFunction_116(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,116};
  data->localData[0]->realVars[3] /* motor._phiMechanical STATE(1,speed) */ = data->modelData->realVarsData[3].attribute /* motor._phiMechanical */.start;
  TRACE_POP
}

/*
 equation index: 117
 type: SIMPLE_ASSIGN
 speedSensor1._flange._phi = motor.phiMechanical + motor.fixed.phi0
 */
void PW_PowerSystem_eqFunction_117(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,117};
  data->localData[0]->realVars[97] /* speedSensor1._flange._phi DUMMY_STATE */ = data->localData[0]->realVars[3] /* motor._phiMechanical STATE(1,speed) */ + data->simulationInfo->realParameter[47] /* motor._fixed._phi0 PARAM */;
  TRACE_POP
}

/*
 equation index: 118
 type: SIMPLE_ASSIGN
 motor._friction._phi = speedSensor1.flange.phi - motor.fixed.phi0
 */
void PW_PowerSystem_eqFunction_118(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,118};
  data->localData[0]->realVars[45] /* motor._friction._phi DUMMY_STATE */ = data->localData[0]->realVars[97] /* speedSensor1._flange._phi DUMMY_STATE */ - data->simulationInfo->realParameter[47] /* motor._fixed._phi0 PARAM */;
  TRACE_POP
}

/*
 equation index: 119
 type: SIMPLE_ASSIGN
 motor._strayLoad._phi = speedSensor1.flange.phi - motor.fixed.phi0
 */
void PW_PowerSystem_eqFunction_119(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,119};
  data->localData[0]->realVars[81] /* motor._strayLoad._phi DUMMY_STATE */ = data->localData[0]->realVars[97] /* speedSensor1._flange._phi DUMMY_STATE */ - data->simulationInfo->realParameter[47] /* motor._fixed._phi0 PARAM */;
  TRACE_POP
}

/*
 equation index: 120
 type: ALGORITHM
 
   assert(motor.ViNominal > 1e-015, "VaNominal has to be > (Ra[+Rse])*IaNominal");
 */
void PW_PowerSystem_eqFunction_120(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,120};
  modelica_boolean tmp22;
  static const MMC_DEFSTRINGLIT(tmp23,42,"VaNominal has to be > (Ra[+Rse])*IaNominal");
  static int tmp24 = 0;
  {
    tmp22 = Greater(data->simulationInfo->realParameter[25] /* motor._ViNominal PARAM */,1e-015);
    if(!tmp22)
    {
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/Electrical/Machines.mo",13653,7,13654,54,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nmotor.ViNominal > 1e-015", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_withEquationIndexes(threadData, info, equationIndexes, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp23)));
      }
    }
  }
  TRACE_POP
}
void PW_PowerSystem_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  PW_PowerSystem_eqFunction_1(data, threadData);
  PW_PowerSystem_eqFunction_2(data, threadData);
  PW_PowerSystem_eqFunction_3(data, threadData);
  PW_PowerSystem_eqFunction_4(data, threadData);
  PW_PowerSystem_eqFunction_5(data, threadData);
  PW_PowerSystem_eqFunction_6(data, threadData);
  PW_PowerSystem_eqFunction_7(data, threadData);
  PW_PowerSystem_eqFunction_8(data, threadData);
  PW_PowerSystem_eqFunction_9(data, threadData);
  PW_PowerSystem_eqFunction_10(data, threadData);
  PW_PowerSystem_eqFunction_11(data, threadData);
  PW_PowerSystem_eqFunction_12(data, threadData);
  PW_PowerSystem_eqFunction_13(data, threadData);
  PW_PowerSystem_eqFunction_14(data, threadData);
  PW_PowerSystem_eqFunction_15(data, threadData);
  PW_PowerSystem_eqFunction_16(data, threadData);
  PW_PowerSystem_eqFunction_17(data, threadData);
  PW_PowerSystem_eqFunction_18(data, threadData);
  PW_PowerSystem_eqFunction_19(data, threadData);
  PW_PowerSystem_eqFunction_20(data, threadData);
  PW_PowerSystem_eqFunction_21(data, threadData);
  PW_PowerSystem_eqFunction_22(data, threadData);
  PW_PowerSystem_eqFunction_23(data, threadData);
  PW_PowerSystem_eqFunction_24(data, threadData);
  PW_PowerSystem_eqFunction_25(data, threadData);
  PW_PowerSystem_eqFunction_26(data, threadData);
  PW_PowerSystem_eqFunction_27(data, threadData);
  PW_PowerSystem_eqFunction_28(data, threadData);
  PW_PowerSystem_eqFunction_29(data, threadData);
  PW_PowerSystem_eqFunction_30(data, threadData);
  PW_PowerSystem_eqFunction_31(data, threadData);
  PW_PowerSystem_eqFunction_32(data, threadData);
  PW_PowerSystem_eqFunction_33(data, threadData);
  PW_PowerSystem_eqFunction_34(data, threadData);
  PW_PowerSystem_eqFunction_35(data, threadData);
  PW_PowerSystem_eqFunction_36(data, threadData);
  PW_PowerSystem_eqFunction_47(data, threadData);
  PW_PowerSystem_eqFunction_48(data, threadData);
  PW_PowerSystem_eqFunction_49(data, threadData);
  PW_PowerSystem_eqFunction_50(data, threadData);
  PW_PowerSystem_eqFunction_51(data, threadData);
  PW_PowerSystem_eqFunction_52(data, threadData);
  PW_PowerSystem_eqFunction_53(data, threadData);
  PW_PowerSystem_eqFunction_54(data, threadData);
  PW_PowerSystem_eqFunction_55(data, threadData);
  PW_PowerSystem_eqFunction_56(data, threadData);
  PW_PowerSystem_eqFunction_57(data, threadData);
  PW_PowerSystem_eqFunction_58(data, threadData);
  PW_PowerSystem_eqFunction_59(data, threadData);
  PW_PowerSystem_eqFunction_60(data, threadData);
  PW_PowerSystem_eqFunction_61(data, threadData);
  PW_PowerSystem_eqFunction_62(data, threadData);
  PW_PowerSystem_eqFunction_63(data, threadData);
  PW_PowerSystem_eqFunction_64(data, threadData);
  PW_PowerSystem_eqFunction_65(data, threadData);
  PW_PowerSystem_eqFunction_66(data, threadData);
  PW_PowerSystem_eqFunction_76(data, threadData);
  PW_PowerSystem_eqFunction_77(data, threadData);
  PW_PowerSystem_eqFunction_78(data, threadData);
  PW_PowerSystem_eqFunction_79(data, threadData);
  PW_PowerSystem_eqFunction_80(data, threadData);
  PW_PowerSystem_eqFunction_81(data, threadData);
  PW_PowerSystem_eqFunction_82(data, threadData);
  PW_PowerSystem_eqFunction_83(data, threadData);
  PW_PowerSystem_eqFunction_84(data, threadData);
  PW_PowerSystem_eqFunction_85(data, threadData);
  PW_PowerSystem_eqFunction_86(data, threadData);
  PW_PowerSystem_eqFunction_87(data, threadData);
  PW_PowerSystem_eqFunction_88(data, threadData);
  PW_PowerSystem_eqFunction_89(data, threadData);
  PW_PowerSystem_eqFunction_90(data, threadData);
  PW_PowerSystem_eqFunction_96(data, threadData);
  PW_PowerSystem_eqFunction_97(data, threadData);
  PW_PowerSystem_eqFunction_98(data, threadData);
  PW_PowerSystem_eqFunction_99(data, threadData);
  PW_PowerSystem_eqFunction_100(data, threadData);
  PW_PowerSystem_eqFunction_101(data, threadData);
  PW_PowerSystem_eqFunction_102(data, threadData);
  PW_PowerSystem_eqFunction_103(data, threadData);
  PW_PowerSystem_eqFunction_104(data, threadData);
  PW_PowerSystem_eqFunction_105(data, threadData);
  PW_PowerSystem_eqFunction_106(data, threadData);
  PW_PowerSystem_eqFunction_107(data, threadData);
  PW_PowerSystem_eqFunction_108(data, threadData);
  PW_PowerSystem_eqFunction_109(data, threadData);
  PW_PowerSystem_eqFunction_110(data, threadData);
  PW_PowerSystem_eqFunction_111(data, threadData);
  PW_PowerSystem_eqFunction_112(data, threadData);
  PW_PowerSystem_eqFunction_113(data, threadData);
  PW_PowerSystem_eqFunction_114(data, threadData);
  PW_PowerSystem_eqFunction_115(data, threadData);
  PW_PowerSystem_eqFunction_116(data, threadData);
  PW_PowerSystem_eqFunction_117(data, threadData);
  PW_PowerSystem_eqFunction_118(data, threadData);
  PW_PowerSystem_eqFunction_119(data, threadData);
  PW_PowerSystem_eqFunction_120(data, threadData);
  TRACE_POP
}


int PW_PowerSystem_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  PW_PowerSystem_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int PW_PowerSystem_functionInitialEquations_lambda0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}
int PW_PowerSystem_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

