

#include <wx/propgrid/propgrid.h>

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/stattext.h>

class wxt16768App : public wxApp
{
    public:
        virtual bool OnInit();
};


IMPLEMENT_APP(wxt16768App);

class wxt16768_frame: public wxFrame
{
    public:
        wxt16768_frame(wxFrame *frame, const wxString& title);

};

wxt16768_frame::wxt16768_frame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{

// Create prop grid with three items
    wxPropertyGrid * pg = new wxPropertyGrid( this, -1, wxPoint( 5,5), wxSize(300,70) );
    pg->Append(  new wxStringProperty( "A", wxPG_LABEL, "av") ) ;
    pg->Append(  new wxStringProperty( "B", wxPG_LABEL, "bv") ) ;
    pg->Append(  new wxStringProperty( "C", wxPG_LABEL, "cv") ) ;

// iterate over items
    wxString msg1;
    wxPropertyGridIterator it;
    for ( it = pg->GetIterator( ); !it.AtEnd();      it-- )
    {
        // add item label and value to string
        wxPGProperty* p = *it;
        msg1 += p->GetLabel() + " : " + p->GetValueAsString() + "\n";
    }

    wxString msg2;
    for ( it = pg->GetIterator(wxPG_ITERATE_DEFAULT, wxBOTTOM ); !it.AtEnd();      it-- )
    {
        // add item label and value to string
        wxPGProperty* p = *it;
        msg2 += p->GetLabel(   ) + " : " + p->GetValueAsString() + "\n";
    }

    new wxStaticText( this,-1, msg1 + " ( default ) ",
                      wxPoint( 5,100), wxSize(-1,-1));
    new wxStaticText( this,-1, msg2 + " ( bottom ) ",
                      wxPoint( 200,100), wxSize(-1,-1));

}

bool wxt16768App::OnInit()
{
    wxt16768_frame* frame = new wxt16768_frame(0L, _("wxWidgets Application Template"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();

    return true;
}

