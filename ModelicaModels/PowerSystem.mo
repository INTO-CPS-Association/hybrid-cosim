model PowerSystem
  parameter Real J = 0.085;
  parameter Real b = 5;
  parameter Real K = 1.8;
  parameter Real R = 0.15;
  parameter Real L = 0.036;
  parameter Real V_abs = 12;
  Real V;
  output Real theta;
  output Real i;
  output Real omega;
  input Real tau;
  input Real u;
  input Real d;
equation
  V = if u > 0.5 then V_abs 
      else if d > 0.5 then - V_abs
      else 0.0;
  der(omega) = (K * i + tau - b * omega) / J;
  L * der(i) = V - R * i - K * omega;
  der(theta) = omega;
annotation(
  experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-6, Interval = 0.002)
);
end PowerSystem;
