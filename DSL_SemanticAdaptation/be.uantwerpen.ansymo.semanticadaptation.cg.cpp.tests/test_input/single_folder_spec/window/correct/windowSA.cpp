#include "windowSA.h"

windowSA::windowSA(shared_ptr<std::string> resourceLocation) : SemanticAdaptation(createInputRules(),createOutputRules())
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


windowSA* windowSA::getRuleThis()
{
	return this;
}


bool windowSA::in_rule_condition1(){
	return true;
}
void windowSA::in_rule_body1(){
	if(this->isSetreaction_force){
		this->stored_windowsa_reaction_force = this->reaction_force;
	}
}
void windowSA::in_rule_flush1(){
	setValue(window,WINDOWREACTION_FORCE,this->stored_windowsa_reaction_force);
}
bool windowSA::in_rule_condition2(){
	return true;
}
void windowSA::in_rule_body2(){
	if(this->isSetdisplacement){
		this->stored_windowsa_displacement = this->displacement;
	}
}
void windowSA::in_rule_flush2(){
	setValue(window,WINDOWDISPLACEMENT,this->stored_windowsa_displacement);
}
bool windowSA::in_rule_condition3(){
	return true;
}
void windowSA::in_rule_body3(){
	if(this->isSetspeed){
		this->stored_windowsa_speed = this->speed;
	}
}
void windowSA::in_rule_flush3(){
	setValue(window,WINDOWSPEED,this->stored_windowsa_speed);
}
shared_ptr<list<Rule<windowSA>>> windowSA::createInputRules()
{
	auto list = make_shared<list<Rule<windowSA>>>()
	
	list->push_back(
		(Rule<windowSA>){
			&windowSA::bool in_rule_condition1();,
			&windowSA::void in_rule_body1();
			&windowSA::void in_rule_flush1();
		});
	
	
	list->push_back(
		(Rule<windowSA>){
			&windowSA::bool in_rule_condition2();,
			&windowSA::void in_rule_body2();
			&windowSA::void in_rule_flush2();
		});
	
	
	list->push_back(
		(Rule<windowSA>){
			&windowSA::bool in_rule_condition3();,
			&windowSA::void in_rule_body3();
			&windowSA::void in_rule_flush3();
		});
	
	
	return list;
	
}

bool windowSA::out_rule_condition1(){
	return true;
}
void windowSA::out_rule_body1(){
	this->stored_window_reaction_torque = getValue(window,WINDOWTAU);
}
void windowSA::out_rule_flush1(){
	this->tau = -this->stored_window_reaction_torque;
}
bool windowSA::out_rule_condition2(){
	return true;
}
void windowSA::out_rule_body2(){
	this->stored_window_height = getValue(window,WINDOWDISP);
}
void windowSA::out_rule_flush2(){
	this->disp = this->stored_window_height * 100;
}
shared_ptr<list<Rule<windowSA>>> windowSA::createOutputRules()
{
	auto list = make_shared<list<Rule<windowSA>>>()
	
	list->push_back(
		(Rule<windowSA>){
			&windowSA::bool out_rule_condition1();,
			&windowSA::void out_rule_body1();
			&windowSA::void out_rule_flush1();
		});
	
	
	list->push_back(
		(Rule<windowSA>){
			&windowSA::bool out_rule_condition2();,
			&windowSA::void out_rule_body2();
			&windowSA::void out_rule_flush2();
		});
	
	
	return list;
	
}

void windowSA::executeInternalControlFlow(double h, double dt)
{
	this->doStep(window,h,dt);
}
double  windowSA::getFmiValueDouble(fmi2ValueReference id)
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

String  windowSA::getFmiValueString(fmi2ValueReference id)
{
	return "";
}

int  windowSA::getFmiValueInteger(fmi2ValueReference id)
{
	return 0;
}

bool  windowSA::getFmiValueBool(fmi2ValueReference id)
{
	return false;
}

void windowSA::setFmiValue(fmi2ValueReference id, double value)
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

void windowSA::setFmiValue(fmi2ValueReference id, String value)
{
}

void windowSA::setFmiValue(fmi2ValueReference id, int value)
{
}

void windowSA::setFmiValue(fmi2ValueReference id, bool value)
{
}
