package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

import java.util.Optional;

public class ScalarVariable {
	private String owner;
	private String name;
	private String valueReference;
	private String description;
	private String variability;
	private SVCausality causality;
	private String initial;
	private SVType type;
	private String start;

	private ScalarVariable() {

	}

	public static ScalarVariable Create() {
		return new ScalarVariable();
	}

	public ScalarVariable setOwner(String owner) {
		this.owner = owner;
		return this;
	}

	public String getOwner(){return this.owner;}

	public String getName() {
		return name;
	}

	public ScalarVariable setName(String name) {
		this.name = name;
		return this;
	}

	public String getValueReference() {
		return valueReference;
	}

	public ScalarVariable setValueReference(String valueReference) {
		this.valueReference = valueReference;
		return this;
	}

	public String getVariability() {
		return variability;
	}

	public ScalarVariable setVariability(String variability) {
		this.variability = variability;
		return this;
	}

	public SVCausality getCausality() {
		return causality;
	}

	public ScalarVariable setCausality(SVCausality causality) {
		this.causality = causality;
		return this;
	}

	public String getInitial() {
		return initial;
	}

	public ScalarVariable setInitial(String initial) {
		this.initial = initial;
		return this;
	}

	public SVType getType() {
		return type;
	}

	public ScalarVariable setType(SVType type) {
		this.type = type;
		return this;
	}

	public String getStart() {
		return start;
	}

	public ScalarVariable setStart(String start) {
		this.start = start;
		return this;
	}

	public String getDescription() {
		return description;
	}

	public ScalarVariable setDescription(String description) {
		this.description = description;
		return this;
	}
}
