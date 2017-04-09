package be.uantwerpen.ansymo.semanticadaptation.tests

import be.uantwerpen.ansymo.semanticadaptation.testframework.XtextParametersRunnerFactory
import java.io.File
import org.apache.commons.io.FileUtils
import org.eclipse.xtext.testing.InjectWith
import org.junit.Assert
import org.junit.Test
import org.junit.runner.RunWith
import org.junit.runners.Parameterized
import java.util.List
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import java.util.HashMap

@RunWith(typeof(Parameterized))
@InjectWith(SemanticAdaptationInjectorProvider)
@Parameterized.UseParametersRunnerFactory(XtextParametersRunnerFactory)
abstract class ParserFolderTest extends BasicParserTest {

	val File directory;

	new(File directory) {
		this.directory = directory;
	}

	@Test
	def test() {
		val File[] files = FileUtils.listFiles(this.directory, #["sa"], true);
		Assert.assertFalse("The folder " + this.directory + " does not contain any .sa files", files.isEmpty);
		var dependencies = new HashMap<File, String[]>();
		var List<String> loadedModules = newArrayList;

		// Get all dependencies
		for (File file : files) {
			dependencies.put(file, getDependencies(file));
		}

		var SemanticAdaptation model = null;

		// Load the modules in the correct order
		while (!dependencies.isEmpty) {
			var List<File> entriesToRemove = newArrayList;
			for (entry : dependencies.entrySet) {
				if (loadedModules.containsAll(entry.value)) {
					if (model === null) {
						model = __parse(entry.key);
					} else {
						model = __parse(entry.key, model.eResource.resourceSet);
					}
					__assertNoParseIssues(model, entry.key)
					loadedModules.add(model.name);
					entriesToRemove.add(entry.key);
				}
			}
			for (entry : entriesToRemove) {
				dependencies.remove(entry);
			}
		}

		__assertNoParseErrors(model, null)
	}
}
