model PW_PowerSystem_Test
  Modelica.Blocks.Sources.Step step1(startTime = 1)  annotation(Placement(visible = true, transformation(origin = {-66, 18}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Constant const(k = 0)  annotation(Placement(visible = true, transformation(origin = {-66, -14}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  PW_PowerSystem pW_PowerSystem1 annotation(Placement(visible = true, transformation(origin = {-10, -10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Math.Gain window_friction(k = -100)  annotation(Placement(visible = true, transformation(origin = {-12, -40}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));
equation
  connect(window_friction.y, pW_PowerSystem1.input_torque) annotation(Line(points = {{-24, -40}, {-34, -40}, {-34, -16}, {-16, -16}, {-16, -16}}, color = {0, 0, 127}));
  connect(pW_PowerSystem1.speed, window_friction.u) annotation(Line(points = {{-2, -14}, {16, -14}, {16, -40}, {0, -40}, {0, -40}, {0, -40}}, color = {0, 0, 127}));
  connect(const.y, pW_PowerSystem1.down_input) annotation(Line(points = {{-54, -14}, {-30, -14}, {-30, -10}, {-16, -10}, {-16, -10}}, color = {0, 0, 127}));
  connect(step1.y, pW_PowerSystem1.up_input) annotation(Line(points = {{-54, 18}, {-24, 18}, {-24, -4}, {-16, -4}, {-16, -4}}, color = {0, 0, 127}));
  annotation(uses(Modelica(version = "3.2.1")), experiment(StartTime = 0, StopTime = 8, Tolerance = 0.0001, Interval = 0.004));
end PW_PowerSystem_Test;