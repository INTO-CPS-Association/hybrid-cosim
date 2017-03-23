package be.uantwerpen.ansymo.semanticadaptation.cg.cpp

import java.util.LinkedHashMap
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CustomControlRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DoStep
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.StepSize
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CurrentTime

class ControlConditionSwitch<CharSequence> extends InOutRulesConditionSwitch {

	new(String adaptationName, LinkedHashMap<String, Pair<String, Integer>> scalars) {
		super(adaptationName, scalars, "");
	}
	
	override String caseCustomControlRule(CustomControlRule object) {
		var String returnVal = "";
		
		for(ruleStm : object.controlRulestatements)
		{
			returnVal += doSwitch(ruleStm);	
		}
		
		var functionPrefix = "void ";
		var functionNameArgs = "executeInternalControlFlow(double h, double dt)"
		functionSignatures.add(functionPrefix+functionNameArgs+";");
		return '''
		«functionPrefix+this.adaptationName»::«functionNameArgs»
		{
			«returnVal»
		}''';
	}
	
	override String caseDoStep(DoStep object){
		return '''this->doStep(«object.fmu.name»,«doSwitch(object.h)»,«doSwitch(object.t)»);'''
	}
	
	override String caseStepSize(StepSize object){
			return '''h''';
	}
	
	override String caseCurrentTime(CurrentTime object){
		return '''dt''';
	}
}
