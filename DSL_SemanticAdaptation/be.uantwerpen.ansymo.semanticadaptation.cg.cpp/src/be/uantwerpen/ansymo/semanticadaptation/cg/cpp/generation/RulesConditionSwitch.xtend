package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.util.SemanticAdaptationSwitch
import java.util.LinkedHashMap
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVType
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable
import java.util.List
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.MappedScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ReturnInformation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Literal
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.RealLiteral
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.IntLiteral
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.BoolLiteral
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.OutRulesBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DataRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InRulesBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.RuleCondition
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.StateTransitionFunction
import org.eclipse.emf.ecore.EObject
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Multi
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Neg
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SingleVarDeclaration
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.If
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CompositeOutputFunction
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Variable
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.LValueDeclaration
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Declaration
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.IsSet
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Div
import org.eclipse.emf.common.util.EList
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InOutRules
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Min
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.exceptions.TypeException
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Minus
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.For
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SaveState
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Rollback
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Range
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Close
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.BreakStatement
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CurrentTime
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Var
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Plus
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.LessThan

class RulesConditionSwitch extends BasicConditionSwitch {
	// Global params
	protected var LinkedHashMap<String, GlobalInOutVariable> params;

	protected final String adaptationName;

	protected final String adaptationClassName;

	protected Integer count = 0;

	/** See the method {@link #createFunctionSignature(String, String)} and subclasses */
	public final String functionPrefix;

	protected List<String> functionSignatures = newArrayList();

	/*
	 * Intermediate variable used for referencing external FMU.
	 * Currently only used by OutRulesConditionSwitch. 
	 */
	protected String externalVariableOwner;

	protected final LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars;
	protected final LinkedHashMap<String, SAScalarVariable> SASVs;

	// Global in and out variables
	protected var LinkedHashMap<String, GlobalInOutVariable> gVars = newLinkedHashMap();
	LinkedHashMap<String, GlobalInOutVariable> inVars;
	LinkedHashMap<String, GlobalInOutVariable> outVars;
	LinkedHashMap<String, GlobalInOutVariable> crtlVars;

	protected boolean inRuleCondition;
	protected boolean inRuleTransition;
	protected boolean inRuleOutput;
	protected boolean inControlRule;

	// Flag to signal whether the declarations to be processed are global or local.
	protected boolean globalDeclaration = false;
	// Add scope information to this.
	protected var LinkedHashMap<String, SVType> localDeclarations = newLinkedHashMap();

	protected String forLoopIterVar;
	protected boolean forLoopIterVarIsSet = false;

	new(
		String adaptationClassName,
		String adaptationName,
		String functionPrefix,
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String, SAScalarVariable> SASVs,
		LinkedHashMap<String, GlobalInOutVariable> params,
		LinkedHashMap<String, GlobalInOutVariable> inVars,
		LinkedHashMap<String, GlobalInOutVariable> outVars,
		LinkedHashMap<String, GlobalInOutVariable> crtlVars
	) {
		super();
		this.params = params;
		this.SASVs = SASVs;
		this.adaptationName = adaptationName;
		this.adaptationClassName = adaptationClassName;
		this.functionPrefix = functionPrefix;
		this.mSVars = mSVars;
		this.outVars = outVars;
		this.inVars = inVars;
		this.crtlVars = crtlVars;
	}

	/*
	 * UTILITY FUNCTIONS 
	 */
	/**
	 * This function adds a header style function signature to the list <i>functionsignatures</i> 
	 * and returns the source style function signature
	 */
	public def String createFunctionSignature(String functionName, String type, int count,
		List<String> functionSignatures) {
		val functionSignature = this.functionPrefix + functionName + count + "()";
		functionSignatures.add(type + " " + functionSignature);
		return type + " " + this.adaptationClassName + "::" + functionSignature;
	}

	public def getDataRuleCount() { return this.count; }

	def void incrementCount() {
		this.count++;
	}

	/*
	 * COMPILATION FUNCTIONS
	 */
	public def Pair<String, LinkedHashMap<String, GlobalInOutVariable>> getGlobalVars(EList<Declaration> gVars) {

		// Get the global variables added to globalVars
		this.globalDeclaration = true;
		val List<String> constructorInits = newArrayList();
		for (gVar : gVars) {
			constructorInits.add('''«doSwitch(gVar).code»''');
		}
		this.globalDeclaration = false;
		return constructorInits.join(System.lineSeparator) -> this.gVars;
	}

