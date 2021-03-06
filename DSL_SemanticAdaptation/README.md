# Introduction

Please read the [paper](http://msdl.cs.mcgill.ca/people/claudio/pub/Gomes2018a.pdf) ([bib](http://msdl.cs.mcgill.ca/people/claudio/pub/Gomes2018a.bib)).

# Checkout

```bash
git clone <repo-url>
git submodule update --init --recursive
```

# Development environment:

Install instructions:
- Download Eclipse Photon (64 bits) installer.
- Run it, and select "Eclipse DSL Tools" environment.
or if you already have Eclipse DSL Tools, then just install the xText plugins as follows:
	http://download.eclipse.org/modeling/tmf/xtext/updates/composite/releases/
		select plugins `Xtend IDE` and `Xtend Complete SDK`, and install

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
# Perform a clean build, and run tests
mvn clean install
```

### Other tasks:
	Run the plugin:
		After building everything, right-click /be.uantwerpen.ansymo.semanticadaptation -> run as -> eclipse application
