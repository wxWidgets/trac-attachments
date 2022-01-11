/////////////////////////////////////////////////////////////////////////////
// Name:        src/msw/fdrepdlg.cpp
// Purpose:     wxFindReplaceDialog class
// Author:      Markus Greither and Vadim Zeitlin
// Modified by:
// Created:     23/03/2001
// RCS-ID:
// Copyright:   (c) Markus Greither
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_FINDREPLDLG

#ifndef WX_PRECOMP
    #include "wx/intl.h"
    #include "wx/log.h"
#endif

#include "wx/msw/wrapcdlg.h"
#include "wx/fdrepdlg.h"

// ----------------------------------------------------------------------------
// externs
// ----------------------------------------------------------------------------

extern "C" WXDLLIMPEXP_BASE HINSTANCE wxGetInstance(void);

#ifdef __WXWINCE__
    extern WXDLLIMPEXP_CORE       wxChar *wxCanvasClassName;
#else
    extern WXDLLIMPEXP_CORE const wxChar *wxCanvasClassName;
#endif

// ----------------------------------------------------------------------------
// functions prototypes
// ----------------------------------------------------------------------------

LRESULT APIENTRY wxFindReplaceWindowProc(HWND hwnd, WXUINT nMsg,
                                         WPARAM wParam, LPARAM lParam);

UINT_PTR CALLBACK wxFindReplaceDialogHookProc(HWND hwnd,
                                              UINT uiMsg,
                                              WPARAM wParam,
                                              LPARAM lParam);

// ----------------------------------------------------------------------------
// wxWin macros
// ----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxFindReplaceDialog, wxDialog)

// ----------------------------------------------------------------------------
// wxFindReplaceDialogImpl: the internals of wxFindReplaceDialog
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxFindReplaceDialogImpl
{
public:
    wxFindReplaceDialogImpl(wxFindReplaceDialog *dialog, int flagsWX);
    ~wxFindReplaceDialogImpl();

    void InitFindWhat(const wxString& str);
    void InitReplaceWith(const wxString& str);

    static UINT GetFindDialogMessage() { return ms_msgFindDialog; }

    // only for passing to ::FindText or ::ReplaceText
    FINDREPLACE *GetPtrFindReplace() { return &m_findReplace; }

    // set/query the "closed by user" flag
    void SetClosedByUser() { m_wasClosedByUser = true; }
    bool WasClosedByUser() const { return m_wasClosedByUser; }

private:
    void InitString(const wxString& str, LPTSTR *ppStr, WORD *pLen);

    // the owner of the dialog (hidden window to get FINDMSGSTRING message)
    HWND m_hwndOwner;

    // the find replace data used by the dialog
    FINDREPLACE m_findReplace;

    // true if the user closed us, false otherwise
    bool m_wasClosedByUser;

    // registered Message for Dialog
    static UINT ms_msgFindDialog;

    DECLARE_NO_COPY_CLASS(wxFindReplaceDialogImpl)
};

UINT wxFindReplaceDialogImpl::ms_msgFindDialog = 0;

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// wxFindReplaceDialogImpl
// ----------------------------------------------------------------------------

