/*
 * generated by Xtext 2.10.0
 */
package be.uantwerpen.ansymo.semanticadaptation.tests

import org.junit.Test
import com.google.inject.Inject
import org.junit.runner.RunWith
import java.io.File
import org.eclipse.xtext.testing.XtextRunner
import org.eclipse.xtext.testing.InjectWith
import org.eclipse.xtext.xbase.testing.CompilationTestHelper
import org.junit.Ignore

@RunWith(XtextRunner)
@InjectWith(SemanticAdaptationInjectorProvider)
class SemanticAdaptationGeneratorTest extends AbstractSemanticAdaptationTest{
	
	@Inject extension CompilationTestHelper
	
	@Ignore @Test def powerwindow_model_only() { __generate('input/powerwindow_model_only.sa') }
	@Ignore @Test def powerwindow_algebraic_loop_delay_BASE() { __generate('input/powerwindow_algebraic_loop_delay_BASE.sa') }
	@Ignore @Test def powerwindow_algebraic_loop_delay() { __generate('input/powerwindow_algebraic_loop_delay.sa') }
	@Ignore @Test def powerwindow_algebraic_loop_iteration_BASE() { __generate('input/powerwindow_algebraic_loop_iteration_BASE.sa') }
	@Ignore @Test def powerwindow_algebraic_loop_iteration() { __generate('input/powerwindow_algebraic_loop_iteration.sa') }
	@Ignore @Test def powerwindow_controller_delay() { __generate('input/powerwindow_controller_delay.sa') }
	@Ignore @Test def powerwindow_controller_delay_BASE() { __generate('input/powerwindow_controller_delay_BASE.sa') }
	@Ignore @Test def powerwindow_multi_rate() { __generate('input/powerwindow_multi_rate.sa') }
	@Ignore @Test def powerwindow_multi_rate_BASE() { __generate('input/powerwindow_multi_rate_BASE.sa') }
	@Ignore @Test def powerwindow() { __generate('input/powerwindow.sa') }
	
	def void __generate(String filename) {
		val f = new File(filename)
		readFile(filename).assertCompilesTo('oracles/test1.txt'/*readFile('oracles/' + f.name)*/)
	}

}
