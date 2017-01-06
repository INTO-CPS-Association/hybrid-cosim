model PowerSystem_Test
  PowerSystem power();
equation
  power.tau = 0.0;
  power.u = if time < 0.5 then 0.0 else 1.0;
  power.d = 0.0;
end PowerSystem_Test;
