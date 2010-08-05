// Parse a GraphML tree and draw it
// uses Xerces XML library
// copyright (c) 2010 Adrian McMenamin
// adrianmcmenamin@gmail.com
// Licensed under version 2 (or later)
// of the GNU GPL

#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include "redblackSAX.hpp"

using namespace std;
using namespace xercesc;

int main(int argc, char* argv[])
{
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		cout << "XML Parsing failed" << endl;
		return 1;
	}

	//XML Parsing code goes here
	char* xmlFile = "graphic.xml";
	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
	parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
	parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);

	redblackSAXHandler* rbSAX = new redblackSAXHandler();
	parser->setContentHandler(rbSAX);
	parser->setErrorHandler(rbSAX);

	try {
		parser->parse(xmlFile);
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
	delete rbSAX;

	XMLPlatformUtils::Terminate();

	return 0;
}
