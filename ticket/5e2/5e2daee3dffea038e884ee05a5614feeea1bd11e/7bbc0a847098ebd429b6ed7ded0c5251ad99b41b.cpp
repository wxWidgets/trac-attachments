#define UNICODE
#define _UNICODE

#define ID_LISTACLIENTES 50
#include <wx/app.h>
#include <wx/image.h>
#include <wx/dataview.h>
#include <wx/frame.h>

class MyApp : public wxApp
{
    public:
        virtual bool OnInit();
};

IMPLEMENT_APP(MyApp);

class MForm: public wxFrame
{
public:
    
    MForm(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    wxDataViewListCtrl* clientList;

};

bool MyApp::OnInit()
{
    //AppInitialize
    bool wxsOK = true;
    if ( wxsOK )
    {
        MForm* Frame = new MForm(NULL);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    
    return wxsOK;

}

MForm::MForm(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    Create(parent, wxID_ANY, "Register");
    SetClientSize(wxSize(950,650));
    SetMinSize(wxSize(400,300));
    clientList = new wxDataViewListCtrl(this, ID_LISTACLIENTES, wxPoint(0,26), wxSize(588,328),wxDV_ROW_LINES);
	
    clientList->AppendTextColumn(L"NAME");
    clientList->AppendTextColumn(L"PASSPORT");
    clientList->AppendTextColumn(L"ADDRESS");
    clientList->AppendTextColumn(L"ZIP CODE");
	clientList->AppendTextColumn(L"CITY");
    
    //FILL WITH DATA
    for(int i=0;i<30;i++){
        wxVector<wxVariant> data;
        data.push_back( wxString::Format("%d",i));
        data.push_back( "items");
        data.push_back( "items");
        data.push_back( "items");
        data.push_back( "items");
        clientList->AppendItem( data );
    }
    for(int i=0;i<clientList->GetColumnCount();i++){ 
        clientList->GetColumn(i)->SetSortable(true);
        //clientList->GetColumn(i)->SetResizeable(false); //tried to see if making the columns not resizeable would solve the problem, but got segmentation fault
    }

}

