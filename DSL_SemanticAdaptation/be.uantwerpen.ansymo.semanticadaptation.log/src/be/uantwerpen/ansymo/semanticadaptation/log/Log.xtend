package be.uantwerpen.ansymo.semanticadaptation.log

import org.apache.log4j.ConsoleAppender
import org.apache.log4j.Level
import org.apache.log4j.LogManager
import org.apache.log4j.Logger
import org.apache.log4j.PatternLayout

class Log {
	var static Log l = null;
	
	var c = 0
	
	private static Logger logger;
	
	protected new() {
		LogManager.resetConfiguration();
		val console = new ConsoleAppender(); // create appender
		// configure the appender
		val PATTERN = "%d [%p] %m%n";
		console.setLayout(new PatternLayout(PATTERN));
		console.setThreshold(Level.DEBUG);
		console.activateOptions();
		// add appender to any Logger (here is root)
		Logger.getRootLogger().addAppender(console);
		
		logger = Logger.getLogger("L")
		logger.info("Logger initialized.")
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
