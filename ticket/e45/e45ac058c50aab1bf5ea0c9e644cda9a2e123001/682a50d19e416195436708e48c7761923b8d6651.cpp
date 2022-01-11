
//*****
// This code crashes at the wxIPV4address() call in the worker thread
//*****
#include <wx/wx.h>
#include <wx/socket.h>
#include <wx/fileconf.h>
#include <iostream>


class TestThread : public wxThread
{
public:
    void* Entry();
};

void* TestThread::Entry()
{
    std::cout << "TestThread running\n";

    wxIPV4address addy;
    addy.Service(9999);
    wxSocketServer* ss = new wxSocketServer( addy );

    std::cout << "SocketServer created\n";

    return 0;
}

class TestApp : public wxAppConsole
{
public:
    virtual int OnRun();
};

DECLARE_APP(TestApp)
IMPLEMENT_APP(TestApp)

int TestApp::OnRun()
{
    std::cout << "Creating a test thread...\n";

    wxIPV4address make_it_safe;

    TestThread* tt = new TestThread();
    tt->Create();
    tt->Run();

    std::cout << "Pausing to allow thread to crash\n";
    wxFgetc(stdin);

    return 0;
}


//****************************************************************
//****************************************************************

//*****
//This code works just fine, after the wxIPV4address is kickstarted in the main thread first
//*****


#include <wx/wx.h>
#include <wx/socket.h>
#include <wx/fileconf.h>
#include <iostream>


class TestThread : public wxThread
{
public:
    void* Entry();
};

void* TestThread::Entry()
{
    std::cout << "TestThread running\n";

    wxIPV4address addy;
    addy.Service(9999);
    wxSocketServer* ss = new wxSocketServer( addy );

    std::cout << "SocketServer created\n";

    return 0;
}

class TestApp : public wxAppConsole
{
public:
    virtual int OnRun();
};

DECLARE_APP(TestApp)
IMPLEMENT_APP(TestApp)

int TestApp::OnRun()
{
    std::cout << "Creating a test thread...\n";

    wxIPV4address make_it_safe;

    TestThread* tt = new TestThread();
    tt->Create();
    tt->Run();

    std::cout << "Pausing to allow thread to crash\n";
    wxFgetc(stdin);

    return 0;
}

 	  	 
