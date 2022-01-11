#include <wx/app.h>
#include <wx/string.h>

///////////////////////////////////////////////////////////////
// Classes
class ReproCrash : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(ReproCrash)

bool ReproCrash::OnInit()
{
    for (wxChar ** nextArgument = argv; *nextArgument != NULL; nextArgument++)
    {
        const wxChar * argument = *nextArgument;
        wxPrintf(L"arg: %s\n", argument);
    }
}

