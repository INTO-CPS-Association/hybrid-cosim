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
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.MappedScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SaveState
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Close
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.BreakStatement
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Rollback
import java.util.List

class ControlConditionSwitch extends RulesConditionSwitch {

	new(
		String adaptationClassName,
		String adaptationName,
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String, SAScalarVariable> SASVs,
		LinkedHashMap<String, GlobalInOutVariable> params,
		LinkedHashMap<String, GlobalInOutVariable> outVars
	) {
		super(adaptationClassName, adaptationName, "", mSVars, SASVs, params, outVars);
	}

	override ReturnInformation caseAssignment(Assignment object) {
		
		if (object.lvalue.owner !== null) {
			var retVal = new ReturnInformation();
			retVal.code = '''setValue(«object.lvalue.owner.name»,«mSVars.get(object.lvalue.owner.name).get(object.lvalue.ref.name).define»,«doSwitch(object.expr).code»)'''
			return retVal;
		} else {
			return super.caseAssignment(object);
		}
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
		tempDoSwitchCode += System.lineSeparator() + '''return «doSwitch(object.returnstatement.expr).code»;
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
		retVal.code = '''this->do_step(«object.fmu.name»,«doSwitch(object.h).code»,«doSwitch(object.t).code»)''';
		retVal.type = SVType.Integer;
		return retVal;
	}

	override ReturnInformation caseDoStep(DoStep object) {
		var retVal = new ReturnInformation();
		retVal.code = '''this->do_step(«object.fmu.name»,«doSwitch(object.h).code»,«doSwitch(object.t).code»)''';
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
	
	

	override ReturnInformation caseSaveState(SaveState object) {
		var retVal = new ReturnInformation();
		retVal.appendCode('''
		saveState(«object.fmu.name»)''')
		return retVal;
	}
	
	override ReturnInformation caseClose(Close object)
	{
		var retVal = new ReturnInformation();
		retVal.code = '''is_close(«object.args.map[e | doSwitch(e).code].join(", ")»)''';		
		return retVal;
	}
	
	override ReturnInformation caseBreakStatement(BreakStatement object){
		var retVal = new ReturnInformation();
		retVal.appendCode('''break''')
		return retVal;
	}
	
	override ReturnInformation caseRollback(Rollback object)
	{
		var retVal = new ReturnInformation();
		retVal.appendCode('''rollback(«object.fmu.name»)''')
		return retVal;
	}
}
