#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif


#include "base.h"
#include <wx/file.h>

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
	
#if wxUSE_LIBPNG
    wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
    wxImage::AddHandler(new wxGIFHandler);
#endif
   HtmFrame *win = new HtmFrame(_("Frame"), wxPoint (100, 100),
     wxSize(450, 340));
   win->Show(TRUE);
   SetTopWindow(win);

   return TRUE;
}

void HtmFrame::CreateHtm()
{
	 //width=\"800\" height=\"130\"
    wxFile *tempFile = new wxFile();
    tempFile->Open("agroReport.html", wxFile::write);
    tempFile->Write("<HTML>\n<BODY>\n");
    tempFile->Write(_T("<center><img src=\"fejlec.jpg\" width=800 height=130></center>"));
    tempFile->Write("</BODY>\n</HTML>\n");
    tempFile->Close();

}

HtmFrame::HtmFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
	CreateHtm();
	
    m_pMenuBar = new wxMenuBar();
    // File Menu
    m_pFileMenu = new wxMenu();
/*
    m_pFileMenu->Append(MENU_FILE_OPEN, "&Open", "Opens an existing file");
    m_pFileMenu->Append(MENU_FILE_SAVE, "&Save", "Save the content");
    m_pFileMenu->AppendSeparator();
*/
    m_pFileMenu->Append(MENU_FILE_QUIT, "&Quit", "Quit the application");

    m_pPrintMenu = new wxMenu();
    m_pPrintMenu->Append(Minimal_PageSetup, _("Page Setup"));
    m_pPrintMenu->Append(Minimal_Print, _("Print..."));
    m_pPrintMenu->Append(Minimal_Preview, _("Preview..."));
    
    m_pMenuBar->Append(m_pFileMenu, "&File");
    m_pMenuBar->Append(m_pPrintMenu, "&Print");
    SetMenuBar(m_pMenuBar);
    CreateStatusBar(3);
    SetStatusText("Ready" , 0);
    
    m_Name = wxT("agroReport.html");

    m_Html = new wxHtmlWindow(this/*, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO*/);
    m_Html->SetRelatedFrame(this, _T("HTML: %s"));
    m_Html -> LoadPage(m_Name);

    m_Prn = new wxHtmlEasyPrinting(_("Easy Printing Demo"), NULL);
//    m_Prn -> SetHeader(m_Name + wxT("(@PAGENUM@/@PAGESCNT@)<hr>"), wxPAGE_ALL);
    

}

HtmFrame::~HtmFrame()
{
    delete m_Prn;
    m_Prn = (wxHtmlEasyPrinting *) NULL;
}

BEGIN_EVENT_TABLE(HtmFrame, wxFrame)
    EVT_MENU(MENU_FILE_OPEN, HtmFrame::OnMenuFileOpen)
    EVT_MENU(MENU_FILE_SAVE, HtmFrame::OnMenuFileSave)
    EVT_MENU(MENU_FILE_QUIT, HtmFrame::OnMenuFileQuit)

    EVT_MENU(Minimal_Print, HtmFrame::OnPrint)
    EVT_MENU(Minimal_Preview, HtmFrame::OnPreview)
    EVT_MENU(Minimal_PageSetup, HtmFrame::OnPageSetup)

END_EVENT_TABLE()

void HtmFrame::OnMenuFileOpen(wxCommandEvent &event)
{
}


void HtmFrame::OnMenuFileSave(wxCommandEvent &event)
{
}

void HtmFrame::OnMenuFileQuit(wxCommandEvent &event)
{
    
    Close(FALSE);
}

void HtmFrame::OnPageSetup(wxCommandEvent& WXUNUSED(event))
{
    wxPageSetupDialogData *SetupMargins =  m_Prn->GetPageSetupData();
    SetupMargins->SetPaperId(wxPAPER_A4);
    SetupMargins->SetMarginTopLeft(wxPoint(10,10));
    SetupMargins->SetMarginBottomRight(wxPoint(10,10));
    m_Prn->PageSetup();
}	


void HtmFrame::OnPrint(wxCommandEvent& WXUNUSED(event))
{
    wxPageSetupDialogData *SetupMargins =  m_Prn->GetPageSetupData();
    SetupMargins->SetPaperId(wxPAPER_A4);
    SetupMargins->SetMarginTopLeft(wxPoint(10,10));
    SetupMargins->SetMarginBottomRight(wxPoint(10,10));

    m_Prn -> PrintFile(m_Name);
}


void HtmFrame::OnPreview(wxCommandEvent& WXUNUSED(event))
{
    wxPageSetupDialogData *SetupMargins =  m_Prn->GetPageSetupData();
    SetupMargins->SetPaperId(wxPAPER_A4);
    SetupMargins->SetMarginTopLeft(wxPoint(10,10));
    SetupMargins->SetMarginBottomRight(wxPoint(10,10));

    m_Prn -> PreviewFile(m_Name);
}


 	  	 
