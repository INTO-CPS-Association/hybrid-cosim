package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data;

import java.util.ArrayList;
import java.util.Optional;

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.exceptions.MissingScalarVariableInformationException;

public class SAScalarVariable {

	private String defineName;
	private Optional<Integer> valueReference = Optional.empty();
	private Optional<SVCausality> causality = Optional.empty();
	private Optional<SVType> type = Optional.empty();
	private String name;
	private Optional<SVVariability> variability = Optional.empty();
	private boolean partOfMD = false;

	public ScalarVariable CalcSVar() throws MissingScalarVariableInformationException {

		ArrayList<String> error = new ArrayList<String>();
		if (!this.causality.isPresent()) {
			error.add("Missing causality information");
		}
		if (!this.type.isPresent()) {
			error.add("Missing type information");
		}
		if (!this.variability.isPresent()) {
			error.add("Missing variability information");
		}
		if (this.name == null) {
			error.add("Missing name information");
		}
		if (!this.valueReference.isPresent()) {
			error.add("Missing value reference information");
		}

		if (error.isEmpty()) {
			return ScalarVariable.Create().setCausality(this.causality.get()).setVariability(this.variability.get())
					.setType(this.type.get()).setName(this.name).setValueReference(this.getValueReference().toString());
		} else {
			throw new MissingScalarVariableInformationException(String.join(" -- ", error));
		}
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Optional<SVCausality> getCausality() {
		return causality;
	}

	public void setCausality(SVCausality causality) {
		this.causality = Optional.of(causality);
	}

	public Optional<SVType> getType() {
		return type;
	}

	public void setType(SVType type) {
		this.type = Optional.of(type);
	}

	public Optional<SVVariability> getVariability() {
		return variability;
	}

	public void setVariability(SVVariability variability) {
		this.variability = Optional.of(variability);
	}

	public Integer getValueReference() throws MissingScalarVariableInformationException {
		if (!this.valueReference.isPresent()) {
			throw new MissingScalarVariableInformationException("Missing value reference information");
		}
		return valueReference.get();
	}

	public void setValueReference(Integer valueReference) {
		this.valueReference = Optional.of(valueReference);
	}

	public String getDefineName() {
		return defineName;
	}

	public void setDefineName(String defineName) {
		this.defineName = defineName;
	}

	public boolean getPartOfMD() {
		return partOfMD;
	}

	public void SetPartOfMD(boolean partOfMD) {
		this.partOfMD = partOfMD;
	}
}
