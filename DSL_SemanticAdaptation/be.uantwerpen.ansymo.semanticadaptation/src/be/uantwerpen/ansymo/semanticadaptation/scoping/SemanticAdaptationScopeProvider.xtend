/*******************************************************************************
 * Copyright (c) 2015 itemis AG (http://www.itemis.eu) and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *******************************************************************************/
package be.uantwerpen.ansymo.semanticadaptation.scoping

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Adaptation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.AlgebraicLoopSolution
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Component
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Connection
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.DataRule
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Declaration
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.FMU
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.For
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.FunctionDeclaration
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.If
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InOutRules
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.LValueDeclaration
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.OutputFunction
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Port
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptationPackage
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SpecifiedPort
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.StateTransitionFunction
import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.Variable
import com.google.common.base.Predicate
import com.google.inject.Inject
import java.util.LinkedList
import java.util.List
import org.eclipse.emf.common.util.BasicEList
import org.eclipse.emf.common.util.EList
import org.eclipse.emf.ecore.EObject
import org.eclipse.emf.ecore.EReference
import org.eclipse.emf.ecore.resource.Resource
import org.eclipse.xtext.EcoreUtil2
import org.eclipse.xtext.resource.IEObjectDescription
import org.eclipse.xtext.scoping.IGlobalScopeProvider
import org.eclipse.xtext.scoping.IScope
import org.eclipse.xtext.scoping.Scopes
import org.eclipse.xtext.scoping.impl.AbstractDeclarativeScopeProvider
import org.eclipse.xtext.scoping.impl.IScopeWrapper
import be.uantwerpen.ansymo.semanticadaptation.log.Log

/**
 * This class contains custom scoping description.
 * 
 * See https://www.eclipse.org/Xtext/documentation/303_runtime_concepts.html#scoping
 * on how and when to use it.
 */
 
class SemanticAdaptationScopeProvider extends AbstractDeclarativeScopeProvider  {

	/* provides a global scope for all elements!
	 * overrides all the remainder of this class
	 */
	override getScope(EObject context, EReference reference) {
		Log.push("Getting scope for " + reference.name + " within context " + context.class)
		
		// TODO: This does not work for semantic adaptations on multiple files.
		// There is incomplete code for that below.
		
		if (reference.name == "port" && context instanceof SpecifiedPort){
			var portRef = context as SpecifiedPort
			if (portRef.owner !== null){
				val scopeFound = getFMUScope(portRef.owner)
				Log.pop("Scope found:" + scopeFound)
				return scopeFound
			} else {
				val scopeFound = getGenericScopePort(context)
				Log.pop("Scope found:" + scopeFound)
				return scopeFound
			}
		}
		
		if (reference.name == "port" && context instanceof Port){
			val scopeFound = getGenericScopePort(context)
			Log.pop("Scope found:" + scopeFound)
			return scopeFound
		}
		
		if (reference.name == "ref" && context instanceof Variable){
			var variable = context as Variable
			
			if(variable.owner !== null){
				val scopeFound = getFMUScope(variable.owner)
				Log.pop("Scope found:" + scopeFound)
				return scopeFound
			} else {
				var rootContainner = EcoreUtil2.getRootContainer(context)
				val scopeFound = Scopes.scopeFor(EcoreUtil2.getAllContentsOfType(rootContainner, LValueDeclaration))
				Log.pop("Scope found:" + scopeFound)
				return scopeFound
			}
		}
		
		/*
		println("Getting broader scope...")
		
		if (reference === SemanticAdaptationPackage.Literals.IMPORT__MODULE) {
			return getGlobalScope(context.eResource, reference)
		}
		
		val module = EcoreUtil2.getContainerOfType(context, SemanticAdaptation)
		var moduleScope = IScope.NULLSCOPE
		for (import : module.imports) {
			if (!import.module.eIsProxy)
				moduleScope = getModuleScope(context, reference, import.module, moduleScope)
		}
		moduleScope = getModuleScope(context, reference, module, moduleScope)
		val scopeFound = Scopes.scopeFor(context.eResource.allContents.toList, moduleScope)
		println("Scope found:" + scopeFound)
		return scopeFound
		 */
		
		Log.println("Delegating scope discovery to super class...")
		val scopeFound = super.getScope(context, reference)
		Log.pop("Scope found:" + scopeFound)
		return scopeFound
	}
	
	def getGenericScopePort(EObject context) {
		Log.println("Getting all port declarations")
		var rootContainner = EcoreUtil2.getRootContainer(context)
		val scopeFound = Scopes.scopeFor(EcoreUtil2.getAllContentsOfType(rootContainner, Port))
		return scopeFound
	}
	
	def getFMUScope(FMU fmu) {
		Log.println("Getting scope within FMU: " + fmu.name)
		val scopeFound = Scopes.scopeFor(EcoreUtil2.getAllContentsOfType(fmu, Port))
		return scopeFound
	}
	
	
	
