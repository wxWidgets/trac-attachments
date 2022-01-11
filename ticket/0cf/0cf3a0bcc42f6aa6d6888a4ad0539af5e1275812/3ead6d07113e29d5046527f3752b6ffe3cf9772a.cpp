#include "wx/wxprec.h"
#include "wx/dataobj.h"
#include "wx/clipbrd.h"
#include "wx/bitmap.h"
#include <wx/dcmemory.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
  
private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    MyFrame *frame = new MyFrame("Minimal wxWidgets App");

    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
  wxImage::AddHandler(new wxPNGHandler);
  wxImage::AddHandler(new wxXPMHandler);
  wxImage::AddHandler(new wxJPEGHandler);

  wxMemoryDC dc;
  wxBitmap bmp;
  bmp.Create(100,100);

  dc.SelectObject(bmp);
  dc.SetUserScale(2,2);
  dc.SetBackground(*(wxTheBrushList->FindOrCreateBrush(wxT("white"), wxBRUSHSTYLE_SOLID)));
  dc.Clear();
  dc.SelectObject(wxNullBitmap);
  
  if (wxTheClipboard->Open())
    {
      wxTheClipboard->SetData(new wxBitmapDataObject(bmp));
      wxTheClipboard->Close();
    }
  
}

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
wxEND_EVENT_TABLE()
