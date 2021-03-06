package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.MappedScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVType
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.BreakStatement
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Close
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ControlRuleBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CurrentTime
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CustomControlRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DoStep
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DoStepFun
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.GetNextInternalTimeStep
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Rollback
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SaveState
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Variable
import java.util.LinkedHashMap

class ControlConditionSwitch extends RulesConditionSwitch {

	new(
		String adaptationClassName,
		String adaptationName,
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String, SAScalarVariable> SASVs,
		LinkedHashMap<String, GlobalInOutVariable> params,
		LinkedHashMap<String, GlobalInOutVariable> inVars,
		LinkedHashMap<String, GlobalInOutVariable> outVars,
		LinkedHashMap<String, GlobalInOutVariable> crtlVars
	) {
		super(adaptationClassName, adaptationName, "", mSVars, SASVs, params, inVars, outVars, crtlVars);
	}
	
	override ReturnInformation caseAssignment(Assignment object) {
		if (object.lvalue.ref instanceof Port){
			return super.caseAssignmentToPort(object)
		} else {
			return super.caseAssignment(object);
		}
	}

	override ReturnInformation caseVariable(Variable object) {
		var retVal = new ReturnInformation();
		retVal = super.caseVariable(object);
		return retVal;
	}

	def LinkedHashMap<String, GlobalInOutVariable> getGlobalVars(ControlRuleBlock object) {
		if (object.globalCtrlVars !== null) {
			this.globalDeclaration = true;
			for (gVar : object.globalCtrlVars)
				doSwitch(gVar);
			this.globalDeclaration = false;
		}
		return this.gVars;
	}

	override ReturnInformation caseControlRuleBlock(ControlRuleBlock object) {
		var retVal = new ReturnInformation();

		retVal.appendCode(doSwitch(object.rule).code);

		return retVal;
	}

	override ReturnInformation caseCustomControlRule(CustomControlRule object) {
		var retVal = new ReturnInformation();

		val functionPrefix = "double ";
		val functionNameArgs = "executeInternalControlFlow(double t, double H)"
		functionSignatures.add(functionPrefix + functionNameArgs);
				
		val code = '''
		«functionPrefix+this.adaptationClassName»::«functionNameArgs» {
			«Utilities.getDebug(functionPrefix+this.adaptationClassName + "::" + functionNameArgs)»
			«FOR ruleStm : object.controlRulestatements»
			«val result = doSwitch(ruleStm)»
			«result.code»«if (!result.isExpression) ";"»
			«ENDFOR»
			
			return «doSwitch(object.returnstatement.expr).code»;
		}
		''';

		
		retVal.code = code;
		return retVal;
	}

	override ReturnInformation caseDoStepFun(DoStepFun object) {
		var retVal = new ReturnInformation();
		retVal.code = '''this->do_step(«object.fmu.name»,«doSwitch(object.t).code»,«doSwitch(object.t).code»-t,«doSwitch(object.h).code»);''';
		retVal.type = SVType.Integer;
		return retVal;
	}

	override ReturnInformation caseDoStep(DoStep object) {
		var retVal = new ReturnInformation();
		retVal.code = '''this->do_step(«object.fmu.name»,«doSwitch(object.t).code»,«doSwitch(object.t).code»-t,«doSwitch(object.h).code»);''';
		return retVal;
	}

	override ReturnInformation caseCurrentTime(CurrentTime object) {
		var retVal = new ReturnInformation();
		retVal.code = '''t''';
		retVal.type = SVType.Real;
		retVal.forceType = true;
		return retVal;
	}

	override ReturnInformation caseSaveState(SaveState object) {
		var retVal = new ReturnInformation();
		retVal.appendCode('''save_state(«object.fmu.name»)''')
		return retVal;
	}

	override ReturnInformation caseClose(Close object) {
		var retVal = new ReturnInformation();
		retVal.code = '''HyfMath::is_close(«object.args.map[e | doSwitch(e).code].join(", ")»)''';
		retVal.type = SVType.Boolean;
		return retVal;
	}

	override ReturnInformation caseBreakStatement(BreakStatement object) {
		var retVal = new ReturnInformation();
		retVal.appendCode('''break''')
		return retVal;
	}

	override ReturnInformation caseRollback(Rollback object) {
		var retVal = new ReturnInformation();
		retVal.appendCode('''rollback(«object.fmu.name»)''')
		return retVal;
	}

	override ReturnInformation caseGetNextInternalTimeStep(GetNextInternalTimeStep object)
	{
		var retVal = new ReturnInformation();
		retVal.type = SVType.Real;
		retVal.code = '''getNextTimeStep(«object.fmu.name»)''';
		return retVal;
	}
}
