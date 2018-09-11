package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.tests

import be.uantwerpen.ansymo.semanticadaptation.tests.SemanticAdaptationInjectorProvider
import org.eclipse.xtext.testing.InjectWith
import org.eclipse.xtext.testing.XtextRunner
import org.junit.runner.RunWith
import org.junit.Test

@RunWith(XtextRunner)
@InjectWith(SemanticAdaptationInjectorProvider)
class TwoInnerModelsTest extends SATest {
	
	@Test
	def ParseSAWithMultipleInnerModels()
	{
		__parseAndGenerateWithNoErrors('mim.sa', 'test_input/multipleInnerModels/', 'mim');
	}

	@Test
	def ParseSAWithPlantSensorMR()
	{
		__parseAndGenerateWithNoErrors('multirate_two_fmus.sa', 'test_input/multipleInnerModels/', 'multirate_two_fmus');
	}

	
}