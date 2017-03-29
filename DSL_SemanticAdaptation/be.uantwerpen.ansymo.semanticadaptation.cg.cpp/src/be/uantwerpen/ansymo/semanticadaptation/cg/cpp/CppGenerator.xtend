package be.uantwerpen.ansymo.semanticadaptation.cg.cpp

import be.uantwerpen.ansymo.semanticadaptation.generator.SemanticAdaptationGenerator
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Adaptation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ControlRuleBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InOutRules
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InRulesBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InnerFMU
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.OutRulesBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import java.io.File
import java.util.ArrayList
import java.util.LinkedHashMap
import org.eclipse.emf.ecore.resource.Resource
import org.eclipse.xtext.generator.IFileSystemAccess2
import org.eclipse.xtext.generator.IGeneratorContext
import java.util.Collection
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import org.eclipse.emf.common.util.EList

class CppGenerator extends SemanticAdaptationGenerator {

	var ModelDescriptionCreator mdCreator = new ModelDescriptionCreator()

	private var IFileSystemAccess2 fsa;

	override void doGenerate(Resource resource, IFileSystemAccess2 fsa, IGeneratorContext context) {
		this.fsa = fsa;
		for (SemanticAdaptation type : resource.allContents.toIterable.filter(SemanticAdaptation)) {
			type.compile;

		}
	}

// TODO: Verify adaptation.name is not a C++ keyword
// TODO: Add initial value to inputs in the model description file
	def void compile(SemanticAdaptation adaptation) {
		for (Adaptation type : adaptation.elements.filter(Adaptation)) {
			val adapInteralRefName = type.name;
			val adapClassName = type.name.toFirstUpper;
			val adapExternalName = type.type.name;
			var LinkedHashMap<String, Pair<String, Integer>> svDefs = newLinkedHashMap();
			var ArrayList<Pair<String, String>> fmus = newArrayList();
			var LinkedHashMap<String, ScalarVariable> sVars = newLinkedHashMap();
			var String genSource = "";
			var ModelDescription md;
			var LinkedHashMap<String, Collection<ScalarVariable>> scalarVariables = newLinkedHashMap();
			var LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mappedScalarVariables = newLinkedHashMap();			

			// Load Model Description file
			val innerFmus = type.inner.eAllContents.toList.filter(InnerFMU);
			if (innerFmus.size > 1) {
				throw new IncorrectAmountOfElementsException("Only one InnerFmu is supported.")
			}
			if (innerFmus.isEmpty) {
				throw new IncorrectAmountOfElementsException("The adaptation does not contain any InnerFMUs.")
			}

			var LinkedHashMap<String,SAScalarVariable> SASVs = calcSASVsFromInportsOutports(adapInteralRefName, type.inports, type.outports)

			for (fmu : type.inner.eAllContents.toList.filter(InnerFMU)) {
				// TODO: Merge this with ModelDescriptionCreator
				md = new ModelDescription(fmu.name, fmu.type.name, new File(fmu.path.replace('\"', '')));
				fmus.add(fmu.name -> fmu.type.name);
				svDefs.putAll(md.svDef);
				sVars.putAll(md.sv);
				scalarVariables.put(fmu.name, md.sv.values);

				mdCreator.name = adapExternalName;
				mdCreator.CalcContent(md);
				fsa.generateFile("modelDescription.xml", mdCreator.modelDescription);
			}

			/*
			 * We might have conflicting scalar variables, 
			 * and therefore the scalar variables cannot be directly mapped to the mdCreator.
			 * mappedScalarVariables is therefore: HashMap (fmuName -> HashMap(SVName->mappedSV))
			 */
			for (mdSv : scalarVariables.entrySet) {
				val LinkedHashMap<String, MappedScalarVariable> msv = newLinkedHashMap();
				for (sv : mdSv.value) {
					var mappedSv = new MappedScalarVariable(sv);
					mappedSv.define = (mappedSv.mappedSv.owner + mappedSv.mappedSv.name).toUpperCase;
					msv.put(mappedSv.mappedSv.name, mappedSv);
				}
				mappedScalarVariables.put(mdSv.key, msv);
			}
			
			// Compile the in rules
			val inRuleResult = compileInOutRuleBlocks(InputOutputType.Input, adaptation.eAllContents.toIterable.filter(
				InRulesBlock).map[x|x as InOutRules], adapClassName, adapInteralRefName, mappedScalarVariables, SASVs);
			genSource += inRuleResult.generatedCpp;

			// Compile the out rules
			val outRuleResult = compileInOutRuleBlocks(InputOutputType.Output, adaptation.eAllContents.toIterable.
				filter(OutRulesBlock).map[x|x as InOutRules], adapClassName, adapInteralRefName, mappedScalarVariables, SASVs);
			genSource += outRuleResult.generatedCpp;

			/*
			 * We now have the explicit input and output values determined in the SA. 
			 * This along with the model descriptions should be enough to create a model description for the SA FMU. 
			 */
			// Generate the Control Rules
			val crtlRuleResult = compileControlRuleBlock(adaptation.eAllContents.toIterable.filter(ControlRuleBlock),
				adapClassName, adapInteralRefName, svDefs, SASVs);
			genSource += crtlRuleResult.generatedCpp;

			// Compile the source file includes, namespace and constructor 
			val String include = '''#include "«adapClassName.toFirstLower».h"''';
			val String constructor = compileDeAndConstructor(adapClassName, outRuleResult, inRuleResult, sVars,
				fmus.head.key, fmus.head.value, md.guid);
			val String getRuleThis = compileGetRuleThis(adapClassName);

			// Compile the get functions
			val String getFuncs = compileGetFmuValue(adapClassName, sVars, svDefs);

			// Compile the set functions
			val String setFuncs = compileSetFmuValue(adapClassName, sVars, svDefs);

			// Generate the source file for the SA
			val source = compileSource(
				include,
				constructor,
				getRuleThis,
				getFuncs,
				setFuncs,
				inRuleResult.generatedCpp,
				crtlRuleResult.generatedCpp,
				outRuleResult.generatedCpp
			);

			fsa.generateFile(adapClassName.toFirstLower + ".cpp", source);

			// Compile defines for the scalar variables
			var genDef = calcDefines(svDefs).join("\n");
			// Compile the class definition file for the SA
			val String header = compileHeader(adapClassName, inRuleResult, outRuleResult, crtlRuleResult, fmus, sVars,
				genDef);

			// Generate the header file for the SA
			fsa.generateFile(adapClassName.toLowerCase + ".h", header);
		}
	}

