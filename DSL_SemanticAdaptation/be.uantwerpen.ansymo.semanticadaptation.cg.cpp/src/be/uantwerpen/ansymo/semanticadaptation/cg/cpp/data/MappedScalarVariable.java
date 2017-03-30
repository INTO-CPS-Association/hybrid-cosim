package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data;

public class MappedScalarVariable {

	private String define;
	private ScalarVariable mappedSV;
	public MappedScalarVariable(ScalarVariable sv) {
		this.mappedSV = sv;
	}
	
	public ScalarVariable getMappedSv()
	{
		return this.mappedSV;
	}
	
	public void setDefine(String define)
	{
		this.define = define;
	}
	
	public String getDefine()
	{
		return this.define;
	}

	public String getValueReference()
	{
		return this.mappedSV.getValueReference();
	}

}
