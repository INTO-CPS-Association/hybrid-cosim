/*
 * generated by Xtext 2.10.0
 */
package be.uantwerpen.ansymo.semanticadaptation


/**
 * Initialization support for running Xtext languages without Equinox extension registry.
 */
class SemanticAdaptationStandaloneSetup extends SemanticAdaptationStandaloneSetupGenerated {

	def static void doSetup() {
		new SemanticAdaptationStandaloneSetup().createInjectorAndDoEMFRegistration()
	}
}
