package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import be.uantwerpen.ansymo.semanticadaptation.generator.SemanticAdaptationGenerator
import org.eclipse.xtext.generator.IFileSystemAccess2

import org.eclipse.xtext.generator.IGeneratorContext
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import org.eclipse.emf.ecore.resource.Resource
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Adaptation
import java.util.ArrayList
import java.util.LinkedHashMap
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.MappedScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InnerFMU
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.exceptions.IncorrectAmountOfElementsException
import java.io.File
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import org.eclipse.emf.common.util.EList
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVCausality
import java.util.Collection
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InOutRules
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InRulesBlock
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.InOutRulesBlockResult
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.OutRulesBlock
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ControlRuleBlock
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.RulesBlockResult
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ScalarVariable
import java.util.List
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVType
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ParamDeclarations
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.InnerFMUData
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.IORuleType
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.RuleType
import org.eclipse.emf.ecore.EObject
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Declaration

class CppGenerator extends SemanticAdaptationGenerator {
	private var IFileSystemAccess2 fsa;
	private List<File> resourcePaths = newArrayList();

	override void doGenerate(Resource resource, IFileSystemAccess2 fsa, IGeneratorContext context) {
		this.fsa = fsa;
		for (SemanticAdaptation type : resource.allContents.toIterable.filter(SemanticAdaptation)) {
			type.compile;
		}
	}

