/////////////////////////////////////////////////////////////////////////////
// Name:        test_gui.cpp
// Purpose:     Test program for wxWidgets with GUI features
// Author:      Wlodzimierz Skiba
// Modified by:
// Created:     06/04/2004
// RCS-ID:      $Id: test_gui.cpp,v 1.0 2004/04/06 00:00:00 ABX Exp $
// Copyright:   (c) Wlodzimierz Skiba
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/cppunit.h"
#include "wx/progdlg.h"

#define SUIT_PREFIX _T("Run ")

// ----------------------------------------------------------------------------
// wxTextOutputer
// ----------------------------------------------------------------------------

CPPUNIT_NS_BEGIN

class CPPUNIT_API wxOutputter : public Outputter
{
public:
    wxOutputter( TestResultCollector *result, 
                 wxTextCtrl *textctrl);

    void write();

    virtual void printStart();

    virtual void printFailures();

    virtual void printHeader();

    virtual void printFailure( TestFailure *failure,
                               int failureNumber );
    virtual void printFailureListMark( int failureNumber );
    virtual void printFailureTestName( TestFailure *failure );
    virtual void printFailureType( TestFailure *failure );
    virtual void printFailureLocation( SourceLine sourceLine );
    virtual void printFailureDetail( Exception *thrownException );
    virtual void printFailureWarning();
    virtual void printStatistics();
    virtual void printNewLine();

    virtual void printStartTest( Test *test );
    virtual void printAddFailure( const TestFailure *failure );

#if wxUSE_PROGRESSDLG
    void setProgress( wxProgressDialog *progress = NULL)
                    { m_progress = progress; }
#endif

protected:
    TestResultCollector *m_result;
    wxTextCtrl *m_textctrl;

private:
    /// Prevents the use of the copy constructor.
    wxOutputter( const wxOutputter &copy );

    /// Prevents the use of the copy operator.
    void operator =( const wxOutputter &copy );

#if wxUSE_PROGRESSDLG
    wxProgressDialog *m_progress;
    int m_count;
#endif
};
 
wxOutputter::wxOutputter( TestResultCollector *result,
                          wxTextCtrl *textctrl)
{
    m_textctrl = textctrl;
    m_result = result;
#if wxUSE_PROGRESSDLG
    m_progress = NULL;
    m_count = 0;
#endif
}

void wxOutputter::write() 
{
    printHeader();
    m_textctrl->AppendText(_T("\n"));
    printFailures();
    m_textctrl->AppendText(_T("\n"));
}

void wxOutputter::printStart() 
{
    wxString msg;
    msg << _("build: ") << _T( WX_BUILD_OPTIONS_SIGNATURE ) << _T("\n");
    m_textctrl->AppendText( msg );
#if wxUSE_PROGRESSDLG
    m_count = 0;
#endif
}

void wxOutputter::printFailures()
{
    TestResultCollector::TestFailures::const_iterator itFailure = m_result->failures().begin();
    int failureNumber = 1;
    while ( itFailure != m_result->failures().end() ) 
    {
        m_textctrl->AppendText(_T("\n"));
        printFailure( *itFailure++, failureNumber++ );
    }
}


void wxOutputter::printFailure( TestFailure *failure,
                                int failureNumber )
{
    printFailureListMark( failureNumber );
    m_textctrl->AppendText(_T(" "));
    printFailureTestName( failure );
    m_textctrl->AppendText(_T(" "));
    printFailureType( failure );
    m_textctrl->AppendText(_T(" "));
    printFailureLocation( failure->sourceLine() );
    m_textctrl->AppendText(_T("\n"));
    printFailureDetail( failure->thrownException() );
    m_textctrl->AppendText(_T("\n"));
}


void wxOutputter::printFailureListMark( int failureNumber )
{
    wxString msg;
    msg << failureNumber << _T(")");
    m_textctrl->AppendText(msg);
}


