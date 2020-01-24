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
/*static*/ int CXml::getNodeLevel(Poco::XML::Node* pNode) {
    if (pNode->parentNode() != nullptr) {
        // there is at list one level above this one
        return (1+getNodeLevel(pNode->parentNode()));
    } else {
        return 0;
    }
}

/*static*/ void
CXml::printSubNodes(Poco::XML::Node* pNode) {
    Poco::XML::NodeIterator it(pNode, Poco::XML::NodeFilter::SHOW_ALL);
    Poco::XML::Node* node = it.nextNode();
    while (node) {
        int level = CXml::getNodeLevel(node);
        std::cout << level;
        for (int i=0; i<level; i++ ) {
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
    setAttribute(pNewNode, "id", getAttribute(pNode,"id")+"_2");
    pParentNode->appendChild(pNewNode);
}