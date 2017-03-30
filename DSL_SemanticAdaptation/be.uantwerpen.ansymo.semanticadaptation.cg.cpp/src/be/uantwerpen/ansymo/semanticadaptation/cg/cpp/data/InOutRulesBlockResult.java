package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data;

import java.util.LinkedHashMap;
import java.util.List;

import org.eclipse.xtext.xbase.lib.Pair;

public class InOutRulesBlockResult extends RulesBlockResult {
	public final LinkedHashMap<String, Pair<SVType, Object>> globalVars;
	public final LinkedHashMap<String, GlobalInOutVariable> globalVars2;

	public InOutRulesBlockResult(String generatedCpp, List<String> functionSignatures, 
			LinkedHashMap<String, Pair<SVType, Object>> globalVars, 
			LinkedHashMap<String, GlobalInOutVariable> globalVars2)
	{
		super(generatedCpp, functionSignatures);
		this.globalVars = globalVars;
		this.globalVars2 = globalVars2;
	}
}
