package be.uantwerpen.ansymo.semanticadaptation.tests

import java.io.File
import java.io.FileReader
import java.util.ArrayList
import org.eclipse.emf.common.util.BasicEList
import org.eclipse.emf.common.util.EList
import org.eclipse.emf.ecore.EObject
import org.eclipse.emf.ecore.util.EDataTypeEList
import org.eclipse.emf.ecore.util.EObjectEList
import org.eclipse.xtext.testing.InjectWith
import org.eclipse.xtext.testing.XtextRunner
import org.junit.runner.RunWith

import static extension com.google.common.io.CharStreams.*

@RunWith(XtextRunner)
@InjectWith(SemanticAdaptationInjectorProvider)
abstract class AbstractSemanticAdaptationTest {
	
	ArrayList<Integer> visited = new ArrayList<Integer>
	
	/*@Inject
    private InMemoryFileSystemAccess fsa
	
	def __setUp(File dir) {
		for (File f : dir.listFiles()) {
			if (f.name.endsWith(".sa") && !fsa.isFile(f.name)) {
				//println("adding " + f.name)
				fsa.generateFile(f.name, new FileReader(f).readLines.join("\n"))
			}
		}
		//println(fsa.allFiles.keySet)
	}*/
	
	/**
	 * reads a file from the permanent file system
	 */
	 def String readFile(File file){
	 	return new FileReader(file).readLines.join("\n");
	 }
	 
	def String readFile(String basefilename) {
		val f = new File(basefilename)
		//println("testing " + f.name)
		//__setUp(f.parentFile)
		//return fsa.readTextFile(f.name).toString()
		return new FileReader(f).readLines.join("\n")
	}
	
	def print_ast(EObject root) {
		visited.clear
		println(root.eClass.name)
		print_ast_element(root, 0)
	}
	
	private def void print_ast_element(EObject element, int indent) {
		if (visited.contains(element.hashCode)) {
			return
		}
		visited.add(element.hashCode)
		element.eClass.EAllStructuralFeatures.forEach[f | 
			val feature = element.eGet(f)
			if (feature != null) {
				if (feature instanceof EList<?>) {
					(feature as EObjectEList<?>).forEach[e | 
						print(ind(indent+1) + f.name + "(" + feature.indexOf(e) + "): ")
						//println("List<" + f.EType.name + ">")
						if (feature instanceof EObjectEList<?>) {
							print((e as EObject).class.simpleName.substring(0, (e as EObject).class.simpleName.length-4))
							printObject((e as EObject), indent+1)
						} else if (feature instanceof EDataTypeEList<?>) { // in case of enums
							println(e.class.simpleName + " = " + e)
						} else if (feature instanceof BasicEList<?>) {
							throw new Exception(f.name + " other type of list: " + feature.class.name)
						}
					]
				} else {
					print(ind(indent+1) + f.name + ": ")
					if (feature instanceof EObject) {
						print(feature.class.simpleName.substring(0, feature.class.simpleName.length-4))
						printObject((feature as EObject), indent+1)
					} else if (feature instanceof String) {
						println(feature.class.simpleName + " = '" + feature + "'")
					} else {
						println(feature.class.simpleName + " = " + feature)
					}
				}
			} else { // filter out null values
				print(ind(indent+1) + f.name + ": ")
				println("null")
			}
		]
		return
	}
	
	private def void printObject(EObject element, int indent) {
		if (visited.contains(element.hashCode)) {
			val namelist = element.eClass.EAllStructuralFeatures.filter(e | e.name.equals("name"))
			if (namelist.length == 0) {
				throw new Exception("Reference " + element + " does not have a 'name' attribute")
			}
			println(" -> " + element.eGet(element.eClass.EAllStructuralFeatures.filter(e | e.name.equals("name")).get(0)))
		} else {
			println()
			print_ast_element(element, indent)
		}
		return
	}
	
	private def ind(int indent) {
		var s = ""
		for (var i = 0 ; i < indent ; i++) {
			s += "|   "
		}
		return s
	}

}
