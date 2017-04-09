package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ParamDeclarations
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SingleParamDeclaration
import java.util.LinkedHashMap

class ParamConditionSwitch extends GeneralConditionSwitch {
	var LinkedHashMap<String, GlobalInOutVariable> gVars;
	new(LinkedHashMap<String, GlobalInOutVariable> gVars) {
		this.gVars = gVars;
	}

	override ReturnInformation caseParamDeclarations(ParamDeclarations object) {
		var retInfo = new ReturnInformation();
		for (SingleParamDeclaration declaration : object.declarations) {
			var doSwitchRes = doSwitch(declaration);
			retInfo.code = retInfo.code +
				'''
					«doSwitchRes.code»
				'''
		}
		return retInfo;
	}

	override ReturnInformation caseSingleParamDeclaration(SingleParamDeclaration object) {
		val doSwitchRes = doSwitch(object.expr);
		var GlobalInOutVariable gVar = new GlobalInOutVariable();
		gVar.type = doSwitchRes.type;
		gVar.name = object.name;
		// TODO: Does this hold?
		gVar.value = doSwitchRes.value;
		this.gVars.put(gVar.name, gVar);		
		val retInfo = new ReturnInformation();
		retInfo.code = 
		'''
			this->«gVar.name» = «doSwitchRes.code»;
		'''
		return retInfo;

	}

}
