/*
g++ `wx-config-3.0 --cxxflags` -c text_test.cpp
g++ -o text  `wx-config-3.0 --libs` text_test.o

g++ `~/software/wxWidgets-3.1.3/build_gtk3/wx-config --cxxflags` -c text_test.cpp
g++ -o text  `~/software/wxWidgets-3.1.3/build_gtk3/wx-config --libs` text_test.o
*/

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/textctrl.h>

class MyApp: public wxApp
{
public:
  bool OnInit();
};

bool MyApp::OnInit()
{
  if ( !wxApp::OnInit() )
    return false;

  wxFrame *frame = new wxFrame(NULL, wxID_ANY, wxS("Test"), wxPoint(50, 50));

  wxTextCtrl * m_text = new wxTextCtrl(frame, wxID_ANY, wxEmptyString,
				       wxDefaultPosition, wxSize(200,70),
				       wxTE_MULTILINE /* | wxTE_RICH*/);
  m_text->AppendText("This is a test\n");
  m_text->SetForegroundColour(*wxWHITE);
  m_text->SetBackgroundColour(*wxBLACK);
  //m_text->SetDefaultStyle(wxTextAttr(*wxWHITE,*wxBLACK,*wxITALIC_FONT));
  //m_text->SetStyle(0, m_text->GetLastPosition(),
  //		   wxTextAttr(*wxWHITE,*wxBLACK));
  m_text->AppendText("This is another test");
  frame->Show(true);
  return true;
}

IMPLEMENT_APP(MyApp)
