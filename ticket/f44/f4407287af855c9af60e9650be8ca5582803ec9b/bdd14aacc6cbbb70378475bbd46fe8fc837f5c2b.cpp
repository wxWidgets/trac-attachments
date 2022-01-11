#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/graphics.h>

#define DIM 100
#define POS 20

struct TestPanel: public wxPanel {
    TestPanel(wxWindow* parent)
        : wxPanel(parent)
        , bmp1(MakeBitmap(0, 0, 128, 128))
        , bmp2(MakeBitmap(0, 0, 0, 0))
        , bmp3(MakeBitmap(0, 0, 255, 255))
    {
        Connect(wxEVT_PAINT, wxPaintEventHandler(TestPanel::paint));
    }
    wxBitmap MakeBitmap(int r, int g, int b, int a)
    {
        wxImage image(DIM, DIM);
        image.InitAlpha();
        memset(image.GetAlpha(), wxByte(a), DIM*DIM);
        wxByte* p = image.GetData();
        for (int i = 0; i < DIM*DIM; i++) {
            *p++ = wxByte(r);
            *p++ = wxByte(g);
            *p++ = wxByte(b);
        }
        wxBitmap bmp(image);
        wxMemoryDC mdc(bmp);
        wxGraphicsContext* gc = wxGraphicsContext::Create(mdc);
        wxGraphicsPath path = gc->CreatePath();
        path.MoveToPoint(POS, POS);
        path.AddLineToPoint(DIM-POS, DIM-POS);
        gc->SetPen(wxPen(*wxRED, 8));
        gc->StrokePath(path);
        delete gc;
        return bmp;
    }
    void paint(wxPaintEvent&)
    {
        wxPaintDC dc(this);
        wxSize sz = GetSize();
        dc.SetPen(wxPen("navy"));
        int x = 0, y = 0;
        while (x < sz.x * 2 || y < sz.y * 2) {
            x += 20;
            y += 20;
            dc.DrawLine(x, 0, 0, y);
        }
        x = y = 25;
        dc.DrawBitmap(bmp1, x, y, true);
        x += DIM + 25;
        dc.DrawBitmap(bmp2, x, y, true);
        x += DIM + 25;
        dc.DrawBitmap(bmp3, x, y, true);
    }
    wxBitmap bmp1;
    wxBitmap bmp2;
    wxBitmap bmp3;
};
struct App: public wxApp {
    bool OnInit()
    {
        wxFrame* frame = new wxFrame(NULL, -1, "bitmap test");
        new TestPanel(frame);
        frame->Show(true);
        return true;
    }
};
IMPLEMENT_APP(App)
