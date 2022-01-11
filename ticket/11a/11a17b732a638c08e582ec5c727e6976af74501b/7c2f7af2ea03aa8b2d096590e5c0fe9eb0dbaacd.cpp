#include <wx/app.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialog
///////////////////////////////////////////////////////////////////////////////
class GUIDialog : public wxDialog
{
private:

protected:
    wxStaticText* m_staticText2;
    wxStaticText* m_staticText3;

    public:
    GUIDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("wxWidgets Application Template"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE )
     : wxDialog( parent, id, title, pos, size, style )
    {
        this->SetSizeHints( wxDefaultSize, wxDefaultSize );

        wxBoxSizer* bSizer1;
        bSizer1 = new wxBoxSizer( wxHORIZONTAL );

        m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Only files/directories that pass filtering will be selected for synchronization. The filter will be applied to the name relative(!) to the base synchronization directories."), wxDefaultPosition, wxDefaultSize, 0 );
        m_staticText2->Wrap( 300 );
        bSizer1->Add( m_staticText2, 0, wxALL|wxEXPAND, 5 );

        m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Только файлы/папки, которые проходят фильтрацию будут отобраны для синхронизации. Фильтр будет применяться ко всем именам, относящимся к основным синхронизируемым папкам."), wxDefaultPosition, wxDefaultSize, 0 );
        m_staticText3->Wrap( 300 );
        bSizer1->Add( m_staticText3, 0, wxALL|wxEXPAND, 5 );

        this->SetSizer( bSizer1 );
        this->Layout();
        bSizer1->Fit( this );

        // Connect Events
        this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIDialog::OnClose ) );
    }


    virtual void OnClose(wxCloseEvent& event)
    {
        Destroy();
    }

};



class lang_testApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        GUIDialog* dlg = new GUIDialog(0L);
        dlg->Show();
        return true;
    }
};

IMPLEMENT_APP(lang_testApp);
