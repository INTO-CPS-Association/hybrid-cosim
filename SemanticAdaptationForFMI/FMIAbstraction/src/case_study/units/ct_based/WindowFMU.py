from abstract_units.CTSimulationUnit_Euler import CTSimulationUnit_Euler


class WindowFMU(CTSimulationUnit_Euler):
    
    def __init__(self, name, num_rtol, num_atol, internal_step_size, J, r, b, c):
        self.omega_input = "omega_input"
        self.theta_input = "theta_input"
        self.tau = "tau"
        self.x = "x"
        self.v = "v"
        self.omega = "omega"
        self.theta = "theta"
        
        input_vars = [self.omega_input, self.theta_input]
        
        def calc_v(x, u):
            return r * x[self.omega]
        def calc_x(x, u):
            return r * x[self.theta]
        def calc_tau(x,u):
            return c * ( u[self.theta_input] - x[self.theta] ) - b * calc_v(x,u)
        
        def der_theta(x, u):
            return x[self.omega]
        def der_omega(x, u):
            return calc_tau(x,u) / J
        
        state_derivatives = {
                             self.theta: der_theta,
                             self.omega: der_omega
                             }
        
        algebraic_functions = {
                            self.v : calc_v,
                            self.x : calc_x,
                            self.tau: calc_tau
                            }
        
        CTSimulationUnit_Euler.__init__(self, name, num_rtol, num_atol, internal_step_size, state_derivatives, algebraic_functions, input_vars)
    
    