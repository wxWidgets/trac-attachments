#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/fs_mem.h>

class MyApp;

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxFileSystem::AddHandler(new wxMemoryFSHandler);
    wxMemoryFSHandler::AddFile("foo.txt", "*********************************************");

    wxFileSystem fsys;
    wxFSFile *file = fsys.OpenFile("memory:foo.txt");
    wxInputStream *stream = file->GetStream();
    const size_t BUFSIZE = 1024;
    char buf[BUFSIZE];
    size_t len = stream->Read(buf, 1024).LastRead();
    printf("%d\n", len);
    
    return TRUE;
}


 	  	 