	protected def ReturnInformation doSwitch(EList<Declaration> gVars, InOutRules object) {
		var retVal = new ReturnInformation();

		for (dataRule : object.eAllContents.toIterable.filter(DataRule)) {
			this.incrementCount;
			retVal.appendCode(doSwitch(dataRule).code);
		}

		return retVal;
	}

	override ReturnInformation caseDataRule(DataRule object) {
		var retVal = new ReturnInformation();
		inRuleCondition = true;
		val conditionSwitch = doSwitch(object.condition);
		inRuleCondition = false;
		inRuleTransition = true;
		val transitionSwitch = doSwitch(object.statetransitionfunction);
		inRuleTransition = false;
		inRuleOutput = true;
		val outputSwitch = doSwitch(object.outputfunction);
		inRuleOutput = false;
		retVal.code = '''
			«conditionSwitch.code»
			«transitionSwitch.code»
			«outputSwitch.code»
		'''

		return retVal;
	}

	override ReturnInformation caseRuleCondition(RuleCondition object) {
		var retVal = new ReturnInformation();

		val functionSignature = createFunctionSignature("condition", "bool", this.count, this.functionSignatures);
		retVal.code = '''
			«functionSignature»{
				return «doSwitch(object.condition).code»;
			}
		''';

		return retVal;
	}

	override ReturnInformation caseStateTransitionFunction(StateTransitionFunction object) {
		var retVal = new ReturnInformation();

		val functionSig = createFunctionSignature("body", "void", this.count, this.functionSignatures);
		retVal.code = '''
			«functionSig»{
				«IF object.expression !== null»
					«val result = doSwitch(object.expression)»
					«result.code»«if (!result.isExpression) ";"»
				«ENDIF»
				«IF object.statements !== null»
					«FOR stm : object.statements»
						«val result = doSwitch(stm)»
						«result.code»«if (!result.isExpression) ";"»
					«ENDFOR»
				«ENDIF»			
				«IF object.assignment !== null»
					«val result = doSwitch(object.assignment)»
					«result.code»«if (!result.isExpression) ";"»
				«ENDIF»
			}
		''';

		return retVal;
	}

	override ReturnInformation caseIf(If object) {
		var retVal = new ReturnInformation();
		retVal.isExpression = true;
		retVal.code = '''
			if(«doSwitch(object.ifcondition).code»){
				«FOR stm : object.ifstatements»
					«val result = doSwitch(stm)»
					«result.code»«if (!result.isExpression) ";"»
				«ENDFOR»
			}
		''';
		if (object.elsestatements.length > 0) {
			retVal.appendCode('''
				else {
					«FOR stm : object.elsestatements»
						«doSwitch(stm).code»;
					«ENDFOR»
				}
			''')
		}

		return retVal;
	}

	private def calcConSaSvData(SAScalarVariable SASV, ReturnInformation rI) {
		if (SASV !== null) {
			if (rI.typeIsSet) {
				SASV.type = rI.type;
				SASV.variability = Conversions.fmiTypeToFmiVariability(rI.type);
				return;
			} else if (rI.conGlobVar !== null) {
				SASV.type = rI.conGlobVar.type;
				SASV.variability = Conversions.fmiTypeToFmiVariability(rI.conGlobVar.type);
				return;
			}
		}
		throw new Exception("Not enough information to determine content of the SASV: " + SASV.name);

	}

	override ReturnInformation caseAssignment(Assignment object) {
		var retVal = new ReturnInformation();
		var lValSwitch = doSwitch(object.lvalue);
		var rValSwitch = doSwitch(object.expr);

		// Here we set the information necessary to create a scalar variables in the model description for the SA.
		if (inRuleTransition) {
			if (rValSwitch.conSaSv !== null) {
				calcConSaSvData(rValSwitch.conSaSv, lValSwitch);
			}
		} else if (inRuleOutput) {
			calcConSaSvData(lValSwitch.conSaSv, rValSwitch);
		}

		retVal.code = '''«lValSwitch.code» = «rValSwitch.code»''';

		return retVal;
	}