	// Compiles the final source file
	def String compileSource(String include, String constructor, String getRuleThis, String getFunctions,
		String setFunctions, String inFunctions, String controlFunction, String outFunctions) {
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
	def String compileHeader(String adaptationName, InOutRulesBlockResult inRulesResult,
		InOutRulesBlockResult outRulesResult, RulesBlockResult crtlRulesResult, ArrayList<Pair<String, String>> fmus,
		LinkedHashMap<String, ScalarVariable> sVars, String defines) {
		return '''
			#include "SemanticAdaptation.h"
			#include <memory>
			#include "Fmu.h"
			
			using namespace std;
			using namespace fmi2;
			
			namespace adaptation
			{
			
				class «adaptationName» : public SemanticAdaptation<«adaptationName»>{
					public:
						«adaptationName»(shared_ptr<string> resourceLocation);
						virtual ~«adaptationName»();
						
						void setFmiValue(fmi2ValueReference id, int value);
						void setFmiValue(fmi2ValueReference id, bool value);
						void setFmiValue(fmi2ValueReference id, double value);
					
						int getFmiValueInteger(fmi2ValueReference id);
						bool getFmiValueBoolean(fmi2ValueReference id);
						double getFmiValueDouble(fmi2ValueReference id);
					private:
						
						«adaptationName»* getRuleThis();
						
						/*in rules*/
						«inRulesResult.functionSignatures.join("\n")»
						
						/*out rules*/
						«outRulesResult.functionSignatures.join("\n")»
						
						«crtlRulesResult.functionSignatures.join("\n")»
						
						«FOR fmu : fmus»
							shared_ptr<FmuComponent> «fmu.key»;
						«ENDFOR»
						
						«FOR sv : sVars.entrySet»
							«Conversions.fmiTypeToCppType(sv.value.type)» «sv.value.name»;
							«IF sv.value.causality == SVCausality.input»
								bool isSet«sv.value.name»;
							«ENDIF»
						«ENDFOR»
						
						«FOR v : outRulesResult.globalVars.entrySet»
							«Conversions.fmiTypeToCppType(v.value.key)» «v.key»;
						«ENDFOR»
						
						«FOR v : inRulesResult.globalVars.entrySet»
							«Conversions.fmiTypeToCppType(v.value.key)» «v.key»;
						«ENDFOR»
				}
			}
		''';
	}

	/*
	 * Compiles the source file constructor and destructor
	 */
	def String compileDeAndConstructor(String adaptationName, InOutRulesBlockResult outRuleResult,
		InOutRulesBlockResult inRuleResult, LinkedHashMap<String, ScalarVariable> sVars, String fmuName,
		String fmuTypeName, String guid) {
		return '''
			«adaptationName»::«adaptationName»(shared_ptr<string> resourceLocation) : SemanticAdaptation(createInputRules(),createOutputRules())
			{
				«FOR v : outRuleResult.globalVars.entrySet»
					«(v.key)» = «v.value.value»;
				«ENDFOR»
				
				«FOR v : inRuleResult.globalVars.entrySet»
					this->«(v.key)» = «v.value.value»;
				«ENDFOR»
				
				«FOR v : sVars.entrySet»
					«IF v.value.start !== null»
						this->«(v.key)» = «v.value.start»;
					«ENDIF»
				«ENDFOR»
				
				const char* path = Fmu::combinePath(resourceLocation, make_shared<string>("«fmuTypeName».fmu"))->c_str();
				auto «fmuName»Fmu = make_shared<fmi2::Fmu>(path);
				«fmuName»Fmu->initialize();
				this->«fmuName» = «fmuName»Fmu->instantiate("«fmuTypeName»",fmi2CoSimulation, "«guid»", true, true, make_shared<Callback>()); 
			}
			«adaptationName»::~«adaptationName»()
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
	def String compileGetFmuValue(String adaptationName, LinkedHashMap<String, ScalarVariable> sVars,
		LinkedHashMap<String, Pair<String, Integer>> sVarDefs) {
		var ArrayList<String> cpp = newArrayList();
		var sVarsOrdered = sVars.entrySet.filter[value.causality === SVCausality.output].groupBy[value.type];

		for (SVType type : SVType.values) {
			val functionSignature = '''«Conversions.fmiTypeToCppType(type)»  «adaptationName»::getFmiValue«type.toString»(fmi2ValueReference id)''';
			val functionReturn = '''return «Conversions.fmiTypeToCppDefaultValue(type)»''';
			if (sVarsOrdered.containsKey(type)) {
				cpp.add(
					'''
						«functionSignature»
						{
							switch (id)
							{
								«FOR svInner : sVarsOrdered.get(type)»
									case «sVarDefs.get(svInner.value.owner + svInner.value.name).key»:
									{
										return this->«svInner.key»;
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
	def String compileSetFmuValue(String adaptationName, LinkedHashMap<String, ScalarVariable> sVars,
		LinkedHashMap<String, Pair<String, Integer>> sVarDefs) {
		var ArrayList<String> cpp = newArrayList();
		var sVarsOrdered = sVars.entrySet.filter[value.causality === SVCausality.input].groupBy[value.type];

		for (SVType type : SVType.values) {

			cpp.add(
				'''
					void «adaptationName»::setFmiValue(fmi2ValueReference id, «Conversions.fmiTypeToCppType(type)» value)
					{
						«IF sVarsOrdered.containsKey(type)»
							switch (id)	
								{
									«FOR svInner : sVarsOrdered.get(type)»
										case «sVarDefs.get(svInner.value.owner + svInner.value.name).key»:
										{
											this->«svInner.key» = value;
											this->isSet«svInner.key» = true;
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
		String adaptationName, LinkedHashMap<String, Pair<String, Integer>> svDefs, LinkedHashMap<String, SAScalarVariable> SASVs) {
		var cpp = "";
		val visitor = new ControlConditionSwitch(adaptationClassName, adaptationName, svDefs, SASVs);
		for (crtlRule : crtlRuleBlocks) {
			cpp += visitor.doSwitch(crtlRule);
		}

		return new RulesBlockResult(cpp, visitor.functionSignatures);
	}

	def String SplitAtSpaceAndRemoveFirst(String content) {
		content.substring(content.indexOf(" ") + 1, content.length);
	}

	/*
	 * Compiles the source file functions <in/out>_rule_<condition, body, flush>.
	 * Calculates necessary information on global in/out variables necessary for generation of the header file.
	 * Calculates necessary information on function signatures necessary for generation of the header file.
	 */
	def InOutRulesBlockResult compileInOutRuleBlocks(InputOutputType ioType, Iterable<InOutRules> rulesBlocks,
		String adaptationClassName, String adaptationName,
		LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars, LinkedHashMap<String,SAScalarVariable> SASVs) {
			
		val visitor = if (ioType == InputOutputType.Input)
				new InRulesConditionSwitch(adaptationClassName, adaptationName, mSVars, SASVs)
			else
				new OutRulesConditionSwitch(adaptationClassName, adaptationName, mSVars, SASVs);
				
		val functionName = "create" + ioType + "Rules()";
		var String cpp = "";
		val ruleBlock = rulesBlocks.head;
		if (ruleBlock !== null) {
			cpp += visitor.doSwitch(ruleBlock);
			if (!visitor.functionSignatures.empty) {
				var ArrayList<String> createRulesFunction = newArrayList();
				for (var int i = 0; i < (visitor.functionSignatures.length); i += 3) {
					createRulesFunction.add( 
					'''
						list->push_back(
							(Rule<«adaptationClassName»>){
								&«adaptationClassName»::«visitor.functionSignatures.get(i).SplitAtSpaceAndRemoveFirst»,
								&«adaptationClassName»::«visitor.functionSignatures.get(i+1).SplitAtSpaceAndRemoveFirst»
								&«adaptationClassName»::«visitor.functionSignatures.get(i+2).SplitAtSpaceAndRemoveFirst»
							});
						
					''');
				}
				val functionPrefix = '''shared_ptr<list<Rule<«adaptationClassName»>>>''';
				visitor.functionSignatures.add(functionPrefix + " " + functionName + ";")
				cpp += '''
					«functionPrefix» «adaptationClassName»::«functionName»
					{
						auto list = make_shared<list<Rule<«adaptationClassName»>>>()
						
						«createRulesFunction.join("\n")»
						
						return list;
						
					}
					
				'''
			}
		}
		return new InOutRulesBlockResult(cpp, visitor.functionSignatures, visitor.globalVars);
	}

	/*
	 * Calculates defines for accessing scalar variables via value references. 
	 */
	def ArrayList<String> calcDefines(LinkedHashMap<String, Pair<String, Integer>> svDefs) {
		// Create Defines for the scalar values
		var defines = newArrayList();
		for (scalar : svDefs.entrySet) {
			val definition = scalar.value;
			defines.add("#define " + definition.key + " " + definition.value);
		}
		return defines;
	}

	def LinkedHashMap<String, SAScalarVariable> calcSASVsFromInportsOutports(String definePrefix, EList<Port> inports, EList<Port> outports) {
		var LinkedHashMap<String, SAScalarVariable> saSVs = newLinkedHashMap();
		
		var int valueReference = 0;
		for (inport : inports) {
			var saSV = new SAScalarVariable();
			saSV.valueReference = valueReference++;
			saSV.name = inport.name;
			saSV.defineName = (definePrefix + inport.name).toUpperCase
			saSV.causality = SVCausality.input;
			saSVs.put(saSV.name, saSV);
		}

		for (outport : outports) {
			var saSV = new SAScalarVariable();
			saSV.valueReference = valueReference++;
			saSV.defineName = (definePrefix + outport.name).toUpperCase
			saSV.name = outport.name;
			saSV.causality = SVCausality.output;
			saSVs.put(saSV.name, saSV);
		}
		
		return saSVs;
	}
}
