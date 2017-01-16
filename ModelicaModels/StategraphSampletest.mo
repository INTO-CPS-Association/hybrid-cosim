model StategraphSampletest
  StategraphSample stategraphSample1 annotation(
    Placement(visible = true, transformation(origin = {-10, 8}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Ramp ramp1 annotation(
    Placement(visible = true, transformation(origin = {-70, 10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(ramp1.y, stategraphSample1.u) annotation(
    Line(points = {{-58, 10}, {-18, 10}, {-18, 13}, {-16, 13}}, color = {0, 0, 127}));
  annotation(
    uses(Modelica(version = "3.2.2")));
end StategraphSampletest;
