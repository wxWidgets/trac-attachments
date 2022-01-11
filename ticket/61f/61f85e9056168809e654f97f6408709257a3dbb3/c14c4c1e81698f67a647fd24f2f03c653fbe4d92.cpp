#include "wx/wx.h"

//Main window class
class MyFrame: public wxFrame
{
public:
    MyFrame();
    void OnLeftDown(wxMouseEvent& event);
private:
         //Declaration event table
    DECLARE_EVENT_TABLE()

};

//Define the event table
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_LEFT_DOWN(MyFrame::OnLeftDown)
END_EVENT_TABLE()

void draw(wxFrame * win)
{
        wxClientDC dc(win);
        dc.SetPen(*wxRED_PEN);
        dc.SetBrush(*wxRED_BRUSH);
	dc.DrawRectangle(50,0,33,300);
	dc.DrawRectangle(300,0,33,300);

	dc.SetPen(*wxGREEN_PEN);
        dc.SetBrush(*wxGREEN_BRUSH);
	dc.DrawRectangle(84,0,33,300);
	dc.DrawRectangle(334,0,33,300);

	dc.SetPen(*wxBLUE_PEN);
        dc.SetBrush(*wxBLUE_BRUSH);
	dc.DrawRectangle(118,0,33,300);
	dc.DrawRectangle(368,0,33,300);
	
	dc.SetPen(*wxBLACK_PEN);
        dc.SetBrush(*wxBLACK_BRUSH);
	dc.DrawRectangle(0,0,200,150);
	
	//dc.DrawRectangle(250,0,200,150);
	for(int x=0;x < 200; x++)
	{
	  for(int y=0; y < 150; y++)
	  {
	     dc.DrawPoint(250+x,y);	  
	  }
	}
        dc.SetPen(wxNullPen);
        dc.SetBrush(wxNullBrush);
}


//Main window class constructor
MyFrame::MyFrame()
        :wxFrame(NULL, wxID_ANY, wxT("Title"), wxDefaultPosition, wxSize(460, 300))
{
    //Center window
    CentreOnScreen();

    //Set the background color
    SetBackgroundColour(wxColour(0xF4F4F4));
    
}

//The left mouse button press event processing
void MyFrame::OnLeftDown(wxMouseEvent& event)
{
   draw(this);
}



//Application class
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

//Automatically instantiate the MyApp object and assign it to the global variable wxTheApp
DECLARE_APP(MyApp)
//Declare that you can use wxGetApp() to get the instance object
IMPLEMENT_APP(MyApp)

//Application entrance
bool MyApp::OnInit()
{
    //Instantiate a main window
    MyFrame *frame = new MyFrame();

    //Display the main window
    frame->Show(true);

    //Start the event loop
    return true;
}
