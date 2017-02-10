code AdaptedFMU:
	
	var in_condition_executed;
	var out_condition_executed;
	in_condition_executed = empty map;
	
	function instantiate()
		fmu1.instantiate()
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
		
		if (in_condition_1) then
			in_condition_executed[cond1] = true
			sa_in_1
			<if AdaptedFMU is mealy then>	
				update_sa_in_1
			<end if>
		end if
		...
		
		out_condition_executed := empty map // force output computation.
	end function
	
	function doStep(t, H)
		
		control_block // or generic algorithm cosim step
		/* 
		In the midst of the control block code,
		before any setValues is called on an inner FMU,
		the following code will be injected:
			if in_condition_executed[cond1] then
				update_in_1
			end if
			...
		*/
		
		in_condition_executed = empty map;
		out_condition_executed := empty map // force output computation.
		
	end function
	
	function getValues(ports)
		
		if out_condition_executed == empty map then
			if (out_condition_1) then
				out_condition_executed[cond1] = true
				update_out_1
			end if
			...
		end if
		
		if out_condition_executed[cond1] then
			sa_out_1
		end if
		...
	end function