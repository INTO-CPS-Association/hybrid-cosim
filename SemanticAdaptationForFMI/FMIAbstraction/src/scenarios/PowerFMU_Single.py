from bokeh.plotting import figure, output_file, show
from sampleunits.PowerFMU import PowerFMU
import logging
l = logging.getLogger()
l.setLevel(logging.DEBUG)

power_fmu = PowerFMU("power", 1e-08, 1e-05, 0.001, J=0.01, b=0.1, K=0.01, R=1, L=0.5, V=12)

power_fmu.enterInitMode()

power_fmu.setValues(0, 0, {power_fmu.i: 0.0,
                            power_fmu.omega: 0.0,
                            power_fmu.theta: 0.0,
                            power_fmu.tau: 0.0
                            })

power_fmu.exitInitMode()

cosim_step_size = 0.01;
time = 0.0

l.debug("cosim_step_size=%f", cosim_step_size)

trace_i = [0.0]
trace_omega = [0.0]
times = [0.0]

for step in range(1, int(1 / cosim_step_size) + 1):
    power_fmu.setValues(step, 0, {power_fmu.tau: 0.0})
    power_fmu.doStep(time, step, 0, cosim_step_size)
    values = power_fmu.getValues(step, 0, [power_fmu.omega, power_fmu.i])
    times.append(time)
    trace_omega.append(values[power_fmu.omega])
    trace_i.append(values[power_fmu.i])
    time += step

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
