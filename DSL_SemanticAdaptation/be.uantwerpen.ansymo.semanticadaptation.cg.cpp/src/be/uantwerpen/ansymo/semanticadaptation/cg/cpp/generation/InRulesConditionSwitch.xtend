package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import java.util.LinkedHashMap
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.MappedScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CompositeOutputFunction
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InRulesBlock

class InRulesConditionSwitch extends RulesConditionSwitch {

	private Boolean inOutputFunction = false;

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

	public def LinkedHashMap<String, GlobalInOutVariable> getGlobalVars(InRulesBlock object) {
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
		var retVal = new ReturnInformation();

		if (inOutputFunction) {
			retVal.code = '''setValue(«object.lvalue.owner.name»,«mSVars.get(object.lvalue.owner.name).get(object.lvalue.ref.name).define»,«doSwitch(object.expr).code»)''';
			return retVal;
		} else {
			return super.caseAssignment(object);
		}
	}	

}
