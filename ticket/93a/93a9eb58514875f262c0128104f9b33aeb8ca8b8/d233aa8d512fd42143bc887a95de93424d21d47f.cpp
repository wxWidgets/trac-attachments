/** \file
 * Rich Edit test.
 ******************************************************************************/

/****** INCLUDES *************************************************************/

#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>

/****** TYPES ****************************************************************/
class RichTest : public wxApp
{
public:
    virtual bool OnInit();
};

class TestFrame : public wxFrame 
{
protected:
    wxRichTextCtrl * m_richInfo;
	
    void OnTestClick( wxCommandEvent& event );

public:
    TestFrame( wxWindow* parent);
};

IMPLEMENT_APP(RichTest)

/****** MEMBER FUNCTIONS *******************************************************************/
TestFrame::TestFrame( wxWindow* parent) : wxFrame( parent, wxID_ANY, "Test", wxDefaultPosition, wxSize(200, 200))
{
    wxBoxSizer * bSizer1 = new wxBoxSizer( wxVERTICAL );

    wxPanel * panelMain = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );

    wxBoxSizer * bSizerMain = new wxBoxSizer( wxVERTICAL );

	wxButton * butTest = new wxButton( panelMain, wxID_ANY, wxT("Test"));
	bSizerMain->Add( butTest, 0, wxALL, 5 );

    m_richInfo = new wxRichTextCtrl( panelMain, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxHSCROLL|wxVSCROLL|wxWANTS_CHARS );
    bSizerMain->Add( m_richInfo, 2, wxEXPAND | wxALL, 5 );

    panelMain->SetSizer( bSizerMain );
    panelMain->Layout();
    bSizerMain->Fit( panelMain );

    bSizer1->Add( panelMain, 1, wxEXPAND, 5 );

    this->SetSizer( bSizer1 );
    this->Layout();
    this->Centre( wxBOTH );

	butTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestFrame::OnTestClick ), NULL, this );
}

void TestFrame::OnTestClick( wxCommandEvent& WXUNUSED(event) )
{
    m_richInfo->Clear();

    m_richInfo->BeginLeftIndent(100);
    m_richInfo->WriteText("This is some text\n");
    m_richInfo->EndLeftIndent();

    m_richInfo->WriteText(wxT("This is some text\n"));
}

bool RichTest::OnInit()
{
    // Init image handlers
    wxInitAllImageHandlers();

    // Create main frame
    TestFrame * testFrame = new TestFrame(NULL);
    testFrame->Show();
    SetTopWindow(testFrame);

    return true;
}


