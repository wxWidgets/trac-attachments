#include <wx/wx.h>
#include <wx/odcombo.h>
#include <fstream>

class ComboBoxOwner : public wxOwnerDrawnComboBox 
{
	// Operations
protected:
	virtual void OnDrawItem (wxDC &dc, const wxRect &rect, int item, int flags) const {}
	virtual wxCoord OnMeasureItem (size_t item) const {return wxCoord(20);}
	virtual wxCoord OnMeasureItemWidth (size_t item) const {return -1;}

	// Construction/Destruction
public:
	ComboBoxOwner() {}
	ComboBoxOwner(wxWindow *pParent)
		: wxOwnerDrawnComboBox(pParent, wxID_ANY, "Dialog", wxDefaultPosition, wxDefaultSize, wxArrayString(), 0)
	{
	}

	DECLARE_DYNAMIC_CLASS(ComboBoxOwner)
};

IMPLEMENT_DYNAMIC_CLASS(ComboBoxOwner, wxOwnerDrawnComboBox)

class CustomDialog : public wxDialog
{
	bool m_Run;
public:
	CustomDialog(wxWindow *pParent)
		: wxDialog(pParent, wxID_ANY, "Dialog"), m_Run(false)
	{
		wxBoxSizer *p_sizer = new wxBoxSizer(wxVERTICAL);
		p_sizer->Add(new ComboBoxOwner(this));
		p_sizer->Add(new wxButton(this, wxID_ANY, "Close with this button ONLY"));
		SetSizer(p_sizer);
	}

	void RunAsModal()
	{
		m_Run = true;
		Show();
		while(m_Run)
		{
			if(wxApp::GetInstance()->Pending())
				wxApp::GetInstance()->Dispatch();
			else
				wxMilliSleep(10);
		}
	}

	void on_button(wxCommandEvent &)
	{
		m_Run = false;
	}

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(CustomDialog, wxDialog)
	EVT_BUTTON(wxID_ANY, CustomDialog::on_button)
END_EVENT_TABLE()

class WidgetsFrame : public wxFrame
{
public:
    // ctor(s) and dtor
    WidgetsFrame(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title)
	{
		wxBoxSizer *p_sizer = new wxBoxSizer(wxHORIZONTAL);
		p_sizer->Add(new wxButton(this, wxID_ANY, "Run"));
	}

	void on_button(wxCommandEvent &)
	{
		// Show dialog
		CustomDialog(NULL).RunAsModal();
	}

	void on_quit(wxCloseEvent &)
	{
		Destroy();
	}

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(WidgetsFrame, wxFrame)
	EVT_BUTTON(wxID_ANY, WidgetsFrame::on_button)
	EVT_CLOSE(WidgetsFrame::on_quit)
END_EVENT_TABLE()


class WidgetsApp : public wxApp
{
	std::ofstream m_Log;
public:
    virtual bool OnInit()
	{
		m_Log.open("out.log");
		wxLog* logger = new wxLogStream(&m_Log);
		wxLog::SetActiveTarget(logger);
		if(!wxApp::OnInit())
			return false;
		wxFrame *frame = new WidgetsFrame("Frame");
		frame->Show();

		return true;

	}
};

IMPLEMENT_APP(WidgetsApp)
