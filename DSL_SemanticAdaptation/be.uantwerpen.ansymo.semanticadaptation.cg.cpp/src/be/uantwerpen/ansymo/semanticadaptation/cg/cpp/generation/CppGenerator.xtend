package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.GlobalInOutVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.IORuleType
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.InOutRulesBlockResult
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.InnerFMUData
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.MappedScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SAScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVCausality
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVType
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.exceptions.IncorrectAmountOfElementsException
import be.uantwerpen.ansymo.semanticadaptation.generator.SemanticAdaptationGenerator
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Adaptation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ControlRuleBlock
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Declaration
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InOutRules
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InnerFMU
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.MooreOrMealy
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ParamDeclarations
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.ReactiveOrDelayed
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import java.io.File
import java.util.ArrayList
import java.util.Collection
import java.util.LinkedHashMap
import java.util.List
import org.eclipse.emf.common.util.EList
import org.eclipse.emf.ecore.resource.Resource
import org.eclipse.xtext.generator.IFileSystemAccess2
import be.uantwerpen.ansymo.semanticadaptation.log.Log
import org.eclipse.emf.common.util.URI
import org.eclipse.emf.common.CommonPlugin

class CppGenerator {
	private var IFileSystemAccess2 fsa;
	private List<File> resourcePaths = newArrayList();

	def void doGenerate(Resource resource, IFileSystemAccess2 fsa) {
		Log.push("CppGenerator.doGenerate")
		val adaptationFolderURI = resource.URI.trimSegments(1)
		Log.println("Adaptation folder URI: " + adaptationFolderURI)
		doGenerate(resource, fsa, adaptationFolderURI)
		Log.pop("CppGenerator.doGenerate")
	}
	
	def void doGenerate(Resource resource, IFileSystemAccess2 fsa, URI adaptationFolderURI) {
		Log.push("CppGenerator.doGenerate " + adaptationFolderURI)
		this.fsa = fsa;
		for (SemanticAdaptation type : resource.allContents.toIterable.filter(SemanticAdaptation)) {
			type.compile(adaptationFolderURI);
		}
		Log.pop("CppGenerator.doGenerate"  + adaptationFolderURI)
	}
	

