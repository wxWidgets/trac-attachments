#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include <wx/wx.h>
#include <wx/app.h>

class wxCodeTestFrame: public wxFrame
{
    public:
       wxCodeTestFrame(wxFrame *frame, const wxString& title)
		: wxFrame(frame, -1, title)
			{
			#if wxUSE_MENUS
				// create a menu bar
				wxMenuBar* mbar = new wxMenuBar();
				wxMenu* fileMenu = new wxMenu(_T(""));
				fileMenu->Append(idMenuQuit, _("Execute"), _("Execute the Code"));
				mbar->Append(fileMenu, _("&File"));


				SetMenuBar(mbar);
			#endif // wxUSE_MENUS

			#if wxUSE_STATUSBAR
				// create a status bar with some information about the used wxWidgets version
				CreateStatusBar(2);
				SetStatusText(_("Hello Code::Blocks user!"),0);
			#endif // wxUSE_STATUSBAR

			char *bfr = reinterpret_cast<char*>(GetBin().GetData());
			printf( "wxMemoryBuffer after  return : 0x%02X \n", *bfr);
			}

        ~wxCodeTestFrame(){};

    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event){ Destroy();}
void OnCmd(wxCommandEvent& event){
	char *bfr = reinterpret_cast<char*>(GetBin().GetData());
	printf( "wxMemoryBuffer after  return : 0x%02X \n", *bfr);
}

wxMemoryBuffer GetBin(){
	wxMemoryBuffer memodata;
	char bfr = 0x31;
	memodata.AppendByte( bfr );
	char *bfrx = static_cast<char*>(memodata.GetData());
	printf( "wxMemoryBuffer before return : 0x%02X \n", *bfrx);
	return memodata;
	}

	DECLARE_EVENT_TABLE()
	};

BEGIN_EVENT_TABLE(wxCodeTestFrame, wxFrame)
    EVT_CLOSE(wxCodeTestFrame::OnClose)
    EVT_MENU(idMenuQuit, wxCodeTestFrame::OnCmd)
END_EVENT_TABLE()

class wxCodeTestApp : public wxApp
{
    public:
        virtual bool OnInit(){
			wxCodeTestFrame* frame = new wxCodeTestFrame(0L, _("wxWidgets Application Template"));

			frame->Show();

			return true;
			}
};

IMPLEMENT_APP(wxCodeTestApp);

