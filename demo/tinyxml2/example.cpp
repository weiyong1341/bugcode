#include <tinyxml2.h>

using namespace tinyxml2;
int main()
{
    static const char* xml = "<element/>";
    XMLDocument doc;
    doc.Parse( xml );
 
    return doc.ErrorID();
}