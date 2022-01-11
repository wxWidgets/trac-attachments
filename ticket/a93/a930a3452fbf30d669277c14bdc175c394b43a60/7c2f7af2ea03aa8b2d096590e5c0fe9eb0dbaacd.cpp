// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/listbook.h>
#include <wx/rawbmp.h>
	
class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title);
private:
    void OnExit(wxCommandEvent& event);
    DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)  	
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp);

static wxListbook *lb;
static int count = 1;

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World");
    frame->Show( true );
    return true;
}

inline wxString str2wx(const char *str)
{
    if(!str) return wxEmptyString; 

    return wxString(str, wxConvISO8859_1);
}

static wxWindow *makepage(wxWindow *parent, const char *title)
{
	wxWindow *panel = new wxPanel(parent, -1);
	wxSizer *s = new wxBoxSizer(wxVERTICAL);
	wxButton *b = new wxButton(panel, -1, str2wx(title));
	
	s->Add(b, 1, wxEXPAND);
	
	panel->SetSizer(s);
	
	return panel;
}

static void evtcallback(wxCommandEvent &event) 
{ 	
    char tmp[32];
    sprintf(tmp, "Page %d", ++count);
    	
    lb->InsertPage(0, makepage(lb, tmp), str2wx(tmp), false, 0); 
}

static void rectfill2wxbmap(int x, int y, int width, int height, int color, wxBitmap *dstbm)
{		
	int r = (color & 0xff0000) >> 16;
	int g = (color & 0xff00) >> 8;
	int b = (color & 0xff);
	
	wxAlphaPixelData pixData(*dstbm, wxPoint(x, y), wxSize(width, height));     
	if(!pixData) return;
		
        wxAlphaPixelData::Iterator p(pixData);
	                
       	for(int y = 0; y < height; y++) {
                	                	
               	wxAlphaPixelData::Iterator rowStart = p;
                    	                   		
       	    	for(int x = 0; x < width; x++) {
			p.Red()   = r;
			p.Green() = g;
			p.Blue()  = b;	
			p.Alpha() = 255;
        		p++;
      		}
                    
		p = rowStart;
        	p.OffsetY(pixData, 1);
       	}				
}

		
MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxWindow *panel = new wxPanel(this, -1);
    wxSizer *vbox;
    
    lb = new wxListbook(panel, -1); 
    
    wxImageList *il = new wxImageList(32, 32);		
    lb->AssignImageList(il);

    wxBitmap *bm = new wxBitmap();
    bm->CreateScaled(24, 24, 32, 2);
    rectfill2wxbmap(0, 0, 48, 48, 0xff0000, bm);
    il->Add(*bm);    
    
    lb->AddPage(makepage(lb, "Page 1"), wxT("Page 1"), false, 0);
    
    wxButton *b = new wxButton(panel, -1, wxT("Add page to top"));
                 
    vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(lb, 1, wxEXPAND);
    vbox->Add(b, 0, wxEXPAND);

    b->Bind(wxEVT_BUTTON, evtcallback, wxID_ANY, wxID_ANY);  
      
    panel->SetSizer(vbox);    
    SetClientSize(panel->GetBestSize());			
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
