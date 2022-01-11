#include <wx/module.h>
#include <wx/thread.h>

using namespace std;

//*****************************************************************************
// TCTest is a joinable thread that is created/run on construction and stops
// on destruction.  The thread itself does nothing in this example.
//*****************************************************************************
struct TCTest : public wxThread
{
  TCTest()
    : wxThread(wxTHREAD_JOINABLE)
  {
    Create();
    Run();
  }

  void* Entry()
  {
    return 0;
  }

  ~TCTest()
  {
    Wait();
  }
};

//*****************************************************************************
// TCTestModule is a wxModule that creates a TCTest OnInit and destroys a
// TCTest OnExit.  It depends on wxThreadModule.
//*****************************************************************************
class TCTestModule : public wxModule
{
  public:

    TCTest* mpTest;

    TCTestModule()
      : mpTest(0)
    {
      AddDependency(wxClassInfo::FindClass("wxThreadModule"));
    }

    bool OnInit()
    {
      mpTest = new TCTest;

      return true;
    }

    void OnExit()
    {
      // The following line will fail because wxThread::Wait needs wxTraits
      // which are provided by wxApp which has been destroyed:
      mpTest->Wait();

      delete mpTest;

      mpTest = 0;
    }

  DECLARE_DYNAMIC_CLASS(TCTestModule)
};

IMPLEMENT_DYNAMIC_CLASS(TCTestModule, wxModule)
