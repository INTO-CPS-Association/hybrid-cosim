from bokeh.plotting import figure, output_file, show
from sampleunits.PowerFMU import PowerFMU
import logging
from sampleunits.WindowFMU import WindowFMU
l = logging.getLogger()
l.setLevel(logging.DEBUG)

def env_up(time):
    return 1.0 if time < 6 else 0.0

def env_down(time):
    return 0.0 if time < 6 else 1.0

cosim_step_size = 0.001
num_internal_steps = 10
stop_time = 1.0;

power = PowerFMU("power", 1e-08, 1e-08, cosim_step_size/num_internal_steps, 
                     J=0.085, 
                     b=5, 
                     K=1.8, 
                     R=0.15, 
                     L=0.036,
                     V=12)

window = WindowFMU("window", 1e-08, 1e-08, cosim_step_size/num_internal_steps, 
                     J=0.085, 
                     r=0.017, 
                     b = 150, 
                     c = 1e3) # c = 1e5 makes this an unstable system.

power.enterInitMode()
window.enterInitMode()

# Solve initialisation.
# Notice the order in which the FMUs can be given inputs and obtained outputs.

power.setValues(0, 0, {power.i: 0.0,
                            power.omega: 0.0,
                            power.theta: 0.0,
                            power.up: env_up(0.0),
                            power.down: env_down(0.0)
                            })

pOut = power.getValues(0, 0, [power.omega, power.theta])

window.setValues(0, 0, {window.omega_input: pOut[power.omega],
                            window.theta_input: pOut[power.theta],
                            window.theta: 0.0,
                            window.omega: 0.0
                            })

wOut = window.getValues(0, 0, [window.tau])

power.setValues(0, 0, {power.tau: wOut[window.tau]})

power.exitInitMode()
window.exitInitMode()

trace_i = [0.0]
trace_omega = [0.0]
trace_x = [0.0]
times = [0.0]

time = 0.0

for step in range(1, int(stop_time / cosim_step_size) + 1):
    
    # set old values for window (this is not ideal)
    pOut = power.getValues(step-1, 0, [power.omega, power.theta, power.i])
    window.setValues(step, 0, {window.omega_input: pOut[power.omega],
                            window.theta_input: pOut[power.theta]})
    
    window.doStep(time, step, 0, cosim_step_size)
    
    wOut = window.getValues(step, 0, [window.tau, window.x])
    
    # Coupling equation
    power_tau = - wOut[window.tau]
    
    power.setValues(step, 0, {power.tau: power_tau,
                                  power.up: env_up(time),
                                  power.down: env_down(time)})
    
    power.doStep(time, step, 0, cosim_step_size)
    
    pOut = power.getValues(step, 0, [power.omega, power.theta, power.i])
    
    trace_omega.append(pOut[power.omega])
    trace_i.append(pOut[power.i])
    trace_x.append(wOut[window.x])
    time += cosim_step_size
    times.append(time)

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
p.line(x=times, y=trace_omega, legend="trace_omega", color=color_pallete[0])
p.line(x=times, y=trace_i, legend="trace_i", color=color_pallete[1])
show(p)

output_file("./results_x.html", title="Results")
p = figure(title="Plot", x_axis_label='time', y_axis_label='')
p.line(x=times, y=trace_x, legend="trace_x", color=color_pallete[2])
show(p)
