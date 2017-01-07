model UncontrolledScenario
  PowerSystem power();
  Window window();
  Obstacle obstacle();
equation
  power.u = 1.0;
  power.d = 0.0;
  window.omega_input = power.omega;
  window.theta_input = power.theta;
  power.tau = -(window.tau + obstacle.F*window.r);
  obstacle.x = window.x;
  annotation(
    experiment(StartTime = 0, StopTime = 10, Tolerance = 1e-06, Interval = 0.004));
end UncontrolledScenario;
