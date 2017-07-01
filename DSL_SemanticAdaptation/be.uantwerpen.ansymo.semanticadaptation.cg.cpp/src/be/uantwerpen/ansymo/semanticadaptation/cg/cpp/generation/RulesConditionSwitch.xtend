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

abstract class RulesConditionSwitch extends SemanticAdaptationSwitch<ReturnInformation> {
	// Global in and out variables
	protected var LinkedHashMap<String, GlobalInOutVariable> gVars = newLinkedHashMap();

	// Global params
	protected var LinkedHashMap<String, GlobalInOutVariable> params;

	protected final String adaptationName;

	protected final String adaptationClassName;

	private Integer count = 0;

	/** See the method {@link #createFunctionSignature(String, String)} and subclasses */
	private final String functionPrefix;

	protected List<String> functionSignatures = newArrayList();

	/*
	 * Intermediate variable used for referencing external FMU.
	 * It is necessary because of parsing error
	 */
	protected String externalVariableOwner;

	protected final LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars;
	protected final LinkedHashMap<String, SAScalarVariable> SASVs;

	protected boolean inRuleCondition;
	protected boolean inRuleTransition;
	protected boolean inRuleOutput;
	protected boolean inControlRule;

	// This is used for storing initialization information for global declarations.
	protected String constructorInitialization = "";
	// Flag to signal whether the declarations to be processed are global or local.
	protected boolean globalDeclaration = false;
	// Add scope information to this.
	protected var LinkedHashMap<String, SVType> localDeclarations = newLinkedHashMap();

	new(
		String adaptationClassName,
		String adaptationName,
		String functionPrefix,
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String, SAScalarVariable> SASVs,
		LinkedHashMap<String, GlobalInOutVariable> params
	) {
		this.params = params;
		this.SASVs = SASVs;
		this.adaptationName = adaptationName;
		this.adaptationClassName = adaptationClassName;
		this.functionPrefix = functionPrefix;
		this.mSVars = mSVars;
	}

	/*
	 * UTILITY FUNCTIONS 
	 */
	override ReturnInformation defaultCase(EObject object) {
		var retVal = new ReturnInformation();
		retVal.code = '''[«object.class»]''';
		return retVal;
	}

	private def Object convertTypeToObject(SVType type, Literal object) {
		switch (type) {
			case Real: {
				return (object as RealLiteral).value.doubleValue;
			}
			case Integer: {
				return (object as IntLiteral).value;
			}
			case Boolean: {
				return Boolean.parseBoolean((object as BoolLiteral).value);
			}
			default: {
			}
		}
	}

	public def getGlobalVars() { return this.gVars; }

	public def getConstructorInitialization() { return this.constructorInitialization; }

	/**
	 * This function adds a header style function signature to the list <i>functionsignatures</i> 
	 * and returns the source style function signature
	 */
	protected def String createFunctionSignature(String functionName, String type) {
		val functionSignature = this.functionPrefix + functionName + this.count + "()";
		this.functionSignatures.add(type + " " + functionSignature);
		return type + " " + this.adaptationClassName + "::" + functionSignature;
	}

	def void incrementCount() {
		this.count++;
	}

	/*
	 * COMPILATION FUNCTIONS
	 */
	protected def ReturnInformation doSwitch(EList<Declaration> gVars, InOutRules object) {

		this.globalDeclaration = true;

		var retVal = new ReturnInformation();

		// Get the global variables added to globalVars
		for (gVar : gVars) {
			constructorInitialization += doSwitch(gVar).code;
		}

		this.globalDeclaration = false;

		for (dataRule : object.eAllContents.toIterable.filter(DataRule)) {
			this.incrementCount;
			retVal.appendCode(doSwitch(dataRule).code);
		}

		return retVal;
	}

	override ReturnInformation caseInRulesBlock(InRulesBlock object) {
		return this.doSwitch(object.globalInVars, object);
	}

	override ReturnInformation caseOutRulesBlock(OutRulesBlock object) {

		return this.doSwitch(object.globalOutVars, object);
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

		val functionSignature = createFunctionSignature("condition", "bool");
		retVal.code = '''
			«functionSignature»{
				return «doSwitch(object.condition).code»;
			}
		''';

		return retVal;
	}

	override ReturnInformation caseStateTransitionFunction(StateTransitionFunction object) {
		var retVal = new ReturnInformation();

		val functionSig = createFunctionSignature("body", "void");
		retVal.code = '''
			«functionSig»{
				«IF object.expression !== null»
					«doSwitch(object.expression).code»
				«ENDIF»
				«IF object.statements !== null»
					«FOR stm : object.statements»
						«doSwitch(stm).code»
					«ENDFOR»
				«ENDIF»			
				«IF object.assignment !== null»
					«doSwitch(object.assignment).code»
				«ENDIF»
			}
		''';

		return retVal;
	}

	override ReturnInformation caseIf(If object) {
		var retVal = new ReturnInformation();
		retVal.code = '''
			if(«doSwitch(object.ifcondition).code»){
				«FOR stm : object.ifstatements»
					«doSwitch(stm).code»
				«ENDFOR»
			}
		''';

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

		retVal.code = '''«lValSwitch.code» = «rValSwitch.code»;''';
		return retVal;
	}

	override ReturnInformation caseMulti(Multi object) {

		val doSwitchLeft = doSwitch(object.left);
		val doSwitchRight = doSwitch(object.right);
		var retVal = new ReturnInformation(doSwitchLeft, doSwitchRight);
		retVal.code = '''«doSwitchLeft.code» * «doSwitchRight.code»''';
		return retVal;
	}

