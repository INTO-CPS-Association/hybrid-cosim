
	#ifndef SRC_WINDOWSA_H
	#define SRC_WINDOWSA_H

	#include "SemanticAdaptation.h"
	#include <memory>
	#include "Fmu.h"
	
	using namespace std;
	using namespace fmi2;
	
	namespace adaptation
	{
		
		#define WINDOWDISPLACEMENT 0
		#define WINDOWFRICTION 1
		#define WINDOWHEIGHT 2
		#define WINDOWREACTION_FORCE 3
		#define WINDOWREACTION_TORQUE 4
		#define WINDOWSPEED 5
		#define WINDOWV 6
		#define WINDOWB 7
		#define WINDOWR 8
		
		#define WINDOWSAREACTION_FORCE 0
		#define WINDOWSADISPLACEMENT 1
		#define WINDOWSASPEED 2
		#define WINDOWSADISP 3
		#define WINDOWSATAU 4
	
		class WindowSA : public SemanticAdaptation<WindowSA>, public enable_shared_from_this<WindowSA>
		{
			public:
				WindowSA(shared_ptr<string> resourceLocation, const fmi2CallbackFunctions* functions);
				void initialize();
				virtual ~WindowSA();
				
				void setFmiValue(fmi2ValueReference id, int value);
				void setFmiValue(fmi2ValueReference id, bool value);
				void setFmiValue(fmi2ValueReference id, double value);
				void setFmiValue(fmi2ValueReference id, string value);
			
				int getFmiValueInteger(fmi2ValueReference id);
				bool getFmiValueBoolean(fmi2ValueReference id);
				double getFmiValueReal(fmi2ValueReference id);
				string getFmiValueString(fmi2ValueReference id);
				
			private:
				
				WindowSA* getRuleThis();
				
				/*in rules*/
				bool in_rule_condition1();
				void in_rule_body1();
				void in_rule_flush1();
				bool in_rule_condition2();
				void in_rule_body2();
				void in_rule_flush2();
				bool in_rule_condition3();
				void in_rule_body3();
				void in_rule_flush3();
				shared_ptr<list<Rule<WindowSA>>> createInputRules();;
				
				/*out rules*/
				bool out_rule_condition1();
				void out_rule_body1();
				void out_rule_flush1();
				bool out_rule_condition2();
				void out_rule_body2();
				void out_rule_flush2();
				shared_ptr<list<Rule<WindowSA>>> createOutputRules();;
				
				void executeInternalControlFlow(double h, double dt);;
				
				shared_ptr<FmuComponent> window;
				
				double reaction_force;
				bool isSetreaction_force;
				double displacement;
				bool isSetdisplacement;
				double speed;
				bool isSetspeed;
				double disp;
				double tau;
				
				double stored_window_reaction_torque;
				double stored_window_height;
				double stored_windowsa_reaction_force;
				double stored_windowsa_displacement;
				double stored_windowsa_speed;
		};
	}
