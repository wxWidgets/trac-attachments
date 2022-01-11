// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/dataview.h>

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnItemSelected(wxDataViewEvent& event);
    wxDECLARE_EVENT_TABLE();
private:
    wxDataViewListCtrl * m_dtv;
};
enum
{
    ID_Hello = 1,
    ID_DTV
};
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello,   MyFrame::OnHello)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_DATAVIEW_ITEM_VALUE_CHANGED(ID_DTV, MyFrame::OnItemSelected)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );
    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );

    wxPanel *p = new wxPanel(this, wxID_ANY);

    wxFlexGridSizer * fgs = new wxFlexGridSizer(1, 1, 0, 0);
    fgs->AddGrowableRow(0);
    fgs->AddGrowableCol(0);

    m_dtv = new wxDataViewListCtrl(p, ID_DTV);
    m_dtv->AppendTextColumn("id", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER, wxDATAVIEW_COL_RESIZABLE);
    wxArrayString choices;
    for(long i = 0; i < 10; i++)
        choices.Add(wxString::Format("item %ld", i));

    wxDataViewChoiceByIndexRenderer * renderer = new wxDataViewChoiceByIndexRenderer(choices, wxDATAVIEW_CELL_EDITABLE, wxDVR_DEFAULT_ALIGNMENT);
    
    wxDataViewColumn * choiceCol = new wxDataViewColumn("Choices", renderer, 1, wxDVC_DEFAULT_WIDTH, wxALIGN_CENTER, wxDATAVIEW_COL_RESIZABLE);
    m_dtv->AppendColumn(choiceCol);

    fgs->Add(m_dtv, 0, wxEXPAND);
    p->SetSizer(fgs);


    wxVector<wxVariant> data;
    for(long i = 0; i < 10; i++)
    {
        data.clear();
        data.push_back(wxVariant(choices[i]));
        data.push_back(wxVariant(i));
        m_dtv->AppendItem(data, (wxUIntPtr) 0);
    }
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
                  "About Hello World", wxOK | wxICON_INFORMATION );
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
void MyFrame::OnItemSelected(wxDataViewEvent& event)
{
    wxVariant id;
    wxDataViewItem item = event.GetItem();
    if(item.IsOk())
    {
        // Change the value of the first column according to the user-selected row 
        wxDataViewChoiceByIndexRenderer * renderer = wxDynamicCast(m_dtv->GetColumn(1)->GetRenderer(), wxDataViewChoiceByIndexRenderer);
        if(renderer != nullptr)
        {
            m_dtv->GetStore()->GetValue(id, item, 1);
            m_dtv->GetStore()->SetValue(renderer->GetChoice(id.GetInteger()), item, 0);
        }
    }
}

