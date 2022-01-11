/////////////////////////////////////////////////////////////////////////////
// Name:        include/wx/gtk/webview_download.h
// Purpose:     GTK WebKit Download File header
// Author:      Stefano Mtangoo
// Id:          $Id:$
// Copyright:   (c) 2012 Hosanna Higher Technologies
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
/*
The following functionalities will be added as events to webview.h file
//Download Events
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_WEBVIEW, wxEVT_COMMAND_WEB_VIEW_DOWNLOAD_STARTED, wxWebViewEvent );
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_WEBVIEW, wxEVT_COMMAND_WEB_VIEW_DOWNLOAD_PROGRESS, wxWebViewEvent );//GetInt to get progress?
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_WEBVIEW, wxEVT_COMMAND_WEB_VIEW_DOWNLOAD_COMPLETE, wxWebViewEvent );
 

*/


#ifndef _WX_GTK_DOWNLOAD_H_
#define _WX_GTK_DOWNLOAD_H_

#include "wx/defs.h"

#if wxUSE_WEBVIEW && wxUSE_WEBVIEW_WEBKIT && defined(__WXGTK__)

enum WebviewDownloadStatus{
    WEBVIEW_DOWNLOAD_STATUS_ERROR = -1,
    WEBVIEW_DOWNLOAD_STATUS_STARTED = 0, 
    WEBVIEW_DOWNLOAD_STATUS_CANCELLED,
    WEBVIEW_DOWNLOAD_STATUS_FINISHED
};



enum wxWebViewDownloadError
{
    wxWEB_DOWNLOAD_ERR_USER_CANCELLED,
    wxWEB_WEBKIT_DOWNLOAD_ERR_DESTINATION,
    wxWEB_DOWNLOAD_ERR_NETWORK, 
    wxWEB_DOWNLOAD_ERR_OTHER
};

class WXDLLIMPEXP_WEBVIEW wxWebViewDownload 
{
public:
    wxWebViewDownload(const wxString& url = wxString(), const wxString& target = wxString(), unsigned long id=-1); 
    wxWebViewDownload();
    
    SetFileInfo(wxFileType info);
    SetFileInfoByExt(const wxString& ext);
    SetFileTarget(const wxString& path); 
    
    wxFileType GetFileInfo();
    
    SetId(unsigned long id);
    unsigned long GetId();
    
    SetReferrerUrl(const wxString& url);
    SetReferrerUrl(wxURL url);
    wxURL GetReferrerUrl();
    
    wxDateTime GetStartTime();
    wxDateTime GetEndTime();
    
    wxFileName GetFileName();
    long long GetFileSize();
    
    WebviewDownloadStatus GetStatus();
    wxWebViewDownloadError GetError();

private:
     wxDateTime m_startTime;
     wxDateTime m_endTime;
     unsigned long m_downloadId;//it will identify download in case there is download manager
     
     wxFileType m_fileInfo;
     wxString m_filename;
     long long m_fileSize;//The total size of the file in bytes or -1 if unknown
     
     wxURL m_referrerUrl;
     WebviewDownloadStatus m_status;
     wxWebViewDownloadError m_error;
     wxString m_targetFile;//Indicates the location at which the downloaded file will be
     
};
 

#endif // _WX_GTK_DOWNLOAD_H_
