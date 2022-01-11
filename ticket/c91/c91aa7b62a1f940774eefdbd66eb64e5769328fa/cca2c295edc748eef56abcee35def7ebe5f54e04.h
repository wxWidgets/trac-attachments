#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <chrono>
#include "wx/wx.h"
#include "wx/tglbtn.h"
#include "wx/wupdlock.h"

using namespace std;
using namespace std::chrono;

#define newV new wxBoxSizer(wxVERTICAL)
#define newH new wxBoxSizer(wxHORIZONTAL)

class cMain : public wxFrame
{
public:
	cMain() : wxFrame(nullptr, wxID_ANY, wxT("Ja"), wxPoint(-1,-1), wxSize(1500,1000), wxSYSTEM_MENU|wxMINIMIZE_BOX|wxCLOSE_BOX|wxCAPTION|wxTAB_TRAVERSAL|wxCLIP_CHILDREN) {
		int buttons = 3;
		wxGridSizer *g = new wxGridSizer(buttons, buttons, 0, 0);
		g->SetMinSize(wxSize(800, 800));
		wxFlexGridSizer* fgMain = new wxFlexGridSizer( 2, 2, 0, 0 );
		wxBoxSizer *vLeft = newV; hGridPanel   = newH;
		wxBoxSizer *hTop  = newH; vPanelCommon = newV;
		hGridPanel->Add(g, 1, wxEXPAND, 0);
		hGridPanel->Add(vPanelCommon, 1, wxEXPAND, 0);
		
		fgMain->Add(new wxButton(this, 10000, wxEmptyString, wxPoint(0,0), wxSize(20,20)), 0, wxALL, 0);
		fgMain->Add(hTop, 0, wxALL, 0);
		fgMain->Add(vLeft, 0, wxALL, 0);

		for (int i = 0; i < 2; i++) {
			vPanel[i] = newV;
			vPanelCommon->Add(vPanel[i], 0, wxEXPAND, 0);
			vPanelCommon->Hide(vPanel[i]);
		}
	
		wxBoxSizer* P = vPanel[C = 0];
		wxFlexGridSizer *g0 = new wxFlexGridSizer(20, 15, 0, 0);
		add_building_table(g0, 20, 15);
		P->Add(g0, 0, wxTOP|wxLEFT, 15);

		P = vPanel[C = 1];
		wxFlexGridSizer *g1 = new wxFlexGridSizer(20, 15, 0, 0);
		add_building_table(g1, 20, 15);
		P->Add(g1, 0, wxTOP|wxLEFT, 15);

		fgMain->Add(hGridPanel, 1, wxEXPAND, 0);
	
		this->SetSizer(fgMain);

		update_panel();
	}
	~cMain() {};

public:
	int C = 0;
	wxBoxSizer *hGridPanel	= nullptr;
	wxBoxSizer *vPanelCommon = nullptr;
	wxBoxSizer *vPanel[2] = { 0 };
	
	void update_panel() {
		auto start = high_resolution_clock::now();
		///wxWindowUpdateLocker updater(this);
		vPanelCommon->Show(vPanel[C]);
		for (int i = 0; i < 2; i++) {
			if (i == C) continue;
			vPanelCommon->Hide(vPanel[i]);
		}
		vPanelCommon->Layout();
		this->SetTitle((to_string(duration_cast<microseconds>(high_resolution_clock::now() - start).count()/1000)  + "ms"));
	}

	void add_building_table(wxFlexGridSizer* g, int rows, int cols) {
		for (int j = 0; j < rows; j++) {
			for (int i = 0; i < cols; i++) {
				wxToggleButton* b = new wxToggleButton( this, wxID_ANY, to_string(rand()%10), wxDefaultPosition, wxSize(45,45), 0 );
				g->Add(b); b->Bind(wxEVT_TOGGLEBUTTON, &cMain::OnToggleTable, this);
			}
		}
	}

	void OnToggleTable(wxCommandEvent &evt) {
		wxToggleButton* b = (wxToggleButton*)wxWindow::FindWindowById(evt.GetId());
			 if (C == 0) C = 1;
		else if (C == 1) C = 0;
		update_panel();
	}

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
//	EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

class cApp : public wxApp {
public:
	cApp() {};
	~cApp() {};

private:
	cMain* m_main = nullptr;

public:
	virtual bool OnInit() {
		m_main = new cMain();
		m_main->Show();
		return true;
	};
};

wxIMPLEMENT_APP(cApp);