model PW_Window
  Modelica.Blocks.Interfaces.RealInput speed_motor annotation(Placement(visible = true, transformation(origin = {-100, 50}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-80, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Mechanics.Rotational.Sources.Speed rotation(exact = true, phi(fixed = true, start = 0), useSupport = false) annotation(Placement(visible = true, transformation(origin = {-58, 50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Mechanics.Rotational.Components.Inertia window_worm(J = 0.08) annotation(Placement(visible = true, transformation(origin = {-28, 50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput window_torque_out annotation(Placement(visible = true, transformation(origin = {100, 52}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Mechanics.Rotational.Sensors.SpeedSensor window_rot_speed annotation(Placement(visible = true, transformation(origin = {38, 32}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Mechanics.Rotational.Sensors.AngleSensor window_angle annotation(Placement(visible = true, transformation(origin = {42, -18}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput window_speed_out annotation(Placement(visible = true, transformation(origin = {100, 10}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Math.Gain window_speed(k = 0.017) annotation(Placement(visible = true, transformation(origin = {74, 10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Math.Gain window_height(k = 0.017) annotation(Placement(visible = true, transformation(origin = {74, -40}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput window_height_out annotation(Placement(visible = true, transformation(origin = {100, -40}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Math.Gain window_torque(k = -0.4) annotation(Placement(visible = true, transformation(origin = {76, 52}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(window_rot_speed.w, window_speed.u) annotation(Line(points = {{49, 32}, {58, 32}, {58, 10}, {62, 10}}, color = {0, 0, 127}));
  connect(window_worm.flange_b, window_rot_speed.flange) annotation(Line(points = {{-18, 50}, {14, 50}, {14, 32}, {28, 32}}));
  connect(window_rot_speed.w, window_torque.u) annotation(Line(points = {{49, 32}, {58, 32}, {58, 52}, {64, 52}}, color = {0, 0, 127}));
  connect(window_torque.y, window_torque_out) annotation(Line(points = {{87, 52}, {100, 52}}, color = {0, 0, 127}));
  connect(window_worm.flange_b, window_angle.flange) annotation(Line(points = {{-18, 50}, {14, 50}, {14, -18}, {32, -18}}));
  connect(rotation.flange, window_worm.flange_a) annotation(Line(points = {{-48, 50}, {-38, 50}}));
  connect(speed_motor, rotation.w_ref) annotation(Line(points = {{-100, 50}, {-70, 50}}, color = {0, 0, 127}));
  connect(window_angle.phi, window_height.u) annotation(Line(points = {{54, -18}, {58, -18}, {58, -40}, {62, -40}, {62, -40}}, color = {0, 0, 127}));
  connect(window_height.y, window_height_out) annotation(Line(points = {{85, -40}, {100, -40}}, color = {0, 0, 127}));
  connect(window_speed.y, window_speed_out) annotation(Line(points = {{85, 10}, {100, 10}}, color = {0, 0, 127}));
  annotation(uses(Modelica(version = "3.2.1")));
end PW_Window;