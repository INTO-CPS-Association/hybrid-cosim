package be.uantwerpen.ansymo.semanticadaptation.tests

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import be.uantwerpen.ansymo.semanticadaptation.testframework.XtextParametersRunnerFactory
import java.io.File
import org.apache.commons.io.FileUtils
import org.eclipse.xtext.testing.InjectWith
import org.junit.Assert
import org.junit.Test
import org.junit.runner.RunWith
import org.junit.runners.Parameterized

@RunWith(typeof(Parameterized))
@InjectWith(SemanticAdaptationInjectorProvider)
@Parameterized.UseParametersRunnerFactory(XtextParametersRunnerFactory)
abstract class ParserFolderTest extends BasicParserTest{
	
	val File directory;
	new (File directory){
		this.directory = directory; 
	}
	
	@Test
	def test() {
		val File[] files = FileUtils.listFiles(this.directory, #["sa"], true);
		Assert.assertFalse("The folder " + this.directory + " does not contain any .sa files", files.isEmpty);

		var SemanticAdaptation model = null;
		for (File file : files) {
			System.out.println("Processing file: "+file)
			if (model === null) {
				model = __parse(file);
			} else {
				model = __parse(file, model.eResource.resourceSet);
			}
			
			__assertNoParseIssues(model,file)
		}
			__assertNoParseErrors(model, null)
	}
}
