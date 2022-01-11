// Test for ticket 4265 using custom wxLogGui

#include "wx/app.h"
#include "wx/button.h"
#include "wx/intl.h"
#include "wx/menu.h"
#include "wx/log.h"
#include "wx/frame.h"
#include "wx/filedlg.h"
#include "wx/msgdlg.h"
#include "wx/sizer.h"
#include "wx/statbmp.h"
#include "wx/settings.h"

#include "wx/file.h"
#include "wx/textfile.h"
#include "wx/statline.h"
#include "wx/artprov.h"

#ifdef  __WXMSW__
    // for OutputDebugString()
    #include  "wx/msw/private.h"
#endif // Windows

#ifdef  __WXPM__
    #include <time.h>
#endif

#include "wx/listctrl.h"
#include "wx/imaglist.h"
#include "wx/image.h"

#if defined(__MWERKS__) && wxUSE_UNICODE
    #include <wtime.h>
#endif

#include "wx/datetime.h"

// the suffix we add to the button to show that the dialog can be expanded
#define EXPAND_SUFFIX _T(" >>")

class LogGui : public wxLogGui
{
public:
    // ctor
    LogGui(wxFrame* frame) : wxLogGui(), m_frame(frame) {}

    // show all messages that were logged since the last Flush()
    virtual void Flush();

protected:
    wxFrame* m_frame;	// main frame
};

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// this function is a wrapper around strftime(3)
// allows to exclude the usage of wxDateTime
static wxString TimeStamp(const wxChar *format, time_t t)
{
#if wxUSE_DATETIME
    wxChar buf[4096];
    struct tm tm;
    if ( !wxStrftime(buf, WXSIZEOF(buf), format, wxLocaltime_r(&t, &tm)) )
    {
        // buffer is too small?
        wxFAIL_MSG(_T("strftime() failed"));
    }
    return wxString(buf);
#else // !wxUSE_DATETIME
    return wxEmptyString;
#endif // wxUSE_DATETIME/!wxUSE_DATETIME
}

class LogDialog : public wxDialog
{
public:
    LogDialog(wxWindow *parent,
                const wxArrayString& messages,
                const wxArrayInt& severity,
                const wxArrayLong& timess,
                const wxString& caption,
                long style);
    virtual ~LogDialog();

    // event handlers
    void OnOk(wxCommandEvent& event);
    void OnDetails(wxCommandEvent& event);
#if wxUSE_FILE
    void OnSave(wxCommandEvent& event);
#endif // wxUSE_FILE
    void OnListSelect(wxListEvent& event);

private:
    // create controls needed for the details display
    void CreateDetailsControls();

    // the data for the listctrl
    wxArrayString m_messages;
    wxArrayInt m_severity;
    wxArrayLong m_times;

    // the "toggle" button and its state
#ifndef __SMARTPHONE__
    wxButton *m_btnDetails;
#endif
    bool      m_showingDetails;

    // the controls which are not shown initially (but only when details
    // button is pressed)
    wxListCtrl *m_listctrl;
#ifndef __SMARTPHONE__
#if wxUSE_STATLINE
    wxStaticLine *m_statline;
#endif // wxUSE_STATLINE
#if wxUSE_FILE
    wxButton *m_btnSave;
#endif // wxUSE_FILE
#endif // __SMARTPHONE__

    // the translated "Details" string
    static wxString ms_details;

    DECLARE_EVENT_TABLE()
    DECLARE_NO_COPY_CLASS(LogDialog)
};

BEGIN_EVENT_TABLE(LogDialog, wxDialog)
    EVT_BUTTON(wxID_OK, LogDialog::OnOk)
    EVT_BUTTON(wxID_MORE,   LogDialog::OnDetails)
#if wxUSE_FILE
    EVT_BUTTON(wxID_SAVE,   LogDialog::OnSave)
#endif // wxUSE_FILE
    EVT_LIST_ITEM_SELECTED(wxID_ANY, LogDialog::OnListSelect)
END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// private functions
// ----------------------------------------------------------------------------

