package be.uantwerpen.ansymo.semanticadaptation.testframework;

import static org.eclipse.xtext.util.Exceptions.throwUncheckedException;

import org.eclipse.xtext.testing.IInjectorProvider;
import org.eclipse.xtext.testing.InjectWith;
import org.junit.runners.model.TestClass;

import com.google.common.collect.ClassToInstanceMap;
import com.google.common.collect.MutableClassToInstanceMap;

public class InjectorProviders {

	private static ClassToInstanceMap<IInjectorProvider> injectorProviderClassCache = MutableClassToInstanceMap.create();
	
	public static IInjectorProvider getOrCreateInjectorProvider(TestClass testClass) {
		InjectWith injectWith = testClass.getJavaClass().getAnnotation(InjectWith.class);
		if (injectWith != null) {
			Class<? extends IInjectorProvider> klass = injectWith.value();
			IInjectorProvider injectorProvider = injectorProviderClassCache.get(klass);
			if (injectorProvider == null) {
				try {
					injectorProvider = klass.newInstance();
					injectorProviderClassCache.put(klass, injectorProvider);
				} catch (Exception e) {
					throwUncheckedException(e);
				}
			}
			return injectorProvider;
		}
		return null;
	}

	public static IInjectorProvider getInjectorProvider(TestClass testClass) {
		InjectWith injectWith = testClass.getJavaClass().getAnnotation(InjectWith.class);
		if (injectWith != null) {
			return injectorProviderClassCache.get(injectWith.value());
		}
		return null;
	}

	public static IInjectorProvider createInjectorProvider(TestClass testClass) {
		InjectWith injectWith = testClass.getJavaClass().getAnnotation(InjectWith.class);
		if (injectWith != null) {
			try {
				return injectWith.value().newInstance();
			} catch (Exception e) {
				throwUncheckedException(e);
			}
		}
		return null;
	}

}
