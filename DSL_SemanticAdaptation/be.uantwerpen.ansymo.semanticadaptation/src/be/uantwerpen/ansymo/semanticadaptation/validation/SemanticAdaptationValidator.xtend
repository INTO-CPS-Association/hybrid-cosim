/*******************************************************************************
 * Copyright (c) 2015 itemis AG (http://www.itemis.eu) and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *******************************************************************************/
package be.uantwerpen.ansymo.semanticadaptation.validation

/**
 * Custom validation rules. 
 *
 * See https://www.eclipse.org/Xtext/documentation/303_runtime_concepts.html#validation
 */
class SemanticAdaptationValidator extends AbstractSemanticAdaptationValidator {
//	@Inject Interpreter interpreter
//
//	@Check
//	def checkDivByZero(Div div) {
//		val bigDecimal = interpreter.evaluate(div.right)
//		if (bigDecimal.doubleValue()==0.0) 
//			error("Division by zero detected.", DIV__RIGHT)
//	}
//	
//	public static val String NORMALIZABLE = "normalizable-expression"
//
//	@Check
//	def void checkNormalizable(Expression expr) {
//		// ignore literals
//		if (expr instanceof NumberLiteral || expr instanceof FunctionCall) 
//			return;
//		// ignore evaluations
//		if (EcoreUtil2.getContainerOfType(expr, Evaluation)!=null)
//			return;
//		
//		val contents = expr.eAllContents
//		while(contents.hasNext()) {
//			val next = contents.next()
//			if (next instanceof FunctionCall) 
//				return
//		}
//		val decimal = interpreter.evaluate(expr)
//		if (decimal.toString().length()<=8) {
//			warning(
//					"Expression could be normalized to constant '"+decimal+"'", 
//					null,
//					ValidationMessageAcceptor.INSIGNIFICANT_INDEX,
//					NORMALIZABLE,
//					decimal.toString())
//		}
//	}
}
