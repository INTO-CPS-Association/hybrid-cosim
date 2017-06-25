package be.uantwerpen.ansymo.semanticadaptation.generator

class Log {
	var static Log l = null;
	
	var c = 0
	
	protected new() {
		// Exists only to defeat instantiation.
	}

	def protected static Log gl() {
		if (l === null) {
			l = new Log();
		}
		return l;
	}
	
	def static void space(){
		for (var i=0; i<gl().c; i++){
			System.out.print(" ")
		}
	}
	
	def static void println(String msg){
		for(line : msg.split('\n')){
			space()
			System.out.println(line)
		}
	}
	
	def static void push(String msg){
		space()
		System.out.print(">")
		System.out.println(msg)
		gl().c++
	}
	
	def static void pop(String msg){
		gl().c--
		space()
		System.out.print("<")
		System.out.println(msg)
	}
	
}