	override ReturnInformation caseSingleVarDeclaration(SingleVarDeclaration object) {
		var retVal = new ReturnInformation();
		var exprRes = doSwitch(object.expr);
		var String code = "";
		if (globalDeclaration) {
			// This is an in var, out var or crtl var declaration
			code = '''this->internalState.«object.name» = «exprRes.code»''';
			var globVar = new GlobalInOutVariable(object.name, exprRes.type);
			gVars.put(object.name, globVar)
		} else {
			// This is a local declaration.
			val String type = Conversions.fmiTypeToCppType(exprRes.type)
			code = '''«type» «object.name» = «exprRes.code»''';
			this.localDeclarations.put(object.name, exprRes.type);
		}
		retVal.code = code;
		return retVal;

	}

	override ReturnInformation caseCompositeOutputFunction(CompositeOutputFunction object) {

		var retVal = new ReturnInformation();
		val functionSig = createFunctionSignature("flush", "void", this.count, this.functionSignatures);
		retVal.code = '''
			«functionSig»{
				«FOR stm : object.statements»
					«val result = doSwitch(stm)»
					«result.code»«if(!result.isExpression) ";"»
				«ENDFOR»
			}
		''';
		return retVal;
	}

	override ReturnInformation caseVariable(Variable object) {

		var retVal = new ReturnInformation();

		if (object.owner === null || object.owner.name == this.adaptationName) {

			if ((SASVs !== null && SASVs.containsKey(object.ref.name)) || params.containsKey(object.ref.name) ||
				(outVars !== null && outVars.containsKey(object.ref.name)) ||
				(inVars !== null && inVars.containsKey(object.ref.name)) ||
				(crtlVars !== null && crtlVars.containsKey(object.ref.name))) {

				retVal.code = '''this->internalState.«object.ref.name»''';

				if (SASVs !== null && SASVs.containsKey(object.ref.name)) {
					retVal.conSaSv = SASVs.get(object.ref.name);
				} else if (crtlVars !== null && crtlVars.containsKey(object.ref.name)) {
					retVal.conGlobVar = crtlVars.get(object.ref.name);
				} else if (params.containsKey(object.ref.name)) {
					retVal.conGlobVar = params.get(object.ref.name);
				} else if (outVars !== null && outVars.containsKey(object.ref.name)) {
					retVal.conGlobVar = outVars.get(object.ref.name);
				} else if (inVars !== null && inVars.containsKey(object.ref.name)) {
					retVal.conGlobVar = inVars.get(object.ref.name);
				}
			} else if (localDeclarations.containsKey(object.ref.name)) {
				retVal.code = '''«object.ref.name»'''
				retVal.type = localDeclarations.get(object.ref.name);
			} else {
				throw new Exception("Variable not found: " + object.ref.name);
			}

		} else {
			this.externalVariableOwner = object.owner.name;
			val res =  doSwitch(object.ref);
			retVal.code = res.code;
			retVal.type = res.type;
		}
		return retVal;
	}

	override ReturnInformation caseLValueDeclaration(LValueDeclaration object) {

		var retVal = new ReturnInformation();
		retVal.code = '''«object.name»''';
		return retVal;
	}

	override ReturnInformation caseVar(Var object) {
		var retVal = new ReturnInformation();
		return retVal;
	}

	override ReturnInformation caseDeclaration(Declaration object) {
		var retVal = new ReturnInformation();
		val code = '''
			«FOR decl : object.declarations»
				«val res = doSwitch(decl)»
				«res.code»;
			«ENDFOR»
		'''

		retVal.code = code;
		retVal.isExpression = true;

		return retVal;
	}

	override ReturnInformation caseIsSet(IsSet object) {
		var retInfo = new ReturnInformation();
		retInfo.code = '''this->internalState.isSet«(object.args as Variable).ref.name»''';
		return retInfo;
	}

	override ReturnInformation caseFor(For object) {
		{
			var retVal = new ReturnInformation();
			retVal.isExpression = true;
			val iterator = doSwitch(object.iterator);
			forLoopIterVar = iterator.code;
			forLoopIterVarIsSet = true;
			val iterable = doSwitch(object.iterable);
			retVal.appendCode('''
				for (int «forLoopIterVar» = «iterable.code»){
					«FOR stm : object.statements»
						«val result = doSwitch(stm)»		
						«result.code»«if (!result.isExpression) ";"»
					«ENDFOR»
				}
			''')
			forLoopIterVarIsSet = false;
			return retVal;
		}
	}

	override ReturnInformation caseRange(Range object) {
		var retVal = new ReturnInformation();
		val left = doSwitch(object.left);
		val right = doSwitch(object.right);
		retVal.appendCode('''«left.code»; «forLoopIterVar»<=«right.code»; «forLoopIterVar»++''')
		return retVal;
	}

}
