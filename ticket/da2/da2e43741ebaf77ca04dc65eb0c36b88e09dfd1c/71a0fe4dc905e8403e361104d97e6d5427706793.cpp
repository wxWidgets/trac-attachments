#include <wx/app.h>
#include <wx/bitmap.h>
#include <wx/frame.h>
#include <wx/image.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>

#include "blocks.xpm"

class MinimalApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MinimalApp);

bool MinimalApp::OnInit()
{
    wxInitAllImageHandlers();
    wxFrame *Frame = new wxFrame(nullptr, wxID_ANY, "Minimal");
    wxBoxSizer *BoxSizer = new wxBoxSizer(wxVERTICAL);
    wxBitmap Bmp(blocks_xpm, wxBITMAP_TYPE_XPM);
    wxStaticBitmap *StaticBitmap = new wxStaticBitmap(Frame, wxID_ANY, Bmp);
    BoxSizer->Add(StaticBitmap);
    Frame->SetSizer(BoxSizer);
    Frame->Show();
    SetTopWindow(Frame);
    return true;
}
