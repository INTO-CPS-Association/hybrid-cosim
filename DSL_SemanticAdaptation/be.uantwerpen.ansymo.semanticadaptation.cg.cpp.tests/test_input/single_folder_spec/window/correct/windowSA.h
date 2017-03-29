#include "SemanticAdaptation.h"
#include <memory>
#include "Fmu.h"

using namespace std;
using namespace fmi2;

namespace adaptation
{

	class WindowSA : public SemanticAdaptation<WindowSA>{
		public:
			WindowSA(shared_ptr<string> resourceLocation);
			virtual ~WindowSA();
			
			void setFmiValue(fmi2ValueReference id, int value);
			void setFmiValue(fmi2ValueReference id, bool value);
			void setFmiValue(fmi2ValueReference id, double value);
		
			int getFmiValueInteger(fmi2ValueReference id);
			bool getFmiValueBoolean(fmi2ValueReference id);
			double getFmiValueDouble(fmi2ValueReference id);
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
			shared_ptr<list<Rule<WindowSA>>> createInputRules();
			
			/*out rules*/
			bool out_rule_condition1();
			void out_rule_body1();
			void out_rule_flush1();
			bool out_rule_condition2();
			void out_rule_body2();
			void out_rule_flush2();
			shared_ptr<list<Rule<WindowSA>>> createOutputRules();
			
			void executeInternalControlFlow(double h, double dt);
			
			shared_ptr<FmuComponent> window;
			
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
}
