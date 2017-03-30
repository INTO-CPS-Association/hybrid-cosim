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

abstract class InOutRulesConditionSwitch extends SemanticAdaptationSwitch<ReturnInformation> {

	protected var LinkedHashMap<String, Pair<SVType, Object>> globalVars = newLinkedHashMap();
	protected var LinkedHashMap<String, GlobalInOutVariable> globalVars2 = newLinkedHashMap();
	private var Pair<SVType, Object> lastVal;
	protected final String adaptationName;
	protected final String adaptationClassName;
	private Integer count = 0;
	private final String functionPrefix;
	protected List<String> functionSignatures = newArrayList();
	protected String externalVariableOwner;
	protected final LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars;
	protected final LinkedHashMap<String, SAScalarVariable> SASVs;
	protected boolean inRuleCondition;
	protected boolean inRuleTransition;
	protected boolean inRuleOutput;

	new(
		String adaptationClassName,
		String adaptationName,
		String functionPrefix,
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String, SAScalarVariable> SASVs
	) {
		this.SASVs = SASVs;
		this.adaptationName = adaptationName;
		this.adaptationClassName = adaptationClassName;
		this.functionPrefix = functionPrefix;
		this.mSVars = mSVars;
	}

	/*
	 * UTILITY FUNCTIONS 
	 */
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

	public def getVars() { return this.globalVars; }
	
	public def getGlobalVars() { return this.globalVars2; }

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
	override ReturnInformation caseOutRulesBlock(OutRulesBlock object) {
		var retVal = new ReturnInformation();

		// Get the global variables added to globalVars
		for (gVar : object.globalOutVars) {
			doSwitch(gVar)
		}
		for (dataRule : object.eAllContents.toIterable.filter(DataRule)) {
			this.incrementCount;
			retVal.appendCode(doSwitch(dataRule).code);
		}

		return retVal;

//		var cpp = ""
//		for (gVar : object.globalOutVars) {
//			doSwitch(gVar)
//		}
//		for (dataRule : object.eAllContents.toIterable.filter(DataRule)) {
//			this.incrementCount;
//			cpp += doSwitch(dataRule);
//		}
//		return cpp;
	}

	override ReturnInformation caseInRulesBlock(InRulesBlock object) {

		var retVal = new ReturnInformation();

		// Get the global variables added to globalVars
		for (gVar : object.globalInVars) {
			doSwitch(gVar)
		}

		for (DataRule dataRule : object.eAllContents.toIterable.filter(DataRule)) {
			// This is used for naming each datarule
			this.incrementCount;
			retVal.appendCode(doSwitch(dataRule).code);
		}

		return retVal;

//		var cpp = ""
//		for (gVar : object.globalInVars) {
//			doSwitch(gVar)
//		}
//		for (DataRule dataRule : object.eAllContents.toIterable.filter(DataRule)) {
//			this.incrementCount;
//			cpp += doSwitch(dataRule);
//		}
//		return cpp;
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
		retVal.code = 
			'''
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

//		val functionSignature = createFunctionSignature("condition", "bool");
//		'''
//			«functionSignature»{
//				return «doSwitch(object.condition)»;
//			}
//		''';
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

//		val functionSig = createFunctionSignature("body", "void");
//		'''
//			«functionSig»{
//				«IF object.expression !== null»
//					«doSwitch(object.expression)»
//				«ENDIF»
//				«IF object.statements !== null»
//					«FOR stm : object.statements»
//						«doSwitch(stm)»
//					«ENDFOR»
//				«ENDIF»			
//				«IF object.assignment !== null»
//					«doSwitch(object.assignment)»
//				«ENDIF»
//			}
//		''';
	}

	override ReturnInformation defaultCase(EObject object) {
		var retVal = new ReturnInformation();
		retVal.code = '''[«object.class»]''';
		return retVal;

//		return '''[«object.class»]''';
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

//		return '''
//			if(«doSwitch(object.ifcondition)»){
//				«FOR stm : object.ifstatements»
//					«doSwitch(stm)»
//				«ENDFOR»
//			}
//		''';
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

//		return '''«doSwitch(object.lvalue)» = «doSwitch(object.expr)»;'''
	}

	override ReturnInformation caseMulti(Multi object) {
		
		val doSwitchLeft = doSwitch(object.left);
		val doSwitchRight =  doSwitch(object.right);
		var retVal = new ReturnInformation(doSwitchLeft, doSwitchRight);
		retVal.code = '''«doSwitchLeft.code» * «doSwitchRight.code»''';
		return retVal;

//		return '''«doSwitch(object.left)» * «doSwitch(object.right)»''';
	}

