package be.uantwerpen.ansymo.semanticadaptation.cg.cpp;

public class Conversions {
	public static String fmiTypeToCppType(SVType t)
	{
		switch (t) {
		case Real:
			return "double";
		default:
			return t.toString().toLowerCase();
		}
	}
}
