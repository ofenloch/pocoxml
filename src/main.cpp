#include <iostream>
#include <fstream>

#include <main.h>

int main(int, char**) {
    std::cout << "Hello, World!\n";

    std::ifstream in("data/test.xml");
    Poco::XML::InputSource src(in);
    Poco::XML::DOMParser parser;
    Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&src);

    Poco::XML::NodeIterator it(pDoc, Poco::XML::NodeFilter::SHOW_ALL);
    Poco::XML::Node* pNode = it.nextNode();
    while (pNode) {
        int level = getNodeLevel(pNode);
        std::cout << level;
        for (int i=0; i<level; i++ ) {
            std::cout << " ";
        }
        std::cout << pNode->nodeName() << "  : " << pNode->nodeValue() << std::endl;
        pNode = it.nextNode();
    }


    return 0;
}

int getNodeLevel(Poco::XML::Node* pNode) {
    int level = 0;
    if (pNode->parentNode() != nullptr) {
        return (1+getNodeLevel(pNode->parentNode()));
    }
    return level;
}
