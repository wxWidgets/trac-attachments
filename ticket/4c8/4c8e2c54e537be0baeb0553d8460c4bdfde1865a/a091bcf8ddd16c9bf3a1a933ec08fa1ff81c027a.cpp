#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/webview.h>

class MyApp: public wxApp
{
public:
  virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
  MyFrame();
private:
  void OnFind(wxCommandEvent& event);
  wxDECLARE_EVENT_TABLE();
  wxWebView* mBrowser;
};
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_FIND, MyFrame::OnFind)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
  MyFrame *frame = new MyFrame();
  frame->Show( true );
  return true;
}
MyFrame::MyFrame(): wxFrame(NULL, wxID_ANY, "WebView")
{
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(wxID_FIND, "&Find...\tCtrl-F");
  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append( menuFile, "&File" );
  SetMenuBar( menuBar );
  CreateStatusBar();

  wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(topsizer);
  mBrowser = wxWebView::New(this, wxID_ANY, "http://braillenet.org");
  topsizer->Add(mBrowser, wxSizerFlags().Expand().Proportion(1));
}
void MyFrame::OnFind(wxCommandEvent& WXUNUSED(event))
{
  mBrowser->Find("a");
}
