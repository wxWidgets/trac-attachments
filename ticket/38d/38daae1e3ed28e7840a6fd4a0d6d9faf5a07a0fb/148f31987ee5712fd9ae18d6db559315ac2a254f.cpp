void wxWebViewIE::SetPage(const wxString& html, const wxString& baseUrl)
{
    IHTMLDocument2* document = GetDocument();
    BSTR bstr = SysAllocString(OLESTR(""));
    SAFEARRAY *psaStrings = SafeArrayCreateVector(VT_VARIANT, 0, 1);
    if (psaStrings != NULL)
    {
        VARIANT *param;
        HRESULT hr = SafeArrayAccessData(psaStrings, (LPVOID*)&param);
        param->vt = VT_BSTR;
        param->bstrVal = bstr;

        hr = SafeArrayUnaccessData(psaStrings);
        document->write(psaStrings);
        document->close();

        SafeArrayDestroy(psaStrings);

        bstr = SysAllocString(html.wc_str());

        // Creates a new one-dimensional array
        psaStrings = SafeArrayCreateVector(VT_VARIANT, 0, 1);
        if (psaStrings != NULL)
        {
            hr = SafeArrayAccessData(psaStrings, (LPVOID*)&param);
            param->vt = VT_BSTR;
            param->bstrVal = bstr;
            hr = SafeArrayUnaccessData(psaStrings);

            document = GetDocument();
            document->write(psaStrings);
            document->Release();

            // SafeArrayDestroy calls SysFreeString for each BSTR
            SafeArrayDestroy(psaStrings);

            //We send the events when we are done to mimic webkit
            //Navigated event
            wxWebViewEvent event(wxEVT_COMMAND_WEB_VIEW_NAVIGATED,
                                 GetId(), baseUrl, "");
            event.SetEventObject(this);
            HandleWindowEvent(event);

            //Document complete event
            event.SetEventType(wxEVT_COMMAND_WEB_VIEW_LOADED);
            event.SetEventObject(this);
            HandleWindowEvent(event);
        }
        else
        {
            wxLogError("wxWebViewIE::SetPage() : psaStrings is NULL");
        }
    }
    else
    {
        wxLogError("wxWebViewIE::SetPage() : psaStrings is NULL during clear");
    }
}