	// TODO: Verify adaptation.name is not a C++ keyword
	def void compile(SemanticAdaptation adaptation) {
		for (Adaptation adap : adaptation.elements.filter(Adaptation)) {
			// Value used for scoping variables in the .sa file
			val adapInteralRefName = adap.name;

			// The CPP class name
			val adapClassName = adap.name.toFirstUpper;

			// This is the external name used in the model description file for the semantic adaptation FMU
			val adapExternalName = adap.type.name;

			// List of inner FMUs
			var ArrayList<InnerFMUData> innerFMUsData = newArrayList();
			val innerFmus = adap.inner.eAllContents.toList.filter(InnerFMU);
			if (innerFmus.isEmpty) {
				throw new IncorrectAmountOfElementsException("The adaptation does not contain any InnerFMUs.")
			}

			/*
			 * This map will contain scalar variables from the FMUs defined in InnerFMU.
			 * The structure is fmuName -> (SVName -> mappedSV) where SVName = mappedSV.name for easy lookup.
			 * The mappedSV contains the original scalar variable and extra data such as define name.
			 */
			var LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mappedScalarVariables = newLinkedHashMap();

			/*
			 * Loading the FMU defined in InnerFMU, the related model description file and its scalar variables.
			 */
			// TODO: Add support for multiple inner fmus. Only partially supported
			var ModelDescription md;
			for (fmu : adap.inner.eAllContents.toList.filter(InnerFMU)) {
				val fmuFile = new File(fmu.path.replace('\"', ''));
				this.resourcePaths.add(fmuFile);
				md = new ModelDescription(fmu.name, fmu.type.name, fmuFile);
				innerFMUsData.add(new InnerFMUData(fmu.name, fmu.type.name, md.guid));
				// fmus.add(fmu.name -> fmu.type.name);
				val LinkedHashMap<String, MappedScalarVariable> mSV = newLinkedHashMap();
				for (sv : md.sv.values) {
					var mappedSv = new MappedScalarVariable(sv);
					mappedSv.define = (mappedSv.mappedSv.owner + mappedSv.mappedSv.name).toUpperCase;
					mSV.put(mappedSv.mappedSv.name, mappedSv);
				}
				mappedScalarVariables.put(fmu.name, mSV);
			}

			// C++ Defines for accessing FMU scalar variables.
			val String fmusDefines = calcDefines(mappedScalarVariables);

			/*
			 * This map contains all the ScalarVariables for the semantic adaptation. 
			 * Some of them are not populated yet, but they will be during the compilation of the in and out rule blocks. 
			 */
			var LinkedHashMap<String, SAScalarVariable> SASVs = calcSASVsFromInportsOutports(adapInteralRefName,
				adap.inports, adap.outports, mappedScalarVariables)

			// C++ defines for accessing semantic adaptation scalar variables 
			val String SADefines = calcSADefines(SASVs.values);

			// Compile Params
			var LinkedHashMap<String, GlobalInOutVariable> params = newLinkedHashMap;
			val String paramsConstructorSource = compileParams(params, adap.params);

			// Handles cases like this: output ports tau <- loop_sa.tau		
			var List<Port> outPortsWithSrcDep = newArrayList();
			if (adap.outports !== null) {
				outPortsWithSrcDep = adap.outports.filter[x|x.sourcedependency !== null].toList;
			}

			// The three rule blocks
			val inRuleBlock = adap.in;
			val outRuleBlock = adap.out;
			val crtlRuleBlock = adap.control;

			// Get the control vars, in vars, and out vars				
			val inVars = if(inRuleBlock !== null) compileRuleBlockVars(inRuleBlock.globalInVars, params);
			var outVars = if(outRuleBlock !== null) compileRuleBlockVars(outRuleBlock.globalOutVars, params);
			val crtlVars = if(crtlRuleBlock !== null) compileRuleBlockVars(crtlRuleBlock.globalCtrlVars, params);
			/*
			 * Support for source dependency: output ports tau <- loop_sa.tau
			 * Only carried out for outVars.
			 * TODO: Do for inVars
			 */ 
			for (Port port : outPortsWithSrcDep) {
				val name = '''stored_«port.sourcedependency.owner.name»_«port.sourcedependency.port.name»;''';
				val type = mappedScalarVariables.get(port.sourcedependency.owner.name).get(
					port.sourcedependency.port.name).mappedSv.type;
				val globVar = new GlobalInOutVariable(name, type);
				val sourceDepType = mappedScalarVariables.get(port.sourcedependency.owner.name).get(
					port.sourcedependency.port.name).mappedSv.type;
				val constructorInit = '''this->«name» = «Conversions.fmiTypeToCppDefaultValue(sourceDepType)»'''
				if (outVars !== null) {
					outVars.value.put(name, globVar);
					outVars = outVars.key.concat(constructorInit) -> outVars.value;
				} else {
					val LinkedHashMap<String, GlobalInOutVariable> gVars = newLinkedHashMap();
					gVars.put(name, globVar)
					outVars = constructorInit -> gVars;
				}
			}

			// Compile the in rules
			val inRuleResult = compileInOutRuleBlocks(IORuleType.Input, adaptation.eAllContents.toIterable.filter(
				InRulesBlock).map[x|x as InOutRules], adapClassName, adapInteralRefName, mappedScalarVariables, SASVs,
				params, inVars.value, outVars.value, crtlVars.value, newArrayList());

			// Compile the out rules
			val outRuleResult = compileInOutRuleBlocks(IORuleType.Output, adaptation.eAllContents.toIterable.filter(
				OutRulesBlock).map[x|x as InOutRules], adapClassName, adapInteralRefName, mappedScalarVariables, SASVs,
				params, inVars.value, outVars.value, crtlVars.value, outPortsWithSrcDep);

			// Compile the Control Rules. These might use the out vars, so pass these along.
			val crtlRuleResult = compileControlRuleBlock(adaptation.eAllContents.toIterable.filter(ControlRuleBlock),
				adapClassName, adapInteralRefName, mappedScalarVariables, SASVs, params, inVars.value, outVars.value,
				crtlVars.value);

			/*
			 * Compile the constructor, destructor and initialize functions
			 */
			val String deAndConstructorAndInitializeSource = compileDeAndConstructorAndInitialize(
				adapClassName,
				innerFMUsData,
				md.guid,
				paramsConstructorSource,
				inVars.key,
				outVars.key,
				crtlVars.key
			);

			/*
			 * Compile getRuleThis function
			 */
			val String getRuleThisSource = compileGetRuleThis(adapClassName);

			/*
			 * The in and out rules have populated the semantic adaptation scalar variables we can generate the getFmiValue* and setFmiValue functions.
			 */
			val String getFuncsSource = compileGetFmiValueFunctions(adapClassName, SASVs);
			val String setFuncsSource = compileSetFmiValueFunctions(adapClassName, SASVs);

			// Compile the source file
			val String sourceInclude = '''#include "«adapClassName».h"''';
			val sourceFile = compileSource(
				sourceInclude,
				deAndConstructorAndInitializeSource,
				getRuleThisSource,
				getFuncsSource,
				setFuncsSource,
				inRuleResult.generatedCpp,
				outRuleResult.generatedCpp,
				crtlRuleResult.generatedCpp
			);
			fsa.generateFile(adapClassName + ".cpp", sourceFile);

			// Merge the global variables for use in compiling the header file.
			// TODO: Check for duplicates
			var LinkedHashMap<String, GlobalInOutVariable> allGVars = newLinkedHashMap();
			allGVars.putAll(params);
			allGVars.putAll(inVars.value);
			allGVars.putAll(outVars.value);
			allGVars.putAll(crtlVars.value);

			// Compile the header file
			val headerFile = compileHeader(
				adapClassName,
				fmusDefines,
				SADefines,
				inRuleResult.functionSignatures,
				outRuleResult.functionSignatures,
				crtlRuleResult.functionSignatures,
				allGVars,
				innerFMUsData,
				SASVs.values.map[CalcSVar()].toList
			);
			fsa.generateFile(adapClassName + ".h", headerFile);

			// Compile the model description file
			val modelDescCreator = new ModelDescriptionCreator(adapExternalName);
			val modelDescription = modelDescCreator.generateModelDescription(SASVs.values);
			fsa.generateFile("modelDescription.xml", modelDescription);

			// Compile the fmu.cpp file
			val fmuCppFile = StaticGenerators.GenFmuCppFile(adapClassName);
			fsa.generateFile("Fmu.cpp", fmuCppFile);

		}
	}