#if wxUSE_FILE && wxUSE_FILEDLG

// pass an uninitialized file object, the function will ask the user for the
// filename and try to open it, returns true on success (file was opened),
// false if file couldn't be opened/created and -1 if the file selection
// dialog was cancelled
static int OpenLogFile(wxFile& file, wxString *filename = NULL, wxWindow *parent = NULL);

#endif // wxUSE_FILE

// ----------------------------------------------------------------------------
// global variables
// ----------------------------------------------------------------------------

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// LogGui implementation
// ----------------------------------------------------------------------------

void LogGui::Flush()
{
    if ( !m_bHasMessages )
        return;

    // do it right now to block any new calls to Flush() while we're here
    m_bHasMessages = false;

    unsigned repeatCount = 0;
    if ( wxLog::GetRepetitionCounting() )
    {
        repeatCount = wxLog::DoLogNumberOfRepeats();
    }

    wxString appName = wxTheApp->GetAppName();
    if ( !appName.empty() )
        appName[0u] = (wxChar)wxToupper(appName[0u]);

    long style;
    wxString titleFormat;
    if ( m_bErrors ) {
        titleFormat = _("%s Error");
        style = wxICON_STOP;
    }
    else if ( m_bWarnings ) {
        titleFormat = _("%s Warning");
        style = wxICON_EXCLAMATION;
    }
    else {
        titleFormat = _("%s Information");
        style = wxICON_INFORMATION;
    }

    wxString title;
    title.Printf(titleFormat, appName.c_str());

    size_t nMsgCount = m_aMessages.Count();

    // avoid showing other log dialogs until we're done with the dialog we're
    // showing right now: nested modal dialogs make for really bad UI!
    Suspend();

    wxString str;
    if ( nMsgCount == 1 )
    {
        str = m_aMessages[0];
    }
    else // more than one message
    {
        if ( repeatCount > 0 )
            m_aMessages[nMsgCount-1] += wxString::Format(wxT(" (%s)"), m_aMessages[nMsgCount-2].c_str());
        LogDialog dlg(m_frame,
                        m_aMessages, m_aSeverity, m_aTimes,
                        title, style);

        // clear the message list before showing the dialog because while it's
        // shown some new messages may appear
        Clear();

        (void)dlg.ShowModal();
    }

    // this catches both cases of 1 message with wxUSE_LOG_DIALOG and any
    // situation without it
    if ( !str.empty() )
    {
        wxMessageBox(str, title, wxOK | style, m_frame);

        // no undisplayed messages whatsoever
        Clear();
    }

    // allow flushing the logs again
    Resume();
}

// ----------------------------------------------------------------------------
// LogDialog
// ----------------------------------------------------------------------------

#ifndef __SMARTPHONE__
static const size_t MARGIN = 10;
#else
static const size_t MARGIN = 0;
#endif

wxString LogDialog::ms_details;

