#include <wx/wx.h>

class MyEventHandler : public wxEvtHandler
{
public:
	bool ProcessEvent(wxEvent&);
};

class MyThread : public wxThread
{
public:
	MyThread(wxEvtHandler* evthandler) : eventhandler(evthandler)
	{}
private:
	ExitCode Entry();
	wxEvtHandler* eventhandler;
};

class MyApp : public wxApp
{
private:
	bool OnInit();
	MyEventHandler eventhandler;
	MyThread* thethread;
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	wxLog::SetActiveTarget(new wxLogStderr);
	thethread = new MyThread(&eventhandler);
	thethread->Create();
	thethread->Run();
	return true;
}

bool MyEventHandler::ProcessEvent(wxEvent& event)
{
	wxLogMessage("event received");
	return true;
}

wxThread::ExitCode MyThread::Entry()
{
	while (!TestDestroy())
	{
		wxSleep(2);
		wxLogMessage("sending event");
		eventhandler->QueueEvent(new wxTimerEvent);
		wxLogMessage("event sent");
	}
	return (ExitCode)0;
}
