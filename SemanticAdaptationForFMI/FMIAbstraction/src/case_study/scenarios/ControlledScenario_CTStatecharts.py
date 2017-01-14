"""
In this scenario, the controller is a statchart that receives events at his input.
The main semantic adaptation is getting the continuous armature signal coming from the power system,
and converting it into an event.
"""

import logging

from bokeh.plotting import figure, output_file, show

from case_study.units.adaptations.InacurateControllerArmatureAdaptation_CT import InacurateControllerArmatureAdaptation_CT
from case_study.units.ct_based.ObstacleFMU import ObstacleFMU
from case_study.units.ct_based.PowerFMU import PowerFMU
from case_study.units.ct_based.WindowFMU import WindowFMU
from case_study.units.de_based.DriverControllerStatechartFMU_CTInOut import DriverControllerStatechartFMU_CTInOut
from case_study.units.de_based.EnvironmentStatechartFMU_CTInOut import EnvironmentStatechartFMU_CTInOut

NUM_RTOL = 1e-08
NUM_ATOL = 1e-08

l = logging.getLogger()
l.setLevel(logging.DEBUG)

cosim_step_size = 0.001
num_internal_steps = 1
stop_time = 6;

environment = EnvironmentStatechartFMU_CTInOut("env", NUM_RTOL, NUM_ATOL)

controller = DriverControllerStatechartFMU_CTInOut("controller", NUM_RTOL, NUM_ATOL)

power = PowerFMU("power", NUM_RTOL, NUM_ATOL, cosim_step_size/num_internal_steps, 
                     J=0.085, 
                     b=5, 
                     K=7.45, 
                     R=0.15, 
                     L=0.036,
                     V_a=12)

armature_threshold = 5
adapt_armature = InacurateControllerArmatureAdaptation_CT("arm_adapt", NUM_RTOL, NUM_ATOL, armature_threshold, True)

window = WindowFMU("window", NUM_RTOL, NUM_ATOL, cosim_step_size/num_internal_steps,
                     r=0.11, 
                     b = 10)

obstacle = ObstacleFMU("obstacle", NUM_RTOL, NUM_ATOL, cosim_step_size/num_internal_steps, 
                     c=1e5, 
                     fixed_x=0.45)

environment.enterInitMode()
controller.enterInitMode()
power.enterInitMode()
adapt_armature.enterInitMode()
window.enterInitMode()
obstacle.enterInitMode()

# Solve initialisation.
"""
The initialisation may impose a completely different order for the execution of the FMUs.
In this case we know that there is no direct feed-through between the power input and its outputs,
    so we can safely set its initial state, get its output, and then compute all the other FMUs,
    before setting the new inputs to the power.
There is also a tight coupling between the window and the obstacle FMU but we 
    know what the initial force is, so we can use that to set the inputs and outputs in the right order,
    without having to do a fixed point iteration.
    But in the general case, we would need a fixed point iteration.
"""

power.setValues(0, 0, {
                                 power.omega: 0.0, 
                                 power.theta: 0.0, 
                                 power.i: 0.0
                                 })
pOut = power.getValues(0, 0, [power.omega, power.theta, power.i])

window.setValues(0, 0, {window.omega_input: pOut[power.omega],
                            window.theta_input: pOut[power.theta],
                            })
wOut = window.getValues(0, 0, [window.x])

obstacle.setValues(0, 0, {obstacle.x: wOut[window.x]})
oOut = obstacle.getValues(0, 0, [obstacle.F])

window.setValues(0, 0, {window.F_obj: oOut[obstacle.F]})
wOut = window.getValues(0, 0, [window.tau])

adapt_armature.setValues(0, 0, {adapt_armature.armature_current: pOut[power.i],
                                adapt_armature.out_obj: 0.0 })

adaptArmOut = adapt_armature.getValues(0, 0, [adapt_armature.out_obj])

envOut = environment.getValues(0, 0, [environment.out_up, environment.out_down])

