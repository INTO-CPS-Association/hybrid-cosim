package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.tests

import org.eclipse.xtext.testing.XtextRunner
import org.junit.runners.parameterized.TestWithParameters
import org.junit.runners.model.InitializationError
import java.util.List
import org.junit.runners.model.Statement
import org.junit.runner.notification.RunNotifier

class ParameterizedXtextRunner extends XtextRunner {
	val Object[] parameters;
	val String annotatedName;
	
	new(TestWithParameters test) throws InitializationError {
		super(test.testClass.javaClass)
		parameters = test.parameters;
		annotatedName = test.name;
	}
	
	override protected getName() {
		return super.name + annotatedName;
	}

	override protected createTest() throws Exception {
		val object = testClass.onlyConstructor.newInstance(parameters)
		val injectorProvider = getOrCreateInjectorProvider
		if (injectorProvider != null) {
			val injector = injectorProvider.injector
			if (injector != null)
				injector.injectMembers(object)
		}
		return object;
	}
	
	override public void run(RunNotifier notifier){
		super.run(notifier);
	}

	override protected void validateConstructor(List<Throwable> errors) {
		validateOnlyOneConstructor(errors)
	}
	
}