package be.uantwerpen.ansymo.semanticadaptation.cg.cpp

import java.io.File
import java.util.zip.ZipFile
import java.util.Enumeration
import java.util.zip.ZipEntry
import org.w3c.dom.Document
import javax.xml.parsers.DocumentBuilderFactory
import javax.xml.parsers.DocumentBuilder
import javax.xml.xpath.XPathExpression
import javax.xml.xpath.XPathFactory
import javax.xml.xpath.XPath
import javax.xml.soap.Node
import javax.xml.xpath.XPathConstants
import org.w3c.dom.NodeList
import java.util.LinkedHashMap
import javax.lang.model.element.Element

class ModelDescription {
	private final Document md;
	private final String name;
	private var LinkedHashMap<String,Pair<String,Integer>> scalarDefinitions = newLinkedHashMap();
	private var LinkedHashMap<String,SVType> scalarWithTypes = newLinkedHashMap();

	new(String name, File path) {
		this.name = name;

		var ZipFile fmu = new ZipFile(path);
		var Enumeration<? extends ZipEntry> entries = fmu.entries();
		var boolean entryFound = false;
		var ZipEntry locatedEntry;

		while (!entryFound && entries.hasMoreElements()) {
			var ZipEntry entry = entries.nextElement();
			if (entry.name.equalsIgnoreCase("modelDescription.xml"))
				locatedEntry = entry;
		}
		var DocumentBuilderFactory fac = DocumentBuilderFactory.newInstance();
		var DocumentBuilder builder = fac.newDocumentBuilder();
		val is = fmu.getInputStream(locatedEntry)
		this.md = builder.parse(is);
		is.close();
		calcScalars();
	}

	private def calcScalars() {
		val XPathFactory xPathfactory = XPathFactory.newInstance();
		val XPath xpath = xPathfactory.newXPath();
		val XPathExpression expr = xpath.compile("/fmiModelDescription/ModelVariables/ScalarVariable");
		val NodeList nl = expr.evaluate(this.md, XPathConstants.NODESET) as NodeList;
		for (var int i = 0; i < nl.length; i++) {
			val node = nl.item(i);
			val nodeName = node.attributes.getNamedItem("name").nodeValue;
			val name = this.name + nodeName;
			val define = name.toUpperCase; 
			this.scalarDefinitions.put(name,define -> i+1);
			
			for(var j = 0; j < node.childNodes.length; j++)
			{
				val subNode = node.childNodes.item(i);
				if(subNode.nodeType == Node.ELEMENT_NODE)
				{
					val type = SVType.valueOf(subNode.nodeName);
					this.scalarWithTypes.put(nodeName, type);
					//Alternative break, as break is not allowed
					j = node.childNodes.length;
				}
			}
		}
	}
	
	public def getName(){
		return this.name;
	}
	
	public def getScalars() {
		return this.scalarDefinitions;
	}
}
