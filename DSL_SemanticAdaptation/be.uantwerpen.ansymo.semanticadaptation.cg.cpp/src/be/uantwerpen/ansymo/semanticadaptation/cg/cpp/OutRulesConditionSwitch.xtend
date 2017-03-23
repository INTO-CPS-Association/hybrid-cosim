package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

import java.util.LinkedHashMap;

import org.eclipse.xtext.xbase.lib.Pair;

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment;
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.StateTransitionFunction

public class OutRulesConditionSwitch extends InOutRulesConditionSwitch {


	private boolean inBody = false;

	new(String adaptationName, LinkedHashMap<String, Pair<String, Integer>> scalars) {
		super(adaptationName, scalars, "out_rule_");
	}
	
	override String casePort(Port object){
		return '''getValue(«this.externalVariableOwner»,«this.scalars.get(this.externalVariableOwner+object.name).key»)'''
	}
}
