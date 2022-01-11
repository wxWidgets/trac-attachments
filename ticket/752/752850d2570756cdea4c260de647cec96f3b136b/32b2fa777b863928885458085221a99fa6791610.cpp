#include <wx/wx.h>

// class TestcaseApp : public wxAppConsole
class TestcaseApp : public wxApp
{
public:
    int OnRun();
};

// IMPLEMENT_APP_CONSOLE(TestcaseApp) ;
IMPLEMENT_APP(TestcaseApp) ;

int TestcaseApp::OnRun()
{
    // check size of output with
    // sh -c 'for i in {1..66000} ; do echo -n . ; done; echo' | wc
    // from bash.
    {
        wxString cmd("sh -c 'for i in {1..65000} ; do echo -n . ; done; echo'");
        wxArrayString out, err;
        wxLogMessage("command: '%s'", cmd.c_str());
        wxExecute(cmd, out, err); // returns only, if output < 64KByte!
        wxLogMessage("finished '%s'", cmd.c_str());
    }
    {
        wxString cmd("sh -c 'for i in {1..66000} ; do echo -n . ; done; echo'");
        wxArrayString out, err;
        wxLogMessage("command: '%s'", cmd.c_str());
        wxExecute(cmd, out, err); // returns only, if output < 64KByte!
        wxLogMessage("finished '%s'", cmd.c_str());
    }
    return 0;
}

 	  	 
