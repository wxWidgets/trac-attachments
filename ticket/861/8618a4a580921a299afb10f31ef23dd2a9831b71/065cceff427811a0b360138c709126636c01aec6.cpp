#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/app.h"
#include "wx/frame.h"
#include "wx/dataview.h"

class BasicFrame : public wxFrame
{
public:
	BasicFrame(wxString const& title);
};

BasicFrame::BasicFrame(wxString const& title)
	: wxFrame(nullptr, wxID_ANY, title)
{
	wxDataViewCtrl *ctrl = new wxDataViewCtrl(this, wxID_ANY);
	ctrl->AppendTextColumn(_("Name"), 0);
//	ctrl->AppendTextColumn(_("Size"), 1);	// Uncommenting this line removes the crash
}

/**********************************
The rest of this is boring.
**********************************/

class BasicApp : public wxApp
{
public:
	virtual bool OnInit();
};

bool BasicApp::OnInit()
{
	BasicFrame *frame = new BasicFrame(_("DataViewCtrl Crash Test"));
	frame->Show();
	return true;
}

IMPLEMENT_APP(BasicApp)
