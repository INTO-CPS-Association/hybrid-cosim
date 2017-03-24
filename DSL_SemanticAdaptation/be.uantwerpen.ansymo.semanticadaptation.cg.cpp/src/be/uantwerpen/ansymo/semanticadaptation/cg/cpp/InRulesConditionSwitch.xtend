package be.uantwerpen.ansymo.semanticadaptation.cg.cpp

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment
import java.util.LinkedHashMap
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CompositeOutputFunction

class InRulesConditionSwitch extends InOutRulesConditionSwitch {

	private Boolean inOutput = false;

	new(String adaptationName, LinkedHashMap<String, Pair<String, Integer>> scalars) {
		super(adaptationName, scalars, "in_rule_");
	}

	override String caseCompositeOutputFunction(CompositeOutputFunction object) {
		this.inOutput = true;
		val returnVal = super.caseCompositeOutputFunction(object);
		this.inOutput = false;
		return returnVal;
	}

	override String caseAssignment(Assignment object) {
		if (inOutput) {	'''
			setValue(«object.lvalue.owner.name»,«scalars.get(object.lvalue.owner.name+object.lvalue.ref.name).key»,«doSwitch(object.expr)»);
		''';
		} else {
			super.caseAssignment(object);
		}
	}

}
