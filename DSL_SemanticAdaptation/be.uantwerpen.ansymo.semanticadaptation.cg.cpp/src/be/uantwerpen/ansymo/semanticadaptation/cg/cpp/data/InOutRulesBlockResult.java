package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data;

import java.util.LinkedHashMap;
import java.util.List;

import org.eclipse.xtext.xbase.lib.Pair;

public class InOutRulesBlockResult extends RulesBlockResult {
	//public final LinkedHashMap<String, GlobalInOutVariable> gVars;
	//public final String constructorInitialization;

	public InOutRulesBlockResult(String generatedCpp, List<String> functionSignatures)
	{
		super(generatedCpp, functionSignatures);
	}
}