LogDialog::LogDialog(wxWindow *parent,
                         const wxArrayString& messages,
                         const wxArrayInt& severity,
                         const wxArrayLong& times,
                         const wxString& caption,
                         long style)
           : wxDialog(parent, wxID_ANY, caption,
                      wxDefaultPosition, wxDefaultSize,
                      wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    if ( ms_details.empty() )
    {
        // ensure that we won't loop here if wxGetTranslation()
        // happens to pop up a Log message while translating this :-)
        ms_details = wxTRANSLATE("&Details");
        ms_details = wxGetTranslation(ms_details);
#ifdef __SMARTPHONE__
        ms_details = wxStripMenuCodes(ms_details);
#endif
    }

    size_t count = messages.GetCount();
    m_messages.Alloc(count);
    m_severity.Alloc(count);
    m_times.Alloc(count);

    for ( size_t n = 0; n < count; n++ )
    {
        wxString msg = messages[n];
        msg.Replace(wxT("\n"), wxT(" "));
        m_messages.Add(msg);
        m_severity.Add(severity[n]);
        m_times.Add(times[n]);
    }

    m_showingDetails = false; // not initially
    m_listctrl = (wxListCtrl *)NULL;

#ifndef __SMARTPHONE__

#if wxUSE_STATLINE
    m_statline = (wxStaticLine *)NULL;
#endif // wxUSE_STATLINE

#if wxUSE_FILE
    m_btnSave = (wxButton *)NULL;
#endif // wxUSE_FILE

#endif // __SMARTPHONE__

    bool isPda = (wxSystemSettings::GetScreenType() <= wxSYS_SCREEN_PDA);

    // create the controls which are always shown and layout them: we use
    // sizers even though our window is not resizeable to calculate the size of
    // the dialog properly
    wxBoxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
#ifndef __SMARTPHONE__
    wxBoxSizer *sizerButtons = new wxBoxSizer(isPda ? wxHORIZONTAL : wxVERTICAL);
#endif
    wxBoxSizer *sizerAll = new wxBoxSizer(isPda ? wxVERTICAL : wxHORIZONTAL);

#ifdef __SMARTPHONE__
    SetLeftMenu(wxID_OK);
    SetRightMenu(wxID_MORE, ms_details + EXPAND_SUFFIX);
#else
    wxButton *btnOk = new wxButton(this, wxID_OK);
    sizerButtons->Add(btnOk, 0, isPda ? wxCENTRE : wxCENTRE|wxBOTTOM, MARGIN/2);
    m_btnDetails = new wxButton(this, wxID_MORE, ms_details + EXPAND_SUFFIX);
    sizerButtons->Add(m_btnDetails, 0, isPda ? wxCENTRE|wxLEFT : wxCENTRE | wxTOP, MARGIN/2 - 1);
#endif

    wxBitmap bitmap;
    switch ( style & wxICON_MASK )
    {
        case wxICON_ERROR:
            bitmap = wxArtProvider::GetBitmap(wxART_ERROR, wxART_MESSAGE_BOX);
#ifdef __WXPM__
            bitmap.SetId(wxICON_SMALL_ERROR);
#endif
            break;

        case wxICON_INFORMATION:
            bitmap = wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_MESSAGE_BOX);
#ifdef __WXPM__
            bitmap.SetId(wxICON_SMALL_INFO);
#endif
            break;

        case wxICON_WARNING:
            bitmap = wxArtProvider::GetBitmap(wxART_WARNING, wxART_MESSAGE_BOX);
#ifdef __WXPM__
            bitmap.SetId(wxICON_SMALL_WARNING);
#endif
            break;

        default:
            wxFAIL_MSG(_T("incorrect log style"));
    }

    if (!isPda)
        sizerAll->Add(new wxStaticBitmap(this, wxID_ANY, bitmap), 0,
                  wxALIGN_CENTRE_VERTICAL);

    const wxString& message = messages.Last();
    sizerAll->Add(CreateTextSizer(message), 1,
                  wxALIGN_CENTRE_VERTICAL | wxLEFT | wxRIGHT, MARGIN);
#ifndef __SMARTPHONE__
    sizerAll->Add(sizerButtons, 0, isPda ? wxCENTRE|wxTOP|wxBOTTOM : (wxALIGN_RIGHT | wxLEFT), MARGIN);
#endif

    sizerTop->Add(sizerAll, 0, wxALL | wxEXPAND, MARGIN);

    SetSizer(sizerTop);

    // see comments in OnDetails()
    //
    // Note: Doing this, this way, triggered a nasty bug in
    //       wxTopLevelWindowGTK::GtkOnSize which took -1 literally once
    //       either of maxWidth or maxHeight was set.  This symptom has been
    //       fixed there, but it is a problem that remains as long as we allow
    //       unchecked access to the internal size members.  We really need to
    //       encapuslate window sizes more cleanly and make it clear when -1 will
    //       be substituted and when it will not.

    wxSize size = sizerTop->Fit(this);
    m_maxHeight = size.y;
    SetSizeHints(size.x, size.y, m_maxWidth, m_maxHeight);

