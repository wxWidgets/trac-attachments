//
//  launcher.cpp
//  OS X app to demonstrate spawned process completion notification.
//
//  Created by Steven Houchin of Forest Park Lab on 12/7/12.
//  Lake Forest Park, WA
//  www.forestparklab.com
//

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/log.h>
#endif

#include <wx/osx/private.h>
#include <wx/process.h>

#include <Carbon/Carbon.h>


// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

#define FR_INITIAL_WINDOW_WIDTH (400)
#define PID_NONE                (-1)
#define MAX_CSTRING_BUFFER      (512)

// ----------------------------------------------------------------------------
// class definitions
// ----------------------------------------------------------------------------

class CMainFrame;


//
// The application class
//
class CApp : public wxApp
{
public:
    CApp()
    { 
        m_pframe = NULL;
        
    }
    virtual ~CApp()
    {
    }
    
    virtual bool OnInit();
    
    bool GetFromCFString(const CFStringRef inStr, wxString& outStr);
    const wxString& GetLastError(void) { return m_lastError; }
    
protected:
    CMainFrame *m_pframe;
    wxString m_lastError;
    
};



//
// The child process manager class
//
class CProcessManager
{
public:
    CProcessManager(wxEvtHandler *parent = NULL, int nId = wxID_ANY);
    virtual ~CProcessManager();
    
    bool IsInitialized(void) { return (NULL != m_sCarbonEventsRef); }
    pid_t SetPid(void);
    pid_t GetPid(void) { return m_pid; }
    ProcessSerialNumber *GetPsnPointer(void) { return &m_psn; }
    
    
protected:
    static OSStatus CarbonEventHandler(EventHandlerCallRef inHandlerCallRef, 
                                       EventRef inEvent, 
                                       void *inUserData
                                       );
    
protected:
    int     m_id;               // ID for Terminate event
    pid_t   m_pid;              // unix process id
    ProcessSerialNumber m_psn;  // Carbon process number
    wxEvtHandler *m_parent;     // Terminate event target
    EventHandlerRef m_sCarbonEventsRef; // Registered Carbon event reference
};


//
// The user interface frame class
//
class CMainFrame : public wxFrame
{
public:
    CMainFrame(const wxString& title);
    virtual ~CMainFrame();
    
protected:
    void OnQuit(wxCommandEvent& event);
    void OnTerminate(wxProcessEvent& event);
    void OnButtonLaunch(wxCommandEvent& event);
    
    
    bool CreateMenus(void);
    bool CreateControls(void);
    
    pid_t LaunchApp(wxString& appPath, CProcessManager *procManager,
                    const char *arg0 = NULL, const char *arg1 = NULL);
    
    
    wxStatusBar *m_statusBar;
    wxButton *m_buttonLaunch;
    wxString m_lastError;
    CProcessManager *m_pm;       
    
public:
    DECLARE_EVENT_TABLE()
    
};



// ----------------------------------------------------------------------------
// helper functions
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// CApp implementation
// ----------------------------------------------------------------------------

IMPLEMENT_APP(CApp)

#define kApplicationTitle wxT("Launch Application Testbed")


// 'Main program' equivalent: the program execution "starts" here
bool CApp::OnInit()
{
    // create the main application window
    m_pframe = new CMainFrame(kApplicationTitle);
    
    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    m_pframe->Show(true);
    
    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}


/*
 * Given CFStringRef, return the string in a wxString object. This function
 * is not thread safe.
 */
bool CApp::GetFromCFString(const CFStringRef inStr, wxString& outStr)
{
    outStr.Empty();
    if (NULL == inStr)
    {
        m_lastError = wxT("Null input string");
        return false;
    }
    m_lastError.Empty();

    char buffer[MAX_CSTRING_BUFFER];
                
    // Create a C string for the CFStringRef in the buffer
    bool success = CFStringGetCString(inStr,
                                      buffer,
                                      MAX_CSTRING_BUFFER,
                                      kCFStringEncodingMacRoman
                                      );
    
    if (success)
    {
        outStr = buffer;    // assign result string
    }
    else
    {
        m_lastError = wxT("CFStringGetCString failed");
    }
    return success;
}



