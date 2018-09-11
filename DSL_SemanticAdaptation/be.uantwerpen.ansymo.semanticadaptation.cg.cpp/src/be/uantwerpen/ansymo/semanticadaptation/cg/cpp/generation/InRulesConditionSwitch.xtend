package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.MappedScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.log.Log
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CompositeOutputFunction
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InRulesBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import java.util.LinkedHashMap

class InRulesConditionSwitch extends RulesConditionSwitch {

	Boolean inOutputFunction = false;

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
		super(adaptationClassName, adaptationName, "in_rule_", mSVars, SASVs, params, inVars, outVars, crtlVars);
	}

	def LinkedHashMap<String, GlobalInOutVariable> getGlobalVars(InRulesBlock object) {
		if (object.globalInVars !== null) {
			this.globalDeclaration = true;
			for (gVar : object.globalInVars)
				doSwitch(gVar);
			this.globalDeclaration = false;
		}
		return this.gVars;
	}

	override ReturnInformation caseInRulesBlock(InRulesBlock object) {
		return this.doSwitch(object.globalInVars, object);
	}

	override ReturnInformation caseCompositeOutputFunction(CompositeOutputFunction object) {

		this.inOutputFunction = true;
		val ReturnInformation retVal = super.caseCompositeOutputFunction(object);
		this.inOutputFunction = false;
		return retVal;
	}

	override ReturnInformation caseAssignment(Assignment object) {
		if (inOutputFunction) {
			if (object.lvalue.ref instanceof Port){
				return super.caseAssignmentToPort(object)
			} else {
				throw new Exception("Assignment to a non_port variable.")
			}
		} else {
			return super.caseAssignment(object);
		}
	}	

}
