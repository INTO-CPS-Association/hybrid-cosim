model Window
  parameter Real r = 0.11;
  parameter Real b = 10;
  input Real speed;
  input Real displacement;
  input Real reaction_force;
  output Real reaction_torque;
  output Real height;
  Real v;
  output Real friction;
equation
  reaction_torque = reaction_force * r + friction;
  height = r * displacement;
  v = r * speed;
  friction = b * v;
  annotation(
    experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-06, Interval = 0.002));
end Window;