	// TODO: Verify adaptation.name is not a C++ keyword
	def void compile(SemanticAdaptation adaptation, URI adaptationFolderURI) {
		for (Adaptation adap : adaptation.elements.filter(Adaptation)) {
			// Value used for scoping variables in the .sa file
			val adapInteralRefName = adap.name;

			// The CPP class name
			val adapClassName = adap.name.toFirstUpper;

			// This is the external name used in the model description file for the semantic adaptation FMU
			val adapExternalName = adap.name;

   
			// List of inner FMUs
			var ArrayList<InnerFMUData> innerFMUsData = newArrayList();
			val innerFmus = adap.inner.eAllContents.toList.filter(InnerFMU);
   			
			if (innerFmus.isEmpty) {
				throw new IncorrectAmountOfElementsException("The adaptation does not contain any InnerFMUs.")
			}
			
			if (innerFmus.size > 1) {
				throw new IncorrectAmountOfElementsException("Only one InnerFmu is supported.")
			}
			
			/*
			 * This map will contain scalar variables from the FMUs defined in InnerFMU.
			 * The structure is fmuName -> (SVName -> mappedSV) where SVName = mappedSV.name for easy lookup.
			 * The mappedSV contains the original scalar variable and extra data such as define name.
			 */
			var LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mappedScalarVariables = newLinkedHashMap();
			
			/*
			 * Loading the FMU defined in InnerFMU, the related model description file and its scalar variables.
			 */
			// TODO: Add support for multiple inner fmus. Only partially supported
			var ModelDescription md;
			for (fmu : adap.inner.eAllContents.toList.filter(InnerFMU)) {
				Log.push("Loading fmu " + fmu.path)
				val fmuFile = getFMUFile(fmu.path, adaptationFolderURI)
				this.resourcePaths.add(fmuFile);
				md = new ModelDescription(fmu.name, fmu.type.name, fmuFile);
	
				innerFMUsData.add(new InnerFMUData(fmu.name, fmu.path, md.guid));
				val LinkedHashMap<String, MappedScalarVariable> mSV = newLinkedHashMap();
	
				Log.push("Loading fmu variables")
				for (sv : md.sv.values) {
					// Only declared ports are considered.
					val svInPort = fmu.inports.findFirst[Port p | p.name==sv.name || BuildUtilities.stripDelimiters(p.alias) == sv.name]
					val svOutPort = fmu.outports.findFirst[Port p | p.name==sv.name || BuildUtilities.stripDelimiters(p.alias) == sv.name]
					if (svInPort !== null || svOutPort !== null){
						val svPort = if (svInPort !== null) svInPort else svOutPort
						val svPortRef = svPort.name;
						var mappedSv = new MappedScalarVariable(sv);
						mappedSv.define = (mappedSv.mappedSv.owner + svPortRef).toUpperCase;
						mSV.put(mappedSv.mappedSv.name, mappedSv);
						Log.println("Variable " + sv.name + " declared.")
					} else {
						Log.println("Variable " + sv.name + " undeclared.")
					}
				}
				mappedScalarVariables.put(fmu.name, mSV);
				Log.pop("Loading fmu variables")
									
				mappedScalarVariables.put(fmu.name, mSV);
			}

			// C++ Defines for accessing FMU scalar variables.
			val String fmusDefines = calcDefines(mappedScalarVariables);

			/*
			 * This map contains all the ScalarVariables for the semantic adaptation. 
			 * Some of them are not populated yet, but they will be during the compilation of the in and out rule blocks. 
			 */
			var LinkedHashMap<String, SAScalarVariable> SASVs = calcSASVsFromInportsOutports(adapInteralRefName,
				adap.inports, adap.outports, mappedScalarVariables)

			// C++ defines for accessing semantic adaptation scalar variables 
			val String SADefines = calcSADefines(SASVs.values);

			// Compile Params
			var LinkedHashMap<String, GlobalInOutVariable> params = newLinkedHashMap;
			val String paramsConstructorSource = compileParams(params, adap.params);

			// Handles cases like this: output ports tau <- loop_sa.tau		
			var List<Port> outPortsWithSrcDep = newArrayList();
			if (adap.outports !== null) {
				outPortsWithSrcDep = adap.outports.filter[x|x.sourcedependency !== null].toList;
			}

			var List<Port> inPortsWithSrcDep = newArrayList();
			if (adap.inports !== null) {
				inPortsWithSrcDep = adap.inports.filter[x|x.targetdependency !== null].toList;
			}

			// The three rule blocks
			val inRuleBlock = adap.in;
			val outRuleBlock = adap.out;
			val crtlRuleBlock = adap.control;

			// Get the control vars, in vars, and out vars				
			var inVars = if(inRuleBlock !== null) compileRuleBlockVars(inRuleBlock.globalInVars, params);
			var outVars = if(outRuleBlock !== null) compileRuleBlockVars(outRuleBlock.globalOutVars, params);
			val crtlVars = if(crtlRuleBlock !== null) compileRuleBlockVars(crtlRuleBlock.globalCtrlVars, params);
			/*
			 * Support for source dependency: output ports tau <- loop_sa.tau
			 * Only carried out for outVars.
			 * TODO: Do for inVars
			 */
			for (Port port : outPortsWithSrcDep) {
				val name = '''stored_«port.sourcedependency.owner.name»_«port.sourcedependency.port.name»''';
				val type = mappedScalarVariables.get(port.sourcedependency.owner.name).get(
					port.sourcedependency.port.name).mappedSv.type;
				val globVar = new GlobalInOutVariable(name, type);
				val sourceDepType = mappedScalarVariables.get(port.sourcedependency.owner.name).get(
					port.sourcedependency.port.name).mappedSv.type;
				val constructorInit = '''this->internalState.«name» = «Conversions.fmiTypeToCppDefaultValue(sourceDepType)»;'''
				if (outVars !== null) {
					outVars.value.put(name, globVar);
					outVars = outVars.key.concat(constructorInit) -> outVars.value;
				} else {
					val LinkedHashMap<String, GlobalInOutVariable> gVars = newLinkedHashMap();
					gVars.put(name, globVar)
					outVars = constructorInit -> gVars;
				}
			}

			for (Port port : inPortsWithSrcDep) {
				val dependency = port.targetdependency;
				val name = '''stored_«dependency.owner.name»_«dependency.port.name»'''
				val type = mappedScalarVariables.get(dependency.owner.name).get(dependency.port.name).mappedSv.type;
				val globVar = new GlobalInOutVariable(name, type);
				val constructorInit = '''this->internalState.«name» = «Conversions.fmiTypeToCppDefaultValue(type)»;''';
				if (inVars !== null) {
					inVars.value.put(name, globVar);
					inVars = inVars.key.concat("\n" + constructorInit) -> inVars.value;
				} else {
					val LinkedHashMap<String, GlobalInOutVariable> gVars = newLinkedHashMap();
					gVars.put(name, globVar);
					inVars = constructorInit -> gVars;
				}
			}

			// Compile the in rules
			val inRules = if(adap.in !== null) adap.in as InOutRules else null;
			val inRuleResult = compileInOutRuleBlocks(IORuleType.Input, inRules, adapClassName, adapInteralRefName,
				mappedScalarVariables, SASVs, params, if(inVars !== null) inVars.value else null,
				if(outVars !== null) outVars.value else null, if(crtlVars !== null) crtlVars.value else null,
				inPortsWithSrcDep);
   
								  
																										 
   
						   
																											 
																						 
															 
																							 
																											

								  
																										 
   
				// Compile the out rules
				val outRules = if(adap.out !== null) adap.out as InOutRules else null;
				val outRuleResult = compileInOutRuleBlocks(IORuleType.Output, outRules, adapClassName,
					adapInteralRefName, mappedScalarVariables, SASVs, params,
					if(inVars !== null) inVars.value else null, if(outVars !== null) outVars.value else null,
					if(crtlVars !== null) crtlVars.value else null, outPortsWithSrcDep);

				// Compile the Control Rules. These might use the out vars, so pass these along.
				val crtlRules = if(adap.control !== null) adap.control else null;
	  
																						 
				val crtlRuleResult = compileControlRuleBlock(crtlRules, adapClassName, adapInteralRefName,
																						 
				  
				  
			
							
					mappedScalarVariables, SASVs, params, if(inVars !== null) inVars.value else null,
											 
					if(outVars !== null) outVars.value else null, if(crtlVars !== null) crtlVars.value else null);
				 
					  
													 
													  
	 
	 

				/*
				 * Compile the constructor, destructor and initialize functions
				 */
				val String deAndConstructorAndInitializeSource = compileDeAndConstructorAndInitialize(
					adapClassName,
					innerFMUsData,
					md.guid,
					paramsConstructorSource,
					if(inVars !== null) inVars.key else "",
					if(outVars !== null) outVars.key else "",
					if(crtlVars !== null) crtlVars.key else "",
					adap.machine,
					adap.reactiveness,
					inRules !== null || inPortsWithSrcDep.length > 0,
					outRules !== null || outPortsWithSrcDep.length > 0
				);

				/*
				 * Compile getRuleThis function
				 */
																				 
				val String getRuleThisSource = compileGetRuleThis(adapClassName);
																				 

				/*
				 * The in and out rules have populated the semantic adaptation scalar variables we can generate the getFmiValue* and setFmiValue functions.
				 */
				val String getFuncsSource = compileGetFmiValueFunctions(adapClassName, SASVs);
				val String setFuncsSource = compileSetFmiValueFunctions(adapClassName, SASVs);

				// Compile the state functions
				val Pair<String,String> stateFunctions = compileStateFunctions(adapClassName);
								  
				  
										
					  
				   
				   
							  
							   
								
						
	 
														

				// Compile the source file
				val String sourceInclude = '''#include "«adapClassName».h"''';
				val sourceFile = compileSource(
					sourceInclude,
					deAndConstructorAndInitializeSource,
					getRuleThisSource,
					getFuncsSource,
					setFuncsSource,
					inRuleResult.generatedCpp,
					outRuleResult.generatedCpp,
					crtlRuleResult.generatedCpp,
					stateFunctions.value
				);
				fsa.generateFile(adapClassName + ".cpp", sourceFile);

				// Merge the global variables for use in compiling the header file.
				// TODO: Check for duplicates
				var LinkedHashMap<String, GlobalInOutVariable> allGVars = newLinkedHashMap();
				allGVars.putAll(params);
				if (inVars !== null)
					allGVars.putAll(inVars.value);
				if (outVars !== null)
									  
					allGVars.putAll(outVars.value);
				if (crtlVars !== null)
					allGVars.putAll(crtlVars.value);
										
					  
	 
													  

				// Compile the header file
				val headerFile = compileHeader(
					adapClassName,
					fmusDefines,
					SADefines,
					inRuleResult.functionSignatures,
					outRuleResult.functionSignatures,
					crtlRuleResult.functionSignatures,
					allGVars,
					innerFMUsData,
					SASVs.values.map[CalcSVar()].toList,
					stateFunctions.key
				);
				fsa.generateFile(adapClassName + ".h", headerFile);

				// Compile the model description file
				val modelDescCreator = new ModelDescriptionCreator(adapExternalName);
				val modelDescription = modelDescCreator.generateModelDescription(SASVs.values);
				fsa.generateFile("modelDescription.xml", modelDescription);
   
																																									  
																																							 

				// Compile the fmu.cpp file
				val fmuCppFile = FmuGenerator.genFmuCppFile(adapClassName);
				fsa.generateFile("Fmu.cpp", fmuCppFile);
				
				fsa.generateFile("CMakeLists.txt",CMakeListsGenerator.generateCMakeLists(adapExternalName))
				fsa.generateFile("msys-toolchain.cmake",CMakeListsGenerator.generateToolChainCmake());

			}
		}
  		
