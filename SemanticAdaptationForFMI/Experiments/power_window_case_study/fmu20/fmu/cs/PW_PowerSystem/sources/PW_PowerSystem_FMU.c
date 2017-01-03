
// define class name and unique id
#define MODEL_IDENTIFIER PW_PowerSystem
#define MODEL_GUID "{4d380cc7-cc74-4e83-9726-8f0ae3e20528}"

// include fmu header files, typedefs and macros
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "openmodelica.h"
#include "openmodelica_func.h"
#include "simulation_data.h"
#include "util/omc_error.h"
#include "PW_PowerSystem_functions.h"
#include "simulation/solver/initialization/initialization.h"
#include "simulation/solver/events.h"
#include "fmi2/fmu2_model_interface.h"

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
#define NUMBER_OF_STATES 4
#define NUMBER_OF_EVENT_INDICATORS 2
#define NUMBER_OF_REALS 384
#define NUMBER_OF_INTEGERS 4
#define NUMBER_OF_STRINGS 0
#define NUMBER_OF_BOOLEANS 19
#define NUMBER_OF_EXTERNALFUNCTIONS 0

// define variable data for model
#define $Pmotor$PairGapDC$Ppsi_e_vr 0 // "Excitation flux"
#define $Pmotor$PinertiaRotor$Pw_vr 1 // "Absolute angular velocity of component (= der(phi))"
#define $Pmotor$Pla$Pi_vr 2 // "Current flowing from pin p to pin n"
#define $Pmotor$PphiMechanical_vr 3 // "Mechanical angle of rotor against stator"
#define $P$DER$Pmotor$PairGapDC$Ppsi_e_vr 4 // "Excitation flux"
#define $P$DER$Pmotor$PinertiaRotor$Pw_vr 5 // "Absolute angular velocity of component (= der(phi))"
#define $P$DER$Pmotor$Pla$Pi_vr 6 // "Current flowing from pin p to pin n"
#define $P$DER$Pmotor$PphiMechanical_vr 7 // "Mechanical angle of rotor against stator"
#define $P$DER$Pmotor$Pfriction$Pphi_vr 8 // "Angle between shaft and support"
#define $P$DER$Pmotor$Plesigma$Pi_vr 9 // "Current flowing from pin p to pin n"
#define $P$DER$Pmotor$PstrayLoad$Pphi_vr 10 // "Angle between shaft and support"
#define $P$DER$PspeedSensor1$Pflange$Pphi_vr 11 // "Absolute rotation angle of flange"
#define $Parm_current_vr 12 
#define $Parm_sensor$Pp$Pv_vr 13 // "Potential at the pin"
#define $Pdown_input_vr 14 
#define $PidealCommutingSwitch1$PLossPower_vr 15 // "Loss power leaving component via heatPort"
#define $PidealCommutingSwitch1$Pn1$Pi_vr 16 // "Current flowing into the pin"
#define $PidealCommutingSwitch1$Pn2$Pi_vr 17 // "Current flowing into the pin"
#define $PidealCommutingSwitch1$Ps1_vr 18 
#define $PidealCommutingSwitch1$Ps2_vr 19 // "Auxiliary variables"
#define $PidealCommutingSwitch2$PLossPower_vr 20 // "Loss power leaving component via heatPort"
#define $PidealCommutingSwitch2$Pn1$Pi_vr 21 // "Current flowing into the pin"
#define $PidealCommutingSwitch2$Pn2$Pi_vr 22 // "Current flowing into the pin"
#define $PidealCommutingSwitch2$Pp$Pv_vr 23 // "Potential at the pin"
#define $PidealCommutingSwitch2$Ps1_vr 24 
#define $PidealCommutingSwitch2$Ps2_vr 25 // "Auxiliary variables"
#define $Pinput_torque_vr 26 
#define $Pmotor$PairGapDC$Ppin_ap$Pv_vr 27 // "Potential at the pin"
#define $Pmotor$PairGapDC$Pvai_vr 28 // "Induced armature voltage"
#define $Pmotor$PairGapDC$Pvei_vr 29 // "Voltage drop across field excitation inductance"
#define $Pmotor$Pbrush$PheatPort$PQ_flow_vr 30 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$Pbrush$PlossPower_vr 31 // "Loss power leaving component via heatPort (> 0, if heat is flowing out of component)"
#define $Pmotor$Pbrush$Pv_vr 32 // "Voltage drop between the two pins (= p.v - n.v)"
#define $Pmotor$PcompoundDCExcitation$Ppin_sen$Pi_vr 33 // "Current flowing into the pin"
#define $Pmotor$PcompoundDCExcitation$Ppin_sep$Pi_vr 34 // "Current flowing into the pin"
#define $Pmotor$PcompoundDCExcitation$Pvse_vr 35 
#define $Pmotor$Pcore$PGc_vr 36 // "Variable core loss conductance"
#define $Pmotor$Pcore$PheatPort$PQ_flow_vr 37 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$Pcore$Pi_vr 38 // "Current flowing from pin p to pin n"
#define $Pmotor$Pcore$PlossPower_vr 39 // "Loss power leaving component via heatPort (> 0, if heat is flowing out of component)"
#define $Pmotor$Pcore$Pn$Pi_vr 40 // "Current flowing into the pin"
#define $Pmotor$Pcore$Pp$Pv_vr 41 // "Potential at the pin"
#define $Pmotor$Pcore$Pv_vr 42 // "Voltage drop between the two pins (= p.v - n.v)"
#define $Pmotor$Pcore$PwLimit_vr 43 // "Limited angular velocity"
#define $Pmotor$Pfixed$Pflange$Ptau_vr 44 // "Cut torque in the flange"
#define $Pmotor$Pfriction$Pphi_vr 45 // "Angle between shaft and support"
#define $Pmotor$Pfriction$Ptau_vr 46 // "Torque"
#define $Pmotor$Pfriction$Pw_vr 47 // "Relative angular velocity of flange and support"
#define $Pmotor$Pground$Pp$Pi_vr 48 // "Current flowing into the pin"
#define $Pmotor$Pground$Pp$Pv_vr 49 // "Potential at the pin"
#define $Pmotor$PgroundSE$Pp$Pv_vr 50 // "Potential at the pin"
#define $Pmotor$PinertiaRotor$Pa_vr 51 // "Absolute angular acceleration of component (= der(w))"
#define $Pmotor$PinertiaRotor$Pflange_b$Ptau_vr 52 // "Cut torque in the flange"
#define $Pmotor$PinertiaStator$Pa_vr 53 // "Absolute angular acceleration of component (= der(w))"
#define $Pmotor$PinertiaStator$Pflange_a$Ptau_vr 54 // "Cut torque in the flange"
#define $Pmotor$PinertiaStator$Pflange_b$Ptau_vr 55 // "Cut torque in the flange"
#define $Pmotor$PinertiaStator$Pw_vr 56 // "Absolute angular velocity of component (= der(phi))"
#define $Pmotor$PinternalSupport$Ptau_vr 57 // "Reaction torque in the support/housing"
#define $Pmotor$PinternalThermalPort$PheatPortArmature$PQ_flow_vr 58 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PinternalThermalPort$PheatPortBrush$PQ_flow_vr 59 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PinternalThermalPort$PheatPortCore$PQ_flow_vr 60 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PinternalThermalPort$PheatPortExcitation$PQ_flow_vr 61 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PinternalThermalPort$PheatPortFriction$PQ_flow_vr 62 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PinternalThermalPort$PheatPortStrayLoad$PQ_flow_vr 63 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$Pla$Pv_vr 64 // "Voltage drop between the two pins (= p.v - n.v)"
#define $Pmotor$Plesigma$Pi_vr 65 // "Current flowing from pin p to pin n"
#define $Pmotor$Plesigma$Pp$Pv_vr 66 // "Potential at the pin"
#define $Pmotor$Plesigma$Pv_vr 67 // "Voltage drop between the two pins (= p.v - n.v)"
#define $Pmotor$PpowerBalance$PlossPowerTotal_vr 68 // "Total loss power"
#define $Pmotor$PpowerBalance$PpowerArmature_vr 69 // "Electrical armature power"
#define $Pmotor$PpowerBalance$PpowerExcitation_vr 70 // "Electrical (shunt) excitation power"
#define $Pmotor$PpowerBalance$PpowerInertiaRotor_vr 71 // "Rotor inertia power"
#define $Pmotor$PpowerBalance$PpowerInertiaStator_vr 72 // "Stator inertia power"
#define $Pmotor$PpowerBalance$PpowerMechanical_vr 73 // "Mechanical power"
#define $Pmotor$Pra$PR_actual_vr 74 // "Actual resistance = R*(1 + alpha*(T_heatPort - T_ref))"
#define $Pmotor$Pra$Pv_vr 75 // "Voltage drop between the two pins (= p.v - n.v)"
#define $Pmotor$Pre$PR_actual_vr 76 // "Actual resistance = R*(1 + alpha*(T_heatPort - T_ref))"
#define $Pmotor$Pre$Pv_vr 77 // "Voltage drop between the two pins (= p.v - n.v)"
#define $Pmotor$PstrayLoad$Pflange$Ptau_vr 78 // "Cut torque in the flange"
#define $Pmotor$PstrayLoad$PheatPort$PQ_flow_vr 79 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PstrayLoad$PlossPower_vr 80 // "Loss power leaving component via heatPort (> 0, if heat is flowing out of component)"
#define $Pmotor$PstrayLoad$Pphi_vr 81 // "Angle between shaft and support"
#define $Pmotor$PstrayLoad$Ptau_vr 82 // "Torque"
#define $Pmotor$PstrayLoad$Pv_vr 83 // "Voltage drop between the two pins (= p.v - n.v)"
#define $Pmotor$PstrayLoad$Pw_vr 84 // "Relative angular velocity of flange and support"
#define $Pmotor$PtauElectrical_vr 85 // "Electromagnetic torque"
#define $Pmotor$PthermalAmbient$PQ_flowArmature_vr 86 // "Heat flow rate of armature"
#define $Pmotor$PthermalAmbient$PQ_flowExcitation_vr 87 // "Heat flow rate of (shunt) excitation"
#define $Pmotor$PthermalAmbient$PQ_flowFriction_vr 88 // "Heat flow rate of friction losses"
#define $Pmotor$PthermalAmbient$PQ_flowTotal_vr 89 
#define $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PT_vr 90 // "Port temperature"
#define $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PT_vr 91 // "Port temperature"
#define $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PT_vr 92 // "Port temperature"
#define $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PT_vr 93 // "Port temperature"
#define $Pmotor$Pva_vr 94 // "Armature voltage"
#define $Pmotor$PwMechanical_vr 95 // "Mechanical angular velocity of rotor against stator"
#define $Pspeed_vr 96 
#define $PspeedSensor1$Pflange$Pphi_vr 97 // "Absolute rotation angle of flange"
#define $PspeedSensor1$Pflange$Ptau_vr 98 // "Cut torque in the flange"
#define $Ptorque1$Pphi_support_vr 99 // "Absolute angle of support flange"
#define $Pup_ground$Pp$Pi_vr 100 // "Current flowing into the pin"
#define $Pup_ground$Pp$Pv_vr 101 // "Potential at the pin"
#define $Pup_input_vr 102 
#define $Pup_voltage$Pi_vr 103 // "Current flowing from pin p to pin n"
#define $Pvoltage_ground$Pp$Pi_vr 104 // "Current flowing into the pin"
#define $Pvoltage_ground$Pp$Pv_vr 105 // "Potential at the pin"
#define $PconvertToBoolean$Pthreshold_vr 106 // "Comparison with respect to threshold"
#define $Pdc_motor_power$PV_vr 107 // "Value of constant voltage"
#define $PgreaterThreshold1$Pthreshold_vr 108 // "Comparison with respect to threshold"
#define $PidealCommutingSwitch1$PGoff_vr 109 // "Opened switch conductance"
#define $PidealCommutingSwitch1$PRon_vr 110 // "Closed switch resistance"
#define $PidealCommutingSwitch1$PT_vr 111 // "Fixed device temperature if useHeatPort = false"
#define $PidealCommutingSwitch2$PGoff_vr 112 // "Opened switch conductance"
#define $PidealCommutingSwitch2$PRon_vr 113 // "Closed switch resistance"
#define $PidealCommutingSwitch2$PT_vr 114 // "Fixed device temperature if useHeatPort = false"
#define $Pmotor$PIaNominal_vr 115 // "Nominal armature current (>0..Motor, <0..Generator)"
#define $Pmotor$PIeNominal_vr 116 // "Nominal excitation current"
#define $Pmotor$PJr_vr 117 // "Rotor's moment of inertia"
#define $Pmotor$PJs_vr 118 // "Stator's moment of inertia"
#define $Pmotor$PLa_vr 119 // "Armature inductance"
#define $Pmotor$PLe_vr 120 // "Total field excitation inductance"
#define $Pmotor$PLesigma_vr 121 // "Stray part of excitation inductance"
#define $Pmotor$PLme_vr 122 // "Main part of excitation inductance"
#define $Pmotor$PRa_vr 123 // "Armature resistance at TRef"
#define $Pmotor$PRe_vr 124 // "Field excitation resistance at TRef"
#define $Pmotor$PTaNominal_vr 125 // "Nominal armature temperature"
#define $Pmotor$PTaOperational_vr 126 // "Operational armature temperature"
#define $Pmotor$PTaRef_vr 127 // "Reference temperature of armature resistance"
#define $Pmotor$PTeOperational_vr 128 // "Operational (shunt) excitation temperature"
#define $Pmotor$PTeRef_vr 129 // "Reference temperature of excitation resistance"
#define $Pmotor$PVaNominal_vr 130 // "Nominal armature voltage"
#define $Pmotor$PViNominal_vr 131 // "Nominal induced Voltage"
#define $Pmotor$PairGapDC$PLe_vr 132 // "Excitation inductance"
#define $Pmotor$PairGapDC$PturnsRatio_vr 133 // "Ratio of armature turns over number of turns of the excitation winding"
#define $Pmotor$Palpha20a_vr 134 // "Temperature coefficient of armature resistance"
#define $Pmotor$Palpha20e_vr 135 // "Temperature coefficient of excitation resistance"
#define $Pmotor$Pbrush$PbrushParameters$PILinear_vr 136 // "Current indicating linear voltage region of brush voltage drop"
#define $Pmotor$Pbrush$PbrushParameters$PV_vr 137 // "Total voltage drop of brushes for currents > ILinear"
#define $Pmotor$PbrushParameters$PILinear_vr 138 // "Current indicating linear voltage region of brush voltage drop"
#define $Pmotor$PbrushParameters$PV_vr 139 // "Total voltage drop of brushes for currents > ILinear"
#define $Pmotor$PcompoundDCExcitation$PexcitationTurnsRatio_vr 140 // "Ratio of series excitation turns over shunt excitation turns"
#define $Pmotor$Pcore$PcoreParameters$PGcRef_vr 141 // "Reference conductance at reference frequency and voltage"
#define $Pmotor$Pcore$PcoreParameters$PPRef_vr 142 // "Reference core losses at reference inner voltage VRef"
#define $Pmotor$Pcore$PcoreParameters$PVRef_vr 143 // "Reference inner RMS voltage that reference core losses PRef refer to"
#define $Pmotor$Pcore$PcoreParameters$PratioHysteresis_vr 144 // "Ratio of hysteresis losses with respect to the total core losses at VRef and fRef"
#define $Pmotor$Pcore$PcoreParameters$PwMin_vr 145 
#define $Pmotor$Pcore$PcoreParameters$PwRef_vr 146 // "Reference angular velocity that reference core losses PRef refer to"
#define $Pmotor$PcoreParameters$PGcRef_vr 147 // "Reference conductance at reference frequency and voltage"
#define $Pmotor$PcoreParameters$PPRef_vr 148 // "Reference core losses at reference inner voltage VRef"
#define $Pmotor$PcoreParameters$PVRef_vr 149 // "Reference inner RMS voltage that reference core losses PRef refer to"
#define $Pmotor$PcoreParameters$PratioHysteresis_vr 150 // "Ratio of hysteresis losses with respect to the total core losses at VRef and fRef"
#define $Pmotor$PcoreParameters$PwMin_vr 151 
#define $Pmotor$PcoreParameters$PwRef_vr 152 // "Reference angular velocity that reference core losses PRef refer to"
#define $Pmotor$Pfixed$Pphi0_vr 153 // "Fixed offset angle of housing"
#define $Pmotor$Pfriction$PfrictionParameters$PPRef_vr 154 // "Reference friction losses at wRef"
#define $Pmotor$Pfriction$PfrictionParameters$Plinear_vr 155 // "Linear angular velocity range with respect to reference angular velocity"
#define $Pmotor$Pfriction$PfrictionParameters$Ppower_w_vr 156 // "Exponent of friction torque w.r.t. angular velocity"
#define $Pmotor$Pfriction$PfrictionParameters$PtauLinear_vr 157 // "Torque corresponding with linear angular velocity range"
#define $Pmotor$Pfriction$PfrictionParameters$PtauRef_vr 158 // "Reference friction torque at reference angular velocity"
#define $Pmotor$Pfriction$PfrictionParameters$PwLinear_vr 159 // "Linear angular velocity range"
#define $Pmotor$Pfriction$PfrictionParameters$PwRef_vr 160 // "Reference angular velocity that the PRef refer to"
#define $Pmotor$PfrictionParameters$PPRef_vr 161 // "Reference friction losses at wRef"
#define $Pmotor$PfrictionParameters$Plinear_vr 162 // "Linear angular velocity range with respect to reference angular velocity"
#define $Pmotor$PfrictionParameters$Ppower_w_vr 163 // "Exponent of friction torque w.r.t. angular velocity"
#define $Pmotor$PfrictionParameters$PtauLinear_vr 164 // "Torque corresponding with linear angular velocity range"
#define $Pmotor$PfrictionParameters$PtauRef_vr 165 // "Reference friction torque at reference angular velocity"
#define $Pmotor$PfrictionParameters$PwLinear_vr 166 // "Linear angular velocity range"
#define $Pmotor$PfrictionParameters$PwRef_vr 167 // "Reference angular velocity that the PRef refer to"
#define $Pmotor$PinertiaRotor$PJ_vr 168 // "Moment of inertia"
#define $Pmotor$PinertiaStator$PJ_vr 169 // "Moment of inertia"
#define $Pmotor$Pla$PL_vr 170 // "Inductance"
#define $Pmotor$Plesigma$PL_vr 171 // "Inductance"
#define $Pmotor$Ppsi_eNominal_vr 172 // "Nominal magnetic flux"
#define $Pmotor$Pra$PR_vr 173 // "Resistance at temperature T_ref"
#define $Pmotor$Pra$PT_vr 174 // "Fixed device temperature if useHeatPort = false"
#define $Pmotor$Pra$PT_ref_vr 175 // "Reference temperature"
#define $Pmotor$Pra$Palpha_vr 176 // "Temperature coefficient of resistance (R_actual = R*(1 + alpha*(T_heatPort - T_ref))"
#define $Pmotor$Pre$PR_vr 177 // "Resistance at temperature T_ref"
#define $Pmotor$Pre$PT_vr 178 // "Fixed device temperature if useHeatPort = false"
#define $Pmotor$Pre$PT_ref_vr 179 // "Reference temperature"
#define $Pmotor$Pre$Palpha_vr 180 // "Temperature coefficient of resistance (R_actual = R*(1 + alpha*(T_heatPort - T_ref))"
#define $Pmotor$Psigmae_vr 181 // "Stray fraction of total excitation inductance"
#define $Pmotor$PstrayLoad$PstrayLoadParameters$PIRef_vr 182 // "Reference RMS current that PRef refers to"
#define $Pmotor$PstrayLoad$PstrayLoadParameters$PPRef_vr 183 // "Reference stray load losses at IRef and wRef"
#define $Pmotor$PstrayLoad$PstrayLoadParameters$Ppower_w_vr 184 // "Exponent of stray load loss torque w.r.t. angular velocity"
#define $Pmotor$PstrayLoad$PstrayLoadParameters$PtauRef_vr 185 // "Reference stray load torque at reference angular velocity and reference current"
#define $Pmotor$PstrayLoad$PstrayLoadParameters$PwRef_vr 186 // "Reference angular velocity that PRef refers to"
#define $Pmotor$PstrayLoadParameters$PIRef_vr 187 // "Reference RMS current that PRef refers to"
#define $Pmotor$PstrayLoadParameters$PPRef_vr 188 // "Reference stray load losses at IRef and wRef"
#define $Pmotor$PstrayLoadParameters$Ppower_w_vr 189 // "Exponent of stray load loss torque w.r.t. angular velocity"
#define $Pmotor$PstrayLoadParameters$PtauRef_vr 190 // "Reference stray load torque at reference angular velocity and reference current"
#define $Pmotor$PstrayLoadParameters$PwRef_vr 191 // "Reference angular velocity that PRef refers to"
#define $Pmotor$PthermalAmbient$PTa_vr 192 // "Temperature of armature"
#define $Pmotor$PthermalAmbient$PTe_vr 193 // "Temperature of (shunt) excitation"
#define $Pmotor$PthermalAmbient$PconstTa$Pk_vr 194 // "Constant output value"
#define $Pmotor$PthermalAmbient$PconstTe$Pk_vr 195 // "Constant output value"
#define $Pmotor$PthermalAmbient$PtemperatureBrush$PT_vr 196 // "Fixed temperature at port"
#define $Pmotor$PthermalAmbient$PtemperatureCore$PT_vr 197 // "Fixed temperature at port"
#define $Pmotor$PthermalAmbient$PtemperatureFriction$PT_vr 198 // "Fixed temperature at port"
#define $Pmotor$PthermalAmbient$PtemperatureStrayLoad$PT_vr 199 // "Fixed temperature at port"
#define $Pmotor$PturnsRatio_vr 200 // "Ratio of armature turns over number of turns of the excitation winding"
#define $Pmotor$PwNominal_vr 201 // "Nominal speed"
#define $Pmotor_frictionParameters$PPRef_vr 202 // "Reference friction losses at wRef"
#define $Pmotor_frictionParameters$Plinear_vr 203 // "Linear angular velocity range with respect to reference angular velocity"
#define $Pmotor_frictionParameters$Ppower_w_vr 204 // "Exponent of friction torque w.r.t. angular velocity"
#define $Pmotor_frictionParameters$PtauLinear_vr 205 // "Torque corresponding with linear angular velocity range"
#define $Pmotor_frictionParameters$PtauRef_vr 206 // "Reference friction torque at reference angular velocity"
#define $Pmotor_frictionParameters$PwLinear_vr 207 // "Linear angular velocity range"
#define $Pmotor_frictionParameters$PwRef_vr 208 // "Reference angular velocity that the PRef refer to"
#define $Pup_voltage$PV_vr 209 // "Value of constant voltage"
#define $Parm_sensor$Pi_vr 210 // "Current in the branch from p to n as output signal"
#define $Parm_sensor$Pn$Pi_vr 211 // "Current flowing into the pin"
#define $Parm_sensor$Pn$Pv_vr 212 // "Potential at the pin"
#define $Parm_sensor$Pp$Pi_vr 213 // "Current flowing into the pin"
#define $PconvertToBoolean$Pu_vr 214 // "Connector of Boolean input signal"
#define $Pdc_motor_power$Pi_vr 215 // "Current flowing from pin p to pin n"
#define $Pdc_motor_power$Pn$Pi_vr 216 // "Current flowing into the pin"
#define $Pdc_motor_power$Pn$Pv_vr 217 // "Potential at the pin"
#define $Pdc_motor_power$Pp$Pi_vr 218 // "Current flowing into the pin"
#define $Pdc_motor_power$Pp$Pv_vr 219 // "Potential at the pin"
#define $Pdc_motor_power$Pv_vr 220 // "Voltage drop between the two pins (= p.v - n.v)"
#define $PgreaterThreshold1$Pu_vr 221 // "Connector of Boolean input signal"
#define $PidealCommutingSwitch1$PT_heatPort_vr 222 // "Temperature of heatPort"
#define $PidealCommutingSwitch1$Pn1$Pv_vr 223 // "Potential at the pin"
#define $PidealCommutingSwitch1$Pn2$Pv_vr 224 // "Potential at the pin"
#define $PidealCommutingSwitch1$Pp$Pi_vr 225 // "Current flowing into the pin"
#define $PidealCommutingSwitch1$Pp$Pv_vr 226 // "Potential at the pin"
#define $PidealCommutingSwitch2$PT_heatPort_vr 227 // "Temperature of heatPort"
#define $PidealCommutingSwitch2$Pn1$Pv_vr 228 // "Potential at the pin"
#define $PidealCommutingSwitch2$Pn2$Pv_vr 229 // "Potential at the pin"
#define $PidealCommutingSwitch2$Pp$Pi_vr 230 // "Current flowing into the pin"
#define $Pmotor$PairGapDC$Pflange$Pphi_vr 231 // "Absolute rotation angle of flange"
#define $Pmotor$PairGapDC$Pflange$Ptau_vr 232 // "Cut torque in the flange"
#define $Pmotor$PairGapDC$Pia_vr 233 // "Armature current"
#define $Pmotor$PairGapDC$Pie_vr 234 // "Excitation current"
#define $Pmotor$PairGapDC$Ppin_an$Pi_vr 235 // "Current flowing into the pin"
#define $Pmotor$PairGapDC$Ppin_an$Pv_vr 236 // "Potential at the pin"
#define $Pmotor$PairGapDC$Ppin_ap$Pi_vr 237 // "Current flowing into the pin"
#define $Pmotor$PairGapDC$Ppin_en$Pi_vr 238 // "Current flowing into the pin"
#define $Pmotor$PairGapDC$Ppin_en$Pv_vr 239 // "Potential at the pin"
#define $Pmotor$PairGapDC$Ppin_ep$Pi_vr 240 // "Current flowing into the pin"
#define $Pmotor$PairGapDC$Ppin_ep$Pv_vr 241 // "Potential at the pin"
#define $Pmotor$PairGapDC$Psupport$Pphi_vr 242 // "Absolute rotation angle of flange"
#define $Pmotor$PairGapDC$Psupport$Ptau_vr 243 // "Cut torque in the flange"
#define $Pmotor$PairGapDC$PtauElectrical_vr 244 
#define $Pmotor$PairGapDC$Pw_vr 245 // "Angular velocity"
#define $Pmotor$Pbrush$PheatPort$PT_vr 246 // "Port temperature"
#define $Pmotor$Pbrush$Pi_vr 247 // "Current flowing from pin p to pin n"
#define $Pmotor$Pbrush$Pn$Pi_vr 248 // "Current flowing into the pin"
#define $Pmotor$Pbrush$Pn$Pv_vr 249 // "Potential at the pin"
#define $Pmotor$Pbrush$Pp$Pi_vr 250 // "Current flowing into the pin"
#define $Pmotor$Pbrush$Pp$Pv_vr 251 // "Potential at the pin"
#define $Pmotor$PcompoundDCExcitation$Pi_vr 252 
#define $Pmotor$PcompoundDCExcitation$Pie_vr 253 
#define $Pmotor$PcompoundDCExcitation$Pise_vr 254 
#define $Pmotor$PcompoundDCExcitation$Ppin_en$Pi_vr 255 // "Current flowing into the pin"
#define $Pmotor$PcompoundDCExcitation$Ppin_en$Pv_vr 256 // "Potential at the pin"
#define $Pmotor$PcompoundDCExcitation$Ppin_ep$Pi_vr 257 // "Current flowing into the pin"
#define $Pmotor$PcompoundDCExcitation$Ppin_ep$Pv_vr 258 // "Potential at the pin"
#define $Pmotor$PcompoundDCExcitation$Ppin_n$Pi_vr 259 // "Current flowing into the pin"
#define $Pmotor$PcompoundDCExcitation$Ppin_n$Pv_vr 260 // "Potential at the pin"
#define $Pmotor$PcompoundDCExcitation$Ppin_p$Pi_vr 261 // "Current flowing into the pin"
#define $Pmotor$PcompoundDCExcitation$Ppin_p$Pv_vr 262 // "Potential at the pin"
#define $Pmotor$PcompoundDCExcitation$Ppin_sen$Pv_vr 263 // "Potential at the pin"
#define $Pmotor$PcompoundDCExcitation$Ppin_sep$Pv_vr 264 // "Potential at the pin"
#define $Pmotor$PcompoundDCExcitation$Pv_vr 265 
#define $Pmotor$PcompoundDCExcitation$Pve_vr 266 
#define $Pmotor$Pcore$PheatPort$PT_vr 267 // "Port temperature"
#define $Pmotor$Pcore$Pn$Pv_vr 268 // "Potential at the pin"
#define $Pmotor$Pcore$Pp$Pi_vr 269 // "Current flowing into the pin"
#define $Pmotor$Pcore$Pw_vr 270 // "Remagnetization angular velocity"
#define $Pmotor$Pfixed$Pflange$Pphi_vr 271 // "Absolute rotation angle of flange"
#define $Pmotor$Pflange$Pphi_vr 272 // "Absolute rotation angle of flange"
#define $Pmotor$Pflange$Ptau_vr 273 // "Cut torque in the flange"
#define $Pmotor$Pfriction$Pflange$Pphi_vr 274 // "Absolute rotation angle of flange"
#define $Pmotor$Pfriction$Pflange$Ptau_vr 275 // "Cut torque in the flange"
#define $Pmotor$Pfriction$PheatPort$PQ_flow_vr 276 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$Pfriction$PheatPort$PT_vr 277 // "Port temperature"
#define $Pmotor$Pfriction$PlossPower_vr 278 // "Loss power leaving component via heatPort (> 0, if heat is flowing out of component)"
#define $Pmotor$Pfriction$Psupport$Pphi_vr 279 // "Absolute rotation angle of flange"
#define $Pmotor$Pfriction$Psupport$Ptau_vr 280 // "Cut torque in the flange"
#define $Pmotor$PgroundSE$Pp$Pi_vr 281 // "Current flowing into the pin"
#define $Pmotor$Pia_vr 282 // "Armature current"
#define $Pmotor$Pie_vr 283 // "Field excitation current"
#define $Pmotor$PinertiaRotor$Pflange_a$Pphi_vr 284 // "Absolute rotation angle of flange"
#define $Pmotor$PinertiaRotor$Pflange_a$Ptau_vr 285 // "Cut torque in the flange"
#define $Pmotor$PinertiaRotor$Pflange_b$Pphi_vr 286 // "Absolute rotation angle of flange"
#define $Pmotor$PinertiaRotor$Pphi_vr 287 // "Absolute rotation angle of component"
#define $Pmotor$PinertiaStator$Pflange_a$Pphi_vr 288 // "Absolute rotation angle of flange"
#define $Pmotor$PinertiaStator$Pflange_b$Pphi_vr 289 // "Absolute rotation angle of flange"
#define $Pmotor$PinertiaStator$Pphi_vr 290 // "Absolute rotation angle of component"
#define $Pmotor$PinternalSupport$Pphi_vr 291 // "Absolute rotation angle of the support/housing"
#define $Pmotor$PinternalThermalPort$PheatPortArmature$PT_vr 292 // "Port temperature"
#define $Pmotor$PinternalThermalPort$PheatPortBrush$PT_vr 293 // "Port temperature"
#define $Pmotor$PinternalThermalPort$PheatPortCore$PT_vr 294 // "Port temperature"
#define $Pmotor$PinternalThermalPort$PheatPortExcitation$PT_vr 295 // "Port temperature"
#define $Pmotor$PinternalThermalPort$PheatPortFriction$PT_vr 296 // "Port temperature"
#define $Pmotor$PinternalThermalPort$PheatPortStrayLoad$PT_vr 297 // "Port temperature"
#define $Pmotor$Pla$Pn$Pi_vr 298 // "Current flowing into the pin"
#define $Pmotor$Pla$Pn$Pv_vr 299 // "Potential at the pin"
#define $Pmotor$Pla$Pp$Pi_vr 300 // "Current flowing into the pin"
#define $Pmotor$Pla$Pp$Pv_vr 301 // "Potential at the pin"
#define $Pmotor$Plesigma$Pn$Pi_vr 302 // "Current flowing into the pin"
#define $Pmotor$Plesigma$Pn$Pv_vr 303 // "Potential at the pin"
#define $Pmotor$Plesigma$Pp$Pi_vr 304 // "Current flowing into the pin"
#define $Pmotor$Ppin_an$Pi_vr 305 // "Current flowing into the pin"
#define $Pmotor$Ppin_an$Pv_vr 306 // "Potential at the pin"
#define $Pmotor$Ppin_ap$Pi_vr 307 // "Current flowing into the pin"
#define $Pmotor$Ppin_ap$Pv_vr 308 // "Potential at the pin"
#define $Pmotor$Ppin_en$Pi_vr 309 // "Current flowing into the pin"
#define $Pmotor$Ppin_en$Pv_vr 310 // "Potential at the pin"
#define $Pmotor$Ppin_ep$Pi_vr 311 // "Current flowing into the pin"
#define $Pmotor$Ppin_ep$Pv_vr 312 // "Potential at the pin"
#define $Pmotor$PpowerBalance$PlossPowerArmature_vr 313 // "Armature copper losses"
#define $Pmotor$PpowerBalance$PlossPowerBrush_vr 314 // "Brush losses"
#define $Pmotor$PpowerBalance$PlossPowerCore_vr 315 // "Core losses"
#define $Pmotor$PpowerBalance$PlossPowerExcitation_vr 316 // "Excitation losses"
#define $Pmotor$PpowerBalance$PlossPowerFriction_vr 317 // "Friction losses"
#define $Pmotor$PpowerBalance$PlossPowerStrayLoad_vr 318 // "Stray load losses"
#define $Pmotor$Pra$PLossPower_vr 319 // "Loss power leaving component via heatPort"
#define $Pmotor$Pra$PT_heatPort_vr 320 // "Temperature of heatPort"
#define $Pmotor$Pra$PheatPort$PQ_flow_vr 321 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$Pra$PheatPort$PT_vr 322 // "Port temperature"
#define $Pmotor$Pra$Pi_vr 323 // "Current flowing from pin p to pin n"
#define $Pmotor$Pra$Pn$Pi_vr 324 // "Current flowing into the pin"
#define $Pmotor$Pra$Pn$Pv_vr 325 // "Potential at the pin"
#define $Pmotor$Pra$Pp$Pi_vr 326 // "Current flowing into the pin"
#define $Pmotor$Pra$Pp$Pv_vr 327 // "Potential at the pin"
#define $Pmotor$Pre$PLossPower_vr 328 // "Loss power leaving component via heatPort"
#define $Pmotor$Pre$PT_heatPort_vr 329 // "Temperature of heatPort"
#define $Pmotor$Pre$PheatPort$PQ_flow_vr 330 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$Pre$PheatPort$PT_vr 331 // "Port temperature"
#define $Pmotor$Pre$Pi_vr 332 // "Current flowing from pin p to pin n"
#define $Pmotor$Pre$Pn$Pi_vr 333 // "Current flowing into the pin"
#define $Pmotor$Pre$Pn$Pv_vr 334 // "Potential at the pin"
#define $Pmotor$Pre$Pp$Pi_vr 335 // "Current flowing into the pin"
#define $Pmotor$Pre$Pp$Pv_vr 336 // "Potential at the pin"
#define $Pmotor$PstrayLoad$Pflange$Pphi_vr 337 // "Absolute rotation angle of flange"
#define $Pmotor$PstrayLoad$PheatPort$PT_vr 338 // "Port temperature"
#define $Pmotor$PstrayLoad$Pi_vr 339 // "Current flowing from pin p to pin n"
#define $Pmotor$PstrayLoad$Pn$Pi_vr 340 // "Current flowing into the pin"
#define $Pmotor$PstrayLoad$Pn$Pv_vr 341 // "Potential at the pin"
#define $Pmotor$PstrayLoad$Pp$Pi_vr 342 // "Current flowing into the pin"
#define $Pmotor$PstrayLoad$Pp$Pv_vr 343 // "Potential at the pin"
#define $Pmotor$PstrayLoad$Psupport$Pphi_vr 344 // "Absolute rotation angle of flange"
#define $Pmotor$PstrayLoad$Psupport$Ptau_vr 345 // "Cut torque in the flange"
#define $Pmotor$PtauShaft_vr 346 // "Shaft torque"
#define $Pmotor$PthermalAmbient$PQ_flowBrush_vr 347 // "Heat flow rate of brushes"
#define $Pmotor$PthermalAmbient$PQ_flowCore_vr 348 // "Heat flow rate of core losses"
#define $Pmotor$PthermalAmbient$PQ_flowStrayLoad_vr 349 // "Heat flow rate of stray load losses"
#define $Pmotor$PthermalAmbient$PconstTa$Py_vr 350 // "Connector of Real output signal"
#define $Pmotor$PthermalAmbient$PconstTe$Py_vr 351 // "Connector of Real output signal"
#define $Pmotor$PthermalAmbient$PtemperatureArmature$PT_vr 352 
#define $Pmotor$PthermalAmbient$PtemperatureArmature$Pport$PQ_flow_vr 353 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PtemperatureArmature$Pport$PT_vr 354 // "Port temperature"
#define $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PQ_flow_vr 355 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PQ_flow_vr 356 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PtemperatureExcitation$PT_vr 357 
#define $Pmotor$PthermalAmbient$PtemperatureExcitation$Pport$PQ_flow_vr 358 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PtemperatureExcitation$Pport$PT_vr 359 // "Port temperature"
#define $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PQ_flow_vr 360 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PQ_flow_vr 361 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortArmature$PQ_flow_vr 362 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortArmature$PT_vr 363 // "Port temperature"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortBrush$PQ_flow_vr 364 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortBrush$PT_vr 365 // "Port temperature"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortCore$PQ_flow_vr 366 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortCore$PT_vr 367 // "Port temperature"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortExcitation$PQ_flow_vr 368 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortExcitation$PT_vr 369 // "Port temperature"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortFriction$PQ_flow_vr 370 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortFriction$PT_vr 371 // "Port temperature"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortStrayLoad$PQ_flow_vr 372 // "Heat flow rate (positive if flowing from outside into the component)"
#define $Pmotor$PthermalAmbient$PthermalPort$PheatPortStrayLoad$PT_vr 373 // "Port temperature"
#define $Pmotor$Pve_vr 374 // "Field excitation voltage"
#define $PspeedSensor1$Pw_vr 375 // "Absolute angular velocity of flange as output signal"
#define $Ptorque1$Pflange$Pphi_vr 376 // "Absolute rotation angle of flange"
#define $Ptorque1$Pflange$Ptau_vr 377 // "Cut torque in the flange"
#define $Ptorque1$Ptau_vr 378 // "Accelerating torque acting at flange (= -flange.tau)"
#define $Pup_voltage$Pn$Pi_vr 379 // "Current flowing into the pin"
#define $Pup_voltage$Pn$Pv_vr 380 // "Potential at the pin"
#define $Pup_voltage$Pp$Pi_vr 381 // "Current flowing into the pin"
#define $Pup_voltage$Pp$Pv_vr 382 // "Potential at the pin"
#define $Pup_voltage$Pv_vr 383 // "Voltage drop between the two pins (= p.v - n.v)"
#define $Pmotor$Pcore$PcoreParameters$Pm_vr 0 // "Number of phases (1 for DC, 3 for induction machines)"
#define $Pmotor$PcoreParameters$Pm_vr 1 // "Number of phases (1 for DC, 3 for induction machines)"
#define $Pmotor$PinertiaRotor$PstateSelect_vr 2 // "Priority to use phi and w as states"
#define $Pmotor$PinertiaStator$PstateSelect_vr 3 // "Priority to use phi and w as states"
#define $PconvertToBoolean$Py_vr 0 // "Connector of Boolean output signal"
#define $PgreaterThreshold1$Py_vr 1 // "Connector of Boolean output signal"
#define $PidealCommutingSwitch1$PuseHeatPort_vr 2 // "=true, if heatPort is enabled"
#define $PidealCommutingSwitch2$PuseHeatPort_vr 3 // "=true, if heatPort is enabled"
#define $Pmotor$PairGapDC$PquasiStationary_vr 4 // "No electrical transients if true"
#define $Pmotor$Pbrush$PuseHeatPort_vr 5 // "=true, if heatPort is enabled"
#define $Pmotor$Pcore$PuseHeatPort_vr 6 // "=true, if heatPort is enabled"
#define $Pmotor$Pfriction$PuseHeatPort_vr 7 // "=true, if heatPort is enabled"
#define $Pmotor$Pla$PquasiStationary_vr 8 // "No electrical transients if true"
#define $Pmotor$Plesigma$PquasiStationary_vr 9 // "No electrical transients if true"
#define $Pmotor$Pra$PuseHeatPort_vr 10 // "=true, if heatPort is enabled"
#define $Pmotor$Pre$PuseHeatPort_vr 11 // "=true, if heatPort is enabled"
#define $Pmotor$PstrayLoad$PuseHeatPort_vr 12 // "=true, if heatPort is enabled"
#define $Pmotor$PthermalAmbient$PuseTemperatureInputs_vr 13 // "If true, temperature inputs are used; else, temperatures are constant"
#define $Pmotor$PuseSupport_vr 14 // "Enable / disable (=fixed stator) support"
#define $Pmotor$PuseThermalPort_vr 15 // "Enable / disable (=fixed temperatures) thermal port"
#define $Ptorque1$PuseSupport_vr 16 // "= true, if support flange enabled, otherwise implicitly grounded"
#define $PidealCommutingSwitch1$Pcontrol_vr 17 // "true => p--n2 connected, false => p--n1 connected"
#define $PidealCommutingSwitch2$Pcontrol_vr 18 // "true => p--n2 connected, false => p--n1 connected"


