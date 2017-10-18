package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVType
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.BoolLiteral
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ParamDeclarations
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.RealLiteral
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SingleParamDeclaration
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.util.SemanticAdaptationSwitch
import org.eclipse.emf.ecore.EObject
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.IntLiteral

class GeneralConditionSwitch extends SemanticAdaptationSwitch<ReturnInformation> {
	override ReturnInformation caseParamDeclarations(ParamDeclarations object) {
		for (SingleParamDeclaration declaration : object.declarations) {
			doSwitch(declaration);
		}
		return new ReturnInformation();
	}

	override ReturnInformation caseIntLiteral(IntLiteral object){
		var retInfo = new ReturnInformation();
		retInfo.type = SVType.Integer;
		retInfo.value = Conversions.convertTypeToObject(retInfo.type, object);
		retInfo.code = '''«object.value»''';
		return retInfo;
	}

	override ReturnInformation caseRealLiteral(RealLiteral object) {
		var retInfo = new ReturnInformation();
		retInfo.type = SVType.Real;
		retInfo.value = Conversions.convertTypeToObject(retInfo.type, object);
		retInfo.code = '''«object.value»''';
		return retInfo;
	}
	
	override ReturnInformation caseBoolLiteral(BoolLiteral object) {
		var retInfo = new ReturnInformation();
		retInfo.type = SVType.Boolean;
		retInfo.value = Conversions.convertTypeToObject(retInfo.type, object);
		retInfo.code = '''«object.value»''';
		return retInfo;
	}

	override ReturnInformation defaultCase(EObject object) {
		var retVal = new ReturnInformation();
		retVal.code = '''[«object.class»]''';
		System.out.println('''[«object.class»]''');
		return retVal;

//		return '''[«object.class»]''';
	}
}
