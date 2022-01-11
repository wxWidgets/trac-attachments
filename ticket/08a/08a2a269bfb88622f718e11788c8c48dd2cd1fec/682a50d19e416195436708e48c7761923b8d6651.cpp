#include "main.h"
#include "openfile.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

    Openfile *open = new Openfile(wxT("Openfile"));
    open->Show(true);

    return true;
}
