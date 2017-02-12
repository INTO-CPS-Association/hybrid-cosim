code AdaptedFMU:
	
	/*
	These maps will keep track of which rules execute and which don't
	*/
	var out_condition_executed = empty map
	var in_condition_executed = empty map
	
	var fmu1 //FMU fmu1 ref
	var fmu2 //FMU fmu2 ref
	...
	
	/*
	Keeps track of the last time that the FMU window did a step.
	*/
	var time_last_fmu1
	var time_last_fmu2
	...
	
	// parameters
	var param_p1 = c1
	...
	
	// in vars
	var cv1 = init_cv1
	...
	
	// out vars
	var ov1 = init_ov1
	...
	
	function instantiate()
		fmu1.instantiate()
		...
		return
	end function
	
	function setup_experiment(t,...) 
		window.setup_experiment(t,...)
		time_last_fmu1 = t
		...
		return
	end function
	
	function enter_init() 
		fmu1.enter_init()
		...
		return
	end function
	
	function exit_init() 
		fmu1.exit_init()
		...
		return
	end function
	
	function setValues(ports, values) 
		/*
		Evaluates each condition (and sa_in rule) in order.
		*/
		
		if (in_condition_1) then
			in_condition_executed[IN_COND_1] = true
			<sa_in_1>
			<if AdaptedFMU is mealy then>	
			{// new scope
				/*
				These variables are available in the scope of the update_in block.
				*/
				var h = 0
				var dt = 0
				<update_sa_in_1>
			}
			<end if>
		end if
		...
		
		out_condition_executed := empty map // force output computation.
	end function
	
	function doStep(t, H)
		
		/*
		A new doStep means that a new set of conditions will be triggered.
		*/
		out_condition_executed = empty map
		
		/*
		Calculate the elapsed time since the last transition
		*/
		var elapsed_fmu1 = t - time_last_fmu1
		...
		var e = min(elapsed_fmu1, ...)
		
		<control_block_part_1>
		
		/*
		Evaluate each update_in block of the rules that were successfully evaluated before the doStep was called.
		This is because the window.doStep will be called immediately afterward.
		*/
		if (in_condition_executed[IN_COND_1]) then
			/*
			These variables are available in the scope of the update_in block.
				It's not a good idea to have t also in that scope, because it is not available when getValues/setValues is called.
			*/
			var h = h
			var dt = inner_t - t
			<update_in_1>
		end if
		if (in_condition_executed[IN_COND_2]) then
			var h = h
			var dt = inner_t - t
			<update_in_2>
		end if
		...
		do_step(fmu1, inner_t, h)
		/*
		Executes the update_out blocks.
		These always execute after a doStep is called on an internal FMU.
		*/
		if (<out_condition_1>) then
			out_condition_executed[OUT_COND_1] = true
			var h = h
			var dt = inner_t - t
			<update_out_1>
		end if
		...
		
		in_condition_executed = empty map;
		
	end function
	
	function getValues(ports)
		if out_condition_executed == empty map then
			// This can happen since the adapted unit is a mealy machine
			// So execute the update_out blocks
			if (<out_condition_1>) then
				out_condition_executed[OUT_COND_1] = true
				var h = 0
				var dt = 0
				<update_out_1>
			end if
			...
		end if
		
		// Execute the sa_out blocks
		if out_condition_executed[OUT_COND_1] then
			<sa_out_1>
		end if
		...
	end function