import logging

from bokeh.plotting import figure, output_file, show

from case_study.units.adaptations.AccurateControllerArmatureAdaptation import AccurateControllerArmatureAdaptation
from case_study.units.adaptations.StepDelay import DecoupleAdaptation
from case_study.units.de_based.DriverControllerStatechartFMU_CTInOut import DriverControllerStatechartFMU_CTInOut
from case_study.units.de_based.EnvironmentStatechartFMU_CTInOut import EnvironmentStatechartFMU_CTInOut
from master.GaussSeidelMaster import GaussSeidelMaster
from case_study.units.adaptations.MultiRateAdaptation_Power_Window_Obstacle import MultiRateAdaptation_Power_Window_Obstacle


NUM_RTOL = 1e-08
NUM_ATOL = 1e-08

l = logging.getLogger()
l.setLevel(logging.DEBUG)

START_STEP_SIZE = 0.01
MAX_STEP_SIZE = 0.01
MIN_STEPS_BEFORE_INCREASE_STEP_SIZE = 10
STEP_SIZE_INCREASE_RATE = 10 # e.g, 10%

FMU_START_RATE = 10
STOP_TIME = 6;

environment = EnvironmentStatechartFMU_CTInOut("env", NUM_RTOL, NUM_ATOL)

controller = DriverControllerStatechartFMU_CTInOut("controller", NUM_RTOL, NUM_ATOL)

plant = MultiRateAdaptation_Power_Window_Obstacle("plant", NUM_RTOL, NUM_ATOL, FMU_START_RATE, START_STEP_SIZE)

armature_threshold = 5 # This was the initial threshold, but did not work.
adapt_armature = AccurateControllerArmatureAdaptation("arm_adapt", NUM_RTOL, NUM_ATOL, armature_threshold, True)

delay_up = DecoupleAdaptation("delay_up")
delay_down = DecoupleAdaptation("delay_down")

units = [
         environment,                   # 0
         controller,                    # 1
         plant,                         # 2
         adapt_armature,                # 3
         delay_up,                      # 4
         delay_down                     # 5
         ]

order = [
         4,
         5,
         0,
         2,
         3,
         1
         ]

initial_state = [
                 None,
                 None,
                 None,
                 {adapt_armature.out_obj: 0.0},
                 {delay_up.out_v: 0.0},
                 {delay_down.out_v: 0.0},
                 ]

def coupling_controller(y):
    envOut = y[0]
    adaptArmOut = y[3]
    return {controller.in_dup : envOut[environment.out_up],
            controller.in_ddown : envOut[environment.out_down],
            controller.in_obj : adaptArmOut[adapt_armature.out_obj]}

def coupling_plant(y):
    dupOut = y[4]
    ddownOut = y[5]
    
    return {plant.in_power_up : dupOut[delay_up.out_v],
            plant.in_power_down : ddownOut[delay_down.out_v]
            }

def coupling_adapt_armature(y):
    pOut = y[2]
    return {adapt_armature.armature_current: pOut[plant.out_power_i]}

def coupling_delay_up(y):
    cOut = y[1]
    return {delay_up.in_v: cOut[controller.out_up]} if cOut != None else None

def coupling_delay_down(y):
    cOut = y[1]
    return {delay_down.in_v: cOut[controller.out_down]} if cOut != None else None

couplings = [
             lambda y: None,
             coupling_controller,
             coupling_plant,
             coupling_adapt_armature,
             coupling_delay_up,
             coupling_delay_down
             ]

trace_i = [0.0]
trace_omega = [0.0]
trace_x = [0.0]
trace_F = [0.0]
times = [0.0]

def plot(t, s, y):
    pOut = y[2]
    
    times.append(t)
    trace_i.append(pOut[plant.out_power_i])
    trace_x.append(pOut[plant.out_window_x])
    trace_F.append(pOut[plant.out_obs_F])


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