	def String compileParams(LinkedHashMap<String, GlobalInOutVariable> gVars, EList<ParamDeclarations> params) {
		val paramsConditionSwitch = new ParamConditionSwitch(gVars);
		var String paramsConstructorSource = "";
		for (paramDecl : params) {
			val doSwitchRes = paramsConditionSwitch.doSwitch(paramDecl);
			paramsConstructorSource += doSwitchRes.code;
		}
		return paramsConstructorSource;
	}

	def calcSADefines(Collection<SAScalarVariable> variables) {
		var ArrayList<String> defines = newArrayList();

		for (SASV : variables) {
			defines.add("#define " + SASV.defineName + " " + SASV.valueReference);
		}

		return defines.join("\n");
	}

	def calcDefines(LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> map) {
		var ArrayList<String> defines = newArrayList();

		for (fmuEntries : map.entrySet) {
			for (MappedScalarVariable mSV : fmuEntries.value.values) {
				defines.add("#define " + mSV.define + " " + mSV.valueReference);
			}
		}

		return defines.join("\n");
	}

	// Compiles the final source file
	def String compileSource(String include, String constructor, String getRuleThis, String getFunctions,
		String setFunctions, String inFunctions, String outFunctions, String controlFunction) {
		return '''
			«include»
			
			namespace adaptation 
			{
				«constructor»
				
				«getRuleThis»
				
				«getFunctions»
				
				«setFunctions»
				
				«inFunctions»
				
				«controlFunction»
				
				«outFunctions»
			
			}
			
		'''
	}

