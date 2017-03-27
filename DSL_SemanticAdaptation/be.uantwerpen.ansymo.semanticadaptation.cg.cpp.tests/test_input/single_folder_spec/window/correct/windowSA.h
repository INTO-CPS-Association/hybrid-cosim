#define WINDOWDISP 0
#define WINDOWDISPLACEMENT 1
#define WINDOWFRICTION 2
#define WINDOWREACTION_FORCE 3
#define WINDOWSPEED 4
#define WINDOWTAU 5
#define WINDOWV 6
#define WINDOWB 7
#define WINDOWR 8

#include "SemanticAdaptation.h"
#include <memory>
#include "Fmu.h"

using namespace std;
using namespace fmi2

class windowSA : public SemanticAdaptation<windowSA>{
	public:
		windowSA();
		virtual ~windowSA();
		
		void setFmiValue(fmi2ValueReference id, int value);
		void setFmiValue(fmi2ValueReference id, bool value);
		void setFmiValue(fmi2ValueReference id, double value);
	
		int getFmiValueInteger(fmi2ValueReference id);
		bool getFmiValueBoolean(fmi2ValueReference id);
		double getFmiValueDouble(fmi2ValueReference id);
	private:
		
		windowSA* getRuleThis();
		
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
		shared_ptr<list<Rule<windowSA>>> createInputRules;
		
		/*out rules*/
		bool out_rule_condition1();
		void out_rule_body1();
		void out_rule_flush1();
		bool out_rule_condition2();
		void out_rule_body2();
		void out_rule_flush2();
		shared_ptr<list<Rule<windowSA>>> createOutputRules;
		
		void executeInternalControlFlow(double h, double dt);
		
		shared_ptr<Fmu> window;
		
		double disp;
		double displacement;
		bool isSetdisplacement;								
		double friction;
		double reaction_force;
		bool isSetreaction_force;								
		double speed;
		bool isSetspeed;								
		double tau;
		double v;
		double b;
		double r;
		
		double stored_window_reaction_torque;
		double stored_window_height;
		
		double stored_windowsa_reaction_force;
		double stored_windowsa_displacement;
		double stored_windowsa_speed;
}
