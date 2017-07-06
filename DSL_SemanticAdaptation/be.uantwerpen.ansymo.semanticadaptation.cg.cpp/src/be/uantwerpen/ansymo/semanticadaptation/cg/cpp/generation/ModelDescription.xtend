package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVCausality
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVType
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVVariability
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ScalarVariable
import be.uantwerpen.ansymo.semanticadaptation.log.Log
import java.io.File
import java.util.Enumeration
import java.util.LinkedHashMap
import java.util.zip.ZipEntry
import java.util.zip.ZipFile
import javax.xml.parsers.DocumentBuilder
import javax.xml.parsers.DocumentBuilderFactory
import javax.xml.soap.Node
import javax.xml.xpath.XPath
import javax.xml.xpath.XPathConstants
import javax.xml.xpath.XPathExpression
import javax.xml.xpath.XPathFactory
import org.w3c.dom.Document
import org.w3c.dom.NodeList

class ModelDescription {
	private final Document md;
	private final String name;
	private final String type;
	//Get rid of these. We need more information anyways.
	private var LinkedHashMap<String, Pair<String, Integer>> svDefs = newLinkedHashMap();
	private var LinkedHashMap<String, ScalarVariable> svs = newLinkedHashMap();
	private var String guid;

	new(String name, String type, File path) {
		Log.push("Loading model description for fmu " + name)
		this.name = name;
		this.type = type;
		
		Log.println("Source fmu absolute path: " + path.absolutePath)
		
		var ZipFile fmu = new ZipFile(path);
		var Enumeration<? extends ZipEntry> entries = fmu.entries();
		var boolean entryFound = false;
		var ZipEntry locatedEntry;

		while (!entryFound && entries.hasMoreElements()) {
			var ZipEntry entry = entries.nextElement();
			if (entry.name.equalsIgnoreCase("modelDescription.xml")) {
				locatedEntry = entry;
				entryFound = true;

			}
		}
		var DocumentBuilderFactory fac = DocumentBuilderFactory.newInstance();
		var DocumentBuilder builder = fac.newDocumentBuilder();
		val is = fmu.getInputStream(locatedEntry)
		this.md = builder.parse(is);
		is.close();
		calcExtractInformation();
		Log.pop("Loading model description for fmu " + name)
	}

	private def calcExtractInformation() {
		val XPathFactory xPathfactory = XPathFactory.newInstance();
		val XPath xpath = xPathfactory.newXPath();
		val XPathExpression exprGuid = xpath.compile("/fmiModelDescription/@guid");
		this.guid = exprGuid.evaluate(this.md);
		val XPathExpression expr = xpath.compile("/fmiModelDescription/ModelVariables/ScalarVariable");
		val NodeList nl = expr.evaluate(this.md, XPathConstants.NODESET) as NodeList;
		for (var int i = 0; i < nl.length; i++) {
			val node = nl.item(i);
			val nodeName = node.attributes.getNamedItem("name").nodeValue;
			val valueRef = node.attributes.getNamedItem("valueReference").nodeValue;
			val name = this.name + nodeName;
			val define = name.toUpperCase;
			
			this.svDefs.put(name, define -> Integer.parseInt(valueRef));
			val sv = ScalarVariable.Create()
				.setCausality(SVCausality.valueOf(node.attributes.getNamedItem("causality").nodeValue))
				.setName(nodeName)
				.setOwner(this.name)
				.setValueReference(valueRef)
				.setIndex((i + 1).toString)
				.setVariability(SVVariability.valueOf(node.attributes.getNamedItem("variability").nodeValue));
				
			for (var j = 0; j < node.childNodes.length; j++) {
				val subNode = node.childNodes.item(j);
				if (subNode.nodeType == Node.ELEMENT_NODE) {
					val startAttribute = subNode.attributes.getNamedItem("start");
					if (startAttribute !== null) {
						sv.start = startAttribute.nodeValue;
					}
					sv.type = SVType.valueOf(subNode.nodeName);

					this.svs.put(nodeName, sv);

				}
			}
		}
	}

	public def getName() {
		return this.name;
	}

	public def getSvDef() {
		return this.svDefs;
	}

	public def getSv() { return this.svs; }

	public def getGuid() { return this.guid; }
}
