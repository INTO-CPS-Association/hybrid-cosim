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
	private boolean forceType = false;
	private boolean isExpression = false;

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

	public void setIsExpression(boolean isExpression) {
		this.isExpression = isExpression;
	}

	public boolean getIsExpression() {
		return this.isExpression;
	}

	public SVType getType() throws Exception {
		if (!typeIsSet) {
			throw new Exception("Attempt to retrieve unset type for code: " + code);
		}
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

	public void setConSaSv(SAScalarVariable conSaSv) throws InvalidConversionException {
		ConSaSv = conSaSv;
		if (this.typeIsSet && conSaSv.getType().isPresent()) {
			this.type = Conversions.typeDecider(conSaSv.getType().get(), this.type);
		} else {
			if (conSaSv.getType().isPresent()) {
				this.type = conSaSv.getType().get();
				this.typeIsSet = true;
			}
		}
	}

	public GlobalInOutVariable getConGlobVar() {
		return conGlobVar;
	}

	public void setConGlobVar(GlobalInOutVariable conGlobVar) throws InvalidConversionException {
		this.conGlobVar = conGlobVar;
		if (this.typeIsSet) {
			this.type = Conversions.typeDecider(conGlobVar.type, this.type);
		} else {
			this.type = conGlobVar.type;
			this.typeIsSet = true;
		}
	}

	/*
	 * This method automatically extracts type information
	 */
	public ReturnInformation(ReturnInformation information) throws InvalidConversionException {
		this.conGlobVar = information.conGlobVar;
		if (information.typeIsSet)
			this.setType(information.type);
		this.ConSaSv = information.ConSaSv;

	}

	/*
	 * This method automatically extracts and compares type information
	 */

	public ReturnInformation(ReturnInformation information, ReturnInformation information2) throws Exception {
		if (information.conGlobVar != null) {
			if (information2.conGlobVar != null) {
				if (information.conGlobVar == information2.conGlobVar) {
					this.conGlobVar = information.conGlobVar;
				}
				// In this case they must have the same type otherwise the
				// return value is impossible to typecheck.
				else if (information.conGlobVar.type != information2.conGlobVar.type) {
					throw new Exception("The two connected global variables: " + information.conGlobVar.name + " and "
							+ information2.conGlobVar.name + " have different types");
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

		if (information.forceType && information2.forceType) {
			if (information.getType() != information2.getType()) {
				throw new Exception("Two connected return informations with force types contain different types: "
						+ information.getType() + " and " + information2.getType());
			}
		} else if (information.forceType || information2.forceType) {

			this.forceType = true;
			if (information.forceType)
				this.type = information.type;
			else
				this.type = information2.type;
		}

	}

	public boolean getForceType() {
		return forceType;
	}

	public void setForceType(boolean forceType) {
		this.forceType = forceType;
	}

}
