#include <wx/wx.h>
enum
{
	Menu_File_Quit = wxID_HIGHEST,
	Menu_File_About,
	ID_MY_LIST
};

class MyApp : public wxApp
{
	public:
		virtual bool OnInit();
};

class MyFrame : public wxFrame
{
	public:
		MyFrame( const wxString& title, const wxPoint& pos, const wxSize& pos );
		void OnQuit( wxCommandEvent& event );
		void OnAbout( wxCommandEvent& event );
		void EventItemSelected(wxListEvent& event);
		void EventItemDeSelected(wxListEvent& event);
	private:

		wxListCtrl* mylist;
		DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(MyFrame,wxFrame)
	EVT_MENU(Menu_File_Quit, MyFrame::OnQuit)
	EVT_MENU(Menu_File_About, MyFrame::OnAbout)
	EVT_LIST_ITEM_SELECTED(ID_MY_LIST,MyFrame::EventItemSelected)
	EVT_LIST_ITEM_DESELECTED(ID_MY_LIST,MyFrame::EventItemDeSelected)
END_EVENT_TABLE()


IMPLEMENT_APP(MyApp)
	

bool MyApp::OnInit()
{
 MyFrame *frame = new MyFrame( wxT( "Hello World" ), wxPoint(50,50), wxSize(450,340) ); 
 frame->Show(TRUE);
 SetTopWindow(frame);
 return TRUE;
} 

MyFrame::MyFrame( const wxString& title, const wxPoint& pos, const wxSize& size ): wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
 wxMenu *menuFile = new wxMenu;
 menuFile->Append( Menu_File_About, wxT( "&About..." ) );
 menuFile->AppendSeparator();
 menuFile->Append( Menu_File_Quit, wxT( "E&xit" ) );
 wxMenuBar *menuBar = new wxMenuBar;
 menuBar->Append( menuFile, wxT( "&File" ) );
 SetMenuBar(menuBar);

 mylist=new wxListCtrl(this,ID_MY_LIST,wxDefaultPosition,wxDefaultSize,wxLC_REPORT/*|wxLC_VIRTUAL*/);
 mylist->InsertColumn(0,wxT("col1"));
 //mylist->SetItemCount(5);
 mylist->InsertItem(0,wxT("one"));
 mylist->InsertItem(1,wxT("two"));
 mylist->InsertItem(2,wxT("three"));
}



void MyFrame::OnQuit( wxCommandEvent& WXUNUSED( event ) )
{
 Close(TRUE);
}

static int s;
static int d;

void MyFrame::OnAbout( wxCommandEvent& WXUNUSED( event ) )
{
 wxMessageBox(wxString::Format(wxT("Sel->%d, desel->%d"),s,d));
}

void MyFrame::EventItemSelected(wxListEvent& event)
{
 s++;
}

void MyFrame::EventItemDeSelected(wxListEvent& event)
{
 d++;
}



 	  	 
