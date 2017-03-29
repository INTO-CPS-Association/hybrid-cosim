package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.Map.Entry;

import org.eclipse.xtext.xbase.lib.Pair;

// TODO: Add ports not mentioned in the sa file to the model description
public class ModelDescriptionCreatorV2 {

	ArrayList<SAScalarVariable> SVs;
	ArrayList<SAScalarVariable> outputSVs;
	
	public ModelDescriptionCreatorV2(String adaptationName,
			LinkedHashMap<String, Pair<SVType, Object>> globalOutputVars,
			LinkedHashMap<String, Pair<SVType, Object>> globalInputVars,
			LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mappedScalarVariables) {
		int valueRef = 1;
		
		for (Entry<String, Pair<SVType, Object>> outputVar : globalOutputVars.entrySet()) {
			// Find the corresponding correct SV value
			MappedScalarVariable foundSV = null;
			for (Entry<String, LinkedHashMap<String, MappedScalarVariable>> mSV : mappedScalarVariables.entrySet()) {
				if (mSV.getValue().containsKey(outputVar.getKey())) {
					foundSV = mSV.getValue().get(outputVar.getKey());
					break;
				}
			}
			if(foundSV != null)
			{
				SAScalarVariable saSV = new SAScalarVariable();
			}
		}

	}
}
