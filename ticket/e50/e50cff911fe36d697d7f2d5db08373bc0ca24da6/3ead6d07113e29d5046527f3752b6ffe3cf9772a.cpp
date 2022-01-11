#include "wx/wxprec.h"
#include "wx/filesys.h"
#include "wx/fs_zip.h"
#include "wx/uri.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    // Add zip files to the list of file systems we handle
    wxFileSystem::AddHandler(new wxZipFSHandler);

    wxFileSystem fs;
    wxString wxmxURI = wxURI(wxT("file://test.wxmx")).BuildURI();
    wxString filename = wxmxURI + wxT("#zip:content.xml");

    std::cerr<<"Trying to open file "<<filename<<"\n";
    wxFSFile *fsfile = fs.OpenFile(filename);

    std::cerr<<"Result (should be != NULL): "<<fsfile<<"\n";
    exit(fsfile != NULL);
    return true;
}
