"""
In this scenario, the controller is a statchart that receives events at his input.
The main semantic adaptation is getting the continuous armature signal coming from the power system,
and converting it into an event.
"""

import logging

from bokeh.plotting import figure, output_file, show

from case_study.units.adaptations.InacurateControllerArmatureAdaptation_Event import InacurateControllerArmatureAdaptation_Event
from case_study.units.adaptations.PowerInputAdaptation_Event import PowerInputAdaptation_Event
from case_study.units.ct_based.ObstacleFMU import ObstacleFMU
from case_study.units.ct_based.PowerFMU import PowerFMU
from case_study.units.ct_based.WindowFMU import WindowFMU
from case_study.units.de_based.DriverControllerStatechartFMU_Event import DriverControllerStatechartFMU_Event
from case_study.units.de_based.EnvironmentStatechartFMU_Event import EnvironmentStatechartFMU_Event


NUM_RTOL = 1e-08
NUM_ATOL = 1e-08

l = logging.getLogger()
l.setLevel(logging.DEBUG)

START_STEP_SIZE = 0.001
FMU_START_RATE = 10
STOP_TIME = 10;

environment = EnvironmentStatechartFMU_Event("env", NUM_RTOL, NUM_ATOL)

controller = DriverControllerStatechartFMU_Event("controller", NUM_RTOL, NUM_ATOL)

power = PowerFMU("power", NUM_RTOL, NUM_ATOL, START_STEP_SIZE/FMU_START_RATE, 
                     J=0.085, 
                     b=5, 
                     K=1.8, 
                     R=0.15, 
                     L=0.036,
                     V_a=12)

armature_threshold = 20.0
adapt_armature = InacurateControllerArmatureAdaptation_Event("arm_adapt", NUM_RTOL, NUM_ATOL, armature_threshold, True)

adapt_power_input = PowerInputAdaptation_Event("power_adapt")


window = WindowFMU("window", NUM_RTOL, NUM_ATOL, START_STEP_SIZE/FMU_START_RATE, 
                     J=0.085, 
                     r=0.017, 
                     b = 150, 
                     c = 1e3) # c = 1e5 makes this an unstable system.

