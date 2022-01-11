#include <wx/wx.h>

// compile with g++ testwx.cc `wx-config --libs` `wx-config --cxxflags` -o testwx



class test_rectangle : public wxApp {
    virtual bool OnInit();

};

class test_frame : public wxFrame {
public:
    test_frame();
    void OnPaint(wxPaintEvent &e);
private:
    DECLARE_EVENT_TABLE()

};

IMPLEMENT_APP(test_rectangle);

BEGIN_EVENT_TABLE(test_frame, wxFrame)
    EVT_PAINT  (test_frame::OnPaint)
END_EVENT_TABLE()

bool test_rectangle::OnInit()
{
    test_frame *f = new test_frame();
    f->Show(TRUE);
    SetTopWindow(f);
    return true;

}

test_frame::test_frame() :
wxFrame(NULL,-1,wxT("test_frame"),wxPoint(-1,-1),wxSize(100,100))
{
}

void
test_frame::OnPaint(wxPaintEvent &e)
{
  wxPaintDC dc(this);
  wxSize size=GetClientSize();
  dc.SetAxisOrientation(true,true);
  dc.SetDeviceOrigin(0,size.y-1);
  dc.SetPen(wxPen(wxColour(255,0,0)));
  dc.DrawRectangle(0,0,size.x,size.y);
  dc.SetPen(wxPen(wxColour(0,255,0)));
  dc.DrawLine(0,0,0,size.y);
  dc.DrawLine(size.x-1,0,size.x-1,size.y);
  dc.DrawLine(0,0,size.x,0);
  dc.DrawLine(0,size.y-1,size.x,size.y-1);
  dc.SetPen(wxPen(wxColour(0,0,255)));
  dc.DrawLine(static_cast<int>(size.x*0.2),static_cast<int>(size.y*0.2),static_cast<int>(size.x*0.8),static_cast<int>(size.y*0.2));
  dc.DrawLine(static_cast<int>(size.x*0.2),static_cast<int>(size.y*0.2),static_cast<int>(size.x*0.5),static_cast<int>(size.y*0.8));
  dc.DrawLine(static_cast<int>(size.x*0.5),static_cast<int>(size.y*0.8),static_cast<int>(size.x*0.8),static_cast<int>(size.y*0.2));

}
 	  	 
