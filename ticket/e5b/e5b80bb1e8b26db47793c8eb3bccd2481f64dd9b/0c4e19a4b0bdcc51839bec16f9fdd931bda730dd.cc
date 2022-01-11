// g++ crappy.cc -o crappy `wx-config --cflags --libs` -g

#include <wx/mimetype.h>
#include <iostream>

int main()
{
    using std::cout;
    if( 0 != wxTheMimeTypesManager->GetFileTypeFromExtension(wxT('pdf')) )
        cout << "MimeType for pdf extension found\n";
    else
        cout << "MimeType for pdf extension not found\n";

    return 0;
}
