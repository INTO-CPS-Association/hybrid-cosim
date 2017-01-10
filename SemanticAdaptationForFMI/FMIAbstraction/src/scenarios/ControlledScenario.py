import logging

from bokeh.plotting import figure, output_file, show

from sampleunits.DriverControllerStatechartFMU import DriverControllerStatechartFMU
from sampleunits.EnvironmentStatechartFMU import EnvironmentStatechartFMU
from sampleunits.InacurateControllerArmatureAdaptation import InacurateControllerArmatureAdaptation
from sampleunits.ObstacleFMU import ObstacleFMU
from sampleunits.PowerFMU import PowerFMU
from sampleunits.PowerInputAdaptation import PowerInputAdaptation
from sampleunits.WindowFMU import WindowFMU


NUM_RTOL = 1e-08
NUM_ATOL = 1e-08

l = logging.getLogger()
l.setLevel(logging.DEBUG)

cosim_step_size = 0.001
num_internal_steps = 10
stop_time = 6.0;

environment = EnvironmentStatechartFMU("env", NUM_RTOL, NUM_ATOL)

controller = DriverControllerStatechartFMU("controller", NUM_RTOL, NUM_ATOL)

power = PowerFMU("power", NUM_RTOL, NUM_ATOL, cosim_step_size/num_internal_steps, 
                     J=0.085, 
                     b=5, 
                     K=1.8, 
                     R=0.15, 
                     L=0.036,
                     V=12)

armature_threshold = 30.0
adapt_armature = InacurateControllerArmatureAdaptation("arm_adapt", NUM_RTOL, NUM_ATOL, armature_threshold, True)

adapt_power_input = PowerInputAdaptation("power_adapt")

window_radius = 0.017

window = WindowFMU("window", NUM_RTOL, NUM_ATOL, cosim_step_size/num_internal_steps, 
                     J=0.085, 
                     r=window_radius, 
                     b = 150, 
                     c = 1e3) # c = 1e5 makes this an unstable system.

obstacle = ObstacleFMU("obstacle", NUM_RTOL, NUM_ATOL, cosim_step_size/num_internal_steps, 
                     c=1e5, 
                     fixed_x=0.45)

environment.enterInitMode()
controller.enterInitMode()
power.enterInitMode()
adapt_armature.enterInitMode()
adapt_power_input.enterInitMode()
window.enterInitMode()
obstacle.enterInitMode()

# Solve initialisation.
"""
The initialisation may impose a completely different order for the execution of the FMUs.
In this case we know that there is no direct feed-through between the power input and its outputs,
    so we can safely set its initial state, get its output, and then compute all the other FMUs,
    before setting the new inputs to the power.
"""

pOut = power.setValues(0, 0, {
                                 power.omega: 0.0, 
                                 power.theta: 0.0, 
                                 power.i: 0.0
                                 })
pOut = power.getValues(0, 0, [power.omega, power.theta, power.i])

window.setValues(0, 0, {window.omega_input: pOut[power.omega],
                            window.theta_input: pOut[power.theta],
                            window.theta: 0.0,
                            window.omega: 0.0
                            })
wOut = window.getValues(0, 0, [window.tau, window.x])

obstacle.setValues(0, 0, {obstacle.x: wOut[window.x]})
oOut = obstacle.getValues(0, 0, [obstacle.F])


adapt_armature.setValues(0, 0, {adapt_armature.armature_current: pOut[power.i]})

adaptArmOut = adapt_armature.getValues(0, 0, [adapt_armature.out_event])

envOut = environment.getValues(0, 0, [environment.out_event])

# coupling equation for the input event of the controller
controller_in = adaptArmOut[adapt_armature.out_event] + envOut[environment.out_event]
if adaptArmOut[adapt_armature.out_event] != "" and envOut[environment.out_event] != "":
    controller_in = adaptArmOut[adapt_armature.out_event]
controller.setValues(0, 0, {controller.in_event : controller_in})

cOut = controller.getValues(0, 0, [controller.out_event])

adapt_power_input.setValues(0, 0, {adapt_power_input.in_event : cOut[controller.out_event]})
adaptPowerOut = adapt_power_input.getValues(0, 0, [adapt_power_input.out_up, adapt_power_input.out_down])

# Coupling equation for power
power_tau = - ( wOut[window.tau] + window_radius * oOut[obstacle.F])

# Finally set the other power inputs
power.setValues(0, 0, {power.tau: power_tau, 
                       power.up: adaptPowerOut.out_up,
                       power.down: adaptPowerOut.out_down})


environment.exitInitMode()
controller.exitInitMode()
power.exitInitMode()
adapt_armature.exitInitMode()
adapt_power_input.exitInitMode()
window.exitInitMode()
obstacle.exitInitMode()

trace_i = [0.0]
trace_omega = [0.0]
trace_x = [0.0]
trace_F = [0.0]
times = [0.0]

time = 0.0

for step in range(1, int(stop_time / cosim_step_size) + 1):
    
    pOut = power.getValues(step, 0, [power.omega, power.theta, power.i])
    
    window.setValues(step, 0, {window.omega_input: pOut[power.omega],
                            window.theta_input: pOut[power.theta],
                            window.theta: 0.0,
                            window.omega: 0.0
                            })
    wOut = window.getValues(step, 0, [window.tau, window.x])
    
    obstacle.setValues(step, 0, {obstacle.x: wOut[window.x]})
    oOut = obstacle.getValues(step, 0, [obstacle.F])
    
    adapt_armature.setValues(step, 0, {adapt_armature.armature_current: pOut[power.i]})

    adaptArmOut = adapt_armature.getValues(step, 0, [adapt_armature.out_event])
    
    envOut = environment.getValues(step, 0, [environment.out_event])
    
    # coupling equation for the input event of the controller
    controller_in = adaptArmOut[adapt_armature.out_event] + envOut[environment.out_event]
    if adaptArmOut[adapt_armature.out_event] != "" and envOut[environment.out_event] != "":
        controller_in = adaptArmOut[adapt_armature.out_event]
    controller.setValues(step, 0, {controller.in_event : controller_in})
    
    cOut = controller.getValues(step, 0, [controller.out_event])
    
    adapt_power_input.setValues(step, 0, {adapt_power_input.in_event : cOut[controller.out_event]})
    adaptPowerOut = adapt_power_input.getValues(step, 0, [adapt_power_input.out_up, adapt_power_input.out_down])
    
    # Coupling equation for power
    power_tau = - ( wOut[window.tau] + window_radius * oOut[obstacle.F])
    
    # Finally set the other power inputs
    power.setValues(step, 0, {power.tau: power_tau, 
                           power.up: adaptPowerOut.out_up,
                           power.down: adaptPowerOut.out_down})
    
    trace_omega.append(pOut[power.omega])
    trace_i.append(pOut[power.i])
    trace_x.append(wOut[window.x])
    trace_F.append(oOut[obstacle.F])
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

output_file("./results_F.html", title="Results")
p = figure(title="Plot", x_axis_label='time', y_axis_label='')
p.line(x=times, y=trace_F, legend="trace_F", color=color_pallete[3])
show(p)