#ifndef __SMARTPHONE__
    btnOk->SetFocus();
#endif

    Centre();

    if (isPda)
    {
        // Move up the screen so that when we expand the dialog,
        // there's enough space.
        Move(wxPoint(GetPosition().x, GetPosition().y / 2));
    }
}

void LogDialog::CreateDetailsControls()
{
#ifndef __SMARTPHONE__
    // create the save button and separator line if possible
#if wxUSE_FILE
    m_btnSave = new wxButton(this, wxID_SAVE);
#endif // wxUSE_FILE

#if wxUSE_STATLINE
    m_statline = new wxStaticLine(this, wxID_ANY);
#endif // wxUSE_STATLINE

#endif // __SMARTPHONE__

    // create the list ctrl now
    m_listctrl = new wxListCtrl(this, wxID_ANY,
                                wxDefaultPosition, wxDefaultSize,
                                wxSUNKEN_BORDER |
                                wxLC_REPORT |
                                wxLC_NO_HEADER |
                                wxLC_SINGLE_SEL);
#ifdef __WXWINCE__
    // This maks a big aesthetic difference on WinCE but I
    // don't want to risk problems on other platforms
    m_listctrl->Hide();
#endif

    // no need to translate these strings as they're not shown to the
    // user anyhow (we use wxLC_NO_HEADER style)
    m_listctrl->InsertColumn(0, _T("Message"));
    m_listctrl->InsertColumn(1, _T("Time"));

    // prepare the imagelist
    static const int ICON_SIZE = 16;
    wxImageList *imageList = new wxImageList(ICON_SIZE, ICON_SIZE);

    // order should be the same as in the switch below!
    static const wxChar* icons[] =
    {
        wxART_ERROR,
        wxART_WARNING,
        wxART_INFORMATION
    };

    bool loadedIcons = true;

    for ( size_t icon = 0; icon < WXSIZEOF(icons); icon++ )
    {
        wxBitmap bmp = wxArtProvider::GetBitmap(icons[icon], wxART_MESSAGE_BOX,
                                                wxSize(ICON_SIZE, ICON_SIZE));

        // This may very well fail if there are insufficient colours available.
        // Degrade gracefully.
        if ( !bmp.Ok() )
        {
            loadedIcons = false;

            break;
        }

        imageList->Add(bmp);
    }

    m_listctrl->SetImageList(imageList, wxIMAGE_LIST_SMALL);

    // and fill it
    wxString fmt = wxLog::GetTimestamp();
    if ( !fmt )
    {
        // default format
        fmt = _T("%c");
    }

    size_t count = m_messages.GetCount();
    for ( size_t n = 0; n < count; n++ )
    {
        int image;

        if ( loadedIcons )
        {
            switch ( m_severity[n] )
            {
                case wxLOG_Error:
                    image = 0;
                    break;

                case wxLOG_Warning:
                    image = 1;
                    break;

                default:
                    image = 2;
            }
        }
        else // failed to load images
        {
            image = -1;
        }

        m_listctrl->InsertItem(n, m_messages[n], image);
        m_listctrl->SetItem(n, 1, TimeStamp(fmt, (time_t)m_times[n]));
    }

    // let the columns size themselves
    m_listctrl->SetColumnWidth(0, wxLIST_AUTOSIZE);
    m_listctrl->SetColumnWidth(1, wxLIST_AUTOSIZE);

    // calculate an approximately nice height for the listctrl
    int height = GetCharHeight()*(count + 4);

    // but check that the dialog won't fall fown from the screen
    //
    // we use GetMinHeight() to get the height of the dialog part without the
    // details and we consider that the "Save" button below and the separator
    // line (and the margins around it) take about as much, hence double it
    int heightMax = wxGetDisplaySize().y - GetPosition().y - 2*GetMinHeight();

    // we should leave a margin
    heightMax *= 9;
    heightMax /= 10;

    m_listctrl->SetSize(wxDefaultCoord, wxMin(height, heightMax));
}

