#ifndef _xml_h_
#define _xml_h_

#include <iostream> // std::cout
#include <fstream>
#include <string>  // std::string
#include <sstream> // std::stringstream, std::stringbuf

#include <Poco/AutoPtr.h> //typedef to Poco::AutoPtr
#include <Poco/DOM/Document.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/NamedNodeMap.h>
#include <Poco/DOM/NodeFilter.h>
#include <Poco/DOM/NodeList.h>
#include <Poco/DOM/NodeIterator.h>
#include <Poco/SAX/InputSource.h>
#include <Poco/DOM/Text.h>
#include <Poco/XML/XML.h>
#include <Poco/XML/XMLWriter.h>
#include <Poco/UTF8Encoding.h>

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

    /**
     * Save an XML file in a normalized format to make comparison easier.
     * 
     * Parse the given file and write it to a new file. This way,
     * we should get a "normalized" version of the input file
     * that can be compared with another xml file in "normalized" format
     */
    static int
    normalizeXMLFile(const std::string& inFileName, const std::string& outFileName);

    /**
     * create an XML file from scratch
     */
    static int
    createTestFile(const std::string& fileName);
}; // class CXml

#endif // #ifndef _xml_h_
