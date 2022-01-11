
// Returns the native path for a file URL
wxFileName wxFileSystem::URLToFileName(const wxString& url)
{
    wxString path = url;

    if ( path.Find(wxT("file://")) == 0 )
    {
        path = path.Mid(7);
    }
    else if ( path.Find(wxT("file:")) == 0 )
    {
        path = path.Mid(5);
    }
    // Remove preceding double slash on Mac Classic
#if defined(__WXMAC__) && !defined(__UNIX__)
    else if ( path.Find(wxT("//")) == 0 )
        path = path.Mid(2);
#endif

    path.Replace(wxT("%25"), wxT("%"));
    path.Replace(wxT("%3A"), wxT(":"));

#ifdef __WXMSW__
    // file urls either start with a forward slash (local harddisk),
    // otherwise they have a servername/sharename notation,
    // which only exists on msw and corresponds to a unc
    if ( path[0u] == wxT('/') && path [1u] != wxT('/'))
    {
        path = path.Mid(1);
    }
    else if ( (url.Find(wxT("file://")) == 0) &&
              (path.Find(wxT('/')) != wxNOT_FOUND) &&
              (path.Length() > 1) && (path[1u] != wxT(':')) )
    {
        path = wxT("//") + path;
    }

#ifdef __WXWINCE__
    if ((path.length () > 2) && (path[0u] == wxT('/')) && (path[1u] == wxT('/')))
    {
        path = path.Mid(1);
    }
#endif

#endif

    path.Replace(g_unixPathString, g_nativePathString);

    return wxFileName(path, wxPATH_NATIVE);
}


 	  	 
