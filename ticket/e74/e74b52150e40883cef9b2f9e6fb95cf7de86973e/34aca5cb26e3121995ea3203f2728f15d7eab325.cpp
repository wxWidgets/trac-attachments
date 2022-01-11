#include <iostream>
#include <string>

#include "lib/expat.h"

// The following is a UTF8 with bom encoded data with the following contents:
// <?xml version="1.0" encoding="UTF-8"?>
// <test>ТХИС ИС А ТЕСТ</test>
char xmlDocument[] =
{
        0xef, 0xbb, 0xbf, 0x3c, 0x3f, 0x78, 0x6d, 0x6c, 0x20, 0x76,
        0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3d, 0x22, 0x31, 0x2e,
        0x30, 0x22, 0x20, 0x65, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e,
        0x67, 0x3d, 0x22, 0x55, 0x54, 0x46, 0x2d, 0x38, 0x22, 0x3f,
        0x3e, 0x0d, 0x0a, 0x3c, 0x74, 0x65, 0x73, 0x74, 0x3e,
                                                              0xd0,
        0xa2, 0xd0, 0xa5, 0xd0, 0x98, 0xd0, 0xa1, 0x20, 0xd0, 0x98,
        0xd0, 0xa1, 0x20, 0xd0, 0x90, 0x20, 0xd0, 0xa2, 0xd0, 0x95,
        0xd0, 0xa1, 0xd0, 0xa2,
                                0x3c, 0x2f, 0x74, 0x65, 0x73, 0x74,
        0x3e, 0x0d, 0x0a
};

size_t const documentLen = sizeof( xmlDocument );

void handleCharData( void *, XML_Char const * s, int length )
{
    if ( length != 25 ) // 3 spaces + 11 cyrillic chars (2 bytes each).
    {
        std::cout << "Invalid length: " << length << ".\n";
        return;
    }
    int result = std::memcmp( s, xmlDocument + 49, length );
    std::cout << ( result ? "Failure." : "Success." ) << '\n';
}


int main()
{
    XML_Parser parser = XML_ParserCreate( 0 );
    XML_SetCharacterDataHandler( parser, &handleCharData );
    
    for ( size_t index = 0; index < documentLen; ++index )
    {
        int parseResult = XML_Parse( parser, xmlDocument + index, 1, index == documentLen - 1 );
        if ( parseResult == XML_STATUS_ERROR )
            std::cout << "Parse error.\n";
    }
    std::cout << "Done.";
    XML_ParserFree( parser );
}