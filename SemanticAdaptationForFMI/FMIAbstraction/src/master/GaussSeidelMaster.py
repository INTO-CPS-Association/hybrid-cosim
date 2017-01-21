'''
This follows algorithm 4 in the paper.
'''
import logging

l = logging.getLogger()

class GaussSeidelMaster():
    def simulate(self, order, units, coupling, initial_state,
                 start_step_size, max_step_size, step_increase_rate, min_steps_before_increase,
                 stop_time,
                 plot):
        
        t = 0
        H = start_step_size
        step = 0
        
        l.debug("Entering init mode...")
        
        for j in order:
            unit = units[j];
            unit.enterInitMode()
        
        y = [] 
        u = []
        H_proposed = []
        for unit in units:
            y.append(None)
            u.append(None)
            H_proposed.append(None)
        
        l.debug("Setting initial states...")
        
        for sigmaj in order:
            if initial_state[sigmaj] != None:
                units[sigmaj].setValues(step,0,initial_state[sigmaj])
        
        for sigmaj in order:
            u[sigmaj] = coupling[sigmaj](y)
            if u[sigmaj] != None:
                units[sigmaj].setValues(step,0,u[sigmaj])
            y[sigmaj] = units[sigmaj].getValues(step,0)
        
        step=1
        last_rollback_step = 0
        
        l.debug("Exiting init mode...")
        for j in order:
            unit = units[j];
            unit.exitInitMode()
        
        plot(t, step, y)
        
        l.debug("Going to step mode...")
        while t < stop_time:
            
            l.debug("New cosim step: %d at time %f", step, t)
            
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
            
            t = t + H
            plot(t, step, y)
            step = step + 1
        