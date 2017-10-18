model Obstacle
  parameter Real c = 1e10;
  parameter Real fixed_x = 0.45;
  input Real disp;
  output Real reaction_force;
  Real compression;
equation
  compression = disp - fixed_x;
  reaction_force = if disp > fixed_x then c * compression else 0;
  annotation(
    experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-06, Interval = 0.002));
end Obstacle;