// ----------------------------------------------------------------------------
// CProcessManager implementation
// ----------------------------------------------------------------------------
static const EventTypeSpec kEvents[] = {
    { kEventClassApplication, kEventAppLaunched },
    { kEventClassApplication, kEventAppTerminated }
};

CProcessManager::CProcessManager(wxEvtHandler *parent, int nId) :
                                m_parent(parent), m_id(nId)
{
    m_pid = PID_NONE;
    m_sCarbonEventsRef = NULL;
    memset(&m_psn, 0, sizeof(ProcessSerialNumber));
    
    // Install a process notification handler
    EventTargetRef targetRef = ::GetApplicationEventTarget();
    OSStatus status = ::InstallEventHandler(targetRef,
                                            (EventHandlerUPP) CarbonEventHandler,
                                            GetEventTypeCount(kEvents),
                                            kEvents,
                                            (void *)this,
                                            &m_sCarbonEventsRef
                                            );
    if (noErr != status)
    {
        wxLogDebug(wxT("CProcessManager: InstallEventHandler failed: %d"), status);
    }
}

CProcessManager::~CProcessManager()
{
    if (NULL != m_sCarbonEventsRef)
    {
        // Remove the installed notification handler
        ::RemoveEventHandler(m_sCarbonEventsRef);
        m_sCarbonEventsRef = NULL;
    }
}

/*
 * Convert the ProcessSerialNumber into a unix pid.
 */
pid_t CProcessManager::SetPid(void)
{
    if (noErr != ::GetProcessPID(&m_psn, &m_pid))
    {
        m_pid = PID_NONE;
    }
    return m_pid;
}

/*
 * This function is called back by the system when any process terminates.
 * If the process serial number matches ours, the parent is sent a
 * wxEVT_END_PROCESS event.
 */
OSStatus CProcessManager::CarbonEventHandler(EventHandlerCallRef inHandlerCallRef, 
                                        EventRef            inEvent, 
                                        void *              inUserData
                                        )
{
    ProcessSerialNumber psnSource;
    OSErr err = ::GetEventParameter(inEvent, 
                             kEventParamProcessID, 
                             typeProcessSerialNumber, 
                             NULL, 
                             sizeof(psnSource), 
                             NULL, 
                             &psnSource
                             );
    if (noErr != err)
        return err;
    
    CProcessManager *pThis = (CProcessManager *)inUserData;
    switch ( ::GetEventKind(inEvent) )
    {
        case kEventAppLaunched:
        {
            wxLogDebug(wxT("launched psn %u.%u"), 
                       (unsigned int) psnSource.highLongOfPSN, 
                       (unsigned int) psnSource.lowLongOfPSN
                       );
            // An app has been launched
            if (memcmp(&psnSource, &pThis->m_psn, sizeof(ProcessSerialNumber)) == 0)
            {
                // Our process was launched
                
                // Just a test: does a unix waitpid work with our pid value?
                int status_check;
                pid_t retval = waitpid(pThis->m_pid, &status_check, WNOHANG);
                if (-1 == retval)
                {
                    // Nope ... I'm getting ECHILD error - is the process not created
                    // as a true child of the parent, as happens with fork()?
                    wxLogDebug(wxT("waitpid %d failed, errno %d"), pThis->m_pid, errno);
                }
            }
            
            break;
        }
        case kEventAppTerminated:
        {
            wxLogDebug(wxT("terminated psn %u.%u"), 
                       (unsigned int) psnSource.highLongOfPSN, 
                       (unsigned int) psnSource.lowLongOfPSN
                       );
            // An app has terminated
            if (memcmp(&psnSource, &pThis->m_psn, sizeof(ProcessSerialNumber)) == 0)
            {
                // Our process has terminated
                
                // Notify the interested party with a wxEVT_END_PROCESS event
                wxLogDebug(wxT("our pid_t %d terminated"), pThis->m_pid);
                wxProcessEvent event(pThis->m_id, pThis->m_pid);
                wxPostEvent(pThis->m_parent, event);
                
                // Self destruct this process object
                delete pThis;
                pThis = NULL;
            }
            break;
        }

        default:
            assert(false);
            break;
    }
    return noErr;
}


