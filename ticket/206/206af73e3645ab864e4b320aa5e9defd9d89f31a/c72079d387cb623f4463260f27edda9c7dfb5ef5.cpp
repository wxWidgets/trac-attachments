#include <wx/wx.h>
#include <wx/intl.h>
#include <wx/filepicker.h>

#include <memory>

enum {
	ID_NONE = 6000,
	ID_BUTTON_CHECK
};

class MainWindow : public wxFrame
{
	wxDECLARE_EVENT_TABLE();

public:
	MainWindow()
		: wxFrame(NULL, wxID_ANY, "fp", wxDefaultPosition, wxSize(400, 320))
	{
		wxPanel *mainPanel = new wxPanel(this);
		wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

		m_filePicker = new wxFilePickerCtrl(mainPanel, wxID_ANY, wxGetHomeDir());		
		wxButton *check = new wxButton(mainPanel, ID_BUTTON_CHECK, wxT("Check"));
		
		mainSizer->Add(m_filePicker, 0, wxEXPAND|wxALL, 5);
		mainSizer->Add(check, 0, wxEXPAND|wxALL, 5);
		
		mainPanel->SetSizerAndFit(mainSizer);
	}

	void OnButton(wxCommandEvent &event)
	{
		const wxString path = m_filePicker->GetPath();
		
		wxLogMessage(path);
	}

private:
	wxFilePickerCtrl *m_filePicker;
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_BUTTON(ID_BUTTON_CHECK, MainWindow::OnButton)
wxEND_EVENT_TABLE()

class App : public wxApp
{
public:
	bool OnInit()
	{
		wxLocale locale(wxLANGUAGE_DEFAULT);

		MainWindow *window = new MainWindow;
		window->Show();
		window->Center();

		return true;
	}
};

wxIMPLEMENT_APP(App);
