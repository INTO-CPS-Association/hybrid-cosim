package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation;

import java.util.LinkedHashMap
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.MappedScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable

public class OutRulesConditionSwitch extends InOutRulesConditionSwitch {
	new(String adaptationClassName, 
		String adaptationName,  
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String,SAScalarVariable> SASVs, LinkedHashMap<String, GlobalInOutVariable> params) {
		super(adaptationClassName, adaptationName, "out_rule_", mSVars, SASVs, params);
	}
	
	override ReturnInformation casePort(Port object){
		var retVal = new ReturnInformation();
		
		val type = mSVars.get(this.externalVariableOwner).get(object.name).mappedSv.type;
		val define = mSVars.get(this.externalVariableOwner).get(object.name).define;
		retVal.code = '''getValue«Conversions.fmiTypeToCppTypeCapitalized(type)»(«this.externalVariableOwner»,«define»)''';
		
		return retVal;
	}
}
