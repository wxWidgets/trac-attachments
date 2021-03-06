// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/rawbmp.h>
#include <wx/treectrl.h>

#define myprintf wxMessageOutput::Get()->Printf

unsigned char pixels[2304] = {  
255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 167, 167, 167, 5, 221, 221, 221, 60, 234, 234,
  234, 134, 239, 239, 239, 172, 243, 243, 243, 185, 243,
  243, 243, 185, 241, 241, 241, 172, 235, 235, 235, 134,
  222, 222, 222, 60, 168, 168, 168, 5, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 0, 0, 0, 2, 206, 206, 206, 62, 238, 239,
  239, 197, 199, 237, 246, 238, 119, 227, 250, 246, 79,
  226, 252, 250, 73, 231, 251, 251, 80, 237, 250, 251,
  98, 245, 250, 250, 146, 248, 249, 246, 211, 248, 247,
  238, 240, 241, 241, 197, 207, 207, 207, 62, 0, 0,
  0, 2, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 0, 0, 0, 5, 222, 222,
  222, 120, 224, 238, 242, 236, 69, 202, 239, 250, 1,
  199, 249, 255, 5, 208, 254, 255, 14, 217, 253, 255,
  24, 226, 252, 255, 34, 235, 251, 255, 43, 244, 250,
  255, 69, 250, 250, 255, 117, 251, 251, 255, 182, 250,
  250, 250, 238, 245, 245, 236, 222, 222, 222, 120, 0,
  0, 0, 5, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 0, 0,
  0, 5, 217, 217, 217, 122, 221, 234, 238, 238, 14,
  173, 220, 254, 0, 180, 231, 255, 0, 194, 244, 255,
  3, 206, 254, 255, 13, 216, 253, 255, 24, 226, 252,
  255, 35, 236, 250, 255, 48, 246, 250, 255, 88, 250,
  250, 255, 139, 251, 251, 255, 183, 253, 253, 255, 225,
  254, 254, 254, 242, 243, 243, 238, 218, 218, 218, 122,
  0, 0, 0, 5, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 0, 0, 0, 2, 184, 184, 184, 68, 220,
  233, 237, 237, 14, 158, 204, 254, 0, 159, 209, 255,
  0, 172, 222, 255, 0, 186, 237, 255, 1, 202, 251,
  255, 11, 214, 253, 255, 24, 226, 252, 255, 36, 239,
  250, 255, 58, 248, 250, 255, 114, 251, 251, 255, 169,
  252, 252, 255, 218, 254, 254, 255, 241, 254, 254, 255,
  224, 253, 253, 254, 234, 242, 242, 237, 185, 185, 185,
  68, 0, 0, 0, 2, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 58,
  58, 58, 16, 227, 228, 228, 201, 68, 187, 223, 251,
  0, 159, 209, 255, 0, 152, 202, 255, 0, 161, 211,
  255, 0, 177, 228, 255, 0, 196, 246, 255, 8, 212,
  253, 255, 24, 226, 252, 255, 38, 241, 250, 255, 79,
  250, 250, 255, 148, 252, 251, 255, 210, 253, 253, 255,
  241, 254, 254, 255, 216, 254, 254, 255, 181, 253, 253,
  255, 180, 248, 248, 251, 229, 230, 230, 201, 57, 57,
  57, 16, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 0, 0, 0, 2, 168, 168, 168, 76,
  192, 226, 236, 240, 1, 181, 230, 255, 0, 172, 222,
  255, 0, 160, 211, 255, 0, 154, 204, 255, 0, 165,
  215, 255, 0, 184, 235, 255, 4, 191, 237, 255, 16,
  202, 235, 255, 31, 214, 234, 255, 80, 220, 236, 255,
  182, 245, 249, 255, 238, 254, 254, 255, 208, 253, 253,
  255, 167, 252, 252, 255, 136, 251, 251, 255, 115, 251,
  251, 255, 208, 239, 238, 240, 169, 169, 169, 76, 0,
  0, 0, 2, 255, 0, 255, 0, 255, 0, 255, 0,
  0, 0, 0, 9, 203, 203, 203, 149, 110, 214, 241,
  248, 0, 193, 244, 255, 0, 186, 236, 255, 0, 177,
  227, 255, 0, 164, 214, 255, 0, 155, 205, 255, 3,
  167, 217, 255, 150, 219, 237, 248, 197, 227, 233, 246,
  201, 228, 230, 246, 198, 232, 236, 248, 165, 225, 239,
  255, 179, 245, 249, 255, 145, 252, 251, 255, 112, 251,
  251, 255, 86, 250, 250, 255, 67, 250, 250, 255, 140,
  242, 243, 248, 203, 203, 203, 149, 0, 0, 0, 9,
  255, 0, 255, 0, 255, 0, 255, 0, 0, 0, 0,
  18, 212, 212, 212, 184, 65, 215, 248, 251, 0, 206,
  253, 255, 0, 201, 251, 255, 0, 195, 246, 255, 0,
  186, 237, 255, 0, 165, 215, 255, 151, 206, 223, 247,
  214, 214, 214, 225, 56, 56, 56, 113, 54, 54, 54,
  113, 208, 208, 208, 225, 199, 232, 235, 247, 78, 220,
  236, 255, 77, 250, 250, 255, 57, 248, 250, 255, 47,
  246, 250, 255, 43, 244, 250, 255, 95, 239, 245, 251,
  213, 213, 213, 184, 0, 0, 0, 18, 255, 0, 255,
  0, 255, 0, 255, 0, 0, 0, 0, 25, 214, 214,
  214, 197, 51, 222, 249, 252, 0, 217, 254, 255, 0,
  215, 254, 255, 0, 213, 254, 255, 0, 208, 253, 255,
  0, 184, 233, 255, 200, 230, 236, 244, 65, 65, 65,
  99, 0, 0, 0, 54, 0, 0, 0, 54, 63, 63,
  63, 99, 199, 228, 230, 244, 30, 213, 234, 255, 38,
  241, 250, 255, 36, 238, 250, 255, 35, 236, 251, 255,
  33, 235, 251, 255, 77, 234, 247, 252, 214, 214, 214,
  197, 0, 0, 0, 25, 255, 0, 255, 0, 255, 0,
  255, 0, 0, 0, 0, 28, 213, 213, 213, 198, 51,
  229, 249, 252, 0, 229, 254, 255, 0, 229, 254, 255,
  0, 229, 254, 255, 0, 229, 254, 255, 0, 203, 237,
  255, 204, 233, 236, 243, 88, 88, 88, 76, 0, 0,
  0, 16, 0, 0, 0, 16, 88, 88, 88, 76, 198,
  229, 234, 243, 14, 201, 235, 255, 24, 226, 252, 255,
  24, 226, 252, 255, 24, 226, 252, 255, 24, 226, 252,
  255, 70, 227, 247, 252, 213, 213, 213, 198, 0, 0,
  0, 28, 255, 0, 255, 0, 255, 0, 255, 0, 0,
  0, 0, 28, 206, 206, 206, 188, 64, 235, 247, 251,
  0, 240, 254, 255, 0, 242, 254, 255, 0, 245, 254,
  255, 1, 248, 254, 255, 12, 220, 238, 255, 151, 235,
  237, 246, 230, 230, 230, 214, 162, 162, 162, 42, 163,
  163, 163, 42, 231, 231, 231, 214, 152, 219, 236, 246,
  3, 190, 237, 255, 8, 212, 254, 255, 10, 214, 253,
  255, 13, 216, 253, 255, 14, 217, 253, 255, 75, 221,
  246, 251, 206, 206, 206, 188, 0, 0, 0, 28, 255,
  0, 255, 0, 255, 0, 255, 0, 0, 0, 0, 25,
  186, 186, 186, 159, 108, 239, 242, 249, 1, 251, 254,
  255, 10, 253, 254, 255, 34, 254, 254, 255, 75, 254,
  254, 255, 135, 246, 250, 255, 148, 225, 239, 255, 182,
  234, 237, 245, 207, 235, 236, 240, 202, 232, 237, 240,
  148, 205, 223, 245, 3, 166, 216, 255, 0, 183, 235,
  255, 0, 195, 246, 255, 1, 202, 251, 255, 2, 206,
  253, 255, 5, 208, 254, 255, 112, 218, 242, 249, 187,
  187, 187, 159, 0, 0, 0, 25, 255, 0, 255, 0,
  255, 0, 255, 0, 0, 0, 0, 18, 126, 126, 126,
  99, 189, 231, 231, 243, 45, 254, 254, 255, 76, 254,
  254, 255, 119, 254, 254, 255, 179, 254, 254, 255, 227,
  254, 254, 255, 142, 246, 250, 255, 20, 221, 238, 255,
  0, 205, 237, 255, 0, 186, 234, 255, 0, 165, 216,
  255, 0, 155, 205, 255, 0, 164, 214, 255, 0, 177,
  227, 255, 0, 186, 236, 255, 0, 193, 244, 255, 1,
  198, 248, 255, 185, 222, 231, 243, 126, 126, 126, 99,
  0, 0, 0, 18, 255, 0, 255, 0, 255, 0, 255,
  0, 0, 0, 0, 9, 0, 0, 0, 46, 210, 211,
  211, 212, 143, 246, 246, 252, 145, 254, 254, 255, 196,
  254, 254, 255, 234, 254, 254, 255, 183, 254, 254, 255,
  78, 254, 254, 255, 3, 249, 254, 255, 0, 230, 254,
  255, 0, 209, 253, 255, 0, 186, 238, 255, 0, 165,
  215, 255, 0, 154, 204, 255, 0, 160, 211, 255, 0,
  172, 222, 255, 0, 180, 230, 255, 65, 197, 233, 252,
  209, 210, 210, 212, 19, 19, 19, 49, 0, 0, 0,
  9, 255, 0, 255, 0, 255, 0, 255, 0, 0, 0,
  0, 2, 0, 0, 0, 28, 113, 113, 113, 107, 220,
  227, 227, 242, 206, 253, 253, 255, 238, 254, 254, 255,
  198, 254, 254, 255, 122, 254, 254, 255, 36, 254, 254,
  255, 0, 245, 254, 255, 0, 229, 254, 255, 0, 213,
  254, 255, 0, 196, 246, 255, 0, 177, 228, 255, 0,
  161, 211, 255, 0, 152, 202, 255, 0, 159, 209, 255,
  14, 171, 219, 255, 208, 221, 225, 242, 114, 114, 114,
  107, 0, 0, 0, 29, 0, 0, 0, 2, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 0,
  0, 0, 12, 0, 0, 0, 45, 161, 161, 161, 158,
  225, 226, 226, 243, 208, 253, 253, 255, 147, 254, 254,
  255, 79, 254, 254, 255, 12, 253, 254, 255, 0, 243,
  254, 255, 0, 229, 254, 255, 0, 215, 254, 255, 0,
  202, 251, 255, 0, 186, 237, 255, 0, 172, 222, 255,
  0, 159, 209, 255, 14, 158, 204, 255, 206, 218, 222,
  243, 161, 161, 161, 158, 0, 0, 0, 45, 0, 0,
  0, 13, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 0, 0, 0, 2,
  0, 0, 0, 21, 0, 0, 0, 54, 156, 156, 156,
  161, 218, 225, 225, 242, 143, 245, 245, 252, 48, 254,
  254, 255, 2, 251, 254, 255, 0, 240, 254, 255, 0,
  229, 254, 255, 0, 218, 254, 255, 0, 206, 254, 255,
  0, 194, 244, 255, 1, 181, 231, 255, 65, 184, 220,
  252, 205, 217, 221, 242, 156, 156, 156, 161, 0, 0,
  0, 54, 0, 0, 0, 21, 0, 0, 0, 2, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 0, 0, 0,
  5, 0, 0, 0, 24, 0, 0, 0, 54, 100, 100,
  100, 120, 202, 203, 203, 218, 186, 227, 227, 245, 106,
  237, 239, 250, 63, 235, 245, 252, 50, 228, 247, 253,
  50, 220, 247, 253, 63, 213, 245, 252, 106, 210, 237,
  250, 181, 215, 224, 245, 201, 202, 202, 218, 100, 100,
  100, 120, 0, 0, 0, 54, 0, 0, 0, 24, 0,
  0, 0, 5, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 0, 0,
  0, 5, 0, 0, 0, 21, 0, 0, 0, 45, 0,
  0, 0, 69, 100, 100, 100, 123, 164, 164, 164, 177,
  187, 187, 187, 202, 194, 194, 194, 211, 194, 194, 194,
  211, 187, 187, 187, 202, 164, 164, 164, 177, 100, 100,
  100, 123, 0, 0, 0, 69, 0, 0, 0, 45, 0,
  0, 0, 21, 0, 0, 0, 5, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 0,
  0, 0, 2, 0, 0, 0, 12, 0, 0, 0, 28,
  0, 0, 0, 46, 0, 0, 0, 58, 0, 0, 0,
  66, 0, 0, 0, 69, 0, 0, 0, 69, 0, 0,
  0, 66, 0, 0, 0, 58, 0, 0, 0, 46, 0,
  0, 0, 28, 0, 0, 0, 12, 0, 0, 0, 2,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 0, 0, 0, 2, 0, 0, 0,
  9, 0, 0, 0, 18, 0, 0, 0, 25, 0, 0,
  0, 28, 0, 0, 0, 28, 0, 0, 0, 25, 0,
  0, 0, 18, 0, 0, 0, 9, 0, 0, 0, 2,
  255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
  255, 0, 255, 0, 255, 0, };

