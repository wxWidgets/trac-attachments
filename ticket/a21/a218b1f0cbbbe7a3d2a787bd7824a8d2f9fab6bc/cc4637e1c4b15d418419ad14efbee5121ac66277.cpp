src/generic/busyinfo.cpp
*** src/generic/busyinfo.cpp	Fri Dec  3 10:29:29 2021
--- src/generic/busyinfo.cpp	Fri Dec  3 10:29:34 2021
***************
*** 126,132 ****
--- 126,136 ----
  
  void wxBusyInfo::UpdateText(const wxString& str)
  {
+ #if wxUSE_MARKUP
      m_text->SetLabelMarkup(str);
+ #else //!wxUSE_MARKUP
+     m_text->SetLabelText(str);
+ #endif //wxUSE_MARKUP/!wxUSE_MARKUP    
  }
  
  void wxBusyInfo::UpdateLabel(const wxString& str)
