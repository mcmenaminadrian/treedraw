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

void allocBranchNode(Tree& rbtree, DOMNodeList* dlist)
{
	bool red = false;
	XMLCh* testData = XMLString::transcode("data");
	XMLCh* testV = XMLString::transcode("v");
	XMLCh* testC = XMLString::transcode("c");
	XMLCh* testKey = XMLString::transcode("key");
	XMLCh* testRed = XMLString::transcode("red");

	XMLSize_t cl = dlist->getLength();

	for (XMLSize_t r = 0; r < cl; r++)
	{
		DOMNode* cNode = dlist->item(r);
		const XMLCh* elTag = cNode->getNodeName();
		if (XMLString::equals(elTag, testData)) {
			//have a data tag - what is the key?
			DOMElement* eNode = (DOMElement*) cNode;
			const XMLCh* keyval = eNode->getAttribute(testKey);
			if (XMLString::equals(testV, keyval)) {
				//read in the value
				DOMText* txtEl =
					(DOMText*)eNode->getFirstChild();
				const XMLCh* valD = txtEl->getData();
				char* valstr = XMLString::transcode(valD);
				Node* rbnode = new Node(valstr);
				rbtree.items.push_back(rbnode);
				XMLString::release(&valstr);
			}
			else if (XMLString::equals(testC, keyval))
			{
				DOMText* txtEl =
					(DOMText*)eNode->getFirstChild();
				const XMLCh* colD = txtEl->getData();
				if (XMLString::equals(colD, testRed))
				red = true;
			}
		}
	}
	if (red)
		rbtree.items[rbtree.items.size() - 1]->black = false;

	XMLString::release(&testData);
	XMLString::release(&testV);
	XMLString::release(&testC);
	XMLString::release(&testKey);
	XMLString::release(&testRed);
}

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
	string xmlFile("graphic.xml");
	XercesDOMParser* parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Always);
	parser->setDoNamespaces(true);

	ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
	parser->setErrorHandler(errHandler);
	Tree rbtree;

	try {
		parser->parse(xmlFile.c_str());
		DOMDocument* rbtreedoc = parser->getDocument();

		XMLCh* nodeTag = XMLString::transcode("node");
		DOMNodeList* nodeslist = rbtreedoc->getElementsByTagName(nodeTag);
		if (!nodeslist)
			cout << "Empty tree: nothing to process" << endl;
		else {
			int max = nodeslist->getLength();
			for (int x = 0; x < max; x++)
			{
				DOMNode* nxtNode = nodeslist->item(x);
				if (!nxtNode->hasChildNodes()) {
					//leaf node
					Node* lfnode = new Node();
					rbtree.items.push_back(lfnode);
				}
				else {

					DOMNodeList* childlist =
						nxtNode->getChildNodes();
					allocBranchNode(rbtree, childlist);
				}
			}
			cout << "We have " << rbtree.items.size() << " nodes in this red black tree, matching " << max << "hopefully" << endl;
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
