package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.tests

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation.BuildUtilities
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation.CppGenerator
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.tests.CMakeUtil.CMakeGenerateException
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation.CMakeListsGenerator
import be.uantwerpen.ansymo.semanticadaptation.testframework.FmuMainTestGenerator
import be.uantwerpen.ansymo.semanticadaptation.tests.AbstractSemanticAdaptationTest
import be.uantwerpen.ansymo.semanticadaptation.tests.SemanticAdaptationInjectorProvider
import com.google.inject.Inject
import java.io.File
import java.io.FileFilter
import java.io.FileWriter
import java.nio.file.Files
import java.nio.file.Paths
import java.util.regex.Pattern
import org.apache.commons.io.FileUtils
import org.eclipse.emf.ecore.EObject
import org.eclipse.emf.ecore.resource.ResourceSet
import org.eclipse.xtext.generator.InMemoryFileSystemAccess
import org.eclipse.xtext.testing.InjectWith
import org.eclipse.xtext.testing.XtextRunner
import org.eclipse.xtext.testing.util.ParseHelper
import org.eclipse.xtext.testing.validation.ValidationTestHelper
import org.junit.Assert
import org.junit.BeforeClass
import org.junit.Ignore
import org.junit.Test
import org.junit.runner.RunWith

abstract class SATest extends AbstractSemanticAdaptationTest {
	
	@Inject extension ParseHelper<SemanticAdaptation>
	@Inject extension  ValidationTestHelper
	
	/**
	 * Parses the SA file and generates the C++.
	 * 
	 * @param filename Name of the SA file
	 * @param directory Name of the directory containing the SA file and respective FMUs
	 * @param projectName Name of the current project
	 */
	def __parseAndGenerateWithNoErrors(String filename, String directory, String projectName) {
		val dirTestOutput = directory.replace('test_input/','target/test-classes/')
		val saRootDir = Paths.get(dirTestOutput).toFile();
		val saGenRootTempDir = Paths.get(dirTestOutput, projectName).toFile();
		val absFileName = Paths.get(dirTestOutput, filename).toFile();
		val srcGenPath = new File(saGenRootTempDir, "sources")
		val resourcesPath = new File(saGenRootTempDir, "resources");
		
		println("saGenRootTempDir="+saGenRootTempDir.absolutePath)
		println("absFileName="+absFileName.absolutePath)
		
		val model = __parse(absFileName.absolutePath)
		__assertNoParseErrors(model, absFileName.absolutePath)

		val fsa = new InMemoryFileSystemAccess();
		val cppGen = new CppGenerator();
		cppGen.doGenerate(model.eResource, fsa, saRootDir.absolutePath);

		if (saGenRootTempDir.exists) {
			BuildUtilities.deleteFolder(saGenRootTempDir);
		}

		saGenRootTempDir.mkdirs();
		srcGenPath.mkdirs();
		resourcesPath.mkdirs();

		for (files : fsa.allFiles.entrySet) {
			val fName = files.key.substring(14);

			var File fp;
			if (fName.equals("modelDescription.xml") || fName.equals("CMakeLists.txt") || fName.equals("msys-toolchain.cmake")) {
				fp = new File(saGenRootTempDir, fName);
			} else {
				fp = new File(srcGenPath, fName);
			}

			BuildUtilities.writeToFile(fp, files.value.toString);
		}

		val mainCpp = FmuMainTestGenerator.generateMainCppFile(resourcesPath.absolutePath.replace("\\", "\\\\"));
		BuildUtilities.writeToFile(new File(srcGenPath, "main.cpp"), mainCpp);

		for (rf : cppGen.resourcePaths) {
			val sinkFile = new File(resourcesPath, rf.name);
			System.out.println("Copied file to: " + sinkFile);
			BuildUtilities.copyFile(rf, sinkFile);
		}
	}
	
	
	
	
	def __parse(String filename) {
		return readFile(filename).parse
	}

	def __parse(
		String filename,
		ResourceSet resourceSetToUse
	) {

		return readFile(filename).parse(resourceSetToUse)
	}
	
	def __assertNoParseErrors(EObject root, String filename) {
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