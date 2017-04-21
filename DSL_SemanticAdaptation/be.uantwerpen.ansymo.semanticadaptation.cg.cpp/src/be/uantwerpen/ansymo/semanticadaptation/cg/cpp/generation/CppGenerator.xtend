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
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.InputOutputType
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

			// This is the external name used in the model description file for the semantic adaptation FMU.
			val adapExternalName = adap.type.name;

			// List of FMUs with a pairing between its name and its type.name.
			var ArrayList<Pair<String, String>> fmus = newArrayList();

			// TODO: Currently only 1 inner fmu is supported
			val innerFmus = adap.inner.eAllContents.toList.filter(InnerFMU);
			if (innerFmus.size > 1) {
				throw new IncorrectAmountOfElementsException("Only one InnerFmu is supported.")
			}
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
			// TODO: Add support for multiple inner fmus
			var ModelDescription md;
			for (fmu : adap.inner.eAllContents.toList.filter(InnerFMU)) {
				val fmuFile = new File(fmu.path.replace('\"', ''));
				this.resourcePaths.add(fmuFile);
				md = new ModelDescription(fmu.name, fmu.type.name, fmuFile);
				fmus.add(fmu.name -> fmu.type.name);
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

			// Compile Params
			var LinkedHashMap<String, GlobalInOutVariable> params = newLinkedHashMap;
			val String paramsConstructorSource = compileParams(params, adap.params);

			/*
			 * This map contains all the ScalarVariables for the semantic adaptation. 
			 * The are not populated yet, but they will be during the compilation of the in and out rule blocks. 
			 */
			var LinkedHashMap<String, SAScalarVariable> SASVs = calcSASVsFromInportsOutports(adapInteralRefName,
				adap.inports, adap.outports)

			// C++ defines for accessing semantic adaptation scalar variables 
			val String SADefines = calcSADefines(SASVs.values);

			// Compile the transparent in mappings

			// Compile the in rules
			val inRuleResult = compileInOutRuleBlocks(InputOutputType.Input, adaptation.eAllContents.toIterable.filter(
				InRulesBlock).map[x|x as InOutRules], adapClassName, adapInteralRefName, mappedScalarVariables, SASVs,
				params);

			// Compile the out rules
			val outRuleResult = compileInOutRuleBlocks(InputOutputType.Output, adaptation.eAllContents.toIterable.
				filter(OutRulesBlock).map[x|x as InOutRules], adapClassName, adapInteralRefName, mappedScalarVariables,
				SASVs, params);

			// Compile the Control Rules
			val crtlRuleResult = compileControlRuleBlock(adaptation.eAllContents.toIterable.filter(ControlRuleBlock),
				adapClassName, adapInteralRefName, SASVs);

			/*
			 * Compile the constructor, destructor and initialize functions
			 */
			val String deAndConstructorAndInitializeSource = compileDeAndConstructorAndInitialize(
				adapClassName,
				fmus.head.key,
				fmus.head.value,
				md.guid,
				paramsConstructorSource,
				inRuleResult.constructorInitialization,
				outRuleResult.constructorInitialization
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
			allGVars.putAll(outRuleResult.gVars);
			allGVars.putAll(inRuleResult.gVars);

			// Compile the header file
			val headerFile = compileHeader(
				adapClassName,
				fmusDefines,
				SADefines,
				inRuleResult.functionSignatures,
				outRuleResult.functionSignatures,
				crtlRuleResult.functionSignatures,
				allGVars,
				fmus,
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
		LinkedHashMap<String, GlobalInOutVariable> globalVariables, ArrayList<Pair<String, String>> fmus,
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
								shared_ptr<FmuComponent> «fmu.key»;
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
	def String compileDeAndConstructorAndInitialize(String adapClassName, String fmuName, String fmuTypeName,
		String guid, String paramsCons, String inCons, String outCons) {
		return '''
			«adapClassName»::«adapClassName»(shared_ptr<std::string> fmiInstanceName,shared_ptr<string> resourceLocation, const fmi2CallbackFunctions* functions) : 
				SemanticAdaptation(fmiInstanceName, resourceLocation, createInputRules(),createOutputRules(), functions)
			{
				
				«paramsCons»
				«inCons»
				«outCons»
			}
			
			void «adapClassName»::initialize()
			{				
				auto path = make_shared<string>(*resourceLocation);
				path->append(string("«fmuTypeName».fmu"));
				auto «fmuName»Fmu = make_shared<fmi2::Fmu>(*path);
				«fmuName»Fmu->initialize();
				this->«fmuName» = «fmuName»Fmu->instantiate("«fmuName»",fmi2CoSimulation, "«guid»", true, true, shared_from_this());
				
				if(this->«fmuName»->component == NULL)
					this->lastErrorState = fmi2Fatal;
				this->instances->push_back(this->«fmuName»);
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
	def RulesBlockResult compileControlRuleBlock(Iterable<ControlRuleBlock> crtlRuleBlocks, String adaptationClassName,
		String adaptationName, LinkedHashMap<String, SAScalarVariable> SASVs) {
		var cpp = "";
		val visitor = new ControlConditionSwitch(adaptationClassName, adaptationName, SASVs);
		for (crtlRule : crtlRuleBlocks) {
			cpp += visitor.doSwitch(crtlRule).code;
		}

		return new RulesBlockResult(cpp, visitor.functionSignatures);
	}

	def String SplitAtSpaceAndRemoveFirst(String content) {
		content.substring(content.indexOf(" ") + 1, content.length);
	}

	def String removeEmptyArgumentParenthesis(String content) {
		return content.substring(0, content.length - 2);
	}

	/*
	 * Compiles the source file functions <in/out>_rule_<condition, body, flush>.
	 * Calculates necessary information on global in/out variables necessary for generation of the header file.
	 * Calculates necessary information on function signatures necessary for generation of the header file.
	 */
	def InOutRulesBlockResult compileInOutRuleBlocks(InputOutputType ioType, Iterable<InOutRules> rulesBlocks,
		String adaptationClassName, String adaptationName,
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
		LinkedHashMap<String, SAScalarVariable> SASVs, LinkedHashMap<String, GlobalInOutVariable> params) {

		val visitor = if (ioType == InputOutputType.Input)
				new InRulesConditionSwitch(adaptationClassName, adaptationName, mSVars, SASVs, params)
			else
				new OutRulesConditionSwitch(adaptationClassName, adaptationName, mSVars, SASVs, params);

		val functionName = "create" + ioType + "Rules()";
		var String cpp = "";
		val ruleBlock = rulesBlocks.head;
		if (ruleBlock !== null) {
			cpp += visitor.doSwitch(ruleBlock).code;
			if (!visitor.functionSignatures.empty) {
				var ArrayList<String> createRulesFunction = newArrayList();
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
				val functionPrefix = '''shared_ptr<list<Rule<«adaptationClassName»>>>''';
				visitor.functionSignatures.add(functionPrefix + " " + functionName)
				cpp += '''
					«functionPrefix» «adaptationClassName»::«functionName»
					{
						auto list = make_shared<std::list<Rule<«adaptationClassName»>>>();
						
						«createRulesFunction.join("\n")»
						
						return list;
						
					}
					
				'''
			}
		}
		return new InOutRulesBlockResult(cpp, visitor.functionSignatures, visitor.getGlobalVars,
			visitor.constructorInitialization);
	}

	/*
	 * Calculates the semantic adaptation scalar variables via input ports and output ports.
	 * Note: These a not fully populated yet as the in rules and out rules must be compiled first. 
	 */
	def LinkedHashMap<String, SAScalarVariable> calcSASVsFromInportsOutports(String definePrefix, EList<Port> inports,
		EList<Port> outports) {
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
