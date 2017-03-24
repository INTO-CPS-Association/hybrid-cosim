package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;

import org.eclipse.xtext.xbase.lib.Pair;

public class InOutRulesBlockResult extends RulesBlockResult {
	public final LinkedHashMap<String, Pair<SVType, Object>> globalVars;

	public InOutRulesBlockResult(String generatedCpp, List<String> functionSignatures, LinkedHashMap<String, Pair<SVType, Object>> globalVars)
	{
		super(generatedCpp, functionSignatures);
		this.globalVars = globalVars;
	}
}
