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

void redblackSAXHandler::fatalError(const SAXParseException& e)
{
	char* message = XMLString::transcode(e.getMessage());
	cout << "SAX fatal error: " << message << " at line ";
	cout << e.getLineNumber() << endl;
	XMLString::release(&message);
}
