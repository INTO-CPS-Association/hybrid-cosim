model PW_PowerSystem_Test
  PW_PowerSystem power annotation(Placement(visible = true, transformation(origin = {-20, 6}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  PW_Window window annotation(Placement(visible = true, transformation(origin = {10, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Obstacle obstacle annotation(Placement(visible = true, transformation(origin = {10, -28}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));
  Modelica.Blocks.Math.Add add1 annotation(Placement(visible = true, transformation(origin = {-20, -22}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Pulse up(nperiod = 1, period = 3.5, startTime = 0.0, width = 100)  annotation(Placement(visible = true, transformation(origin = {-66, 24}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Pulse down(nperiod = 1, period = 3, startTime = 3.55, width = 100) annotation(Placement(visible = true, transformation(origin = {-66, -14}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(down.y, power.down_input) annotation(Line(points = {{-54, -14}, {-42, -14}, {-42, 6}, {-26, 6}, {-26, 6}}, color = {0, 0, 127}));
  connect(up.y, power.up_input) annotation(Line(points = {{-54, 24}, {-38, 24}, {-38, 12}, {-26, 12}, {-26, 12}}, color = {0, 0, 127}));
  connect(obstacle.object_reaction, add1.u2) annotation(Line(points = {{-1, -28}, {-8, -28}}, color = {0, 0, 127}));
  connect(window.window_height_out, obstacle.in_height) annotation(Line(points = {{21, 5}, {34, 5}, {34, -28}, {18, -28}}, color = {0, 0, 127}));
  connect(window.window_torque_out, add1.u1) annotation(Line(points = {{21, -5}, {28, -5}, {28, -16}, {-8, -16}}, color = {0, 0, 127}));
  connect(power.speed, window.speed_motor) annotation(Line(points = {{-12, 0}, {2, 0}}, color = {0, 0, 127}));
  connect(add1.y, power.input_torque) annotation(Line(points = {{-32, -22}, {-38, -22}, {-38, 0}, {-26, 0}, {-26, 0}}, color = {0, 0, 127}));
  annotation(uses(Modelica(version = "3.2.1")), experiment(StartTime = 0, StopTime = 5, Tolerance = 0.0001, Interval = 0.0025));
end PW_PowerSystem_Test;