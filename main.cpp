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

void addEdges(Tree& rbtree, DOMNodeList* edgelist)
{
	XMLCh* testID = XMLString::transcode("id");
	XMLCh* testSource = XMLString::transcode("source");
	XMLCh* testTarget = XMLString::transcode("target");
	XMLSize_t nedges = edgelist->getLength();

	for (XMLSize_t z = 0; z < nedges; z++)
	{
		bool left = true;
		int source = -1;
		int target = -1;
		DOMElement* elEdge = (DOMElement*)edgelist->item(z);
		//left or right?
		const XMLCh* eID = elEdge->getAttribute(testID);
		char* idstr = XMLString::transcode(eID);
		string xx(idstr);
		if (xx[0] == 'r')
			left = false;
		//source
		const XMLCh* eS = elEdge->getAttribute(testSource);
		char* srcstr = XMLString::transcode(eS);
		source = atoi(srcstr);
		//target
		const XMLCh* eT = elEdge->getAttribute(testTarget);
		char* tarstr = XMLString::transcode(eT);
		target = atoi(tarstr);
		if (left)
			rbtree.items[source]->left = target;
		else
			rbtree.items[source]->right = target;
		XMLString::release(&idstr);
		XMLString::release(&srcstr);
		XMLString::release(&tarstr);
	}
	XMLString::release(&testID);
	XMLString::release(&testTarget);
	XMLString::release(&testSource);
}	

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

		//Process nodes
		XMLCh* nodeTag = XMLString::transcode("node");
		DOMNodeList* nodeslist =
			rbtreedoc->getElementsByTagName(nodeTag);
		XMLString::release(&nodeTag);
		if (!nodeslist || nodeslist->getLength() == 0) {
			cout << "Cannot get list of tree nodes" << endl;
			goto cleanup;
		}
		else {
			XMLSize_t max = nodeslist->getLength();
			for (XMLSize_t x = 0; x < max; x++)
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
		}
		//Process edges
		XMLCh* edgeTag = XMLString::transcode("edge");
		DOMNodeList* edgelist =
			rbtreedoc->getElementsByTagName(edgeTag);
		XMLString::release(&edgeTag);
		if (!edgelist || edgelist->getLength() == 0) {
			cout << "Malformed GraphML file - no edges" << endl;
			goto cleanup;
		}
		else
			addEdges(rbtree, edgelist);
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

	rbtree.position();
cleanup:

	delete parser;

	XMLPlatformUtils::Terminate();

	return 0;
}
