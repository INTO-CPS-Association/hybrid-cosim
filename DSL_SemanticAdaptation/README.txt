# Checkout

```bash
git clone <repo-url>
git submodule update --init --recursive
```

# Development environmant:

Install instructions:
- Download Eclipse NEON (64 bits) installer.
- Run it, and select "Eclipse DSL Tools" environment.
or if you already have Eclipse NEON then just install the xText plugins
- repo http://download.eclipse.org/modeling/tmf/xtext/updates/composite/releases/
-  plugins `Xtend IDE` and `Xtend Complete SDK`

# Compilation

## Using Eclipse
Generation and Compilation
- Import all projects in this folder.
- Right click in be.uantwerpen.ansymo.semanticadaptation/src/be/uantwerpen/ansymo/semanticadaptation/SemanticAdaptation.xtext   and select "run as -> generate xtext artifacts"
- Check that the console log is similar to the one in File "first_generation_sucessful_log.txt".

## Using Maven
- In CONSOLE run "mvn package" in DSL_SemanticAdaptation
- In eclipse choose import -> Maven -> Existing Maven Projects and choose the LEAF nodes
- Might be necessary to right click on a project -> Maven -> Update project

```bash
# Perform a clean build
mvn clean package
```

### Other tasks:
	Run the tests: right-click be.uantwerpen.ansymo.semanticadaptation.tests/src/be/uantwerpen/ansymo/semanticadaptation/tests/SemanticAdaptationParsingTest.xtend -> run as -> J-Unit test
	
	Run the plugin: After building everything, right-click /be.uantwerpen.ansymo.semanticadaptation -> run as -> eclipse application
