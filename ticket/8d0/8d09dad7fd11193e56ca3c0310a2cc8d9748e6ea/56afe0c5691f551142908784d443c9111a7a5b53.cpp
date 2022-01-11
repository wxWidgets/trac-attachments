#include "bug.h"

IMPLEMENT_APP(App);


bool App::OnInit()
{
	frame = new wxFrame(NULL, wxID_ANY,_T("wxTextValidator Bug demo"));
	wxPanel *panel = new wxPanel(frame); 
	
	wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL); 
	
	wxButton *button=new wxButton(panel, -1, _T("Ok"));
	
	wxStaticText *text=new wxStaticText(panel,-1, _T("Try to click on the ok button without filling\nthe TextCtrl above, and you'll see the bug"));
	
	//--- the important line :
	textctrl=new wxTextCtrl(panel,-1,_T(""),wxDefaultPosition,wxDefaultSize,0,wxTextValidator(wxFILTER_EMPTY));
	//creating a TextCtrl with a validator. Only flag in the validator : wxFILTER_EMPTY
	 
	main_sizer->Add(textctrl,0);
	main_sizer->Add(text,0);
	main_sizer->Add(button,0);
	
	panel->SetSizer(main_sizer);
	
	button->Bind(wxEVT_BUTTON, &App::onClick, this);
	
    frame->Show();
	frame->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);

	
	return true;
}

void App::onClick(wxCommandEvent &event)
{
	if(frame->Validate())//<-- the unwanted pop-up is comming from this function
	{
		wxMessageBox(_T("Ok !"));
	}
	else 
	{
		wxMessageBox(_T("Not ok !\n(and the previous pop-up is unwanted)"));
	}
}