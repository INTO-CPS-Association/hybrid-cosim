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

class CppGenerator extends SemanticAdaptationGenerator {

	var ModelDescriptionCreator mdCreator = new ModelDescriptionCreator()
	var SwitchTest = new Visitor();

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

			var LinkedHashMap<String, Pair<String, Integer>> svDefs = newLinkedHashMap();
			var ArrayList<Pair<String, String>> fmus = newArrayList();
			var LinkedHashMap<String, ScalarVariable> sVars = newLinkedHashMap();
			var String genSource = "";
			var ModelDescription md;
			// Load Model Description file
			for (fmu : type.inner.eAllContents.toIterable.filter(InnerFMU)) {
				// TODO: Merge this with ModelDescriptionCreator
				md = new ModelDescription(fmu.name, fmu.type.name, new File(fmu.path.replace('\"', '')));
				fmus.add(fmu.name -> fmu.type.name);
				svDefs.putAll(md.svDef);
				sVars.putAll(md.sv);

				mdCreator.name = type.name;
				mdCreator.CalcContent(md);
				fsa.generateFile("modelDescription.xml", mdCreator.modelDescription);
			}

			// Compile the in rules
			val inRuleResult = compileInRuleBlock(adaptation.eAllContents.toIterable.filter(InRulesBlock), svDefs,
				type.name);
			genSource += inRuleResult.generatedCpp;

			// Compile the out rules
			val outRuleResult = compileOutRuleBlock(adaptation.eAllContents.toIterable.filter(OutRulesBlock), svDefs,
				type.name);
			genSource += outRuleResult.generatedCpp;

			// Generate the Control Rules
			val crtlRuleResult = compileControlRuleBlock(adaptation.eAllContents.toIterable.filter(ControlRuleBlock),
				type.name, svDefs);
			genSource += crtlRuleResult.generatedCpp;

			// Compile the includes and constructor 
			val String include = '''#include "«type.name».h"''';
			val String constructor = compileConstructor(type.name, outRuleResult, inRuleResult, sVars, fmus.head.key, fmus.head.value,
				md.guid);
			val String getRuleThis = compileGetRuleThis(type.name);
			genSource = include + "\n\n" + constructor + "\n\n" + getRuleThis + "\n\n" + genSource;

			// Compile the get functions
			val String getFuncs = compileGetFmuValue(type.name, sVars, svDefs);
			genSource += "\n" + getFuncs;

			// Compile the set functions
			val String setFuncs = compileSetFmuValue(type.name, sVars, svDefs);
			genSource += "\n" + setFuncs;

			// Generate the source file for the SA
			fsa.generateFile(type.name + ".cpp", genSource);

			// Compile defines for the scalar variables
			var genDef = calcDefines(svDefs).join("\n");
			// Compile the class definition file for the SA
			val String header = compileHeader(type.name, inRuleResult, outRuleResult, crtlRuleResult, fmus, sVars);

