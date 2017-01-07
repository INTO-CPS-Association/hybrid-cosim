model Obstacle
  parameter Real c = 1e5;
  parameter Real fixed_x = 0.45;
  input Real x;
  output Real F;
equation
  F = if x > fixed_x then c*(x - fixed_x) else 0;
annotation(
  experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-6, Interval = 0.002)
);
end Obstacle;
