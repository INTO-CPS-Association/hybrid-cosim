model PowerSystem_Test
  PowerSystem power();
equation
  power.tau = if time < 4 then 0.0 else 100.0;
  power.u = if time < 0.5 then 0.0 else 1.0;
  power.d = 0.0;
annotation(
    experiment(StartTime = 0, StopTime = 6, Tolerance = 1e-06, Interval = 0.0024));end PowerSystem_Test;
