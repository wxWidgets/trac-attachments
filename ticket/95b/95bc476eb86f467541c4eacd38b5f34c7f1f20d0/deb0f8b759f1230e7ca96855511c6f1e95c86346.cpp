/////////////////////////////////////////////////////////////////////////////
// Name:        StartsWithProblem.cpp
// Purpose:     Based on Minimal wxWidgets sample to demonstrate problem
//              bug with repeated calls to wxString::StartsWith
// Author:      Scott Furry
// Created:     28Jun2007
//
// NOTE!!!!!
// NOTE!!!!!    (more for me when I look at this again)
// USE			-D_UNICODE  (undefined stdrup error if missing)
// REMOVE       -mwindows (DO NOT USE to see std::cout output)
// LINKING w/	-Wl,--enable-auto-import
// 				-Wl,--enable-runtime-pseudo-reloc
//              -lwxmsw28u
//				-lwxregexu (not necessarily needed for this demo)
/////////////////////////////////////////////////////////////////////////////
// ============================================================================
// declarations
// ============================================================================
// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/string.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <iostream>

	const wxChar* C_TEST_COND_ONE(wxT("@"));
	const wxChar* C_TEST_COND_TWO(wxT("#"));
	const wxChar* C_TEST_COND_THREE(wxT("$"));
	const wxChar* C_TEST_COND_FOUR(wxT("%"));

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
    void OnQuit(wxCommandEvent& event);
	void DemoBugWithwxString(wxCommandEvent& event);
	void DemoBugWithwxChar(wxCommandEvent& event);
private:
	wxButton *m_btnDemowxString;
	wxButton *m_btnDemowxChar;
    DECLARE_EVENT_TABLE()
};

// IDs for the controls and the menu commands
enum
{
	//Buttons to initiate Demonstration
	ID_BTN_DEMO_WXCHAR = 1002,
	ID_BTN_DEMO_WXSTRING = 1001,
    // menu items
    Minimal_Quit = wxID_EXIT,
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_BUTTON(ID_BTN_DEMO_WXCHAR,MyFrame::DemoBugWithwxChar)
	EVT_BUTTON(ID_BTN_DEMO_WXSTRING,MyFrame::DemoBugWithwxString)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================
bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;
    MyFrame *frame = new MyFrame(_T("StartsWith Bug Demonstration App"));
    frame->Show(true);
    return true;
}
// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------
// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
    
    //Create a button to initiate Demonstration
	m_btnDemowxString = new wxButton(this, ID_BTN_DEMO_WXSTRING, wxT("Demostrate\nStartsWith using\nwxString stored prefix"), wxPoint(100,100), wxSize(100,60), 0, wxDefaultValidator, wxT("m_btnDemowxString"));
	m_btnDemowxChar = new wxButton(this, ID_BTN_DEMO_WXCHAR, wxT("Demostrate\nStartsWith using\nwxChar stored prefix"), wxPoint(200,100), wxSize(100,60), 0, wxDefaultValidator, wxT("m_btnDemowxChar"));
#endif // wxUSE_MENUS
}
// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MyFrame::DemoBugWithwxString(wxCommandEvent& WXUNUSED(event))
{
	wxString SZ_TEST_COND_ONE(wxT("@"));
	wxString SZ_TEST_COND_TWO(wxT("#"));
	wxString SZ_TEST_COND_THREE(wxT("$"));
	wxString SZ_TEST_COND_FOUR(wxT("%"));

	bool bCondOne	= false;
	bool bCondTwo	= false;
	bool bCondThree = false;
	bool bCondFour  = false;
	
	wxString sMessage(wxT("Please Enter a string to be used for StartsWith compairison\n"));
	sMessage += wxT("The entered string is tested with StartsWith for the following four values: \n(stored as wxString)\n");
	sMessage += wxT("One  : ") + SZ_TEST_COND_ONE + wxT("\n");
	sMessage += wxT("Two  : ") + SZ_TEST_COND_TWO + wxT("\n");
	sMessage += wxT("Three: ") + SZ_TEST_COND_THREE + wxT("\n");
	sMessage += wxT("Four : ") + SZ_TEST_COND_FOUR + wxT("\n");
	wxString sCaption(wxT("StartsWith Demo Bug"));
	wxString sTrimmed(wxEmptyString);
	
	wxTextEntryDialog pEnterText(this, sMessage, sCaption, wxEmptyString, wxOK | wxCENTRE, wxDefaultPosition);
    if(pEnterText.ShowModal() == wxID_OK)
    {
		wxString sData = pEnterText.GetValue();
// ----------------------------------------------------------------------------
// AND THIS WORKS when using wxString.c_str() as "prefix" parameter
// ----------------------------------------------------------------------------
		bCondOne	= sData.StartsWith(SZ_TEST_COND_ONE.c_str(), &sTrimmed);
		bCondTwo	= sData.StartsWith(SZ_TEST_COND_TWO.c_str(), &sTrimmed);
		bCondThree	= sData.StartsWith(SZ_TEST_COND_THREE.c_str(), &sTrimmed);
		bCondFour	= sData.StartsWith(SZ_TEST_COND_FOUR.c_str(), &sTrimmed);
// ----------------------------------------------------------------------------
		std::cout << "Tests Results (wxString): " << bCondOne << "  " << bCondTwo << "  " << bCondThree << "  " << bCondFour << std::endl;
		std::cout << "Input String: " << sData.mb_str(wxConvUTF8) << std::endl;
		std::cout << "Trimmed Str: " << sTrimmed.mb_str(wxConvUTF8) << std::endl;

		sCaption = wxT("Results of testing");
		wxString sResultMsg(wxT("Results of testing: \n"));
		sResultMsg += wxT("Input String: \t");
		sResultMsg += sData;
		sResultMsg += wxT("\nCondition One   (") + SZ_TEST_COND_ONE + wxString::Format(wxT("): %d\n"), bCondOne);
		sResultMsg += wxT("Condition Two   (") + SZ_TEST_COND_TWO + wxString::Format(wxT("): %d\n"), bCondTwo);
		sResultMsg += wxT("Condition Three (") + SZ_TEST_COND_THREE + wxString::Format(wxT("): %d\n"), bCondThree);
		sResultMsg += wxT("Condition Four  (") + SZ_TEST_COND_FOUR + wxString::Format(wxT("): %d\n"), bCondFour);
		sResultMsg += wxT("Trimmed String\n(if StartsWith processed input): \n");
		sResultMsg += sTrimmed;
		wxMessageDialog pResult(this,sResultMsg,sCaption,wxOK | wxICON_EXCLAMATION);
		pResult.ShowModal();
	}
}

