package be.uantwerpen.ansymo.semanticadaptation.tests

import java.io.File
import java.util.Collection
import java.util.List
import java.util.Vector
import org.junit.runners.Parameterized.Parameters
import org.junit.runner.RunWith
import org.junit.runners.Parameterized
import org.eclipse.xtext.testing.InjectWith
import be.uantwerpen.ansymo.semanticadaptation.testframework.XtextParametersRunnerFactory

@RunWith(typeof(Parameterized))
@InjectWith(SemanticAdaptationInjectorProvider)
@Parameterized.UseParametersRunnerFactory(XtextParametersRunnerFactory)
class PowerWindowCaseStudyFolderTest extends ParserFolderTest {
	
	@Parameters(name = "{index} - {0}")
	def static Collection<Object[]> data() {
		
		val List<Object[]> tests = new Vector
		
		tests.add(#[new File("testInputs/single_folder_spec".replace('/',File.separatorChar))]);
		
		return tests;
	}
	
	new(File directory) {
		super(directory)
	}
	
}