wxFindReplaceDialogImpl::wxFindReplaceDialogImpl(wxFindReplaceDialog *dialog,
                                                 int flagsWX)
{
    // get the identifier for the find dialog message if we don't have it yet
    if ( !ms_msgFindDialog )
    {
        ms_msgFindDialog = ::RegisterWindowMessage(FINDMSGSTRING);

        if ( !ms_msgFindDialog )
        {
            wxLogLastError(_T("RegisterWindowMessage(FINDMSGSTRING)"));
        }
    }

    m_wasClosedByUser = false;


    // create hidden window for recieving FINDMSGSTRING message
    m_hwndOwner = ::CreateWindow
                    (
                        wxCanvasClassName,
                        NULL,
                        0, 0, 0, 0,
                        0,
                        (HWND)NULL,
                        (HMENU)NULL,
                        wxGetInstance(),
                        (LPVOID) NULL
                    );
    wxSetWindowProc(m_hwndOwner, wxFindReplaceWindowProc);

    //Now fill our FINDREPLACE structure
      
    wxZeroMemory(m_findReplace);

    // translate the flags: first the dialog creation flags

    // always set this to be able to set the title
    int flags = FR_ENABLEHOOK;

    int flagsDialog = dialog->GetWindowStyle();
    if ( flagsDialog & wxFR_NOMATCHCASE)
        flags |= FR_NOMATCHCASE;
    if ( flagsDialog & wxFR_NOWHOLEWORD)
        flags |= FR_NOWHOLEWORD;
    if ( flagsDialog & wxFR_NOUPDOWN)
        flags |= FR_NOUPDOWN;

    // and now the flags governing the initial values of the dialogs controls
    if ( flagsWX & wxFR_DOWN)
        flags |= FR_DOWN;
    if ( flagsWX & wxFR_MATCHCASE)
        flags |= FR_MATCHCASE;
    if ( flagsWX & wxFR_WHOLEWORD )
        flags |= FR_WHOLEWORD;

    m_findReplace.lStructSize = sizeof(FINDREPLACE);
    m_findReplace.hwndOwner = m_hwndOwner;
    m_findReplace.Flags = flags;

    m_findReplace.lCustData = (LPARAM)dialog;
    m_findReplace.lpfnHook = wxFindReplaceDialogHookProc;
}

void wxFindReplaceDialogImpl::InitString(const wxString& str,
                                         LPTSTR *ppStr, WORD *pLen)
{
    size_t len = str.length() + 1;
    if ( len < 80 )
    {
        // MSDN docs say that the buffer must be at least 80 chars
        len = 80;
    }

    *ppStr = new wxChar[len];
    wxStrcpy(*ppStr, str);
    *pLen = (WORD)len;
}

void wxFindReplaceDialogImpl::InitFindWhat(const wxString& str)
{
    InitString(str, &m_findReplace.lpstrFindWhat, &m_findReplace.wFindWhatLen);
}

void wxFindReplaceDialogImpl::InitReplaceWith(const wxString& str)
{
    InitString(str,
               &m_findReplace.lpstrReplaceWith,
               &m_findReplace.wReplaceWithLen);
}

wxFindReplaceDialogImpl::~wxFindReplaceDialogImpl()
{
    delete [] m_findReplace.lpstrFindWhat;
    delete [] m_findReplace.lpstrReplaceWith;

    ::DestroyWindow(m_hwndOwner);
}

// ----------------------------------------------------------------------------
// Window Proc for handling RegisterWindowMessage(FINDMSGSTRING)
// ----------------------------------------------------------------------------

