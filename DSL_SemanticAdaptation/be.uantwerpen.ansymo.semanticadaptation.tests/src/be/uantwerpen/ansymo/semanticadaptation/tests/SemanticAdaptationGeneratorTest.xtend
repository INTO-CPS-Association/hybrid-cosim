/*
 * generated by Xtext 2.10.0
 */
package be.uantwerpen.ansymo.semanticadaptation.tests

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Adaptation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.AtomicUnity
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.BoolLiteral
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InnerFMU
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.MultiplyUnity
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import com.google.inject.Inject
import org.eclipse.xtext.testing.InjectWith
import org.eclipse.xtext.testing.XtextRunner
import org.eclipse.xtext.util.IAcceptor
import org.eclipse.xtext.xbase.testing.CompilationTestHelper
import org.eclipse.xtext.xbase.testing.CompilationTestHelper.Result
import org.junit.Test
import org.junit.runner.RunWith
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Variable
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Assignment
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.CompositeOutputFunction

@RunWith(XtextRunner)
@InjectWith(SemanticAdaptationInjectorProvider)
class SemanticAdaptationGeneratorTest extends AbstractSemanticAdaptationTest{
	
	@Inject extension CompilationTestHelper
	
	@Test def test_inferTypesAndUnits_sample1() { __generate('input/canonical_generation/sample1.sa', new IAcceptor<CompilationTestHelper.Result>(){
			override accept(Result t) {
				var Adaptation sa = t.resourceSet.resources.head.allContents.toIterable.filter(SemanticAdaptation).last.elements.filter(Adaptation).head
				sa.name == "outerFMU"
				sa.eAllContents.filter(Port).filter[p | p.name=="ext_input_port3"].head.unity instanceof MultiplyUnity
				sa.eAllContents.filter(InnerFMU).filter[f | f.name=="innerFMU2"].head
							.eAllContents.filter(Port).filter[p | p.name=="input_port1"].head.type == "Real"
				sa.eAllContents.filter(InnerFMU).filter[f | f.name=="innerFMU2"].head
							.eAllContents.filter(Port).filter[p | p.name=="outout_port1"].head.type == "Real"
				sa.eAllContents.filter(InnerFMU).filter[f | f.name=="innerFMU2"].head
							.eAllContents.filter(Port).filter[p | p.name=="outout_port1"].head.unity instanceof AtomicUnity
				
			}
		}) }
	
	@Test def test_addInputPorts_sample1() { __generate('input/canonical_generation/sample1.sa', new IAcceptor<CompilationTestHelper.Result>(){
			override accept(Result t) {
				var Adaptation sa = t.resourceSet.resources.head.allContents.toIterable.filter(SemanticAdaptation).last.elements.filter(Adaptation).head
				sa.inports.filter[p | p.name=="innerFMU1__input_port2"].head.type == "Bool"
				sa.inports.filter[p | p.name=="innerFMU2__input_port3"].head.targetdependency.owner.name == "innerFMU2"
				sa.inports.filter[p | p.name=="innerFMU2__input_port3"].head.targetdependency.port.name == "input_port3"
			}
		}) }
	
	@Test def test_addParams_sample1() { __generate('input/canonical_generation/sample1.sa', new IAcceptor<CompilationTestHelper.Result>(){
			override accept(Result t) {
				var Adaptation sa = t.resourceSet.resources.head.allContents.toIterable.filter(SemanticAdaptation).last.elements.filter(Adaptation).head
				sa.params.head.declarations.filter[p | p.name=="INIT_EXT_INPUT_PORT3"].head.type == "Real"
				sa.params.head.declarations.filter[p | p.name=="INIT_INNERFMU1__INPUT_PORT2"].head.expr instanceof BoolLiteral
			}
		}) }
	
	@Test def test_addInVars_sample1() { __generate('input/canonical_generation/sample1.sa', new IAcceptor<CompilationTestHelper.Result>(){
			override accept(Result t) {
				var Adaptation sa = t.resourceSet.resources.head.allContents.toIterable.filter(SemanticAdaptation).last.elements.filter(Adaptation).head
				sa.in.globalInVars.head.declarations.filter[p | p.name=="stored__innerFMU2__input_port2"].head.type == "Bool"
				sa.in.globalInVars.head.declarations.filter[p | p.name=="stored__innerFMU2__input_port3"].head.expr instanceof Variable
			}
		}) }
	
	@Test def test_addExternal2StoredAssignments_sample1() { __generate('input/canonical_generation/sample1.sa', new IAcceptor<CompilationTestHelper.Result>(){
			override accept(Result t) {
				var Adaptation sa = t.resourceSet.resources.head.allContents.toIterable.filter(SemanticAdaptation).last.elements.filter(Adaptation).head
				sa.in.rules.head.statetransitionfunction.statements.head instanceof Assignment
				(sa.in.rules.head.statetransitionfunction.statements.head as Assignment).lvalue.ref.name == "stored__innerFMU2__input_port3"
				((sa.in.rules.head.statetransitionfunction.statements.head as Assignment).expr as Variable).ref.name == "innerFMU2__input_port3"
			}
		}) }
	
	@Test def test_addInRules_External2Internal_Assignments_sample1() { __generate('input/canonical_generation/sample1.sa', new IAcceptor<CompilationTestHelper.Result>(){
			override accept(Result t) {
				var Adaptation sa = t.resourceSet.resources.head.allContents.toIterable.filter(SemanticAdaptation).last.elements.filter(Adaptation).head
				val outFunction = sa.in.rules.head.outputfunction as CompositeOutputFunction
				val firstAssignment = outFunction.statements.head as Assignment
				firstAssignment.lvalue.ref.name == "input_port3"
				(firstAssignment.expr as Variable).ref.name == "innerFMU2__input_port3"
			}
		}) }
	
	@Test def window_SA_parseNoExceptions() { __generate('input/power_window_case_study/window_sa.BASE.sa', new IAcceptor<CompilationTestHelper.Result>(){
			override accept(Result t) { }
		}) }
	
	@Test def window_SA_parseNoExceptions2() { __generate('input/power_window_case_study/window_sa_comp_units.sa', new IAcceptor<CompilationTestHelper.Result>(){
			override accept(Result t) { }
		}) }
	
	@Test def lazy_SA_parseNoExceptions() { __generate('input/power_window_case_study/lazy.sa', new IAcceptor<CompilationTestHelper.Result>(){
			override accept(Result t) { }
		}) }
	
	
	def void __generate(String filename, IAcceptor<CompilationTestHelper.Result> acceptor) {
		//readFile(filename).assertCompilesTo('oracles/power_window_case_study/lazy.BASE.sa')
		
		readFile(filename).compile(acceptor)
		
	}
}