  		def getFMUFile(String fmuUnresolvedPath, URI adaptationFolderURI) {
			var resolvedFolderURI = CommonPlugin.resolve(adaptationFolderURI);
			val fmuCompleteURI = URI.createFileURI(resolvedFolderURI.toFileString + File.separatorChar + fmuUnresolvedPath.replace('\"', ''))
			var fmuPath = fmuCompleteURI.toFileString
			Log.println("Resolved fmu path: " + fmuPath)
			val fmuFile = new File(fmuPath);
			return fmuFile
		}

		def String compileParams(LinkedHashMap<String, GlobalInOutVariable> gVars, EList<ParamDeclarations> params) {
			val paramsConditionSwitch = new ParamConditionSwitch(gVars);
			var String paramsConstructorSource = "";
			for (paramDecl : params) {
				val doSwitchRes = paramsConditionSwitch.doSwitch(paramDecl);
				paramsConstructorSource += doSwitchRes.code;
			}
			return paramsConstructorSource;
		}
								 
  

		def calcSADefines(Collection<SAScalarVariable> variables) {
			var ArrayList<String> defines = newArrayList();

			for (SASV : variables) {
				defines.add("#define " + SASV.defineName + " " + SASV.valueReference);
			}

			return defines.join("\n");
		}

		def calcDefines(LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> map) {
			var ArrayList<String> defines = newArrayList();

			for (fmuEntries : map.entrySet) {
				for (MappedScalarVariable mSV : fmuEntries.value.values) {
					defines.add("#define " + mSV.define.replace('(','_').replace(')','_') + " " + mSV.valueReference);
				}
			}

			return defines.join("\n");
		}

											
  

