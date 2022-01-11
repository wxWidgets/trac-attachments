// BUILD: g++ buggy.cpp -Wall -Wno-deprecated-declarations $(wx-config --cxxflags --libs xrc,core,base) $(pkg-config --libs x11)
#include <wx/wx.h>
#include <wx/xrc/xmlres.h> // for class wxXmlResource
#if defined(__WXGTK__)
    #include <X11/Xlib.h> // for function XInitThreads
#endif

class CApp : public wxApp
{
public:
    bool OnInit() {
        // Initialization
#if defined(__WXGTK__)
        // Comment out next line to avoid segfault that happens when LoadXXX is called. See below.
        if (!::XInitThreads()) throw std::runtime_error("XInitThreads Failure");
#endif
        // Create the main frame.
        wxFrame *frame = new wxFrame(NULL, wxID_ANY, "buggy");
#if 0
        // segfault
        wxXmlResource *res = wxXmlResource::Get();
        res->Load("file:a.xrc");
        res->InitAllHandlers();
        frame->SetMenuBar(res->LoadMenuBar("MyMenuBar1"));
#elif 0
        // segfault
        wxMenu * menus[] = {new wxMenu, new wxMenu};
        wxString labels[] = {wxT("&File"), wxT("&Help")};
        frame->wxFrame::SetMenuBar(new wxMenuBar(2, menus, labels));
#elif 0
        // segfault
        wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(new wxTextCtrl(frame, wxID_ANY));
        sizer->Add(new wxButton(frame, wxID_OK));
        frame->SetSizer(sizer);
        frame->Layout();
#else
        // no segfault
        new wxWindow(frame, wxID_ANY);
#endif
        // Enter the message loop.
        frame->Center(wxBOTH);
        frame->Show(true);
        return true;
    }
};
wxDECLARE_APP(CApp);
wxIMPLEMENT_APP(CApp);
