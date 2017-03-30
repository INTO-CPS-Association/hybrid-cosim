package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation;

import java.util.Collection;
import java.util.UUID;

import javax.xml.parsers.ParserConfigurationException;

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable;
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.exceptions.MissingScalarVariableInformationException;

public class ModelDescriptionCreator {
	private final ModelDescriptionBuilder mdBuilder;
	private final String mdName;
	private final String guid;

	public ModelDescriptionCreator(String name) throws ParserConfigurationException
	{
		this.mdName = name;
		this.guid = UUID.randomUUID().toString();
		this.mdBuilder = new ModelDescriptionBuilder();
	}
	
	public String generateModelDescription(Collection<SAScalarVariable> SASVs) throws ParserConfigurationException, MissingScalarVariableInformationException {
		mdBuilder.CreateTemplate(this.getMdName(), this.guid);
		for (SAScalarVariable sasv : SASVs) {
			mdBuilder.addScalarVariable(sasv.CalcSVar());
		}

		return mdBuilder.toString();
	}


	public String getGuid() {
		return guid;
	}

	public String getMdName() {
		return mdName;
	}
}
