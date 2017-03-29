package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

public class MappedScalarVariable {

	private String define;
	private int valueReference;
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
	
	public void setValueReference(int valueReference)
	{
		this.valueReference = valueReference;
	}
	
	public int getValueReference()
	{
		return this.valueReference;
	}

}
