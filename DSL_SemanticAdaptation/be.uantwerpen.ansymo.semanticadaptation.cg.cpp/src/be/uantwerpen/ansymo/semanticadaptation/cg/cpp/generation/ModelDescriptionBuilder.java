package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation;

import java.io.StringWriter;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVCausality;
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVType;
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.SVVariability;
import be.uantwerpen.ansymo.semanticadaptation.cg.cpp.data.ScalarVariable;

public class ModelDescriptionBuilder {
	private DocumentBuilderFactory docFactory;
	private DocumentBuilder docBuilder;
	private Document doc;
	private Element rootElement;
	private Element coSimulation;
	private Element modelVariables;
	private Element outputs;
	private int valueReferenceCounter = 1;

	public ModelDescriptionBuilder() throws ParserConfigurationException {
		docFactory = DocumentBuilderFactory.newInstance();
		docBuilder = docFactory.newDocumentBuilder();
		doc = docBuilder.newDocument();
		doc.setXmlStandalone(true);
	}

	public void CreateTemplate(String modelName, String guid) throws ParserConfigurationException {
		rootElement = doc.createElement("fmiModelDescription");
		doc.appendChild(rootElement);
		rootElement.setAttribute("fmiVersion", "2.0");
		rootElement.setAttribute("modelName", modelName);
		rootElement.setAttribute("guid", guid);
		rootElement.setAttribute("variableNamingConvention", "flat");
		rootElement.setAttribute("generationTool", "BaseSA");
		rootElement.setAttribute("numberOfEventIndicators", "0");
		rootElement.setAttribute("copyright", "Aarhus University and University of Antwerpen");
		rootElement.setAttribute("license", "MIT");
		
		coSimulation = doc.createElement("CoSimulation");
		coSimulation.setAttribute("modelIdentifier", modelName);
		coSimulation.setAttribute("needsExecutionTool", "false");
		coSimulation.setAttribute("canHandleVariableCommunicationStepSize", "true");
		coSimulation.setAttribute("canInterpolateInputs", "true");
		coSimulation.setAttribute("maxOutputDerivativeOrder", "0");
		coSimulation.setAttribute("canRunAsynchronuously", "false");
		coSimulation.setAttribute("canBeInstantiatedOnlyOncePerProcess", "true");
		coSimulation.setAttribute("canNotUseMemoryManagementFunctions", "true");
		coSimulation.setAttribute("canGetAndSetFMUstate", "true");
		coSimulation.setAttribute("canSerializeFMUstate", "false");
		coSimulation.setAttribute("providesDirectionalDerivative", "false");
		rootElement.appendChild(coSimulation);
		
		Element logCategories = doc.createElement("LogCategories");
		for(String c : new String[] {"logAll", "logError", "logFmiCall", "logEvent"})
		{
			Element cat = doc.createElement("Category");
			cat.setAttribute("name", c);
			logCategories.appendChild(cat);
		}
		rootElement.appendChild(logCategories);
		
		modelVariables = doc.createElement("ModelVariables");
		rootElement.appendChild(modelVariables);

		Element modelStructure = doc.createElement("ModelStructure");
		rootElement.appendChild(modelStructure);
		outputs = doc.createElement("Outputs");
		modelStructure.appendChild(outputs);
	}

	public String getNextValueReference() {
		return Integer.toString(valueReferenceCounter++);
	}

	public void addScalarVariable(ScalarVariable var) {
		Element sv = doc.createElement("ScalarVariable");
		modelVariables.appendChild(sv);
		if (var.getName() != null)
			sv.setAttribute("name", var.getName());

		if (var.getValueReference() != null)
			sv.setAttribute("valueReference", var.getValueReference());

		if (var.getDescription() != null)
			sv.setAttribute("description", var.getDescription());

		if (var.getVariability() != null)
			sv.setAttribute("variability", var.getVariability().name());

		if (var.getCausality() != null) {
			sv.setAttribute("causality", var.getCausality().name());
			if (var.getCausality() == SVCausality.output) {
				outputs.appendChild(createUnknown(Integer.toString(modelVariables.getChildNodes().getLength())));
			}
		}

		if (var.getType() != null) {
			Element svType = getSvType(var.getType());
			sv.appendChild(svType);
			if (var.getStart() != null) {
				svType.setAttribute("start", var.getStart());
			}
			else
			{
				if(var.getVariability() == SVVariability.continuous && var.getCausality() == SVCausality.input)
				{
					svType.setAttribute("start", "0.0");
				}
			}
		}

	}

	private Element createUnknown(String index) {
		Element e = doc.createElement("Unknown");
		e.setAttribute("index", index);
		e.setAttribute("dependencies", "");
		return e;
	}

	private Element getSvType(SVType type) {
		return doc.createElement(type.name());
	}

	@Override
	public String toString() {
		try {
			StringWriter sw = new StringWriter();
			TransformerFactory tf = TransformerFactory.newInstance();
			Transformer transformer = tf.newTransformer();
			transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "no");
			transformer.setOutputProperty(OutputKeys.METHOD, "xml");
			transformer.setOutputProperty(OutputKeys.INDENT, "yes");
			transformer.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
			transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");
			transformer.transform(new DOMSource(doc), new StreamResult(sw));
			return sw.toString();
		} catch (Exception ex) {
			throw new RuntimeException("Error converting to String", ex);
		}
	}

}
