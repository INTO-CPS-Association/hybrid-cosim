import logging

from abstract_units.MultiRateAdaptationUnit import MultiRateAdaptationUnit
from case_study.units.adaptations.StepDelay import DecoupleAdaptation
from case_study.units.ct_based.ObstacleFMU import ObstacleFMU
from case_study.units.ct_based.PowerFMU import PowerFMU
from case_study.units.ct_based.WindowFMU import WindowFMU
from case_study.units.adaptations.ZOHAdaptation import ZOHAdaptation


l = logging.getLogger()

class MultiRateAdaptation_Power_Window_Obstacle(MultiRateAdaptationUnit):
    """
    This is the adaptation that realizes the strong coupling between the power,
    window, and obstacle units.
    """
    
    def __init__(self, name, num_rtol, num_atol, start_rate, start_step_size):
        
        self.in_power_up = "in_power_up"
        self.in_power_down = "in_power_down"
        self.out_power_i = "out_power_i"
        self.out_window_x = "out_window_x"
        self.out_obs_F = "out_obs_F"
        
        power = PowerFMU(name+":"+"power", num_rtol, num_atol, start_step_size/start_rate, 
                     J=0.085, 
                     b=5, 
                     K=7.45, 
                     R=0.15, 
                     L=0.036,
                     V_a=12)

        window = WindowFMU(name+":"+"window", num_rtol, num_atol, start_step_size/start_rate,
                             r=0.11, 
                             b = 10)
        
        obstacle = ObstacleFMU(name+":"+"obstacle", num_rtol, num_atol, start_step_size/start_rate, 
                             c=1e5, 
                             fixed_x=0.45)
        
        delay_reaction_torque = DecoupleAdaptation(name+":"+"delay_reaction_torque")
        delay_height = DecoupleAdaptation(name+":"+"delay_height")
        
        zoh_up = ZOHAdaptation(name+":"+"zoh_up", "in_ext_up", "out_ext_up")
        zoh_down = ZOHAdaptation(name+":"+"zoh_down", "in_ext_down", "out_ext_down")
        
        units = [
                 power,                  # 0
                 window,                 # 1
                 obstacle,               # 2
                 delay_height,           # 3
                 delay_reaction_torque,  # 4
                 zoh_up,                 # 5
                 zoh_down                # 6
                 ]
        
        order = [
                 5,
                 6,
                 3,
                 4,
                 2,
                 0,
                 1
                 ]
        
        initial_state = [
                         {power.omega: 0.0,power.theta: 0.0, power.i: 0.0},
                         None,
                         None,
                         {delay_height.out_v: 0.0},
                         {delay_reaction_torque.out_v: 0.0},
                         None,
                         None
                         ]
        
        def coupling_power(y):
            zohUpOut = y[5]
            zohDownOut = y[6]
            dtauOut = y[4]
            
            return {power.up : zohUpOut[zoh_up.output_var],
                    power.down : zohDownOut[zoh_down.output_var],
                    power.tau : dtauOut[delay_reaction_torque.out_v]}
        
        def coupling_window(y):
            pOut = y[0]
            oOut = y[2]
            return {window.omega_input: pOut[power.omega],
                    window.theta_input: pOut[power.theta],
                    window.F_obj: oOut[obstacle.F]
                    }
        
        def coupling_obstacle(y):
            dheightOut = y[3]
            return {obstacle.x: dheightOut[delay_height.out_v]}
        
        def coupling_delay_torque(y):
            wOut = y[1]
            return {delay_reaction_torque.in_v: wOut[window.tau]} if wOut != None else None
        
        def coupling_delay_height(y):
            wOut = y[1]
            return {delay_height.in_v: wOut[window.x]} if wOut != None else None
        
        def coupling_zoh_up(y):
            last_known_inputs = self._inputs
            output=None
            if last_known_inputs != None:
                output= {
                         zoh_up.input_var : last_known_inputs[self.in_power_up]
                         }
            return output
        
        def coupling_zoh_down(y):
            last_known_inputs = self._inputs
            output=None
            if last_known_inputs != None:
                output= {
                         zoh_down.input_var : last_known_inputs[self.in_power_down]
                         }
            return output
        
        def external_coupling(y):
            pOut = y[0]
            wOut = y[1]
            oOut = y[2]
            
            return {
                    self.out_power_i : pOut[power.i],
                    self.out_window_x: wOut[window.x],
                    self.out_obs_F: oOut[obstacle.F]
                    }
            
        couplings = [
                     coupling_power,
                     coupling_window,
                     coupling_obstacle,
                     coupling_delay_height,
                     coupling_delay_torque,
                     coupling_zoh_up,
                     coupling_zoh_down
                     ]
        
        MultiRateAdaptationUnit.__init__(self, name, num_rtol, num_atol, 
                                         order, units, couplings, external_coupling,
                                         start_rate,
                                         initial_state)
    
