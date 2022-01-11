wx/src/msw/utilsgui.cpp:

#ifndef __WXMICROWIN__

bool wxLoadUserResource(wxMemoryBuffer* buf, const wxChar* resourceName, const wxChar* resourceType, HMODULE module)
{
    if (NULL == module) module = wxGetInstance();
    HRSRC hrsrc = FindResource(module, resourceName, resourceType);
    bool ok = (hrsrc != NULL);
    if (ok)
    {
        const size_t len = SizeofResource(module, hrsrc);
        if (len)
        {
            HGLOBAL hglob = LoadResource(module, hrsrc);
            if (hglob)
            {
                const void* src = LockResource(hglob);
                      void* dst = buf->GetWriteBuf(len);
                memcpy(dst, src, len);
                buf->UngetWriteBuf(len);
            }
        }
    }
    return ok;
}

bool wxLoadUserResource(wxString* str, const wxChar* resourceName, const wxChar* resourceType, 
                        HMODULE module, bool unicode)
{
    wxMemoryBuffer buf;
    bool ok = wxLoadUserResource(&buf, resourceName, resourceType, module);
    if (ok)
    {
        const size_t len = buf.GetDataLen();
        if (len)
        {
            if (unicode)
            {
                str->operator=(wxString((const wchar_t*)buf.GetData(), *wxConvCurrent, len / sizeof(wchar_t)));
            }
            else
            {
                str->operator=(wxString((const char*)buf.GetData(), *wxConvCurrent, len));
            }
        }
    }
    return ok;
}

/*DEPRECATED*/ wxChar* wxLoadUserResource(const wxString& resourceName, const wxString& resourceType)
{
    wxChar* p = NULL;
    wxString str;
#if wxUSE_UNICODE
    const bool unicode = true;
#else
    const bool unicode = false;
#endif
    if (wxLoadUserResource(&str, resourceName, resourceType, wxGetInstance(), unicode))
    {
        p = new wxChar[str.Length()+1];
        wxStrncpy(p, str, str.Length()+1);
    }
    return p;
}


 	  	 
