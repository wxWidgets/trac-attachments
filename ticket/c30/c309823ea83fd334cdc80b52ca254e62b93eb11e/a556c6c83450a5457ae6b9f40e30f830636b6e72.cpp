/*
 *	wxEventFixModule (needs a better name) allows message handling to continute while a menu
 *  is being shown - ie, to continue processing messages from a worker thread.
 * 
 *  Code originally by Jason W. from wx-dev, reworked into a wxModule by Chris Mellon
 */




#if defined(__WXMSW__)
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
//end WxWin includes

#include "wx/module.h"



class wxEventFixModule : public wxModule {
public:
	//base class virtuals
	virtual bool OnInit() {
		wxEventFixModule::s_hMsgHookProc = SetWindowsHookEx(
			WH_GETMESSAGE,
			&wxEventFixModule::MsgHookProc,
			NULL,
			GetCurrentThreadId());
			wxLogDebug(_T("Loaded event fix module"));
			return true;
	};
	virtual void OnExit() {
		UnhookWindowsHookEx(wxEventFixModule::s_hMsgHookProc);

	};
	static LRESULT CALLBACK MsgHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
		MSG *msg = (MSG*)lParam;
		switch (msg->message)
		{
        case WM_NULL:
            static bool bInHookProc = false;
            if (!bInHookProc)
            {
                bInHookProc = true;
                wxTheApp->ProcessPendingEvents();
                bInHookProc = false;
            }
            break;
		}
		return CallNextHookEx(wxEventFixModule::s_hMsgHookProc, nCode, wParam, lParam);
	};
private:
	static HHOOK s_hMsgHookProc;
DECLARE_DYNAMIC_CLASS(wxEventFixModule)
};
HHOOK wxEventFixModule::s_hMsgHookProc = 0;

IMPLEMENT_DYNAMIC_CLASS(wxEventFixModule, wxModule)
#endif	//def __WXMSW__
 	  	 
