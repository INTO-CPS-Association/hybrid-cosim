model PowerAndWindowSystem
  
  // power params
  parameter Real J = 0.085;
  parameter Real b = 5;
  parameter Real K = 1.8;
  parameter Real R = 0.15;
  parameter Real L = 0.036;
  parameter Real V_abs = 12;
  
  // window params
  parameter Real wJ = 0.08;
  parameter Real wr = 0.017;
  parameter Real wb = 150;
  parameter Real wc = 1e3;
  
  // power vars
  Real V;
  Real theta;
  output Real i;
  Real omega;
  input Real u;
  input Real d;
  
  // window vars
  Real wtau;
  output Real wx;
  output Real wv;
  Real womega;
  Real wtheta;
  Real wfriction;
  
equation

  // power equations
  V = if u > 0.5 then V_abs 
      else if d > 0.5 then - V_abs
      else 0.0;
  der(omega) = (K * i + (- wtau) - b * omega) / J;
  L * der(i) = V - R * i - K * omega;
  der(theta) = omega;
  
  // window equations
  der(wtheta) = womega;
  wtau = wc * (theta - wtheta) - wfriction;
  der(womega) = wtau/wJ;
  wx = wr * wtheta;
  wv = wr * womega;
  wfriction = wb*wv;
  
annotation(
  experiment(StartTime = 0, StopTime = 1, Tolerance = 1e-6, Interval = 0.002)
);
end PowerAndWindowSystem;