obstacle = ObstacleFMU("obstacle", NUM_RTOL, NUM_ATOL, START_STEP_SIZE/FMU_START_RATE, 
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
There is also a tight coupling between the window and the obstacle FMU but we 
    know what the initial force is, so we can use that to set the inputs and outputs in the right order,
    without having to do a fixed point iteration.
    But in the general case, we would need a fixed point iteration.
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
wOut = window.getValues(0, 0, [window.x])

obstacle.setValues(0,0, {obstacle.x: wOut[window.x]})
oOut = obstacle.getValues(0, 0, [obstacle.F])

window.setValues(0, 0, {window.F_obj: oOut[obstacle.F]})
wOut = window.getValues(0, 0, [window.tau])

adapt_armature.setValues(0, 0, {adapt_armature.armature_current: pOut[power.i],
                                adapt_armature.out_event: "" })

adaptArmOut = adapt_armature.getValues(0, 0, [adapt_armature.out_event])

environment.setValues(0, 0, {environment.__current_state : "Neutral",
                             environment.out_event : ""})
envOut = environment.getValues(0, 0, [environment.out_event])

# coupling equation for the input event of the controller
controller_in = adaptArmOut[adapt_armature.out_event] + envOut[environment.out_event]
if adaptArmOut[adapt_armature.out_event] != "" and envOut[environment.out_event] != "":
    controller_in = adaptArmOut[adapt_armature.out_event]
controller.setValues(0, 0, {controller.in_event : controller_in,
                            controller.__current_state: "Neutral",
                            controller.out_event: ""})

cOut = controller.getValues(0, 0, [controller.out_event])

adapt_power_input.setValues(0, 0, {adapt_power_input.in_event : cOut[controller.out_event],
                                   adapt_power_input.out_down: 0.0,
                                   adapt_power_input.out_up: 0.0})

adaptPowerOut = adapt_power_input.getValues(0, 0, [adapt_power_input.out_up, adapt_power_input.out_down])

# Finally set the other power inputs
power.setValues(0, 0, {power.tau: wOut[window.tau], 
                       power.up: adaptPowerOut[adapt_power_input.out_up],
                       power.down: adaptPowerOut[adapt_power_input.out_down]})


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

for step in range(1, int(STOP_TIME / START_STEP_SIZE) + 1):
    
    # Note that despite the fact that there is no feedthrough between 
    # the inputs and the outputs of the power system, 
    # the internal solver would still benefit from an up-to-date 
    # value given for the inputs. However, that creates an algebraic loop, 
    # so for now, we just get old values for the inputs.
    
    wOut = window.getValues(step-1, 0, [window.tau, window.x])
    
    adaptPowerOut = adapt_power_input.getValues(step-1, 0, [adapt_power_input.out_up, adapt_power_input.out_down])
    
    power.setValues(step, 0, {power.tau: wOut[window.tau], 
                           power.up: adaptPowerOut[adapt_power_input.out_up],
                           power.down: adaptPowerOut[adapt_power_input.out_down]})
    
    power.doStep(time, step, 0, START_STEP_SIZE)
    pOut = power.getValues(step, 0, [power.omega, power.theta, power.i])
    
    obstacle.setValues(step, 0, {obstacle.x: wOut[window.x]})
    obstacle.doStep(time, step, 0, START_STEP_SIZE) 
    oOut = obstacle.getValues(step, 0, [obstacle.F])
        
    window.setValues(step, 0, {window.omega_input: pOut[power.omega],
                               window.theta_input: pOut[power.theta],
                               window.F_obj: oOut[obstacle.F]
                            })
    window.doStep(time, step, 0, START_STEP_SIZE) 
    wOut = window.getValues(step, 0, [window.tau, window.x])
    
    
    adapt_armature.setValues(step, 0, {adapt_armature.armature_current: pOut[power.i]})
    adapt_armature.doStep(time, step, 0, START_STEP_SIZE) 
    adaptArmOut = adapt_armature.getValues(step, 0, [adapt_armature.out_event])
    
    environment.doStep(time, step, 0, START_STEP_SIZE) 
    envOut = environment.getValues(step, 0, [environment.out_event])
    
    # coupling equation for the input event of the controller
    controller_in = adaptArmOut[adapt_armature.out_event] + envOut[environment.out_event]
    if adaptArmOut[adapt_armature.out_event] != "" and envOut[environment.out_event] != "":
        controller_in = adaptArmOut[adapt_armature.out_event]
    controller.setValues(step, 0, {controller.in_event : controller_in})
    controller.doStep(time, step, 0, START_STEP_SIZE) 
    cOut = controller.getValues(step, 0, [controller.out_event])
    
    adapt_power_input.setValues(step, 0, {adapt_power_input.in_event : cOut[controller.out_event]})
    adapt_power_input.doStep(time, step, 0, START_STEP_SIZE) 
    adaptPowerOut = adapt_power_input.getValues(step, 0, [adapt_power_input.out_up, adapt_power_input.out_down])
    
    # Finally set the other power inputs
    """
    The instruction below is not really needed, as power has already performed the step.
    However, we leave it here because in case an algebraic loop were being solved,
    this is where we would set the improved values for the power inputs, 
    and check for convergence.
    
    """
    power.setValues(step, 0, {power.tau: wOut[window.tau], 
                           power.up: adaptPowerOut[adapt_power_input.out_up],
                           power.down: adaptPowerOut[adapt_power_input.out_down]})
    
    trace_omega.append(pOut[power.omega])
    trace_i.append(pOut[power.i])
    trace_x.append(wOut[window.x])
    trace_F.append(oOut[obstacle.F])
    time += START_STEP_SIZE
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