LRESULT APIENTRY wxFindReplaceWindowProc(HWND hwnd, WXUINT nMsg,
                                         WPARAM wParam, LPARAM lParam)
{
#if wxUSE_UNICODE_MSLU
    static unsigned long s_lastMsgFlags = 0;

    // This flag helps us to identify the bogus ANSI message
    // sent by UNICOWS.DLL (see below)
    // while we're sending our message to the dialog
    // we ignore possible messages sent in between
    static bool s_blockMsg = false;
#endif // wxUSE_UNICODE_MSLU

    if ( nMsg == wxFindReplaceDialogImpl::GetFindDialogMessage() )
    {
        FINDREPLACE *pFR = (FINDREPLACE *)lParam;

#if wxUSE_UNICODE_MSLU
        // This is a hack for a MSLU problem: Versions up to 1.0.4011
        // of UNICOWS.DLL send the correct UNICODE item after button press
        // and a bogus ANSI mode item right after this, so lets ignore
        // the second bogus message
        if ( wxUsingUnicowsDll() && s_lastMsgFlags == pFR->Flags )
        {
            s_lastMsgFlags = 0;
            return 0;
        }
        s_lastMsgFlags = pFR->Flags;
#endif // wxUSE_UNICODE_MSLU

        wxFindReplaceDialog *dialog = (wxFindReplaceDialog *)pFR->lCustData;

        // map flags from Windows
        wxEventType evtType;

        bool replace = false;
        if ( pFR->Flags & FR_DIALOGTERM )
        {
            // we have to notify the dialog that it's being closed by user and
            // not deleted programmatically as it behaves differently in these
            // 2 cases
            dialog->GetImpl()->SetClosedByUser();

            evtType = wxEVT_COMMAND_FIND_CLOSE;
        }
        else if ( pFR->Flags & FR_FINDNEXT )
        {
            evtType = wxEVT_COMMAND_FIND_NEXT;
        }
        else if ( pFR->Flags & FR_REPLACE )
        {
            evtType = wxEVT_COMMAND_FIND_REPLACE;

            replace = true;
        }
        else if ( pFR->Flags & FR_REPLACEALL )
        {
            evtType = wxEVT_COMMAND_FIND_REPLACE_ALL;

            replace = true;
        }
        else
        {
            wxFAIL_MSG( _T("unknown find dialog event") );

            return 0;
        }

        wxUint32 flags = 0;
        if ( pFR->Flags & FR_DOWN )
            flags |= wxFR_DOWN;
        if ( pFR->Flags & FR_WHOLEWORD )
            flags |= wxFR_WHOLEWORD;
        if ( pFR->Flags & FR_MATCHCASE )
            flags |= wxFR_MATCHCASE;

        wxFindDialogEvent event(evtType, dialog->GetId());
        event.SetEventObject(dialog);
        event.SetFlags(flags);
        event.SetFindString(pFR->lpstrFindWhat);
        if ( replace )
        {
            event.SetReplaceString(pFR->lpstrReplaceWith);
        }

#if wxUSE_UNICODE_MSLU
        s_blockMsg = true;
#endif // wxUSE_UNICODE_MSLU

        dialog->Send(event);

#if wxUSE_UNICODE_MSLU
        s_blockMsg = false;
#endif // wxUSE_UNICODE_MSLU
    }
#if wxUSE_UNICODE_MSLU
    else if ( !s_blockMsg )
        s_lastMsgFlags = 0;
#endif // wxUSE_UNICODE_MSLU

    return ::DefWindowProc(hwnd, nMsg, wParam, lParam);
}

// ----------------------------------------------------------------------------
// Find/replace dialog hook proc
// ----------------------------------------------------------------------------

UINT_PTR CALLBACK
wxFindReplaceDialogHookProc(HWND hwnd,
                            UINT uiMsg,
                            WPARAM WXUNUSED(wParam),
                            LPARAM lParam)
{
    if ( uiMsg == WM_INITDIALOG )
    {
        FINDREPLACE *pFR = (FINDREPLACE *)lParam;
        wxFindReplaceDialog *dialog = (wxFindReplaceDialog *)pFR->lCustData;

        ::SetWindowText(hwnd, dialog->GetTitle());

        // HACK: Since we don't set the HWND owner of the find dialog to our
        // parent the initial positioning of the window will be off 
        // (Normally it puts the dialog a bit to the right and bottom of 
        //  the owner - and since our owner is a hidden window it will
        //  do it in (0,0) so we just adjust that to our parent's coords)
        RECT rect, parentrect;
        ::GetWindowRect(hwnd, &rect);
        ::GetWindowRect((HWND)dialog->GetParent()->GetHandle(), &parentrect);

        ::MoveWindow(hwnd, 
                     rect.left + parentrect.left, 
                     rect.top + parentrect.top,
                     rect.right - rect.left, 
                     rect.bottom - rect.top, 
                     TRUE);
    
        // don't return FALSE from here or the dialog won't be shown
        return TRUE;
    }

    return 0;
}

// ============================================================================
// wxFindReplaceDialog implementation
// ============================================================================

// ----------------------------------------------------------------------------
// wxFindReplaceDialog ctors/dtor
// ----------------------------------------------------------------------------

void wxFindReplaceDialog::Init()
{
    m_impl = NULL;
    m_FindReplaceData = NULL;

    // as we're created in the hidden state, bring the internal flag in sync
    m_isShown = false;
}

wxFindReplaceDialog::wxFindReplaceDialog(wxWindow *parent,
                                         wxFindReplaceData *data,
                                         const wxString &title,
                                         int flags)
                   : wxFindReplaceDialogBase(parent, data, title, flags)
{
    Init();

    (void)Create(parent, data, title, flags);
}

