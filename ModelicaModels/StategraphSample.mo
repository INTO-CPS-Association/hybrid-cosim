model StategraphSample
  Modelica.Blocks.Interfaces.RealInput u annotation(
    Placement(visible = true, transformation(origin = {-100, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-58, 46}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.StateGraph.InitialStepWithSignal s1 annotation(
    Placement(visible = true, transformation(origin = {-22, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.StateGraph.Transition t1(condition = u > 0.5, waitTime = 0)  annotation(
    Placement(visible = true, transformation(origin = {4, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.StateGraph.Transition t2(enableTimer = true, waitTime = 1)  annotation(
    Placement(visible = true, transformation(origin = {0, 40}, extent = {{-10, -10}, {10, 10}}, rotation = 180)));
  inner Modelica.StateGraph.StateGraphRoot stateGraphRoot annotation(
    Placement(visible = true, transformation(origin = {-66, 64}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Logical.Switch switch1 annotation(
    Placement(visible = true, transformation(origin = {-22, -40}, extent = {{-10, -10}, {10, 10}}, rotation = -90)));
  Modelica.Blocks.Sources.RealExpression realExpression1(y = 0.0)  annotation(
    Placement(visible = true, transformation(origin = {14, -24}, extent = {{-10, -10}, {10, 10}}, rotation = 180)));
  Modelica.Blocks.Sources.RealExpression realExpression2(y = 1) annotation(
    Placement(visible = true, transformation(origin = {-54, -24}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput y annotation(
    Placement(visible = true, transformation(origin = {50, -48}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {56, -30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.StateGraph.Step step1 annotation(
    Placement(visible = true, transformation(origin = {32, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(step1.outPort[1], t2.inPort) annotation(
    Line(points = {{42, 0}, {48, 0}, {48, 40}, {4, 40}, {4, 40}}));
  connect(t1.outPort, step1.inPort[1]) annotation(
    Line(points = {{6, 0}, {20, 0}, {20, 0}, {20, 0}}));
  connect(switch1.y, y) annotation(
    Line(points = {{-22, -52}, {-22, -52}, {-22, -48}, {50, -48}, {50, -48}}, color = {0, 0, 127}));
  connect(s1.active, switch1.u2) annotation(
    Line(points = {{-22, -12}, {-22, -12}, {-22, -28}, {-22, -28}}, color = {255, 0, 255}));
  connect(realExpression1.y, switch1.u1) annotation(
    Line(points = {{2, -24}, {-14, -24}, {-14, -28}, {-14, -28}}, color = {0, 0, 127}));
  connect(realExpression2.y, switch1.u3) annotation(
    Line(points = {{-42, -24}, {-30, -24}, {-30, -28}, {-30, -28}}, color = {0, 0, 127}));
  connect(s1.outPort[1], t1.inPort) annotation(
    Line(points = {{-12, 0}, {0, 0}, {0, 0}, {0, 0}}));
  connect(t2.outPort, s1.inPort[1]) annotation(
    Line(points = {{-2, 40}, {-60, 40}, {-60, 0}, {-34, 0}, {-34, 0}}));
  annotation(
    uses(Modelica(version = "3.2.2")));
end StategraphSample;