void wxOutputter::printFailureTestName( TestFailure *failure )
{
    wxString msg;
    msg << _T("test: ") << wxString::FromAscii( failure->failedTestName().c_str() );
    m_textctrl->AppendText(msg);
}


void wxOutputter::printFailureType( TestFailure *failure )
{
    m_textctrl->AppendText(_T("("));
    printAddFailure( failure );
    m_textctrl->AppendText(_T(")"));
}


void wxOutputter::printFailureLocation( SourceLine sourceLine )
{
    if ( !sourceLine.isValid() )
        return;

    wxString msg;
    msg << _T("line: ") << sourceLine.lineNumber()
        << _T(" ") << wxString::FromAscii( sourceLine.fileName().c_str() );
    m_textctrl->AppendText(msg);
}


void wxOutputter::printFailureDetail( Exception *thrownException )
{
    wxString msg;
    msg << wxString::FromAscii( thrownException->message().shortDescription().c_str() ) << _T("\n");
    msg << wxString::FromAscii( thrownException->message().details().c_str() );
    m_textctrl->AppendText(msg);
}


void wxOutputter::printHeader()
{
    if ( m_result->wasSuccessful() )
    {
        wxString msg;
        msg << _T("\nOK (") << m_result->runTests () << _T(" tests)\n"); 
        m_textctrl->AppendText(msg);
    }
    else
    {
        m_textctrl->AppendText(_T("\n"));
        printFailureWarning();
        printStatistics();
    }
}


void wxOutputter::printFailureWarning()
{
    m_textctrl->AppendText( _T( "!!!FAILURES!!!\n" ) );
}


void wxOutputter::printStatistics()
{
    wxString msg;
    msg << _T("Test Results:\n") 
        << _T("Run:  ") << m_result->runTests()
        << _T("   Failures: ") << m_result->testFailures()
        << _T("   Errors: ") << m_result->testErrors()
        << _T("\n");
    m_textctrl->AppendText(msg);
}

void wxOutputter::printNewLine()
{
    m_textctrl->AppendText(_T("\n"));
}

void wxOutputter::printStartTest( Test *test )
{
    m_textctrl->AppendText(_T("."));
    wxSafeYield();
#if wxUSE_PROGRESSDLG
    m_count++;
    wxString name = wxString::FromAscii( test->getName().c_str() );
    if (m_progress) m_progress->Update( m_count , name );
#endif
}

void wxOutputter::printAddFailure( const TestFailure *failure )
{
    m_textctrl->AppendText( failure->isError() ? _T("E") : _T("F") );
}

// ----------------------------------------------------------------------------
// wxTestProgressListener
// ----------------------------------------------------------------------------

class CPPUNIT_API wxTestProgressListener : public TestListener
{
public:
    wxTestProgressListener( wxOutputter *outputter =NULL );

    void startTest( Test *test );

    void addFailure( const TestFailure &failure );

    void endTestRun( Test *test, TestResult *eventManager );

private:
    wxTestProgressListener( const wxTestProgressListener &copy );

    void operator =( const wxTestProgressListener &copy );

private:
    wxOutputter *m_outputter;
};


wxTestProgressListener::wxTestProgressListener( wxOutputter *outputter )
{
    m_outputter = outputter;
}


void wxTestProgressListener::startTest( Test *test )
{
    m_outputter->printStartTest( test );
}


void wxTestProgressListener::addFailure( const TestFailure &failure )
{
    m_outputter->printAddFailure( &failure );
}


void wxTestProgressListener::endTestRun( Test *WXUNUSED(test), TestResult *WXUNUSED(eventManager) )
{
    m_outputter->printNewLine();
}


// ----------------------------------------------------------------------------
// wxTestRunner
// ----------------------------------------------------------------------------

class CPPUNIT_API wxTestRunner : public TestRunner
{
public:
    wxTestRunner( TestResultCollector *result, wxOutputter *outputter =NULL );

    virtual ~wxTestRunner();

