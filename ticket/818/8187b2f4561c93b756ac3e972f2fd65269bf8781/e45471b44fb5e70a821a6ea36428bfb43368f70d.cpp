#include "wx/wx.h"
#include "wx/aui/tabmdi.h"

class Frame: public wxAuiMDIParentFrame {
public:
	void OnClose(wxCloseEvent& event) {
		Close();
	}
	Frame():wxAuiMDIParentFrame(0, wxID_ANY, "Parent") {
		auto menu_file = new wxMenu();
		menu_file->Append(wxID_EXIT, wxT("E&xit"));
		
		auto menubar = new wxMenuBar();
		menubar->Append(menu_file, wxT("&File"));
		SetMenuBar(menubar);
		
		auto child = new wxAuiMDIChildFrame(this, wxID_ANY, "Child");
		child->SetSizer(new wxBoxSizer(wxVERTICAL));
		child->GetSizer()->Add(new wxTextCtrl(child, wxID_ANY));
		
		Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCloseEventHandler(Frame::OnClose));
		Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(Frame::OnClose));
	}
};

class Test: public wxApp {
public:
	bool OnInit() {
		wxApp::OnInit();
		
		auto parent = new Frame();
		parent->Show();
		SetTopWindow(parent);

		return true;
	}
};

IMPLEMENT_APP(Test)