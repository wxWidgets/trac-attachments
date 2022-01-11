include/wx/utils.h:

#ifdef __WXMSW__
    extern WXDLLEXPORT const wxChar* wxUserResourceStr;
    wxDEPRECATED(WXDLLEXPORT wxChar* wxLoadUserResource(const wxString& resourceName, const wxString& resourceType = wxUserResourceStr));

    WXDLLEXPORT bool wxLoadUserResource(wxMemoryBuffer*, const wxChar* resourceName, const wxChar* resourceType = wxUserResourceStr, HMODULE module = NULL);
    WXDLLEXPORT bool wxLoadUserResource(wxString*, const wxChar* resourceName, const wxChar* resourceType, 
                                        HMODULE module = NULL, bool unicode = false);

#endif // MSW

 	  	 