    bool runTests( std::string testPath ="",
                   bool doWait = false,
                   bool doPrintResult = true,
                   bool doPrintProgress = true );

    TestResultCollector &result() const;

    TestResult &eventManager() const;

protected:
    virtual void wait( bool doWait );
    virtual void printResult( bool doPrintResult );

    TestResultCollector *m_result;
    TestResult *m_eventManager;
    wxOutputter *m_outputter;
}; 

wxTestRunner::wxTestRunner( TestResultCollector *result, wxOutputter *outputter ) 
    : m_eventManager( new TestResult() )
{
  m_outputter = outputter;
  m_result = result;
  m_eventManager->addListener( m_result );
}


wxTestRunner::~wxTestRunner()
{
  delete m_eventManager;
}


bool wxTestRunner::runTests( std::string testPath,
                             bool doWait,
                             bool doPrintResult,
                             bool doPrintProgress )
{
    m_outputter->printStart();

    wxTestProgressListener progress( m_outputter );
    if ( doPrintProgress )
        m_eventManager->addListener( &progress );

    TestRunner *pThis = this;
    pThis->run( *m_eventManager, testPath );

    if ( doPrintProgress )
        m_eventManager->removeListener( &progress );

    printResult( doPrintResult );
    wait( doWait );

    return m_result->wasSuccessful();
}


void wxTestRunner::wait( bool doWait )
{
    if ( doWait ) 
    {
        wxMessageBox(_T("Waiting message"));
    }
}


void wxTestRunner::printResult( bool doPrintResult )
{
    m_outputter->printNewLine();
    if ( doPrintResult )
        m_outputter->write();
}


TestResultCollector& wxTestRunner::result() const
{
    return *m_result;
}


TestResult& wxTestRunner::eventManager() const
{
    return *m_eventManager;
}


CPPUNIT_NS_END
 
using namespace std;
using namespace CppUnit;

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "test.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

class TestApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class TestFrame : public wxFrame
{
public:
    TestFrame(const wxString& title);

    void RunTests(wxString& test_name);

