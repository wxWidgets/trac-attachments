#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif




#include <wx/app.h>
#include <wx/bitmap.h>
#include <wx/timer.h>
#include <wx/dynlib.h>
#include <wx/fileconf.h>
#include <string>
#include <map>


static const int BITMAP_SIZE_X = 50;
static const int BITMAP_SIZE_Y = 15;
enum
{
    StatusBar_Checkbox = 1000,
};

// A custom status bar which contains controls, icons &c
class BarreInfo : public wxStatusBar
{
    enum
    {
        Champ_Text,
		Champ_BitmapZoom,
        Champ_BitmapStat,
        Champ_Checkbox,
        Champ_BitmapVideo,
        Champ_Clock
    };
char	curseur;
    wxCheckBox *m_checkbox;
    wxBitmapButton *m_videoBmp;
    wxButton *m_statBmp;
    wxButton *m_zoomBmp;

public:
 BarreInfo(wxWindow *parent) : wxStatusBar(parent, wxID_ANY), m_checkbox(NULL)
{
static const int widths[6] = { -1,BITMAP_SIZE_X,BITMAP_SIZE_X, 80, BITMAP_SIZE_X,100 };

SetFieldsCount(6);
SetStatusWidths(6, widths);
curseur=1;
#if wxUSE_CHECKBOX
m_checkbox = new wxCheckBox(this, StatusBar_Checkbox, _T("&Cursor"));
m_checkbox->SetValue(true);
#endif

videoRouge = CreateBitmapForButton();
videoVert = CreateBitmapForButton(true);
m_videoBmp = new wxBitmapButton(this, 3789,videoVert ,
                               wxDefaultPosition, wxDefaultSize,
                               wxBU_EXACTFIT);
m_videoBmp->Show(false);

m_statBmp = new wxButton(this, 3790,"Stat",
                               wxDefaultPosition, wxDefaultSize,
                               wxBU_EXACTFIT);
m_statBmp->SetLabel("Stat");
m_zoomBmp = new wxButton(this, 3791,"Zoom",
                               wxDefaultPosition, wxDefaultSize,
                               wxBU_EXACTFIT);
m_zoomBmp->SetLabel("Zoom");



//SetMinHeight(BITMAP_SIZE_Y);

}

virtual ~BarreInfo(){};



void OnSize(wxSizeEvent& event)
{
#if wxUSE_CHECKBOX
    if ( !m_checkbox )
        return;
#endif

    wxRect rect;
    GetFieldRect(Champ_Checkbox, rect);

#if wxUSE_CHECKBOX
    m_checkbox->SetSize(rect.x + 2, rect.y + 2, rect.width - 4, rect.height - 4);
#endif

    GetFieldRect(Champ_BitmapVideo, rect);
    wxSize size = m_videoBmp->GetSize();

    m_videoBmp->Move(rect.x + (rect.width - size.x) / 2,
                    rect.y + (rect.height - size.y) / 2);
    GetFieldRect(Champ_BitmapStat, rect);
    size = m_statBmp->GetSize();

    m_statBmp->Move(rect.x + (rect.width - size.x) / 2,
                    rect.y + (rect.height - size.y) / 2);
    GetFieldRect(Champ_BitmapZoom, rect);
    size = m_zoomBmp->GetSize();

    m_zoomBmp->Move(rect.x + (rect.width - size.x) / 2,
                    rect.y + (rect.height - size.y) / 2);


    event.Skip();
}
private:
    // toggle the state of the status bar controls
    void DoToggle();
    wxBitmap	videoRouge,videoVert;

wxBitmap BarreInfo::CreateBitmapForButton(bool on=true)
{
    static const int BMP_BUTTON_SIZE_X = 10;
    static const int BMP_BUTTON_SIZE_Y = 9;

    wxBitmap bitmap(BMP_BUTTON_SIZE_X, BMP_BUTTON_SIZE_Y);
    wxMemoryDC dc;
    dc.SelectObject(bitmap);
    dc.SetBrush(on ? *wxGREEN_BRUSH : *wxRED_BRUSH);
    dc.SetBackground(*wxLIGHT_GREY_BRUSH);
    dc.Clear();
    dc.DrawEllipse(0, 0, BMP_BUTTON_SIZE_X, BMP_BUTTON_SIZE_Y);
    dc.SelectObject(wxNullBitmap);

    return bitmap;
}

    DECLARE_EVENT_TABLE()
};

class ZoneImage : public  wxScrolled<wxWindow>
{
wxBitmap			*bitmapAffiche;
wxImage				*img;

public :
ZoneImage::ZoneImage(wxWindow *parent,wxSize w)
    : wxScrolled<wxWindow>(parent, wxID_ANY)   {
    SetScrollRate( 1, 1 );
    SetBackgroundColour( *wxRED );
img = new wxImage("C:/Users/Public/Pictures/Sample Pictures/koala.jpg");
SetClientSize(img->GetWidth(), img->GetHeight());
SetVirtualSize( img->GetWidth(), img->GetHeight() );
bitmapAffiche=NULL;
Connect(wxEVT_PAINT, wxPaintEventHandler(ZoneImage::OnPaint));
};


void ZoneImage::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);

    // this call is vital: it adjusts the dc to account for the current
    // scroll offset
    PrepareDC(dc);
	if (bitmapAffiche==NULL)
		{
		wxRect		src(0,0,img->GetWidth()-1,img->GetHeight()-1);

		bitmapAffiche=new wxBitmap(*img);
		}
	dc.DrawBitmap(*bitmapAffiche,0,0);
	}
};

class FenetrePrincipale : public wxFrame
{
ZoneImage			*feuille;
BarreInfo			*barreEtat;
public :
FenetrePrincipale(wxFrame *frame, const wxString& title, const wxPoint& pos, 
    const wxSize& size, long style = wxDEFAULT_FRAME_STYLE): wxFrame(frame, wxID_ANY, title , pos, size, style)
{
((wxFrame*)this)->SetBackgroundColour(*wxBLACK);
// Association barre des menus avec la trame


SetClientSize(size.x, size.y);
feuille=NULL;
CreateStatusBar(2);
wxStatusBar *statbarOld = GetStatusBar();
statbarOld->Hide();
barreEtat = new BarreInfo(this);
if (barreEtat)
	SetStatusBar(barreEtat);

wxSize tailleUtile;
GetClientSize(&tailleUtile.x, &tailleUtile.y);
wxInitAllImageHandlers();
feuille = new ZoneImage(this,wxSize(100, 100));
feuille->Show();
GetStatusBar()->Show(false);
PositionStatusBar();

}

void OnSize( wxSizeEvent &w)
{
wxSize	taille=GetClientSize();
feuille->SetSize(taille);

}
    DECLARE_EVENT_TABLE()

};



/* Define a new application type */
class wxOsgApp : public wxApp
{

public :
wxOsgApp() {  };
bool wxOsgApp::OnInit()
{
wxFrame *w=new wxFrame(NULL,-1,"test");

w->Show(true);
FenetrePrincipale *f=new FenetrePrincipale(NULL, "wxOpenCV",
    wxPoint(100,100), wxSize(530,570),wxCLOSE_BOX|wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLIP_CHILDREN);
f->Show(true);
f->GetStatusBar()->Show(true);
return true;
}
};


BEGIN_EVENT_TABLE(BarreInfo, wxStatusBar)
    EVT_SIZE(BarreInfo::OnSize)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(FenetrePrincipale, wxFrame)
    EVT_SIZE(FenetrePrincipale::OnSize)
END_EVENT_TABLE()

IMPLEMENT_APP(wxOsgApp)

