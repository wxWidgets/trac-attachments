/////////////////////////////////////////////////////////////////////
//  Example to show focused redraw problem with a notebook in
//  GTK version of wxWidgets. Problem doesn't occurs in CVS and 2.5.x
//  but not in 2.4.x
//
// Compiles with:
//  c++ `wx-config --cxxflags` test.cpp `wx-config --libs`
//
// To show the problem start the program and toggle the check box
// TWICE. This should disable and enable the TextCtrl entry.
// Now move the mouse to focus on the TextCtrl. With the focus
// still on the TextCtrl change to page2 and then back to page1
// of the notebook. The problem shows up when page1 is redrawn 
// with the text in the TextCtrl not being drawn.
// The text shows back up if the check box is toggled or
// TextCtrl selected.

/////////////////////////////////////////////////////////////////////
// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/notebook.h"
#include "wx/statbox.h"


// Define a new application
class MyApp : public wxApp
{
public:
    bool OnInit();
};

DECLARE_APP(MyApp)

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title );

    virtual ~MyFrame();

     void OnExit( wxCommandEvent& event );
     void OnCheck( wxCommandEvent& event );


private:


    wxPanel *m_cntl_panel;
    wxTextCtrl *m_txt;


    wxPanel *m_panel; 

    wxNotebook   *m_notebook;


    wxBoxSizer *m_sizerFrame;


    DECLARE_EVENT_TABLE()
};


IMPLEMENT_APP(MyApp)


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,MyFrame::OnExit)
    EVT_CHECKBOX(-1,MyFrame::OnCheck)
END_EVENT_TABLE()





bool MyApp::OnInit()
{
    // Create the main window
    MyFrame *frame = new MyFrame( wxT("Example of Notebook disable/focus problem") );

    frame->Show();

    return true;
}


MyFrame::MyFrame(const wxString& title  )
    : wxFrame((wxWindow *) NULL, wxID_ANY, title )
{



    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT, wxT("E&xit"), wxT("Quits the application"));

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, wxT("&File"));
    SetMenuBar(menuBar);

//
// The idea is to create two pages for the notebook. The first
// just has some text on it. The second contains a wxPanel and a
// wxCheckBox in which the wxCheckBox enables/disables the wxPanel.
//


    m_panel      = (wxPanel *)      NULL;
    m_notebook   = (wxNotebook *)   NULL;


    m_sizerFrame = new wxBoxSizer(wxVERTICAL);
    m_panel = new wxPanel( this, -1, wxDefaultPosition, wxDefaultSize  );

    m_notebook = new wxNotebook( m_panel, -1 );




//-----------------------------------------------------------
// First page: this contains a wxTextCtrl inside a wxPanel.
// the Idea is to be able to disable the wxTextCtrl (and 
// anything else in the wxPanel) with the checkbox.


    wxPanel *page1 = new wxPanel( m_notebook );
    m_cntl_panel = new wxPanel( page1 ); 

    wxSizer *m_sizer_box = new wxBoxSizer(wxVERTICAL );




    m_txt = new wxTextCtrl( m_cntl_panel, -1, _T("test"),
				wxDefaultPosition, wxDefaultSize,
				wxTE_PROCESS_ENTER );


    m_sizer_box->Add( m_txt, 1, wxALL, 5 );


    m_cntl_panel->SetAutoLayout(true);
    m_cntl_panel->SetSizer( m_sizer_box);


    wxSizer *sizer1 = new wxBoxSizer(wxHORIZONTAL);

    sizer1->Add( m_cntl_panel, 1, wxALL, 2 );
    wxCheckBox *cb = new wxCheckBox( page1, -1, _T(""));
    cb->SetValue(true);

    sizer1->Add( cb, 0, wxALIGN_CENTRE_VERTICAL | wxALL, 2 );
    page1->SetSizer( sizer1);

//-----------------------------------------------------------
// Second page
//

    wxPanel *page2 = new wxPanel( m_notebook );


    wxSizer *sizer2 = new wxBoxSizer(wxVERTICAL);
    wxStaticText *txt2 = new wxStaticText( page2, 
				-1, 
				_T("First Page") 
			);
    sizer2->Add( txt2, 0, wxEXPAND, 0 );
    page2->SetSizer( sizer2 );

//-----------------------------------------------------------

    m_notebook->AddPage( page1, _T("Page1"), FALSE, -1 );
    m_notebook->AddPage( page2, _T("Page2"), FALSE, -1 );

    m_sizerFrame->Add( m_notebook, 1, wxGROW | wxALL, 2 );

    m_panel->SetAutoLayout(true);
    m_panel->SetSizer(m_sizerFrame);


    Centre(wxBOTH);

}

MyFrame::~MyFrame()
{

}

void MyFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
void MyFrame::OnCheck(wxCommandEvent& event)
{
	bool state = event.IsChecked();

	m_cntl_panel->Enable(state); 
	
}


 	  	 
