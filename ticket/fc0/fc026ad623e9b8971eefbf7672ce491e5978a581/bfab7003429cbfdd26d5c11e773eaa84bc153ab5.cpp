#include <iostream>
#include <wx/wx.h>

using namespace std;

class CMyDlg : public wxFrame
{
public:
   CMyDlg();
   virtual ~CMyDlg();

private:
   DECLARE_EVENT_TABLE()
   void OnLButtonDown(wxMouseEvent &event);
   void OnLButtonUp(wxMouseEvent &event);
   void OnMouseMove(wxMouseEvent &event);
};

class CMyApp : public wxApp
{
public:
   virtual bool OnInit();
};


IMPLEMENT_APP(CMyApp)

bool CMyApp::OnInit()
{
   CMyDlg *dlg = new CMyDlg();
   dlg->Show(true);

   return true;
}

CMyDlg::CMyDlg()
   : wxFrame(NULL, wxID_ANY, wxT("Test Program"), wxDefaultPosition, wxSize(110, 77))
{
   Centre();
}

CMyDlg::~CMyDlg()
{
}

BEGIN_EVENT_TABLE(CMyDlg, wxFrame)
   EVT_LEFT_DOWN(CMyDlg::OnLButtonDown)
   EVT_LEFT_UP(CMyDlg::OnLButtonUp)
   EVT_MOTION(CMyDlg::OnMouseMove)
END_EVENT_TABLE()

void CMyDlg::OnLButtonDown(wxMouseEvent &event)
{
   wxSetCursor(wxCursor(wxCURSOR_SIZEWE));
#if 1  // If this is enabled, neither of the wxSetCursor calls will work
   CaptureMouse();
#endif
   wxSetCursor(wxCursor(wxCURSOR_SIZEWE));
}

void CMyDlg::OnLButtonUp(wxMouseEvent &event)
{
   wxSetCursor(wxCursor(wxCURSOR_ARROW));
   if (HasCapture())
      ReleaseMouse();
}

void CMyDlg::OnMouseMove(wxMouseEvent &event)
{
   wxSetCursor(wxCursor(wxCURSOR_SIZENS));
}
