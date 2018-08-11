package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data;

public class InnerFMUData {
	private String name;
	private String path;
	private String guid;
	public InnerFMUData(String name, String path, String guid)
	{
		this.name = name;
		this.path = path;
		this.guid = guid;
	}
	public String getName() {
		return name;
	}
	public String getPath() {
		return path;
	}
	public String getGuid() {
		return guid;
	}
}