	/*
	override getScope(EObject context, EReference reference) {
		println("Getting scope for " + reference + " within context " + context)
		if (reference === SemanticAdaptationPackage.Literals.IMPORT__MODULE) {
			return getGlobalScope(context.eResource, reference)
		}
		val module = EcoreUtil2.getContainerOfType(context, SemanticAdaptation)
		var result = IScope.NULLSCOPE
		for (import : module.imports) {
			if (!import.module.eIsProxy)
				result = getModuleScope(context, reference, import.module, result)
		}
		result = getModuleScope(context, reference, module, result)
		//println(Scopes.scopeFor(context.eResource.allContents.toList, result))
		return Scopes.scopeFor(context.eResource.allContents.toList, result)
	}
	 */
	
	// TODO: only correct src and tgt references
	def scope_Connection_src(Connection context, EReference r) {
		return __getImportedScope(context, r).__addScope(__getAllPorts(context))
	}
	
	def scope_Connection_tgt(Connection context, EReference r) {
		return __getImportedScope(context, r).__addScope(__getAllPorts(context))
	}
	
	def scope_Port_target(Port context, EReference r) {
		return __getImportedScope(context, r).__addScope(__getAllPorts(context))
	}
	
	def scope_AlgebraicLoopSolution_signals(AlgebraicLoopSolution context, EReference r) {
		return __getImportedScope(context, r).__addScope(__getAllPorts(context))
	}
	
	def scope_Variable_ref(Variable context, EReference r) {
		//println(context.eContainer())
		//var scope = __getImportedScope(context, r)
		var EList<EObject> elements = __getAllPorts(context)
		val outputfunction = EcoreUtil2.getContainerOfType(context, OutputFunction)
		if (outputfunction !== null) {
			val rule = outputfunction.eContainer as DataRule
			if (rule.statetransitionfunction !== null) {
				elements += rule.statetransitionfunction.statements
			}
		}
		elements += context.__getFrom(If, "ifstatements", Declaration, true).flatten
		elements += context.__getFrom(If, "ifstatements", FunctionDeclaration, true).flatten
		elements += context.__getFrom(For, "iterator", null, true).flatten
		elements += context.__getFromElement(StateTransitionFunction, "statements", Declaration)
		elements += context.__getFromElement(StateTransitionFunction, "statements", FunctionDeclaration)
		elements += context.__getFromElement(InOutRules, "globalvars")
		elements += context.__getFromElement(InOutRules, "iterationvars")
		elements += context.__getFromElement(Adaptation, "params")
		
		return __getImportedScope(context, r).__addScope(elements)
	}
	
	def scope_Adaptation_instances(Adaptation context, EReference r) {
		return __getImportedScope(context, r)
	}
	
	def scope_Adaptation_ports(Adaptation context, EReference r) {
		return __getImportedScope(context, r)
	}
	
	def scope_CompositeFMU_instances(SemanticAdaptation context, EReference r) {
		return __getImportedScope(context, r)
	}
	
	/*def scope_Step_fmu(Step context, EReference r) {
		return Scopes.scopeFor(EcoreUtil2.getContainerOfType(context, Adaptation).inner.instances, IScope.NULLSCOPE)
	}*/
	
	/*def EObject __getAncestorOfType(EObject object, Class<?> type) { // same as EcoreUtil2.getContainerOfType
		val parent = object.eContainer
		if (parent == null) {
			return null
		}
		if (type.isAssignableFrom(parent.class)) {
			return parent
		} else{
			return __getAncestorOfType(object.eContainer, type)
		}
	}*/
	
	def __addScope(IScope scope, EList elements) {
		return Scopes.scopeFor(elements, scope)
	}
	
	def __getAllPorts(EObject context) {
		val module = EcoreUtil2.getContainerOfType(context, SemanticAdaptation)
		var elementlist = new BasicEList<EObject>;
		for (Component element : module.elements) {
			if (element instanceof FMU) {
				elementlist += element.inports+element.outports
			}
		}
		return elementlist
	}
	
	def __getFromElement(EObject context, Class<? extends EObject> containertype, String featurename, Class<? extends EObject> featuretype) {
		/*val object = EcoreUtil2.getContainerOfType(context, containertype)
		if (object != null) {
			val feature = object.eClass.EAllStructuralFeatures.findFirst(f | f.name.equals(featurename))
			if (feature != null) {
				val featurevalue = object.eGet(feature)
				if (featurevalue instanceof EList) {
					if (featuretype != null) {
						return featurevalue.filter(v | featuretype.isInstance(v))
					} else {
						return featurevalue
					}
				} else {
					if (featuretype == null || featuretype.isInstance(featurevalue)) {
						val featurevaluelist = new BasicEList()
						featurevaluelist.add(featurevalue)
						return featurevaluelist
					}
				}
			} else {
				throw new Exception("Feature " + featurename + " not found in object of type " + containertype.name)
			}
		}
		return new BasicEList<EObject>()*/
		return context.__getFrom(containertype, featurename, featuretype, false).flatten
	}
	
	def __getFromElement(EObject context, Class<? extends EObject> containertype, String featurename) {
		return context.__getFromElement(containertype, featurename, null)
	}
	
