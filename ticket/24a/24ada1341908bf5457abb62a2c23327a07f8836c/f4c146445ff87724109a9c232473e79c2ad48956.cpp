bool wxBitmap_CopyFromIcon(wxBitmap* bmp, const wxIcon& icon)
{
#if defined(__WXMSW__) && !wxUSE_UNICODE
   bool ok;
   if (wxPlatformInfo().GetOperatingSystemId() == wxOS_WINDOWS_9X)
   {
      ICONINFO iconInfo;
      ok = GetIconInfo((HICON)icon.GetHandle(), &iconInfo) ? true : false;
      if (ok)
      {
         bmp->SetHBITMAP(iconInfo.hbmColor);
         bmp->SetMask(new wxMask(wxInvertMask(iconInfo.hbmMask, icon.GetWidth(), icon.GetHeight())));
         DeleteObject(iconInfo.hbmMask);
      }
      else
      {
         wxLogLastError(wxT("GetIconInfo"));
      }
   }
   else
#endif
   {
      ok = bmp->CopyFromIcon(icon);
   }
   return ok;
}

 	  	 
