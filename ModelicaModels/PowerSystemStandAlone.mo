model PowerSystemStandAlone
  PowerSystem power;
equation
  power.tau = 0;
  power.u = 0;
  power.d = 1;
annotation(
  experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-6, Interval = 0.002)
);
end PowerSystemStandAlone;
