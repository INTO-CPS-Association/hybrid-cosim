"""
This scenario covers the following adaptations:
- Step delay to the output of the controller
- Algebraic loop adaptation for the power, window, and obstacle
"""

import logging

from bokeh.plotting import figure, output_file, show

from case_study.units.adaptations.InacurateControllerArmatureAdaptation_CT import InacurateControllerArmatureAdaptation_CT
from case_study.units.de_based.DriverControllerStatechartFMU_CTInOut import DriverControllerStatechartFMU_CTInOut
from case_study.units.de_based.EnvironmentStatechartFMU_CTInOut import EnvironmentStatechartFMU_CTInOut
from case_study.units.adaptations.AlgebraicAdaptation_Power_Window_Obstacle import AlgebraicAdaptation_Power_Window_Obstacle

NUM_RTOL = 1e-05
NUM_ATOL = 1e-05

l = logging.getLogger()
l.setLevel(logging.DEBUG)


START_STEP_SIZE = 0.001
FMU_START_RATE = 1
STOP_TIME = 6;

environment = EnvironmentStatechartFMU_CTInOut("env", NUM_RTOL, NUM_ATOL)

controller = DriverControllerStatechartFMU_CTInOut("controller", NUM_RTOL, NUM_ATOL)

power_window_obstacle = AlgebraicAdaptation_Power_Window_Obstacle("strong_comp", NUM_RTOL, NUM_ATOL, START_STEP_SIZE, FMU_START_RATE)

armature_threshold = 5
adapt_armature = InacurateControllerArmatureAdaptation_CT("arm_adapt", NUM_RTOL, NUM_ATOL, armature_threshold, True)

environment.enterInitMode()
controller.enterInitMode()
power_window_obstacle.enterInitMode()
adapt_armature.enterInitMode()

step = 0
iteration = 0

envOut = environment.getValues(step, iteration, [environment.out_up, environment.out_down])

power_window_obstacle.setValues(step, iteration, {
                                 power_window_obstacle.omega: 0.0, 
                                 power_window_obstacle.theta: 0.0, 
                                 power_window_obstacle.i: 0.0,
                                 power_window_obstacle.up: 0.0, # Delayed input
                                 power_window_obstacle.down: 0.0    # Delayed input
                                 })

pOut = power_window_obstacle.getValues(step, iteration, [power_window_obstacle.i])

adapt_armature.setValues(step, iteration, {adapt_armature.armature_current: pOut[power_window_obstacle.i],
                                adapt_armature.out_obj: 0.0 })
adaptArmOut = adapt_armature.getValues(step, iteration, [adapt_armature.out_obj])

controller.setValues(step, iteration, {controller.in_dup : envOut[environment.out_up],
                            controller.in_ddown : envOut[environment.out_down],
                            controller.in_obj : adaptArmOut[adapt_armature.out_obj]})
cOut = controller.getValues(step, iteration, [controller.out_up, controller.out_down])

# Set the improved inputs to the components that got delayed inputs.
power_window_obstacle.setValues(step, iteration, {
                                                  power_window_obstacle.up: cOut[controller.out_up],
                                                  power_window_obstacle.down: cOut[controller.out_down]})

environment.exitInitMode()
controller.exitInitMode()
power_window_obstacle.exitInitMode()
adapt_armature.exitInitMode()

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
    
    environment.doStep(time, step, iteration, START_STEP_SIZE) 
    envOut = environment.getValues(step, iteration, [environment.out_up, environment.out_down])
    
    # get power delayed inputs
    cOut = controller.getValues(step-1, iteration, [controller.out_up, controller.out_down])
    
    power_window_obstacle.setValues(step, iteration, {
                                     power_window_obstacle.up: cOut[controller.out_up], # Delayed input
                                     power_window_obstacle.down: cOut[controller.out_down]    # Delayed input
                                     })
    power_window_obstacle.doStep(time, step, iteration, START_STEP_SIZE)
    pOut = power_window_obstacle.getValues(step, iteration, 
                        [power_window_obstacle.i,
                         power_window_obstacle.omega,
                         power_window_obstacle.x,
                         power_window_obstacle.F
                         ])
    
    adapt_armature.setValues(step, iteration, 
                             {adapt_armature.armature_current: pOut[power_window_obstacle.i]})
    adapt_armature.doStep(time, step, iteration, START_STEP_SIZE)
    adaptArmOut = adapt_armature.getValues(step, iteration, [adapt_armature.out_obj])
    
    controller.setValues(step, iteration, {controller.in_dup : envOut[environment.out_up],
                                controller.in_ddown : envOut[environment.out_down],
                                controller.in_obj : adaptArmOut[adapt_armature.out_obj]})
    controller.doStep(time, step, iteration, START_STEP_SIZE)
    
    trace_omega.append(pOut[power_window_obstacle.omega])
    trace_i.append(pOut[power_window_obstacle.i])
    trace_x.append(pOut[power_window_obstacle.x])
    trace_F.append(pOut[power_window_obstacle.F])
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