		def Pair<String,String> compileStateFunctions(String saName)
  
		
	 
									 
											   
												   
	 
	 
	 
												
   
										  
							
			
   
  
														  
   
												
   
		
	 
									 
											   
												   
	 
	 
	 
												
   
										  
							
			
   
  
														  
   
												
   
  
														   
		{
			return
			'''
			fmi2FMUstate getInternalFMUState();
			void setInternalFMUState(fmi2FMUstate state);
			void freeInternalFMUState(fmi2FMUstate state);			
			'''
			-> 
			'''
			fmi2FMUstate «saName»::getInternalFMUState()
   
						
			{
				InternalState* s = new InternalState();
				*s = this->internalState;
				return s;
			}
					
	
					
	
				   
	
					   
	
					
	
					  
			
			void «saName»::setInternalFMUState(fmi2FMUstate state)
			{
				this->internalState = *(InternalState*)state;
			}
			
			void «saName»::freeInternalFMUState(fmi2FMUstate state)
			{
				delete (InternalState*)state;
			}''';			
		}

   
		// Compiles the final source file
									  
	
		def String compileSource(String include, String constructor, String getRuleThis, String getFunctions,
																						   
																						   
			String setFunctions, String inFunctions, String outFunctions, String controlFunction, String stateFunctions) {
																						   
															
			return '''
				«include»
											   
   
								   
						
					 
					
	
						
						 
				
				namespace adaptation 
				{
					«constructor»
					
					«getRuleThis»
					
					«getFunctions»
					
					«setFunctions»
					
					«inFunctions»
					
					«controlFunction»
					
					«outFunctions»
					
					«stateFunctions»
				
				}
				
			'''
	

   
	
								   
																									   
																												 
			 
			   
	
						 
	 
					
	 
					
	 
					 
	 
					 
	 
					
	 
						
	 
					 
	 
					   
	
	 
	
	  
		}

