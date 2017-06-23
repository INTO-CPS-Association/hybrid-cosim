package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data;

import java.util.LinkedHashMap;
import java.util.List;

import org.eclipse.xtext.xbase.lib.Pair;

public class InOutRulesBlockResult extends RulesBlockResult {
	public final LinkedHashMap<String, GlobalInOutVariable> gVars;
	public final String constructorInitialization;

	public InOutRulesBlockResult(String generatedCpp, List<String> functionSignatures,
			LinkedHashMap<String, GlobalInOutVariable> gVars, String constructorInitialization)
	{
		super(generatedCpp, functionSignatures);
		this.gVars = gVars;
		this.constructorInitialization = constructorInitialization;
	}
}
