package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

class Utilities {
	def static String getDebug(String functionName){

	return '''
	#ifdef SA_DEBUG
		printf("Invoking «functionName»");
	#endif SA_DEBUG	''';
}
}