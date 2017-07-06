package be.uantwerpen.ansymo.semanticadaptation.generator

import org.apache.log4j.Logger

class Log {
	var static Log l = null;
	
	var c = 0
	
	private static final Logger logger = Logger.getLogger("");
	
	protected new() {
		// Exists only to defeat instantiation.
	}

	def protected static Log gl() {
		if (l === null) {
			l = new Log();
		}
		return l;
	}
	
	def static String space(int indent){
		var res = ""
		for(var i = 0; i<indent; i++){
			res += " "
		}
		return res;
	}

	def static void println(String msg){
		val space = space(gl().c)
		for(line : msg.split('\n')){
			logger.info(space + line)
		}
	}
	
	def static void push(String msg){
		logger.info(space(gl().c) + ">" + msg)
		gl().c++
	}
	
	def static void pop(String msg){
		gl().c--
		logger.info(space(gl().c) + "<" + msg)
	}
	
}
