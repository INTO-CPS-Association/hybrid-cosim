Installation Instructions:
- Download Eclipse NEON (64 bits) installer.
- Run it, and select "Eclipse DSL Tools" environment.
or if you allready have Eclipse NEON then just install the xText plugins
- repo http://download.eclipse.org/modeling/tmf/xtext/updates/composite/releases/
-  plugins `Xtend IDE` and `Xtend Complete SDK`

Generationa and Compilation
- Import all projects in this folder.
- Right click in be.uantwerpen.ansymo.semanticadaptation/src/be/uantwerpen/ansymo/semanticadaptation/SemanticAdaptation.xtext   and select "run as -> generate xtext artifacts"
- Check that the console log is similar to the one in File "first_generation_sucessful_log.txt".


Other tasks:
	Run the tests: right-click be.uantwerpen.ansymo.semanticadaptation.tests/src/be/uantwerpen/ansymo/semanticadaptation/tests/SemanticAdaptationParsingTest.xtend -> run as -> J-Unit test
	
	Run the plugin: right-click /be.uantwerpen.ansymo.semanticadaptation -> run as -> eclipse application
