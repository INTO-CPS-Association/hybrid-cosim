package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

class Utilities {
	def static String getDebug(String functionName){

	return '''
	#ifdef SA_DEBUG
		printf("Invoking «functionName»");
		printf("\n");
	#endif SA_DEBUG	''';
}
def static String getDebug2(String printf){

	return '''
	#ifdef SA_DEBUG
		«printf»
		printf("\n");
	#endif SA_DEBUG	''';
}

}