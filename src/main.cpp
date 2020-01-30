#include <main.h>

int main(int, char **) {
    std::cout << "Hello, World!\n";

    Poco::AutoPtr<Poco::XML::Document> pDoc = CXml::parseFile("data/random.xml");

    CXml::printSubNodes(pDoc);

    Poco::AutoPtr<Poco::XML::Document> pDoc2 = CXml::parseFile("data/test.xml");
    Poco::XML::NodeList* persons = pDoc2->getElementsByTagName("person");
    CXml::saveNodeToFile((Poco::XML::Node*)pDoc2, "test-original.xml");
    if (persons->length() > 0) {
        Poco::XML::Node* pPerson = persons->item(0);
        CXml::duplicateNode(pPerson);
        CXml::printSubNodes(pDoc2);
        CXml::saveNodeToFile((Poco::XML::Node*)pDoc2, "test-copy.xml");
    }

    CXml::createTestFile("test-file.xml");

    return 0;
}
