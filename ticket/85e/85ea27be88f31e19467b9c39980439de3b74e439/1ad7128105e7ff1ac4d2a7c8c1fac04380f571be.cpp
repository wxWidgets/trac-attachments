//
// file name: fonttest.cpp
//
//   purpose: Demonstration of striked fonts
//

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/fontenum.h>
#include <wx/spinctrl.h>


class MyApp: public wxApp
{
    virtual bool OnInit();
};

class FontComboBox: public wxComboBox
{
public:
    FontComboBox(wxWindow* parent, wxWindowID id);
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void OnChangeFont(wxCommandEvent& event);
    void OnSpinChangeFont(wxSpinEvent& event);

    void DoChangeFont();

private:
    wxTextCtrl *m_TextSample;
    wxCheckBox *m_CheckBold;
    wxCheckBox *m_CheckItalic;
    wxCheckBox *m_CheckUnderline;
    wxCheckBox *m_CheckStrikethrough;
    wxStaticText *m_LabelFont;
    FontComboBox *m_FontComboBox;
    wxStaticText *m_LabelSize;
    wxSpinCtrl *m_SpinSize;
    wxButton *m_ButtonChangeFont;

    DECLARE_EVENT_TABLE()
};

enum
{
    ID_Quit = 1,
    ID_About,
    ID_TextSample,
    ID_CheckBold,
    ID_CheckItalic,
    ID_CheckUnderline,
    ID_CheckStrikethrough,
    ID_FontComboBox,
    ID_SpinSize,
    ID_ButtonChangeFont
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Quit,  MyFrame::OnQuit)
    EVT_MENU(ID_About, MyFrame::OnAbout)
    EVT_BUTTON(ID_ButtonChangeFont, MyFrame::OnChangeFont)
    EVT_CHECKBOX(ID_CheckBold, MyFrame::OnChangeFont)
    EVT_CHECKBOX(ID_CheckItalic, MyFrame::OnChangeFont)
    EVT_CHECKBOX(ID_CheckUnderline, MyFrame::OnChangeFont)
    EVT_CHECKBOX(ID_CheckStrikethrough, MyFrame::OnChangeFont)
    EVT_COMBOBOX(ID_FontComboBox, MyFrame::OnChangeFont)
    EVT_SPINCTRL(ID_SpinSize, MyFrame::OnSpinChangeFont)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50,50), wxSize(450,340) );
    frame->Show( true );
    SetTopWindow( frame );
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;

    menuFile->Append( ID_About, "&About..." );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, "E&xit" );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );

    wxBoxSizer *boxSizer1 = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer *boxSizer2 = new wxBoxSizer( wxHORIZONTAL );
    wxBoxSizer *boxSizer3 = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer *boxSizer4 = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer *boxSizer5 = new wxBoxSizer( wxVERTICAL );

    m_TextSample = new wxTextCtrl( this, ID_TextSample, "Hello World!" );
    m_TextSample->SetWindowStyleFlag( wxTE_CENTER );

    m_CheckBold = new wxCheckBox( this, ID_CheckBold, "Bold" );
    m_CheckItalic = new wxCheckBox( this, ID_CheckItalic, "Italic" );
    m_CheckUnderline = new wxCheckBox( this, ID_CheckUnderline, "Underline" );
    m_CheckStrikethrough = new wxCheckBox( this, ID_CheckStrikethrough, "Strikethrough" );

    m_LabelFont = new wxStaticText( this, -1, "Font:" );
    m_FontComboBox = new FontComboBox( this, ID_FontComboBox );
    m_FontComboBox->SetStringSelection("Arial");
    m_LabelSize = new wxStaticText( this, -1, "Size:" );
    m_SpinSize = new wxSpinCtrl( this, ID_SpinSize );
    m_SpinSize->SetMin( 8 );
    m_SpinSize->SetMax( 48 );
    m_SpinSize->SetValue( 20 );

    m_ButtonChangeFont = new wxButton( this, ID_ButtonChangeFont, "Change Font" );

    boxSizer5->AddStretchSpacer();
    boxSizer5->Add(m_ButtonChangeFont, 0, wxGROW | wxALL, 5 );

    boxSizer4->Add(m_LabelFont, 0, wxALL, 5 );
    boxSizer4->Add(m_FontComboBox, 1, wxGROW | wxALL, 5 );
    boxSizer4->Add(m_LabelSize, 0, wxALL, 5 );
    boxSizer4->Add(m_SpinSize, 0, wxALL, 5 );

    boxSizer3->Add(m_CheckBold, 0, wxALL, 5 );
    boxSizer3->Add(m_CheckItalic, 0, wxALL, 5 );
    boxSizer3->Add(m_CheckUnderline, 0, wxALL, 5 );
    boxSizer3->Add(m_CheckStrikethrough, 0, wxALL, 5 );

    boxSizer2->Add(boxSizer3, 0, wxALL, 5 );
    boxSizer2->Add(boxSizer4, 1, wxGROW | wxALL, 5 );
    boxSizer2->Add(boxSizer5, 1, wxGROW | wxALL, 5 );

    boxSizer1->Add( m_TextSample, 1, wxGROW | wxALL, 5 );
    boxSizer1->Add( boxSizer2, 0, wxALL, 5 );

    SetSizer( boxSizer1 );

    DoChangeFont();
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close( true );
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox( "This is a wxWidgets' striked font demonstration.",
                  "About ...", wxOK | wxICON_INFORMATION );
}

class FontEnumeratorImplementation: public wxFontEnumerator
{
public:
    FontEnumeratorImplementation(FontComboBox *FontComboBox)
        { m_FontComboBox = FontComboBox; }

private:
    virtual bool OnFacename(const wxString& font)
        { m_FontComboBox->Append( font ); return true; }

    FontComboBox *m_FontComboBox;
};

FontComboBox::FontComboBox(wxWindow *parent, wxWindowID id)
        : wxComboBox(parent, id, wxEmptyString,
                    wxDefaultPosition, wxDefaultSize, 0, NULL,
                    wxCB_READONLY | wxCB_SORT)
{
    FontEnumeratorImplementation fei(this);

    fei.EnumerateFacenames();
}

void MyFrame::DoChangeFont()
{
    wxFont font(
        m_SpinSize->GetValue(),
        wxFONTFAMILY_DEFAULT,
        (m_CheckBold->GetValue() ? wxFONTFLAG_BOLD : 0) |
        (m_CheckItalic->GetValue() ? wxFONTFLAG_ITALIC : 0) |
        (m_CheckUnderline->GetValue() ? wxFONTFLAG_UNDERLINED : 0) |
        (m_CheckStrikethrough->GetValue() ? wxFONTFLAG_STRIKETHROUGH : 0),
        m_FontComboBox->GetValue() );

    m_TextSample->SetFont(font);
}

void MyFrame::OnChangeFont(wxCommandEvent&)
{
    DoChangeFont();
}

void MyFrame::OnSpinChangeFont(wxSpinEvent&)
{
    DoChangeFont();
}