// ----------------------------------------------------------------------------
// CMainFrame events
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    IDvalue_Quit = wxID_EXIT,
    IDvalue_About = wxID_ABOUT,
    IDvalue_Launch = wxID_HIGHEST,
    IDvalue_Cancel,
    IDvalue_Terminate,
};

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
EVT_MENU(IDvalue_Quit, CMainFrame::OnQuit)
EVT_BUTTON(IDvalue_Launch, CMainFrame::OnButtonLaunch)
EVT_BUTTON(IDvalue_Cancel, CMainFrame::OnQuit)
EVT_END_PROCESS(IDvalue_Terminate, CMainFrame::OnTerminate)
END_EVENT_TABLE()


// ----------------------------------------------------------------------------
// CMainFrame implementation
// ----------------------------------------------------------------------------

CMainFrame::CMainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(FR_INITIAL_WINDOW_WIDTH,-1),
          (wxDEFAULT_FRAME_STYLE) &
          ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
#ifdef __WXMAC__
    // SetIcon(wxIcon(kIconFilename));
#endif
    m_pm = NULL;
    
    CreateMenus();
    CreateControls();
}

CMainFrame::~CMainFrame()
{
    if (NULL != m_pm)
    {
        delete m_pm;    // delete orphan process manager object
    }
}

/*
 * Create all user interface menu items.
 */
bool CMainFrame::CreateMenus(void)
{
#if wxUSE_MENUS
    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    wxMenu *fileMenu = new wxMenu;
    
    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));
    
    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS
    
    return true;
}

/*
 * Create all user interface controls.
 */
bool CMainFrame::CreateControls(void)
{
    bool success = true;
    
    // Create the panel that encloses the controls
    wxPanel *panel = new wxPanel();
    panel->Create(this, wxID_ANY);
    
    
    // Create buttons Cancel and Launch
    m_buttonLaunch = new wxButton( panel, IDvalue_Launch,
                                          wxT("Launch!"), wxDefaultPosition, wxDefaultSize );
    m_buttonLaunch->SetDefault();

    wxButton *buttonCancel = new wxButton( panel, IDvalue_Cancel,
                                          wxT("Cancel"), wxDefaultPosition );
    
    
    // Create a status bar for feedback
    m_statusBar = new wxStatusBar( panel, wxID_ANY,
                                             wxSTB_SHOW_TIPS|wxSTB_ELLIPSIZE_END );    
    
    // Sizer and layout stuff
    wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer *butSizer = new wxBoxSizer( wxHORIZONTAL );
    
    butSizer->Add( buttonCancel, 0, wxALL, 0 );
    butSizer->AddSpacer(20);    // space between buttons
    butSizer->Add( m_buttonLaunch, 0, wxALL, 0 );
    
    topSizer->AddSpacer(40);    // space above buttons
    topSizer->Add( butSizer, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 0 );
    topSizer->AddSpacer(22);
    topSizer->Add( m_statusBar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 0 );
    
    panel->SetSizer( topSizer );
    panel->Layout();
    
    this->CenterOnScreen(); 
    
    // Prompt the user
    m_statusBar->SetStatusText(wxT("Launch the app, please"));
    
    return success;
}

void CMainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

/*
 * User pressed the Launch button.
 */
void CMainFrame::OnButtonLaunch(wxCommandEvent& WXUNUSED(event))
{
    m_buttonLaunch->Enable(false);
    
    // Create the object to monitor the process status
    m_pm = new CProcessManager(this, IDvalue_Terminate);
    if ((NULL == m_pm) || !(m_pm->IsInitialized()))
    {
        m_statusBar->SetStatusText(wxT("Process Manager object init failed."));
        
        delete m_pm;
        m_pm = NULL;
        return;
    }

    // Launch the Mac Address Book app
    wxString appPath = wxT("/Applications/Address Book.app");
    pid_t pid = LaunchApp(appPath, m_pm, NULL, NULL);
    if (PID_NONE == pid)
    {
        wxLogError(wxT("LaunchApp failed: %s"), wxGetApp().GetLastError());
        
        delete m_pm;
        m_pm = NULL;
        return;
    }
    
    m_pm = NULL;    // process callback will delete this
    m_statusBar->SetStatusText(wxT("App was launched."));
}

                
/*
 * Event handler for wxEVT_END_PROCESS
 */
