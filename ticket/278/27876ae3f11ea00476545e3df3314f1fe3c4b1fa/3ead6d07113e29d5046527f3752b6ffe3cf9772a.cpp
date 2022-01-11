#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
    #include "wx/process.h"
#endif

//////////////////////////////////////////////////
// MyApp class declaration
//////////////////////////////////////////////////
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

//////////////////////////////////////////////////
// sysProcess class declaration (from pgAdmin)
//////////////////////////////////////////////////
class sysProcess : public wxProcess
{
public:
    sysProcess(wxEvtHandler *evh);

    bool Run(const wxString &exec);
    void Abort();
    void SetEnvironment(const wxArrayString &environment);
    wxString ReadInputStream();
    wxString ReadErrorStream();

    static sysProcess *Create(const wxString &exec, wxEvtHandler *evh=0, wxArrayString *env=0);

private:
    int pid;
    void OnTerminate(int pid, int status) const;
    wxString ReadStream(wxInputStream *input);
};

//////////////////////////////////////////////////
// MyFrame class declaration
//////////////////////////////////////////////////
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
    void Go(wxCommandEvent &ev);
    void OnEndProcess(wxProcessEvent& event);
    void OnPollProcess(wxTimerEvent& event);
    void checkStreams();

    wxTextCtrl *ip, 
               *op;
    wxButton   *go;
    sysProcess *proc;
    wxTimer    *tm;

    DECLARE_EVENT_TABLE()
};

//////////////////////////////////////////////////
// MyApp class implementation
//////////////////////////////////////////////////
IMPLEMENT_APP(MyApp)

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    MyFrame *window = new MyFrame(_T("wxProcess test app"));
    window->Show(true);
    return true;
}

//////////////////////////////////////////////////
// MyFrame class implementation
//////////////////////////////////////////////////
const int ID_PROCESS_IP = 101;
const int ID_PROCESS_OP = 102;
const int ID_PROCESS_GO = 103;
const int ID_PROCESS_TM = 104;

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(ID_PROCESS_GO, MyFrame::Go)
    EVT_END_PROCESS(-1,       MyFrame::OnEndProcess)
    EVT_TIMER(ID_PROCESS_TM,  MyFrame::OnPollProcess)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title) 
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER | wxRESIZE_BOX | wxMAXIMIZE_BOX))
{
    wxPanel *pnl = new wxPanel(this);
    ip = new wxTextCtrl(pnl, ID_PROCESS_IP, _T("ls -alR /"), wxPoint(5, 5), wxSize(710, 20));
    go = new wxButton(pnl, ID_PROCESS_GO, _T("Execute"), wxPoint(720, 3), wxSize(65, 25));
    op = new wxTextCtrl(pnl, ID_PROCESS_OP, wxEmptyString, wxPoint(5, 30), wxSize(790, 530), wxTE_MULTILINE | wxHSCROLL);
    tm = new wxTimer(this, ID_PROCESS_TM);
    proc = 0;
}

void MyFrame::Go(wxCommandEvent &ev)
{
    if (op)
        op->SetValue(_T("Executing: ") + ip->GetValue() + _T("\n"));

    if (proc)
        delete proc;

    proc = new sysProcess(this);

    if (wxExecute(ip->GetValue(), wxEXEC_ASYNC, proc))
    {
        go->Disable();
        if (op)
        {
            checkStreams();
            tm->Start(100L);
        }
        return;
    }
    else
    {
        delete proc;
        proc=0;
        op->AppendText(_T("Failed to execute process!"));
        return;
    }
}

void MyFrame::OnEndProcess(wxProcessEvent &ev)
{
    tm->Stop();

    checkStreams();
    op->AppendText(_T("\n")
                   + wxString::Format(_("Process returned exit code %d."), ev.GetExitCode())
                   + _T("\n"));

    if (proc)
    {
        delete proc;
        proc=0;
    }
    go->Enable();
}

void MyFrame::OnPollProcess(wxTimerEvent &ev)
{
    checkStreams();
}

void MyFrame::checkStreams()
{
    if (proc)
    {
        op->AppendText(proc->ReadErrorStream());
        op->AppendText(proc->ReadInputStream());
    }
}

//////////////////////////////////////////////////
// sysProcess class implementation
//////////////////////////////////////////////////
sysProcess::sysProcess(wxEvtHandler *evh)
: wxProcess(evh)
{
    pid=0;
    Redirect();
}


sysProcess *sysProcess::Create(const wxString &exec, wxEvtHandler *evh, wxArrayString *env)
{
    sysProcess *proc=new sysProcess(evh);
    if (env)
        proc->SetEnvironment(*env);
    
    if (!proc->Run(exec))
    {
        delete proc;
        proc=0;
    }
    return proc;
}


bool sysProcess::Run(const wxString &exec)
{
    pid = wxExecute(exec, wxEXEC_ASYNC, this);

    return (pid != 0);
}


void sysProcess::SetEnvironment(const wxArrayString &environment)
{
    size_t i;
    for (i=0 ; i < environment.GetCount() ; i++)
    {
        wxString str=environment.Item(i);
        wxSetEnv(str.BeforeFirst('='), str.AfterFirst('='));
    }
}


void sysProcess::Abort()
{
    if (pid)
        wxKill(pid, wxSIGTERM);
}


wxString sysProcess::ReadInputStream()
{
    if (IsInputAvailable())
        return ReadStream(GetInputStream());
    return wxEmptyString;
}


wxString sysProcess::ReadErrorStream()
{
    if (IsErrorAvailable())
        return ReadStream(GetErrorStream());
    return wxEmptyString;
}


wxString sysProcess::ReadStream(wxInputStream *input)
{
    wxString str;

    char buffer[1000+1];
    size_t size=1;
    while (size && !input->Eof())
    {
        input->Read(buffer, sizeof(buffer)-1);
        size=input->LastRead();
        if (size)
        {
            buffer[size]=0;
            str.Append(wxString::Format(wxT("%s"),wxString(buffer,wxConvLibc).c_str()));
        }
    }
    return str;
}

 	  	 
