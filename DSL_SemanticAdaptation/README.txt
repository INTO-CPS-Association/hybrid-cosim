Installation Instructions:
- Download Eclipse NEON (64 bits) installer.
- Run it, and select "Eclipse DSL Tools" environment.
or if you already have Eclipse DSL Tools, then just install the xText plugins as follows:
	http://download.eclipse.org/modeling/tmf/xtext/updates/composite/releases/
		select plugins `Xtend IDE` and `Xtend Complete SDK`, and install

- In CONSOLE run "mvn package" in DSL_SemanticAdaptation
- In eclipse choose import -> Maven -> Existing Maven Projects and choose the LEAF nodes
- Might be necessary to right click on a project -> Maven -> Update project

Build Instructions:
mvn clean
mvn package

Other tasks:
	Run the plugin: 
		After building everything, right-click /be.uantwerpen.ansymo.semanticadaptation -> run as -> eclipse application