		/*
		 * Compiles the header file split into two: The first part contains the includes and using namespace definitions and start the ,
		 * the second part contains the class
		 */
		def String compileHeader(String adapClassName, String fmusDefines, String SADefines,
			List<String> inRulesFuncSig, List<String> outRulesFuncSig, List<String> crtlRulesFuncSig,
			LinkedHashMap<String, GlobalInOutVariable> globalVariables, ArrayList<InnerFMUData> fmus,
			Collection<ScalarVariable> sVars, String stateFunctions) {
			return '''

	
				
					#ifndef SRC_«adapClassName.toUpperCase»_H
					#define SRC_«adapClassName.toUpperCase»_H
			   
				
	
   
													 
		
													   
									  
														
								 
																																												 
				
					#include "SemanticAdaptation.h"
					#include "HyfMath.h"
					#include <memory>
					#include "Fmu.h"
					
					using namespace std;
					using namespace fmi2;
					
					namespace adaptation
					{
			 
																																																																		  
						 
									
	   
																					   
																						
																						   
																						   
						
						«fmusDefines»
						
						«SADefines»
					
						class «adapClassName» : public SemanticAdaptation<«adapClassName»>, public enable_shared_from_this<«adapClassName»>
						{
							public:
								«adapClassName»(shared_ptr<std::string> fmiInstanceName, shared_ptr<string> resourceLocation, const fmi2CallbackFunctions* functions);
								void initialize(bool loggingOn);
								virtual ~«adapClassName»();
								
								void setFmiValue(fmi2ValueReference id, int value);
								void setFmiValue(fmi2ValueReference id, bool value);
								void setFmiValue(fmi2ValueReference id, double value);
								void setFmiValue(fmi2ValueReference id, string value);
					
													
	   
													 
	   
						 
											  
				 
							
								int getFmiValueInteger(fmi2ValueReference id);
								bool getFmiValueBoolean(fmi2ValueReference id);
								double getFmiValueReal(fmi2ValueReference id);
								string getFmiValueString(fmi2ValueReference id);
								
				  
				  
								
				  
				  
								
							protected:
								«stateFunctions»
								
							private:
								
								«adapClassName»* getRuleThis();
								
								/*in rules*/
								«inRulesFuncSig.map[x | x+";"].join("\n")»
								
								/*out rules*/
								«outRulesFuncSig.map[x | x+";"].join("\n")»
								
								«crtlRulesFuncSig.map[x | x+";"].join("\n")»
								
								«FOR fmu : fmus»
									shared_ptr<FmuComponent> «fmu.name»;
								«ENDFOR»
								
								struct InternalState {
									«FOR sv : sVars»
										«Conversions.fmiTypeToCppType(sv.type)» «sv.name»;
										«IF sv.causality == SVCausality.input»
											bool isSet«sv.name»;
										«ENDIF»
									«ENDFOR»
									
									«FOR v : globalVariables.entrySet»
										«Conversions.fmiTypeToCppType(v.value.type)» «v.key»;
									«ENDFOR»
								};
								
								InternalState internalState;
						};
					}
					
					#endif
			''';
		}

		/*
		 * Compiles the source file constructor, destructor and the initialize function
		 */
		def String compileDeAndConstructorAndInitialize(String adapClassName, ArrayList<InnerFMUData> fmus, String guid,
			String paramsCons, String inCons, String outCons, String crtlCons, MooreOrMealy machineType,
			ReactiveOrDelayed reactiveOrDealyed, boolean inputRules, boolean outputRules) {

			var ArrayList<String> initialisations = newArrayList();
			if (reactiveOrDealyed == ReactiveOrDelayed.DELAYED) {
				initialisations.add('''this->reactiveness = ReactiveOrDelayed::Delayed;''');
   

			} else if (reactiveOrDealyed == ReactiveOrDelayed.REACTIVE) {
																										  
												 
				initialisations.add('''this->reactiveness = ReactiveOrDelayed::Reactive;''');
   
					
					
										  
			   
						  
															   
														 
																 
								  
																																													
	
											 
									  
												   
		
   
			
																																							   
																																											   
	   
				  
			  
			   
				
											 
									  
												   
		
   
			
																																							   
																																											   
	   
				  
			  
			   
				
			}

			if (machineType == MooreOrMealy.MOORE) {
				initialisations.add('''this->machineType = MooreOrMealy::Moore;''');
			} else if (machineType == MooreOrMealy.MEALY) {
				initialisations.add('''this->machineType = MooreOrMealy::Mealy;''');
			}
			var pathCount = 1;
			for (fmu : fmus) {
				val pathName = '''path«pathCount»''';
				pathCount++;
				initialisations.add('''
					auto «pathName» = make_shared<string>(*resourceLocation);
					«pathName»->append(string(«fmu.getPath»));
					auto «fmu.name»Fmu = make_shared<fmi2::Fmu>(*«pathName»);
					«fmu.name»Fmu->initialize();
					this->«fmu.name» = «fmu.name»Fmu->instantiate("«fmu.name»",fmi2CoSimulation, "«fmu.guid»", true, loggingOn, shared_from_this());
					
					if(this->«fmu.name»->component == NULL)
						this->lastErrorState = fmi2Fatal;
					this->instances->push_back(this->«fmu.name»);
				''');
			}
			return '''
				«adapClassName»::«adapClassName»(shared_ptr<std::string> fmiInstanceName,shared_ptr<string> resourceLocation, const fmi2CallbackFunctions* functions) : 
				SemanticAdaptation(fmiInstanceName, resourceLocation, «if(inputRules) "createInputRules()" else "NULL"», «if(outputRules) "createOutputRules()" else "NULL"», functions)
				{			
					«paramsCons»
					«inCons»
					«outCons»
					«crtlCons»
				}
				
				void «adapClassName»::initialize(bool loggingOn)
				{
					«initialisations.join("\r\n")»
				}
				
				«adapClassName»::~«adapClassName»()
				{
				}
			''';
		}

