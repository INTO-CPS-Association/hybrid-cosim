model NoObstacle_Test
  PowerSystem power;
  Window window;
equation
  power.u = 1.0;
  power.d = 0.0;
  window.omega_input = power.omega;
  window.theta_input = power.theta;
  power.tau = - window.tau;
  annotation(
    experiment(StartTime = 0, StopTime = 2, Tolerance = 1e-07, Interval = 0.002));
end NoObstacle_Test;