	/*
	 * Compiles the header file split into two: The first part contains the includes and using namespace definitions and start the ,
	 * the second part contains the class
	 */
	def String compileHeader(String adapClassName, String fmusDefines, String SADefines, List<String> inRulesFuncSig,
		List<String> outRulesFuncSig, List<String> crtlRulesFuncSig,
		LinkedHashMap<String, GlobalInOutVariable> globalVariables, ArrayList<InnerFMUData> fmus,
		Collection<ScalarVariable> sVars) {
		return '''
			
				#ifndef SRC_«adapClassName.toUpperCase»_H
				#define SRC_«adapClassName.toUpperCase»_H
			
				#include "SemanticAdaptation.h"
				#include <memory>
				#include "Fmu.h"
				
				using namespace std;
				using namespace fmi2;
				
				namespace adaptation
				{
					
					«fmusDefines»
					
					«SADefines»
				
					class «adapClassName» : public SemanticAdaptation<«adapClassName»>, public enable_shared_from_this<«adapClassName»>
					{
						public:
							«adapClassName»(shared_ptr<std::string> fmiInstanceName, shared_ptr<string> resourceLocation, const fmi2CallbackFunctions* functions);
							void initialize();
							virtual ~«adapClassName»();
							
							void setFmiValue(fmi2ValueReference id, int value);
							void setFmiValue(fmi2ValueReference id, bool value);
							void setFmiValue(fmi2ValueReference id, double value);
							void setFmiValue(fmi2ValueReference id, string value);
						
							int getFmiValueInteger(fmi2ValueReference id);
							bool getFmiValueBoolean(fmi2ValueReference id);
							double getFmiValueReal(fmi2ValueReference id);
							string getFmiValueString(fmi2ValueReference id);
							
						private:
							
							«adapClassName»* getRuleThis();
							
							/*in rules*/
							«inRulesFuncSig.map[x | x+";"].join("\n")»
							
							/*out rules*/
							«outRulesFuncSig.map[x | x+";"].join("\n")»
							
							«crtlRulesFuncSig.map[x | x+";"].join("\n")»
							
							«FOR fmu : fmus»
								shared_ptr<FmuComponent> «fmu.name»;
							«ENDFOR»
							
							«FOR sv : sVars»
								«Conversions.fmiTypeToCppType(sv.type)» «sv.name»;
								«IF sv.causality == SVCausality.input»
									bool isSet«sv.name»;
								«ENDIF»
							«ENDFOR»
							
							«FOR v : globalVariables.entrySet»
								«Conversions.fmiTypeToCppType(v.value.type)» «v.key»;
							«ENDFOR»
					};
				}
				
				#endif
		''';
	}

	/*
	 * Compiles the source file constructor, destructor and the initialize function
	 */
	def String compileDeAndConstructorAndInitialize(String adapClassName, ArrayList<InnerFMUData> fmus, String guid,
		String paramsCons, String inCons, String outCons, String crtlCons) {

		var ArrayList<String> initialisations = newArrayList();
		for (fmu : fmus) {
			initialisations.add('''
				auto path = make_shared<string>(*resourceLocation);
				path->append(string("«fmu.typeName».fmu"));
				auto «fmu.name»Fmu = make_shared<fmi2::Fmu>(*path);
				«fmu.name»Fmu->initialize();
				this->«fmu.name» = «fmu.name»Fmu->instantiate("«fmu.name»",fmi2CoSimulation, "«fmu.guid»", true, true, shared_from_this());
				
				if(this->«fmu.name»->component == NULL)
					this->lastErrorState = fmi2Fatal;
				this->instances->push_back(this->«fmu.name»);
			''');
		}
		return '''
				«adapClassName»::«adapClassName»(shared_ptr<std::string> fmiInstanceName,shared_ptr<string> resourceLocation, const fmi2CallbackFunctions* functions) : 
				SemanticAdaptation(fmiInstanceName, resourceLocation, createInputRules(),createOutputRules(), functions)
				{
				
				«paramsCons»
				«inCons»
				«outCons»
				«crtlCons»
				}
				
				void «adapClassName»::initialize()
				{
				«initialisations.join("\r\n")»
				«««				«FOR fmu : fmus»
«««				auto path = make_shared<string>(*resourceLocation);
«««				path->append(string("«fmu.value».fmu"));
«««				auto «fmu.key»Fmu = make_shared<fmi2::Fmu>(*path);
«««				«fmu.key»Fmu->initialize();
«««				this->«fmu.key» = «fmu.key»Fmu->instantiate("«fmu.key»",fmi2CoSimulation, "«guid»", true, true, shared_from_this());
«««				
«««				if(this->«fmu.key»->component == NULL)
«««					this->lastErrorState = fmi2Fatal;
«««				this->instances->push_back(this->«fmu.key»);
«««				«ENDFOR»
			}
			
			«adapClassName»::~«adapClassName»()
				{
				}
		''';
	}

