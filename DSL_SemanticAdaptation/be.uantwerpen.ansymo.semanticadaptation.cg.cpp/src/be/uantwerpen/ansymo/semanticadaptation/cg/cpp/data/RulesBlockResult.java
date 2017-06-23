package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data;

import java.util.List;

public class RulesBlockResult {
	public final String generatedCpp;
	public final List<String> functionSignatures;
	public RulesBlockResult(String generatedCpp, List<String> functionSignatures) {
		this.generatedCpp = generatedCpp;
		this.functionSignatures = functionSignatures;
	}
}
