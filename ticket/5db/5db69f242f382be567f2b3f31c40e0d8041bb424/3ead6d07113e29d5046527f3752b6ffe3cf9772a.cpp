#include "wx/wxprec.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <math.h>

// ----------------------------------------------------------------------------

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
protected:
    void OnPaint(wxPaintEvent& event);
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// ----------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame(_T("Minimal wxWindows App"));
    frame->Show(true);
    return true;
}

// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_PAINT(MyFrame::OnPaint)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
}

void ShowText(wxDC& dc, wxCoord x, wxCoord y, double angle)
{
    dc.DrawLine(x-4, y  , x+4, y  );
    dc.DrawLine(x  , y-4, x  , y+4);

    dc.ResetBoundingBox();
    if (angle == 0.0)
        dc.DrawText(wxT("XXXXXX"), x, y);
    else
        dc.DrawRotatedText(wxT("XXXXXX"), x, y, angle);
    dc.DrawLine(dc.MinX(), dc.MinY(), dc.MinX(), dc.MaxY());
    dc.DrawLine(dc.MaxX(), dc.MinY(), dc.MaxX(), dc.MaxY());
    dc.DrawLine(dc.MinX(), dc.MinY(), dc.MaxX(), dc.MinY());
    dc.DrawLine(dc.MinX(), dc.MaxY(), dc.MaxX(), dc.MaxY());
}

static inline double DegToRad(double deg) { return (deg * M_PI) / 180.0; }

void MyFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
    
    dc.SetFont(wxFont(10, wxROMAN, wxNORMAL, wxNORMAL, FALSE, wxT("Arial")));

    ShowText(dc, 20, 10, 0.0);
    ShowText(dc, 20, 50, 0.001);
    ShowText(dc, 20, 90, 1.0);

    ShowText(dc, 200, 10, -70.0);

    wxCoord x, y;
    double angle;
    x = 200;
    y = 70;
    angle = -70.0;
    dc.DrawRotatedText(wxT("XXXXXX"), x, y, angle);
    dc.DrawLine(x-4, y  , x+4, y  );
    dc.DrawLine(x  , y-4, x  , y+4);
    dc.ResetBoundingBox();
    

        // call the bounding box by adding all four vertices of the rectangle
        // containing the text to it (simpler and probably not slower than
        // determining which of them is really topmost/leftmost/...)
        wxCoord w, h;
        dc.GetTextExtent("XXXXXX", &w, &h);

        double rad = DegToRad(angle);

        // "upper left" and "upper right"
        dc.CalcBoundingBox(x, y);
        dc.CalcBoundingBox(x + wxCoord(w*cos(rad)), y - wxCoord(w*sin(rad)));

        // "bottom left" and "bottom right"
        x += (wxCoord)(h*sin(rad));
        y += (wxCoord)(h*cos(rad));
        dc.CalcBoundingBox(x, y);
        dc.CalcBoundingBox(x + wxCoord(w*cos(rad)), y - wxCoord(w*sin(rad)));

    dc.DrawLine(dc.MinX(), dc.MinY(), dc.MinX(), dc.MaxY());
    dc.DrawLine(dc.MaxX(), dc.MinY(), dc.MaxX(), dc.MaxY());
    dc.DrawLine(dc.MinX(), dc.MinY(), dc.MaxX(), dc.MinY());
    dc.DrawLine(dc.MinX(), dc.MaxY(), dc.MaxX(), dc.MaxY());
}


 	  	 
