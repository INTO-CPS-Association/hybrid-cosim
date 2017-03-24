package be.uantwerpen.ansymo.semanticadaptation.cg.cpp

import be.uantwerpen.ansymo.semanticadaptation.generator.SemanticAdaptationGenerator
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Adaptation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DataRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InnerFMU
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.OutRulesBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import java.io.File
import java.util.LinkedHashMap
import org.eclipse.emf.ecore.resource.Resource
import org.eclipse.xtext.generator.IFileSystemAccess2
import org.eclipse.xtext.generator.IGeneratorContext
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InRulesBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ControlRuleBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ControlRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InOutRules
import java.util.ArrayList

class CppGenerator extends SemanticAdaptationGenerator {

	var ModelDescriptionCreator mdCreator = new ModelDescriptionCreator()
	var SwitchTest = new Visitor();

	private var IFileSystemAccess2 fsa;

	override void doGenerate(Resource resource, IFileSystemAccess2 fsa, IGeneratorContext context) {
		this.fsa = fsa;
		for (type : resource.allContents.toIterable.filter(SemanticAdaptation)) {
			type.compile;
			mdCreator.name = type.name;
			fsa.generateFile("modelDescription.xml", mdCreator.modelDescription);
		}
	}

// TODO: Verify adaptation.name is not a C++ keyword
// TODO: Add initial value to inputs in the model description file
	def void compile(SemanticAdaptation adaptation) {
		for (type : adaptation.elements.filter(Adaptation)) {
			var LinkedHashMap<String, Pair<String, Integer>> svDefs = newLinkedHashMap();
			var ArrayList<String> fmus = newArrayList();
			var LinkedHashMap<String, ScalarVariable> sVars = newLinkedHashMap();
			var String genSource = "";
						
			// Load Model Description file
			for (fmu : type.inner.eAllContents.toIterable.filter(InnerFMU)) {
				// TODO: Merge this with ModelDescriptionCreator
				var md = new ModelDescription(fmu.name, new File(fmu.path.replace('\"', '')));
				fmus.add(fmu.name);
				svDefs.putAll(md.svDef);
				sVars.putAll(md.sv);
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
			val String include = '''#include «type.name».h''';			
			val String constructor = compileConstructor(type.name, outRuleResult, inRuleResult, sVars);
			genSource = include + constructor + genSource;				

			// Generate the source file for the SA
			fsa.generateFile(type.name + ".cpp", genSource);

			// Compile defines for the scalar variables
			var genDef = calcDefines(svDefs).join("\n");
			// Compile the class definition file for the SA
			val String header = compileHeader(type.name, inRuleResult, outRuleResult, crtlRuleResult, fmus, sVars);
			
 			// Generate the header file for the SA
			fsa.generateFile(type.name + ".h", genDef + header);
		}
	}

	def String compileHeader(String name, InOutRulesBlockResult inRulesResult, InOutRulesBlockResult outRulesResult,
		RulesBlockResult crtlRulesResult, ArrayList<String> fmus, LinkedHashMap<String, ScalarVariable> sVars) {
		return '''
			class «name» : SemanticAdaptation<«name»>{
				public:
					«name»();
					virtual ~«name»();
					
					void setFmiValue(int id, int value);
					void setFmiValue(int id, bool value);
					void setFmiValue(int id, double value);
				
					int getFmiValueInteger(int id);
					bool getFmiValueBoolean(int id);
					double getFmiValueDouble(int id);
				private:
					shared_ptr<std::list<Rule<«name»>>>createInputRules();
					shared_ptr<std::list<Rule<«name»>>> createOutputRules();
					
					/*in rules*/
					«inRulesResult.functionSignatures.join("\n")»
					
					/*out rules*/
					«outRulesResult.functionSignatures.join("\n")»
					
					«crtlRulesResult.functionSignatures.join("\n")»
					
					«FOR fmu : fmus»
						shared_ptr<Fmu> «fmu»;
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
		LinkedHashMap<String, ScalarVariable> sVars) {
		return 
			'''
				«name»::«name»() : SemanticAdaptation(createInputRules(),createOutputRules())
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
				}
			''';
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
			svDefs, name);
	}

	def InOutRulesBlockResult compileInRuleBlock(Iterable<InRulesBlock> rulesBlocks,
		LinkedHashMap<String, Pair<String, Integer>> svDefs, String name) {
		return compileInOutRuleBlocks(new InRulesConditionSwitch(name, svDefs), rulesBlocks.map[x|x as InOutRules],
			svDefs, name);
	}

	def InOutRulesBlockResult compileInOutRuleBlocks(InOutRulesConditionSwitch visitor,
		Iterable<InOutRules> rulesBlocks, LinkedHashMap<String, Pair<String, Integer>> svDefs, String name) {
		var String cpp = "";
		for (ruleBlock : rulesBlocks) {
			cpp += visitor.doSwitch(ruleBlock)
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
