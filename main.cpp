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
#include "tree.hpp"

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
	Tree rbtree;

	try {
		parser->parse(xmlFile);
		DOMDocument* rbtreedoc = parser->getDocument();

		DOMDocumentType* rbtreetype = rbtreedoc->getDoctype();
		if (rbtreetype == NULL)
			cout << "NULL Document type" << endl;

		XMLCh* nodeTag = XMLString::transcode("node");
		DOMNodeList* nodeslist = rbtreedoc->getElementsByTagName(nodeTag);
		if (!nodeslist)
			cout << "Empty tree: nothing to process" << endl;
		else {
			int max = nodeslist->getLength();
			for (int x = 0; x < max; x++)
			{
				DOMNode* nxtNode = nodeslist->item(x);
				if (!nxtNode.hasChildNodes()) {
					//leaf node
					cout << "Node " << x << " is a leaf node" << endl;
					Node* lfnode = new Node();
					rbtree.items.push_back(lfnode);
				}
				else {
					int val = 0;
					bool red = false;
					//examine children
					DOMNodeList* childlist = nxtNode->getChildNodes();
					XMLSize_t cl = childlist->getLength();
					XMLCh* testData = XMLString::transcode("data");
					XMLCh* testV = XMLString::transcode("v");
					XMLCh* testC = XMLString::transcode("c");
					XMLCh* testKey = XMLString::transcode("key");
					for (XMLSize_t r = 0; r < cl; r++)
					{
						DOMNode* cNode = childlist->Item(r);
						XMLCh* elTag = XMLString::transcode(cNode->getNodeName());
						if (XMLString::equals(elTag, testData)) {
							//have a data tag - what is the key?
							XMLCh* keyval = cNode->getAttribute(testKey);
							if (XMLString::equals(testV, keyval)) {
								//read in the value
								XMLCh* valD = cNode->getData();
								char* valstr = XMLString::transcode(valD);
								cout << "Node " << x << " has value " << valstr << endl;
								val = atoi(valstr);
								XMLString::release(valstr);
								XMLString::release(valD);
							}
							XMLString::release(keyval);
						}
					}
				}
			}
			cout << "We have " << max << " nodes in this red black tree" << endl;
		}
		XMLString::release(&nodeTag);	

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
