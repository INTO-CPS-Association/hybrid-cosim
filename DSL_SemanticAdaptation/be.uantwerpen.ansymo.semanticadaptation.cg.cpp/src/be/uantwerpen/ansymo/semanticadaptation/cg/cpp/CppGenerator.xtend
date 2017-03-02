package be.uantwerpen.ansymo.semanticadaptation.cg.cpp

import be.uantwerpen.ansymo.semanticadaptation.generator.SemanticAdaptationGenerator
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Adaptation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import org.eclipse.emf.ecore.resource.Resource
import org.eclipse.xtext.generator.IFileSystemAccess2
import org.eclipse.xtext.generator.IGeneratorContext

class CppGenerator extends SemanticAdaptationGenerator {

	var ModelDescriptionCreator mdCreator = new ModelDescriptionCreator()

	override void doGenerate(Resource resource, IFileSystemAccess2 fsa, IGeneratorContext context) {

		for (type : resource.allContents.toIterable.filter(SemanticAdaptation)){
				fsa.generateFile(type.name + ".cpp", type.compile)
				mdCreator.name = type.name;
				fsa.generateFile("modelDescription.xml", mdCreator.modelDescription);
		}
	}

// TODO: Verify adaptation.name is not a C++ keyword
// TODO: Add initial value to inputs in the model description file
	def CharSequence compile(SemanticAdaptation adaptation) {
		var adaptationCharSequence = newArrayList()
		for (type : adaptation.elements.filter(Adaptation)) {
			mdCreator.CreateInputsOutput(type);
			adaptationCharSequence.add(type.compile)
		}

		return adaptationCharSequence.join('''\n''');
	}

	def CharSequence compile(Adaptation adaptation) {
		
		return '''compiling «adaptation.toString»''';
	}
}