		/*
		 * Compiles the source file function getRuleThis
		 */
		def String compileGetRuleThis(String adaptationName) {
			return '''
				«adaptationName»* «adaptationName»::getRuleThis()
				{
					return this;
				}
			'''
		}

		/*
		 * Compiles the source file functions getFmiValue<double, int, string, bool>
		 */
		def String compileGetFmiValueFunctions(String adaptationName,
			LinkedHashMap<String, SAScalarVariable> variables) {
			var ArrayList<String> cpp = newArrayList();
			var List<ScalarVariable> convertedSASVs = variables.values.map[CalcSVar()].toList;
			var convertedSASVsOrdered = convertedSASVs.filter[causality === SVCausality.output].groupBy[type];

			for (SVType type : SVType.values) {
				val functionSignature = '''«Conversions.fmiTypeToCppType(type)» «adaptationName»::getFmiValue«type.toString»(fmi2ValueReference id)''';
				val functionReturn = '''return «Conversions.fmiTypeToCppDefaultValue(type)»''';
				if (convertedSASVsOrdered.containsKey(type)) {
					cpp.add(
						'''
							«functionSignature»
	   
												
				  
							{
								«Utilities.getDebug(functionSignature)»
								switch (id)
								{
									«FOR svInner : convertedSASVsOrdered.get(type)»
										case «variables.get(svInner.name).defineName»:
										{
											return this->internalState.«svInner.name»;
										}
									«ENDFOR»
									default:
									{
										«functionReturn»;
									}
				  
				
		 
							
								}
								
							}
						'''
					);
				} else {
					cpp.add(
						'''
							«functionSignature»
							{
								«Utilities.getDebug(functionSignature)»
								«functionReturn»;
							}
						'''
					);
				}
			}

			return cpp.join("\n");
		}

		/*
		 * Compiles the source file functions setFmiValue<double, int, string, bool>*
		 */
		def String compileSetFmiValueFunctions(String adapClassName,
			LinkedHashMap<String, SAScalarVariable> variables) {
			var ArrayList<String> cpp = newArrayList();
			var List<ScalarVariable> convertedSASVs = variables.values.map[CalcSVar()].filter [
				causality === SVCausality.input
			].toList;
			var convertedSASVsOrdered = convertedSASVs.groupBy[type];

			for (SVType type : SVType.values) {
				val functionSignature = '''void «adapClassName»::setFmiValue(fmi2ValueReference id, «Conversions.fmiTypeToCppType(type)» value)''';
				cpp.add(
					'''
						«functionSignature»
						{
							«Utilities.getDebug2('''printf("«adapClassName»::setFmiValue(%d,?)",id);''')»
							«IF convertedSASVsOrdered.containsKey(type)»
								switch (id)	
									{
										«FOR svInner : convertedSASVsOrdered.get(type)»
											case «variables.get(svInner.name).defineName»:
											{
												this->internalState.«svInner.name» = value;
												this->internalState.isSet«svInner.name» = true;
												break;
											}
										«ENDFOR»
										default:
										{
										}
									}
							«ENDIF»
						}
					'''
				);
	
   

						
			}

			return cpp.join("\n");
		}
	
															 
													  
											 
																					 
								  
		   
														   

		/*
		 * Compiles the source file function executeInternalControlFlow.
		 * Calculates necessary information on function signatures necessary for generation of the header file.
		 */
		def InOutRulesBlockResult compileControlRuleBlock(ControlRuleBlock crtlRuleBlock, String adaptationClassName,
			String adaptationName, LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
			LinkedHashMap<String, SAScalarVariable> SASVs, LinkedHashMap<String, GlobalInOutVariable> params,
			LinkedHashMap<String, GlobalInOutVariable> inVars, LinkedHashMap<String, GlobalInOutVariable> outVars,
			LinkedHashMap<String, GlobalInOutVariable> crtlVars) {
   
			var cpp = "";
   
			val visitor = new ControlConditionSwitch(adaptationClassName, adaptationName, mSVars, SASVs, params, inVars,
																																								  
																																												 
				 
		   
				   
				 
		  
		  
		 
			   
	  
	   
				outVars, crtlVars);
			if (crtlRuleBlock !== null)
				cpp += visitor.doSwitch(crtlRuleBlock).code;
										 
  
				 
		  
		  
		 
			   
	  
	   
	 

			return new InOutRulesBlockResult(cpp, visitor.functionSignatures);
		}

		def String SplitAtSpaceAndRemoveFirst(String content) {
			content.substring(content.indexOf(" ") + 1, content.length);
		}

