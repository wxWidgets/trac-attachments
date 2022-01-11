#include <iostream>
#include "wx/wx.h"
#include "wx/utils.h"

class MovableButton : public wxButton
{
        bool dragging;
        int x,y;
        wxPanel* parent;
public:
       
        MovableButton(wxPanel* parent) : wxButton(parent, wxID_ANY, wxT("Drag me around"))
        {
                MovableButton::parent = parent;
                dragging = false;
        }
               
        void onMouseDown(wxMouseEvent& evt)
        {
                CaptureMouse();
                x = evt.GetX();
                y = evt.GetY();
                dragging=true;
        }
        void onMouseUp(wxMouseEvent& evt)
        {
                ReleaseMouse();
                dragging=false;
        }
        void onMove(wxMouseEvent& evt)
        {
                if(dragging)
                {
                        wxPoint mouseOnScreen = wxGetMousePosition();
                        int newx = mouseOnScreen.x - x;
                        int newy = mouseOnScreen.y - y;
                        this->Move( parent->ScreenToClient( wxPoint(newx, newy) ) );
                }
        }
       
        DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MovableButton,wxButton)
EVT_LEFT_DOWN(MovableButton::onMouseDown)
EVT_LEFT_UP(MovableButton::onMouseUp)
EVT_MOTION(MovableButton::onMove)
END_EVENT_TABLE()

class MyFrame : public wxFrame
{
        wxPanel* mainPanel;
public:
        MyFrame(wxWindow* ptr, int id, wxString name, wxPoint pos, wxSize size) : wxFrame(ptr,id,name,pos,size)
{
                mainPanel = new wxPanel(this, wxID_ANY);
                MovableButton* btn = new MovableButton(mainPanel);
               
                Center();
                Show();
}
};

class MyApp: public wxApp
{
    virtual bool OnInit();
};


IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame(NULL, wxID_ANY,  wxT("Hello World"), wxDefaultPosition, wxSize(640,480));
       
    return true;
} 
