model NoObstacle_Test
  PowerSystem power;
  Window window;
equation
  power.u = 1.0;
  power.d = 0.0;
  window.speed = power.omega;
  window.displacement = power.theta;
  power.tau = - window.tau;
  annotation(
    experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-06, Interval = 0.001));
end NoObstacle_Test;
