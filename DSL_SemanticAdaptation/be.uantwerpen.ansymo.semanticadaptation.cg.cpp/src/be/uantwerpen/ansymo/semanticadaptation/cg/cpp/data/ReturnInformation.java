package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data;

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.exceptions.InvalidConversionException;
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation.Conversions;

public class ReturnInformation {

	private SVType type;
	private boolean typeIsSet;
	private Object value;
	private String code = "";
	private SAScalarVariable ConSaSv;
	private GlobalInOutVariable conGlobVar;

	public ReturnInformation() {
		// TODO Auto-generated constructor stub
	}

	public void appendCode(String code) {
		this.code += code;
	}

	public String getCode() {
		return code;
	}

	public void setCode(String code) {
		this.code = code;
	}

	public SVType getType() {
		return type;
	}

	public void setType(SVType type) throws InvalidConversionException {
		if (this.typeIsSet) {
			this.type = Conversions.typeDecider(this.type, type);
		} else {
			this.type = type;
			this.typeIsSet = true;
		}
	}

	public Object getValue() {
		return value;
	}

	public void setValue(Object value) {
		this.value = value;
	}

	public boolean isTypeIsSet() {
		return typeIsSet;
	}

	public SAScalarVariable getConSaSv() {
		return ConSaSv;
	}

	public void setConSaSv(SAScalarVariable conSaSv) {
		ConSaSv = conSaSv;
	}

	public GlobalInOutVariable getConGlobVar() {
		return conGlobVar;
	}

	public void setConGlobVar(GlobalInOutVariable conGlobVar) throws InvalidConversionException {
		this.conGlobVar = conGlobVar;
		if (this.typeIsSet) {
			this.type = Conversions.typeDecider(conGlobVar.getType(), this.type);
		}
		else
		{
			this.type = conGlobVar.getType();
			this.typeIsSet = true;
		}
	}

	/*
	 * This method automatically extracts information that should be passed on
	 */
	public ReturnInformation(ReturnInformation information) throws InvalidConversionException {

		this.conGlobVar = information.conGlobVar;
		if (information.typeIsSet)
			this.setType(information.type);
		this.ConSaSv = information.ConSaSv;

	}

	public ReturnInformation(ReturnInformation information, ReturnInformation information2) throws Exception {
		if (information.conGlobVar != null) {
			if (information2.conGlobVar != null) {
				if (information.conGlobVar == information2.conGlobVar) {
					this.conGlobVar = information.conGlobVar;
				}
				// In this case they must have the same type otherwise the
				// return value is impossible to typecheck.
				else if (information.conGlobVar.getType() != information2.conGlobVar.getType()) {
					throw new Exception("The two connected global variables: " + information.conGlobVar.getName()
							+ " and " + information2.conGlobVar.getName() + " have different types");
				}

			} else {
				this.conGlobVar = information.conGlobVar;
			}
		} else {
			if (information2.conGlobVar != null) {
				this.conGlobVar = information2.conGlobVar;
			}
		}

		if (information.typeIsSet) {
			if (information2.typeIsSet == false) {
				this.setType(information.getType());
			} else {
				if (information.getType() != information2.getType()) {
					this.type = Conversions.typeDecider(information.getType(), information2.getType());
				} else {
					this.setType(information.getType());
				}
			}
		} else {
			if (information2.typeIsSet) {
				this.setType(information2.getType());
			}
		}

		if (information.ConSaSv != null) {
			if (information2.ConSaSv != null) {
				if (information.ConSaSv != information2.ConSaSv) {
					throw new Exception(
							"Two connected return informations contain different ConSaSv have the wrong type: "
									+ information.ConSaSv.getName() + " and " + information2.ConSaSv.getName());
				} else {
					this.setConSaSv(information.ConSaSv);
				}
			} else {
				this.setConSaSv(information.ConSaSv);
			}
		} else {
			if (information2.ConSaSv != null) {
				this.setConSaSv(information2.ConSaSv);
			}
		}

	}

}
