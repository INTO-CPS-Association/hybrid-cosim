package be.uantwerpen.ansymo.semanticadaptation.cg.cpp

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.BoolLiteral
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CompositeOutputFunction
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DataRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.If
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.IsSet
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.LValueDeclaration
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.RealLiteral
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.RuleCondition
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SingleVarDeclaration
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.StateTransitionFunction
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Variable
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.util.SemanticAdaptationSwitch
import java.util.LinkedHashMap
import java.util.List
import org.eclipse.emf.ecore.EObject
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Multi
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.IntLiteral
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Neg
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Declaration
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Literal
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InRulesBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.OutRulesBlock

abstract class InOutRulesConditionSwitch extends SemanticAdaptationSwitch<String> {

	protected var LinkedHashMap<String, Pair<SVType, Object>> globalVars = newLinkedHashMap();
	private var Pair<SVType, Object> lastVal;
	protected final String adaptationName;
	protected final LinkedHashMap<String, Pair<String, Integer>> scalars;
	private Integer count = 0;
	private final String functionPrefix;
	protected List<String> functionSignatures = newArrayList();
	protected String externalVariableOwner;

	new(String adaptationName, LinkedHashMap<String, Pair<String, Integer>> scalars, String functionPrefix) {
		this.adaptationName = adaptationName;
		this.scalars = scalars;
		this.functionPrefix = functionPrefix;
	}

	/**
	 * This function adds a header style function signature to the list <i>functionsignatures</i> 
	 * and returns the source style function signature
	 */
	protected def String createFunctionSignature(String functionName, String type) {
		val functionSignature = this.functionPrefix + functionName + this.count + "()";
		this.functionSignatures.add(type + " " + functionSignature);
		return type + " " + this.adaptationName + "::" + functionSignature;
	}

	def void incrementCount() {
		this.count++;
	}

	override String caseOutRulesBlock(OutRulesBlock object) {
		var cpp = ""
		for (gVar : object.globalOutVars) {
			doSwitch(gVar)
		}
		for (dataRule : object.eAllContents.toIterable.filter(DataRule)) {
			this.incrementCount;
			cpp += doSwitch(dataRule);
		}
		return cpp;
	}

	override String caseInRulesBlock(InRulesBlock object) {
		var cpp = ""
		for (gVar : object.globalInVars) {
			doSwitch(gVar)
		}
		for (dataRule : object.eAllContents.toIterable.filter(DataRule)) {
			this.incrementCount;
			cpp += doSwitch(dataRule);
		}
		return cpp;
	}

	override String caseBoolLiteral(BoolLiteral object) {
		return '''«object.value»''';
	}

	override String caseRuleCondition(RuleCondition object) {
		val functionSignature = createFunctionSignature("condition", "bool");
		'''
			«functionSignature»{
				return «doSwitch(object.condition)»;
			}
		''';
	}

	override String caseStateTransitionFunction(StateTransitionFunction object) {
		val functionSig = createFunctionSignature("body", "void");
		'''
			«functionSig»{
				«IF object.expression !== null»
					«doSwitch(object.expression)»
				«ENDIF»
				«IF object.statements !== null»
					«FOR stm : object.statements»
						«doSwitch(stm)»
					«ENDFOR»
				«ENDIF»			
				«IF object.assignment !== null»
					«doSwitch(object.assignment)»
				«ENDIF»
			}
		''';
	}

	override String caseDataRule(DataRule object) {
		return '''
			«doSwitch(object.condition)»
			«doSwitch(object.statetransitionfunction)»
			«doSwitch(object.outputfunction)»
		'''
	}

	override String defaultCase(EObject object) {
		return '''[«object.class»]''';
	}

	override String caseIf(If object) {
		return '''
			if(«doSwitch(object.ifcondition)»){
				«FOR stm : object.ifstatements»
					«doSwitch(stm)»
				«ENDFOR»
			}
		''';
	}

	override String caseLValueDeclaration(LValueDeclaration object) {
		return '''«object.name»'''
	}

	override String caseAssignment(Assignment object) {
		return '''«doSwitch(object.lvalue)» = «doSwitch(object.expr)»;'''
	}

	override String caseIsSet(IsSet object) {
		return '''this->isSet«(object.args as Variable).ref.name»'''
	}

	override String caseMulti(Multi object) {
		return '''«doSwitch(object.left)» * «doSwitch(object.right)»''';
	}

	override String caseIntLiteral(IntLiteral object) {
		return '''«object.value»''';
	}

	override String caseNeg(Neg object) {
		return '''-«doSwitch(object.right)»'''
	}

	override String caseVariable(Variable object) {
		if (object.owner === null || object.owner.name == this.adaptationName) {
			return '''this->«object.ref.name»''';
		} else {
			this.externalVariableOwner = object.owner.name;
			return '''«doSwitch(object.ref)»''';
		}
	}

	override String caseSingleVarDeclaration(SingleVarDeclaration object) {
		var returnVal = '''«object.name»'''
		return returnVal;
	}

	override String caseCompositeOutputFunction(CompositeOutputFunction object) {
		val functionSig = createFunctionSignature("flush", "void");
		val returnVal = '''
			«functionSig»{
				«FOR stm : object.statements»
					«doSwitch(stm)»
				«ENDFOR»
			}
		''';
		return returnVal;
	}

	public def getVars() { return this.globalVars; }

	override String caseDeclaration(Declaration object) {
		var returnVal = "";

		for (decl : object.declarations) {
			returnVal += doSwitch(decl.expr);
			globalVars.put(decl.name, lastVal);
		}
		return returnVal;
	}

	override String caseRealLiteral(RealLiteral object) {
		lastVal = convertType(SVType.Real, object);
		return '''«object.value»''';
	}

	private def Pair<SVType, Object> convertType(SVType type, Literal object) {
		switch (type) {
			case Real: {
				return type -> (object as RealLiteral).value.doubleValue;
			}
			default: {
			}
		}
	}

}
