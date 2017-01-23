'''
This follows algorithm 4 in the paper.
'''
import logging


l = logging.getLogger()

class GaussSeidelMaster():
    
    @staticmethod
    def start_initialize(order, units):
        l.debug(">GaussSeidelMaster.start_initialize()")
        for j in order:
            unit = units[j];
            unit.enterInitMode()
        l.debug("<GaussSeidelMaster.start_initialize()")
    
    @staticmethod
    def finish_initialize(order, units):
        l.debug(">GaussSeidelMaster.finish_initialize()")
        for j in order:
            unit = units[j];
            unit.exitInitMode()
        l.debug("<GaussSeidelMaster.finish_initialize()")
    
    @staticmethod
    def compute_outputs(step, units, order, coupling, y, u):
        l.debug(">GaussSeidelMaster.compute_outputs(%s, %s)", y, u)
        for sigmaj in order:
            u[sigmaj] = coupling[sigmaj](y)
            if u[sigmaj] != None:
                units[sigmaj].setValues(step,0,u[sigmaj])
            y[sigmaj] = units[sigmaj].getValues(step,0)
        l.debug("<GaussSeidelMaster.compute_outputs(%s, %s)", y, u)
        
    
    @staticmethod
    def set_initial_states(units, order, initial_state):
        l.debug(">GaussSeidelMaster.set_initial_states()")
        for sigmaj in order:
            if initial_state[sigmaj] != None:
                units[sigmaj].setValues(0,0,initial_state[sigmaj])
        l.debug("<GaussSeidelMaster.set_initial_states()")
        
    
    @staticmethod
    def do_cosim_step(t, step, order, units, coupling, 
                      u, y, H_proposed, 
                      H, last_rollback_step,
                      min_steps_before_increase, max_step_size, step_increase_rate):
        l.debug(">GaussSeidelMaster.do_cosim_step(%f, %d, %f)", t, step, H)
        ok = False
        
        while not ok:
            for sigmaj in order:
                u[sigmaj] = coupling[sigmaj](y)
                if u[sigmaj] != None:
                    units[sigmaj].setValues(step,0,u[sigmaj])
                (_, H_hat) = units[sigmaj].doStep(t, step, 0, H)
                H_proposed[sigmaj] = H_hat
                y[sigmaj] = units[sigmaj].getValues(step,0)
            
            min_H = min(H_proposed)
            if min_H < H:
                l.debug("Rolling back step: %d at time %f", step, t)
                for unit in units:
                    unit.rollback(step)
                ok = False
                last_rollback_step = step
                l.debug("Decreasing step size from %f to %f...", H, min_H)            
                H = min_H
            else:
                ok = True
        
        for unit in units:
            unit.commit(step)
            
        if (step - last_rollback_step) > min_steps_before_increase \
            and H < max_step_size:
            new_step_size = H + H * (step_increase_rate/100.0)
            l.debug("Increasing step size from %f to %f...", H, new_step_size)            
            H = new_step_size
            if H > max_step_size:
                l.debug("Max step size attained: %f.", max_step_size)  
                H = max_step_size
                
        l.debug("<GaussSeidelMaster.do_cosim_step()=%f , %s", H, H_proposed)
        
        assert H > 0.0
        
        return (H, last_rollback_step)
    
    def simulate(self, order, units, coupling, initial_state,
                 start_step_size, max_step_size, step_increase_rate, min_steps_before_increase,
                 stop_time,
                 plot):
        
        t = 0
        H = start_step_size
        step = 0
        
        l.debug("Entering init mode...")
        
        GaussSeidelMaster.start_initialize(order,units)
        
        y = [] 
        u = []
        H_proposed = []
        for _ in units:
            y.append(None)
            u.append(None)
            H_proposed.append(None)
        
        l.debug("Setting initial states...")
        
        GaussSeidelMaster.set_initial_states(units, order, initial_state)
        
        GaussSeidelMaster.compute_outputs(step, units, order, coupling, y, u)
        
        step=1
        last_rollback_step = 0
        
        l.debug("Finishing init mode...")
        
        GaussSeidelMaster.finish_initialize(order, units)
        
        plot(t, step, y)
        
        l.debug("Going to step mode...")
        while t < stop_time:
            
            l.debug("New cosim step: %d at time %f", step, t)
            
            (H,last_rollback_step) = GaussSeidelMaster.do_cosim_step(t, step, order, units, coupling, 
                                            u, y, H_proposed, 
                                            H, last_rollback_step,
                                            min_steps_before_increase, max_step_size, step_increase_rate)
            
            """
            ok = False
            
            while not ok:
                for sigmaj in order:
                    u[sigmaj] = coupling[sigmaj](y)
                    if u[sigmaj] != None:
                        units[sigmaj].setValues(step,0,u[sigmaj])
                    (_, H_hat) = units[sigmaj].doStep(t, step, 0, H)
                    H_proposed[sigmaj] = H_hat
                    y[sigmaj] = units[sigmaj].getValues(step,0)
                
                min_H = min(H_proposed)
                if min_H < H:
                    l.debug("Rolling back step: %d at time %f", step, t)
                    ok = False
                    last_rollback_step = step
                    l.debug("Decreasing step size from %f to %f...", H, min_H)            
                    H = min_H
                else:
                    ok = True
                
            if (step - last_rollback_step) > min_steps_before_increase \
                and H < max_step_size:
                new_step_size = H + H * (step_increase_rate/100.0)
                l.debug("Increasing step size from %f to %f...", H, new_step_size)            
                H = new_step_size
                if H > max_step_size:
                    l.debug("Max step size attained: %f.", max_step_size)  
                    H = max_step_size
            """
            
            t = t + H
            plot(t, step, y)
            step = step + 1
        