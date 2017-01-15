"""
This scenario covers the following adaptations:
- Step delay and decouple adaptation to all power outputs and to the obstacle output, to break the algebraic loops.
- Inaccurate threshold crossing adaptation to the armature current output.
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


START_STEP_SIZE = 0.001
FMU_START_RATE = 1
STOP_TIME = 6;

environment = EnvironmentStatechartFMU_CTInOut("env", NUM_RTOL, NUM_ATOL)

controller = DriverControllerStatechartFMU_CTInOut("controller", NUM_RTOL, NUM_ATOL)

power = PowerFMU("power", NUM_RTOL, NUM_ATOL, START_STEP_SIZE/FMU_START_RATE, 
                     J=0.085, 
                     b=5, 
                     K=7.45, 
                     R=0.15, 
                     L=0.036,
                     V_a=12)

armature_threshold = 5
adapt_armature = InacurateControllerArmatureAdaptation_CT("arm_adapt", NUM_RTOL, NUM_ATOL, armature_threshold, True)

window = WindowFMU("window", NUM_RTOL, NUM_ATOL, START_STEP_SIZE/FMU_START_RATE,
                     r=0.11, 
                     b = 10)

obstacle = ObstacleFMU("obstacle", NUM_RTOL, NUM_ATOL, START_STEP_SIZE/FMU_START_RATE, 
                     c=1e5, 
                     fixed_x=0.45)

environment.enterInitMode()
controller.enterInitMode()
power.enterInitMode()
adapt_armature.enterInitMode()
window.enterInitMode()
obstacle.enterInitMode()

step = 0
iteration = 0

# Set environment initial inputs
# Nothing to do

# Get environment initial outputs
envOut = environment.getValues(step, iteration, [environment.out_up, environment.out_down])

# Set power initial state
power.setValues(step, iteration, {
                                 power.omega: 0.0, 
                                 power.theta: 0.0, 
                                 power.i: 0.0,
                                 power.tau: 0.0, # Delayed input
                                 power.up: 0.0, # Delayed input
                                 power.down: 0.0    # Delayed input
                                 })
# Get power initial outputs
pOut = power.getValues(step, iteration, [power.omega, power.theta, power.i])

# Set obstacle initial inputs
# Assume they are zero because the outputs of the window are delayed.
obstacle.setValues(step, iteration, {obstacle.x: 0.0})
# Get obstacle outputs
oOut = obstacle.getValues(step, iteration, [obstacle.F])

# Set window inputs
window.setValues(step, iteration, {window.omega_input: pOut[power.omega],
                            window.theta_input: pOut[power.theta],
                            window.F_obj: oOut[obstacle.F]
                            })
# Get window outputs
wOut = window.getValues(step, iteration, [window.x, window.tau])

# Set adapt armature inputs and initial state
adapt_armature.setValues(step, iteration, {adapt_armature.armature_current: pOut[power.i],
                                adapt_armature.out_obj: 0.0 })
# Get adapt armature outputs
adaptArmOut = adapt_armature.getValues(step, iteration, [adapt_armature.out_obj])

# Set the initial inputs to the controller
controller.setValues(step, iteration, {controller.in_dup : envOut[environment.out_up],
                            controller.in_ddown : envOut[environment.out_down],
                            controller.in_obj : adaptArmOut[adapt_armature.out_obj]})
# Get the controller output
cOut = controller.getValues(step, iteration, [controller.out_up, controller.out_down])

# Set the improved inputs to the components that got delayed inputs.
power.setValues(step, iteration, {power.tau: wOut[window.tau], 
                       power.up: cOut[controller.out_up],
                       power.down: cOut[controller.out_down]})
obstacle.setValues(step, iteration, {obstacle.x: wOut[window.x]})

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

# This is always zero because we do not keep track of intermediate values in fixed point iterations
iteration = 0 

for step in range(1, int(STOP_TIME / START_STEP_SIZE) + 1):
    
    """
    We have delays the following inputs:
    - control inputs to the power
    - window tau input to the power
    - window height input to the obstacle
    
    The order of computation in the scenario is as follows:
    environment
    power
    obstacle
    window
    armature adaptation
    controller
    
    """
    
    # Set environment initial inputs
    # Nothing to do
    
    # Get environment initial outputs
    environment.doStep(time, step, iteration, START_STEP_SIZE) 
    envOut = environment.getValues(step, iteration, [environment.out_up, environment.out_down])
    
    # get power and obstacle delayed inputs
    cOut = controller.getValues(step-1, iteration, [controller.out_up, controller.out_down])
    wOut = window.getValues(step-1, iteration, [window.x, window.tau])
    
    # Set power inputs
    power.setValues(step, iteration, {
                                     power.tau: wOut[window.tau], # Delayed input
                                     power.up: cOut[controller.out_up], # Delayed input
                                     power.down: cOut[controller.out_down]    # Delayed input
                                     })
    power.doStep(time, step, iteration, START_STEP_SIZE)
    # Get power outputs
    pOut = power.getValues(step, iteration, [power.omega, power.theta, power.i])
    
    # Set obstacle inputs
    # The outputs of the window are delayed.
    obstacle.setValues(step, iteration, {obstacle.x: wOut[window.x]}) # Delayed input
    obstacle.doStep(time, step, iteration, START_STEP_SIZE)
    # Get obstacle outputs
    oOut = obstacle.getValues(step, iteration, [obstacle.F])
    
    # Set window inputs
    window.setValues(step, iteration, {window.omega_input: pOut[power.omega],
                                window.theta_input: pOut[power.theta],
                                window.F_obj: oOut[obstacle.F]
                                })
    window.doStep(time, step, iteration, START_STEP_SIZE)
    # Get window outputs
    wOut = window.getValues(step, iteration, [window.x, window.tau])
    
    # Set adapt armature inputs and initial state
    adapt_armature.setValues(step, iteration, {adapt_armature.armature_current: pOut[power.i]})
    adapt_armature.doStep(time, step, iteration, START_STEP_SIZE)
    # Get adapt armature outputs
    adaptArmOut = adapt_armature.getValues(step, iteration, [adapt_armature.out_obj])
    
    # Set the initial inputs to the controller
    controller.setValues(step, iteration, {controller.in_dup : envOut[environment.out_up],
                                controller.in_ddown : envOut[environment.out_down],
                                controller.in_obj : adaptArmOut[adapt_armature.out_obj]})
    controller.doStep(time, step, iteration, START_STEP_SIZE)
    # Get the controller output
    cOut = controller.getValues(step, iteration, [controller.out_up, controller.out_down])
    
    # Set the improved inputs to the components that got delayed inputs.
    """
    power.setValues(step, iteration, {power.tau: wOut[window.tau], 
                           power.up: cOut[controller.out_up],
                           power.down: cOut[controller.out_down]})
    obstacle.setValues(step, iteration, {obstacle.x: wOut[window.x]})
    """
    
    
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
