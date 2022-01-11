
#include <wx/wx.h>
#include <wx/image.h>


class MyApp: public wxApp 
{
	virtual bool OnInit();
};

class MyFrame: public wxFrame {
public:

    MyFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

private:
    void do_layout();

protected:
    wxStaticBitmap* bmp;
    wxStaticText* lblLogin;
    wxTextCtrl* txtLogin;
    wxStaticText* lblPassword;
    wxTextCtrl* txtPassword;
    wxButton* btnOk;
    wxButton* btnCancel;
    wxPanel* panel;
}; 

	
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() 
{
    // we use a PNG image in our HTML page
    wxImage::AddHandler(new wxPNGHandler);
	
	MyFrame *frame = new MyFrame(NULL, wxID_ANY, _T("kipuamutay"), wxDefaultPosition ,wxSize(450,450));
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}


MyFrame::MyFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{

    panel = new wxPanel(this, wxID_ANY, pos, size);
    bmp = new wxStaticBitmap(panel, wxID_ANY, wxBitmap(wxT("./logo.png"), wxBITMAP_TYPE_ANY));
	bmp->Center();
	
    lblLogin = new wxStaticText(panel, wxID_ANY, wxT("&login"));
    txtLogin = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    lblPassword = new wxStaticText(panel, wxID_ANY, wxT("&password"));
    txtPassword = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
    btnOk = new wxButton(panel, wxID_ANY, wxT("Ok"));
    btnCancel = new wxButton(panel, wxID_ANY, wxT("Cancel"));

    do_layout();
}




void MyFrame::do_layout()
{
	panel->Center();

    wxBoxSizer* top_sizer_trick = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttons_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxGridSizer* buttons_grid_sizer = new wxGridSizer(1, 2, 0, 5);
    wxFlexGridSizer* input_fields_sizer = new wxFlexGridSizer(0, 2, 2, 5);
    top_sizer_trick->Add(10, 10, 0, 0, 0);
    main_sizer->Add(120, 1, 0, 0, 0);
    input_fields_sizer->Add(lblLogin, 0, 0, 0);
    input_fields_sizer->Add(txtLogin, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    input_fields_sizer->Add(lblPassword, 0, 0, 0);
    input_fields_sizer->Add(txtPassword, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);

    input_fields_sizer->AddGrowableCol(1);
	main_sizer->Add(input_fields_sizer, 0, wxALL|wxEXPAND, 0);
	main_sizer->Add(1, 20, 0, 0, 0);
    buttons_grid_sizer->Add(btnOk, 0, wxALL|wxEXPAND, 0);
    buttons_grid_sizer->Add(btnCancel, 0, wxALL|wxEXPAND, 0);
    buttons_sizer->Add(buttons_grid_sizer, 0, 0, 0);


	main_sizer->Add(buttons_sizer, 0, wxALIGN_CENTER_VERTICAL, 0);
	main_sizer->Add(1, 1, 0, 0, 0);

	top_sizer_trick->Add(main_sizer, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);

    top_sizer_trick->Add(1, 1, 0, 0, 0);
	top_sizer_trick->PrependSpacer(125);
    SetSizer(top_sizer_trick);

    Layout();

}

