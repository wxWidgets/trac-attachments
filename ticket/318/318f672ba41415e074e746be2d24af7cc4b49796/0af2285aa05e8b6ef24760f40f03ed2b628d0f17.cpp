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
private:
    void OnResize(wxSizeEvent& event);
};

bool MyApp::OnInit()
{
    //AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
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
        data.push_back( "items");
        data.push_back( "items");
        data.push_back( "items");
        data.push_back( "items");
        data.push_back( "items");
        clientList->AppendItem( data );
    }
    
    Connect(this->GetId(),wxEVT_SIZE,(wxObjectEventFunction)&MForm::OnResize);
}

void MForm::OnResize(wxSizeEvent& event)
{
	int listHeight,listWidth;
    GetClientSize(&listWidth,&listHeight);
    listHeight-=26;
    //clientList->Freeze();
	clientList->GetColumn(0)->SetWidth(int(0.20*listWidth-2));
    clientList->GetColumn(1)->SetWidth(int(0.15*listWidth-3));
    clientList->GetColumn(2)->SetWidth(int(0.07*listWidth-3));
    clientList->GetColumn(3)->SetWidth(int(0.20*listWidth-3));
    clientList->GetColumn(4)->SetWidth(int(0.10*listWidth-3));

	clientList->SetSize(listWidth,listHeight);
    //clientList->Thaw();
    clientList->Refresh();
    clientList->Update();
    event.Skip();
}
