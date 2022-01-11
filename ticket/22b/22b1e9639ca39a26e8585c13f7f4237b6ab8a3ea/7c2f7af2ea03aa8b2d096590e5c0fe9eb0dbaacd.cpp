
#include <wx/wx.h>

enum
{
	IDC_LISTBOX
};

class MyFrame : public wxFrame
{
	public:

	MyFrame():wxFrame(NULL, wxID_ANY, _T("My frame"), wxDefaultPosition, wxDefaultSize), m_listbox(NULL)
	{
		m_listbox = new wxListBox(this, IDC_LISTBOX, wxDefaultPosition, wxDefaultSize, 0, NULL,  wxLB_SORT|wxLB_ALWAYS_SB);

		for(int i = 0; i < 10; ++i) m_listbox->Append(_T("test"), (void*) new wxString(_T("It works")));

		Show();
	}
	
	void OnSelected(wxCommandEvent &event)
	{
		wxString *str = (wxString*)event.GetClientData();
	
		if (!str)
		{
			wxMessageBox(_T("Null pointer 1"));
		}

		int i = event.GetSelection();
	
		str = (wxString*)m_listbox->GetClientData(i);

		if (!str)
		{
			wxMessageBox(_T("Null pointer 2"));
			return;
		}
		
		wxMessageBox(*str);
	}
	
	protected:
	
	wxListBox *m_listbox;

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_LISTBOX(IDC_LISTBOX, MyFrame::OnSelected)
END_EVENT_TABLE()

class MyApp : public wxApp
{
	public:

	virtual bool OnInit()
	{
		SetTopWindow(new MyFrame());

		return true;
	}
};

IMPLEMENT_APP(MyApp)

 	  	 