	/*
	 * Compiles the source file function getRuleThis
	 */
	def String compileGetRuleThis(String adaptationName) {
		return '''
			«adaptationName»* «adaptationName»::getRuleThis()
			{
				return this;
			}
		'''
	}

	/*
	 * Compiles the source file functions getFmiValue<double, int, string, bool>
	 */
	def String compileGetFmiValueFunctions(String adaptationName, LinkedHashMap<String, SAScalarVariable> variables) {
		var ArrayList<String> cpp = newArrayList();
		var List<ScalarVariable> convertedSASVs = variables.values.map[CalcSVar()].toList;
		var convertedSASVsOrdered = convertedSASVs.filter[causality === SVCausality.output].groupBy[type];

		for (SVType type : SVType.values) {
			val functionSignature = '''«Conversions.fmiTypeToCppType(type)» «adaptationName»::getFmiValue«type.toString»(fmi2ValueReference id)''';
			val functionReturn = '''return «Conversions.fmiTypeToCppDefaultValue(type)»''';
			if (convertedSASVsOrdered.containsKey(type)) {
				cpp.add(
					'''
						«functionSignature»
						{
							switch (id)
							{
								«FOR svInner : convertedSASVsOrdered.get(type)»
									case «variables.get(svInner.name).defineName»:
									{
										return this->«svInner.name»;
									}
								«ENDFOR»
								default:
								{
									«functionReturn»;
								}
							}
							
						}
					'''
				);
			} else {
				cpp.add(
					'''
						«functionSignature»
						{
							«functionReturn»;
						}
					'''
				);
			}
		}

		return cpp.join("\n");
	}

	/*
	 * Compiles the source file functions setFmiValue<double, int, string, bool>*
	 */
	def String compileSetFmiValueFunctions(String adapClassName, LinkedHashMap<String, SAScalarVariable> variables) {
		var ArrayList<String> cpp = newArrayList();
		var List<ScalarVariable> convertedSASVs = variables.values.map[CalcSVar()].filter [
			causality === SVCausality.input
		].toList;
		var convertedSASVsOrdered = convertedSASVs.groupBy[type];

		for (SVType type : SVType.values) {
			cpp.add(
				'''
					void «adapClassName»::setFmiValue(fmi2ValueReference id, «Conversions.fmiTypeToCppType(type)» value)
					{
						«IF convertedSASVsOrdered.containsKey(type)»
							switch (id)	
								{
									«FOR svInner : convertedSASVsOrdered.get(type)»
										case «variables.get(svInner.name).defineName»:
										{
											this->«svInner.name» = value;
											this->isSet«svInner.name» = true;
											break;
										}
									«ENDFOR»
									default:
									{
									}
								}
						«ENDIF»
					}
				'''
			);

		}

		return cpp.join("\n");
	}

	/*
	 * Compiles the source file function executeInternalControlFlow.
	 * Calculates necessary information on function signatures necessary for generation of the header file.
	 */
	def InOutRulesBlockResult compileControlRuleBlock(Iterable<ControlRuleBlock> crtlRuleBlocks,
		String adaptationClassName, String adaptationName,
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String, SAScalarVariable> SASVs, LinkedHashMap<String, GlobalInOutVariable> params,
		LinkedHashMap<String, GlobalInOutVariable> inVars, LinkedHashMap<String, GlobalInOutVariable> outVars,
		LinkedHashMap<String, GlobalInOutVariable> crtlVars) {
		var cpp = "";
		val visitor = new ControlConditionSwitch(adaptationClassName, adaptationName, mSVars, SASVs, params, inVars,
			outVars, crtlVars);
		for (crtlRule : crtlRuleBlocks) {
			cpp += visitor.doSwitch(crtlRule).code;
		}

		return new InOutRulesBlockResult(cpp, visitor.functionSignatures);
	}

