model PowerAndWindowSystem_Test
  PowerAndWindowSystem powerAndWindow;
equation
  powerAndWindow.u = 1.0;
  powerAndWindow.d = 0.0;
  annotation(
    experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-06, Interval = 0.002));
end PowerAndWindowSystem_Test;
