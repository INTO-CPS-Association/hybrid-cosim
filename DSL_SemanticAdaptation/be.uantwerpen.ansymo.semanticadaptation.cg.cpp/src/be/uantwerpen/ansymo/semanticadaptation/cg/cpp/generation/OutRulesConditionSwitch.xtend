package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation;

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.MappedScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import java.util.LinkedHashMap

public class OutRulesConditionSwitch extends RulesConditionSwitch {
	new(String adaptationClassName, String adaptationName,
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String, SAScalarVariable> SASVs, LinkedHashMap<String, GlobalInOutVariable> params) {
		super(adaptationClassName, adaptationName, "out_rule_", mSVars, SASVs, params, null);
	}

	override ReturnInformation casePort(Port object) {
		var retVal = new ReturnInformation();

		val type = mSVars.get(this.externalVariableOwner).get(object.name).mappedSv.type;
		val define = mSVars.get(this.externalVariableOwner).get(object.name).define;
		retVal.code = '''getValue«Conversions.fmiTypeToCppTypeCapitalized(type)»(«this.externalVariableOwner»,«define»)''';
		this.externalVariableOwnerIsSet = false;

		return retVal;
	}

}