void CMainFrame::OnTerminate(wxProcessEvent& WXUNUSED(event))
{
    // This is called when the child app quits
    
    m_pm = NULL;        // this self-deleted when process ended
    m_statusBar->SetStatusText(wxT("OnTerminate called! Launch the app again, please."));
    m_buttonLaunch->Enable(true);
}

/*
 * Start an application with up to two command line params using
 * Launch Services API. The process's unix PID value is returned
 * or PID_NONE if error (but good luck using that pid in any unix
 * process-related calls - it don't work).
 */
pid_t CMainFrame::LaunchApp(wxString& appPath, 
                            CProcessManager *procManager,
                            const char *arg0 /*=NULL*/,
                            const char *arg1 /*=NULL*/
                            )
{
    m_lastError.Empty();
    
    if (NULL == procManager)
    {
        m_lastError = wxT("LaunchApp: Null process manager object.");
        wxLogDebug(m_lastError);
        return PID_NONE;
    }
    
    // Get a File System reference to the application path
    FSRef appRef;
    OSStatus status = FSPathMakeRef((const UInt8 *)(const char *)appPath.c_str(), &appRef, NULL);
    if (status != noErr)
    {
        m_lastError.Printf(wxT("LaunchApp: Couldn't get FSRef for '%s', error %d"), appPath, status);
        wxLogDebug(m_lastError);
        return PID_NONE;
    }
    
    // Create an array for the command line args
    CFIndex capacity = 4;
    CFMutableArrayRef argArrayRef = CFArrayCreateMutable(kCFAllocatorDefault, capacity, &kCFTypeArrayCallBacks);
    
    // Add args to the array
    CFStringRef arg0Ref = NULL;
    if (NULL != arg0)
    {
        CFStringRef arg0Ref = CFStringCreateWithCString(kCFAllocatorDefault, arg0, kCFStringEncodingMacRoman);
        CFArrayAppendValue(argArrayRef, arg0Ref);
    }
    CFStringRef arg1Ref = NULL;
    if (NULL != arg1)
    {
        CFStringRef arg1Ref = CFStringCreateWithCString(kCFAllocatorDefault, arg1, kCFStringEncodingMacRoman);
        CFArrayAppendValue(argArrayRef, arg1Ref);
    }
    
    wxLogDebug(wxT("launch %s"), appPath);
    
    // Create the params object for executing the app
    LSApplicationParameters params = {0, kLSLaunchDontAddToRecents, &appRef, NULL, NULL, NULL};
    params.argv = argArrayRef;  // include the args array
    
    // Execute the app asynchronously, saving its ProcessSerialNumber on return
    status = LSOpenApplication(&params, procManager->GetPsnPointer());
    pid_t resultPid;
    if (noErr != status)
    {
        m_lastError.Printf(wxT("LaunchApp: LSOpenApplication failed: %d"), status);
        wxLogDebug(m_lastError);
        resultPid = PID_NONE;
    }
    else
    {
        // Get a unix pid to return
        resultPid = procManager->SetPid();
        if (PID_NONE != resultPid)
        {
            wxLogDebug(wxT("LSOpenApplication success"));
        }
        else
        {
            // Something horrible happened
            ::KillProcess(procManager->GetPsnPointer());
            m_lastError.Printf(wxT("LaunchApp: Setting pid failed."));
            wxLogDebug(m_lastError);
        }
    }
    
    // Clean up
    CFArrayRemoveAllValues(argArrayRef);
    CFRelease(argArrayRef);
    if (arg0Ref) CFRelease(arg0Ref);
    if (arg1Ref) CFRelease(arg1Ref);
    
    return resultPid;
}


