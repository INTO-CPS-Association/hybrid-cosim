package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

public class Conversions {
	public static String fmiTypeToCppType(SVType t) throws InvalidConversionException {
		switch (t) {
		case Real:
			return "double";
		case Integer:
			return "int";
		case Boolean:
			return "bool";
		case String:
			return "string";
		default:
			throw new InvalidConversionException("The value type: " + t + " is invalid.");
		}
	}
	
	public static SVVariability fmiTypeToVariability(SVType t) throws InvalidConversionException{
		switch (t) {
		case Real:
			return SVVariability.continuous;
		case Integer:
		case Boolean:
		case String:
			return SVVariability.discrete;
		default:
			throw new InvalidConversionException("The value type: " + t + " is invalid.");
		}
	}

	public static String fmiTypeToCppTypeName(SVType t) throws InvalidConversionException {
		switch (t) {
		case Real:
			return "Double";
		case Integer:
			return "Integer";
		case Boolean:
			return "Bool";
		case String:
			return "String";
		default:
			throw new InvalidConversionException("The value type: " + t + " is invalid.");
		}
	}

	public static String fmiTypeToCppDefaultValue(SVType t) throws InvalidConversionException {
		switch (t) {
		case Real:
			return "0.0";
		case Integer:
			return "0";
		case Boolean:
			return "false";
		case String:
			return "\"\"";
		default:
			throw new InvalidConversionException("The value type: " + t + " is invalid.");
		}
	}

}
