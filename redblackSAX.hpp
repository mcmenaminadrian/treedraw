#include <xercesc/sax2/DefaultHandler.hpp>

using namespace xercesc;

class redblackSAXHandler:public DefaultHandler {
	public:
	void startElement(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname,
		const Attributes& attrs
	);
	void fatalError(const SAXParseException&);

	redblackSAXHandler();
};
