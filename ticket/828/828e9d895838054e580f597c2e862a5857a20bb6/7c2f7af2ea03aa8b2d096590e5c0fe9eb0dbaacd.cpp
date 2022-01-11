#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/wx.h"
//#include "wx/odcombo.h"


class MyApplication: public wxApp
{
protected:
    bool OnInit();
};

MyApplication *pApp;

class MyFrame;
class MyMainWindow : public wxFrame
{
protected:
    void OnControlEvent(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    
public:
    MyMainWindow(wxWindow * parent, wxWindowID id, const wxPoint &pos, const wxSize &sizeid);
    
    DECLARE_EVENT_TABLE()
    
private:
    wxTopLevelWindow* pFrame;
};

class Panel1 : public wxPanel
{
protected:
    wxTextCtrl* c1;
    wxTextCtrl* c2;
    wxTextCtrl* c3;
    
public:
    Panel1(wxWindow* frame, wxWindowID id,const wxPoint& pos, const wxSize& size, long style, const wxString& name);
};

class Panel2 : public wxPanel
{
protected:
    wxTextCtrl* c1;
    wxTextCtrl* c2;
    wxTextCtrl* c3;
    
public:
    Panel2(wxWindow* frame, wxWindowID id,const wxPoint& pos, const wxSize& size, long style, const wxString& name);
};

class Panel3 : public wxPanel
{
protected:
    wxTextCtrl* c1;
    wxTextCtrl* c2;
    wxTextCtrl* c3;
    
public:
    Panel3(wxWindow* frame, wxWindowID id,const wxPoint& pos, const wxSize& size, long style, const wxString& name);
};

class MyFrame: public wxFrame
{
public:
    MyFrame(MyMainWindow * parent, wxWindowID id, const wxPoint &pos, const wxSize &sizeid);
    
private:
    Panel1* p1;
    Panel2* p2;
    Panel3* p3;
};

class MyDialog: public wxDialog
{
public:
    MyDialog(MyMainWindow * parent, wxWindowID id, const wxPoint &pos, const wxSize &sizeid);
    
private:
    Panel1* p1;
    Panel2* p2;
    Panel3* p3;
};

Panel1::Panel1(wxWindow* frame, wxWindowID id,const wxPoint& pos, const wxSize& size, long style, const wxString& name) :
wxPanel(frame,id,pos,size,style,name)
{
    c1 = new wxTextCtrl(this,wxID_ANY,wxString("ctrl1"),wxPoint(10, 10), wxSize(100, 25));
    c2 = new wxTextCtrl(this,wxID_ANY,wxString("ctrl2"),wxPoint(120, 10), wxSize(100, 25));
    c3 = new wxTextCtrl(this,wxID_ANY,wxString("ctrl3"),wxPoint(240, 10), wxSize(100, 25));
}

Panel2::Panel2(wxWindow* frame, wxWindowID id,const wxPoint& pos, const wxSize& size, long style, const wxString& name) :
wxPanel(frame,id,pos,size,style,name)
{
    c1 = new wxTextCtrl(this,wxID_ANY,wxString("ctrl4"),wxPoint(10, 10), wxSize(100, 25));
    c2 = new wxTextCtrl(this,wxID_ANY,wxString("ctrl5"),wxPoint(120, 10), wxSize(100, 25));
    c3 = new wxTextCtrl(this,wxID_ANY,wxString("ctrl6"),wxPoint(240, 10), wxSize(100, 25));
}

Panel3::Panel3(wxWindow* frame, wxWindowID id,const wxPoint& pos, const wxSize& size, long style, const wxString& name) :
wxPanel(frame,id,pos,size,style,name)
{
    c1 = new wxTextCtrl(this,wxID_ANY,wxString("ctrl7"),wxPoint(10, 10), wxSize(100, 25));
    c2 = new wxTextCtrl(this,wxID_ANY,wxString("ctrl8"),wxPoint(120, 10), wxSize(100, 25));
    c3 = new wxTextCtrl(this,wxID_ANY,wxString("ctrl9"),wxPoint(240, 10), wxSize(100, 25));
}

MyFrame::MyFrame(MyMainWindow * parent, wxWindowID id, const wxPoint &pos, const wxSize &sizeid):
wxFrame(parent,id,wxString("My frame"),pos,sizeid)
{
    p1 = new Panel1(this, wxID_ANY, wxPoint(10, 10), wxSize(400, 150), wxTAB_TRAVERSAL,wxString("panel1"));
    p2 = new Panel2(this, wxID_ANY, wxPoint(350, 350), wxSize(400, 150), wxTAB_TRAVERSAL,wxString("panel2"));
    p3 = new Panel3(this, wxID_ANY, wxPoint(700, 700), wxSize(400, 150), wxTAB_TRAVERSAL,wxString("panel3"));
}

MyDialog::MyDialog(MyMainWindow * parent, wxWindowID id, const wxPoint &pos, const wxSize &sizeid):
wxDialog(parent,id,wxString("My dialog"),pos,sizeid)
{
    p1 = new Panel1(this, wxID_ANY, wxPoint(10, 10), wxSize(400, 150), wxTAB_TRAVERSAL,wxString("panel1"));
    p2 = new Panel2(this, wxID_ANY, wxPoint(350, 350), wxSize(400, 150), wxTAB_TRAVERSAL,wxString("panel2"));
    p3 = new Panel3(this, wxID_ANY, wxPoint(700, 700), wxSize(400, 150), wxTAB_TRAVERSAL,wxString("panel3"));
}

BEGIN_EVENT_TABLE(MyMainWindow, wxWindow)
EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED, MyMainWindow::OnControlEvent)
EVT_CLOSE(MyMainWindow::OnClose)
END_EVENT_TABLE()

MyMainWindow :: MyMainWindow(wxWindow * parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
: wxFrame(parent, id, wxString("Example"), pos, size)
{
    new wxButton(this, 1, wxString("Show Frame"), wxPoint(14, 14), wxSize(200, 22));
    new wxButton(this, 2, wxString("Show Dialog"), wxPoint(14, 50), wxSize(200, 22));
}

void MyMainWindow::OnControlEvent(wxCommandEvent &event)
{
    if (event.GetEventType() == wxEVT_COMMAND_BUTTON_CLICKED)
    {
        if(event.GetId() == 1)
        {
            pFrame = new MyFrame(NULL, wxID_ANY, wxPoint(50, 50), wxSize(1200, 1000));
            pFrame->Show();
        }
        else
        {
            pFrame = new MyDialog(NULL, wxID_ANY, wxPoint(50, 50), wxSize(1200, 1000));
            pFrame->Show();
        }
    }
}

void MyMainWindow::OnClose(wxCloseEvent& event)
{
    pApp->SetExitOnFrameDelete(true);
    Destroy();
}

IMPLEMENT_APP(MyApplication)

bool MyApplication::OnInit()
{
    MyMainWindow *pMainWindow = new MyMainWindow(NULL, 99, wxPoint(50, 50), wxSize(500, 500));
    pMainWindow->Show();
    pApp = this;
    return true;
}

