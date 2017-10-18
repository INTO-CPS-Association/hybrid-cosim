package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data;

public class InnerFMUData {
	private String name;
	private String typeName;
	private String guid;
	public InnerFMUData(String name, String typeName, String guid)
	{
		this.name = name;
		this.typeName = typeName;
		this.guid = guid;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getTypeName() {
		return typeName;
	}
	public void setTypeName(String typeName) {
		this.typeName = typeName;
	}
	public String getGuid() {
		return guid;
	}
	public void setGuid(String guid) {
		this.guid = guid;
	}
}
