
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnHideCol(wxCommandEvent& event);
    void OnShowCol(wxCommandEvent& event);
    void OnHideRow(wxCommandEvent& event);
    void OnShowRow(wxCommandEvent& event);
protected:
    wxGrid *grid;
};

enum
{
    ID_Quit=1,
    ID_Go
};

class MyApp : public wxApp
{
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)




bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( _("Grid Test"), wxPoint(50, 50),
                                  wxSize(450, 350));

    frame->Show(true);
    SetTopWindow(frame);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame( NULL, -1, title, pos, size ) {
  
  wxBoxSizer *sizer=new wxBoxSizer(wxVERTICAL);
  wxButton *button=new wxButton(this,wxID_ANY,wxT("Hide Row 0"));
  button->Connect(wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MyFrame::OnHideRow,NULL,this);
  sizer->Add(button,0);
  button=new wxButton(this,wxID_ANY,wxT("Show Row 0"));
  sizer->Add(button,0);
  button->Connect(wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MyFrame::OnShowRow,NULL,this);
  button=new wxButton(this,wxID_ANY,wxT("Hide Col 0"));
  sizer->Add(button,0);
  button->Connect(wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MyFrame::OnHideCol,NULL,this);
  button=new wxButton(this,wxID_ANY,wxT("Show Col 0"));
  sizer->Add(button,0);
  button->Connect(wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MyFrame::OnShowCol,NULL,this);
  grid=new wxGrid(this,wxID_ANY);
  grid->CreateGrid(6,6);

  // make sure the autosize works
  grid->AutoSizeRowLabelSize(3);
  grid->AutoSizeColLabelSize(3);

  sizer->Add(grid,1,wxEXPAND);
  SetSizer(sizer);
  Fit();
}


void MyFrame::OnHideCol(wxCommandEvent& event) {
   grid->HideCol(0); 
}
void MyFrame::OnShowCol(wxCommandEvent& event) {
   grid->ShowCol(0); 
}

void MyFrame::OnHideRow(wxCommandEvent& event) {
   grid->HideRow(0); 
}
void MyFrame::OnShowRow(wxCommandEvent& event) {
   grid->ShowRow(0); 
}