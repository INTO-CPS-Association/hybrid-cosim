package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

import javax.management.InvalidAttributeValueException;
import javax.naming.directory.InvalidAttributeIdentifierException;

public class Conversions {
	public static String fmiTypeToCppType(SVType t) throws InvalidConversionException {
		switch (t) {
		case Real:
			return "double";
		case Int:
			return "int";
		case Bool:
			return "bool";
		case String:
			return "String";
		default:
			throw new InvalidConversionException("The value type: " + t + " is invalid.");
		}
	}

	public static String fmiTypeToCppTypeName(SVType t) throws InvalidConversionException {
		switch (t) {
		case Real:
			return "Double";
		case Int:
			return "Integer";
		case Bool:
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
		case Int:
			return "0";
		case Bool:
			return "false";
		case String:
			return "\"\"";
		default:
			throw new InvalidConversionException("The value type: " + t + " is invalid.");
		}
	}
	
	
}
