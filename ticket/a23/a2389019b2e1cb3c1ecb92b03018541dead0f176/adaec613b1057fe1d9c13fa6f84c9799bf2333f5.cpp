
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/html/htmlwin.h>

class MyApp: public wxApp
{
	virtual bool OnInit();
};

class MyFrame: public wxFrame {
public:
    MyFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

private:
    void do_layout();
    void OnHtmlLinkClicked(wxHtmlLinkEvent& event);

protected:
    wxHtmlWindow* htmlW;
    wxButton* btnOk;

};


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxImage::AddHandler(new wxPNGHandler);
	
	MyFrame *frame = new MyFrame(NULL, wxID_ANY, _T("kipuamutay"), wxDefaultPosition, wxSize(450, 450));
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}

MyFrame::MyFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, style)
{
	wxString myText;
	
	myText.Printf(wxT("<html><body bgcolor=\"%s\"><center><table align=\"center\" width=\"380\" border=\"2\" cellspacing=\"0\"><tr><td align=\"center\"><img src=\"%s\"></td></tr><tr><td bgcolor=\"#000000\" align=\"center\"><font color=\"#ffffff\">Version %s </font></td></tr></table></center><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\"><tr><td width=\"50\"></td><td><p>Home page:<a href=\"http://www.kipuamutay.com\">www.kipuamutay.com</a></td></tr></table></body></html>"), wxVERSION_STRING, _T("./logo_test.png"), wxVERSION_STRING);

	//does not scale fine for showing all the page content
	htmlW = new wxHtmlWindow(this, wxID_ANY, wxDefaultPosition, wxSize(380, 160), wxHW_SCROLLBAR_NEVER);
	htmlW->SetBorders(0);
	htmlW->SetPage(myText);
	htmlW->SetSize(htmlW->GetInternalRepresentation() -> GetWidth(),
                    htmlW -> GetInternalRepresentation() -> GetHeight());
    btnOk = new wxButton(this, wxID_ANY, wxT("Ok"));

    do_layout();
}

void MyFrame::do_layout()
{
    wxBoxSizer* top_sizer_trick = new wxBoxSizer(wxVERTICAL);
    top_sizer_trick->Add(htmlW, 1, wxALL, 10);
    top_sizer_trick->Add(btnOk, 0, wxALL, 10);
    SetSizer(top_sizer_trick);
    top_sizer_trick->Fit(this);

}

