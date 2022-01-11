extern int STF_wx_htmlView_go_back (wxWebView *htmlViewP, unsigned long flags)
{
 // STF_generic_msgWindow_output_textf ("Can go Back = %d", htmlViewP->CanGoBack ());

 // There appears to be a bug with some 'wxWebView' functions i.e.
 // 'CanGoBack', 'GoBack', 'CanGoForward' and 'GoForward'.
 // They do not work when navigating through HTML sub-files of another HTML file
 // using a "Hot word" approach. This is probably best shown by what event.GetURL ()
 // returns when these function succeed and when they fail.
 // They will for example SUCCEED when event.GetURL () returns:
 // "U:\ST_Apps\STAPIL_helpDocs\STAPIL_published\files\ST_ABOUT\st_home-c.html"
 // They will for example FAIL when event.GetURL () returns:
 // "file:///U:/ST_Apps/STAPIL_helpDocs/STAPIL_published/files/ST_GUI/ST_gui/ST_gui-c.html#ST_gui"
 
 // Extra info: The "Back" and "Forward" menu items of the Context Menu also work as expected.
 // Extra info: We would also like to request a 'GoHome' function.

 // if (htmlViewP->CanGoBack ())        // Fails when navigating through Pages using e.g "Hot words"
 //  htmlViewP->GoBack ();              // Also fails.

 // However the following lower level functions work as expected
 IWebBrowser2                           *webBrowserP;
 HRESULT                                result;

 webBrowserP = (IWebBrowser2 *)htmlViewP->GetNativeBackend ();
 if (!webBrowserP)
  return -STD_error_data_nonExistent;

 result = webBrowserP->GoBack ();
 if (result)
  return -STD_error_data_nonExistent;

 return STD_error_none;
}
