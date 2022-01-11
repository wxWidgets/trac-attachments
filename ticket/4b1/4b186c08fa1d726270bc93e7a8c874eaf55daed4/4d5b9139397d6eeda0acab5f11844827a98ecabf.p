Index: odcombo.cpp
===================================================================
--- odcombo.cpp	(revision 1005)
+++ odcombo.cpp	(working copy)
@@ -727,4 +728,95 @@
     return (wxClientData*) DoGetItemClientData(n);
 }
 
+#ifdef ODCOMBO_XML_HANDLER
+IMPLEMENT_DYNAMIC_CLASS(wxOwnerDrawnComboBoxXmlHandler, wxXmlResourceHandler)
+
+wxOwnerDrawnComboBoxXmlHandler::wxOwnerDrawnComboBoxXmlHandler()
+: wxXmlResourceHandler() , m_insideBox(false)
+{
+    XRC_ADD_STYLE(wxCB_SIMPLE);
+    XRC_ADD_STYLE(wxCB_SORT);
+    XRC_ADD_STYLE(wxCB_READONLY);
+    XRC_ADD_STYLE(wxCB_DROPDOWN);
+    XRC_ADD_STYLE(wxODCB_STD_CONTROL_PAINT);
+    XRC_ADD_STYLE(wxCC_PAINTING_CONTROL);
+    XRC_ADD_STYLE(wxCC_SPECIAL_DCLICK);
+    XRC_ADD_STYLE(wxCC_ALT_KEYS);
+    XRC_ADD_STYLE(wxCC_STD_BUTTON);
+    XRC_ADD_STYLE(wxCC_BUTTON_OUTSIDE_BORDER);
+    XRC_ADD_STYLE(wxCC_POPUP_ON_MOUSE_UP);
+    XRC_ADD_STYLE(wxCC_NO_TEXT_AUTO_SELECT);
+    AddWindowStyles();
+}
+
+wxObject *wxOwnerDrawnComboBoxXmlHandler::DoCreateResource()
+{
+    if( m_class == wxT("wxOwnerDrawnComboBox"))
+    {
+        // find the selection
+        long selection = GetLong( wxT("selection"), -1 );
+
+        // need to build the list of strings from children
+        m_insideBox = true;
+        CreateChildrenPrivately(NULL, GetParamNode(wxT("content")));
+        wxString *strings = (wxString *) NULL;
+        if (strList.GetCount() > 0)
+        {
+            strings = new wxString[strList.GetCount()];
+            int count = strList.GetCount();
+            for (int i = 0; i < count; i++)
+                strings[i]=strList[i];
+        }
+
+        XRC_MAKE_INSTANCE(control, wxOwnerDrawnComboBox)
+
+        control->Create(m_parentAsWindow,
+                        GetID(),
+                        GetText(wxT("value")),
+                        GetPosition(), GetSize(),
+                        strList.GetCount(),
+                        strings,
+                        GetStyle(),
+                        wxDefaultValidator,
+                        GetName());
+
+        if (selection != -1)
+            control->SetSelection(selection);
+
+        SetupWindow(control);
+
+        if (strings != NULL)
+            delete[] strings;
+        strList.Clear();    // dump the strings
+
+        return control;
+    }
+    else
+    {
+        // on the inside now.
+        // handle <item>Label</item>
+
+        // add to the list
+        wxString str = GetNodeContent(m_node);
+        if (m_resource->GetFlags() & wxXRC_USE_LOCALE)
+            str = wxGetTranslation(str);
+        strList.Add(str);
+
+        return NULL;
+    }
+}
+
+bool wxOwnerDrawnComboBoxXmlHandler::CanHandle(wxXmlNode *node)
+{
+// Avoid GCC bug
+//    return (IsOfClass(node, wxT("wxOwnerDrawnComboBox")) ||
+//           (m_insideBox && node->GetName() == wxT("item")));
+	bool fOurClass = node->GetPropVal(wxT("class"), wxEmptyString) == wxT("wxOwnerDrawnComboBox");
+    return (fOurClass ||
+           (m_insideBox && node->GetName() == wxT("item")));
+}
+
+
+#endif
+
 #endif // wxXTRA_OWNERDRAWNCOMBOBOX
Index: odcombo.h
===================================================================
--- odcombo.h	(revision 1005)
+++ odcombo.h	(working copy)
@@ -270,5 +270,21 @@
 
 
 #endif // wxUSE_OWNERDRAWNCOMBOBOX
+
+#ifdef ODCOMBO_XML_HANDLERS
+class WXDLLIMPEXP_XRC wxOwnerDrawnComboBoxXmlHandler : public wxXmlResourceHandler
+{
+DECLARE_DYNAMIC_CLASS(wxOwnerDrawnComboBoxXmlHandler)
+public:
+    wxOwnerDrawnComboBoxXmlHandler();
+    virtual wxObject *DoCreateResource();
+    virtual bool CanHandle(wxXmlNode *node);
+private:
+    bool m_insideBox;
+    wxArrayString strList;
+};
 #endif
+
+#endif
     // _WX_ODCOMBO_H_
+

 	  	 
