#ifndef _xml_h_
#define _xml_h_

#include <iostream>
#include <fstream>

#include <Poco/AutoPtr.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/NodeFilter.h>
#include <Poco/DOM/NodeIterator.h>
#include <Poco/SAX/InputSource.h>
#include <Poco/XML/XML.h>

class CXml {
public:
    static Poco::AutoPtr<Poco::XML::Document>
    parseFile(std::string fileName); 
    static int
    getNodeLevel(Poco::XML::Node* pNode);
    static void
    printSubNodes(Poco::XML::Node* pNode);
    
}; // class CXml

#endif // #ifndef _xml_h_
