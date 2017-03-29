package be.uantwerpen.ansymo.semanticadaptation.cg.cpp

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ControlRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ControlRuleBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CurrentTime
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CustomControlRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DoStep
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.StepSize
import java.util.LinkedHashMap

class ControlConditionSwitch extends InOutRulesConditionSwitch {

	new(String adaptationClassName, 
		String adaptationName, 
		LinkedHashMap<String, Pair<String, Integer>> scalars,
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
		
		
//		var cpp = "";
//		for (crtlRule : obj.eAllContents.toIterable.filter(ControlRule)) {
//			cpp += doSwitch(crtlRule);
//		}
//
//		return cpp;
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
//		var String returnVal = "";
//
//		for (ruleStm : object.controlRulestatements) {
//			returnVal += doSwitch(ruleStm);
//		}

//		var functionPrefix = "void ";
//		var functionNameArgs = "executeInternalControlFlow(double h, double dt)"
//		functionSignatures.add(functionPrefix + functionNameArgs + ";");
//		return '''
//		«functionPrefix+this.adaptationName»::«functionNameArgs»
//		{
//			«returnVal»
//		}''';
	}

	override ReturnInformation caseDoStep(DoStep object) {
		var retVal = new ReturnInformation();
		retVal.code = '''this->doStep(«object.fmu.name»,«doSwitch(object.h)»,«doSwitch(object.t)»);''';
		return retVal;
//		return '''this->doStep(«object.fmu.name»,«doSwitch(object.h)»,«doSwitch(object.t)»);''';
	}

	override ReturnInformation caseStepSize(StepSize object) {
		var retVal = new ReturnInformation();
		retVal.code = '''h''';
		return retVal;
//		return '''h''';
	}

	override ReturnInformation caseCurrentTime(CurrentTime object) {
		var retVal = new ReturnInformation();
		retVal.code = '''dt''';
		return retVal;
//		return '''dt''';
	}
}
