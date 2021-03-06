model Power
  parameter Real J = 0.085;
  parameter Real b = 5;
  parameter Real K = 7.45;
  parameter Real R = 0.15;
  parameter Real L = 0.036;
  parameter Real V_abs = 12;
  Real V;
  output Real displacement;
  output Real armature_current;
  output Real speed;
  input Real tau;
  input Real u;
  input Real d;
equation
  V = if u > 0.5 then V_abs 
      else if d > 0.5 then -V_abs
      else 0.0;
  J * der(speed) + b * speed = K * armature_current - tau;
  L * der(armature_current) + R * armature_current = V - K * speed;
  der(displacement) = speed;
annotation(
  experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-6, Interval = 0.002)
);
end Power;