		def String removeEmptyArgumentParenthesis(String content) {
			return content.substring(0, content.length - 2);
		}
	
																											  
																								   
																								   
																										
														
  
											 
		
		def String removeArgumentParenthesis(String content) {
			val startParen = content.indexOf('(');
							 
											   
			
			return content.substring(0,startParen);
		}

										
  
 
 
 
		/*
		 * Calculates necessary information on global in/out variables
		 */
		def Pair<String, LinkedHashMap<String, GlobalInOutVariable>> compileRuleBlockVars(EList<Declaration> gVars,
			LinkedHashMap<String, GlobalInOutVariable> params) {

			val visitor = new RulesConditionSwitch("", "", "", null, null, params, null, null, null)
	  
														 
	 
	 
	  
			return visitor.getGlobalVars(gVars);
		}

		/*
		 * Compiles the source file functions <in/out>_rule_<condition, body, flush>.
		 * Calculates necessary information on function signatures necessary for generation of the header file.
		 * Added the extra input and output functions
		 */
		def InOutRulesBlockResult compileInOutRuleBlocks(
			IORuleType ioType,
			InOutRules rulesBlock,
			String adaptationClassName,
			String adaptationName,
			LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVars,
			LinkedHashMap<String, SAScalarVariable> SASVs,
			LinkedHashMap<String, GlobalInOutVariable> params,
			LinkedHashMap<String, GlobalInOutVariable> inVars,
			LinkedHashMap<String, GlobalInOutVariable> outVars,
			LinkedHashMap<String, GlobalInOutVariable> crtlVars,
			List<Port> portsWithSrcDep
		) {


			val visitor = if (ioType == IORuleType.Input)
					new InRulesConditionSwitch(adaptationClassName, adaptationName, mSVars, SASVs, params, inVars,
						outVars, crtlVars)
				else
					new OutRulesConditionSwitch(adaptationClassName, adaptationName, mSVars, SASVs, params, inVars,
											 
  
 
											  
															  
  
 
 
   
																			  
																										
											  
	
												  
					
						
							 
						
																												  
												
													
													
													 
																												  
												
													
													
													 
						outVars, crtlVars);

	
   
																			  
																										
											  
	
												  
					
						
							 
						
																												  
												
													
													
													 
													  
							
	 
  
	
 
			val functionName = "create" + ioType + "Rules()";
			var String cpp = "";
			var List<String> allFunctionSignatures = newArrayList();

			if (rulesBlock !== null) {
				cpp += visitor.doSwitch(rulesBlock).code;
			}
			if (!visitor.functionSignatures.empty || !portsWithSrcDep.empty) {
				allFunctionSignatures.addAll(visitor.functionSignatures);
				var ArrayList<String> createRulesFunction = newArrayList();

				if (rulesBlock !== null) {
					// For-loop Handles the out rules defined in the sa file
					for (var int i = 0; i < (visitor.functionSignatures.length); i += 3) {
						createRulesFunction.add( 
					'''
							list->push_back(
								(Rule<«adaptationClassName»>){
									&«adaptationClassName»::«visitor.functionSignatures.get(i).SplitAtSpaceAndRemoveFirst.removeArgumentParenthesis»,
									&«adaptationClassName»::«visitor.functionSignatures.get(i+1).SplitAtSpaceAndRemoveFirst.removeArgumentParenthesis»,
									&«adaptationClassName»::«visitor.functionSignatures.get(i+2).SplitAtSpaceAndRemoveFirst.removeArgumentParenthesis»
								});
							
						''');
					}
				}

				var List<String> depFunctionSource = newArrayList();
				var List<String> depFunctionSignatures = newArrayList();
				for (var int i = 0; i < portsWithSrcDep.length; i++) {
					val currentPort = portsWithSrcDep.get(i);
					// Output ports uses source dependencies.
					// Input ports uses target dependencies;
					val dependency = (if (ioType == IORuleType.Input)
							currentPort.targetdependency
						else
							currentPort.sourcedependency);
					val newCount = visitor.functionSignatures.length + i + 1;
					val funcSigCon = visitor.createFunctionSignature('''condition''', "bool", newCount,
						depFunctionSignatures)
					val funcSigBody = visitor.createFunctionSignature('''body''', "void", newCount,
						depFunctionSignatures)
					val funcSigFlush = visitor.createFunctionSignature('''flush''', "void", newCount,
						depFunctionSignatures)

					val type = mSVars.get(dependency.owner.name).get(dependency.port.name).mappedSv.type;
					val define = mSVars.get(dependency.owner.name).get(dependency.port.name).define;

					var ruleCpp = "";
					if (ioType == IORuleType.Output) {
						val getValueCpp = '''getValue«Conversions.fmiTypeToGetValueString(type)»(«dependency.owner.name»,«define»)''';
						ruleCpp = '''
							«funcSigCon»{
								«Utilities.getDebug(funcSigCon)»
								return true;
							}
							«funcSigBody»{
								«Utilities.getDebug(funcSigBody)»
								this->internalState.stored_«dependency.owner.name»_«dependency.port.name» = «getValueCpp»;
							}
							«funcSigFlush»{
								«Utilities.getDebug(funcSigFlush)»
								this->internalState.«currentPort.name» = this->internalState.stored_«dependency.owner.name»_«dependency.port.name»;
							}
						'''
					} else if (ioType == IORuleType.Input) {
						val setValueCpp = '''setValue(«dependency.owner.name»,«define»,this->internalState.stored_«dependency.owner.name»_«dependency.port.name»);''';
						ruleCpp = '''
							«funcSigCon»{
								«Utilities.getDebug(funcSigCon)»
								return true;
							}
							«funcSigBody»{
								«Utilities.getDebug(funcSigBody)»
								this->internalState.stored_«dependency.owner.name»_«dependency.port.name» = this->internalState.«currentPort.name»;
							}
							«funcSigFlush»{
								«Utilities.getDebug(funcSigFlush)»
								«setValueCpp»
							}
						'''
					}
					cpp += ruleCpp;
					depFunctionSource.add(funcSigCon);
					depFunctionSource.add(funcSigBody);
					depFunctionSource.add(funcSigFlush);

				}
				allFunctionSignatures.addAll(depFunctionSignatures);

				for (var int i = 0; i < (depFunctionSource.length); i += 3) {
					createRulesFunction.add( 
					'''
						list->push_back(
							(Rule<«adaptationClassName»>){
								&«depFunctionSource.get(i).SplitAtSpaceAndRemoveFirst.removeArgumentParenthesis»,
								&«depFunctionSource.get(i+1).SplitAtSpaceAndRemoveFirst.removeArgumentParenthesis»,
								&«depFunctionSource.get(i+2).SplitAtSpaceAndRemoveFirst.removeArgumentParenthesis»
							});
						
					''');
				}

				// Handles the createOutputRules and createInputRules
				val functionPrefix = '''shared_ptr<list<Rule<«adaptationClassName»>>>''';
				allFunctionSignatures.add(functionPrefix + " " + functionName)
				cpp += '''
					«functionPrefix» «adaptationClassName»::«functionName»
					{
						auto list = make_shared<std::list<Rule<«adaptationClassName»>>>();
						
						«createRulesFunction.join("\n")»
						
						return list;
						
					}
					
				'''
			}

			return new InOutRulesBlockResult(cpp, allFunctionSignatures);
		}

