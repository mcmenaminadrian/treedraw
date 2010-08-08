// Parse a GraphML tree and draw it
// uses Xerces XML library
// copyright (c) 2010 Adrian McMenamin
// adrianmcmenamin@gmail.com
// Licensed under version 2 (or later)
// of the GNU GPL

#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

using namespace std;
using namespace xercesc;

int main(int argc, char* argv[])
{
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage()); 
		cout << "XML Parsing failed: " << message << endl;
		XMLString::release(&message);
		return 1;
	}

	//XML Parsing code goes here
	char* xmlFile = "graphic.xml";
	XercesDOMParser* parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setDoNamespaces(true);

	ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
	parser->setErrorHandler(errHandler);

	try {
		parser->parse(xmlFile);
		DOMDocument* rbtreedoc = parser->getDocument();

		DOMDocumentType* rbtreetype = rbtreedoc->getDoctype();
		if (rbtreetype == NULL)
			cout << "NULL Document type" << endl;

		XMLCh* nodeTag = XMLString::transcode("node");
		DOMNodeList* nodeslist = rbtreedoc->getElementsByTagName(nodeTag);
		if (!nodeslist)
			cout << "Empty list?!" << endl;
		else {
			cout << "We have " << nodeslist->getLength() << " nodes in this red black tree" << endl;
		}
		XMLString::release(&nodeTag);
	//	char* docname = XMLString::transcode(rbtreetype->getName());
	//	cout << "The supplied XML file is of type: " << docname << endl;
	//	XMLString::release(&docname);

	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is:" << endl;
		cout << message << endl;
		XMLString::release(&message);
		return -1;
	}
	catch (const SAXParseException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is:" << endl;
		cout << message << endl;
		XMLString::release(&message);
		return -1;
	}
	catch (...) {
		cout << "Unexpected Exception" << endl;
		return -1;
	}


	delete parser;

	XMLPlatformUtils::Terminate();

	return 0;
}