    // event handlers
    void OnQuit(wxCommandEvent& event);
    void OnClearLog(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void OnTest(wxCommandEvent& event);

    void OnSize(wxSizeEvent& event);

private:
    wxTextCtrl *m_textctrl;
    int m_tests;

    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

enum
{
    Test_Quit = wxID_EXIT,
    Test_About = wxID_ABOUT,
    Test_ClearLog = wxID_HIGHEST,
    Test_HIGHEST
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(TestFrame, wxFrame)
    EVT_MENU(Test_Quit,  TestFrame::OnQuit)
    EVT_MENU(Test_ClearLog, TestFrame::OnClearLog)
    EVT_MENU(Test_About, TestFrame::OnAbout)
    EVT_SIZE(TestFrame::OnSize)
    // consider all menu positions not considered earlier
    EVT_MENU_RANGE(Test_HIGHEST, INT_MAX, TestFrame::OnTest)
END_EVENT_TABLE()

IMPLEMENT_APP(TestApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

bool TestApp::OnInit()
{
    // create the main application window
    TestFrame *frame = new TestFrame(_T("Unit Test"));

    frame->Show(true);

    return true;
}

// ----------------------------------------------------------------------------
// creation of menu with tests
// ----------------------------------------------------------------------------

int GetItemID()
{
    static int Last_ID = Test_HIGHEST;
    return Last_ID++;
}

wxMenu *List(Test *test, wxString& title, int &count, int depth = 0)
{
    wxMenu *list = new wxMenu;
    TestSuite *suite = dynamic_cast<TestSuite*>(test);

    title = wxString::FromAscii( test->getName().c_str() );

    if (suite)
    {
        wxString name;
        name << SUIT_PREFIX << title;
        list->Append(GetItemID(), name);

        typedef const vector<Test*> Tests;
        typedef Tests::const_iterator Iter;

        Tests& tests = suite->getTests();

        for (Iter it = tests.begin(); it != tests.end(); ++it)
        {
            if (list->GetMenuItemCount()==1)
                list->AppendSeparator();

            wxString subtitle;
            wxMenu *sublist = List(*it, subtitle, count, depth + 1);

            if (sublist->GetMenuItemCount()==1)
                list->Append(GetItemID(), subtitle);
            else
                list->Append(GetItemID(), subtitle, sublist);
        }
    }
    else
    {
        list->Append(GetItemID(), title);
        count++;
    }

    return list;
}

wxMenu *CreateTestMenus(int& count)
{
    auto_ptr<Test> test(TestFactoryRegistry::getRegistry().makeTest());
    wxString title;
    wxMenu *menu = List(test.get(),title,count);
    return menu;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
TestFrame::TestFrame(const wxString& title)
          : wxFrame(NULL, wxID_ANY, title)
{
    m_textctrl = NULL;

    // set the frame icon
    SetIcon(wxICON(test));

    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(Test_ClearLog, _T("Clear &log\tCtrl-L"));
    fileMenu->Append(Test_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

    m_tests = 0;
    wxMenu *testMenu = CreateTestMenus(m_tests);

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Test_About, _T("&About...\tF1"), _T("Show about dialog"));

    wxMenuBar *menuBar = new wxMenuBar();

    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(testMenu, _T("&Tests"));
    menuBar->Append(helpMenu, _T("&Help"));

    SetMenuBar(menuBar);

    // create the log text window and initialize it with build info
    m_textctrl = new wxTextCtrl(this, -1, _T(""),
                                wxDefaultPosition, wxDefaultSize,
                                wxTE_MULTILINE | wxTE_READONLY);
    m_textctrl->SetEditable(false);
}

// event handlers

void TestFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void TestFrame::OnClearLog(wxCommandEvent& WXUNUSED(event))
{
    m_textctrl->Clear();
}

void TestFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg << _("Test program for wxWidgets\n")
        << _("build: ") << _T( WX_BUILD_OPTIONS_SIGNATURE );
    wxMessageBox(msg, _T("About ..."), wxOK | wxICON_INFORMATION, this);
}

void TestFrame::OnTest(wxCommandEvent& event)
{
    int id = event.GetId();
    wxMenuItem *item = GetMenuBar()->FindItem(id);
    if(item)
    {
        wxString label = item->GetLabel(); 
        if ( label.StartsWith( SUIT_PREFIX ) )
            label.Replace( SUIT_PREFIX, _T(""), false );
        RunTests(label);
    }
}

void TestFrame::RunTests(wxString& test_name)
{
    wxLogNull log;
    TestResultCollector result;
    wxOutputter out(&result,m_textctrl);
    wxTestRunner runner(&result,&out);

    string name = string(test_name.mb_str());

    auto_ptr<Test> test(TestFactoryRegistry::getRegistry(name).makeTest());
    TestSuite *suite = dynamic_cast<TestSuite*>(test.get());

    if (suite && suite->countTestCases() != 0)
        runner.addTest(test.release());
    else
    {
        m_textctrl->AppendText(_T("This is test suit component, select complete test suit.\n"));
        return;
    }

#if wxUSE_PROGRESSDLG
    wxProgressDialog progress( _T("Tests for wxWidgets"),
                               wxEmptyString,
                               m_tests,
                               this,
                               wxPD_ELAPSED_TIME | wxPD_AUTO_HIDE );
    out.setProgress( &progress );
#endif

    runner.runTests("", false, true, true);

#if wxUSE_PROGRESSDLG
    out.setProgress( NULL );
#endif
}

void TestFrame::OnSize(wxSizeEvent& WXUNUSED(event))
{
    if ( !m_textctrl )
        return;

    wxSize size = GetClientSize();
    m_textctrl->SetSize(0, 0, size.x, size.y);

#ifdef __WXUNIVERSAL__
    PositionMenuBar();
#endif // __WXUNIVERSAL__
}

 	  	 
