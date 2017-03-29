#include "windowSA.h"

namespace adaptation 
{
	WindowSA::WindowSA(shared_ptr<string> resourceLocation) : SemanticAdaptation(createInputRules(),createOutputRules())
	{
		stored_window_reaction_torque = 0.0;
		stored_window_height = 0.0;
		
		this->stored_windowsa_reaction_force = 0.0;
		this->stored_windowsa_displacement = 0.0;
		this->stored_windowsa_speed = 0.0;
		
		this->displacement = 0.0;
		this->reaction_force = 0.0;
		this->speed = 0.0;
		this->b = 10.0;
		this->r = 0.11;
		
		const char* path = Fmu::combinePath(resourceLocation, make_shared<string>("Window.fmu"))->c_str();
		auto windowFmu = make_shared<fmi2::Fmu>(path);
		windowFmu->initialize();
		this->window = windowFmu->instantiate("Window",fmi2CoSimulation, "{29e3eae4-7ed5-4ccc-a0e7-7d8198e20bc0}", true, true, make_shared<Callback>()); 
	}
	WindowSA::~WindowSA()
	{
	}
	
	WindowSA* WindowSA::getRuleThis()
	{
		return this;
	}
	
	double  WindowSA::getFmiValueReal(fmi2ValueReference id)
	{
		switch (id)
		{
			case WINDOWDISP:
			{
				return this->disp;
			}
			case WINDOWFRICTION:
			{
				return this->friction;
			}
			case WINDOWTAU:
			{
				return this->tau;
			}
			default:
			{
				return 0.0;
			}
		}
		
	}
	
	string  WindowSA::getFmiValueString(fmi2ValueReference id)
	{
		return "";
	}
	
	int  WindowSA::getFmiValueInteger(fmi2ValueReference id)
	{
		return 0;
	}
	
	bool  WindowSA::getFmiValueBoolean(fmi2ValueReference id)
	{
		return false;
	}
	
	void WindowSA::setFmiValue(fmi2ValueReference id, double value)
	{
		switch (id)	
			{
				case WINDOWDISPLACEMENT:
				{
					this->displacement = value;
					this->isSetdisplacement = true;
					break;
				}
				case WINDOWREACTION_FORCE:
				{
					this->reaction_force = value;
					this->isSetreaction_force = true;
					break;
				}
				case WINDOWSPEED:
				{
					this->speed = value;
					this->isSetspeed = true;
					break;
				}
				default:
				{
				}
			}
	}
	
	void WindowSA::setFmiValue(fmi2ValueReference id, string value)
	{
	}
	
	void WindowSA::setFmiValue(fmi2ValueReference id, int value)
	{
	}
	
	void WindowSA::setFmiValue(fmi2ValueReference id, bool value)
	{
	}
	
	bool WindowSA::in_rule_condition1(){
		return true;
	}
	void WindowSA::in_rule_body1(){
		if(this->isSetreaction_force){
			this->stored_windowsa_reaction_force = this->reaction_force;
		}
	}
	void WindowSA::in_rule_flush1(){
		setValue(window,WINDOWREACTION_FORCE,this->stored_windowsa_reaction_force);
	}
	bool WindowSA::in_rule_condition2(){
		return true;
	}
	void WindowSA::in_rule_body2(){
		if(this->isSetdisplacement){
			this->stored_windowsa_displacement = this->displacement;
		}
	}
	void WindowSA::in_rule_flush2(){
		setValue(window,WINDOWDISPLACEMENT,this->stored_windowsa_displacement);
	}
	bool WindowSA::in_rule_condition3(){
		return true;
	}
	void WindowSA::in_rule_body3(){
		if(this->isSetspeed){
			this->stored_windowsa_speed = this->speed;
		}
	}
	void WindowSA::in_rule_flush3(){
		setValue(window,WINDOWSPEED,this->stored_windowsa_speed);
	}
	shared_ptr<list<Rule<WindowSA>>> WindowSA::createInputRules()
	{
		auto list = make_shared<list<Rule<WindowSA>>>()
		
		list->push_back(
			(Rule<WindowSA>){
				&WindowSA::in_rule_condition1();,
				&WindowSA::in_rule_body1();
				&WindowSA::in_rule_flush1();
			});
		
		
		list->push_back(
			(Rule<WindowSA>){
				&WindowSA::in_rule_condition2();,
				&WindowSA::in_rule_body2();
				&WindowSA::in_rule_flush2();
			});
		
		
		list->push_back(
			(Rule<WindowSA>){
				&WindowSA::in_rule_condition3();,
				&WindowSA::in_rule_body3();
				&WindowSA::in_rule_flush3();
			});
		
		
		return list;
		
	}
	
	
	void windowSA::executeInternalControlFlow(double h, double dt)
	{
		this->doStep(window,h,dt);
	}
	
	bool WindowSA::out_rule_condition1(){
		return true;
	}
	void WindowSA::out_rule_body1(){
		this->stored_window_reaction_torque = getValueReal(window,WINDOWTAU);
	}
	void WindowSA::out_rule_flush1(){
		this->tau = -this->stored_window_reaction_torque;
	}
	bool WindowSA::out_rule_condition2(){
		return true;
	}
	void WindowSA::out_rule_body2(){
		this->stored_window_height = getValueReal(window,WINDOWDISP);
	}
	void WindowSA::out_rule_flush2(){
		this->disp = this->stored_window_height * 100;
	}
	shared_ptr<list<Rule<WindowSA>>> WindowSA::createOutputRules()
	{
		auto list = make_shared<list<Rule<WindowSA>>>()
		
		list->push_back(
			(Rule<WindowSA>){
				&WindowSA::out_rule_condition1();,
				&WindowSA::out_rule_body1();
				&WindowSA::out_rule_flush1();
			});
		
		
		list->push_back(
			(Rule<WindowSA>){
				&WindowSA::out_rule_condition2();,
				&WindowSA::out_rule_body2();
				&WindowSA::out_rule_flush2();
			});
		
		
		return list;
		
	}
	

}

