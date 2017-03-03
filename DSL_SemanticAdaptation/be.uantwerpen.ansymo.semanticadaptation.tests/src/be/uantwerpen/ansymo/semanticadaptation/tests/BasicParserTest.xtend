package be.uantwerpen.ansymo.semanticadaptation.tests

import java.util.regex.Pattern
import org.eclipse.emf.ecore.EObject
import org.eclipse.emf.ecore.resource.ResourceSet
import org.eclipse.xtext.testing.util.ParseHelper
import com.google.inject.Inject
import org.eclipse.xtext.testing.validation.ValidationTestHelper
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import java.io.File
import java.util.List
import org.eclipse.xtext.util.Arrays
import org.eclipse.xtext.validation.Issue
import com.google.common.base.Predicate
import static org.junit.Assert.fail
import static com.google.common.collect.Iterables.isEmpty
import static com.google.common.collect.Iterables.filter
import org.eclipse.xtext.diagnostics.Severity
import java.io.BufferedReader
import java.io.FileReader

abstract class BasicParserTest extends AbstractSemanticAdaptationTest {

	@Inject extension ParseHelper<SemanticAdaptation>
	@Inject extension  ValidationTestHelper

	def getDependencies(File file) {
		var List<String> dependencies = newArrayList;
		val BufferedReader in = new BufferedReader(new FileReader(file));
		var continue = true;
		while (continue) {
			val line = in.readLine();
			if (line.contains("module")) {
				continue = false;
			} else if (line.contains("import")) {
				val module = line.substring(line.indexOf("import") + 7, line.length());
				dependencies.add(module);
			}
			continue = in.ready && continue;
		}

		in.close();

		return dependencies;
	}

	def __parseNoErrors(File filename) {
		val model = __parse(filename)
		__assertNoParseErrors(model, filename)
	}

	def __parseNoErrorsPrint(File filename) {
		val root = __parse(filename)
		print_ast(root)
		__assertNoParseErrors(root, filename)
	}

	def __parse(File filename) {
		val model = readFile(filename).parse
		return model;
	}

	def __parse(File filename, ResourceSet resourceSetToUse) {

		return readFile(filename).parse(resourceSetToUse)
	}

	def __assertNoParseIssues(EObject root, File filename) {

		val List<Issue> validate = root.validate();
		val Iterable<Issue> issues = filter(validate, new Predicate<Issue>() {

			override apply(Issue input) {

				return Severity.ERROR == input.getSeverity() && !input.code.contains("Linking");

//				if (issuecode.equals(input.getCode())) {
//					return userData == null || Arrays.contains(input.getData(), userData);
//				}
//				return false;
			}

		});
		if (!isEmpty(issues))
			// fail("Expected no errors, but got :" + root.getIssuesAsString(resource, issues, new StringBuilder()));
			__assertNoParseErrors(root, filename) // we are bit lazy
	}

	def __assertNoParseErrors(EObject root, File filename) {
		try {
			root.assertNoErrors
		} catch (AssertionError e) {
			val p = Pattern.compile(".*, offset (?<offset>[0-9]+), length (?<length>[0-9]+)")
			val code = readFile(filename)
			for (String line : e.message.split("\n")) {
				val m = p.matcher(line)
				m.matches()
				val count = __occurrencesInString(code.subSequence(0, Integer.valueOf(m.group("offset"))).toString(),
					"\n")
				print(filename + " at line " + (count + 1) + ": ")
				println(line)
			}
			throw e
		}
	}

	def __occurrencesInString(String str, String findstr) {
		var lastIndex = 0
		var count = 0
		while (lastIndex != -1) {
			lastIndex = str.indexOf(findstr, lastIndex)
			if (lastIndex != -1) {
				count++
				lastIndex += findstr.length()
			}
		}
		return count
	}
}
