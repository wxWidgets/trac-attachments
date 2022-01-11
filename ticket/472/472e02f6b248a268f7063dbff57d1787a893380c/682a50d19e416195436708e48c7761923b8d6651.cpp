#include <iostream>
#include <wx/wx.h>

using namespace std;

int main()
{
    /*
    // Calling Localtime first
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ( "Current local time and date: %s", asctime (timeinfo) );

    cout << endl << endl;
    */

    wxString str;

    /*
    str = wxDateTime::Now().Format("%c");
    cout << "wxDateTime::Now() : " << str << endl << endl;
    */

    wxDateTime dt;
    dt.SetToCurrent();

    str = dt.Format("%c");
    cout << "SetToCurrent : " << str << endl;

    str = dt.Format("%Z");
    cout << "TimeZone : " << str << endl << endl;

    str = wxDateTime::Now().Format("%c");
    cout << "wxDateTime::Now() [AGAIN]: " << str << endl << endl;


    return 0;
}
