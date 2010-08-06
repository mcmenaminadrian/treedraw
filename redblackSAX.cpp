#include "redblackSAX.hpp"
#include <iostream>

using namespace xercesc;
using namespace std;

redblackSAXHandler::redblackSAXHandler()
{}

void redblackSAXHandler::startElement(const XMLCh* const uri,
	const XMLCh* const localname, const XMLCh* const qname,
	const Attributes& attrs)
{
	char* message = XMLString::transcode(localname);
	cout << "We got element " << message << endl;
	XMLString::release(&message);
}

void redblackSAXHandler::endElement(const XMLCh* const uri,
	const XMLCh* const localname, const XMLCh* const qname)
{
	char* message = XMLString::transcode(localname);
	char* uriname = XMLString::transcode(uri);
	char* qnamem = XMLString::transcode(qname);
	cout << "End of element " << message << " with uri " << uriname << " and qname " << qnamem << endl;
	XMLString::release(&message);
	XMLString::release(&uriname);
	XMLString::release(&qnamem);
}

void redblackSAXHandler::fatalError(const SAXParseException& e)
{
	char* message = XMLString::transcode(e.getMessage());
	cout << "SAX fatal error: " << message << " at line ";
	cout << e.getLineNumber() << endl;
	XMLString::release(&message);
}
