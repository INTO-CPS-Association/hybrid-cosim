package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation;

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.MappedScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import java.util.LinkedHashMap
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.OutRulesBlock

class OutRulesConditionSwitch extends RulesConditionSwitch {
	new(String adaptationClassName, String adaptationName,
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String, SAScalarVariable> SASVs, LinkedHashMap<String, GlobalInOutVariable> params,
		LinkedHashMap<String, GlobalInOutVariable> inVars, LinkedHashMap<String, GlobalInOutVariable> outVars,
		LinkedHashMap<String, GlobalInOutVariable> crtlVars) {
		super(adaptationClassName, adaptationName, "out_rule_", mSVars, SASVs, params, inVars, outVars, crtlVars);
	}

	def LinkedHashMap<String, GlobalInOutVariable> getGlobalVars(OutRulesBlock object) {
		if (object.globalOutVars !== null) {
			this.globalDeclaration = true;
			for (gVar : object.globalOutVars)
				doSwitch(gVar);
			this.globalDeclaration = false;
		}
		return this.gVars;
	}

	override ReturnInformation caseOutRulesBlock(OutRulesBlock object) {

		return this.doSwitch(object.globalOutVars, object);
	}

	override ReturnInformation casePort(Port object) {
		var retVal = new ReturnInformation();
		val portName = if (object.alias !== null) BuildUtilities.stripDelimiters(object.alias) else object.name; // remove delimiters from string
		val fmu_sVar = mSVars.get(this.externalVariableOwner)
		val sVar = fmu_sVar.get(portName)
		val type = sVar.mappedSv.type;
		val define = mSVars.get(this.externalVariableOwner).get(portName).define;
		retVal.code = '''getValue«Conversions.fmiTypeToGetValueString(type)»(«this.externalVariableOwner»,«define»)''';
		retVal.type = type;
		return retVal;
	}
	
}
