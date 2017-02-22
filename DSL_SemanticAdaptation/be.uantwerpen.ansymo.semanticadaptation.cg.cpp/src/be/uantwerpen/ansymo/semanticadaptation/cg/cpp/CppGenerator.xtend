package be.uantwerpen.ansymo.semanticadaptation.cg.cpp

import be.uantwerpen.ansymo.semanticadaptation.generator.SemanticAdaptationGenerator
import org.eclipse.emf.ecore.resource.Resource
import org.eclipse.xtext.generator.IFileSystemAccess2
import org.eclipse.xtext.generator.IGeneratorContext
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.AtomicFMU

class CppGenerator extends SemanticAdaptationGenerator {
	override void doGenerate(Resource resource, IFileSystemAccess2 fsa, IGeneratorContext context) {

		for (type : resource.allContents.filter(typeof(SemanticAdaptation)).toIterable)
			fsa.generateFile(type.name + ".cpp", '''
				«FOR state : type.elements.filter(AtomicFMU)»
					«state.name» = «state.path»
				«ENDFOR»
			''')

	}
}
