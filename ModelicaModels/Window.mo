model Window
  parameter Real J = 0.08;
  parameter Real r = 0.017;
  parameter Real b = 150;
  parameter Real c = 1e5;
  input Real omega_input;
  input Real theta_input;
  output Real tau;
  output Real x;
  output Real v;
  output Real omega;
  output Real theta;
  output Real friction;
equation
  der(theta) = omega;
  tau = c * (theta_input - theta) - friction;
  //tau = c * (theta - theta_input);
  der(omega) = tau/J;
  x = r * theta;
  v = r * omega;
  friction = b*v;
annotation(
  experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-6, Interval = 0.002)
);
end Window;
