model Obstacle
  Modelica.Blocks.Interfaces.RealInput in_height annotation(Placement(visible = true, transformation(origin = {-100, 34}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-80, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Math.Add add1(k1 = -1)  annotation(Placement(visible = true, transformation(origin = {-50, 40}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.RealExpression realExpression1(y = 0.4)  annotation(Placement(visible = true, transformation(origin = {-86, 70}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput object_reaction annotation(Placement(visible = true, transformation(origin = {110, -8}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Logical.GreaterEqualThreshold greaterEqualThreshold1(threshold = 0)  annotation(Placement(visible = true, transformation(origin = {-18, -8}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Logical.Switch switch1 annotation(Placement(visible = true, transformation(origin = {76, -8}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.RealExpression realExpression2(y = 0.0) annotation(Placement(visible = true, transformation(origin = {30, -26}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Math.Gain gain1(k = -10e10)  annotation(Placement(visible = true, transformation(origin = {-2, 40}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(switch1.u1, gain1.y) annotation(Line(points = {{64, 0}, {34, 0}, {34, 40}, {8, 40}, {8, 40}, {10, 40}}, color = {0, 0, 127}));
  connect(realExpression2.y, switch1.u3) annotation(Line(points = {{42, -26}, {52, -26}, {52, -16}, {64, -16}, {64, -16}}, color = {0, 0, 127}));
  connect(switch1.y, object_reaction) annotation(Line(points = {{87, -8}, {110, -8}}, color = {0, 0, 127}));
  connect(greaterEqualThreshold1.y, switch1.u2) annotation(Line(points = {{-7, -8}, {64, -8}}, color = {255, 0, 255}));
  connect(add1.y, gain1.u) annotation(Line(points = {{-38, 40}, {-14, 40}, {-14, 40}, {-14, 40}}, color = {0, 0, 127}));
  connect(add1.y, greaterEqualThreshold1.u) annotation(Line(points = {{-38, 40}, {-36, 40}, {-36, -8}, {-30, -8}}, color = {0, 0, 127}));
  connect(in_height, add1.u2) annotation(Line(points = {{-100, 34}, {-62, 34}}, color = {0, 0, 127}));
  connect(realExpression1.y, add1.u1) annotation(Line(points = {{-74, 70}, {-68, 70}, {-68, 46}, {-62, 46}, {-62, 46}}, color = {0, 0, 127}));
  annotation(uses(Modelica(version = "3.2.2")));
end Obstacle;
