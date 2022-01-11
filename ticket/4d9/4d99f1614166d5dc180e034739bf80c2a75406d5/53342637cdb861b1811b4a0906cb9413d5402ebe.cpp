/*
 * Copyright (c) 2007 Hot Neuron LLC.  All Rights Reserved.
 *
 * $Id: clustify.cpp,v 1.15 2007/12/17 07:51:32 billd Exp $
 *
 * http://sourceforge.net/tracker/index.php?func=detail&aid=1868825&group_id=9863&atid=109863
 */

#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/mimetype.h>
#include <stdio.h>

class TestApp : public wxApp
	{
	virtual bool OnInit();
	};


void do_test(const char *fname, const char *mime_type)
	{
#ifdef WIN32
	wxFileType *ft = wxTheMimeTypesManager->GetFileTypeFromExtension(wxFileName(fname).GetExt());
#else
	wxFileType *ft = wxTheMimeTypesManager->GetFileTypeFromMimeType(mime_type);
#endif
	wxString cmd;
	cmd = ft->GetOpenCommand(fname);
	fprintf(stderr, "%s\n", cmd.c_str());
	}

class TestFrame : public wxFrame
	{
	public:
		TestFrame() : wxFrame(NULL, wxID_ANY, wxT("Test"), wxDefaultPosition, wxSize(400, 200))
			{
			do_test("file with spaces.txt", "text/plain");
			do_test("file with spaces.pdf", "application/pdf");
/*
			do_test("file with spaces.htm", "text/html");
			do_test("file with spaces.xls", "application/excel");
*/
			}
	};


bool TestApp::OnInit()
	{
	TestFrame *frame = new TestFrame;

	return false;  // exit
	} 

IMPLEMENT_APP(TestApp)

 	  	 