		/*
		 * Calculates the semantic adaptation scalar variables via input ports and output ports.
		 * Note: These a not fully populated yet as the in rules and out rules must be compiled first. 
		 */
		def LinkedHashMap<String, SAScalarVariable> calcSASVsFromInportsOutports(String definePrefix,
			EList<Port> inports, EList<Port> outports,
			LinkedHashMap<String, LinkedHashMap<String, MappedScalarVariable>> mSVs) {
			var LinkedHashMap<String, SAScalarVariable> saSVs = newLinkedHashMap();

			var int valueReference = 0;
			for (inport : inports) {
				var saSV = new SAScalarVariable();
				saSV.SetPartOfMD(true);
				saSV.valueReference = valueReference++;
				saSV.name = inport.name;
				saSV.defineName = (definePrefix + inport.name).toUpperCase
				saSV.causality = SVCausality.input;
				saSVs.put(saSV.name, saSV);
				if (inport.targetdependency !== null) {
					saSV.type = mSVs.get(inport.targetdependency.owner.name).get(inport.targetdependency.port.name).
						mappedSv.type;
					saSV.variability = mSVs.get(inport.targetdependency.owner.name).get(
						inport.targetdependency.port.name).mappedSv.variability;
				}
			}

			for (outport : outports) {
				var saSV = new SAScalarVariable();
				if (outport.sourcedependency !== null) {
					saSV.type = mSVs.get(outport.sourcedependency.owner.name).get(outport.sourcedependency.port.name).
						mappedSv.type;
					saSV.variability = mSVs.get(outport.sourcedependency.owner.name).get(
						outport.sourcedependency.port.name).mappedSv.variability;

				}
				saSV.SetPartOfMD(true);
				saSV.valueReference = valueReference++;
				saSV.defineName = (definePrefix + outport.name).toUpperCase
				saSV.name = outport.name;
				saSV.causality = SVCausality.output;
				saSVs.put(saSV.name, saSV);
			}

			return saSVs;
		}

		def List<File> getResourcePaths() {
			return resourcePaths;
		}
	}
	