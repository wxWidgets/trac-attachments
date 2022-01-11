/*!
	\file
	\brief	copy_wx_app

				Test program for clipboard

	\author	Benjamin Silvestre
	\date		2013-06-19
*/

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/clipbrd.h>

//-------------------------------------------------------------------------------
// copy_wx_frame class
//-------------------------------------------------------------------------------

class copy_wx_frame : public wxFrame
{
//-------------------------------------------------------------------------------
// Construction/Destruction
	
	public: copy_wx_frame() : wxFrame(NULL, wxID_ANY, wxT("Test copy"))
		{
			wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
			sizer->Add(new wxButton(this, wxID_HIGHEST+1, wxT("wxTextDataObject")), 0, wxEXPAND|wxALL, 10);
			sizer->Add(new wxButton(this, wxID_HIGHEST+2, wxT("wxHTMLDataObject")), 0, wxEXPAND|wxALL, 10);
			sizer->Add(new wxButton(this, wxID_HIGHEST+3, wxT("wxDataObjectComposite")), 0, wxEXPAND|wxALL, 10);
			SetSizer(sizer);
			sizer->Fit(this);

			Connect(wxID_HIGHEST+1, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(copy_wx_frame::on_text));
			Connect(wxID_HIGHEST+2, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(copy_wx_frame::on_html));
			Connect(wxID_HIGHEST+3, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(copy_wx_frame::on_composite));
		};

//-------------------------------------------------------------------------------
// Functions

	private: void send_to_clipboard(wxDataObject* data)
		{
			if (wxTheClipboard->Open())
			{
				wxTheClipboard->Clear();
				wxTheClipboard->SetData(data);
				wxTheClipboard->Close();
			}
			else
				delete data;
		};
		
//-------------------------------------------------------------------------------
// Events

	private: void on_text(wxCommandEvent&)
		{
			send_to_clipboard(new wxTextDataObject(wxT("Hello World!\r\nThis is text data")));
		};
		
	private: void on_html(wxCommandEvent&)
		{
#if wxCHECK_VERSION(2, 9, 0)
			send_to_clipboard(new wxHTMLDataObject(wxT("<h1>Hello World!</h1><p>This is HTML data</p>")));
#endif // wxCHECK_VERSION(2, 9, 0)
		};

	private: void on_composite(wxCommandEvent&)
		{
			wxDataObjectComposite* tmp_data = new wxDataObjectComposite();
			tmp_data->Add(new wxTextDataObject(wxT("Hello World!\r\nThis is text data")), true);
#if wxCHECK_VERSION(2, 9, 0)			
			tmp_data->Add(new wxHTMLDataObject(wxT("<h1>Hello World!</h1><p>This is HTML data</p>")), false);
#endif // wxCHECK_VERSION(2, 9, 0)		
			send_to_clipboard(tmp_data);

		};			
};


//-------------------------------------------------------------------------------
// copy_wx_app class
//-------------------------------------------------------------------------------

class copy_wx_app : public wxApp
{
//-------------------------------------------------------------------------------
// Function

	public: virtual bool OnInit()
		{
			copy_wx_frame* frame = new copy_wx_frame();
			frame->Show(true);
			frame->Centre();
			SetTopWindow(frame);
			return true;
		};
};

IMPLEMENT_APP(copy_wx_app)
