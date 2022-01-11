#include <wx/aui/aui.h>
#include <wx/aui/dockart.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/gbsizer.h>

class MyApp : public wxApp {
public:
  bool OnInit();
  wxFrame* frame;
};

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);


class MyDlg : public wxDialog {
public:
  MyDlg (wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE, const wxString &name=wxDialogNameStr);
  wxGrid *getGrid() { return m_grid; }
protected:
  void onResize(wxSizeEvent& event);
  wxGrid *m_grid;
};

class MyFrame : public wxFrame {
public:
  MyFrame(wxWindow* parent);
  ~MyFrame(){ m_timer->Stop(); delete m_timer; }
  void onTimer(wxTimerEvent& event);
protected:
  wxTimer *m_timer;
  wxStaticText *m_size_txt;
  wxStaticText *m_vsize_txt;
  wxStaticText *m_scrollbars_txt;
  MyDlg *m_grid_window;
};

MyDlg::MyDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name) 
  : wxDialog(parent,id,title,pos,size,style,name)
{
  wxGridBagSizer *sizer=new wxGridBagSizer();
 // sizer->Add(new wxButton(this,wxID_ANY,"dummy button"),wxGBPosition(0,0),wxDefaultSpan);
 // m_grid=new wxGrid(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE|wxHSCROLL|wxVSCROLL|wxBORDER_SIMPLE);
  m_grid=new wxGrid(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE|wxBORDER_SIMPLE);
  m_grid->CreateGrid(5,5);
  m_grid->SetMinSize(wxSize(100,50));
  sizer->Add(m_grid,wxGBPosition(1,0),wxDefaultSpan,wxEXPAND);
  sizer->AddGrowableCol(0);
  sizer->AddGrowableRow(1);
  SetSizer(sizer);
  Bind(wxEVT_SIZE,&MyDlg::onResize,this);
}

void MyDlg::onResize( wxSizeEvent& event )
{
  Layout();
  bool test=m_grid->IsScrollbarShown(wxHORIZONTAL);
  event.Skip(false);
}

MyFrame::MyFrame(wxWindow* parent) : wxFrame(parent, -1, _("Grid Scrollbar Test"),
                                             wxDefaultPosition, wxDefaultSize,
                                             wxDEFAULT_FRAME_STYLE)                             
{
  m_grid_window=new MyDlg(this,wxID_ANY,wxString("grid dlg window"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
  m_grid_window->Show();

  wxBoxSizer *sz=new wxBoxSizer(wxVERTICAL);
  m_size_txt=new wxStaticText(this,wxID_ANY,wxString("Pending"));
  sz->Add(m_size_txt,wxSizerFlags(0).Expand());

  m_vsize_txt=new wxStaticText(this,wxID_ANY,wxString("Pending"));
  sz->Add(m_vsize_txt,wxSizerFlags(0).Expand());

  m_scrollbars_txt=new wxStaticText(this,wxID_ANY,wxString("Pending"));
  sz->Add(m_scrollbars_txt,wxSizerFlags(0).Expand());
  sz->AddStretchSpacer();
  SetSizer(sz);
  Layout();
  m_timer= new wxTimer(this);
  m_timer->Start(100);
  Bind(wxEVT_TIMER,&MyFrame::onTimer,this);
}

void MyFrame::onTimer( wxTimerEvent& event )
{
  bool updated=false;
  wxString msg="grid GetSize()=";
  wxSize sz=m_grid_window->getGrid()->GetSize();
  msg << sz.GetWidth() << ',' << sz.GetHeight();
  if (m_size_txt->GetLabel()!=msg) {
    m_size_txt->SetLabel(msg);
    updated=true;
  }

  msg="grid GetVirtualSize()=";
  sz=m_grid_window->getGrid()->GetVirtualSize();
 // sz=m_grid_window->getGrid()->GetBestVirtualSize();
  msg << sz.GetWidth() << ',' << sz.GetHeight();
  if (m_vsize_txt->GetLabel()!=msg) {
    m_vsize_txt->SetLabel(msg);
    updated=true;
  }

  msg="grid HasScrollbar() H,V=";
  msg << wxString(m_grid_window->getGrid()->HasScrollbar(wxHORIZONTAL)?"True":"False") << ',' << wxString(m_grid_window->getGrid()->HasScrollbar(wxVERTICAL)?"True":"False");
  msg << " IsScrollbarShown() H,V=" << wxString(m_grid_window->getGrid()->IsScrollbarShown(wxHORIZONTAL)?"True":"False") << ',' << wxString(m_grid_window->getGrid()->IsScrollbarShown(wxVERTICAL)?"True":"False");
  if (m_scrollbars_txt->GetLabel()!=msg) {
    m_scrollbars_txt->SetLabel(msg);
    updated=true;
  }

  if (updated)
    Layout();
}

bool MyApp::OnInit()
{
  frame = new MyFrame(NULL);
  SetTopWindow(frame);
  frame->Show();
  return true;                   
}