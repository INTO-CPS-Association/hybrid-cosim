model PowerSystemStandAlone
  parameter Real J = 0.01;
  parameter Real b = 0.1;
  parameter Real K = 0.01;
  parameter Real R = 1;
  parameter Real L = 0.5;
  parameter Real V = 12;
  Real thetha;
  Real e;
  Real i;
  Real T;
  Real dthetha;
  input Real tau;
equation
  T = K * i;
  e = K * der(thetha);
  J * der(dthetha) + b * der(thetha) = T;
  L * der(i) + R * i = V - e;
  der(thetha) = dthetha;
end PowerSystemStandAlone;
