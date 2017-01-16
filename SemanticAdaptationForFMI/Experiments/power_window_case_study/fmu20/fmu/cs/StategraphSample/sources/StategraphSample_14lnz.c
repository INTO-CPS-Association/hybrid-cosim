/* Linearization */
#include "StategraphSample_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

const char *StategraphSample_linear_model_frame()
{
  return "model linear_StategraphSample\n  parameter Integer n = 0; // states\n  parameter Integer k = 1; // top-level inputs\n  parameter Integer l = 1; // top-level outputs\n"
  "  parameter Real x0[0] = {%s};\n"
  "  parameter Real u0[1] = {%s};\n"
  "  parameter Real A[0,0] = zeros(0,0);%s\n"
  "  parameter Real B[0,1] = zeros(0,1);%s\n"
  "  parameter Real C[1,0] = zeros(1,0);%s\n"
  "  parameter Real D[1,1] = [%s];\n"
  "  Real x[0];\n"
  "  input Real u[1](start= u0);\n"
  "  output Real y[1];\n"
  "\n    Real 'u_u' = u[1];\n  Real 'y_y' = y[1];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\nend linear_StategraphSample;\n";
}
const char *StategraphSample_linear_model_datarecovery_frame()
{
  return "model linear_StategraphSample\n  parameter Integer n = 0; // states\n  parameter Integer k = 1; // top-level inputs\n  parameter Integer l = 1; // top-level outputs\n  parameter Integer nz = 13; // data recovery variables\n"
  "  parameter Real x0[0] = {%s};\n"
  "  parameter Real u0[1] = {%s};\n"
  "  parameter Real z0[13] = {%s};\n"
  "  parameter Real A[0,0] = zeros(0,0);%s\n"
  "  parameter Real B[0,1] = zeros(0,1);%s\n"
  "  parameter Real C[1,0] = zeros(1,0);%s\n"
  "  parameter Real D[1,1] = [%s];\n"
  "  parameter Real Cz[13,0] = zeros(13,0);%s\n"
  "  parameter Real Dz[13,1] = [%s];\n"
  "  Real x[0];\n"
  "  input Real u[1](start= u0);\n"
  "  output Real y[1];\n"
  "  output Real z[13];\n"
  "\n  Real 'u_u' = u[1];\n  Real 'y_y' = y[1];\n  Real 'z_realExpression1.y' = z[1];\n  Real 'z_realExpression2.y' = z[2];\n  Real 'z_s1.outerStatePort.subgraphStatePort.activeSteps' = z[3];\n  Real 'z_stateGraphRoot.subgraphStatePort.activeSteps' = z[4];\n  Real 'z_stateGraphRoot.subgraphStatePort.activeStepsDummy' = z[5];\n  Real 'z_step1.outerStatePort.subgraphStatePort.activeSteps' = z[6];\n  Real 'z_t1.t' = z[7];\n  Real 'z_t1.t_dummy' = z[8];\n  Real 'z_t1.t_start' = z[9];\n  Real 'z_t2.t' = z[10];\n  Real 'z_t2.t_dummy' = z[11];\n  Real 'z_u' = z[12];\n  Real 'z_y' = z[13];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\n  z = Cz * x + Dz * u;\nend linear_StategraphSample;\n";
}
#if defined(__cplusplus)
}
#endif

