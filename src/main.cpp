#include <main.h>

int main(int, char**) {
    std::cout << "Hello, World!\n";
    
    
    
    Poco::AutoPtr<Poco::XML::Document> pDoc = CXml::parseFile("data/test.xml");
    
    CXml::printSubNodes(pDoc);
    
    
    
    return 0;
}