			// Generate the header file for the SA
			fsa.generateFile(type.name + ".h", genDef + "\n\n" + header);
		}
	}

	def String compileHeader(String name, InOutRulesBlockResult inRulesResult, InOutRulesBlockResult outRulesResult,
		RulesBlockResult crtlRulesResult, ArrayList<Pair<String, String>> fmus,
		LinkedHashMap<String, ScalarVariable> sVars) {
			return '''
				#include "SemanticAdaptation.h"
				#include <memory>
				#include "Fmu.h"
				
				using namespace std;
				using namespace fmi2
				
				class «name» : public SemanticAdaptation<«name»>{
					public:
						«name»();
						virtual ~«name»();
						
						void setFmiValue(fmi2ValueReference id, int value);
						void setFmiValue(fmi2ValueReference id, bool value);
						void setFmiValue(fmi2ValueReference id, double value);
					
						int getFmiValueInteger(fmi2ValueReference id);
						bool getFmiValueBoolean(fmi2ValueReference id);
						double getFmiValueDouble(fmi2ValueReference id);
					private:
						
						«name»* getRuleThis();
						
						/*in rules*/
						«inRulesResult.functionSignatures.join("\n")»
						
						/*out rules*/
						«outRulesResult.functionSignatures.join("\n")»
						
						«crtlRulesResult.functionSignatures.join("\n")»
						
						«FOR fmu : fmus»
							shared_ptr<Fmu> «fmu.key»;
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
			''';
		}

		def compileConstructor(String name, InOutRulesBlockResult outRuleResult, InOutRulesBlockResult inRuleResult,
			LinkedHashMap<String, ScalarVariable> sVars, String fmuName, String fmuTypeName, String guid) {
			return '''
				«name»::«name»(shared_ptr<std::string> resourceLocation) : SemanticAdaptation(createInputRules(),createOutputRules())
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
			''';
		}

		def compileGetRuleThis(String name) {
			return '''
				«name»* «name»::getRuleThis()
				{
					return this;
				}
			'''
		}

		def compileGetFmuValueCppFuncSig(String adaptationName, SVType type) {
			return '''«Conversions.fmiTypeToCppType(type)»  «adaptationName»::getFmiValue«Conversions.fmiTypeToCppTypeName(type)»(fmi2ValueReference id)''';
		}

		def compileGetFmuValueCppFuncReturn(SVType type) {
			return '''return «Conversions.fmiTypeToCppDefaultValue(type)»''';
		}

		def compileGetFmuValue(String adaptationName, LinkedHashMap<String, ScalarVariable> sVars,
			LinkedHashMap<String, Pair<String, Integer>> sVarDefs) {
			var ArrayList<String> cpp = newArrayList();
			var sVarsOrdered = sVars.entrySet.filter[value.causality === SVCausality.output].groupBy[value.type];

			for (SVType type : SVType.values) {
				if (sVarsOrdered.containsKey(type)) {
					cpp.add(
						'''
							«compileGetFmuValueCppFuncSig(adaptationName,type)»
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
										«compileGetFmuValueCppFuncReturn(type)»;
									}
								}
								
							}
						'''
					);
				} else {
					cpp.add(
						'''
							«compileGetFmuValueCppFuncSig(adaptationName,type)»
							{
								«compileGetFmuValueCppFuncReturn(type)»;
							}
						'''
					);
				}
			}

			return cpp.join("\n");
		}

		def compileSetFmuValueCppFuncSig(String adaptationName, SVType type) {
			return '''«Conversions.fmiTypeToCppType(type)»  «adaptationName»::getFmiValue«Conversions.fmiTypeToCppTypeName(type)»(fmi2ValueReference id)''';
		}

		def compileSetFmuValue(String adaptationName, LinkedHashMap<String, ScalarVariable> sVars,
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

		def RulesBlockResult compileControlRuleBlock(Iterable<ControlRuleBlock> crtlRuleBlocks, String name,
			LinkedHashMap<String, Pair<String, Integer>> svDefs) {
			var cpp = "";
			val visitor = new ControlConditionSwitch(name, svDefs);
			for (crtlRule : crtlRuleBlocks) {
				cpp += visitor.doSwitch(crtlRule);
			}

			return new RulesBlockResult(cpp, visitor.functionSignatures);
		}

		def InOutRulesBlockResult compileOutRuleBlock(Iterable<OutRulesBlock> rulesBlocks,
			LinkedHashMap<String, Pair<String, Integer>> svDefs, String name) {
			return compileInOutRuleBlocks(new OutRulesConditionSwitch(name, svDefs), rulesBlocks.map[x|x as InOutRules],
				svDefs, name, "createOutputRules");
		}

		def InOutRulesBlockResult compileInRuleBlock(Iterable<InRulesBlock> rulesBlocks,
			LinkedHashMap<String, Pair<String, Integer>> svDefs, String name) {
			return compileInOutRuleBlocks(new InRulesConditionSwitch(name, svDefs), rulesBlocks.map[x|x as InOutRules],
				svDefs, name, "createInputRules");
		}

		def InOutRulesBlockResult compileInOutRuleBlocks(InOutRulesConditionSwitch visitor,
			Iterable<InOutRules> rulesBlocks, LinkedHashMap<String, Pair<String, Integer>> svDefs, String name,
			String functionName) {
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
									(Rule<«name»>){
										&«name»::«visitor.functionSignatures.get(i)»,
										&«name»::«visitor.functionSignatures.get(i+1)»
										&«name»::«visitor.functionSignatures.get(i+2)»
									});
								
							''');
						}
						val functionPrefix = '''shared_ptr<list<Rule<«name»>>>''';
						visitor.functionSignatures.add(functionPrefix + " " + functionName + ";")
						cpp += '''
							«functionPrefix» «name»::«functionName»()
							{
								auto list = make_shared<list<Rule<«name»>>>()
								
								«createRulesFunction.join("\n")»
								
								return list;
								
							}
							
						'''
					}
				}
				return new InOutRulesBlockResult(cpp, visitor.functionSignatures, visitor.globalVars);
			}

			def calcDefines(LinkedHashMap<String, Pair<String, Integer>> svDefs) {
				// Create Defines for the scalar values
				var defines = newArrayList();
				for (scalar : svDefs.entrySet) {
					val definition = scalar.value;
					defines.add("#define " + definition.key + " " + definition.value);
				}
				return defines;
			}
		}
		