	/**
	 * Look from context to root for elements
	 * @params:
	 * 		context: element to start from
	 * 		containertype: type of elements that have a feature that needs to be found
	 * 		featurename: name of feature that must be a feature of containertype
	 * 		featuretype: only take features of featuretype
	 * 		all: if true: go through all instances of container type; if false: only the first encounter from context to root 
	 * 
	 * @returns:
	 * 		all: list of lists of found elements (from context to root)
	 * 		!all: list of found elements (first encounter from context to root)
	 */
	def List<? extends List<? extends EObject>> __getFrom(EObject context, Class<? extends EObject> containertype, String featurename, Class<? extends EObject> featuretype, boolean all) {
		val List<List<EObject>> listOfElementLists = new LinkedList<List<EObject>>()
		for (object : EcoreUtil2.getAllContainers(context)) {
			if (containertype.isInstance(object)) {
				val List<EObject> listOfElements = new LinkedList<EObject>()
				val feature = object.eClass.EAllStructuralFeatures.findFirst(f | f.name.equals(featurename))
				if (feature !== null) {
					val featurevalue = object.eGet(feature)
					if (featurevalue instanceof EList) {
						if (featuretype !== null) {
							listOfElements.addAll(featurevalue.filter(v | featuretype.isInstance(v)).map(v | v as EObject))
						} else {
							listOfElements.addAll(featurevalue)
						}
					} else if (featurevalue instanceof EObject) {
						if (featuretype === null || featuretype.isInstance(featurevalue)) {
							listOfElements.add(featurevalue)
						}
					} else {
						throw new Exception("todo")
					}
				} else {
					throw new Exception("Feature " + featurename + " not found in object of type " + containertype.name)
				}
				listOfElementLists.add(listOfElements)
				if (!all) {
					return listOfElementLists
				}
			}
		}
		return listOfElementLists
	}
	
	
	
	
	
	
	
	
	
	
	
	
	@Inject IGlobalScopeProvider globalScopeProvider;

	def protected IScope getGlobalScope(Resource context, EReference reference) {
		return getGlobalScope(context, reference, null);
	}
	
	def protected IScope getGlobalScope(Resource context, EReference reference, Predicate<IEObjectDescription> filter) {
		return wrap(globalScopeProvider.getScope(context, reference, filter));
	}
	
	IScopeWrapper scopeWrapper;
	
	override setWrapper(IScopeWrapper wrapper) {
		this.scopeWrapper = wrapper;
	}

	def protected IScope wrap(IScope scope) {
		if (scopeWrapper!==null){
			return scopeWrapper.wrap(scope)
		} else {
			return scope
		}
	}
	
	def __getImportedScope(EObject context, EReference reference) {
		if (reference === SemanticAdaptationPackage.Literals.IMPORT__MODULE) {
			return getGlobalScope(context.eResource, reference)
		}
		val module = EcoreUtil2.getContainerOfType(context, SemanticAdaptation)
		var result = IScope.NULLSCOPE
		for (import : module.imports) {
			if (!import.module.eIsProxy)
				result = getModuleScope(context, reference, import.module, result)
		}
		result = getModuleScope(context, reference, module, result)
		return result//getDefinitionScope(context, reference, result)
	}
	
	def getModuleScope(EObject context, EReference reference, SemanticAdaptation module, IScope parent) {
		// FMUs and ports are visible
		val allDefinitions = module.elements.filter(FMU) + __getAllPorts(module)
		//println(allDefinitions)
		return Scopes.scopeFor(allDefinitions, parent)
	}
	
	/*def getDefinitionScope(EObject context, EReference reference, IScope parent) {
		val containingDef = EcoreUtil2.getContainerOfType(context, Definition)
		if (containingDef === null) {
			return parent
		}
		return Scopes.scopeFor(containingDef.args, parent)
	}*/

	
//class SemanticAdaptationScopeProvider extends AbstractGlobalScopeDelegatingScopeProvider {

//	override getScope(EObject context, EReference reference) {
//		if (reference === SemanticAdaptationPackage.Literals.IMPORT__MODULE) {
//			return super.getGlobalScope(context.eResource, reference)
//		}
//		val module = EcoreUtil2.getContainerOfType(context, Module)
//		var result = IScope.NULLSCOPE
//		for (import : module.imports) {
//			if (!import.module.eIsProxy)
//				result = getModuleScope(context, reference, import.module, result)
//		}
//		result = getModuleScope(context, reference, module, result)
//		return getDefinitionScope(context, reference, result)
//	}
//	
//	def getModuleScope(EObject context, EReference reference, Module module, IScope parent) {
//		val allDefinitions = module.statements.filter(Definition)
//		if (context instanceof FunctionCall) {
//			return Scopes.scopeFor(allDefinitions.filter[context.args.size == args.size], parent)
//		} else {
//			return Scopes.scopeFor(allDefinitions, parent)
//		}
//	}
//	
//	def getDefinitionScope(EObject context, EReference reference, IScope parent) {
//		val containingDef = EcoreUtil2.getContainerOfType(context, Definition)
//		if (containingDef === null) {
//			return parent
//		}
//		return Scopes.scopeFor(containingDef.args, parent)
//	}

}