wxFindReplaceDialog::~wxFindReplaceDialog()
{
    // the dialog might have been already deleted if the user closed it
    // manually but in this case we should have got a notification about it and
    // the flagmust have been set
    if ( !m_impl->WasClosedByUser() )
    {
        // if it wasn't, delete the dialog ourselves
        if ( !::DestroyWindow(GetHwnd()) )
        {
            wxLogLastError(_T("DestroyWindow(find dialog)"));
        }
    }

    // unsubclass the parent
    delete m_impl;

    // prevent the base class dtor from trying to hide us!
    m_isShown = false;

    // and from destroying our window [again]
    m_hWnd = (WXHWND)NULL;
}

bool wxFindReplaceDialog::Create(wxWindow *parent,
                                 wxFindReplaceData *data,
                                 const wxString &title,
                                 int flags)
{
    m_windowStyle = flags;
    m_FindReplaceData = data;
    m_parent = parent;

    SetTitle(title);

    // Well, we don't really need a parent but it is a good idea anyway...
    return parent != NULL;
}

// ----------------------------------------------------------------------------
// wxFindReplaceData show/hide
// ----------------------------------------------------------------------------

bool wxFindReplaceDialog::Show(bool show)
{
    if ( !wxWindowBase::Show(show) )
    {
        // visibility status didn't change
        return false;
    }

    // do we already have the dialog window?
    if ( m_hWnd )
    {
        // yes, just use it
        (void)::ShowWindow(GetHwnd(), show ? SW_SHOW : SW_HIDE);

        return true;
    }

    if ( !show )
    {
        // well, it doesn't exist which is as good as being hidden
        return true;
    }

    wxCHECK_MSG( m_FindReplaceData, false, _T("call Create() first!") );

    wxASSERT_MSG( !m_impl, _T("why don't we have the window then?") );

    m_impl = new wxFindReplaceDialogImpl(this, m_FindReplaceData->GetFlags());

    m_impl->InitFindWhat(m_FindReplaceData->GetFindString());

    bool replace = HasFlag(wxFR_REPLACEDIALOG);
    if ( replace )
    {
        m_impl->InitReplaceWith(m_FindReplaceData->GetReplaceString());
    }

    // call the right function to show the dialog which does what we want
    FINDREPLACE *pFR = m_impl->GetPtrFindReplace();
    HWND hwnd;
    if ( replace )
        hwnd = ::ReplaceText(pFR);
    else
        hwnd = ::FindText(pFR);

    if ( !hwnd )
    {
        wxLogError(_("Failed to create the standard find/replace dialog (error code %d)"),
                   ::CommDlgExtendedError());

        delete m_impl;
        m_impl = NULL;

        return false;
    }

    if ( !::ShowWindow(hwnd, SW_SHOW) )
    {
        wxLogLastError(_T("ShowWindow(find dialog)"));
    }

    m_hWnd = (WXHWND)hwnd;

    return true;
}

// ----------------------------------------------------------------------------
// wxFindReplaceDialog title handling
// ----------------------------------------------------------------------------

// we set the title of this dialog in our jook proc but for now don't crash in
// the base class version because of m_hWnd == 0

void wxFindReplaceDialog::SetTitle( const wxString& title)
{
    m_title = title;
}

wxString wxFindReplaceDialog::GetTitle() const
{
    return m_title;
}

// ----------------------------------------------------------------------------
// wxFindReplaceDialog position/size
// ----------------------------------------------------------------------------

void wxFindReplaceDialog::DoSetSize(int WXUNUSED(x), int WXUNUSED(y),
                                    int WXUNUSED(width), int WXUNUSED(height),
                                    int WXUNUSED(sizeFlags))
{
    // ignore - we can't change the size of this standard dialog
    return;
}

// NB: of course, both of these functions are completely bogus, but it's better
//     than nothing
void wxFindReplaceDialog::DoGetSize(int *width, int *height) const
{
    // the standard dialog size
    if ( width )
        *width = 225;
    if ( height )
        *height = 324;
}

void wxFindReplaceDialog::DoGetClientSize(int *width, int *height) const
{
    // the standard dialog size
    if ( width )
        *width = 219;
    if ( height )
        *height = 299;
}

#endif // wxUSE_FINDREPLDLG
 	  	 
