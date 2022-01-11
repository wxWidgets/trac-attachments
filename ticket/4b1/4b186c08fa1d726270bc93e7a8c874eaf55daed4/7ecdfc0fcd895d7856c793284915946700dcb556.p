--- ../wxWidgets/src/xrc/xh_odcombo.cpp	1970-01-01 01:00:00.000000000 +0100
+++ src/xrc/xh_odcombo.cpp	2006-06-19 20:14:36.000000000 +0100
@@ -0,0 +1,121 @@
+/////////////////////////////////////////////////////////////////////////////
+// Name:        src/xrc/xh_odcombo.cpp
+// Purpose:     XRC resource for wxRadioBox
+// Author:      Alex Bligh
+// Created:     2006/06/19
+// RCS-ID:      $Id: xh_odcombo.cpp,v 1.15 2006/06/07 22:01:12 ABX Exp $
+// Copyright:   (c) 2006 Alex Bligh
+// Licence:     wxWindows licence
+//
+// Based on xh_combo.cpp - see credits therein
+//
+/////////////////////////////////////////////////////////////////////////////
+
+// For compilers that support precompilation, includes "wx.h".
+#include "wx/wxprec.h"
+
+#ifdef __BORLANDC__
+    #pragma hdrstop
+#endif
+
+#if wxUSE_XRC && wxUSE_ODCOMBOBOX
+
+#include "wx/xrc/xh_odcombo.h"
+#include "wx/odcombo.h"
+
+#ifndef WX_PRECOMP
+    #include "wx/intl.h"
+#endif
+
+IMPLEMENT_DYNAMIC_CLASS(wxOwnerDrawnComboBoxXmlHandler, wxXmlResourceHandler)
+
+wxOwnerDrawnComboBoxXmlHandler::wxOwnerDrawnComboBoxXmlHandler()
+                     :wxXmlResourceHandler()
+                     ,m_insideBox(false)
+{
+    XRC_ADD_STYLE(wxCB_SIMPLE);
+    XRC_ADD_STYLE(wxCB_SORT);
+    XRC_ADD_STYLE(wxCB_READONLY);
+    XRC_ADD_STYLE(wxCB_DROPDOWN);
+    XRC_ADD_STYLE(wxODCB_STD_CONTROL_PAINT);
+    XRC_ADD_STYLE(wxODCB_DCLICK_CYCLES);
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
+        control->SetPopupControl(NULL);
+
+        wxSize ButtonSize=GetSize(wxT("buttonsize"));
+
+        if (ButtonSize != wxDefaultSize)
+	  control->SetButtonPosition(ButtonSize.GetWidth(), ButtonSize.GetHeight());
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
+//  Avoid GCC bug - this fails on certain GCC 3.x builds for an unknown reason
+//  return (IsOfClass(node, wxT("wxOwnerDrawnComboBox")) ||
+//         (m_insideBox && node->GetName() == wxT("item")));
+
+    bool fOurClass = node->GetPropVal(wxT("class"), wxEmptyString) == wxT("wxOwnerDrawnComboBox");
+    return (fOurClass ||
+	    (m_insideBox && node->GetName() == wxT("item")));
+
+}
+
+#endif // wxUSE_XRC && wxUSE_ODCOMBOBOX
--- ../wxWidgets/src/xrc/xmlrsall.cpp	2006-06-01 00:57:54.000000000 +0100
+++ src/xrc/xmlrsall.cpp	2006-06-19 19:49:28.000000000 +0100
@@ -77,6 +77,9 @@
 #if wxUSE_COMBOBOX
     AddHandler(new wxComboBoxXmlHandler);
 #endif
+#if wxUSE_ODCOMBOBOX
+    AddHandler(new wxOwnerDrawnComboBoxXmlHandler);
+#endif
 #if wxUSE_NOTEBOOK
     AddHandler(new wxNotebookXmlHandler);
 #endif
--- ../wxWidgets/include/wx/xrc/xh_all.h	2006-06-01 00:57:28.000000000 +0100
+++ include/wx/xrc/xh_all.h	2006-06-19 19:49:56.000000000 +0100
@@ -34,6 +34,7 @@
 #include "wx/xrc/xh_sizer.h"
 #include "wx/xrc/xh_stbmp.h"
 #include "wx/xrc/xh_notbk.h"
+#include "wx/xrc/xh_odcombo.h"
 #include "wx/xrc/xh_listbk.h"
 #include "wx/xrc/xh_choicbk.h"
 #include "wx/xrc/xh_treebk.h"
--- ../wxWidgets/include/wx/xrc/xh_odcombo.h	1970-01-01 01:00:00.000000000 +0100
+++ include/wx/xrc/xh_odcombo.h	2006-06-19 20:14:43.000000000 +0100
@@ -0,0 +1,35 @@
+/////////////////////////////////////////////////////////////////////////////
+// Name:        xh_odcombo.h
+// Purpose:     XML resource handler for wxOwnerDrawnComboBox
+// Author:      Alex Bligh
+// Created:     2006/06/19
+// RCS-ID:      $Id: xh_odcombo.h,v 1.6 2005/09/23 12:51:12 MR Exp $
+// Copyright:   (c) 2006 Alex Bligh
+// Licence:     wxWindows licence
+//
+// Based on xh_combo.h - see credits therein
+//
+/////////////////////////////////////////////////////////////////////////////
+
+#ifndef _WX_XH_ODCOMBO_H_
+#define _WX_XH_ODCOMBO_H_
+
+#include "wx/xrc/xmlres.h"
+
+#if wxUSE_ODCOMBOBOX
+
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
+
+#endif
+
+#endif // _WX_XH_ODCOMBO_H_
--- ../wxWidgets/build/bakefiles/files.bkl	2006-06-19 19:05:22.000000000 +0100
+++ build/bakefiles/files.bkl	2006-06-19 19:24:48.000000000 +0100
@@ -2838,6 +2838,7 @@
     src/xrc/xh_listc.cpp
     src/xrc/xh_menu.cpp
     src/xrc/xh_notbk.cpp
+    src/xrc/xh_odcombo.cpp
     src/xrc/xh_panel.cpp
     src/xrc/xh_radbt.cpp
     src/xrc/xh_radbx.cpp
@@ -2891,6 +2892,7 @@
     wx/xrc/xh_listc.h
     wx/xrc/xh_menu.h
     wx/xrc/xh_notbk.h
+    wx/xrc/xh_odcombo.h
     wx/xrc/xh_panel.h
     wx/xrc/xh_radbt.h
     wx/xrc/xh_radbx.h
--- ../wxWidgets/samples/xrc/rc/controls.xrc	2006-06-19 19:06:55.000000000 +0100
+++ samples/xrc/rc/controls.xrc	2006-06-19 19:46:46.000000000 +0100
@@ -127,6 +127,13 @@
                                             <item>in the toolbar</item>
                                         </content>
                                     </object>
+                                    <object class="wxOwnerDrawnComboBox">
+                                        <content>
+                                            <item>Owner Drawn</item>
+                                            <item>combobox</item>
+                                            <item>in the toolbar</item>
+                                        </content>
+                                    </object>
                                 </object>
                             </object>
                             <object class="sizeritem">

 	  	 
