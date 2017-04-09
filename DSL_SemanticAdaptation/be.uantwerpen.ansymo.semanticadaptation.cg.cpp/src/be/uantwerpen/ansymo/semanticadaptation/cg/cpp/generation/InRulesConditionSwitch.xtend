package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import java.util.LinkedHashMap
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.MappedScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CompositeOutputFunction
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable

class InRulesConditionSwitch extends InOutRulesConditionSwitch {

	private Boolean inOutputFunction = false;

	new(String adaptationClassName, String adaptationName, LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars, LinkedHashMap<String,SAScalarVariable> SASVs
		,LinkedHashMap<String, GlobalInOutVariable> params
	) {
		super(adaptationClassName, adaptationName, "in_rule_", mSVars, SASVs, params);
	}


	override ReturnInformation caseCompositeOutputFunction(CompositeOutputFunction object) {
		
		this.inOutputFunction = true;
		val ReturnInformation retVal = super.caseCompositeOutputFunction(object);
		this.inOutputFunction = false;
		return retVal;
	
//		this.inOutputFunction = true;
//		val returnVal = super.caseCompositeOutputFunction(object);
//		this.inOutputFunction = false;
//		return returnVal;
	}

	override ReturnInformation caseAssignment(Assignment object) {
		var retVal = new ReturnInformation();
				
		if (inOutputFunction) {
			retVal.code = 	
				'''
					setValue(«object.lvalue.owner.name»,«mSVars.get(object.lvalue.owner.name).get(object.lvalue.ref.name).define»,«doSwitch(object.expr).code»);
				''';
			return retVal;
		}
		else
		{
			return super.caseAssignment(object);
		}
	


//		// We need to record the assignments such that we can get the correct variability and such later on. In this case we are in input		
//		if (inOutputFunction) {	'''
//			setValue(«object.lvalue.owner.name»,«mSVars.get(object.lvalue.owner.name).get(object.lvalue.ref.name).define»,«doSwitch(object.expr)»);
//		''';
//		} else {
//			super.caseAssignment(object);
//		}
	}

}
