code window_sa:
	
	/*
	These maps will keep track of which rules execute and which don't
	*/
	var out_condition_executed = empty map
	var in_condition_executed = empty map
	
	var window //FMU window ref
	
	/*
	Keeps track of the last time that the FMU window did a step.
	*/
	var time_last_window
	
	/*
	Variables declared in the base model
	*/
	var stored_windowsa_reaction_force,
		stored_windowsa_displacement,
		stored_windowsa_speed
	var stored_window_reaction_torque,
		stored_window_height
	
	function instantiate()
		window.instantiate()
		return
	end function
	
	function enter_init() 
		window.enter_init()
		return
	end function
	
	
	function setup_experiment(t,...) 
		window.setup_experiment(t,...)
		time_last_window = t
		return
	end function
	
	function exit_init() 
		window.exit_init()
		return
	end function
	
	function setValues(ports, values)
		/*
		Evaluates each condition (and sa_in rule) in order.
		*/
		if (true) then
			in_condition_executed[IN_COND_1] = true
			
			if values has key "reaction_force" then
				stored_windowsa_reaction_force = values["reaction_force"]
			end if 
			
			// Since window_sa is mealy, we forward the inputs immediately to the inner FMUs.
			{ // new scope
				/*
				These 3 variables are available in the scope of the update_in block.
				*/
				var t = 0
				var h = 0
				var dt = 0
				window.setValues("reaction_force", stored_windowsa_reaction_force)
			}
		end if
		if (true) then
			in_condition_executed[IN_COND_2] = true
			
			if values has key "displacement" then
				stored_windowsa_displacement = values["displacement"]
			end if
			
			{ // new scope
				var t = 0
				var h = 0
				var dt = 0
				window.setValues("displacement", stored_windowsa_displacement)
			}
		end if
		if (true) then
			in_condition_executed[IN_COND_3] = true
			
			if values has key "speed" then
				stored_windowsa_speed = values["speed"]
			end if 
			
			// window_sa is mealy
			{ // new scope
				var t = 0
				var h = 0
				var dt = 0
				window.setValues("speed", stored_windowsa_speed)
			}
		end if
		out_condition_executed = empty map // force output computation.
	end function
	
	function doStep(t, H)
		
		/*
		A new doStep means that a new set of conditions will be triggered.
		*/
		out_condition_executed = empty map
		
		/*
		Calculate the elapsed time since the last transition
		*/
		var e = t - time_last_window
		
		/*
		Evaluate each update_in block of the rules that were successfully evaluated before the doStep was called.
		This is because the window.doStep will be called immediately afterward.
		*/
		if (in_condition_executed[IN_COND_1]) then
			/*
			These variables are available in the scope of the update_in block.
				It's not a good idea to have t also in that scope, because it is not available when getValues is called.
			*/
			var h = 0
			var dt = 0
			window.setValues("reaction_force", stored_windowsa_reaction_force)
		end if
		if (in_condition_executed[IN_COND_2]) then
			var h = 0
			var dt = 0
			window.setValues("displacement", stored_windowsa_displacement)
		end if
		if (in_condition_executed[IN_COND_3]) then
			var h = 0
			var dt = 0
			window.setValues("speed", stored_windowsa_speed)
		end if
		// call window.doStep()
		window.doStep(t, H)
		/*
		Executes the update_out blocks.
		These always execute after a doStep is called on an internal FMU.
		*/
		if true then
			var h = 0
			var dt = 0
			out_condition_executed[OUT_COND_1] = true
			stored_window_reaction_torque = window.getValues("reaction_torque")
		end if
		if true then
			var h = 0
			var dt = 0
			out_condition_executed[OUT_COND_2] = true
			stored_window_height = window.getValues("height")
		end if
		
		// keep track of the last time window.doStep was called
		time_last_window = t;
		
		// reset the in_conditions tracker.
		in_condition_executed = empty map
		
	end function
	
	function getValues(ports)
		var values = empty map
		
		if out_condition_executed == empty map then
			// This can happen since the adapted unit is a mealy machine
			// So execute the update_out blocks
			if true then
				var h = 0
				var dt = 0
				out_condition_executed[OUT_COND_1] = true
				stored_window_reaction_torque = window.getValues("reaction_torque")
			end if
			if true then
				var h = 0
				var dt = 0
				out_condition_executed[OUT_COND_2] = true
				stored_window_height = window.getValues("height")
			end if
		end if
		
		// Execute the sa_out blocks
		if out_condition_executed[OUT_COND_1] then
			values["tau"] = - stored_window_reaction_torque
			values["disp"] = stored_window_height * 100
		end if
		if out_condition_executed[OUT_COND_2] then
			values["disp"] = stored_window_height * 100
		end if
		
		return values
	end function