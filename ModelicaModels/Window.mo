model Window
  //parameter Real J = 0.01;
  parameter Real r = 0.11;
  parameter Real b = 10;
  //parameter Real c = 1e5;
  input Real omega_input;
  input Real theta_input;
  input Real obj_F;
  output Real tau;
  output Real x;
  output Real v;
  //output Real omega;
  //output Real theta;
  output Real friction;
equation
//der(theta) = omega;
//tau = c * (theta_input - theta) ; //- obj_F*r
  tau = obj_F * r + friction;
//der(omega) = (tau - friction)/J;
  x = r * theta_input;
  v = r * omega_input;
  friction = b * v;
  annotation(
    experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-06, Interval = 0.002));
end Window;