controller.setValues(0, 0, {controller.in_dup : envOut[environment.out_up],
                            controller.in_ddown : envOut[environment.out_down],
                            controller.in_obj : adaptArmOut[adapt_armature.out_obj]})

cOut = controller.getValues(0, 0, [controller.out_up, controller.out_down])

# Finally set the other power inputs
power.setValues(0, 0, {power.tau: wOut[window.tau], 
                       power.up: cOut[controller.out_up],
                       power.down: cOut[controller.out_down]})

environment.exitInitMode()
controller.exitInitMode()
power.exitInitMode()
adapt_armature.exitInitMode()
window.exitInitMode()
obstacle.exitInitMode()

trace_i = [0.0]
trace_omega = [0.0]
trace_x = [0.0]
trace_F = [0.0]
times = [0.0]

time = 0.0

iteration = 0 # For now this is always zero

for step in range(1, int(stop_time / cosim_step_size) + 1):
    
    # Note that despite the fact that there is no feedthrough between 
    # the inputs and the outputs of the power system, 
    # the internal solver would still benefit from an up-to-date 
    # value given for the inputs. However, that creates an algebraic loop, 
    # so for now, we just get old values for the inputs.
    
    # Compute environment
    environment.doStep(time, step, iteration, cosim_step_size) 
    envOut = environment.getValues(step, iteration, [environment.out_up, environment.out_down])
    
    # Get delayed output from power, to break the algebraic loop.
    pOut = power.getValues(step-1, iteration, [power.omega, power.theta, power.i])
    
    # Compute armature
    adapt_armature.setValues(step, iteration, {adapt_armature.armature_current: pOut[power.i]})
    adapt_armature.doStep(time, step, iteration, cosim_step_size) 
    adaptArmOut = adapt_armature.getValues(step, iteration, [adapt_armature.out_obj])
    
    # Compute controller
    controller.setValues(step, iteration, {controller.in_dup : envOut[environment.out_up],
                            controller.in_ddown : envOut[environment.out_down],
                            controller.in_obj : adaptArmOut[adapt_armature.out_obj]})
    controller.doStep(time, step, iteration, cosim_step_size) 
    cOut = controller.getValues(step, iteration, [controller.out_up, controller.out_down])
    
    # Get delayed outputs from window, to break the algebraic loop it was with the obstacle.
    wOut = window.getValues(step-1, iteration, [window.tau, window.x])
    
    # Compute obstacle
    obstacle.setValues(step, iteration, {obstacle.x: wOut[window.x]})
    obstacle.doStep(time, step, iteration, cosim_step_size) 
    oOut = obstacle.getValues(step, iteration, [obstacle.F])
    
    # Compute the window, with the delayed inputs from the power
    window.setValues(step, iteration, {window.omega_input: pOut[power.omega],
                                       window.theta_input: pOut[power.theta],
                                       window.F_obj: oOut[obstacle.F]
                            })
    window.doStep(time, step, iteration, cosim_step_size) 
    wOut = window.getValues(step, iteration, [window.tau, window.x])
    
    # Compute the power
    power.setValues(step, iteration, {power.tau: wOut[window.tau], 
                           power.up: cOut[controller.out_up],
                           power.down: cOut[controller.out_down]})
    
    power.doStep(time, step, iteration, cosim_step_size)
    pOut = power.getValues(step, iteration, [power.omega, power.theta, power.i])
    
    """
    Here is where we would compute the inputs that were previously delays and
    repeat the step if these were too different.
    """
    
    # Update the delayed inputs
    
    """
    adapt_armature.setValues(step, iteration, {adapt_armature.armature_current: pOut[power.i]})
    
    window.setValues(step, iteration, {window.omega_input: pOut[power.omega],
                                       window.theta_input: pOut[power.theta]})
    
    obstacle.setValues(step, iteration, {obstacle.x: wOut[window.x]})
    """
    
    
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
