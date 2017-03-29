package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

import java.util.LinkedHashMap;

import org.eclipse.xtext.xbase.lib.Pair;

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment;
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.StateTransitionFunction
import java.util.ArrayList

public class OutRulesConditionSwitch extends InOutRulesConditionSwitch {


	private boolean inBody = false;

	new(String adaptationClassName, 
		String adaptationName,  

		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars) {
		super(adaptationClassName, adaptationName, "out_rule_", mSVars);
	}
	
	override String casePort(Port object){
		//TODO getValueBoolean, getValueInteger, getValueString, getValueReal
		val type = mSVars.get(this.externalVariableOwner).get(object.name).mappedSv.type.toString;
		val define = mSVars.get(this.externalVariableOwner).get(object.name).define;
		return '''getValue«type»(«this.externalVariableOwner»,«define»)'''
	}
}
