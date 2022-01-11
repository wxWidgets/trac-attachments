/*!
 * \file LayoutProblem.cpp
 * \author Elias Gerber <egerber@gmx.net>
 * \date 19.05.2013
 * 
 * Demo: Clicking on the Button will set a longer Text on the wxStaticText.
 * After calling Layout() the last two CheckBox look "corrupt".
 * If you call Refresh() manually after calling Layout() things are correct.
 */ 

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#   pragma hdrstop
#endif

#ifndef WX_PRECOMP
#   include "wx/wx.h"
#endif

// Own header
#include "LayoutProblem.h"

IMPLEMENT_APP(LayoutProblem)


// Implementation
// --------------
bool LayoutProblem::OnInit()
{
	wxFrame* pFrame = new wxFrame(NULL, wxID_ANY, L"MyFrame");

	wxSizer* pFrameSizer = new wxBoxSizer(wxVERTICAL);
	pFrame->SetSizer(pFrameSizer);

	m_pPanel = new wxPanel(pFrame, wxID_ANY);
	wxSizer* pPanelSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pPanel->SetSizer(pPanelSizer);
	
	m_pBtn1 = new wxButton(m_pPanel, wxID_ANY, L"ClickMe");
	m_pLbl1 = new wxStaticText(m_pPanel, wxID_ANY, "Short Text");

	wxCheckBox* pCheck1 = new wxCheckBox(m_pPanel, wxID_ANY, L"CheckBox1");
	wxCheckBox* pCheck2 = new wxCheckBox(m_pPanel, wxID_ANY, L"CheckBox2");
	wxCheckBox* pCheck3 = new wxCheckBox(m_pPanel, wxID_ANY, L"CheckBox3");
	wxCheckBox* pCheck4 = new wxCheckBox(m_pPanel, wxID_ANY, L"CheckBox4");
	wxCheckBox* pCheck5 = new wxCheckBox(m_pPanel, wxID_ANY, L"CheckBox5");

	pPanelSizer->Add(m_pBtn1, 0, wxALL, 5);
	pPanelSizer->Add(m_pLbl1, 0, wxALL, 5);
	pPanelSizer->Add(pCheck1, 0, wxALL, 5);
	pPanelSizer->Add(pCheck2, 0, wxALL, 5);
	pPanelSizer->Add(pCheck3, 0, wxALL, 5);
	pPanelSizer->Add(pCheck4, 0, wxALL, 5);
	pPanelSizer->Add(pCheck5, 0, wxALL, 5);

	pFrameSizer->Add(m_pPanel, 1, wxEXPAND|wxALL, 5);
	
	Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LayoutProblem::OnButton1) );
	
	pFrame->SetSize(850, 100);
	pFrame->Show(true);

	return true;

}


void LayoutProblem::OnButton1(wxCommandEvent& event)
{
	m_pLbl1->SetLabel("A very very long text we set here");
	m_pPanel->Layout();
	
	// Here is an extra refresh needed:
//	m_pPanel->Refresh();
}