	override ReturnInformation caseNeg(Neg object) {
		
		var doSwitch = doSwitch(object.right);
		var retVal = new ReturnInformation(doSwitch);
		retVal.code = doSwitch.code;

		return retVal;

//		return '''-«doSwitch(object.right)»'''
	}

	override ReturnInformation caseSingleVarDeclaration(SingleVarDeclaration object) {
		var retVal = new ReturnInformation();
		retVal.code = '''«object.name»''';
		return retVal;

//		var returnVal = '''«object.name»'''
//		return returnVal;
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

//		val functionSig = createFunctionSignature("flush", "void");
//		val returnVal = '''
//			«functionSig»{
//				«FOR stm : object.statements»
//					«doSwitch(stm)»
//				«ENDFOR»
//			}
//		''';
//		return returnVal;
	}

	override ReturnInformation caseVariable(Variable object) {

		var retVal = new ReturnInformation();

		if (object.owner === null || object.owner.name == this.adaptationName) {
			retVal.code = '''this->«object.ref.name»''';
			if (SASVs.containsKey(object.ref.name)) {
				retVal.conSaSv = SASVs.get(object.ref.name);
			} else if (globalVars2.containsKey(object.ref.name)) {
				retVal.conGlobVar = globalVars2.get(object.ref.name);
			}
		} else {
			// TODO: Extract the correct variable here
			this.externalVariableOwner = object.owner.name;
			retVal.code = '''«doSwitch(object.ref).code»''';
		}
		return retVal;

//		if (object.owner === null || object.owner.name == this.adaptationName) {
//			return '''this->«object.ref.name»''';
//		} else {
//			this.externalVariableOwner = object.owner.name;
//			return '''«doSwitch(object.ref)»''';
//		}
	}

	override ReturnInformation caseLValueDeclaration(LValueDeclaration object) {

		var retVal = new ReturnInformation();
		retVal.code = '''«object.name»''';
		return retVal;

//		return '''«object.name»'''
	}

	/*
	 * This is out var and in var declarations.
	 */
	override ReturnInformation caseDeclaration(Declaration object) {
		var retVal2 = new ReturnInformation();
		for (decl : object.declarations) {
			var doSwitchRes = doSwitch(decl.expr);

			retVal2.appendCode(doSwitchRes.code);

			var globVar = new GlobalInOutVariable();
			globVar.name = decl.name;
			globVar.value = doSwitchRes.value;
			globVar.type = doSwitchRes.type;

			globalVars2.put(decl.name, globVar);
		}

		return retVal2;

//		var returnVal = "";
//
//		for (decl : object.declarations) {
//			returnVal += doSwitch(decl.expr);
//			globalVars.put(decl.name, lastVal);
//		}
//		return returnVal;
	}

	override ReturnInformation caseIsSet(IsSet object) {
		var retInfo = new ReturnInformation();
//		retInfo.type = SVType.Real;
//		retInfo.value = convertTypeToObject(retInfo.type, object);
		retInfo.code = '''this->isSet«(object.args as Variable).ref.name»''';
		return retInfo;

//		return '''this->isSet«(object.args as Variable).ref.name»'''
	}

	override ReturnInformation caseRealLiteral(RealLiteral object) {
		var retInfo = new ReturnInformation();
		retInfo.type = SVType.Real;
		retInfo.value = convertTypeToObject(retInfo.type, object);
		retInfo.code = '''«object.value»''';
		return retInfo;

//		lastVal = convertType(SVType.Real, object);
//		return '''«object.value»''';
	}

	override ReturnInformation caseIntLiteral(IntLiteral object) {
		var retInfo = new ReturnInformation();
		retInfo.type = SVType.Integer;
		retInfo.value = convertTypeToObject(retInfo.type, object);
		retInfo.code = '''«object.value»''';
		return retInfo;

//		return '''«object.value»''';
	}

	override ReturnInformation caseBoolLiteral(BoolLiteral object) {
		var retInfo = new ReturnInformation();
		retInfo.type = SVType.Boolean;
		retInfo.value = convertTypeToObject(retInfo.type, object);
		retInfo.code = '''«object.value»''';

		return retInfo;

//		return '''«object.value»''';
	}

//	private def Pair<SVType, Object> convertType(SVType type, Literal object) {
//		switch (type) {
//			case Real: {
//				return type -> (object as RealLiteral).value.doubleValue;
//			}
//			default: {
//			}
//		}
//	}
}
