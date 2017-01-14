model UncontrolledScenario
  PowerSystem power();
  Window window();
  Obstacle obstacle();
equation
  power.u = 1.0;
  power.d = 0.0;
  window.omega_input = power.omega;
  window.theta_input = power.theta;
  window.obj_F = obstacle.F;
  power.tau = window.tau;
  obstacle.x = window.x;
  annotation(
    experiment(StartTime = 0, StopTime = 6, Tolerance = 1e-06, Interval = 0.0024),
    __OpenModelica_simulationFlags(jacobian = "coloredNumerical", s = "dassl", lv = "LOG_STATS"));
end UncontrolledScenario;
