#ifndef _xml_h_
#define _xml_h_

#include <iostream>
#include <fstream>

#include <Poco/AutoPtr.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/NamedNodeMap.h>
#include <Poco/DOM/NodeFilter.h>
#include <Poco/DOM/NodeList.h>
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
    /**
     * write the node and all subnodes to a
     * file with given name
     * return 0 on success
     */
    static int
    saveNodeToFile(Poco::XML::Node* pNode, std::string fileName);
    /**
     * make a deep copy/clone of the given node, change the clone's id
     * and append the copy to the given node's parent node
     */
    static void
    duplicateNode(Poco::XML::Node* pNode);
    /**
     * Returns the attribute's value, if the attribute
     * exists, or an empty string otherwise.
     */
    static std::string
    getAttribute(Poco::XML::Node* pNode, std::string attrName);
    /**
     * Adds a new attribute. If an attribute with that name is already present
     * in the element, its value is changed to be that of the value parameter.
     * This value is a simple string; it is not parsed as it is being set. So any
     * markup (such as syntax to be recognized as an entity reference) is treated
     * as literal text, and needs to be appropriately escaped by the implementation
     * when it is written out.
     */
    static void
    setAttribute(Poco::XML::Node* pNode, std::string attrName, std::string attrValue);
}; // class CXml

#endif // #ifndef _xml_h_
