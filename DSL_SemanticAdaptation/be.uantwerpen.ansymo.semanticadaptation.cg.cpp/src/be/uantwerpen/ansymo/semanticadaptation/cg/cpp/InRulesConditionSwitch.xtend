package be.uantwerpen.ansymo.semanticadaptation.cg.cpp

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment
import java.util.LinkedHashMap
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CompositeOutputFunction
import java.util.ArrayList
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.StateTransitionFunction

class InRulesConditionSwitch extends InOutRulesConditionSwitch {

	private Boolean inOutputFunction = false;
	private Boolean inTransitionFunction = false;

	new(String adaptationClassName, String adaptationName, LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars) {
		super(adaptationClassName, adaptationName, "in_rule_", mSVars
		);
	}
	
	override String caseStateTransitionFunction(StateTransitionFunction object) {
		this.inTransitionFunction = true;
		val returnVal = super.caseStateTransitionFunction(object);
		this.inTransitionFunction = false;
		return returnVal;
	}

	override String caseCompositeOutputFunction(CompositeOutputFunction object) {
		this.inOutputFunction = true;
		val returnVal = super.caseCompositeOutputFunction(object);
		this.inOutputFunction = false;
		return returnVal;
	}

	override String caseAssignment(Assignment object) {
		// We need to record the assignments such that we can get the correct variability and such later on. In this case we are in input		
		if (inOutputFunction) {	'''
			setValue(«object.lvalue.owner.name»,«mSVars.get(object.lvalue.owner.name).get(object.lvalue.ref.name).define»,«doSwitch(object.expr)»);
		''';
		} else {
			super.caseAssignment(object);
		}
	}

}