void LogDialog::OnListSelect(wxListEvent& event)
{
    // we can't just disable the control because this looks ugly under Windows
    // (wrong bg colour, no scrolling...), but we still want to disable
    // selecting items - it makes no sense here
    m_listctrl->SetItemState(event.GetIndex(), 0, wxLIST_STATE_SELECTED);
}

void LogDialog::OnOk(wxCommandEvent& WXUNUSED(event))
{
    EndModal(wxID_OK);
}

#if wxUSE_FILE

void LogDialog::OnSave(wxCommandEvent& WXUNUSED(event))
{
#if wxUSE_FILEDLG
    wxFile file;
    int rc = OpenLogFile(file, NULL, this);
    if ( rc == -1 )
    {
        // cancelled
        return;
    }

    bool ok = rc != 0;

    wxString fmt = wxLog::GetTimestamp();
    if ( !fmt )
    {
        // default format
        fmt = _T("%c");
    }

    size_t count = m_messages.GetCount();
    for ( size_t n = 0; ok && (n < count); n++ )
    {
        wxString line;
        line << TimeStamp(fmt, (time_t)m_times[n])
             << _T(": ")
             << m_messages[n]
             << wxTextFile::GetEOL();

        ok = file.Write(line);
    }

    if ( ok )
        ok = file.Close();

    if ( !ok )
        wxLogError(_("Can't save log contents to file."));
#endif // wxUSE_FILEDLG
}

#endif // wxUSE_FILE

void LogDialog::OnDetails(wxCommandEvent& WXUNUSED(event))
{
    wxSizer *sizer = GetSizer();

    if ( m_showingDetails )
    {
#ifdef __SMARTPHONE__
        SetRightMenu(wxID_MORE, ms_details + EXPAND_SUFFIX);
#else
        m_btnDetails->SetLabel(ms_details + EXPAND_SUFFIX);
#endif

        sizer->Detach( m_listctrl );

#ifndef __SMARTPHONE__

#if wxUSE_STATLINE
        sizer->Detach( m_statline );
#endif // wxUSE_STATLINE

#if wxUSE_FILE
        sizer->Detach( m_btnSave );
#endif // wxUSE_FILE

#endif // __SMARTPHONE__
    }
    else // show details now
    {
#ifdef __SMARTPHONE__
        SetRightMenu(wxID_MORE, wxString(_T("<< ")) + ms_details);
#else
        m_btnDetails->SetLabel(wxString(_T("<< ")) + ms_details);
#endif

        if ( !m_listctrl )
        {
            CreateDetailsControls();
        }

#if wxUSE_STATLINE && !defined(__SMARTPHONE__)
        bool isPda = (wxSystemSettings::GetScreenType() <= wxSYS_SCREEN_PDA);
        if (!isPda)
            sizer->Add(m_statline, 0, wxEXPAND | (wxALL & ~wxTOP), MARGIN);
#endif // wxUSE_STATLINE

        sizer->Add(m_listctrl, 1, wxEXPAND | (wxALL & ~wxTOP), MARGIN);

        // VZ: this doesn't work as this becomes the initial (and not only
        //     minimal) listctrl height as well - why?
#if 0
        // allow the user to make the dialog shorter than its initial height -
        // without this it wouldn't work as the list ctrl would have been
        // incompressible
        sizer->SetItemMinSize(m_listctrl, 100, 3*GetCharHeight());
#endif // 0

#if wxUSE_FILE && !defined(__SMARTPHONE__)
        sizer->Add(m_btnSave, 0, wxALIGN_RIGHT | (wxALL & ~wxTOP), MARGIN);
#endif // wxUSE_FILE
    }

    m_showingDetails = !m_showingDetails;

    // in any case, our size changed - relayout everything and set new hints
    // ---------------------------------------------------------------------

    // we have to reset min size constraints or Fit() would never reduce the
    // dialog size when collapsing it and we have to reset max constraint
    // because it wouldn't expand it otherwise

    m_minHeight =
    m_maxHeight = -1;

    // wxSizer::FitSize() is private, otherwise we might use it directly...
    wxSize sizeTotal = GetSize(),
           sizeClient = GetClientSize();

    wxSize size = sizer->GetMinSize();
    size.x += sizeTotal.x - sizeClient.x;
    size.y += sizeTotal.y - sizeClient.y;

    // we don't want to allow expanding the dialog in vertical direction as
    // this would show the "hidden" details but we can resize the dialog
    // vertically while the details are shown
    if ( !m_showingDetails )
        m_maxHeight = size.y;

    SetSizeHints(size.x, size.y, m_maxWidth, m_maxHeight);

#ifdef __WXWINCE__
    if (m_showingDetails)
        m_listctrl->Show();
#endif

    // don't change the width when expanding/collapsing
    SetSize(wxDefaultCoord, size.y);

#ifdef __WXGTK__
    // VS: this is necessary in order to force frame redraw under
    // WindowMaker or fvwm2 (and probably other broken WMs).
    // Otherwise, detailed list wouldn't be displayed.
    Show();
#endif // wxGTK
}

