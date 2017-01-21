"""
This scenario covers the following adaptations:
- Step delay and decouple adaptation to all power outputs and to the obstacle output, to break the algebraic loops.
- Accurate threshold crossing adaptation to the armature current output.

The master algorithm's policy is as follows:
Each time he asks an FMU to do a step, the FMU may either accept or reject the step.
If the FMU accepts the step, the master moves onto the next one.
If the FMU does not accept the state, the master rollsback every other FMU and retries with the step proposed by the FMU.

After a while, if all FMU continuously accept the steps, the master will gradually increase the step.
"""

import logging

from bokeh.plotting import figure, output_file, show

from case_study.units.adaptations.AccurateControllerArmatureAdaptation import AccurateControllerArmatureAdaptation
from case_study.units.adaptations.StepDelay import StepDelay
from case_study.units.ct_based.ObstacleFMU import ObstacleFMU
from case_study.units.ct_based.PowerFMU import PowerFMU
from case_study.units.ct_based.WindowFMU import WindowFMU
from case_study.units.de_based.DriverControllerStatechartFMU_CTInOut import DriverControllerStatechartFMU_CTInOut
from case_study.units.de_based.EnvironmentStatechartFMU_CTInOut import EnvironmentStatechartFMU_CTInOut
from master.GaussSeidelMaster import GaussSeidelMaster


NUM_RTOL = 1e-08
NUM_ATOL = 1e-08

l = logging.getLogger()
l.setLevel(logging.DEBUG)

START_STEP_SIZE = 0.001
MAX_STEP_SIZE = 0.001
MIN_STEPS_BEFORE_INCREASE_STEP_SIZE = 10
STEP_SIZE_INCREASE_RATE = 10 # e.g, 10%

FMU_START_RATE = 10
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

armature_threshold = 5 # This was the initial threshold, but did not work.
adapt_armature = AccurateControllerArmatureAdaptation("arm_adapt", NUM_RTOL, NUM_ATOL, armature_threshold, True)

window = WindowFMU("window", NUM_RTOL, NUM_ATOL, START_STEP_SIZE/FMU_START_RATE,
                     r=0.11, 
                     b = 10)

obstacle = ObstacleFMU("obstacle", NUM_RTOL, NUM_ATOL, START_STEP_SIZE/FMU_START_RATE, 
                     c=1e5, 
                     fixed_x=0.45)

delay_up = StepDelay("delay_up")
delay_down = StepDelay("delay_down")
delay_reaction_torque = StepDelay("delay_reaction_torque")
delay_height = StepDelay("delay_height")

units = [
         environment,                   # 0
         controller,                    # 1
         power,                         # 2
         adapt_armature,                # 3
         window,                        # 4
         obstacle,                      # 5
         delay_up,                      # 6
         delay_down,                    # 7
         delay_reaction_torque,         # 8
         delay_height                   # 9
         ]

order = [
         6,
         7,
         8,
         9,
         2,
         5,
         4,
         3,
         0,
         1
         ]

initial_state = [
                 None,
                 None,
                 {power.omega: 0.0,power.theta: 0.0, power.i: 0.0},
                 {adapt_armature.out_obj: 0.0},
                 None,
                 None,
                 {delay_up.out_v: 0.0},
                 {delay_down.out_v: 0.0},
                 {delay_reaction_torque.out_v: 0.0},
                 {delay_height.out_v: 0.0}
                 ]

def coupling_controller(y):
    envOut = y[0]
    adaptArmOut = y[3]
    return {controller.in_dup : envOut[environment.out_up],
            controller.in_ddown : envOut[environment.out_down],
            controller.in_obj : adaptArmOut[adapt_armature.out_obj]}

def coupling_power(y):
    dupOut = y[6]
    ddownOut = y[7]
    dtauOut = y[8]
    
    return {power.up : dupOut[delay_up.out_v],
            power.down : ddownOut[delay_down.out_v],
            power.tau : dtauOut[delay_reaction_torque.out_v]}

def coupling_adapt_armature(y):
    pOut = y[2]
    return {adapt_armature.armature_current: pOut[power.i]}

def coupling_window(y):
    pOut = y[2]
    oOut = y[5]
    return {window.omega_input: pOut[power.omega],
            window.theta_input: pOut[power.theta],
            window.F_obj: oOut[obstacle.F]
            }

def coupling_obstacle(y):
    dheightOut = y[9]
    return {obstacle.x: dheightOut[delay_height.out_v]}

def coupling_delay_up(y):
    cOut = y[1]
    return {delay_up.in_v: cOut[controller.out_up]} if cOut != None else None

def coupling_delay_down(y):
    cOut = y[1]
    return {delay_down.in_v: cOut[controller.out_down]} if cOut != None else None

def coupling_delay_torque(y):
    wOut = y[4]
    return {delay_reaction_torque.in_v: wOut[window.tau]} if wOut != None else None

def coupling_delay_height(y):
    wOut = y[4]
    return {delay_height.in_v: wOut[window.x]} if wOut != None else None


couplings = [
             lambda y: None,
             coupling_controller,
             coupling_power,
             coupling_adapt_armature,
             coupling_window,
             coupling_obstacle,
             coupling_delay_up,
             coupling_delay_down,
             coupling_delay_torque,
             coupling_delay_height
             ]



trace_i = [0.0]
trace_omega = [0.0]
trace_x = [0.0]
trace_F = [0.0]
times = [0.0]

def plot(t, s, y):
    pOut = y[2]
    wOut = y[4]
    oOut = y[5]
    
    times.append(t)
    trace_omega.append(pOut[power.omega])
    trace_i.append(pOut[power.i])
    trace_x.append(wOut[window.x])
    trace_F.append(oOut[obstacle.F])


master = GaussSeidelMaster()

master.simulate(order, units, couplings, initial_state, 
                    START_STEP_SIZE, MAX_STEP_SIZE, STEP_SIZE_INCREASE_RATE, MIN_STEPS_BEFORE_INCREASE_STEP_SIZE, 
                    STOP_TIME, plot)


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
