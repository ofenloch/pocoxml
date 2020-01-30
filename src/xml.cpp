#include <xml.h>

/*static*/ Poco::AutoPtr<Poco::XML::Document>
CXml::parseFile(std::string fileName) {

    std::ifstream in(fileName);
    Poco::XML::InputSource src(in);
    Poco::XML::DOMParser parser;
    Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&src);

    return pDoc;
}

/**
 * determine the given node's level in the tree
 * level 0 is the document node
 */
/*static*/ int 
CXml::getNodeLevel(Poco::XML::Node* pNode) {
    if (pNode->parentNode() != nullptr)
    {
        // there is at list one level above this one
        return (1 + getNodeLevel(pNode->parentNode()));
    }
    else
    {
        return 0;
    }
}

/*static*/ void
CXml::printSubNodes(Poco::XML::Node* pNode) {
    Poco::XML::NodeIterator it(pNode, Poco::XML::NodeFilter::SHOW_ALL);
    Poco::XML::Node *node = it.nextNode();
    while (node) {
        int level = CXml::getNodeLevel(node);
        std::cout << level;
        for (int i = 0; i < level; i++) {
            std::cout << " ";
        }
        std::cout << node->nodeName() << "  : " << node->nodeValue() << std::endl;
        node = it.nextNode();
    }
}

/*static*/ int
CXml::saveNodeToFile(Poco::XML::Node* pNode, std::string fileName) {
    Poco::XML::DOMWriter writer;
    writer.setNewLine("\n");
    writer.setIndent(" ");

    std::ofstream ofs;
    ofs.open(fileName);
    writer.writeNode(ofs, pNode);
    ofs.close();

    return 0;
}

/*static*/ std::string
CXml::getAttribute(Poco::XML::Node* pNode, std::string attrName) {
    return ((Poco::XML::Element*)pNode)->getAttribute(attrName);
}

/*static*/ void
CXml::setAttribute(Poco::XML::Node* pNode, std::string attrName, std::string attrValue) {
    ((Poco::XML::Element*)pNode)->setAttribute(attrName, attrValue);
}

/*static*/ void
CXml::duplicateNode(Poco::XML::Node* pNode) {
    // get the node's parent node
    Poco::XML::Node* pParentNode = pNode->parentNode();
    // make a deep clone of the node
    Poco::XML::Node* pNewNode = pNode->cloneNode(true);
    // change the duplicated node's id
    setAttribute(pNewNode, "id", getAttribute(pNode, "id") + "_2");
    pParentNode->appendChild(pNewNode);
}

/*static*/ int
CXml::normalizeXMLFile(const std::string& inFileName, const std::string& outFileName) {

    Poco::AutoPtr<Poco::XML::Document> pDocIn = parseFile(inFileName);
    Poco::XML::DOMWriter writer;
    writer.setNewLine(Poco::XML::XMLWriter::NEWLINE_LF);
    writer.setIndent(" "); // Use a single sapce for indentation. The default is a single TAB character.
    int writerOptions = Poco::XML::XMLWriter::WRITE_XML_DECLARATION + 
                        Poco::XML::XMLWriter::PRETTY_PRINT + 
                        Poco::XML::XMLWriter::PRETTY_PRINT_ATTRIBUTES;
    writer.setOptions(writerOptions);

    std::ofstream ofs;
    ofs.open(outFileName);
    writer.writeNode(ofs, pDocIn);
    ofs.close();

    return 0;
}

/*static*/ int
CXml::createTestFile(const std::string& fileName) {

    // to make things more clear, we call the Document pXMLDoc
    Poco::AutoPtr<Poco::XML::Document> pXMLDoc = new Poco::XML::Document;
    // to make things more clear, we call the Document's too pXMLRoot
    Poco::AutoPtr<Poco::XML::Element> pXMLRoot = pXMLDoc->createElement("DocumentList");
    pXMLRoot->setAttribute("zzzz","54321");
    pXMLRoot->setAttribute("wwww","43215");
    pXMLRoot->setAttribute("aaaa","12345");
    pXMLDoc->appendChild(pXMLRoot);

    // our first node is a document description <Document> element
    Poco::AutoPtr<Poco::XML::Element> pDDDoc1 = pXMLDoc->createElement("Document");
    pDDDoc1->setAttribute("sourcepath", "./data");
    pDDDoc1->setAttribute("targetpath", "./");
    pDDDoc1->setAttribute("id", "Document1");
    pXMLRoot->appendChild(pDDDoc1);

    Poco::AutoPtr<Poco::XML::Element> pChild3 = pXMLDoc->createElement("MasterBlock");
    Poco::AutoPtr<Poco::XML::Text> pText3 = pXMLDoc->createTextNode("text3");
    pChild3->appendChild(pText3);
    pDDDoc1->appendChild(pChild3);
    pChild3->setAttribute("zz", "z");
    pChild3->setAttribute("aa", "a");
    pChild3->setAttribute("id", "3");

    Poco::AutoPtr<Poco::XML::Element> pChild1 = pXMLDoc->createElement("MasterBlock");
    Poco::AutoPtr<Poco::XML::Text> pText1 = pXMLDoc->createTextNode("text1");
    pChild1->setAttribute("id", "1");
    pChild1->appendChild(pText1);
    pDDDoc1->appendChild(pChild1);

    Poco::AutoPtr<Poco::XML::Element> pChild2 = pXMLDoc->createElement("MasterBlockld");
    Poco::AutoPtr<Poco::XML::Text> pText2 = pXMLDoc->createTextNode("text2");
    pChild2->setAttribute("id", "2");
    pChild2->appendChild(pText2);
    pDDDoc1->appendChild(pChild2);

    Poco::XML::DOMWriter writer;
    writer.setNewLine(Poco::XML::XMLWriter::NEWLINE_LF);
    writer.setIndent(" "); // Use a single sapce for indentation. The default is a single TAB character.
    int writerOptions = Poco::XML::XMLWriter::WRITE_XML_DECLARATION +
                        Poco::XML::XMLWriter::PRETTY_PRINT +
                        Poco::XML::XMLWriter::PRETTY_PRINT_ATTRIBUTES;
    writer.setOptions(writerOptions);

    std::ofstream ofs;
    ofs.open(fileName);
    writer.writeNode(ofs, pXMLDoc);
    ofs.close();

    return 0;
}