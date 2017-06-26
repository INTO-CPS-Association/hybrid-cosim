package be.uantwerpen.ansymo.semanticadaptation.valueconverter

import org.eclipse.xtext.conversion.impl.AbstractDeclarativeValueConverterService
import org.eclipse.xtext.conversion.ValueConverter
import org.eclipse.xtext.conversion.impl.AbstractLexerBasedConverter
import org.eclipse.xtext.nodemodel.INode

class SemanticAdaptationValueConverters extends AbstractDeclarativeValueConverterService {
	@ValueConverter(rule = "PREV")
	def PREV() {
		return new AbstractLexerBasedConverter<Integer> {    
		    override toValue(String string, INode node) {
				return -1
		    }
		};
	}
	
	@ValueConverter(rule = "NOW")
	def NOW() {
		return new AbstractLexerBasedConverter<Integer> {    
		    override toValue(String string, INode node) {
				return 0
		    }
		};
	}
	
	@ValueConverter(rule = "REALTYPE")
	def REALTYPE() {
		return new AbstractLexerBasedConverter<Float> {    
		    override toValue(String string, INode node) {
				return Float.valueOf(string)
		    }
		};
	}
	
	@ValueConverter(rule = "STRING")
	def STRING() {
		return new AbstractLexerBasedConverter<String> {    
		    override toValue(String string, INode node) {
				return string
		    }
		};
	}
	
	/*@ValueConverter(rule = "AtomicUnity")
	def AtomicUnity() {
		return new AbstractLexerBasedConverter<Integer> {    
		    override toValue(String string, INode node) {
		    	println(string)
				if (string.equals("0")) {
					return 1
				} else {
					return Integer.valueOf(string)
				}
		    }
		};
	}*/
}