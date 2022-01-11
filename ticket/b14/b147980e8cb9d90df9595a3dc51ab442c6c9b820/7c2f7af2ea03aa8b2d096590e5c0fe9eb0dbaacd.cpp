
#include <wx/wx.h>
#include <wx/vlbox.h>

class MyVListBox : public wxVListBox
{
	public:

	MyVListBox(wxWindow *parent, wxWindowID id = wxID_ANY):wxVListBox(parent, id, wxDefaultPosition, wxDefaultSize)
	{
	}
	
	void OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const
	{
	}
	
	wxCoord OnMeasureItem(size_t n) const
	{
		return 16;
	}
};

class MyFrame : public wxFrame
{
	public:

	MyFrame():wxFrame(NULL, wxID_ANY, _T("My frame"), wxDefaultPosition, wxDefaultSize)
	{
		new MyVListBox(this);

		Show();
	}
};

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

 	  	 
