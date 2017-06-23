package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVType
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ControlRuleBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CurrentTime
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CustomControlRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DoStep
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DoStepFun
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.StepSize
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Variable
import java.util.LinkedHashMap

class ControlConditionSwitch extends RulesConditionSwitch {

	new(
		String adaptationClassName,
		String adaptationName,
		LinkedHashMap<String, SAScalarVariable> SASVs,
		LinkedHashMap<String, GlobalInOutVariable> params
	) {
		super(adaptationClassName, adaptationName, "", null, SASVs, params);
	}

	override ReturnInformation caseVariable(Variable object) {
		var retVal = new ReturnInformation();

		// H and t are protected variables.
		if ((object.owner === null || object.owner.name == this.adaptationName) &&
			(object.ref.name == "H" || object.ref.name == "t")) {
			retVal.type = SVType.Real;
			retVal.forceType = true;
			retVal.code = object.ref.name;
		} else {
			retVal = super.caseVariable(object);
		}

		return retVal;
	}

	override ReturnInformation caseControlRuleBlock(ControlRuleBlock object) {
		this.globalDeclaration = true;

		var retVal = new ReturnInformation();

		// Get the global variables added to globalVars
		for (gVar : object.globalCtrlVars) {
			constructorInitialization += doSwitch(gVar).code;
		}

		this.globalDeclaration = false;
		retVal.appendCode(doSwitch(object.rule).code);

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
		var functionNameArgs = "executeInternalControlFlow(double H, double t)"
		functionSignatures.add(functionPrefix + functionNameArgs);
		retVal.code = '''
			«functionPrefix+this.adaptationClassName»::«functionNameArgs»
			{
				«tempDoSwitchCode»
			}
		''';
		return retVal;
	}

	override ReturnInformation caseDoStepFun(DoStepFun object) {
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
		retVal.code = '''H''';
		return retVal;
	}

	override ReturnInformation caseCurrentTime(CurrentTime object) {
		var retVal = new ReturnInformation();
		retVal.code = '''t''';
		return retVal;
	}
}
