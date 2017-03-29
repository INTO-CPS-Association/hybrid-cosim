package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

import java.util.Optional;

public class SAScalarVariable {

	public MappedScalarVariable sv = null;
	public String defineName;
	public Integer valueReference;
	private SVCausality causality;
	private SVType type;
	private String name;
	private Optional<SVVariability> variability = Optional.empty();
	
	public SAScalarVariable() {
		// TODO Auto-generated constructor stub
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public SVCausality getCausality() {
		return causality;
	}

	public void setCausality(SVCausality causality) {
		this.causality = causality;
	}

	public SVType getType() {
		return type;
	}

	public void setType(SVType type) {
		this.type = type;
	}

	public Optional<SVVariability> getVariability() {
		return variability;
	}

	/*
	 * The variability will only be updated if it is not set.
	 */
	public void setVariability(Optional<SVVariability> variability) {
		if(!this.variability.isPresent())
		this.variability = variability;
	}

}
