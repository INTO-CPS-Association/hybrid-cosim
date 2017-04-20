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
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DoStepFun
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVType

class ControlConditionSwitch extends InOutRulesConditionSwitch {

	new(String adaptationClassName, 
		String adaptationName, 
		LinkedHashMap<String,SAScalarVariable> SASVs
	) {
		super(adaptationClassName, adaptationName, "", null, SASVs, newLinkedHashMap());
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
		tempDoSwitchCode += System.lineSeparator() + '''return «doSwitch(object.returnstatement).code»;
			''';
		
		var functionPrefix = "double ";
		var functionNameArgs = "executeInternalControlFlow(double h, double dt)"
		functionSignatures.add(functionPrefix + functionNameArgs);
		retVal.code = 
			'''
				«functionPrefix+this.adaptationClassName»::«functionNameArgs»
				{
					«tempDoSwitchCode»
				}
			''';
		return retVal;
	}

	override ReturnInformation caseDoStepFun(DoStepFun object)
	{
		var retVal = new ReturnInformation();
		retVal.code = '''this->do_step(«object.fmu.name»,«doSwitch(object.h).code»,«doSwitch(object.t).code»);''';
		retVal.type = SVType.Integer;
		return retVal;
	}

	override ReturnInformation caseDoStep(DoStep object) {
		var retVal = new ReturnInformation();
		retVal.code = '''this->do_step(«object.fmu.name»,«doSwitch(object.h).code»,«doSwitch(object.t).code»);''';
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