LogDialog::~LogDialog()
{
    if ( m_listctrl )
    {
        delete m_listctrl->GetImageList(wxIMAGE_LIST_SMALL);
    }
}

#if wxUSE_FILE && wxUSE_FILEDLG

// pass an uninitialized file object, the function will ask the user for the
// filename and try to open it, returns true on success (file was opened),
// false if file couldn't be opened/created and -1 if the file selection
// dialog was cancelled
static int OpenLogFile(wxFile& file, wxString *pFilename, wxWindow *parent)
{
    // get the file name
    // -----------------
    wxString filename = wxSaveFileSelector(wxT("log"), wxT("txt"), wxT("log.txt"), parent);
    if ( !filename ) {
        // cancelled
        return -1;
    }

    // open file
    // ---------
    bool bOk wxDUMMY_INITIALIZE(false);
    if ( wxFile::Exists(filename) ) {
        bool bAppend = false;
        wxString strMsg;
        strMsg.Printf(_("Append log to file '%s' (choosing [No] will overwrite it)?"),
                      filename.c_str());
        switch ( wxMessageBox(strMsg, _("Question"),
                              wxICON_QUESTION | wxYES_NO | wxCANCEL) ) {
            case wxYES:
                bAppend = true;
                break;

            case wxNO:
                bAppend = false;
                break;

            case wxCANCEL:
                return -1;

            default:
                wxFAIL_MSG(_("invalid message box return value"));
        }

        if ( bAppend ) {
            bOk = file.Open(filename, wxFile::write_append);
        }
        else {
            bOk = file.Create(filename, true /* overwrite */);
        }
    }
    else {
        bOk = file.Create(filename);
    }

    if ( pFilename )
        *pFilename = filename;

    return bOk;
}

#endif // wxUSE_FILE

// ----------------------------------------------------------------------------
// Testing part
// ----------------------------------------------------------------------------

#include <wx/sizer.h>
#include <wx/checkbox.h>

class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
    void OnCheckBox(wxCommandEvent& event);
    void OnButton(wxCommandEvent& event);
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() ) return false;
    MyFrame *frame = new MyFrame(_T("wxWidgets App"));
    frame->Center();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition)
{
    wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );
    wxCheckBox* cb = new wxCheckBox(this, -1, _T("Use custom LogGui"));
    topsizer->Add(cb, 0, wxALL, 50);
    wxButton* bu = new wxButton(this, -1, _T("Show log message"));
    topsizer->Add(bu, 0, wxALL, 50);
    SetSizerAndFit(topsizer);

    cb->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame::OnCheckBox));
    bu->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnButton));
}

void MyFrame::OnCheckBox(wxCommandEvent& event)
{
    if (event.IsChecked())
        delete wxLog::SetActiveTarget(new LogGui(this));
    else
        delete wxLog::SetActiveTarget(NULL);
}

void MyFrame::OnButton(wxCommandEvent& event)
{
    wxLogMessage(_T("You've got log!"));
}

