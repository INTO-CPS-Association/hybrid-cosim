from units.CTSimulationUnit_Euler import CTSimulationUnit_Euler

class PowerFMU(CTSimulationUnit_Euler):
    
    def __init__(self, name, num_rtol, num_atol, internal_step_size, J, b, K, R, L, V_a):
        self.name = name
        
        self.up = "up"
        self.down = "down"
        self.tau = "tau"
        
        input_vars = [self.tau, self.down, self.up]
        
        self.theta = "theta"
        self.omega = "omega"
        self.i = "i"
        
        def get_v(up, down):
            return V_a if up > 0.5 else (-V_a if down>0.5 else 0.0)
        
        def der_theta(x, u):
            return x[self.omega]
        def der_omega(x, u):
            return (K * x[self.i] + u[self.tau] - b * x[self.omega]) / J
        def der_i(x, u):
            volt = get_v(u[self.up], u[self.down])
            return (volt - K * x[self.omega] - R * x[self.i]) / L
        
        state_derivatives = {
                             self.theta: der_theta,
                             self.omega: der_omega,
                             self.i: der_i
                             }
        
        algebraic_functions = {}
        
        CTSimulationUnit_Euler.__init__(self, name, 
                                        num_rtol, num_atol, internal_step_size, 
                                        state_derivatives, algebraic_functions, input_vars)
    
    