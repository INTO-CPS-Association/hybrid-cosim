package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import java.util.LinkedHashMap

public class OutRulesConditionSwitch extends InOutRulesConditionSwitch {


	private boolean inBody = false;

	new(String adaptationClassName, 
		String adaptationName,  
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String,SAScalarVariable> SASVs) {
		super(adaptationClassName, adaptationName, "out_rule_", mSVars, SASVs);
	}
	
	override ReturnInformation casePort(Port object){
		var retVal = new ReturnInformation();
		
		val type = mSVars.get(this.externalVariableOwner).get(object.name).mappedSv.type.toString;
		val define = mSVars.get(this.externalVariableOwner).get(object.name).define;
		retVal.code = '''getValue«type»(«this.externalVariableOwner»,«define»)''';
		
		return retVal;
		
		
//		val type = mSVars.get(this.externalVariableOwner).get(object.name).mappedSv.type.toString;
//		val define = mSVars.get(this.externalVariableOwner).get(object.name).define;
//		return '''getValue«type»(«this.externalVariableOwner»,«define»)'''
	}
}
