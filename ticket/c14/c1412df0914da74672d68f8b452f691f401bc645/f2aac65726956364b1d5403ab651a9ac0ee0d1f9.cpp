#include <wx/wx.h>
#include <wx/regex.h>
#include <iostream>
#include <sstream>

using std::cout;
using std::cin;
using std::stringstream;

class App : public wxApp
{
public:
    bool OnInit() { return argc == 2; }
    int OnRun();
};

IMPLEMENT_APP(App)

int App::OnRun()
{
    wxString pattern = argv[1];
    stringstream ss;
    ss << cin.rdbuf();
    wxString str = wxString::FromAscii(ss.str().c_str());

    wxRegEx regex(pattern, wxRE_ADVANCED);

    if (regex.Matches(str))
        cout << regex.GetMatch(str).mb_str() << "\n";

    return 0;
}
