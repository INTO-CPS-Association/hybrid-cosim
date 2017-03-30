package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation;

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVType;
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVVariability;
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.exceptions.InvalidConversionException;

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
	
	public static String fmiTypeToCppTypeCapitalized(SVType t) throws InvalidConversionException
	{
		String converted = fmiTypeToCppType(t);
		return converted.substring(0,1).toUpperCase()+ converted.substring(1);
	}

	public static SVVariability fmiTypeToFmiVariability(SVType t) throws InvalidConversionException {
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

	public static SVType typeDecider(SVType t1, SVType t2) throws InvalidConversionException {
		switch (t1) {
		case Real:
			switch (t2) {
			case Real:
			case Integer:
				return SVType.Real;
			default:
				throw new InvalidConversionException(
						"The type: " + t1.name() + " is unmergable with " + t2.name() + ".");
			}
		case Integer:
			switch (t2) {
			case Real:
				return SVType.Real;
			case Integer:
				return SVType.Integer;
			default:
				throw new InvalidConversionException(
						"The type: " + t1.name() + " is unmergable with " + t2.name() + ".");
			}
		case Boolean:
			switch (t2) {
			case Boolean:
				return SVType.Boolean;
			default:
				throw new InvalidConversionException(
						"The type: " + t1.name() + " is unmergable with " + t2.name() + ".");
			}
		case String:
			switch (t2) {
			case String:
				return SVType.String;
			default:
				throw new InvalidConversionException(
						"The type: " + t1.name() + " is unmergable with " + t2.name() + ".");
			}
		default:
			throw new InvalidConversionException("The type: " + t1 + " is invalid.");
		}
	}

}
