/* Linearization */
#include "PW_PowerSystem_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

const char *PW_PowerSystem_linear_model_frame()
{
  return "model linear_PW__PowerSystem\n  parameter Integer n = 4; // states\n  parameter Integer k = 3; // top-level inputs\n  parameter Integer l = 2; // top-level outputs\n"
  "  parameter Real x0[4] = {%s};\n"
  "  parameter Real u0[3] = {%s};\n"
  "  parameter Real A[4,4] = [%s];\n"
  "  parameter Real B[4,3] = [%s];\n"
  "  parameter Real C[2,4] = [%s];\n"
  "  parameter Real D[2,3] = [%s];\n"
  "  Real x[4](start=x0);\n"
  "  input Real u[3](start= u0);\n"
  "  output Real y[2];\n"
  "\n    Real 'x_motor.airGapDC.psi_e' = x[1];\n  Real 'x_motor.inertiaRotor.w' = x[2];\n  Real 'x_motor.la.i' = x[3];\n  Real 'x_motor.phiMechanical' = x[4];\n  Real 'u_down_input' = u[1];\n  Real 'u_input_torque' = u[2];\n  Real 'u_up_input' = u[3];\n  Real 'y_arm_current' = y[1];\n  Real 'y_speed' = y[2];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\nend linear_PW__PowerSystem;\n";
}
const char *PW_PowerSystem_linear_model_datarecovery_frame()
{
  return "model linear_PW__PowerSystem\n  parameter Integer n = 4; // states\n  parameter Integer k = 3; // top-level inputs\n  parameter Integer l = 2; // top-level outputs\n  parameter Integer nz = 98; // data recovery variables\n"
  "  parameter Real x0[4] = {%s};\n"
  "  parameter Real u0[3] = {%s};\n"
  "  parameter Real z0[98] = {%s};\n"
  "  parameter Real A[4,4] = [%s];\n"
  "  parameter Real B[4,3] = [%s];\n"
  "  parameter Real C[2,4] = [%s];\n"
  "  parameter Real D[2,3] = [%s];\n"
  "  parameter Real Cz[98,4] = [%s];\n"
  "  parameter Real Dz[98,3] = [%s];\n"
  "  Real x[4](start=x0);\n"
  "  input Real u[3](start= u0);\n"
  "  output Real y[2];\n"
  "  output Real z[98];\n"
  "\n  Real 'x_motor.airGapDC.psi_e' = x[1];\n  Real 'x_motor.inertiaRotor.w' = x[2];\n  Real 'x_motor.la.i' = x[3];\n  Real 'x_motor.phiMechanical' = x[4];\n  Real 'u_down_input' = u[1];\n  Real 'u_input_torque' = u[2];\n  Real 'u_up_input' = u[3];\n  Real 'y_arm_current' = y[1];\n  Real 'y_speed' = y[2];\n  Real 'z_der(motor.friction.phi)' = z[1];\n  Real 'z_der(motor.lesigma.i)' = z[2];\n  Real 'z_der(motor.strayLoad.phi)' = z[3];\n  Real 'z_der(speedSensor1.flange.phi)' = z[4];\n  Real 'z_arm_current' = z[5];\n  Real 'z_arm_sensor.p.v' = z[6];\n  Real 'z_down_input' = z[7];\n  Real 'z_idealCommutingSwitch1.LossPower' = z[8];\n  Real 'z_idealCommutingSwitch1.n1.i' = z[9];\n  Real 'z_idealCommutingSwitch1.n2.i' = z[10];\n  Real 'z_idealCommutingSwitch1.s1' = z[11];\n  Real 'z_idealCommutingSwitch1.s2' = z[12];\n  Real 'z_idealCommutingSwitch2.LossPower' = z[13];\n  Real 'z_idealCommutingSwitch2.n1.i' = z[14];\n  Real 'z_idealCommutingSwitch2.n2.i' = z[15];\n  Real 'z_idealCommutingSwitch2.p.v' = z[16];\n  Real 'z_idealCommutingSwitch2.s1' = z[17];\n  Real 'z_idealCommutingSwitch2.s2' = z[18];\n  Real 'z_input_torque' = z[19];\n  Real 'z_motor.airGapDC.pin_ap.v' = z[20];\n  Real 'z_motor.airGapDC.vai' = z[21];\n  Real 'z_motor.airGapDC.vei' = z[22];\n  Real 'z_motor.brush.heatPort.Q_flow' = z[23];\n  Real 'z_motor.brush.lossPower' = z[24];\n  Real 'z_motor.brush.v' = z[25];\n  Real 'z_motor.compoundDCExcitation.pin_sen.i' = z[26];\n  Real 'z_motor.compoundDCExcitation.pin_sep.i' = z[27];\n  Real 'z_motor.compoundDCExcitation.vse' = z[28];\n  Real 'z_motor.core.Gc' = z[29];\n  Real 'z_motor.core.heatPort.Q_flow' = z[30];\n  Real 'z_motor.core.i' = z[31];\n  Real 'z_motor.core.lossPower' = z[32];\n  Real 'z_motor.core.n.i' = z[33];\n  Real 'z_motor.core.p.v' = z[34];\n  Real 'z_motor.core.v' = z[35];\n  Real 'z_motor.core.wLimit' = z[36];\n  Real 'z_motor.fixed.flange.tau' = z[37];\n  Real 'z_motor.friction.phi' = z[38];\n  Real 'z_motor.friction.tau' = z[39];\n  Real 'z_motor.friction.w' = z[40];\n  Real 'z_motor.ground.p.i' = z[41];\n  Real 'z_motor.ground.p.v' = z[42];\n  Real 'z_motor.groundSE.p.v' = z[43];\n  Real 'z_motor.inertiaRotor.a' = z[44];\n  Real 'z_motor.inertiaRotor.flange_b.tau' = z[45];\n  Real 'z_motor.inertiaStator.a' = z[46];\n  Real 'z_motor.inertiaStator.flange_a.tau' = z[47];\n  Real 'z_motor.inertiaStator.flange_b.tau' = z[48];\n  Real 'z_motor.inertiaStator.w' = z[49];\n  Real 'z_motor.internalSupport.tau' = z[50];\n  Real 'z_motor.internalThermalPort.heatPortArmature.Q_flow' = z[51];\n  Real 'z_motor.internalThermalPort.heatPortBrush.Q_flow' = z[52];\n  Real 'z_motor.internalThermalPort.heatPortCore.Q_flow' = z[53];\n  Real 'z_motor.internalThermalPort.heatPortExcitation.Q_flow' = z[54];\n  Real 'z_motor.internalThermalPort.heatPortFriction.Q_flow' = z[55];\n  Real 'z_motor.internalThermalPort.heatPortStrayLoad.Q_flow' = z[56];\n  Real 'z_motor.la.v' = z[57];\n  Real 'z_motor.lesigma.i' = z[58];\n  Real 'z_motor.lesigma.p.v' = z[59];\n  Real 'z_motor.lesigma.v' = z[60];\n  Real 'z_motor.powerBalance.lossPowerTotal' = z[61];\n  Real 'z_motor.powerBalance.powerArmature' = z[62];\n  Real 'z_motor.powerBalance.powerExcitation' = z[63];\n  Real 'z_motor.powerBalance.powerInertiaRotor' = z[64];\n  Real 'z_motor.powerBalance.powerInertiaStator' = z[65];\n  Real 'z_motor.powerBalance.powerMechanical' = z[66];\n  Real 'z_motor.ra.R_actual' = z[67];\n  Real 'z_motor.ra.v' = z[68];\n  Real 'z_motor.re.R_actual' = z[69];\n  Real 'z_motor.re.v' = z[70];\n  Real 'z_motor.strayLoad.flange.tau' = z[71];\n  Real 'z_motor.strayLoad.heatPort.Q_flow' = z[72];\n  Real 'z_motor.strayLoad.lossPower' = z[73];\n  Real 'z_motor.strayLoad.phi' = z[74];\n  Real 'z_motor.strayLoad.tau' = z[75];\n  Real 'z_motor.strayLoad.v' = z[76];\n  Real 'z_motor.strayLoad.w' = z[77];\n  Real 'z_motor.tauElectrical' = z[78];\n  Real 'z_motor.thermalAmbient.Q_flowArmature' = z[79];\n  Real 'z_motor.thermalAmbient.Q_flowExcitation' = z[80];\n  Real 'z_motor.thermalAmbient.Q_flowFriction' = z[81];\n  Real 'z_motor.thermalAmbient.Q_flowTotal' = z[82];\n  Real 'z_motor.thermalAmbient.temperatureBrush.port.T' = z[83];\n  Real 'z_motor.thermalAmbient.temperatureCore.port.T' = z[84];\n  Real 'z_motor.thermalAmbient.temperatureFriction.port.T' = z[85];\n  Real 'z_motor.thermalAmbient.temperatureStrayLoad.port.T' = z[86];\n  Real 'z_motor.va' = z[87];\n  Real 'z_motor.wMechanical' = z[88];\n  Real 'z_speed' = z[89];\n  Real 'z_speedSensor1.flange.phi' = z[90];\n  Real 'z_speedSensor1.flange.tau' = z[91];\n  Real 'z_torque1.phi_support' = z[92];\n  Real 'z_up_ground.p.i' = z[93];\n  Real 'z_up_ground.p.v' = z[94];\n  Real 'z_up_input' = z[95];\n  Real 'z_up_voltage.i' = z[96];\n  Real 'z_voltage_ground.p.i' = z[97];\n  Real 'z_voltage_ground.p.v' = z[98];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\n  z = Cz * x + Dz * u;\nend linear_PW__PowerSystem;\n";
}
#if defined(__cplusplus)
}
#endif

