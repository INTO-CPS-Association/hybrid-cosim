package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.tests

import org.junit.runners.parameterized.ParametersRunnerFactory
import org.junit.runners.parameterized.TestWithParameters
import org.junit.runners.model.InitializationError

class XtextParametersRunnerFactory implements ParametersRunnerFactory {
	override createRunnerForTestWithParameters(TestWithParameters test) throws InitializationError {
		new ParameterizedXtextRunner(test)
	}
}