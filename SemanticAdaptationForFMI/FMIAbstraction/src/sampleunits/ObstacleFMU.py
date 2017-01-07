from units.CTSimulationUnit_Euler import CTSimulationUnit_Euler

class ObstacleFMU(CTSimulationUnit_Euler):
    
    def __init__(self, name, num_rtol, num_atol, internal_step_size, c, fixed_x):
        self.x = "x"
        self.F = "F"
        
        input_vars = [self.x]
        
        def calc_F(x, u):
            return c*(u[self.x] - fixed_x) if u[self.x] > fixed_x else 0.0
        
        state_derivatives = {}
        
        output_functions = {
                            self.F : calc_F
                            }
        
        CTSimulationUnit_Euler.__init__(self, name, num_rtol, num_atol, internal_step_size, state_derivatives, output_functions, input_vars)
    
    