void MyFrame::DemoBugWithwxChar(wxCommandEvent& WXUNUSED(event))
{
	bool bCondOne	= false;
	bool bCondTwo	= false;
	bool bCondThree = false;
	bool bCondFour  = false;

	wxString sMessage(wxT("Please Enter a string to be used for StartsWith compairison\n"));
	sMessage += wxT("The entered string is tested with StartsWith for the following four values: \n(stored as const wxChar*)\n");
	sMessage += wxString::Format(wxT("One  : %c\n"),*C_TEST_COND_ONE);
	sMessage += wxString::Format(wxT("Two  : %c\n"),*C_TEST_COND_TWO);
	sMessage += wxString::Format(wxT("Three: %c\n"),*C_TEST_COND_THREE);
	sMessage += wxString::Format(wxT("Four : %c\n"),*C_TEST_COND_FOUR);

	wxString sCaption(wxT("StartsWith Demo Bug"));
	wxString sTrimmed(wxEmptyString);

	wxTextEntryDialog pEnterText(this, sMessage, sCaption, wxEmptyString, wxOK | wxCENTRE, wxDefaultPosition);
    if(pEnterText.ShowModal() == wxID_OK)
    {
		wxString sData = pEnterText.GetValue();
// ----------------------------------------------------------------------------
// AND THIS IS WHERE I THOUGHT THE PROBLEMS START!!!!
// conditions two through four were always returning FALSE regardless of
// the input string - possibly due to declaration of prefix
// ----------------------------------------------------------------------------
		bCondOne	= sData.StartsWith(C_TEST_COND_ONE, &sTrimmed);
		bCondTwo	= sData.StartsWith(C_TEST_COND_TWO, &sTrimmed);
		bCondThree	= sData.StartsWith(C_TEST_COND_THREE, &sTrimmed);
		bCondFour	= sData.StartsWith(C_TEST_COND_FOUR, &sTrimmed);
		std::cout << "Tests Results (wxChar): " << bCondOne << "  " << bCondTwo << "  " << bCondThree << "  " << bCondFour << std::endl;
		std::cout << "Input String: " << sData.mb_str(wxConvUTF8) << std::endl;
		std::cout << "Trimmed Str: " << sTrimmed.mb_str(wxConvUTF8) << std::endl;

		sCaption = wxT("Results of testing");
		wxString sResultMsg(wxT("Results of testing: \n"));
		sResultMsg += wxT("Input String: \t");
		sResultMsg += sData;
		sResultMsg += wxString::Format(wxT("\nCondition One   (%c): %d\n"),*C_TEST_COND_ONE, bCondOne);
		sResultMsg += wxString::Format(wxT("Condition Two   (%c): %d\n"),*C_TEST_COND_TWO, bCondTwo);
		sResultMsg += wxString::Format(wxT("Condition Three (%c): %d\n"),*C_TEST_COND_THREE, bCondThree);
		sResultMsg += wxString::Format(wxT("Condition Four  (%c): %d\n"),*C_TEST_COND_FOUR, bCondFour);
		sResultMsg += wxT("Trimmed String\n(if StartsWith processed input): \n");
		sResultMsg += sTrimmed;
		wxMessageDialog pResult(this,sResultMsg,sCaption,wxOK | wxICON_EXCLAMATION);
		pResult.ShowModal();
	}
}

 	  	 
