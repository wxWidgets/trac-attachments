#include <wx/wx.h>

class cApp: public wxApp
{
public:
    virtual bool OnInit();
private:
    static const wxSize BMPSIZE;
    static const int BORDER;

    wxFrame * frame;
    wxPanel * panel;
    wxBitmap * bmp;
    wxMemoryDC * bmpdc;

    void OnResize(wxSizeEvent &event);
    void OnPaint(wxPaintEvent &event);
};

wxIMPLEMENT_APP(cApp);

// cApp

const wxSize cApp::BMPSIZE = wxSize(50, 50);
const int cApp::BORDER = 30;

bool cApp::OnInit()
{
    bmp = new wxBitmap;
    bmpdc = new wxMemoryDC;

    frame = new wxFrame(NULL, wxID_ANY, L"StretchBlit bug");
    frame->Bind(wxEVT_SIZE, &cApp::OnResize, this);

    panel = new wxPanel(frame);
    panel->Bind(wxEVT_PAINT, &cApp::OnPaint, this);

    wxImage img(BMPSIZE, true); // black image
    *bmp = wxBitmap(img);
    bmpdc->SelectObject(*bmp);

    frame->Show();
    return true;
}

void cApp::OnResize(wxSizeEvent &event)
{
    event.Skip();
    panel->Refresh();
}

void cApp::OnPaint(wxPaintEvent &event)
{
    event.Skip();
    wxSize sz = panel->GetClientSize();
    wxPaintDC dc(panel);
    wxPen pen = dc.GetPen();
    dc.Clear();

    pen.SetColour(*wxGREEN);
    dc.SetPen(pen);
    dc.DrawRectangle(wxPoint(BORDER, BORDER), sz - wxSize(2 * BORDER, 2 * BORDER));

    pen.SetColour(*wxRED);
    dc.SetPen(pen);
    dc.DrawRectangle(wxPoint(BORDER + 1, BORDER + 1), sz - wxSize(2 * BORDER + 2, 2 * BORDER + 2));

    dc.StretchBlit(wxPoint(BORDER + 2, BORDER + 2), sz - wxSize(2 * BORDER + 4, 2 * BORDER + 4),
                   bmpdc, wxPoint(0, 0), BMPSIZE);
}
