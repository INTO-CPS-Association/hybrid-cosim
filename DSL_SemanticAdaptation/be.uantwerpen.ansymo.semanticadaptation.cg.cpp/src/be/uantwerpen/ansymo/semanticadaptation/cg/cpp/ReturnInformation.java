package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

public class ReturnInformation {

	private ScalarVariable sv;
	private SVType type;
	private String code;
	
	
	public ReturnInformation() {
		// TODO Auto-generated constructor stub
	}


	public String getCode() {
		return code;
	}


	public void setCode(String code) {
		this.code = code;
	}


	public ScalarVariable getSv() {
		return sv;
	}


	public void setSv(ScalarVariable sv) {
		this.sv = sv;
	}


	public SVType getType() {
		return type;
	}


	public void setType(SVType type) {
		this.type = type;
	}

}
