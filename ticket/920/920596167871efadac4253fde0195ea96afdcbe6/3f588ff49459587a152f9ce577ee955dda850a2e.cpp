/*
 * Copyright (c) 2007 Hot Neuron LLC.  All Rights Reserved.
 *
 * $Id: clustify.cpp,v 1.15 2007/12/17 07:51:32 billd Exp $
 */

#include <wx/wx.h>

class TestApp : public wxApp
	{
	virtual bool OnInit();
	};

class TestFrame : public wxFrame
	{
	public:
		TestFrame() : wxFrame(NULL, wxID_ANY, wxT("Test"), wxDefaultPosition, wxSize(400, 200))
			{
			wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);
			wxPanel *panel = new wxPanel(this, wxID_ANY);
			top_sizer->Add(panel, 1, wxEXPAND);
			wxBoxSizer *panel_sizer = new wxBoxSizer(wxVERTICAL);
	
			wxStaticText *text1 = new wxStaticText(panel, wxID_ANY, wxT("This is the first of three lines."));
			panel_sizer->Add(text1, 0, wxEXPAND);
			text1->Wrap(200);
	
			wxStaticText *text2 = new wxStaticText(panel, wxID_ANY, wxT("» Second line - invisible on GTK."));
			panel_sizer->Add(text2, 0, wxEXPAND);
			text2->Wrap(200);  // BUG - on GTK this causes the text to disappear because of the bad character

			wxStaticText *text3 = new wxStaticText(panel, wxID_ANY, wxT("This is the third line."));
			panel_sizer->Add(text3, 0, wxEXPAND);
			text3->Wrap(200);
	
			panel->SetSizer(panel_sizer);
			SetSizer(top_sizer);
			}
	};


bool TestApp::OnInit()
	{
	TestFrame *frame = new TestFrame;
	frame->Show(true);

	return true;
	} 

IMPLEMENT_APP(TestApp)

 	  	 
