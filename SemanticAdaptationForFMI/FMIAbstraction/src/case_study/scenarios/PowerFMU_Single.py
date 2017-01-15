import logging

from bokeh.plotting import figure, output_file, show

from case_study.units.ct_based.PowerFMU import PowerFMU


l = logging.getLogger()
l.setLevel(logging.DEBUG)

def env_up(time):
    return 1.0 if time < 6 else 0.0

def env_down(time):
    return 0.0 if time < 6 else 1.0

power = PowerFMU("power", 1e-08, 1e-05, 0.001, 
                     J=0.085, 
                     b=5, 
                     K=1.8, 
                     R=0.15, 
                     L=0.036,
                     V_a=12)

power.enterInitMode()

power.setValues(0, 0, {power.i: 0.0,
                            power.omega: 0.0,
                            power.theta: 0.0,
                            power.tau: 0.0,
                            power.up: env_up(0.0),
                            power.down: env_down(0.0)
                            })

power.exitInitMode()


trace_i = [0.0]
trace_omega = [0.0]
times = [0.0]

START_STEP_SIZE = 0.01;
STOP_TIME = 10.0;
time = 0.0
l.debug("START_STEP_SIZE=%f", START_STEP_SIZE)

for step in range(1, int(STOP_TIME / START_STEP_SIZE) + 1):
    power.setValues(step, 0, {power.tau: 0.0,
                                  power.up: env_up(time),
                                  power.down: env_down(time)})
    power.doStep(time, step, 0, START_STEP_SIZE)
    values = power.getValues(step, 0, [power.omega, power.i])
    times.append(time)
    trace_omega.append(values[power.omega])
    trace_i.append(values[power.i])
    time += START_STEP_SIZE

color_pallete = [
                "#e41a1c",
                "#377eb8",
                "#4daf4a",
                "#984ea3",
                "#ff7f00",
                "#ffff33",
                "#a65628",
                "#f781bf"
                 ]

output_file("./results.html", title="Results")
p = figure(title="Plot", x_axis_label='time', y_axis_label='')
p.line(x=range(len(trace_omega)), y=trace_omega, legend="trace_omega", color=color_pallete[0])
p.line(x=range(len(trace_i)), y=trace_i, legend="trace_i", color=color_pallete[1])
show(p)