	def String SplitAtSpaceAndRemoveFirst(String content) {
		content.substring(content.indexOf(" ") + 1, content.length);
	}

	def String removeEmptyArgumentParenthesis(String content) {
		return content.substring(0, content.length - 2);
	}

	/*
	 * Calculates necessary information on global in/out variables
	 */
	def Pair<String, LinkedHashMap<String, GlobalInOutVariable>> compileRuleBlockVars(EList<Declaration> gVars,
		LinkedHashMap<String, GlobalInOutVariable> params) {

		val visitor = new RulesConditionSwitch("", "", "", null, null, params, null, null, null)
		return visitor.getGlobalVars(gVars);
	}

	/*
	 * Compiles the source file functions <in/out>_rule_<condition, body, flush>.
	 * Calculates necessary information on function signatures necessary for generation of the header file.
	 * Added the extra input and output functions
	 */
	def InOutRulesBlockResult compileInOutRuleBlocks(
		IORuleType ioType,
		Iterable<InOutRules> rulesBlocks,
		String adaptationClassName,
		String adaptationName,
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String, SAScalarVariable> SASVs,
		LinkedHashMap<String, GlobalInOutVariable> params,
		LinkedHashMap<String, GlobalInOutVariable> inVars,
		LinkedHashMap<String, GlobalInOutVariable> outVars,
		LinkedHashMap<String, GlobalInOutVariable> crtlVars,
		List<Port> portsWithSrcDep
	) {

		val visitor = if (ioType == IORuleType.Input)
				new InRulesConditionSwitch(adaptationClassName, adaptationName, mSVars, SASVs, params, inVars, outVars,
					crtlVars)
			else
				new OutRulesConditionSwitch(adaptationClassName, adaptationName, mSVars, SASVs, params, inVars, outVars,
					crtlVars);
		//
		val functionName = "create" + ioType + "Rules()";
		var String cpp = "";
		val ruleBlock = rulesBlocks.head;
		var List<String> allFunctionSignatures = newArrayList();

		if (ruleBlock !== null) {
			cpp += visitor.doSwitch(ruleBlock).code;
		}
		if (!visitor.functionSignatures.empty || !portsWithSrcDep.empty) {
			allFunctionSignatures.addAll(visitor.functionSignatures);
			var ArrayList<String> createRulesFunction = newArrayList();
			
			if (ruleBlock !== null) {
				// For-loop Handles the out rules defined in the sa file
				for (var int i = 0; i < (visitor.functionSignatures.length); i += 3) {
					createRulesFunction.add( 
					'''
						list->push_back(
							(Rule<«adaptationClassName»>){
								&«adaptationClassName»::«visitor.functionSignatures.get(i).SplitAtSpaceAndRemoveFirst.removeEmptyArgumentParenthesis»,
								&«adaptationClassName»::«visitor.functionSignatures.get(i+1).SplitAtSpaceAndRemoveFirst.removeEmptyArgumentParenthesis»,
								&«adaptationClassName»::«visitor.functionSignatures.get(i+2).SplitAtSpaceAndRemoveFirst.removeEmptyArgumentParenthesis»
							});
						
					''');
				}
			}
			
			var List<String> portsWithSrcDepFuncSig = newArrayList();
			var List<String> functionSignatures = newArrayList();
			for (var int i = 0; i < portsWithSrcDep.length; i++) {
				val currentPort = portsWithSrcDep.get(i);
				val newCount = visitor.functionSignatures.length + i + 1;
				val inOrOut = (if(ioType == IORuleType.Input) "in" else "out")
				val funcSigCon = visitor.createFunctionSignature('''condition''', "bool", newCount, functionSignatures)
				val funcSigBody = visitor.createFunctionSignature('''body''', "void", newCount, functionSignatures)
				val funcSigFlush = visitor.createFunctionSignature('''flush''', "void", newCount, functionSignatures)

				val type = mSVars.get(currentPort.sourcedependency.owner.name).get(
					currentPort.sourcedependency.port.name).mappedSv.type;
				val define = mSVars.get(currentPort.sourcedependency.owner.name).get(
					currentPort.sourcedependency.port.name).define;
				val getValueCpp = '''getValue«Conversions.fmiTypeToCppTypeCapitalized(type)»(«currentPort.sourcedependency.owner.name»,«define»)''';

				val ruleCpp = '''
				«funcSigCon»{
					return true;
				}
				«funcSigBody»{
					this->stored_«currentPort.sourcedependency.owner.name»_«currentPort.sourcedependency.port.name» = «getValueCpp»;
				}
				«funcSigFlush»{
					this->«currentPort.name» = this->stored_«currentPort.sourcedependency.owner.name»_«currentPort.sourcedependency.port.name»;
				}
				'''
				cpp += ruleCpp;
				portsWithSrcDepFuncSig.add(funcSigCon);
				portsWithSrcDepFuncSig.add(funcSigBody);
				portsWithSrcDepFuncSig.add(funcSigFlush);

			}
			allFunctionSignatures.addAll(functionSignatures);

			for (var int i = 0; i < (portsWithSrcDepFuncSig.length); i += 3) {
				createRulesFunction.add( 
					'''
					list->push_back(
						(Rule<«adaptationClassName»>){
							&«portsWithSrcDepFuncSig.get(i).SplitAtSpaceAndRemoveFirst.removeEmptyArgumentParenthesis»,
							&«portsWithSrcDepFuncSig.get(i+1).SplitAtSpaceAndRemoveFirst.removeEmptyArgumentParenthesis»,
							&«portsWithSrcDepFuncSig.get(i+2).SplitAtSpaceAndRemoveFirst.removeEmptyArgumentParenthesis»
						});
					
				''');
			}

			// Handles the createOutputRules and createInputRules
			val functionPrefix = '''shared_ptr<list<Rule<«adaptationClassName»>>>''';
			allFunctionSignatures.add(functionPrefix + " " + functionName)
			cpp += '''
				«functionPrefix» «adaptationClassName»::«functionName»
				{
					auto list = make_shared<std::list<Rule<«adaptationClassName»>>>();
					
					«createRulesFunction.join("\n")»
					
					return list;
					
				}
				
			'''
		}

		return new InOutRulesBlockResult(cpp, allFunctionSignatures);
	}

