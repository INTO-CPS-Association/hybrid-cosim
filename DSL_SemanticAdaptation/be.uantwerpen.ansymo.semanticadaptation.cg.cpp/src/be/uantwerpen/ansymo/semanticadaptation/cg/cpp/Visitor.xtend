package be.uantwerpen.ansymo.semanticadaptation.cg.cpp

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.util.SemanticAdaptationSwitch
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import org.eclipse.xtext.xbase.interpreter.impl.XbaseInterpreter
import com.google.inject.Inject
import com.google.inject.Provider
import org.eclipse.xtext.xbase.interpreter.IEvaluationContext
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Expression
import org.eclipse.xtext.xbase.interpreter.IEvaluationResult

class Visitor<CharSequence> extends SemanticAdaptationSwitch<String> {
	
	override String caseSemanticAdaptation(SemanticAdaptation adaptatoin) {
		return '''a''';		
	}
	
	override String caseExpression(Expression object){
		return '''object''';
	}
	
}