#define dopremultiply(p, a) ((p) * (a) / 0xff) 

static wxBitmap *raw2bm(unsigned int *rgb, int width, int height)
{
	unsigned char *src;
	int r, g, b, a;
	wxBitmap *bm;
		
	bm = new wxBitmap(width, height, 32);
	if(!bm->IsOk()) return NULL;
	
	src = (unsigned char *) rgb;
	r = 2;
	g = 1;
	b = 0;
	a = 3;
		
	wxAlphaPixelData pixData(*bm, wxPoint(0, 0), wxSize(width, height));     
	
        wxAlphaPixelData::Iterator p(pixData);
	                
      	for(int y = 0; y < height; y++) {
                	                	
		wxAlphaPixelData::Iterator rowStart = p;
                    	                   		
               	for(int x = 0; x < width; x++) {
                  
			unsigned char av = src[a]; 
											
			p.Red()   = dopremultiply(src[r], av);
			p.Green() = dopremultiply(src[g], av);
			p.Blue()  = dopremultiply(src[b], av);					
			p.Alpha() = src[a];
      	        	src += 4;    
			
               	       	p++;             	        	
               	}
                    
        	p = rowStart;
       	        p.OffsetY(pixData, 1); 	        	   	
       	}   				
       			
	return bm;
}	

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

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World");
    frame->Show( true );
    return true;
}

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title)
{	
    wxPanel *panel = new wxPanel(this, -1);
    int image = -1;
    wxBitmap *bm = raw2bm((unsigned int *) pixels, 24, 24);
        
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxTreeCtrl *tc = new wxTreeCtrl(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT);

    wxImageList *il = new wxImageList(24, 24);		
    tc->AssignImageList(il);
    image = il->Add(*bm);

    wxTreeItemId id = tc->AddRoot("Root");   
    
#if 1
    // causes refresh glitches when moving the mouse cursor over the items   
    tc->SetItemHasChildren(tc->AppendItem(id, wxT("CPU"), image, image));
    tc->SetItemHasChildren(tc->AppendItem(id, wxT("Machine"), image, image));
    tc->SetItemHasChildren(tc->AppendItem(id, wxT("Expansion buses"), image, image));
    tc->SetItemHasChildren(tc->AppendItem(id, wxT("Libraries"), image, image));
    tc->SetItemHasChildren(tc->AppendItem(id, wxT("Devices"), image, image));
    tc->SetItemHasChildren(tc->AppendItem(id, wxT("Tasks"), image, image));
#else
    // working fine
    tc->AppendItem(id, wxT("CPU"), image, image);
    tc->AppendItem(id, wxT("Machine"), image, image);
    tc->AppendItem(id, wxT("Expansion buses"), image, image);
    tc->AppendItem(id, wxT("Libraries"), image, image);
    tc->AppendItem(id, wxT("Devices"), image, image);
    tc->AppendItem(id, wxT("Tasks"), image, image);
#endif
                           
    vbox->Add(tc, 1, wxEXPAND);

    panel->SetSizerAndFit(vbox);    
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