// define initial state vector as vector of value references
#define STATES { $Pmotor$PairGapDC$Ppsi_e_vr, $Pmotor$PinertiaRotor$Pw_vr, $Pmotor$Pla$Pi_vr, $Pmotor$PphiMechanical_vr }
#define STATESDERIVATIVES { $P$DER$Pmotor$PairGapDC$Ppsi_e_vr, $P$DER$Pmotor$PinertiaRotor$Pw_vr, $P$DER$Pmotor$Pla$Pi_vr, $P$DER$Pmotor$PphiMechanical_vr }


// implementation of the Model Exchange functions
  extern void PW_PowerSystem_setupDataStruc(DATA *data);
  #define fmu2_model_interface_setupDataStruc PW_PowerSystem_setupDataStruc
  #include "fmi2/fmu2_model_interface.c"

// Set values for all variables that define a start value
void setDefaultStartValues(ModelInstance *comp) {

comp->fmuData->modelData->realVarsData[0].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[1].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[2].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[3].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[4].attribute.start = 0;
comp->fmuData->modelData->realVarsData[5].attribute.start = 0;
comp->fmuData->modelData->realVarsData[6].attribute.start = 0;
comp->fmuData->modelData->realVarsData[7].attribute.start = 0;
comp->fmuData->modelData->realVarsData[8].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[9].attribute.start = 0;
comp->fmuData->modelData->realVarsData[10].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[11].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[12].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[13].attribute.start = 0;
comp->fmuData->modelData->realVarsData[14].attribute.start = 0;
comp->fmuData->modelData->realVarsData[15].attribute.start = 0;
comp->fmuData->modelData->realVarsData[16].attribute.start = 0;
comp->fmuData->modelData->realVarsData[17].attribute.start = 0;
comp->fmuData->modelData->realVarsData[18].attribute.start = 0;
comp->fmuData->modelData->realVarsData[19].attribute.start = 0;
comp->fmuData->modelData->realVarsData[20].attribute.start = 0;
comp->fmuData->modelData->realVarsData[21].attribute.start = 0;
comp->fmuData->modelData->realVarsData[22].attribute.start = 0;
comp->fmuData->modelData->realVarsData[23].attribute.start = 0;
comp->fmuData->modelData->realVarsData[24].attribute.start = 0;
comp->fmuData->modelData->realVarsData[25].attribute.start = 0;
comp->fmuData->modelData->realVarsData[26].attribute.start = 0;
comp->fmuData->modelData->realVarsData[27].attribute.start = 0;
comp->fmuData->modelData->realVarsData[28].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[29].attribute.start = 0;
comp->fmuData->modelData->realVarsData[30].attribute.start = 0;
comp->fmuData->modelData->realVarsData[31].attribute.start = 0;
comp->fmuData->modelData->realVarsData[32].attribute.start = 0;
comp->fmuData->modelData->realVarsData[33].attribute.start = 0;
comp->fmuData->modelData->realVarsData[34].attribute.start = 0;
comp->fmuData->modelData->realVarsData[35].attribute.start = 0;
comp->fmuData->modelData->realVarsData[36].attribute.start = 0;
comp->fmuData->modelData->realVarsData[37].attribute.start = 0;
comp->fmuData->modelData->realVarsData[38].attribute.start = 0;
comp->fmuData->modelData->realVarsData[39].attribute.start = 0;
comp->fmuData->modelData->realVarsData[40].attribute.start = 0;
comp->fmuData->modelData->realVarsData[41].attribute.start = 0;
comp->fmuData->modelData->realVarsData[42].attribute.start = 0;
comp->fmuData->modelData->realVarsData[43].attribute.start = 0;
comp->fmuData->modelData->realVarsData[44].attribute.start = 0;
comp->fmuData->modelData->realVarsData[45].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[46].attribute.start = 0;
comp->fmuData->modelData->realVarsData[47].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[48].attribute.start = 0;
comp->fmuData->modelData->realVarsData[49].attribute.start = 0;
comp->fmuData->modelData->realVarsData[50].attribute.start = 0;
comp->fmuData->modelData->realVarsData[51].attribute.start = 0;
comp->fmuData->modelData->realVarsData[52].attribute.start = 0;
comp->fmuData->modelData->realVarsData[53].attribute.start = 0;
comp->fmuData->modelData->realVarsData[54].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[55].attribute.start = 0;
comp->fmuData->modelData->realVarsData[56].attribute.start = 0;
comp->fmuData->modelData->realVarsData[57].attribute.start = 0;
comp->fmuData->modelData->realVarsData[58].attribute.start = 0;
comp->fmuData->modelData->realVarsData[59].attribute.start = 0;
comp->fmuData->modelData->realVarsData[60].attribute.start = 0;
comp->fmuData->modelData->realVarsData[61].attribute.start = 0;
comp->fmuData->modelData->realVarsData[62].attribute.start = 0;
comp->fmuData->modelData->realVarsData[63].attribute.start = 0;
comp->fmuData->modelData->realVarsData[64].attribute.start = 0;
comp->fmuData->modelData->realVarsData[65].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[66].attribute.start = 12.0;
comp->fmuData->modelData->realVarsData[67].attribute.start = 0;
comp->fmuData->modelData->realVarsData[68].attribute.start = 0;
comp->fmuData->modelData->realVarsData[69].attribute.start = 0;
comp->fmuData->modelData->realVarsData[70].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[71].attribute.start = 0;
comp->fmuData->modelData->realVarsData[72].attribute.start = 0;
comp->fmuData->modelData->realVarsData[73].attribute.start = 0;
comp->fmuData->modelData->realVarsData[74].attribute.start = 0;
comp->fmuData->modelData->realVarsData[75].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[76].attribute.start = 0;
comp->fmuData->modelData->realVarsData[77].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[78].attribute.start = 0;
comp->fmuData->modelData->realVarsData[79].attribute.start = 0;
comp->fmuData->modelData->realVarsData[80].attribute.start = 0;
comp->fmuData->modelData->realVarsData[81].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[82].attribute.start = 0;
comp->fmuData->modelData->realVarsData[83].attribute.start = 0;
comp->fmuData->modelData->realVarsData[84].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[85].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[86].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[87].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[88].attribute.start = 0;
comp->fmuData->modelData->realVarsData[89].attribute.start = 0;
comp->fmuData->modelData->realVarsData[90].attribute.start = 288.15;
comp->fmuData->modelData->realVarsData[91].attribute.start = 288.15;
comp->fmuData->modelData->realVarsData[92].attribute.start = 288.15;
comp->fmuData->modelData->realVarsData[93].attribute.start = 288.15;
comp->fmuData->modelData->realVarsData[94].attribute.start = 0;
comp->fmuData->modelData->realVarsData[95].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[96].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[97].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[98].attribute.start = 0;
comp->fmuData->modelData->realVarsData[99].attribute.start = 0;
comp->fmuData->modelData->realVarsData[100].attribute.start = 0;
comp->fmuData->modelData->realVarsData[101].attribute.start = 0;
comp->fmuData->modelData->realVarsData[102].attribute.start = 0;
comp->fmuData->modelData->realVarsData[103].attribute.start = 0;
comp->fmuData->modelData->realVarsData[104].attribute.start = 0;
comp->fmuData->modelData->realVarsData[105].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[0].attribute.start = 0;
comp->fmuData->modelData->booleanVarsData[1].attribute.start = 0;
comp->fmuData->modelData->realParameterData[0].attribute.start = 0.5;
comp->fmuData->modelData->realParameterData[1].attribute.start = 12.0;
comp->fmuData->modelData->realParameterData[2].attribute.start = 0.5;
comp->fmuData->modelData->realParameterData[3].attribute.start = 1e-005;
comp->fmuData->modelData->realParameterData[4].attribute.start = 1e-005;
comp->fmuData->modelData->realParameterData[5].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[6].attribute.start = 1e-005;
comp->fmuData->modelData->realParameterData[7].attribute.start = 1e-005;
comp->fmuData->modelData->realParameterData[8].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[9].attribute.start = 100.0;
comp->fmuData->modelData->realParameterData[10].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[11].attribute.start = 0.08500000000000001;
comp->fmuData->modelData->realParameterData[12].attribute.start = 0.08500000000000001;
comp->fmuData->modelData->realParameterData[13].attribute.start = 0.036;
comp->fmuData->modelData->realParameterData[14].attribute.start = 4.0;
comp->fmuData->modelData->realParameterData[15].attribute.start = 0.8;
comp->fmuData->modelData->realParameterData[16].attribute.start = 3.2;
comp->fmuData->modelData->realParameterData[17].attribute.start = 0.15;
comp->fmuData->modelData->realParameterData[18].attribute.start = 1.5;
comp->fmuData->modelData->realParameterData[19].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[20].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[21].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[22].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[23].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[24].attribute.start = 100.0;
comp->fmuData->modelData->realParameterData[26].attribute.start = 3.2;
comp->fmuData->modelData->realParameterData[28].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[29].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[30].attribute.start = 0.01;
comp->fmuData->modelData->realParameterData[31].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[32].attribute.start = 0.01;
comp->fmuData->modelData->realParameterData[33].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[34].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[35].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[36].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[38].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[41].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[42].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[44].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[47].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[48].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[49].attribute.start = 0.001;
comp->fmuData->modelData->realParameterData[55].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[56].attribute.start = 0.001;
comp->fmuData->modelData->realParameterData[62].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[63].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[64].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[65].attribute.start = 0.8;
comp->fmuData->modelData->realParameterData[67].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[68].attribute.start = 288.15;
comp->fmuData->modelData->realParameterData[69].attribute.start = 288.15;
comp->fmuData->modelData->realParameterData[71].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[72].attribute.start = 288.15;
comp->fmuData->modelData->realParameterData[73].attribute.start = 288.15;
comp->fmuData->modelData->realParameterData[75].attribute.start = 0.2;
comp->fmuData->modelData->realParameterData[77].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[79].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[82].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[83].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[84].attribute.start = 0.0;
comp->fmuData->modelData->realParameterData[86].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[87].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[88].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[89].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[90].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[91].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[92].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[93].attribute.start = 293.15;
comp->fmuData->modelData->realParameterData[95].attribute.start = 149.2256510455152;
comp->fmuData->modelData->realParameterData[96].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[97].attribute.start = 0.001;
comp->fmuData->modelData->realParameterData[98].attribute.start = 1.0;
comp->fmuData->modelData->realParameterData[102].attribute.start = 1000.0;
comp->fmuData->modelData->realParameterData[103].attribute.start = 12.0;
comp->fmuData->modelData->integerParameterData[1].attribute.start = 1;
comp->fmuData->modelData->integerParameterData[2].attribute.start = 3;
comp->fmuData->modelData->integerParameterData[3].attribute.start = 3;
comp->fmuData->modelData->booleanParameterData[0].attribute.start = 0;
comp->fmuData->modelData->booleanParameterData[1].attribute.start = 0;
comp->fmuData->modelData->booleanParameterData[2].attribute.start = 0;
comp->fmuData->modelData->booleanParameterData[3].attribute.start = 1;
comp->fmuData->modelData->booleanParameterData[4].attribute.start = 1;
comp->fmuData->modelData->booleanParameterData[5].attribute.start = 1;
comp->fmuData->modelData->booleanParameterData[6].attribute.start = 0;
comp->fmuData->modelData->booleanParameterData[7].attribute.start = 0;
comp->fmuData->modelData->booleanParameterData[8].attribute.start = 1;
comp->fmuData->modelData->booleanParameterData[9].attribute.start = 1;
comp->fmuData->modelData->booleanParameterData[10].attribute.start = 1;
comp->fmuData->modelData->booleanParameterData[11].attribute.start = 0;
comp->fmuData->modelData->booleanParameterData[12].attribute.start = 0;
comp->fmuData->modelData->booleanParameterData[13].attribute.start = 0;
comp->fmuData->modelData->booleanParameterData[14].attribute.start = 0;
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
  comp->fmuData->modelData->realVarsData[14].attribute.start =  comp->fmuData->localData[0]->realVars[14];
  comp->fmuData->modelData->realVarsData[15].attribute.start =  comp->fmuData->localData[0]->realVars[15];
  comp->fmuData->modelData->realVarsData[16].attribute.start =  comp->fmuData->localData[0]->realVars[16];
  comp->fmuData->modelData->realVarsData[17].attribute.start =  comp->fmuData->localData[0]->realVars[17];
  comp->fmuData->modelData->realVarsData[18].attribute.start =  comp->fmuData->localData[0]->realVars[18];
  comp->fmuData->modelData->realVarsData[19].attribute.start =  comp->fmuData->localData[0]->realVars[19];
  comp->fmuData->modelData->realVarsData[20].attribute.start =  comp->fmuData->localData[0]->realVars[20];
  comp->fmuData->modelData->realVarsData[21].attribute.start =  comp->fmuData->localData[0]->realVars[21];
  comp->fmuData->modelData->realVarsData[22].attribute.start =  comp->fmuData->localData[0]->realVars[22];
  comp->fmuData->modelData->realVarsData[23].attribute.start =  comp->fmuData->localData[0]->realVars[23];
  comp->fmuData->modelData->realVarsData[24].attribute.start =  comp->fmuData->localData[0]->realVars[24];
  comp->fmuData->modelData->realVarsData[25].attribute.start =  comp->fmuData->localData[0]->realVars[25];
  comp->fmuData->modelData->realVarsData[26].attribute.start =  comp->fmuData->localData[0]->realVars[26];
  comp->fmuData->modelData->realVarsData[27].attribute.start =  comp->fmuData->localData[0]->realVars[27];
  comp->fmuData->modelData->realVarsData[28].attribute.start =  comp->fmuData->localData[0]->realVars[28];
  comp->fmuData->modelData->realVarsData[29].attribute.start =  comp->fmuData->localData[0]->realVars[29];
  comp->fmuData->modelData->realVarsData[30].attribute.start =  comp->fmuData->localData[0]->realVars[30];
  comp->fmuData->modelData->realVarsData[31].attribute.start =  comp->fmuData->localData[0]->realVars[31];
  comp->fmuData->modelData->realVarsData[32].attribute.start =  comp->fmuData->localData[0]->realVars[32];
  comp->fmuData->modelData->realVarsData[33].attribute.start =  comp->fmuData->localData[0]->realVars[33];
  comp->fmuData->modelData->realVarsData[34].attribute.start =  comp->fmuData->localData[0]->realVars[34];
  comp->fmuData->modelData->realVarsData[35].attribute.start =  comp->fmuData->localData[0]->realVars[35];
  comp->fmuData->modelData->realVarsData[36].attribute.start =  comp->fmuData->localData[0]->realVars[36];
  comp->fmuData->modelData->realVarsData[37].attribute.start =  comp->fmuData->localData[0]->realVars[37];
  comp->fmuData->modelData->realVarsData[38].attribute.start =  comp->fmuData->localData[0]->realVars[38];
  comp->fmuData->modelData->realVarsData[39].attribute.start =  comp->fmuData->localData[0]->realVars[39];
  comp->fmuData->modelData->realVarsData[40].attribute.start =  comp->fmuData->localData[0]->realVars[40];
  comp->fmuData->modelData->realVarsData[41].attribute.start =  comp->fmuData->localData[0]->realVars[41];
  comp->fmuData->modelData->realVarsData[42].attribute.start =  comp->fmuData->localData[0]->realVars[42];
  comp->fmuData->modelData->realVarsData[43].attribute.start =  comp->fmuData->localData[0]->realVars[43];
  comp->fmuData->modelData->realVarsData[44].attribute.start =  comp->fmuData->localData[0]->realVars[44];
  comp->fmuData->modelData->realVarsData[45].attribute.start =  comp->fmuData->localData[0]->realVars[45];
  comp->fmuData->modelData->realVarsData[46].attribute.start =  comp->fmuData->localData[0]->realVars[46];
  comp->fmuData->modelData->realVarsData[47].attribute.start =  comp->fmuData->localData[0]->realVars[47];
  comp->fmuData->modelData->realVarsData[48].attribute.start =  comp->fmuData->localData[0]->realVars[48];
  comp->fmuData->modelData->realVarsData[49].attribute.start =  comp->fmuData->localData[0]->realVars[49];
  comp->fmuData->modelData->realVarsData[50].attribute.start =  comp->fmuData->localData[0]->realVars[50];
  comp->fmuData->modelData->realVarsData[51].attribute.start =  comp->fmuData->localData[0]->realVars[51];
  comp->fmuData->modelData->realVarsData[52].attribute.start =  comp->fmuData->localData[0]->realVars[52];
  comp->fmuData->modelData->realVarsData[53].attribute.start =  comp->fmuData->localData[0]->realVars[53];
  comp->fmuData->modelData->realVarsData[54].attribute.start =  comp->fmuData->localData[0]->realVars[54];
  comp->fmuData->modelData->realVarsData[55].attribute.start =  comp->fmuData->localData[0]->realVars[55];
  comp->fmuData->modelData->realVarsData[56].attribute.start =  comp->fmuData->localData[0]->realVars[56];
  comp->fmuData->modelData->realVarsData[57].attribute.start =  comp->fmuData->localData[0]->realVars[57];
  comp->fmuData->modelData->realVarsData[58].attribute.start =  comp->fmuData->localData[0]->realVars[58];
  comp->fmuData->modelData->realVarsData[59].attribute.start =  comp->fmuData->localData[0]->realVars[59];
  comp->fmuData->modelData->realVarsData[60].attribute.start =  comp->fmuData->localData[0]->realVars[60];
  comp->fmuData->modelData->realVarsData[61].attribute.start =  comp->fmuData->localData[0]->realVars[61];
  comp->fmuData->modelData->realVarsData[62].attribute.start =  comp->fmuData->localData[0]->realVars[62];
  comp->fmuData->modelData->realVarsData[63].attribute.start =  comp->fmuData->localData[0]->realVars[63];
  comp->fmuData->modelData->realVarsData[64].attribute.start =  comp->fmuData->localData[0]->realVars[64];
  comp->fmuData->modelData->realVarsData[65].attribute.start =  comp->fmuData->localData[0]->realVars[65];
  comp->fmuData->modelData->realVarsData[66].attribute.start =  comp->fmuData->localData[0]->realVars[66];
  comp->fmuData->modelData->realVarsData[67].attribute.start =  comp->fmuData->localData[0]->realVars[67];
  comp->fmuData->modelData->realVarsData[68].attribute.start =  comp->fmuData->localData[0]->realVars[68];
  comp->fmuData->modelData->realVarsData[69].attribute.start =  comp->fmuData->localData[0]->realVars[69];
  comp->fmuData->modelData->realVarsData[70].attribute.start =  comp->fmuData->localData[0]->realVars[70];
  comp->fmuData->modelData->realVarsData[71].attribute.start =  comp->fmuData->localData[0]->realVars[71];
  comp->fmuData->modelData->realVarsData[72].attribute.start =  comp->fmuData->localData[0]->realVars[72];
  comp->fmuData->modelData->realVarsData[73].attribute.start =  comp->fmuData->localData[0]->realVars[73];
  comp->fmuData->modelData->realVarsData[74].attribute.start =  comp->fmuData->localData[0]->realVars[74];
  comp->fmuData->modelData->realVarsData[75].attribute.start =  comp->fmuData->localData[0]->realVars[75];
  comp->fmuData->modelData->realVarsData[76].attribute.start =  comp->fmuData->localData[0]->realVars[76];
  comp->fmuData->modelData->realVarsData[77].attribute.start =  comp->fmuData->localData[0]->realVars[77];
  comp->fmuData->modelData->realVarsData[78].attribute.start =  comp->fmuData->localData[0]->realVars[78];
  comp->fmuData->modelData->realVarsData[79].attribute.start =  comp->fmuData->localData[0]->realVars[79];
  comp->fmuData->modelData->realVarsData[80].attribute.start =  comp->fmuData->localData[0]->realVars[80];
  comp->fmuData->modelData->realVarsData[81].attribute.start =  comp->fmuData->localData[0]->realVars[81];
  comp->fmuData->modelData->realVarsData[82].attribute.start =  comp->fmuData->localData[0]->realVars[82];
  comp->fmuData->modelData->realVarsData[83].attribute.start =  comp->fmuData->localData[0]->realVars[83];
  comp->fmuData->modelData->realVarsData[84].attribute.start =  comp->fmuData->localData[0]->realVars[84];
  comp->fmuData->modelData->realVarsData[85].attribute.start =  comp->fmuData->localData[0]->realVars[85];
  comp->fmuData->modelData->realVarsData[86].attribute.start =  comp->fmuData->localData[0]->realVars[86];
  comp->fmuData->modelData->realVarsData[87].attribute.start =  comp->fmuData->localData[0]->realVars[87];
  comp->fmuData->modelData->realVarsData[88].attribute.start =  comp->fmuData->localData[0]->realVars[88];
  comp->fmuData->modelData->realVarsData[89].attribute.start =  comp->fmuData->localData[0]->realVars[89];
  comp->fmuData->modelData->realVarsData[90].attribute.start =  comp->fmuData->localData[0]->realVars[90];
  comp->fmuData->modelData->realVarsData[91].attribute.start =  comp->fmuData->localData[0]->realVars[91];
  comp->fmuData->modelData->realVarsData[92].attribute.start =  comp->fmuData->localData[0]->realVars[92];
  comp->fmuData->modelData->realVarsData[93].attribute.start =  comp->fmuData->localData[0]->realVars[93];
  comp->fmuData->modelData->realVarsData[94].attribute.start =  comp->fmuData->localData[0]->realVars[94];
  comp->fmuData->modelData->realVarsData[95].attribute.start =  comp->fmuData->localData[0]->realVars[95];
  comp->fmuData->modelData->realVarsData[96].attribute.start =  comp->fmuData->localData[0]->realVars[96];
  comp->fmuData->modelData->realVarsData[97].attribute.start =  comp->fmuData->localData[0]->realVars[97];
  comp->fmuData->modelData->realVarsData[98].attribute.start =  comp->fmuData->localData[0]->realVars[98];
  comp->fmuData->modelData->realVarsData[99].attribute.start =  comp->fmuData->localData[0]->realVars[99];
  comp->fmuData->modelData->realVarsData[100].attribute.start =  comp->fmuData->localData[0]->realVars[100];
  comp->fmuData->modelData->realVarsData[101].attribute.start =  comp->fmuData->localData[0]->realVars[101];
  comp->fmuData->modelData->realVarsData[102].attribute.start =  comp->fmuData->localData[0]->realVars[102];
  comp->fmuData->modelData->realVarsData[103].attribute.start =  comp->fmuData->localData[0]->realVars[103];
  comp->fmuData->modelData->realVarsData[104].attribute.start =  comp->fmuData->localData[0]->realVars[104];
  comp->fmuData->modelData->realVarsData[105].attribute.start =  comp->fmuData->localData[0]->realVars[105];
  comp->fmuData->modelData->booleanVarsData[0].attribute.start =  comp->fmuData->localData[0]->booleanVars[0];
  comp->fmuData->modelData->booleanVarsData[1].attribute.start =  comp->fmuData->localData[0]->booleanVars[1];
comp->fmuData->modelData->realParameterData[0].attribute.start = comp->fmuData->simulationInfo->realParameter[0];
comp->fmuData->modelData->realParameterData[1].attribute.start = comp->fmuData->simulationInfo->realParameter[1];
comp->fmuData->modelData->realParameterData[2].attribute.start = comp->fmuData->simulationInfo->realParameter[2];
comp->fmuData->modelData->realParameterData[3].attribute.start = comp->fmuData->simulationInfo->realParameter[3];
comp->fmuData->modelData->realParameterData[4].attribute.start = comp->fmuData->simulationInfo->realParameter[4];
comp->fmuData->modelData->realParameterData[5].attribute.start = comp->fmuData->simulationInfo->realParameter[5];
comp->fmuData->modelData->realParameterData[6].attribute.start = comp->fmuData->simulationInfo->realParameter[6];
comp->fmuData->modelData->realParameterData[7].attribute.start = comp->fmuData->simulationInfo->realParameter[7];
comp->fmuData->modelData->realParameterData[8].attribute.start = comp->fmuData->simulationInfo->realParameter[8];
comp->fmuData->modelData->realParameterData[9].attribute.start = comp->fmuData->simulationInfo->realParameter[9];
comp->fmuData->modelData->realParameterData[10].attribute.start = comp->fmuData->simulationInfo->realParameter[10];
comp->fmuData->modelData->realParameterData[11].attribute.start = comp->fmuData->simulationInfo->realParameter[11];
comp->fmuData->modelData->realParameterData[12].attribute.start = comp->fmuData->simulationInfo->realParameter[12];
comp->fmuData->modelData->realParameterData[13].attribute.start = comp->fmuData->simulationInfo->realParameter[13];
comp->fmuData->modelData->realParameterData[14].attribute.start = comp->fmuData->simulationInfo->realParameter[14];
comp->fmuData->modelData->realParameterData[15].attribute.start = comp->fmuData->simulationInfo->realParameter[15];
comp->fmuData->modelData->realParameterData[16].attribute.start = comp->fmuData->simulationInfo->realParameter[16];
comp->fmuData->modelData->realParameterData[17].attribute.start = comp->fmuData->simulationInfo->realParameter[17];
comp->fmuData->modelData->realParameterData[18].attribute.start = comp->fmuData->simulationInfo->realParameter[18];
comp->fmuData->modelData->realParameterData[19].attribute.start = comp->fmuData->simulationInfo->realParameter[19];
comp->fmuData->modelData->realParameterData[20].attribute.start = comp->fmuData->simulationInfo->realParameter[20];
comp->fmuData->modelData->realParameterData[21].attribute.start = comp->fmuData->simulationInfo->realParameter[21];
comp->fmuData->modelData->realParameterData[22].attribute.start = comp->fmuData->simulationInfo->realParameter[22];
comp->fmuData->modelData->realParameterData[23].attribute.start = comp->fmuData->simulationInfo->realParameter[23];
comp->fmuData->modelData->realParameterData[24].attribute.start = comp->fmuData->simulationInfo->realParameter[24];
comp->fmuData->modelData->realParameterData[25].attribute.start = comp->fmuData->simulationInfo->realParameter[25];
comp->fmuData->modelData->realParameterData[26].attribute.start = comp->fmuData->simulationInfo->realParameter[26];
comp->fmuData->modelData->realParameterData[27].attribute.start = comp->fmuData->simulationInfo->realParameter[27];
comp->fmuData->modelData->realParameterData[28].attribute.start = comp->fmuData->simulationInfo->realParameter[28];
comp->fmuData->modelData->realParameterData[29].attribute.start = comp->fmuData->simulationInfo->realParameter[29];
comp->fmuData->modelData->realParameterData[30].attribute.start = comp->fmuData->simulationInfo->realParameter[30];
comp->fmuData->modelData->realParameterData[31].attribute.start = comp->fmuData->simulationInfo->realParameter[31];
comp->fmuData->modelData->realParameterData[32].attribute.start = comp->fmuData->simulationInfo->realParameter[32];
comp->fmuData->modelData->realParameterData[33].attribute.start = comp->fmuData->simulationInfo->realParameter[33];
comp->fmuData->modelData->realParameterData[34].attribute.start = comp->fmuData->simulationInfo->realParameter[34];
comp->fmuData->modelData->realParameterData[35].attribute.start = comp->fmuData->simulationInfo->realParameter[35];
comp->fmuData->modelData->realParameterData[36].attribute.start = comp->fmuData->simulationInfo->realParameter[36];
comp->fmuData->modelData->realParameterData[37].attribute.start = comp->fmuData->simulationInfo->realParameter[37];
comp->fmuData->modelData->realParameterData[38].attribute.start = comp->fmuData->simulationInfo->realParameter[38];
comp->fmuData->modelData->realParameterData[39].attribute.start = comp->fmuData->simulationInfo->realParameter[39];
comp->fmuData->modelData->realParameterData[40].attribute.start = comp->fmuData->simulationInfo->realParameter[40];
comp->fmuData->modelData->realParameterData[41].attribute.start = comp->fmuData->simulationInfo->realParameter[41];
comp->fmuData->modelData->realParameterData[42].attribute.start = comp->fmuData->simulationInfo->realParameter[42];
comp->fmuData->modelData->realParameterData[43].attribute.start = comp->fmuData->simulationInfo->realParameter[43];
comp->fmuData->modelData->realParameterData[44].attribute.start = comp->fmuData->simulationInfo->realParameter[44];
comp->fmuData->modelData->realParameterData[45].attribute.start = comp->fmuData->simulationInfo->realParameter[45];
comp->fmuData->modelData->realParameterData[46].attribute.start = comp->fmuData->simulationInfo->realParameter[46];
comp->fmuData->modelData->realParameterData[47].attribute.start = comp->fmuData->simulationInfo->realParameter[47];
comp->fmuData->modelData->realParameterData[48].attribute.start = comp->fmuData->simulationInfo->realParameter[48];
comp->fmuData->modelData->realParameterData[49].attribute.start = comp->fmuData->simulationInfo->realParameter[49];
comp->fmuData->modelData->realParameterData[50].attribute.start = comp->fmuData->simulationInfo->realParameter[50];
comp->fmuData->modelData->realParameterData[51].attribute.start = comp->fmuData->simulationInfo->realParameter[51];
comp->fmuData->modelData->realParameterData[52].attribute.start = comp->fmuData->simulationInfo->realParameter[52];
comp->fmuData->modelData->realParameterData[53].attribute.start = comp->fmuData->simulationInfo->realParameter[53];
comp->fmuData->modelData->realParameterData[54].attribute.start = comp->fmuData->simulationInfo->realParameter[54];
comp->fmuData->modelData->realParameterData[55].attribute.start = comp->fmuData->simulationInfo->realParameter[55];
comp->fmuData->modelData->realParameterData[56].attribute.start = comp->fmuData->simulationInfo->realParameter[56];
comp->fmuData->modelData->realParameterData[57].attribute.start = comp->fmuData->simulationInfo->realParameter[57];
comp->fmuData->modelData->realParameterData[58].attribute.start = comp->fmuData->simulationInfo->realParameter[58];
comp->fmuData->modelData->realParameterData[59].attribute.start = comp->fmuData->simulationInfo->realParameter[59];
comp->fmuData->modelData->realParameterData[60].attribute.start = comp->fmuData->simulationInfo->realParameter[60];
comp->fmuData->modelData->realParameterData[61].attribute.start = comp->fmuData->simulationInfo->realParameter[61];
comp->fmuData->modelData->realParameterData[62].attribute.start = comp->fmuData->simulationInfo->realParameter[62];
comp->fmuData->modelData->realParameterData[63].attribute.start = comp->fmuData->simulationInfo->realParameter[63];
comp->fmuData->modelData->realParameterData[64].attribute.start = comp->fmuData->simulationInfo->realParameter[64];
comp->fmuData->modelData->realParameterData[65].attribute.start = comp->fmuData->simulationInfo->realParameter[65];
comp->fmuData->modelData->realParameterData[66].attribute.start = comp->fmuData->simulationInfo->realParameter[66];
comp->fmuData->modelData->realParameterData[67].attribute.start = comp->fmuData->simulationInfo->realParameter[67];
comp->fmuData->modelData->realParameterData[68].attribute.start = comp->fmuData->simulationInfo->realParameter[68];
comp->fmuData->modelData->realParameterData[69].attribute.start = comp->fmuData->simulationInfo->realParameter[69];
comp->fmuData->modelData->realParameterData[70].attribute.start = comp->fmuData->simulationInfo->realParameter[70];
comp->fmuData->modelData->realParameterData[71].attribute.start = comp->fmuData->simulationInfo->realParameter[71];
comp->fmuData->modelData->realParameterData[72].attribute.start = comp->fmuData->simulationInfo->realParameter[72];
comp->fmuData->modelData->realParameterData[73].attribute.start = comp->fmuData->simulationInfo->realParameter[73];
comp->fmuData->modelData->realParameterData[74].attribute.start = comp->fmuData->simulationInfo->realParameter[74];
comp->fmuData->modelData->realParameterData[75].attribute.start = comp->fmuData->simulationInfo->realParameter[75];
comp->fmuData->modelData->realParameterData[76].attribute.start = comp->fmuData->simulationInfo->realParameter[76];
comp->fmuData->modelData->realParameterData[77].attribute.start = comp->fmuData->simulationInfo->realParameter[77];
comp->fmuData->modelData->realParameterData[78].attribute.start = comp->fmuData->simulationInfo->realParameter[78];
comp->fmuData->modelData->realParameterData[79].attribute.start = comp->fmuData->simulationInfo->realParameter[79];
comp->fmuData->modelData->realParameterData[80].attribute.start = comp->fmuData->simulationInfo->realParameter[80];
comp->fmuData->modelData->realParameterData[81].attribute.start = comp->fmuData->simulationInfo->realParameter[81];
comp->fmuData->modelData->realParameterData[82].attribute.start = comp->fmuData->simulationInfo->realParameter[82];
comp->fmuData->modelData->realParameterData[83].attribute.start = comp->fmuData->simulationInfo->realParameter[83];
comp->fmuData->modelData->realParameterData[84].attribute.start = comp->fmuData->simulationInfo->realParameter[84];
comp->fmuData->modelData->realParameterData[85].attribute.start = comp->fmuData->simulationInfo->realParameter[85];
comp->fmuData->modelData->realParameterData[86].attribute.start = comp->fmuData->simulationInfo->realParameter[86];
comp->fmuData->modelData->realParameterData[87].attribute.start = comp->fmuData->simulationInfo->realParameter[87];
comp->fmuData->modelData->realParameterData[88].attribute.start = comp->fmuData->simulationInfo->realParameter[88];
comp->fmuData->modelData->realParameterData[89].attribute.start = comp->fmuData->simulationInfo->realParameter[89];
comp->fmuData->modelData->realParameterData[90].attribute.start = comp->fmuData->simulationInfo->realParameter[90];
comp->fmuData->modelData->realParameterData[91].attribute.start = comp->fmuData->simulationInfo->realParameter[91];
comp->fmuData->modelData->realParameterData[92].attribute.start = comp->fmuData->simulationInfo->realParameter[92];
comp->fmuData->modelData->realParameterData[93].attribute.start = comp->fmuData->simulationInfo->realParameter[93];
comp->fmuData->modelData->realParameterData[94].attribute.start = comp->fmuData->simulationInfo->realParameter[94];
comp->fmuData->modelData->realParameterData[95].attribute.start = comp->fmuData->simulationInfo->realParameter[95];
comp->fmuData->modelData->realParameterData[96].attribute.start = comp->fmuData->simulationInfo->realParameter[96];
comp->fmuData->modelData->realParameterData[97].attribute.start = comp->fmuData->simulationInfo->realParameter[97];
comp->fmuData->modelData->realParameterData[98].attribute.start = comp->fmuData->simulationInfo->realParameter[98];
comp->fmuData->modelData->realParameterData[99].attribute.start = comp->fmuData->simulationInfo->realParameter[99];
comp->fmuData->modelData->realParameterData[100].attribute.start = comp->fmuData->simulationInfo->realParameter[100];
comp->fmuData->modelData->realParameterData[101].attribute.start = comp->fmuData->simulationInfo->realParameter[101];
comp->fmuData->modelData->realParameterData[102].attribute.start = comp->fmuData->simulationInfo->realParameter[102];
comp->fmuData->modelData->realParameterData[103].attribute.start = comp->fmuData->simulationInfo->realParameter[103];
comp->fmuData->modelData->integerParameterData[0].attribute.start = comp->fmuData->simulationInfo->integerParameter[0];
comp->fmuData->modelData->integerParameterData[1].attribute.start = comp->fmuData->simulationInfo->integerParameter[1];
comp->fmuData->modelData->integerParameterData[2].attribute.start = comp->fmuData->simulationInfo->integerParameter[2];
comp->fmuData->modelData->integerParameterData[3].attribute.start = comp->fmuData->simulationInfo->integerParameter[3];
comp->fmuData->modelData->booleanParameterData[0].attribute.start = comp->fmuData->simulationInfo->booleanParameter[0];
comp->fmuData->modelData->booleanParameterData[1].attribute.start = comp->fmuData->simulationInfo->booleanParameter[1];
comp->fmuData->modelData->booleanParameterData[2].attribute.start = comp->fmuData->simulationInfo->booleanParameter[2];
comp->fmuData->modelData->booleanParameterData[3].attribute.start = comp->fmuData->simulationInfo->booleanParameter[3];
comp->fmuData->modelData->booleanParameterData[4].attribute.start = comp->fmuData->simulationInfo->booleanParameter[4];
comp->fmuData->modelData->booleanParameterData[5].attribute.start = comp->fmuData->simulationInfo->booleanParameter[5];
comp->fmuData->modelData->booleanParameterData[6].attribute.start = comp->fmuData->simulationInfo->booleanParameter[6];
comp->fmuData->modelData->booleanParameterData[7].attribute.start = comp->fmuData->simulationInfo->booleanParameter[7];
comp->fmuData->modelData->booleanParameterData[8].attribute.start = comp->fmuData->simulationInfo->booleanParameter[8];
comp->fmuData->modelData->booleanParameterData[9].attribute.start = comp->fmuData->simulationInfo->booleanParameter[9];
comp->fmuData->modelData->booleanParameterData[10].attribute.start = comp->fmuData->simulationInfo->booleanParameter[10];
comp->fmuData->modelData->booleanParameterData[11].attribute.start = comp->fmuData->simulationInfo->booleanParameter[11];
comp->fmuData->modelData->booleanParameterData[12].attribute.start = comp->fmuData->simulationInfo->booleanParameter[12];
comp->fmuData->modelData->booleanParameterData[13].attribute.start = comp->fmuData->simulationInfo->booleanParameter[13];
comp->fmuData->modelData->booleanParameterData[14].attribute.start = comp->fmuData->simulationInfo->booleanParameter[14];
}
  // Used to set the next time event, if any.
  void eventUpdate(ModelInstance* comp, fmi2EventInfo* eventInfo) {
  }
  
  fmi2Real getReal(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        case $Pmotor$PairGapDC$Ppsi_e_vr : return comp->fmuData->localData[0]->realVars[0]; break;
        case $Pmotor$PinertiaRotor$Pw_vr : return comp->fmuData->localData[0]->realVars[1]; break;
        case $Pmotor$Pla$Pi_vr : return comp->fmuData->localData[0]->realVars[2]; break;
        case $Pmotor$PphiMechanical_vr : return comp->fmuData->localData[0]->realVars[3]; break;
        case $P$DER$Pmotor$PairGapDC$Ppsi_e_vr : return comp->fmuData->localData[0]->realVars[4]; break;
        case $P$DER$Pmotor$PinertiaRotor$Pw_vr : return comp->fmuData->localData[0]->realVars[5]; break;
        case $P$DER$Pmotor$Pla$Pi_vr : return comp->fmuData->localData[0]->realVars[6]; break;
        case $P$DER$Pmotor$PphiMechanical_vr : return comp->fmuData->localData[0]->realVars[7]; break;
        case $P$DER$Pmotor$Pfriction$Pphi_vr : return comp->fmuData->localData[0]->realVars[8]; break;
        case $P$DER$Pmotor$Plesigma$Pi_vr : return comp->fmuData->localData[0]->realVars[9]; break;
        case $P$DER$Pmotor$PstrayLoad$Pphi_vr : return comp->fmuData->localData[0]->realVars[10]; break;
        case $P$DER$PspeedSensor1$Pflange$Pphi_vr : return comp->fmuData->localData[0]->realVars[11]; break;
        case $Parm_current_vr : return comp->fmuData->localData[0]->realVars[12]; break;
        case $Parm_sensor$Pp$Pv_vr : return comp->fmuData->localData[0]->realVars[13]; break;
        case $Pdown_input_vr : return comp->fmuData->localData[0]->realVars[14]; break;
        case $PidealCommutingSwitch1$PLossPower_vr : return comp->fmuData->localData[0]->realVars[15]; break;
        case $PidealCommutingSwitch1$Pn1$Pi_vr : return comp->fmuData->localData[0]->realVars[16]; break;
        case $PidealCommutingSwitch1$Pn2$Pi_vr : return comp->fmuData->localData[0]->realVars[17]; break;
        case $PidealCommutingSwitch1$Ps1_vr : return comp->fmuData->localData[0]->realVars[18]; break;
        case $PidealCommutingSwitch1$Ps2_vr : return comp->fmuData->localData[0]->realVars[19]; break;
        case $PidealCommutingSwitch2$PLossPower_vr : return comp->fmuData->localData[0]->realVars[20]; break;
        case $PidealCommutingSwitch2$Pn1$Pi_vr : return comp->fmuData->localData[0]->realVars[21]; break;
        case $PidealCommutingSwitch2$Pn2$Pi_vr : return comp->fmuData->localData[0]->realVars[22]; break;
        case $PidealCommutingSwitch2$Pp$Pv_vr : return comp->fmuData->localData[0]->realVars[23]; break;
        case $PidealCommutingSwitch2$Ps1_vr : return comp->fmuData->localData[0]->realVars[24]; break;
        case $PidealCommutingSwitch2$Ps2_vr : return comp->fmuData->localData[0]->realVars[25]; break;
        case $Pinput_torque_vr : return comp->fmuData->localData[0]->realVars[26]; break;
        case $Pmotor$PairGapDC$Ppin_ap$Pv_vr : return comp->fmuData->localData[0]->realVars[27]; break;
        case $Pmotor$PairGapDC$Pvai_vr : return comp->fmuData->localData[0]->realVars[28]; break;
        case $Pmotor$PairGapDC$Pvei_vr : return comp->fmuData->localData[0]->realVars[29]; break;
        case $Pmotor$Pbrush$PheatPort$PQ_flow_vr : return comp->fmuData->localData[0]->realVars[30]; break;
        case $Pmotor$Pbrush$PlossPower_vr : return comp->fmuData->localData[0]->realVars[31]; break;
        case $Pmotor$Pbrush$Pv_vr : return comp->fmuData->localData[0]->realVars[32]; break;
        case $Pmotor$PcompoundDCExcitation$Ppin_sen$Pi_vr : return comp->fmuData->localData[0]->realVars[33]; break;
        case $Pmotor$PcompoundDCExcitation$Ppin_sep$Pi_vr : return comp->fmuData->localData[0]->realVars[34]; break;
        case $Pmotor$PcompoundDCExcitation$Pvse_vr : return comp->fmuData->localData[0]->realVars[35]; break;
        case $Pmotor$Pcore$PGc_vr : return comp->fmuData->localData[0]->realVars[36]; break;
        case $Pmotor$Pcore$PheatPort$PQ_flow_vr : return comp->fmuData->localData[0]->realVars[37]; break;
        case $Pmotor$Pcore$Pi_vr : return comp->fmuData->localData[0]->realVars[38]; break;
        case $Pmotor$Pcore$PlossPower_vr : return comp->fmuData->localData[0]->realVars[39]; break;
        case $Pmotor$Pcore$Pn$Pi_vr : return comp->fmuData->localData[0]->realVars[40]; break;
        case $Pmotor$Pcore$Pp$Pv_vr : return comp->fmuData->localData[0]->realVars[41]; break;
        case $Pmotor$Pcore$Pv_vr : return comp->fmuData->localData[0]->realVars[42]; break;
        case $Pmotor$Pcore$PwLimit_vr : return comp->fmuData->localData[0]->realVars[43]; break;
        case $Pmotor$Pfixed$Pflange$Ptau_vr : return comp->fmuData->localData[0]->realVars[44]; break;
        case $Pmotor$Pfriction$Pphi_vr : return comp->fmuData->localData[0]->realVars[45]; break;
        case $Pmotor$Pfriction$Ptau_vr : return comp->fmuData->localData[0]->realVars[46]; break;
        case $Pmotor$Pfriction$Pw_vr : return comp->fmuData->localData[0]->realVars[47]; break;
        case $Pmotor$Pground$Pp$Pi_vr : return comp->fmuData->localData[0]->realVars[48]; break;
        case $Pmotor$Pground$Pp$Pv_vr : return comp->fmuData->localData[0]->realVars[49]; break;
        case $Pmotor$PgroundSE$Pp$Pv_vr : return comp->fmuData->localData[0]->realVars[50]; break;
        case $Pmotor$PinertiaRotor$Pa_vr : return comp->fmuData->localData[0]->realVars[51]; break;
        case $Pmotor$PinertiaRotor$Pflange_b$Ptau_vr : return comp->fmuData->localData[0]->realVars[52]; break;
        case $Pmotor$PinertiaStator$Pa_vr : return comp->fmuData->localData[0]->realVars[53]; break;
        case $Pmotor$PinertiaStator$Pflange_a$Ptau_vr : return comp->fmuData->localData[0]->realVars[54]; break;
        case $Pmotor$PinertiaStator$Pflange_b$Ptau_vr : return comp->fmuData->localData[0]->realVars[55]; break;
        case $Pmotor$PinertiaStator$Pw_vr : return comp->fmuData->localData[0]->realVars[56]; break;
        case $Pmotor$PinternalSupport$Ptau_vr : return comp->fmuData->localData[0]->realVars[57]; break;
        case $Pmotor$PinternalThermalPort$PheatPortArmature$PQ_flow_vr : return comp->fmuData->localData[0]->realVars[58]; break;
        case $Pmotor$PinternalThermalPort$PheatPortBrush$PQ_flow_vr : return comp->fmuData->localData[0]->realVars[59]; break;
        case $Pmotor$PinternalThermalPort$PheatPortCore$PQ_flow_vr : return comp->fmuData->localData[0]->realVars[60]; break;
        case $Pmotor$PinternalThermalPort$PheatPortExcitation$PQ_flow_vr : return comp->fmuData->localData[0]->realVars[61]; break;
        case $Pmotor$PinternalThermalPort$PheatPortFriction$PQ_flow_vr : return comp->fmuData->localData[0]->realVars[62]; break;
        case $Pmotor$PinternalThermalPort$PheatPortStrayLoad$PQ_flow_vr : return comp->fmuData->localData[0]->realVars[63]; break;
        case $Pmotor$Pla$Pv_vr : return comp->fmuData->localData[0]->realVars[64]; break;
        case $Pmotor$Plesigma$Pi_vr : return comp->fmuData->localData[0]->realVars[65]; break;
        case $Pmotor$Plesigma$Pp$Pv_vr : return comp->fmuData->localData[0]->realVars[66]; break;
        case $Pmotor$Plesigma$Pv_vr : return comp->fmuData->localData[0]->realVars[67]; break;
        case $Pmotor$PpowerBalance$PlossPowerTotal_vr : return comp->fmuData->localData[0]->realVars[68]; break;
        case $Pmotor$PpowerBalance$PpowerArmature_vr : return comp->fmuData->localData[0]->realVars[69]; break;
        case $Pmotor$PpowerBalance$PpowerExcitation_vr : return comp->fmuData->localData[0]->realVars[70]; break;
        case $Pmotor$PpowerBalance$PpowerInertiaRotor_vr : return comp->fmuData->localData[0]->realVars[71]; break;
        case $Pmotor$PpowerBalance$PpowerInertiaStator_vr : return comp->fmuData->localData[0]->realVars[72]; break;
        case $Pmotor$PpowerBalance$PpowerMechanical_vr : return comp->fmuData->localData[0]->realVars[73]; break;
        case $Pmotor$Pra$PR_actual_vr : return comp->fmuData->localData[0]->realVars[74]; break;
        case $Pmotor$Pra$Pv_vr : return comp->fmuData->localData[0]->realVars[75]; break;
        case $Pmotor$Pre$PR_actual_vr : return comp->fmuData->localData[0]->realVars[76]; break;
        case $Pmotor$Pre$Pv_vr : return comp->fmuData->localData[0]->realVars[77]; break;
        case $Pmotor$PstrayLoad$Pflange$Ptau_vr : return comp->fmuData->localData[0]->realVars[78]; break;
        case $Pmotor$PstrayLoad$PheatPort$PQ_flow_vr : return comp->fmuData->localData[0]->realVars[79]; break;
        case $Pmotor$PstrayLoad$PlossPower_vr : return comp->fmuData->localData[0]->realVars[80]; break;
        case $Pmotor$PstrayLoad$Pphi_vr : return comp->fmuData->localData[0]->realVars[81]; break;
        case $Pmotor$PstrayLoad$Ptau_vr : return comp->fmuData->localData[0]->realVars[82]; break;
        case $Pmotor$PstrayLoad$Pv_vr : return comp->fmuData->localData[0]->realVars[83]; break;
        case $Pmotor$PstrayLoad$Pw_vr : return comp->fmuData->localData[0]->realVars[84]; break;
        case $Pmotor$PtauElectrical_vr : return comp->fmuData->localData[0]->realVars[85]; break;
        case $Pmotor$PthermalAmbient$PQ_flowArmature_vr : return comp->fmuData->localData[0]->realVars[86]; break;
        case $Pmotor$PthermalAmbient$PQ_flowExcitation_vr : return comp->fmuData->localData[0]->realVars[87]; break;
        case $Pmotor$PthermalAmbient$PQ_flowFriction_vr : return comp->fmuData->localData[0]->realVars[88]; break;
        case $Pmotor$PthermalAmbient$PQ_flowTotal_vr : return comp->fmuData->localData[0]->realVars[89]; break;
        case $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PT_vr : return comp->fmuData->localData[0]->realVars[90]; break;
        case $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PT_vr : return comp->fmuData->localData[0]->realVars[91]; break;
        case $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PT_vr : return comp->fmuData->localData[0]->realVars[92]; break;
        case $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PT_vr : return comp->fmuData->localData[0]->realVars[93]; break;
        case $Pmotor$Pva_vr : return comp->fmuData->localData[0]->realVars[94]; break;
        case $Pmotor$PwMechanical_vr : return comp->fmuData->localData[0]->realVars[95]; break;
        case $Pspeed_vr : return comp->fmuData->localData[0]->realVars[96]; break;
        case $PspeedSensor1$Pflange$Pphi_vr : return comp->fmuData->localData[0]->realVars[97]; break;
        case $PspeedSensor1$Pflange$Ptau_vr : return comp->fmuData->localData[0]->realVars[98]; break;
        case $Ptorque1$Pphi_support_vr : return comp->fmuData->localData[0]->realVars[99]; break;
        case $Pup_ground$Pp$Pi_vr : return comp->fmuData->localData[0]->realVars[100]; break;
        case $Pup_ground$Pp$Pv_vr : return comp->fmuData->localData[0]->realVars[101]; break;
        case $Pup_input_vr : return comp->fmuData->localData[0]->realVars[102]; break;
        case $Pup_voltage$Pi_vr : return comp->fmuData->localData[0]->realVars[103]; break;
        case $Pvoltage_ground$Pp$Pi_vr : return comp->fmuData->localData[0]->realVars[104]; break;
        case $Pvoltage_ground$Pp$Pv_vr : return comp->fmuData->localData[0]->realVars[105]; break;
        case $PconvertToBoolean$Pthreshold_vr : return comp->fmuData->simulationInfo->realParameter[0]; break;
        case $Pdc_motor_power$PV_vr : return comp->fmuData->simulationInfo->realParameter[1]; break;
        case $PgreaterThreshold1$Pthreshold_vr : return comp->fmuData->simulationInfo->realParameter[2]; break;
        case $PidealCommutingSwitch1$PGoff_vr : return comp->fmuData->simulationInfo->realParameter[3]; break;
        case $PidealCommutingSwitch1$PRon_vr : return comp->fmuData->simulationInfo->realParameter[4]; break;
        case $PidealCommutingSwitch1$PT_vr : return comp->fmuData->simulationInfo->realParameter[5]; break;
        case $PidealCommutingSwitch2$PGoff_vr : return comp->fmuData->simulationInfo->realParameter[6]; break;
        case $PidealCommutingSwitch2$PRon_vr : return comp->fmuData->simulationInfo->realParameter[7]; break;
        case $PidealCommutingSwitch2$PT_vr : return comp->fmuData->simulationInfo->realParameter[8]; break;
        case $Pmotor$PIaNominal_vr : return comp->fmuData->simulationInfo->realParameter[9]; break;
        case $Pmotor$PIeNominal_vr : return comp->fmuData->simulationInfo->realParameter[10]; break;
        case $Pmotor$PJr_vr : return comp->fmuData->simulationInfo->realParameter[11]; break;
        case $Pmotor$PJs_vr : return comp->fmuData->simulationInfo->realParameter[12]; break;
        case $Pmotor$PLa_vr : return comp->fmuData->simulationInfo->realParameter[13]; break;
        case $Pmotor$PLe_vr : return comp->fmuData->simulationInfo->realParameter[14]; break;
        case $Pmotor$PLesigma_vr : return comp->fmuData->simulationInfo->realParameter[15]; break;
        case $Pmotor$PLme_vr : return comp->fmuData->simulationInfo->realParameter[16]; break;
        case $Pmotor$PRa_vr : return comp->fmuData->simulationInfo->realParameter[17]; break;
        case $Pmotor$PRe_vr : return comp->fmuData->simulationInfo->realParameter[18]; break;
        case $Pmotor$PTaNominal_vr : return comp->fmuData->simulationInfo->realParameter[19]; break;
        case $Pmotor$PTaOperational_vr : return comp->fmuData->simulationInfo->realParameter[20]; break;
        case $Pmotor$PTaRef_vr : return comp->fmuData->simulationInfo->realParameter[21]; break;
        case $Pmotor$PTeOperational_vr : return comp->fmuData->simulationInfo->realParameter[22]; break;
        case $Pmotor$PTeRef_vr : return comp->fmuData->simulationInfo->realParameter[23]; break;
        case $Pmotor$PVaNominal_vr : return comp->fmuData->simulationInfo->realParameter[24]; break;
        case $Pmotor$PViNominal_vr : return comp->fmuData->simulationInfo->realParameter[25]; break;
        case $Pmotor$PairGapDC$PLe_vr : return comp->fmuData->simulationInfo->realParameter[26]; break;
        case $Pmotor$PairGapDC$PturnsRatio_vr : return comp->fmuData->simulationInfo->realParameter[27]; break;
        case $Pmotor$Palpha20a_vr : return comp->fmuData->simulationInfo->realParameter[28]; break;
        case $Pmotor$Palpha20e_vr : return comp->fmuData->simulationInfo->realParameter[29]; break;
        case $Pmotor$Pbrush$PbrushParameters$PILinear_vr : return comp->fmuData->simulationInfo->realParameter[30]; break;
        case $Pmotor$Pbrush$PbrushParameters$PV_vr : return comp->fmuData->simulationInfo->realParameter[31]; break;
        case $Pmotor$PbrushParameters$PILinear_vr : return comp->fmuData->simulationInfo->realParameter[32]; break;
        case $Pmotor$PbrushParameters$PV_vr : return comp->fmuData->simulationInfo->realParameter[33]; break;
        case $Pmotor$PcompoundDCExcitation$PexcitationTurnsRatio_vr : return comp->fmuData->simulationInfo->realParameter[34]; break;
        case $Pmotor$Pcore$PcoreParameters$PGcRef_vr : return comp->fmuData->simulationInfo->realParameter[35]; break;
        case $Pmotor$Pcore$PcoreParameters$PPRef_vr : return comp->fmuData->simulationInfo->realParameter[36]; break;
        case $Pmotor$Pcore$PcoreParameters$PVRef_vr : return comp->fmuData->simulationInfo->realParameter[37]; break;
        case $Pmotor$Pcore$PcoreParameters$PratioHysteresis_vr : return comp->fmuData->simulationInfo->realParameter[38]; break;
        case $Pmotor$Pcore$PcoreParameters$PwMin_vr : return comp->fmuData->simulationInfo->realParameter[39]; break;
        case $Pmotor$Pcore$PcoreParameters$PwRef_vr : return comp->fmuData->simulationInfo->realParameter[40]; break;
        case $Pmotor$PcoreParameters$PGcRef_vr : return comp->fmuData->simulationInfo->realParameter[41]; break;
        case $Pmotor$PcoreParameters$PPRef_vr : return comp->fmuData->simulationInfo->realParameter[42]; break;
        case $Pmotor$PcoreParameters$PVRef_vr : return comp->fmuData->simulationInfo->realParameter[43]; break;
        case $Pmotor$PcoreParameters$PratioHysteresis_vr : return comp->fmuData->simulationInfo->realParameter[44]; break;
        case $Pmotor$PcoreParameters$PwMin_vr : return comp->fmuData->simulationInfo->realParameter[45]; break;
        case $Pmotor$PcoreParameters$PwRef_vr : return comp->fmuData->simulationInfo->realParameter[46]; break;
        case $Pmotor$Pfixed$Pphi0_vr : return comp->fmuData->simulationInfo->realParameter[47]; break;
        case $Pmotor$Pfriction$PfrictionParameters$PPRef_vr : return comp->fmuData->simulationInfo->realParameter[48]; break;
        case $Pmotor$Pfriction$PfrictionParameters$Plinear_vr : return comp->fmuData->simulationInfo->realParameter[49]; break;
        case $Pmotor$Pfriction$PfrictionParameters$Ppower_w_vr : return comp->fmuData->simulationInfo->realParameter[50]; break;
        case $Pmotor$Pfriction$PfrictionParameters$PtauLinear_vr : return comp->fmuData->simulationInfo->realParameter[51]; break;
        case $Pmotor$Pfriction$PfrictionParameters$PtauRef_vr : return comp->fmuData->simulationInfo->realParameter[52]; break;
        case $Pmotor$Pfriction$PfrictionParameters$PwLinear_vr : return comp->fmuData->simulationInfo->realParameter[53]; break;
        case $Pmotor$Pfriction$PfrictionParameters$PwRef_vr : return comp->fmuData->simulationInfo->realParameter[54]; break;
        case $Pmotor$PfrictionParameters$PPRef_vr : return comp->fmuData->simulationInfo->realParameter[55]; break;
        case $Pmotor$PfrictionParameters$Plinear_vr : return comp->fmuData->simulationInfo->realParameter[56]; break;
        case $Pmotor$PfrictionParameters$Ppower_w_vr : return comp->fmuData->simulationInfo->realParameter[57]; break;
        case $Pmotor$PfrictionParameters$PtauLinear_vr : return comp->fmuData->simulationInfo->realParameter[58]; break;
        case $Pmotor$PfrictionParameters$PtauRef_vr : return comp->fmuData->simulationInfo->realParameter[59]; break;
        case $Pmotor$PfrictionParameters$PwLinear_vr : return comp->fmuData->simulationInfo->realParameter[60]; break;
        case $Pmotor$PfrictionParameters$PwRef_vr : return comp->fmuData->simulationInfo->realParameter[61]; break;
        case $Pmotor$PinertiaRotor$PJ_vr : return comp->fmuData->simulationInfo->realParameter[62]; break;
        case $Pmotor$PinertiaStator$PJ_vr : return comp->fmuData->simulationInfo->realParameter[63]; break;
        case $Pmotor$Pla$PL_vr : return comp->fmuData->simulationInfo->realParameter[64]; break;
        case $Pmotor$Plesigma$PL_vr : return comp->fmuData->simulationInfo->realParameter[65]; break;
        case $Pmotor$Ppsi_eNominal_vr : return comp->fmuData->simulationInfo->realParameter[66]; break;
        case $Pmotor$Pra$PR_vr : return comp->fmuData->simulationInfo->realParameter[67]; break;
        case $Pmotor$Pra$PT_vr : return comp->fmuData->simulationInfo->realParameter[68]; break;
        case $Pmotor$Pra$PT_ref_vr : return comp->fmuData->simulationInfo->realParameter[69]; break;
        case $Pmotor$Pra$Palpha_vr : return comp->fmuData->simulationInfo->realParameter[70]; break;
        case $Pmotor$Pre$PR_vr : return comp->fmuData->simulationInfo->realParameter[71]; break;
        case $Pmotor$Pre$PT_vr : return comp->fmuData->simulationInfo->realParameter[72]; break;
        case $Pmotor$Pre$PT_ref_vr : return comp->fmuData->simulationInfo->realParameter[73]; break;
        case $Pmotor$Pre$Palpha_vr : return comp->fmuData->simulationInfo->realParameter[74]; break;
        case $Pmotor$Psigmae_vr : return comp->fmuData->simulationInfo->realParameter[75]; break;
        case $Pmotor$PstrayLoad$PstrayLoadParameters$PIRef_vr : return comp->fmuData->simulationInfo->realParameter[76]; break;
        case $Pmotor$PstrayLoad$PstrayLoadParameters$PPRef_vr : return comp->fmuData->simulationInfo->realParameter[77]; break;
        case $Pmotor$PstrayLoad$PstrayLoadParameters$Ppower_w_vr : return comp->fmuData->simulationInfo->realParameter[78]; break;
        case $Pmotor$PstrayLoad$PstrayLoadParameters$PtauRef_vr : return comp->fmuData->simulationInfo->realParameter[79]; break;
        case $Pmotor$PstrayLoad$PstrayLoadParameters$PwRef_vr : return comp->fmuData->simulationInfo->realParameter[80]; break;
        case $Pmotor$PstrayLoadParameters$PIRef_vr : return comp->fmuData->simulationInfo->realParameter[81]; break;
        case $Pmotor$PstrayLoadParameters$PPRef_vr : return comp->fmuData->simulationInfo->realParameter[82]; break;
        case $Pmotor$PstrayLoadParameters$Ppower_w_vr : return comp->fmuData->simulationInfo->realParameter[83]; break;
        case $Pmotor$PstrayLoadParameters$PtauRef_vr : return comp->fmuData->simulationInfo->realParameter[84]; break;
        case $Pmotor$PstrayLoadParameters$PwRef_vr : return comp->fmuData->simulationInfo->realParameter[85]; break;
        case $Pmotor$PthermalAmbient$PTa_vr : return comp->fmuData->simulationInfo->realParameter[86]; break;
        case $Pmotor$PthermalAmbient$PTe_vr : return comp->fmuData->simulationInfo->realParameter[87]; break;
        case $Pmotor$PthermalAmbient$PconstTa$Pk_vr : return comp->fmuData->simulationInfo->realParameter[88]; break;
        case $Pmotor$PthermalAmbient$PconstTe$Pk_vr : return comp->fmuData->simulationInfo->realParameter[89]; break;
        case $Pmotor$PthermalAmbient$PtemperatureBrush$PT_vr : return comp->fmuData->simulationInfo->realParameter[90]; break;
        case $Pmotor$PthermalAmbient$PtemperatureCore$PT_vr : return comp->fmuData->simulationInfo->realParameter[91]; break;
        case $Pmotor$PthermalAmbient$PtemperatureFriction$PT_vr : return comp->fmuData->simulationInfo->realParameter[92]; break;
        case $Pmotor$PthermalAmbient$PtemperatureStrayLoad$PT_vr : return comp->fmuData->simulationInfo->realParameter[93]; break;
        case $Pmotor$PturnsRatio_vr : return comp->fmuData->simulationInfo->realParameter[94]; break;
        case $Pmotor$PwNominal_vr : return comp->fmuData->simulationInfo->realParameter[95]; break;
        case $Pmotor_frictionParameters$PPRef_vr : return comp->fmuData->simulationInfo->realParameter[96]; break;
        case $Pmotor_frictionParameters$Plinear_vr : return comp->fmuData->simulationInfo->realParameter[97]; break;
        case $Pmotor_frictionParameters$Ppower_w_vr : return comp->fmuData->simulationInfo->realParameter[98]; break;
        case $Pmotor_frictionParameters$PtauLinear_vr : return comp->fmuData->simulationInfo->realParameter[99]; break;
        case $Pmotor_frictionParameters$PtauRef_vr : return comp->fmuData->simulationInfo->realParameter[100]; break;
        case $Pmotor_frictionParameters$PwLinear_vr : return comp->fmuData->simulationInfo->realParameter[101]; break;
        case $Pmotor_frictionParameters$PwRef_vr : return comp->fmuData->simulationInfo->realParameter[102]; break;
        case $Pup_voltage$PV_vr : return comp->fmuData->simulationInfo->realParameter[103]; break;
        case $Parm_sensor$Pi_vr : return getReal(comp, $Parm_current_vr); break;
        case $Parm_sensor$Pn$Pi_vr : return (- getReal(comp, $Parm_current_vr)); break;
        case $Parm_sensor$Pn$Pv_vr : return getReal(comp, $Parm_sensor$Pp$Pv_vr); break;
        case $Parm_sensor$Pp$Pi_vr : return getReal(comp, $Parm_current_vr); break;
        case $PconvertToBoolean$Pu_vr : return getReal(comp, $Pup_input_vr); break;
        case $Pdc_motor_power$Pi_vr : return (- getReal(comp, $Pmotor$Plesigma$Pi_vr)); break;
        case $Pdc_motor_power$Pn$Pi_vr : return getReal(comp, $Pmotor$Plesigma$Pi_vr); break;
        case $Pdc_motor_power$Pn$Pv_vr : return getReal(comp, $Pvoltage_ground$Pp$Pv_vr); break;
        case $Pdc_motor_power$Pp$Pi_vr : return (- getReal(comp, $Pmotor$Plesigma$Pi_vr)); break;
        case $Pdc_motor_power$Pp$Pv_vr : return getReal(comp, $Pdc_motor_power$PV_vr); break;
        case $Pdc_motor_power$Pv_vr : return getReal(comp, $Pdc_motor_power$PV_vr); break;
        case $PgreaterThreshold1$Pu_vr : return getReal(comp, $Pdown_input_vr); break;
        case $PidealCommutingSwitch1$PT_heatPort_vr : return getReal(comp, $PidealCommutingSwitch1$PT_vr); break;
        case $PidealCommutingSwitch1$Pn1$Pv_vr : return getReal(comp, $Pup_voltage$PV_vr); break;
        case $PidealCommutingSwitch1$Pn2$Pv_vr : return getReal(comp, $Pup_ground$Pp$Pv_vr); break;
        case $PidealCommutingSwitch1$Pp$Pi_vr : return getReal(comp, $Parm_current_vr); break;
        case $PidealCommutingSwitch1$Pp$Pv_vr : return getReal(comp, $Parm_sensor$Pp$Pv_vr); break;
        case $PidealCommutingSwitch2$PT_heatPort_vr : return getReal(comp, $PidealCommutingSwitch2$PT_vr); break;
        case $PidealCommutingSwitch2$Pn1$Pv_vr : return getReal(comp, $Pup_voltage$PV_vr); break;
        case $PidealCommutingSwitch2$Pn2$Pv_vr : return getReal(comp, $Pup_ground$Pp$Pv_vr); break;
        case $PidealCommutingSwitch2$Pp$Pi_vr : return getReal(comp, $Pmotor$Pla$Pi_vr); break;
        case $Pmotor$PairGapDC$Pflange$Pphi_vr : return getReal(comp, $PspeedSensor1$Pflange$Pphi_vr); break;
        case $Pmotor$PairGapDC$Pflange$Ptau_vr : return (- getReal(comp, $Pmotor$PtauElectrical_vr)); break;
        case $Pmotor$PairGapDC$Pia_vr : return getReal(comp, $Pmotor$Pla$Pi_vr); break;
        case $Pmotor$PairGapDC$Pie_vr : return getReal(comp, $Pmotor$Plesigma$Pi_vr); break;
        case $Pmotor$PairGapDC$Ppin_an$Pi_vr : return (- getReal(comp, $Pmotor$Pla$Pi_vr)); break;
        case $Pmotor$PairGapDC$Ppin_an$Pv_vr : return getReal(comp, $PidealCommutingSwitch2$Pp$Pv_vr); break;
        case $Pmotor$PairGapDC$Ppin_ap$Pi_vr : return getReal(comp, $Pmotor$Pla$Pi_vr); break;
        case $Pmotor$PairGapDC$Ppin_en$Pi_vr : return (- getReal(comp, $Pmotor$Plesigma$Pi_vr)); break;
        case $Pmotor$PairGapDC$Ppin_en$Pv_vr : return getReal(comp, $Pmotor$Pground$Pp$Pv_vr); break;
        case $Pmotor$PairGapDC$Ppin_ep$Pi_vr : return getReal(comp, $Pmotor$Plesigma$Pi_vr); break;
        case $Pmotor$PairGapDC$Ppin_ep$Pv_vr : return getReal(comp, $Pmotor$PairGapDC$Pvei_vr); break;
        case $Pmotor$PairGapDC$Psupport$Pphi_vr : return getReal(comp, $Pmotor$Pfixed$Pphi0_vr); break;
        case $Pmotor$PairGapDC$Psupport$Ptau_vr : return getReal(comp, $Pmotor$PtauElectrical_vr); break;
        case $Pmotor$PairGapDC$PtauElectrical_vr : return getReal(comp, $Pmotor$PtauElectrical_vr); break;
        case $Pmotor$PairGapDC$Pw_vr : return getReal(comp, $Pmotor$PinertiaRotor$Pw_vr); break;
        case $Pmotor$Pbrush$PheatPort$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PT_vr); break;
        case $Pmotor$Pbrush$Pi_vr : return getReal(comp, $Pmotor$Pla$Pi_vr); break;
        case $Pmotor$Pbrush$Pn$Pi_vr : return (- getReal(comp, $Pmotor$Pla$Pi_vr)); break;
        case $Pmotor$Pbrush$Pn$Pv_vr : return getReal(comp, $PidealCommutingSwitch2$Pp$Pv_vr); break;
        case $Pmotor$Pbrush$Pp$Pi_vr : return getReal(comp, $Pmotor$Pla$Pi_vr); break;
        case $Pmotor$Pbrush$Pp$Pv_vr : return getReal(comp, $PidealCommutingSwitch2$Pp$Pv_vr); break;
        case $Pmotor$PcompoundDCExcitation$Pi_vr : return (- getReal(comp, $Pmotor$Plesigma$Pi_vr)); break;
        case $Pmotor$PcompoundDCExcitation$Pie_vr : return getReal(comp, $Pmotor$Plesigma$Pi_vr); break;
        case $Pmotor$PcompoundDCExcitation$Pise_vr : return getReal(comp, $Pmotor$PcompoundDCExcitation$Ppin_sep$Pi_vr); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_en$Pi_vr : return (- getReal(comp, $Pmotor$Plesigma$Pi_vr)); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_en$Pv_vr : return getReal(comp, $Pvoltage_ground$Pp$Pv_vr); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_ep$Pi_vr : return getReal(comp, $Pmotor$Plesigma$Pi_vr); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_ep$Pv_vr : return getReal(comp, $Pmotor$PairGapDC$Pvei_vr); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_n$Pi_vr : return getReal(comp, $Pmotor$Plesigma$Pi_vr); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_n$Pv_vr : return getReal(comp, $Pmotor$Pground$Pp$Pv_vr); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_p$Pi_vr : return (- getReal(comp, $Pmotor$Plesigma$Pi_vr)); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_p$Pv_vr : return getReal(comp, $Pmotor$PairGapDC$Pvei_vr); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_sen$Pv_vr : return getReal(comp, $Pmotor$PgroundSE$Pp$Pv_vr); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_sep$Pv_vr : return getReal(comp, $Pmotor$PcompoundDCExcitation$Pvse_vr); break;
        case $Pmotor$PcompoundDCExcitation$Pv_vr : return getReal(comp, $Pmotor$PairGapDC$Pvei_vr); break;
        case $Pmotor$PcompoundDCExcitation$Pve_vr : return getReal(comp, $Pmotor$PairGapDC$Pvei_vr); break;
        case $Pmotor$Pcore$PheatPort$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PT_vr); break;
        case $Pmotor$Pcore$Pn$Pv_vr : return getReal(comp, $PidealCommutingSwitch2$Pp$Pv_vr); break;
        case $Pmotor$Pcore$Pp$Pi_vr : return getReal(comp, $Pmotor$Pcore$Pi_vr); break;
        case $Pmotor$Pcore$Pw_vr : return getReal(comp, $Pmotor$PinertiaRotor$Pw_vr); break;
        case $Pmotor$Pfixed$Pflange$Pphi_vr : return getReal(comp, $Pmotor$Pfixed$Pphi0_vr); break;
        case $Pmotor$Pflange$Pphi_vr : return getReal(comp, $PspeedSensor1$Pflange$Pphi_vr); break;
        case $Pmotor$Pflange$Ptau_vr : return getReal(comp, $Pinput_torque_vr); break;
        case $Pmotor$Pfriction$Pflange$Pphi_vr : return getReal(comp, $PspeedSensor1$Pflange$Pphi_vr); break;
        case $Pmotor$Pfriction$Pflange$Ptau_vr : return (- getReal(comp, $Pmotor$Pfriction$Ptau_vr)); break;
        case $Pmotor$Pfriction$PheatPort$PQ_flow_vr : return (- getReal(comp, $Pmotor$PthermalAmbient$PQ_flowFriction_vr)); break;
        case $Pmotor$Pfriction$PheatPort$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PT_vr); break;
        case $Pmotor$Pfriction$PlossPower_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowFriction_vr); break;
        case $Pmotor$Pfriction$Psupport$Pphi_vr : return getReal(comp, $Pmotor$Pfixed$Pphi0_vr); break;
        case $Pmotor$Pfriction$Psupport$Ptau_vr : return getReal(comp, $Pmotor$Pfriction$Ptau_vr); break;
        case $Pmotor$PgroundSE$Pp$Pi_vr : return getReal(comp, $Pmotor$PcompoundDCExcitation$Ppin_sep$Pi_vr); break;
        case $Pmotor$Pia_vr : return (- getReal(comp, $Parm_current_vr)); break;
        case $Pmotor$Pie_vr : return getReal(comp, $Pmotor$Plesigma$Pi_vr); break;
        case $Pmotor$PinertiaRotor$Pflange_a$Pphi_vr : return getReal(comp, $PspeedSensor1$Pflange$Pphi_vr); break;
        case $Pmotor$PinertiaRotor$Pflange_a$Ptau_vr : return getReal(comp, $Pmotor$PtauElectrical_vr); break;
        case $Pmotor$PinertiaRotor$Pflange_b$Pphi_vr : return getReal(comp, $PspeedSensor1$Pflange$Pphi_vr); break;
        case $Pmotor$PinertiaRotor$Pphi_vr : return getReal(comp, $PspeedSensor1$Pflange$Pphi_vr); break;
        case $Pmotor$PinertiaStator$Pflange_a$Pphi_vr : return getReal(comp, $Pmotor$Pfixed$Pphi0_vr); break;
        case $Pmotor$PinertiaStator$Pflange_b$Pphi_vr : return getReal(comp, $Pmotor$Pfixed$Pphi0_vr); break;
        case $Pmotor$PinertiaStator$Pphi_vr : return getReal(comp, $Pmotor$Pfixed$Pphi0_vr); break;
        case $Pmotor$PinternalSupport$Pphi_vr : return getReal(comp, $Pmotor$Pfixed$Pphi0_vr); break;
        case $Pmotor$PinternalThermalPort$PheatPortArmature$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr); break;
        case $Pmotor$PinternalThermalPort$PheatPortBrush$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PT_vr); break;
        case $Pmotor$PinternalThermalPort$PheatPortCore$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PT_vr); break;
        case $Pmotor$PinternalThermalPort$PheatPortExcitation$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr); break;
        case $Pmotor$PinternalThermalPort$PheatPortFriction$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PT_vr); break;
        case $Pmotor$PinternalThermalPort$PheatPortStrayLoad$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PT_vr); break;
        case $Pmotor$Pla$Pn$Pi_vr : return (- getReal(comp, $Pmotor$Pla$Pi_vr)); break;
        case $Pmotor$Pla$Pn$Pv_vr : return getReal(comp, $Pmotor$PairGapDC$Ppin_ap$Pv_vr); break;
        case $Pmotor$Pla$Pp$Pi_vr : return getReal(comp, $Pmotor$Pla$Pi_vr); break;
        case $Pmotor$Pla$Pp$Pv_vr : return getReal(comp, $Pmotor$Pcore$Pp$Pv_vr); break;
        case $Pmotor$Plesigma$Pn$Pi_vr : return (- getReal(comp, $Pmotor$Plesigma$Pi_vr)); break;
        case $Pmotor$Plesigma$Pn$Pv_vr : return getReal(comp, $Pmotor$PairGapDC$Pvei_vr); break;
        case $Pmotor$Plesigma$Pp$Pi_vr : return getReal(comp, $Pmotor$Plesigma$Pi_vr); break;
        case $Pmotor$Ppin_an$Pi_vr : return (- getReal(comp, $Pmotor$Pla$Pi_vr)); break;
        case $Pmotor$Ppin_an$Pv_vr : return getReal(comp, $PidealCommutingSwitch2$Pp$Pv_vr); break;
        case $Pmotor$Ppin_ap$Pi_vr : return (- getReal(comp, $Parm_current_vr)); break;
        case $Pmotor$Ppin_ap$Pv_vr : return getReal(comp, $Parm_sensor$Pp$Pv_vr); break;
        case $Pmotor$Ppin_en$Pi_vr : return (- getReal(comp, $Pmotor$Plesigma$Pi_vr)); break;
        case $Pmotor$Ppin_en$Pv_vr : return getReal(comp, $Pvoltage_ground$Pp$Pv_vr); break;
        case $Pmotor$Ppin_ep$Pi_vr : return getReal(comp, $Pmotor$Plesigma$Pi_vr); break;
        case $Pmotor$Ppin_ep$Pv_vr : return getReal(comp, $Pdc_motor_power$PV_vr); break;
        case $Pmotor$PpowerBalance$PlossPowerArmature_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowArmature_vr); break;
        case $Pmotor$PpowerBalance$PlossPowerBrush_vr : return getReal(comp, $Pmotor$Pbrush$PlossPower_vr); break;
        case $Pmotor$PpowerBalance$PlossPowerCore_vr : return getReal(comp, $Pmotor$Pcore$PlossPower_vr); break;
        case $Pmotor$PpowerBalance$PlossPowerExcitation_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowExcitation_vr); break;
        case $Pmotor$PpowerBalance$PlossPowerFriction_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowFriction_vr); break;
        case $Pmotor$PpowerBalance$PlossPowerStrayLoad_vr : return getReal(comp, $Pmotor$PstrayLoad$PlossPower_vr); break;
        case $Pmotor$Pra$PLossPower_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowArmature_vr); break;
        case $Pmotor$Pra$PT_heatPort_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr); break;
        case $Pmotor$Pra$PheatPort$PQ_flow_vr : return (- getReal(comp, $Pmotor$PthermalAmbient$PQ_flowArmature_vr)); break;
        case $Pmotor$Pra$PheatPort$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr); break;
        case $Pmotor$Pra$Pi_vr : return (- getReal(comp, $Parm_current_vr)); break;
        case $Pmotor$Pra$Pn$Pi_vr : return getReal(comp, $Parm_current_vr); break;
        case $Pmotor$Pra$Pn$Pv_vr : return getReal(comp, $Pmotor$Pcore$Pp$Pv_vr); break;
        case $Pmotor$Pra$Pp$Pi_vr : return (- getReal(comp, $Parm_current_vr)); break;
        case $Pmotor$Pra$Pp$Pv_vr : return getReal(comp, $Parm_sensor$Pp$Pv_vr); break;
        case $Pmotor$Pre$PLossPower_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowExcitation_vr); break;
        case $Pmotor$Pre$PT_heatPort_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr); break;
        case $Pmotor$Pre$PheatPort$PQ_flow_vr : return (- getReal(comp, $Pmotor$PthermalAmbient$PQ_flowExcitation_vr)); break;
        case $Pmotor$Pre$PheatPort$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr); break;
        case $Pmotor$Pre$Pi_vr : return getReal(comp, $Pmotor$Plesigma$Pi_vr); break;
        case $Pmotor$Pre$Pn$Pi_vr : return (- getReal(comp, $Pmotor$Plesigma$Pi_vr)); break;
        case $Pmotor$Pre$Pn$Pv_vr : return getReal(comp, $Pmotor$Plesigma$Pp$Pv_vr); break;
        case $Pmotor$Pre$Pp$Pi_vr : return getReal(comp, $Pmotor$Plesigma$Pi_vr); break;
        case $Pmotor$Pre$Pp$Pv_vr : return getReal(comp, $Pdc_motor_power$PV_vr); break;
        case $Pmotor$PstrayLoad$Pflange$Pphi_vr : return getReal(comp, $PspeedSensor1$Pflange$Pphi_vr); break;
        case $Pmotor$PstrayLoad$PheatPort$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PT_vr); break;
        case $Pmotor$PstrayLoad$Pi_vr : return (- getReal(comp, $Parm_current_vr)); break;
        case $Pmotor$PstrayLoad$Pn$Pi_vr : return getReal(comp, $Parm_current_vr); break;
        case $Pmotor$PstrayLoad$Pn$Pv_vr : return getReal(comp, $Parm_sensor$Pp$Pv_vr); break;
        case $Pmotor$PstrayLoad$Pp$Pi_vr : return (- getReal(comp, $Parm_current_vr)); break;
        case $Pmotor$PstrayLoad$Pp$Pv_vr : return getReal(comp, $Parm_sensor$Pp$Pv_vr); break;
        case $Pmotor$PstrayLoad$Psupport$Pphi_vr : return getReal(comp, $Pmotor$Pfixed$Pphi0_vr); break;
        case $Pmotor$PstrayLoad$Psupport$Ptau_vr : return getReal(comp, $Pmotor$PstrayLoad$Ptau_vr); break;
        case $Pmotor$PtauShaft_vr : return (- getReal(comp, $Pinput_torque_vr)); break;
        case $Pmotor$PthermalAmbient$PQ_flowBrush_vr : return getReal(comp, $Pmotor$Pbrush$PlossPower_vr); break;
        case $Pmotor$PthermalAmbient$PQ_flowCore_vr : return getReal(comp, $Pmotor$Pcore$PlossPower_vr); break;
        case $Pmotor$PthermalAmbient$PQ_flowStrayLoad_vr : return getReal(comp, $Pmotor$PstrayLoad$PlossPower_vr); break;
        case $Pmotor$PthermalAmbient$PconstTa$Py_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr); break;
        case $Pmotor$PthermalAmbient$PconstTe$Py_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr); break;
        case $Pmotor$PthermalAmbient$PtemperatureArmature$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr); break;
        case $Pmotor$PthermalAmbient$PtemperatureArmature$Pport$PQ_flow_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowArmature_vr); break;
        case $Pmotor$PthermalAmbient$PtemperatureArmature$Pport$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr); break;
        case $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PQ_flow_vr : return getReal(comp, $Pmotor$Pbrush$PlossPower_vr); break;
        case $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PQ_flow_vr : return getReal(comp, $Pmotor$Pcore$PlossPower_vr); break;
        case $Pmotor$PthermalAmbient$PtemperatureExcitation$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr); break;
        case $Pmotor$PthermalAmbient$PtemperatureExcitation$Pport$PQ_flow_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowExcitation_vr); break;
        case $Pmotor$PthermalAmbient$PtemperatureExcitation$Pport$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr); break;
        case $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PQ_flow_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowFriction_vr); break;
        case $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PQ_flow_vr : return getReal(comp, $Pmotor$PstrayLoad$PlossPower_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortArmature$PQ_flow_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowArmature_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortArmature$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortBrush$PQ_flow_vr : return getReal(comp, $Pmotor$Pbrush$PlossPower_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortBrush$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PT_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortCore$PQ_flow_vr : return getReal(comp, $Pmotor$Pcore$PlossPower_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortCore$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PT_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortExcitation$PQ_flow_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowExcitation_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortExcitation$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortFriction$PQ_flow_vr : return getReal(comp, $Pmotor$PthermalAmbient$PQ_flowFriction_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortFriction$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PT_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortStrayLoad$PQ_flow_vr : return getReal(comp, $Pmotor$PstrayLoad$PlossPower_vr); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortStrayLoad$PT_vr : return getReal(comp, $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PT_vr); break;
        case $Pmotor$Pve_vr : return getReal(comp, $Pdc_motor_power$PV_vr); break;
        case $PspeedSensor1$Pw_vr : return getReal(comp, $Pspeed_vr); break;
        case $Ptorque1$Pflange$Pphi_vr : return getReal(comp, $PspeedSensor1$Pflange$Pphi_vr); break;
        case $Ptorque1$Pflange$Ptau_vr : return (- getReal(comp, $Pinput_torque_vr)); break;
        case $Ptorque1$Ptau_vr : return getReal(comp, $Pinput_torque_vr); break;
        case $Pup_voltage$Pn$Pi_vr : return (- getReal(comp, $Pup_voltage$Pi_vr)); break;
        case $Pup_voltage$Pn$Pv_vr : return getReal(comp, $Pup_ground$Pp$Pv_vr); break;
        case $Pup_voltage$Pp$Pi_vr : return getReal(comp, $Pup_voltage$Pi_vr); break;
        case $Pup_voltage$Pp$Pv_vr : return getReal(comp, $Pup_voltage$PV_vr); break;
        case $Pup_voltage$Pv_vr : return getReal(comp, $Pup_voltage$PV_vr); break;
        default:
            return 0;
    }
  }
  
  fmi2Status setReal(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Real value) {
    switch (vr) {
        case $Pmotor$PairGapDC$Ppsi_e_vr : comp->fmuData->localData[0]->realVars[0] = value; break;
        case $Pmotor$PinertiaRotor$Pw_vr : comp->fmuData->localData[0]->realVars[1] = value; break;
        case $Pmotor$Pla$Pi_vr : comp->fmuData->localData[0]->realVars[2] = value; break;
        case $Pmotor$PphiMechanical_vr : comp->fmuData->localData[0]->realVars[3] = value; break;
        case $P$DER$Pmotor$PairGapDC$Ppsi_e_vr : comp->fmuData->localData[0]->realVars[4] = value; break;
        case $P$DER$Pmotor$PinertiaRotor$Pw_vr : comp->fmuData->localData[0]->realVars[5] = value; break;
        case $P$DER$Pmotor$Pla$Pi_vr : comp->fmuData->localData[0]->realVars[6] = value; break;
        case $P$DER$Pmotor$PphiMechanical_vr : comp->fmuData->localData[0]->realVars[7] = value; break;
        case $P$DER$Pmotor$Pfriction$Pphi_vr : comp->fmuData->localData[0]->realVars[8] = value; break;
        case $P$DER$Pmotor$Plesigma$Pi_vr : comp->fmuData->localData[0]->realVars[9] = value; break;
        case $P$DER$Pmotor$PstrayLoad$Pphi_vr : comp->fmuData->localData[0]->realVars[10] = value; break;
        case $P$DER$PspeedSensor1$Pflange$Pphi_vr : comp->fmuData->localData[0]->realVars[11] = value; break;
        case $Parm_current_vr : comp->fmuData->localData[0]->realVars[12] = value; break;
        case $Parm_sensor$Pp$Pv_vr : comp->fmuData->localData[0]->realVars[13] = value; break;
        case $Pdown_input_vr : comp->fmuData->localData[0]->realVars[14] = value; break;
        case $PidealCommutingSwitch1$PLossPower_vr : comp->fmuData->localData[0]->realVars[15] = value; break;
        case $PidealCommutingSwitch1$Pn1$Pi_vr : comp->fmuData->localData[0]->realVars[16] = value; break;
        case $PidealCommutingSwitch1$Pn2$Pi_vr : comp->fmuData->localData[0]->realVars[17] = value; break;
        case $PidealCommutingSwitch1$Ps1_vr : comp->fmuData->localData[0]->realVars[18] = value; break;
        case $PidealCommutingSwitch1$Ps2_vr : comp->fmuData->localData[0]->realVars[19] = value; break;
        case $PidealCommutingSwitch2$PLossPower_vr : comp->fmuData->localData[0]->realVars[20] = value; break;
        case $PidealCommutingSwitch2$Pn1$Pi_vr : comp->fmuData->localData[0]->realVars[21] = value; break;
        case $PidealCommutingSwitch2$Pn2$Pi_vr : comp->fmuData->localData[0]->realVars[22] = value; break;
        case $PidealCommutingSwitch2$Pp$Pv_vr : comp->fmuData->localData[0]->realVars[23] = value; break;
        case $PidealCommutingSwitch2$Ps1_vr : comp->fmuData->localData[0]->realVars[24] = value; break;
        case $PidealCommutingSwitch2$Ps2_vr : comp->fmuData->localData[0]->realVars[25] = value; break;
        case $Pinput_torque_vr : comp->fmuData->localData[0]->realVars[26] = value; break;
        case $Pmotor$PairGapDC$Ppin_ap$Pv_vr : comp->fmuData->localData[0]->realVars[27] = value; break;
        case $Pmotor$PairGapDC$Pvai_vr : comp->fmuData->localData[0]->realVars[28] = value; break;
        case $Pmotor$PairGapDC$Pvei_vr : comp->fmuData->localData[0]->realVars[29] = value; break;
        case $Pmotor$Pbrush$PheatPort$PQ_flow_vr : comp->fmuData->localData[0]->realVars[30] = value; break;
        case $Pmotor$Pbrush$PlossPower_vr : comp->fmuData->localData[0]->realVars[31] = value; break;
        case $Pmotor$Pbrush$Pv_vr : comp->fmuData->localData[0]->realVars[32] = value; break;
        case $Pmotor$PcompoundDCExcitation$Ppin_sen$Pi_vr : comp->fmuData->localData[0]->realVars[33] = value; break;
        case $Pmotor$PcompoundDCExcitation$Ppin_sep$Pi_vr : comp->fmuData->localData[0]->realVars[34] = value; break;
        case $Pmotor$PcompoundDCExcitation$Pvse_vr : comp->fmuData->localData[0]->realVars[35] = value; break;
        case $Pmotor$Pcore$PGc_vr : comp->fmuData->localData[0]->realVars[36] = value; break;
        case $Pmotor$Pcore$PheatPort$PQ_flow_vr : comp->fmuData->localData[0]->realVars[37] = value; break;
        case $Pmotor$Pcore$Pi_vr : comp->fmuData->localData[0]->realVars[38] = value; break;
        case $Pmotor$Pcore$PlossPower_vr : comp->fmuData->localData[0]->realVars[39] = value; break;
        case $Pmotor$Pcore$Pn$Pi_vr : comp->fmuData->localData[0]->realVars[40] = value; break;
        case $Pmotor$Pcore$Pp$Pv_vr : comp->fmuData->localData[0]->realVars[41] = value; break;
        case $Pmotor$Pcore$Pv_vr : comp->fmuData->localData[0]->realVars[42] = value; break;
        case $Pmotor$Pcore$PwLimit_vr : comp->fmuData->localData[0]->realVars[43] = value; break;
        case $Pmotor$Pfixed$Pflange$Ptau_vr : comp->fmuData->localData[0]->realVars[44] = value; break;
        case $Pmotor$Pfriction$Pphi_vr : comp->fmuData->localData[0]->realVars[45] = value; break;
        case $Pmotor$Pfriction$Ptau_vr : comp->fmuData->localData[0]->realVars[46] = value; break;
        case $Pmotor$Pfriction$Pw_vr : comp->fmuData->localData[0]->realVars[47] = value; break;
        case $Pmotor$Pground$Pp$Pi_vr : comp->fmuData->localData[0]->realVars[48] = value; break;
        case $Pmotor$Pground$Pp$Pv_vr : comp->fmuData->localData[0]->realVars[49] = value; break;
        case $Pmotor$PgroundSE$Pp$Pv_vr : comp->fmuData->localData[0]->realVars[50] = value; break;
        case $Pmotor$PinertiaRotor$Pa_vr : comp->fmuData->localData[0]->realVars[51] = value; break;
        case $Pmotor$PinertiaRotor$Pflange_b$Ptau_vr : comp->fmuData->localData[0]->realVars[52] = value; break;
        case $Pmotor$PinertiaStator$Pa_vr : comp->fmuData->localData[0]->realVars[53] = value; break;
        case $Pmotor$PinertiaStator$Pflange_a$Ptau_vr : comp->fmuData->localData[0]->realVars[54] = value; break;
        case $Pmotor$PinertiaStator$Pflange_b$Ptau_vr : comp->fmuData->localData[0]->realVars[55] = value; break;
        case $Pmotor$PinertiaStator$Pw_vr : comp->fmuData->localData[0]->realVars[56] = value; break;
        case $Pmotor$PinternalSupport$Ptau_vr : comp->fmuData->localData[0]->realVars[57] = value; break;
        case $Pmotor$PinternalThermalPort$PheatPortArmature$PQ_flow_vr : comp->fmuData->localData[0]->realVars[58] = value; break;
        case $Pmotor$PinternalThermalPort$PheatPortBrush$PQ_flow_vr : comp->fmuData->localData[0]->realVars[59] = value; break;
        case $Pmotor$PinternalThermalPort$PheatPortCore$PQ_flow_vr : comp->fmuData->localData[0]->realVars[60] = value; break;
        case $Pmotor$PinternalThermalPort$PheatPortExcitation$PQ_flow_vr : comp->fmuData->localData[0]->realVars[61] = value; break;
        case $Pmotor$PinternalThermalPort$PheatPortFriction$PQ_flow_vr : comp->fmuData->localData[0]->realVars[62] = value; break;
        case $Pmotor$PinternalThermalPort$PheatPortStrayLoad$PQ_flow_vr : comp->fmuData->localData[0]->realVars[63] = value; break;
        case $Pmotor$Pla$Pv_vr : comp->fmuData->localData[0]->realVars[64] = value; break;
        case $Pmotor$Plesigma$Pi_vr : comp->fmuData->localData[0]->realVars[65] = value; break;
        case $Pmotor$Plesigma$Pp$Pv_vr : comp->fmuData->localData[0]->realVars[66] = value; break;
        case $Pmotor$Plesigma$Pv_vr : comp->fmuData->localData[0]->realVars[67] = value; break;
        case $Pmotor$PpowerBalance$PlossPowerTotal_vr : comp->fmuData->localData[0]->realVars[68] = value; break;
        case $Pmotor$PpowerBalance$PpowerArmature_vr : comp->fmuData->localData[0]->realVars[69] = value; break;
        case $Pmotor$PpowerBalance$PpowerExcitation_vr : comp->fmuData->localData[0]->realVars[70] = value; break;
        case $Pmotor$PpowerBalance$PpowerInertiaRotor_vr : comp->fmuData->localData[0]->realVars[71] = value; break;
        case $Pmotor$PpowerBalance$PpowerInertiaStator_vr : comp->fmuData->localData[0]->realVars[72] = value; break;
        case $Pmotor$PpowerBalance$PpowerMechanical_vr : comp->fmuData->localData[0]->realVars[73] = value; break;
        case $Pmotor$Pra$PR_actual_vr : comp->fmuData->localData[0]->realVars[74] = value; break;
        case $Pmotor$Pra$Pv_vr : comp->fmuData->localData[0]->realVars[75] = value; break;
        case $Pmotor$Pre$PR_actual_vr : comp->fmuData->localData[0]->realVars[76] = value; break;
        case $Pmotor$Pre$Pv_vr : comp->fmuData->localData[0]->realVars[77] = value; break;
        case $Pmotor$PstrayLoad$Pflange$Ptau_vr : comp->fmuData->localData[0]->realVars[78] = value; break;
        case $Pmotor$PstrayLoad$PheatPort$PQ_flow_vr : comp->fmuData->localData[0]->realVars[79] = value; break;
        case $Pmotor$PstrayLoad$PlossPower_vr : comp->fmuData->localData[0]->realVars[80] = value; break;
        case $Pmotor$PstrayLoad$Pphi_vr : comp->fmuData->localData[0]->realVars[81] = value; break;
        case $Pmotor$PstrayLoad$Ptau_vr : comp->fmuData->localData[0]->realVars[82] = value; break;
        case $Pmotor$PstrayLoad$Pv_vr : comp->fmuData->localData[0]->realVars[83] = value; break;
        case $Pmotor$PstrayLoad$Pw_vr : comp->fmuData->localData[0]->realVars[84] = value; break;
        case $Pmotor$PtauElectrical_vr : comp->fmuData->localData[0]->realVars[85] = value; break;
        case $Pmotor$PthermalAmbient$PQ_flowArmature_vr : comp->fmuData->localData[0]->realVars[86] = value; break;
        case $Pmotor$PthermalAmbient$PQ_flowExcitation_vr : comp->fmuData->localData[0]->realVars[87] = value; break;
        case $Pmotor$PthermalAmbient$PQ_flowFriction_vr : comp->fmuData->localData[0]->realVars[88] = value; break;
        case $Pmotor$PthermalAmbient$PQ_flowTotal_vr : comp->fmuData->localData[0]->realVars[89] = value; break;
        case $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PT_vr : comp->fmuData->localData[0]->realVars[90] = value; break;
        case $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PT_vr : comp->fmuData->localData[0]->realVars[91] = value; break;
        case $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PT_vr : comp->fmuData->localData[0]->realVars[92] = value; break;
        case $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PT_vr : comp->fmuData->localData[0]->realVars[93] = value; break;
        case $Pmotor$Pva_vr : comp->fmuData->localData[0]->realVars[94] = value; break;
        case $Pmotor$PwMechanical_vr : comp->fmuData->localData[0]->realVars[95] = value; break;
        case $Pspeed_vr : comp->fmuData->localData[0]->realVars[96] = value; break;
        case $PspeedSensor1$Pflange$Pphi_vr : comp->fmuData->localData[0]->realVars[97] = value; break;
        case $PspeedSensor1$Pflange$Ptau_vr : comp->fmuData->localData[0]->realVars[98] = value; break;
        case $Ptorque1$Pphi_support_vr : comp->fmuData->localData[0]->realVars[99] = value; break;
        case $Pup_ground$Pp$Pi_vr : comp->fmuData->localData[0]->realVars[100] = value; break;
        case $Pup_ground$Pp$Pv_vr : comp->fmuData->localData[0]->realVars[101] = value; break;
        case $Pup_input_vr : comp->fmuData->localData[0]->realVars[102] = value; break;
        case $Pup_voltage$Pi_vr : comp->fmuData->localData[0]->realVars[103] = value; break;
        case $Pvoltage_ground$Pp$Pi_vr : comp->fmuData->localData[0]->realVars[104] = value; break;
        case $Pvoltage_ground$Pp$Pv_vr : comp->fmuData->localData[0]->realVars[105] = value; break;
        case $PconvertToBoolean$Pthreshold_vr : comp->fmuData->simulationInfo->realParameter[0] = value; break;
        case $Pdc_motor_power$PV_vr : comp->fmuData->simulationInfo->realParameter[1] = value; break;
        case $PgreaterThreshold1$Pthreshold_vr : comp->fmuData->simulationInfo->realParameter[2] = value; break;
        case $PidealCommutingSwitch1$PGoff_vr : comp->fmuData->simulationInfo->realParameter[3] = value; break;
        case $PidealCommutingSwitch1$PRon_vr : comp->fmuData->simulationInfo->realParameter[4] = value; break;
        case $PidealCommutingSwitch1$PT_vr : comp->fmuData->simulationInfo->realParameter[5] = value; break;
        case $PidealCommutingSwitch2$PGoff_vr : comp->fmuData->simulationInfo->realParameter[6] = value; break;
        case $PidealCommutingSwitch2$PRon_vr : comp->fmuData->simulationInfo->realParameter[7] = value; break;
        case $PidealCommutingSwitch2$PT_vr : comp->fmuData->simulationInfo->realParameter[8] = value; break;
        case $Pmotor$PIaNominal_vr : comp->fmuData->simulationInfo->realParameter[9] = value; break;
        case $Pmotor$PIeNominal_vr : comp->fmuData->simulationInfo->realParameter[10] = value; break;
        case $Pmotor$PJr_vr : comp->fmuData->simulationInfo->realParameter[11] = value; break;
        case $Pmotor$PJs_vr : comp->fmuData->simulationInfo->realParameter[12] = value; break;
        case $Pmotor$PLa_vr : comp->fmuData->simulationInfo->realParameter[13] = value; break;
        case $Pmotor$PLe_vr : comp->fmuData->simulationInfo->realParameter[14] = value; break;
        case $Pmotor$PLesigma_vr : comp->fmuData->simulationInfo->realParameter[15] = value; break;
        case $Pmotor$PLme_vr : comp->fmuData->simulationInfo->realParameter[16] = value; break;
        case $Pmotor$PRa_vr : comp->fmuData->simulationInfo->realParameter[17] = value; break;
        case $Pmotor$PRe_vr : comp->fmuData->simulationInfo->realParameter[18] = value; break;
        case $Pmotor$PTaNominal_vr : comp->fmuData->simulationInfo->realParameter[19] = value; break;
        case $Pmotor$PTaOperational_vr : comp->fmuData->simulationInfo->realParameter[20] = value; break;
        case $Pmotor$PTaRef_vr : comp->fmuData->simulationInfo->realParameter[21] = value; break;
        case $Pmotor$PTeOperational_vr : comp->fmuData->simulationInfo->realParameter[22] = value; break;
        case $Pmotor$PTeRef_vr : comp->fmuData->simulationInfo->realParameter[23] = value; break;
        case $Pmotor$PVaNominal_vr : comp->fmuData->simulationInfo->realParameter[24] = value; break;
        case $Pmotor$PViNominal_vr : comp->fmuData->simulationInfo->realParameter[25] = value; break;
        case $Pmotor$PairGapDC$PLe_vr : comp->fmuData->simulationInfo->realParameter[26] = value; break;
        case $Pmotor$PairGapDC$PturnsRatio_vr : comp->fmuData->simulationInfo->realParameter[27] = value; break;
        case $Pmotor$Palpha20a_vr : comp->fmuData->simulationInfo->realParameter[28] = value; break;
        case $Pmotor$Palpha20e_vr : comp->fmuData->simulationInfo->realParameter[29] = value; break;
        case $Pmotor$Pbrush$PbrushParameters$PILinear_vr : comp->fmuData->simulationInfo->realParameter[30] = value; break;
        case $Pmotor$Pbrush$PbrushParameters$PV_vr : comp->fmuData->simulationInfo->realParameter[31] = value; break;
        case $Pmotor$PbrushParameters$PILinear_vr : comp->fmuData->simulationInfo->realParameter[32] = value; break;
        case $Pmotor$PbrushParameters$PV_vr : comp->fmuData->simulationInfo->realParameter[33] = value; break;
        case $Pmotor$PcompoundDCExcitation$PexcitationTurnsRatio_vr : comp->fmuData->simulationInfo->realParameter[34] = value; break;
        case $Pmotor$Pcore$PcoreParameters$PGcRef_vr : comp->fmuData->simulationInfo->realParameter[35] = value; break;
        case $Pmotor$Pcore$PcoreParameters$PPRef_vr : comp->fmuData->simulationInfo->realParameter[36] = value; break;
        case $Pmotor$Pcore$PcoreParameters$PVRef_vr : comp->fmuData->simulationInfo->realParameter[37] = value; break;
        case $Pmotor$Pcore$PcoreParameters$PratioHysteresis_vr : comp->fmuData->simulationInfo->realParameter[38] = value; break;
        case $Pmotor$Pcore$PcoreParameters$PwMin_vr : comp->fmuData->simulationInfo->realParameter[39] = value; break;
        case $Pmotor$Pcore$PcoreParameters$PwRef_vr : comp->fmuData->simulationInfo->realParameter[40] = value; break;
        case $Pmotor$PcoreParameters$PGcRef_vr : comp->fmuData->simulationInfo->realParameter[41] = value; break;
        case $Pmotor$PcoreParameters$PPRef_vr : comp->fmuData->simulationInfo->realParameter[42] = value; break;
        case $Pmotor$PcoreParameters$PVRef_vr : comp->fmuData->simulationInfo->realParameter[43] = value; break;
        case $Pmotor$PcoreParameters$PratioHysteresis_vr : comp->fmuData->simulationInfo->realParameter[44] = value; break;
        case $Pmotor$PcoreParameters$PwMin_vr : comp->fmuData->simulationInfo->realParameter[45] = value; break;
        case $Pmotor$PcoreParameters$PwRef_vr : comp->fmuData->simulationInfo->realParameter[46] = value; break;
        case $Pmotor$Pfixed$Pphi0_vr : comp->fmuData->simulationInfo->realParameter[47] = value; break;
        case $Pmotor$Pfriction$PfrictionParameters$PPRef_vr : comp->fmuData->simulationInfo->realParameter[48] = value; break;
        case $Pmotor$Pfriction$PfrictionParameters$Plinear_vr : comp->fmuData->simulationInfo->realParameter[49] = value; break;
        case $Pmotor$Pfriction$PfrictionParameters$Ppower_w_vr : comp->fmuData->simulationInfo->realParameter[50] = value; break;
        case $Pmotor$Pfriction$PfrictionParameters$PtauLinear_vr : comp->fmuData->simulationInfo->realParameter[51] = value; break;
        case $Pmotor$Pfriction$PfrictionParameters$PtauRef_vr : comp->fmuData->simulationInfo->realParameter[52] = value; break;
        case $Pmotor$Pfriction$PfrictionParameters$PwLinear_vr : comp->fmuData->simulationInfo->realParameter[53] = value; break;
        case $Pmotor$Pfriction$PfrictionParameters$PwRef_vr : comp->fmuData->simulationInfo->realParameter[54] = value; break;
        case $Pmotor$PfrictionParameters$PPRef_vr : comp->fmuData->simulationInfo->realParameter[55] = value; break;
        case $Pmotor$PfrictionParameters$Plinear_vr : comp->fmuData->simulationInfo->realParameter[56] = value; break;
        case $Pmotor$PfrictionParameters$Ppower_w_vr : comp->fmuData->simulationInfo->realParameter[57] = value; break;
        case $Pmotor$PfrictionParameters$PtauLinear_vr : comp->fmuData->simulationInfo->realParameter[58] = value; break;
        case $Pmotor$PfrictionParameters$PtauRef_vr : comp->fmuData->simulationInfo->realParameter[59] = value; break;
        case $Pmotor$PfrictionParameters$PwLinear_vr : comp->fmuData->simulationInfo->realParameter[60] = value; break;
        case $Pmotor$PfrictionParameters$PwRef_vr : comp->fmuData->simulationInfo->realParameter[61] = value; break;
        case $Pmotor$PinertiaRotor$PJ_vr : comp->fmuData->simulationInfo->realParameter[62] = value; break;
        case $Pmotor$PinertiaStator$PJ_vr : comp->fmuData->simulationInfo->realParameter[63] = value; break;
        case $Pmotor$Pla$PL_vr : comp->fmuData->simulationInfo->realParameter[64] = value; break;
        case $Pmotor$Plesigma$PL_vr : comp->fmuData->simulationInfo->realParameter[65] = value; break;
        case $Pmotor$Ppsi_eNominal_vr : comp->fmuData->simulationInfo->realParameter[66] = value; break;
        case $Pmotor$Pra$PR_vr : comp->fmuData->simulationInfo->realParameter[67] = value; break;
        case $Pmotor$Pra$PT_vr : comp->fmuData->simulationInfo->realParameter[68] = value; break;
        case $Pmotor$Pra$PT_ref_vr : comp->fmuData->simulationInfo->realParameter[69] = value; break;
        case $Pmotor$Pra$Palpha_vr : comp->fmuData->simulationInfo->realParameter[70] = value; break;
        case $Pmotor$Pre$PR_vr : comp->fmuData->simulationInfo->realParameter[71] = value; break;
        case $Pmotor$Pre$PT_vr : comp->fmuData->simulationInfo->realParameter[72] = value; break;
        case $Pmotor$Pre$PT_ref_vr : comp->fmuData->simulationInfo->realParameter[73] = value; break;
        case $Pmotor$Pre$Palpha_vr : comp->fmuData->simulationInfo->realParameter[74] = value; break;
        case $Pmotor$Psigmae_vr : comp->fmuData->simulationInfo->realParameter[75] = value; break;
        case $Pmotor$PstrayLoad$PstrayLoadParameters$PIRef_vr : comp->fmuData->simulationInfo->realParameter[76] = value; break;
        case $Pmotor$PstrayLoad$PstrayLoadParameters$PPRef_vr : comp->fmuData->simulationInfo->realParameter[77] = value; break;
        case $Pmotor$PstrayLoad$PstrayLoadParameters$Ppower_w_vr : comp->fmuData->simulationInfo->realParameter[78] = value; break;
        case $Pmotor$PstrayLoad$PstrayLoadParameters$PtauRef_vr : comp->fmuData->simulationInfo->realParameter[79] = value; break;
        case $Pmotor$PstrayLoad$PstrayLoadParameters$PwRef_vr : comp->fmuData->simulationInfo->realParameter[80] = value; break;
        case $Pmotor$PstrayLoadParameters$PIRef_vr : comp->fmuData->simulationInfo->realParameter[81] = value; break;
        case $Pmotor$PstrayLoadParameters$PPRef_vr : comp->fmuData->simulationInfo->realParameter[82] = value; break;
        case $Pmotor$PstrayLoadParameters$Ppower_w_vr : comp->fmuData->simulationInfo->realParameter[83] = value; break;
        case $Pmotor$PstrayLoadParameters$PtauRef_vr : comp->fmuData->simulationInfo->realParameter[84] = value; break;
        case $Pmotor$PstrayLoadParameters$PwRef_vr : comp->fmuData->simulationInfo->realParameter[85] = value; break;
        case $Pmotor$PthermalAmbient$PTa_vr : comp->fmuData->simulationInfo->realParameter[86] = value; break;
        case $Pmotor$PthermalAmbient$PTe_vr : comp->fmuData->simulationInfo->realParameter[87] = value; break;
        case $Pmotor$PthermalAmbient$PconstTa$Pk_vr : comp->fmuData->simulationInfo->realParameter[88] = value; break;
        case $Pmotor$PthermalAmbient$PconstTe$Pk_vr : comp->fmuData->simulationInfo->realParameter[89] = value; break;
        case $Pmotor$PthermalAmbient$PtemperatureBrush$PT_vr : comp->fmuData->simulationInfo->realParameter[90] = value; break;
        case $Pmotor$PthermalAmbient$PtemperatureCore$PT_vr : comp->fmuData->simulationInfo->realParameter[91] = value; break;
        case $Pmotor$PthermalAmbient$PtemperatureFriction$PT_vr : comp->fmuData->simulationInfo->realParameter[92] = value; break;
        case $Pmotor$PthermalAmbient$PtemperatureStrayLoad$PT_vr : comp->fmuData->simulationInfo->realParameter[93] = value; break;
        case $Pmotor$PturnsRatio_vr : comp->fmuData->simulationInfo->realParameter[94] = value; break;
        case $Pmotor$PwNominal_vr : comp->fmuData->simulationInfo->realParameter[95] = value; break;
        case $Pmotor_frictionParameters$PPRef_vr : comp->fmuData->simulationInfo->realParameter[96] = value; break;
        case $Pmotor_frictionParameters$Plinear_vr : comp->fmuData->simulationInfo->realParameter[97] = value; break;
        case $Pmotor_frictionParameters$Ppower_w_vr : comp->fmuData->simulationInfo->realParameter[98] = value; break;
        case $Pmotor_frictionParameters$PtauLinear_vr : comp->fmuData->simulationInfo->realParameter[99] = value; break;
        case $Pmotor_frictionParameters$PtauRef_vr : comp->fmuData->simulationInfo->realParameter[100] = value; break;
        case $Pmotor_frictionParameters$PwLinear_vr : comp->fmuData->simulationInfo->realParameter[101] = value; break;
        case $Pmotor_frictionParameters$PwRef_vr : comp->fmuData->simulationInfo->realParameter[102] = value; break;
        case $Pup_voltage$PV_vr : comp->fmuData->simulationInfo->realParameter[103] = value; break;
        case $Parm_sensor$Pi_vr : return setReal(comp, $Parm_current_vr, value); break;
        case $Parm_sensor$Pn$Pi_vr : return setReal(comp, $Parm_current_vr, (- value)); break;
        case $Parm_sensor$Pn$Pv_vr : return setReal(comp, $Parm_sensor$Pp$Pv_vr, value); break;
        case $Parm_sensor$Pp$Pi_vr : return setReal(comp, $Parm_current_vr, value); break;
        case $PconvertToBoolean$Pu_vr : return setReal(comp, $Pup_input_vr, value); break;
        case $Pdc_motor_power$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, (- value)); break;
        case $Pdc_motor_power$Pn$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, value); break;
        case $Pdc_motor_power$Pn$Pv_vr : return setReal(comp, $Pvoltage_ground$Pp$Pv_vr, value); break;
        case $Pdc_motor_power$Pp$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, (- value)); break;
        case $Pdc_motor_power$Pp$Pv_vr : return setReal(comp, $Pdc_motor_power$PV_vr, value); break;
        case $Pdc_motor_power$Pv_vr : return setReal(comp, $Pdc_motor_power$PV_vr, value); break;
        case $PgreaterThreshold1$Pu_vr : return setReal(comp, $Pdown_input_vr, value); break;
        case $PidealCommutingSwitch1$PT_heatPort_vr : return setReal(comp, $PidealCommutingSwitch1$PT_vr, value); break;
        case $PidealCommutingSwitch1$Pn1$Pv_vr : return setReal(comp, $Pup_voltage$PV_vr, value); break;
        case $PidealCommutingSwitch1$Pn2$Pv_vr : return setReal(comp, $Pup_ground$Pp$Pv_vr, value); break;
        case $PidealCommutingSwitch1$Pp$Pi_vr : return setReal(comp, $Parm_current_vr, value); break;
        case $PidealCommutingSwitch1$Pp$Pv_vr : return setReal(comp, $Parm_sensor$Pp$Pv_vr, value); break;
        case $PidealCommutingSwitch2$PT_heatPort_vr : return setReal(comp, $PidealCommutingSwitch2$PT_vr, value); break;
        case $PidealCommutingSwitch2$Pn1$Pv_vr : return setReal(comp, $Pup_voltage$PV_vr, value); break;
        case $PidealCommutingSwitch2$Pn2$Pv_vr : return setReal(comp, $Pup_ground$Pp$Pv_vr, value); break;
        case $PidealCommutingSwitch2$Pp$Pi_vr : return setReal(comp, $Pmotor$Pla$Pi_vr, value); break;
        case $Pmotor$PairGapDC$Pflange$Pphi_vr : return setReal(comp, $PspeedSensor1$Pflange$Pphi_vr, value); break;
        case $Pmotor$PairGapDC$Pflange$Ptau_vr : return setReal(comp, $Pmotor$PtauElectrical_vr, (- value)); break;
        case $Pmotor$PairGapDC$Pia_vr : return setReal(comp, $Pmotor$Pla$Pi_vr, value); break;
        case $Pmotor$PairGapDC$Pie_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, value); break;
        case $Pmotor$PairGapDC$Ppin_an$Pi_vr : return setReal(comp, $Pmotor$Pla$Pi_vr, (- value)); break;
        case $Pmotor$PairGapDC$Ppin_an$Pv_vr : return setReal(comp, $PidealCommutingSwitch2$Pp$Pv_vr, value); break;
        case $Pmotor$PairGapDC$Ppin_ap$Pi_vr : return setReal(comp, $Pmotor$Pla$Pi_vr, value); break;
        case $Pmotor$PairGapDC$Ppin_en$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, (- value)); break;
        case $Pmotor$PairGapDC$Ppin_en$Pv_vr : return setReal(comp, $Pmotor$Pground$Pp$Pv_vr, value); break;
        case $Pmotor$PairGapDC$Ppin_ep$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, value); break;
        case $Pmotor$PairGapDC$Ppin_ep$Pv_vr : return setReal(comp, $Pmotor$PairGapDC$Pvei_vr, value); break;
        case $Pmotor$PairGapDC$Psupport$Pphi_vr : return setReal(comp, $Pmotor$Pfixed$Pphi0_vr, value); break;
        case $Pmotor$PairGapDC$Psupport$Ptau_vr : return setReal(comp, $Pmotor$PtauElectrical_vr, value); break;
        case $Pmotor$PairGapDC$PtauElectrical_vr : return setReal(comp, $Pmotor$PtauElectrical_vr, value); break;
        case $Pmotor$PairGapDC$Pw_vr : return setReal(comp, $Pmotor$PinertiaRotor$Pw_vr, value); break;
        case $Pmotor$Pbrush$PheatPort$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PT_vr, value); break;
        case $Pmotor$Pbrush$Pi_vr : return setReal(comp, $Pmotor$Pla$Pi_vr, value); break;
        case $Pmotor$Pbrush$Pn$Pi_vr : return setReal(comp, $Pmotor$Pla$Pi_vr, (- value)); break;
        case $Pmotor$Pbrush$Pn$Pv_vr : return setReal(comp, $PidealCommutingSwitch2$Pp$Pv_vr, value); break;
        case $Pmotor$Pbrush$Pp$Pi_vr : return setReal(comp, $Pmotor$Pla$Pi_vr, value); break;
        case $Pmotor$Pbrush$Pp$Pv_vr : return setReal(comp, $PidealCommutingSwitch2$Pp$Pv_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, (- value)); break;
        case $Pmotor$PcompoundDCExcitation$Pie_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Pise_vr : return setReal(comp, $Pmotor$PcompoundDCExcitation$Ppin_sep$Pi_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_en$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, (- value)); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_en$Pv_vr : return setReal(comp, $Pvoltage_ground$Pp$Pv_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_ep$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_ep$Pv_vr : return setReal(comp, $Pmotor$PairGapDC$Pvei_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_n$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_n$Pv_vr : return setReal(comp, $Pmotor$Pground$Pp$Pv_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_p$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, (- value)); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_p$Pv_vr : return setReal(comp, $Pmotor$PairGapDC$Pvei_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_sen$Pv_vr : return setReal(comp, $Pmotor$PgroundSE$Pp$Pv_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Ppin_sep$Pv_vr : return setReal(comp, $Pmotor$PcompoundDCExcitation$Pvse_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Pv_vr : return setReal(comp, $Pmotor$PairGapDC$Pvei_vr, value); break;
        case $Pmotor$PcompoundDCExcitation$Pve_vr : return setReal(comp, $Pmotor$PairGapDC$Pvei_vr, value); break;
        case $Pmotor$Pcore$PheatPort$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PT_vr, value); break;
        case $Pmotor$Pcore$Pn$Pv_vr : return setReal(comp, $PidealCommutingSwitch2$Pp$Pv_vr, value); break;
        case $Pmotor$Pcore$Pp$Pi_vr : return setReal(comp, $Pmotor$Pcore$Pi_vr, value); break;
        case $Pmotor$Pcore$Pw_vr : return setReal(comp, $Pmotor$PinertiaRotor$Pw_vr, value); break;
        case $Pmotor$Pfixed$Pflange$Pphi_vr : return setReal(comp, $Pmotor$Pfixed$Pphi0_vr, value); break;
        case $Pmotor$Pflange$Pphi_vr : return setReal(comp, $PspeedSensor1$Pflange$Pphi_vr, value); break;
        case $Pmotor$Pflange$Ptau_vr : return setReal(comp, $Pinput_torque_vr, value); break;
        case $Pmotor$Pfriction$Pflange$Pphi_vr : return setReal(comp, $PspeedSensor1$Pflange$Pphi_vr, value); break;
        case $Pmotor$Pfriction$Pflange$Ptau_vr : return setReal(comp, $Pmotor$Pfriction$Ptau_vr, (- value)); break;
        case $Pmotor$Pfriction$PheatPort$PQ_flow_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowFriction_vr, (- value)); break;
        case $Pmotor$Pfriction$PheatPort$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PT_vr, value); break;
        case $Pmotor$Pfriction$PlossPower_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowFriction_vr, value); break;
        case $Pmotor$Pfriction$Psupport$Pphi_vr : return setReal(comp, $Pmotor$Pfixed$Pphi0_vr, value); break;
        case $Pmotor$Pfriction$Psupport$Ptau_vr : return setReal(comp, $Pmotor$Pfriction$Ptau_vr, value); break;
        case $Pmotor$PgroundSE$Pp$Pi_vr : return setReal(comp, $Pmotor$PcompoundDCExcitation$Ppin_sep$Pi_vr, value); break;
        case $Pmotor$Pia_vr : return setReal(comp, $Parm_current_vr, (- value)); break;
        case $Pmotor$Pie_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, value); break;
        case $Pmotor$PinertiaRotor$Pflange_a$Pphi_vr : return setReal(comp, $PspeedSensor1$Pflange$Pphi_vr, value); break;
        case $Pmotor$PinertiaRotor$Pflange_a$Ptau_vr : return setReal(comp, $Pmotor$PtauElectrical_vr, value); break;
        case $Pmotor$PinertiaRotor$Pflange_b$Pphi_vr : return setReal(comp, $PspeedSensor1$Pflange$Pphi_vr, value); break;
        case $Pmotor$PinertiaRotor$Pphi_vr : return setReal(comp, $PspeedSensor1$Pflange$Pphi_vr, value); break;
        case $Pmotor$PinertiaStator$Pflange_a$Pphi_vr : return setReal(comp, $Pmotor$Pfixed$Pphi0_vr, value); break;
        case $Pmotor$PinertiaStator$Pflange_b$Pphi_vr : return setReal(comp, $Pmotor$Pfixed$Pphi0_vr, value); break;
        case $Pmotor$PinertiaStator$Pphi_vr : return setReal(comp, $Pmotor$Pfixed$Pphi0_vr, value); break;
        case $Pmotor$PinternalSupport$Pphi_vr : return setReal(comp, $Pmotor$Pfixed$Pphi0_vr, value); break;
        case $Pmotor$PinternalThermalPort$PheatPortArmature$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr, value); break;
        case $Pmotor$PinternalThermalPort$PheatPortBrush$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PT_vr, value); break;
        case $Pmotor$PinternalThermalPort$PheatPortCore$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PT_vr, value); break;
        case $Pmotor$PinternalThermalPort$PheatPortExcitation$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr, value); break;
        case $Pmotor$PinternalThermalPort$PheatPortFriction$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PT_vr, value); break;
        case $Pmotor$PinternalThermalPort$PheatPortStrayLoad$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PT_vr, value); break;
        case $Pmotor$Pla$Pn$Pi_vr : return setReal(comp, $Pmotor$Pla$Pi_vr, (- value)); break;
        case $Pmotor$Pla$Pn$Pv_vr : return setReal(comp, $Pmotor$PairGapDC$Ppin_ap$Pv_vr, value); break;
        case $Pmotor$Pla$Pp$Pi_vr : return setReal(comp, $Pmotor$Pla$Pi_vr, value); break;
        case $Pmotor$Pla$Pp$Pv_vr : return setReal(comp, $Pmotor$Pcore$Pp$Pv_vr, value); break;
        case $Pmotor$Plesigma$Pn$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, (- value)); break;
        case $Pmotor$Plesigma$Pn$Pv_vr : return setReal(comp, $Pmotor$PairGapDC$Pvei_vr, value); break;
        case $Pmotor$Plesigma$Pp$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, value); break;
        case $Pmotor$Ppin_an$Pi_vr : return setReal(comp, $Pmotor$Pla$Pi_vr, (- value)); break;
        case $Pmotor$Ppin_an$Pv_vr : return setReal(comp, $PidealCommutingSwitch2$Pp$Pv_vr, value); break;
        case $Pmotor$Ppin_ap$Pi_vr : return setReal(comp, $Parm_current_vr, (- value)); break;
        case $Pmotor$Ppin_ap$Pv_vr : return setReal(comp, $Parm_sensor$Pp$Pv_vr, value); break;
        case $Pmotor$Ppin_en$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, (- value)); break;
        case $Pmotor$Ppin_en$Pv_vr : return setReal(comp, $Pvoltage_ground$Pp$Pv_vr, value); break;
        case $Pmotor$Ppin_ep$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, value); break;
        case $Pmotor$Ppin_ep$Pv_vr : return setReal(comp, $Pdc_motor_power$PV_vr, value); break;
        case $Pmotor$PpowerBalance$PlossPowerArmature_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowArmature_vr, value); break;
        case $Pmotor$PpowerBalance$PlossPowerBrush_vr : return setReal(comp, $Pmotor$Pbrush$PlossPower_vr, value); break;
        case $Pmotor$PpowerBalance$PlossPowerCore_vr : return setReal(comp, $Pmotor$Pcore$PlossPower_vr, value); break;
        case $Pmotor$PpowerBalance$PlossPowerExcitation_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowExcitation_vr, value); break;
        case $Pmotor$PpowerBalance$PlossPowerFriction_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowFriction_vr, value); break;
        case $Pmotor$PpowerBalance$PlossPowerStrayLoad_vr : return setReal(comp, $Pmotor$PstrayLoad$PlossPower_vr, value); break;
        case $Pmotor$Pra$PLossPower_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowArmature_vr, value); break;
        case $Pmotor$Pra$PT_heatPort_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr, value); break;
        case $Pmotor$Pra$PheatPort$PQ_flow_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowArmature_vr, (- value)); break;
        case $Pmotor$Pra$PheatPort$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr, value); break;
        case $Pmotor$Pra$Pi_vr : return setReal(comp, $Parm_current_vr, (- value)); break;
        case $Pmotor$Pra$Pn$Pi_vr : return setReal(comp, $Parm_current_vr, value); break;
        case $Pmotor$Pra$Pn$Pv_vr : return setReal(comp, $Pmotor$Pcore$Pp$Pv_vr, value); break;
        case $Pmotor$Pra$Pp$Pi_vr : return setReal(comp, $Parm_current_vr, (- value)); break;
        case $Pmotor$Pra$Pp$Pv_vr : return setReal(comp, $Parm_sensor$Pp$Pv_vr, value); break;
        case $Pmotor$Pre$PLossPower_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowExcitation_vr, value); break;
        case $Pmotor$Pre$PT_heatPort_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr, value); break;
        case $Pmotor$Pre$PheatPort$PQ_flow_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowExcitation_vr, (- value)); break;
        case $Pmotor$Pre$PheatPort$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr, value); break;
        case $Pmotor$Pre$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, value); break;
        case $Pmotor$Pre$Pn$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, (- value)); break;
        case $Pmotor$Pre$Pn$Pv_vr : return setReal(comp, $Pmotor$Plesigma$Pp$Pv_vr, value); break;
        case $Pmotor$Pre$Pp$Pi_vr : return setReal(comp, $Pmotor$Plesigma$Pi_vr, value); break;
        case $Pmotor$Pre$Pp$Pv_vr : return setReal(comp, $Pdc_motor_power$PV_vr, value); break;
        case $Pmotor$PstrayLoad$Pflange$Pphi_vr : return setReal(comp, $PspeedSensor1$Pflange$Pphi_vr, value); break;
        case $Pmotor$PstrayLoad$PheatPort$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PT_vr, value); break;
        case $Pmotor$PstrayLoad$Pi_vr : return setReal(comp, $Parm_current_vr, (- value)); break;
        case $Pmotor$PstrayLoad$Pn$Pi_vr : return setReal(comp, $Parm_current_vr, value); break;
        case $Pmotor$PstrayLoad$Pn$Pv_vr : return setReal(comp, $Parm_sensor$Pp$Pv_vr, value); break;
        case $Pmotor$PstrayLoad$Pp$Pi_vr : return setReal(comp, $Parm_current_vr, (- value)); break;
        case $Pmotor$PstrayLoad$Pp$Pv_vr : return setReal(comp, $Parm_sensor$Pp$Pv_vr, value); break;
        case $Pmotor$PstrayLoad$Psupport$Pphi_vr : return setReal(comp, $Pmotor$Pfixed$Pphi0_vr, value); break;
        case $Pmotor$PstrayLoad$Psupport$Ptau_vr : return setReal(comp, $Pmotor$PstrayLoad$Ptau_vr, value); break;
        case $Pmotor$PtauShaft_vr : return setReal(comp, $Pinput_torque_vr, (- value)); break;
        case $Pmotor$PthermalAmbient$PQ_flowBrush_vr : return setReal(comp, $Pmotor$Pbrush$PlossPower_vr, value); break;
        case $Pmotor$PthermalAmbient$PQ_flowCore_vr : return setReal(comp, $Pmotor$Pcore$PlossPower_vr, value); break;
        case $Pmotor$PthermalAmbient$PQ_flowStrayLoad_vr : return setReal(comp, $Pmotor$PstrayLoad$PlossPower_vr, value); break;
        case $Pmotor$PthermalAmbient$PconstTa$Py_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr, value); break;
        case $Pmotor$PthermalAmbient$PconstTe$Py_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr, value); break;
        case $Pmotor$PthermalAmbient$PtemperatureArmature$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr, value); break;
        case $Pmotor$PthermalAmbient$PtemperatureArmature$Pport$PQ_flow_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowArmature_vr, value); break;
        case $Pmotor$PthermalAmbient$PtemperatureArmature$Pport$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr, value); break;
        case $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PQ_flow_vr : return setReal(comp, $Pmotor$Pbrush$PlossPower_vr, value); break;
        case $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PQ_flow_vr : return setReal(comp, $Pmotor$Pcore$PlossPower_vr, value); break;
        case $Pmotor$PthermalAmbient$PtemperatureExcitation$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr, value); break;
        case $Pmotor$PthermalAmbient$PtemperatureExcitation$Pport$PQ_flow_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowExcitation_vr, value); break;
        case $Pmotor$PthermalAmbient$PtemperatureExcitation$Pport$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr, value); break;
        case $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PQ_flow_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowFriction_vr, value); break;
        case $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PQ_flow_vr : return setReal(comp, $Pmotor$PstrayLoad$PlossPower_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortArmature$PQ_flow_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowArmature_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortArmature$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTa$Pk_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortBrush$PQ_flow_vr : return setReal(comp, $Pmotor$Pbrush$PlossPower_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortBrush$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureBrush$Pport$PT_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortCore$PQ_flow_vr : return setReal(comp, $Pmotor$Pcore$PlossPower_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortCore$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureCore$Pport$PT_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortExcitation$PQ_flow_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowExcitation_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortExcitation$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PconstTe$Pk_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortFriction$PQ_flow_vr : return setReal(comp, $Pmotor$PthermalAmbient$PQ_flowFriction_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortFriction$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureFriction$Pport$PT_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortStrayLoad$PQ_flow_vr : return setReal(comp, $Pmotor$PstrayLoad$PlossPower_vr, value); break;
        case $Pmotor$PthermalAmbient$PthermalPort$PheatPortStrayLoad$PT_vr : return setReal(comp, $Pmotor$PthermalAmbient$PtemperatureStrayLoad$Pport$PT_vr, value); break;
        case $Pmotor$Pve_vr : return setReal(comp, $Pdc_motor_power$PV_vr, value); break;
        case $PspeedSensor1$Pw_vr : return setReal(comp, $Pspeed_vr, value); break;
        case $Ptorque1$Pflange$Pphi_vr : return setReal(comp, $PspeedSensor1$Pflange$Pphi_vr, value); break;
        case $Ptorque1$Pflange$Ptau_vr : return setReal(comp, $Pinput_torque_vr, (- value)); break;
        case $Ptorque1$Ptau_vr : return setReal(comp, $Pinput_torque_vr, value); break;
        case $Pup_voltage$Pn$Pi_vr : return setReal(comp, $Pup_voltage$Pi_vr, (- value)); break;
        case $Pup_voltage$Pn$Pv_vr : return setReal(comp, $Pup_ground$Pp$Pv_vr, value); break;
        case $Pup_voltage$Pp$Pi_vr : return setReal(comp, $Pup_voltage$Pi_vr, value); break;
        case $Pup_voltage$Pp$Pv_vr : return setReal(comp, $Pup_voltage$PV_vr, value); break;
        case $Pup_voltage$Pv_vr : return setReal(comp, $Pup_voltage$PV_vr, value); break;
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  
  fmi2Integer getInteger(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        case $Pmotor$Pcore$PcoreParameters$Pm_vr : return comp->fmuData->simulationInfo->integerParameter[0]; break;
        case $Pmotor$PcoreParameters$Pm_vr : return comp->fmuData->simulationInfo->integerParameter[1]; break;
        case $Pmotor$PinertiaRotor$PstateSelect_vr : return comp->fmuData->simulationInfo->integerParameter[2]; break;
        case $Pmotor$PinertiaStator$PstateSelect_vr : return comp->fmuData->simulationInfo->integerParameter[3]; break;
        default:
            return 0;
    }
  }
  fmi2Status setInteger(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Integer value) {
    switch (vr) {
        case $Pmotor$Pcore$PcoreParameters$Pm_vr : comp->fmuData->simulationInfo->integerParameter[0] = value; break;
        case $Pmotor$PcoreParameters$Pm_vr : comp->fmuData->simulationInfo->integerParameter[1] = value; break;
        case $Pmotor$PinertiaRotor$PstateSelect_vr : comp->fmuData->simulationInfo->integerParameter[2] = value; break;
        case $Pmotor$PinertiaStator$PstateSelect_vr : comp->fmuData->simulationInfo->integerParameter[3] = value; break;
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  fmi2Boolean getBoolean(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        case $PconvertToBoolean$Py_vr : return comp->fmuData->localData[0]->booleanVars[0]; break;
        case $PgreaterThreshold1$Py_vr : return comp->fmuData->localData[0]->booleanVars[1]; break;
        case $PidealCommutingSwitch1$PuseHeatPort_vr : return comp->fmuData->simulationInfo->booleanParameter[0]; break;
        case $PidealCommutingSwitch2$PuseHeatPort_vr : return comp->fmuData->simulationInfo->booleanParameter[1]; break;
        case $Pmotor$PairGapDC$PquasiStationary_vr : return comp->fmuData->simulationInfo->booleanParameter[2]; break;
        case $Pmotor$Pbrush$PuseHeatPort_vr : return comp->fmuData->simulationInfo->booleanParameter[3]; break;
        case $Pmotor$Pcore$PuseHeatPort_vr : return comp->fmuData->simulationInfo->booleanParameter[4]; break;
        case $Pmotor$Pfriction$PuseHeatPort_vr : return comp->fmuData->simulationInfo->booleanParameter[5]; break;
        case $Pmotor$Pla$PquasiStationary_vr : return comp->fmuData->simulationInfo->booleanParameter[6]; break;
        case $Pmotor$Plesigma$PquasiStationary_vr : return comp->fmuData->simulationInfo->booleanParameter[7]; break;
        case $Pmotor$Pra$PuseHeatPort_vr : return comp->fmuData->simulationInfo->booleanParameter[8]; break;
        case $Pmotor$Pre$PuseHeatPort_vr : return comp->fmuData->simulationInfo->booleanParameter[9]; break;
        case $Pmotor$PstrayLoad$PuseHeatPort_vr : return comp->fmuData->simulationInfo->booleanParameter[10]; break;
        case $Pmotor$PthermalAmbient$PuseTemperatureInputs_vr : return comp->fmuData->simulationInfo->booleanParameter[11]; break;
        case $Pmotor$PuseSupport_vr : return comp->fmuData->simulationInfo->booleanParameter[12]; break;
        case $Pmotor$PuseThermalPort_vr : return comp->fmuData->simulationInfo->booleanParameter[13]; break;
        case $Ptorque1$PuseSupport_vr : return comp->fmuData->simulationInfo->booleanParameter[14]; break;
        case $PidealCommutingSwitch1$Pcontrol_vr : return getBoolean(comp, $PgreaterThreshold1$Py_vr); break;
        case $PidealCommutingSwitch2$Pcontrol_vr : return getBoolean(comp, $PconvertToBoolean$Py_vr); break;
        default:
            return fmi2False;
    }
  }
  
  fmi2Status setBoolean(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Boolean value) {
    switch (vr) {
        case $PconvertToBoolean$Py_vr : comp->fmuData->localData[0]->booleanVars[0] = value; break;
        case $PgreaterThreshold1$Py_vr : comp->fmuData->localData[0]->booleanVars[1] = value; break;
        case $PidealCommutingSwitch1$PuseHeatPort_vr : comp->fmuData->simulationInfo->booleanParameter[0] = value; break;
        case $PidealCommutingSwitch2$PuseHeatPort_vr : comp->fmuData->simulationInfo->booleanParameter[1] = value; break;
        case $Pmotor$PairGapDC$PquasiStationary_vr : comp->fmuData->simulationInfo->booleanParameter[2] = value; break;
        case $Pmotor$Pbrush$PuseHeatPort_vr : comp->fmuData->simulationInfo->booleanParameter[3] = value; break;
        case $Pmotor$Pcore$PuseHeatPort_vr : comp->fmuData->simulationInfo->booleanParameter[4] = value; break;
        case $Pmotor$Pfriction$PuseHeatPort_vr : comp->fmuData->simulationInfo->booleanParameter[5] = value; break;
        case $Pmotor$Pla$PquasiStationary_vr : comp->fmuData->simulationInfo->booleanParameter[6] = value; break;
        case $Pmotor$Plesigma$PquasiStationary_vr : comp->fmuData->simulationInfo->booleanParameter[7] = value; break;
        case $Pmotor$Pra$PuseHeatPort_vr : comp->fmuData->simulationInfo->booleanParameter[8] = value; break;
        case $Pmotor$Pre$PuseHeatPort_vr : comp->fmuData->simulationInfo->booleanParameter[9] = value; break;
        case $Pmotor$PstrayLoad$PuseHeatPort_vr : comp->fmuData->simulationInfo->booleanParameter[10] = value; break;
        case $Pmotor$PthermalAmbient$PuseTemperatureInputs_vr : comp->fmuData->simulationInfo->booleanParameter[11] = value; break;
        case $Pmotor$PuseSupport_vr : comp->fmuData->simulationInfo->booleanParameter[12] = value; break;
        case $Pmotor$PuseThermalPort_vr : comp->fmuData->simulationInfo->booleanParameter[13] = value; break;
        case $Ptorque1$PuseSupport_vr : comp->fmuData->simulationInfo->booleanParameter[14] = value; break;
        case $PidealCommutingSwitch1$Pcontrol_vr : return setBoolean(comp, $PgreaterThreshold1$Py_vr, value); break;
        case $PidealCommutingSwitch2$Pcontrol_vr : return setBoolean(comp, $PconvertToBoolean$Py_vr, value); break;
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

