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

class CppGenerator extends SemanticAdaptationGenerator {

	var ModelDescriptionCreator mdCreator = new ModelDescriptionCreator()
	var SwitchTest = new Visitor();
	var InRulesConditionSwitch inrules;
	var LinkedHashMap<String, Pair<String, Integer>> scalars = newLinkedHashMap();
	private var IFileSystemAccess2 fsa;

	override void doGenerate(Resource resource, IFileSystemAccess2 fsa, IGeneratorContext context) {
		this.fsa = fsa;
		for (type : resource.allContents.toIterable.filter(SemanticAdaptation)) {
			type.compile;
			//fsa.generateFile(type.name + ".cpp", type.compile)
			mdCreator.name = type.name;
			fsa.generateFile("modelDescription.xml", mdCreator.modelDescription);
		}
//		
//		for(type : resource.allContents.toIterable)
//		{
//			SwitchTest.doSwitch(type);
//		}
	}

// TODO: Verify adaptation.name is not a C++ keyword
// TODO: Add initial value to inputs in the model description file
	def void compile(SemanticAdaptation adaptation) {
		for (type : adaptation.elements.filter(Adaptation)) {
			var fmus = newArrayList();		
			for (fmu : type.inner.eAllContents.toIterable.filter(InnerFMU)) {
				//TODO: Merge this with ModelDescriptionCreator somehow
				var md = new ModelDescription(fmu.name, new File(fmu.path.replace('\"', '')));
				fmus.add(fmu.name);
				this.scalars.putAll(md.scalars);
			}
			
			var defines = newArrayList();
			for(scalar : this.scalars.entrySet){
				val pair = scalar.value;
				defines.add("#define " + pair.key + " " + pair.value);
			}
			
			var String generatedDefines = defines.join("\n");
			fsa.generateFile("defines.cpp", generatedDefines);
			
			var String generatedCpp;
			
			//This generates all the inrules
			this.inrules = new InRulesConditionSwitch(type.name, scalars);
			for (inRules : adaptation.eAllContents.toIterable.filter(InRulesBlock)) {
				for (dataRule : inRules.eAllContents.toIterable.filter(DataRule)) {
					this.inrules.incrementCount;
					generatedCpp+=this.inrules.doSwitch(dataRule);
				}
			}
			
			//This generates all the outrules
			var outrules = new OutRulesConditionSwitch(type.name, scalars);
			for(outRules : adaptation.eAllContents.toIterable.filter(OutRulesBlock)){
				for(dataRule : outRules.eAllContents.toIterable.filter(DataRule)){
					outrules.incrementCount;
					generatedCpp+=outrules.doSwitch(dataRule);
				}
			}
			
			var controlrule = new ControlConditionSwitch(type.name,	 scalars);
			for(controlRule : adaptation.eAllContents.toIterable.filter(ControlRuleBlock)){
				for(crtlRule : controlRule.eAllContents.toIterable.filter(ControlRule)){
					generatedCpp += controlrule.doSwitch(crtlRule);
				}
			}

			fsa.generateFile(type.name+".cpp", generatedCpp);
			
			var String header = 
			'''
			class «type.name» : SemanticAdaptation<«type.name»>{
				public:
					«type.name»();
					virtual ~«type.name»();
					
					void setFmiValue(int id, int value);
					void setFmiValue(int id, bool value);
					void setFmiValue(int id, double value);
				
					int getFmiValueInteger(int id);
					bool getFmiValueBoolean(int id);
					double getFmiValueDouble(int id);
				private:
					shared_ptr<std::list<Rule<«type.name»>>>createInputRules();
					shared_ptr<std::list<Rule<«type.name»>>> createOutputRules();
					
					/*in rules*/
					«inrules.functionSignatures.join("\n")»
					
					/*out rules*/
					«outrules.functionSignatures.join("\n")»
					
					«controlrule.functionSignatures.join("\n")»
					
					«FOR fmu : fmus»
						shared_ptr<Fmu> «fmu»;
					«ENDFOR»
					
					«FOR sv : scalars.entrySet»
						
					«ENDFOR»
			}
			'''
			fsa.generateFile(type.name+".h", header);
			
		}

	}

	def CharSequence compile(Adaptation adaptation) {
		return '''compiling «adaptation.toString»''';
	}
}