	override ReturnInformation caseDiv(Div object) {
		val doSwitchLeft = doSwitch(object.left);
		val doSwitchRight = doSwitch(object.right);
		var retVal = new ReturnInformation(doSwitchLeft, doSwitchRight);
		retVal.code = '''«doSwitchLeft.code» / «doSwitchRight.code»''';
		retVal.type = SVType.Real;
		retVal.forceType = true;
		return retVal;
	}

	override ReturnInformation caseNeg(Neg object) {

		var doSwitch = doSwitch(object.right);
		var retVal = new ReturnInformation(doSwitch);
		retVal.code = doSwitch.code;

		return retVal;
	}

	override ReturnInformation caseSingleVarDeclaration(SingleVarDeclaration object) {
		var retVal = new ReturnInformation();
		retVal.code = '''«object.name»''';
		return retVal;
	}

	override ReturnInformation caseCompositeOutputFunction(CompositeOutputFunction object) {

		var retVal = new ReturnInformation();
		val functionSig = createFunctionSignature("flush", "void");
		retVal.code = '''
			«functionSig»{
				«FOR stm : object.statements»
					«doSwitch(stm).code»
				«ENDFOR»
			}
		''';
		return retVal;
	}


	override ReturnInformation caseVariable(Variable object) {

		var retVal = new ReturnInformation();

		if (object.owner === null || object.owner.name == this.adaptationName) {

			if (SASVs.containsKey(object.ref.name) || gVars.containsKey(object.ref.name) ||
				params.containsKey(object.ref.name)) {

				retVal.code = '''this->«object.ref.name»''';

				if (SASVs.containsKey(object.ref.name)) {
					retVal.conSaSv = SASVs.get(object.ref.name);
				} else if (gVars.containsKey(object.ref.name)) {
					retVal.conGlobVar = gVars.get(object.ref.name);
				} else if (params.containsKey(object.ref.name)) {
					retVal.conGlobVar = params.get(object.ref.name);
				}
			} else if (localDeclarations.containsKey(object.ref.name)) {
				retVal.code = '''«object.ref.name»'''
				retVal.type = localDeclarations.get(object.ref.name);
			}

		} else {
			this.externalVariableOwner = object.owner.name;
			retVal.code = '''«doSwitch(object.ref).code»''';
		}
		return retVal;
	}

	override ReturnInformation caseLValueDeclaration(LValueDeclaration object) {

		var retVal = new ReturnInformation();
		retVal.code = '''«object.name»''';
		return retVal;
	}

	override ReturnInformation caseDeclaration(Declaration object) {
		var retVal = new ReturnInformation();

		for (SingleVarDeclaration decl : object.declarations) {
			var doSwitchRes = doSwitch(decl.expr);
			var String code = "";

			if (globalDeclaration) {
				// This is an in var, out var or crtl var declaration	
				code = '''
					this->«decl.name» = «doSwitchRes.code»;
				'''
				var globVar = new GlobalInOutVariable(decl.name, doSwitchRes.type);

				gVars.put(decl.name, globVar);
			} else {
				// This is a local declaration.
				val String type = Conversions.fmiTypeToCppType(doSwitchRes.type)
				code = '''«type» «decl.name» = «doSwitchRes.code»''';
				this.localDeclarations.put(decl.name, doSwitchRes.type);
			}
			retVal.appendCode = code;
		}

		return retVal;
	}

	override ReturnInformation caseIsSet(IsSet object) {
		var retInfo = new ReturnInformation();
		retInfo.code = '''this->isSet«(object.args as Variable).ref.name»''';
		return retInfo;
	}

	override ReturnInformation caseRealLiteral(RealLiteral object) {
		var retInfo = new ReturnInformation();
		retInfo.type = SVType.Real;
		retInfo.value = convertTypeToObject(retInfo.type, object);
		retInfo.code = '''«object.value»''';
		return retInfo;
	}

	override ReturnInformation caseIntLiteral(IntLiteral object) {
		var retInfo = new ReturnInformation();
		retInfo.type = SVType.Integer;
		retInfo.value = convertTypeToObject(retInfo.type, object);
		retInfo.code = '''«object.value»''';
		return retInfo;
	}

	override ReturnInformation caseBoolLiteral(BoolLiteral object) {
		var retInfo = new ReturnInformation();
		retInfo.type = SVType.Boolean;
		retInfo.value = convertTypeToObject(retInfo.type, object);
		retInfo.code = '''«object.value»''';

		return retInfo;
	}

	override ReturnInformation caseMin(Min object)
	{
		var retInfo = new ReturnInformation();
		var doSwitchResCode = newArrayList();
		for (expr : object.args) {
			val doSwitchRes_ = this.doSwitch(expr);
			doSwitchResCode.add(doSwitchRes_.code);
			retInfo = new ReturnInformation(retInfo, doSwitchRes_);
		} 
		retInfo.code = 
		'''
		min({«doSwitchResCode.join(",")»})
		'''
		return retInfo;
	}
	
	override ReturnInformation caseMinus(Minus object){
		val doSwitchLeft = doSwitch(object.left);
		val doSwitchRight = doSwitch(object.right);
		var retVal = new ReturnInformation(doSwitchLeft, doSwitchRight);
		retVal.code = '''«doSwitchLeft.code» - «doSwitchRight.code»''';
		return retVal;		
	}

}