	/*
	 * Calculates the semantic adaptation scalar variables via input ports and output ports.
	 * Note: These a not fully populated yet as the in rules and out rules must be compiled first. 
	 */
	def LinkedHashMap<String, SAScalarVariable> calcSASVsFromInportsOutports(String definePrefix, EList<Port> inports,
		EList<Port> outports, LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVs) {
		var LinkedHashMap<String, SAScalarVariable> saSVs = newLinkedHashMap();

		var int valueReference = 0;
		for (inport : inports) {
			var saSV = new SAScalarVariable();
			saSV.SetPartOfMD(true);
			saSV.valueReference = valueReference++;
			saSV.name = inport.name;
			saSV.defineName = (definePrefix + inport.name).toUpperCase
			saSV.causality = SVCausality.input;
			saSVs.put(saSV.name, saSV);
		}

		for (outport : outports) {
			var saSV = new SAScalarVariable();
			if (outport.sourcedependency !== null) {
				saSV.type = mSVs.get(outport.sourcedependency.owner.name).get(outport.sourcedependency.port.name).
					mappedSv.type;
				saSV.variability = mSVs.get(outport.sourcedependency.owner.name).get(
					outport.sourcedependency.port.name).mappedSv.variability;

			}
			saSV.SetPartOfMD(true);
			saSV.valueReference = valueReference++;
			saSV.defineName = (definePrefix + outport.name).toUpperCase
			saSV.name = outport.name;
			saSV.causality = SVCausality.output;
			saSVs.put(saSV.name, saSV);
		}

		return saSVs;
	}

	def List<File> getResourcePaths() {
		return resourcePaths;
	}
}
