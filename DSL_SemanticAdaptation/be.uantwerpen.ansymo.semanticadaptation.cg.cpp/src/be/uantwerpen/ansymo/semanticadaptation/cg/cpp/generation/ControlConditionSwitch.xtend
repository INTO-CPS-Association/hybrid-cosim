package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import java.util.LinkedHashMap
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ControlRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ControlRuleBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CustomControlRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DoStep
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.StepSize
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CurrentTime

class ControlConditionSwitch extends InOutRulesConditionSwitch {

	new(String adaptationClassName, 
		String adaptationName, 
		LinkedHashMap<String,SAScalarVariable> SASVs
	) {
		super(adaptationClassName, adaptationName, "", null, SASVs);
	}

	override ReturnInformation caseControlRuleBlock(ControlRuleBlock obj) {
		var retVal = new ReturnInformation();

		for (crtlRule : obj.eAllContents.toIterable.filter(ControlRule)) {
			retVal.appendCode(doSwitch(crtlRule).code);
		}

		return retVal;
	}

	override ReturnInformation caseCustomControlRule(CustomControlRule object) {
		var retVal = new ReturnInformation();

		var String tempDoSwitchCode = "";
		for (ruleStm : object.controlRulestatements) {
			tempDoSwitchCode += doSwitch(ruleStm).code;
		}
		
		var functionPrefix = "void ";
		var functionNameArgs = "executeInternalControlFlow(double h, double dt)"
		functionSignatures.add(functionPrefix + functionNameArgs + ";");
		retVal.code = 
			'''
				«functionPrefix+this.adaptationName»::«functionNameArgs»
				{
					«tempDoSwitchCode»
				}
			''';

		return retVal;
	}

	override ReturnInformation caseDoStep(DoStep object) {
		var retVal = new ReturnInformation();
		retVal.code = '''this->doStep(«object.fmu.name»,«doSwitch(object.h)»,«doSwitch(object.t)»);''';
		return retVal;
	}

	override ReturnInformation caseStepSize(StepSize object) {
		var retVal = new ReturnInformation();
		retVal.code = '''h''';
		return retVal;
	}

	override ReturnInformation caseCurrentTime(CurrentTime object) {
		var retVal = new ReturnInformation();
		retVal.code = '''dt''';
		return retVal;
	}
}
