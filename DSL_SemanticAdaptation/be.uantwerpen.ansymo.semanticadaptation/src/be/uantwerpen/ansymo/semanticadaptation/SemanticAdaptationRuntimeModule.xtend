/*
 * generated by Xtext 2.10.0
 */
package be.uantwerpen.ansymo.semanticadaptation

import be.uantwerpen.ansymo.semanticadaptation.generator.SemanticAdaptationGenerator
import be.uantwerpen.ansymo.semanticadaptation.scoping.SemanticAdaptationScopeProvider
import be.uantwerpen.ansymo.semanticadaptation.valueconverter.SemanticAdaptationValueConverters

/**
 * Use this class to register components to be used at runtime / without the Equinox extension registry.
 */
class SemanticAdaptationRuntimeModule extends AbstractSemanticAdaptationRuntimeModule {
	
	override bindIValueConverterService() {
		return SemanticAdaptationValueConverters
	}
	override bindIScopeProvider() {
		return SemanticAdaptationScopeProvider
	}
	override bindIGenerator2() {
		return SemanticAdaptationGenerator
	}
}
