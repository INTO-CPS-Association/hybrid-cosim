model PowerSystemStandAlone
  parameter Real J = 0.01;
  parameter Real b = 0.1;
  parameter Real K = 0.01;
  parameter Real R = 1;
  parameter Real L = 0.5;
  parameter Real V = 12;
  Real theta;
  Real e;
  Real i;
  Real T;
  Real omega;
equation
  T = K * i;
  e = K * omega;
  J * der(omega) + b * omega = T;
  L * der(i) + R * i = V - e;
  der(theta) = omega;
annotation(
  experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-6, Interval = 0.002)
);
end PowerSystemStandAlone;
