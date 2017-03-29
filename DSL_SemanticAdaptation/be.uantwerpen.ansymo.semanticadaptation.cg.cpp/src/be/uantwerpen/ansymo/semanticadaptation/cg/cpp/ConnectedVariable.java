package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

public class ConnectedVariable {

	private SVCausality causality;
	private SVType type;
	private String name;
	private String owner;
	private InputOutputType inOut;
	private String value;
	private ConnectedVariable conVar;
	private MappedScalarVariable mapSV;
	
	public ConnectedVariable() {
		
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

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getOwner() {
		return owner;
	}

	public void setOwner(String owner) {
		this.owner = owner;
	}

	public InputOutputType getInOut() {
		return inOut;
	}

	public void setInOut(InputOutputType inOut) {
		this.inOut = inOut;
	}

	public String getValue() {
		return value;
	}

	public void setValue(String value) {
		this.value = value;
	}

	public ConnectedVariable getConVar() {
		return conVar;
	}

	public void setConVar(ConnectedVariable conVar) {
		this.conVar = conVar;
	}

	public MappedScalarVariable getMapSV() {
		return mapSV;
	}

	public void setMapSV(MappedScalarVariable mapSV) {
		this.mapSV = mapSV;
	}

}
