=== include/wx/odcombo.h
==================================================================
--- include/wx/odcombo.h	(revision 572)
+++ include/wx/odcombo.h	(local)
@@ -110,7 +110,7 @@
 protected:
 
     // Called by OnComboDoubleClick and OnComboKeyEvent
-    bool HandleKey( int keycode, bool saturate );
+    bool HandleKey( int keycode, bool saturate, wxChar unicode = 0 );
 
     // sends combobox select event from the parent combo control
     void SendComboBoxEvent( int selection );
@@ -163,6 +163,9 @@
     // Return the index of the widest item (recalculating it if necessary)
     int GetWidestItem() { CalcWidths(); return m_widestItem; }
 
+    // Stop partial completion (when some other event occurs)
+    void StopPartialCompletion();
+
     wxArrayString           m_strings;
     wxArrayPtrVoid          m_clientDatas;
 
@@ -198,6 +201,12 @@
     // Recalculate widths if they are dirty
     void CalcWidths();
 
+    // Partial completion string
+    wxString                m_partialCompletionString;
+
+    // Partial completion timer
+    wxTimer                 m_partialCompletionTimer;
+
     DECLARE_EVENT_TABLE()
 };
 
=== src/generic/odcombo.cpp
==================================================================
--- src/generic/odcombo.cpp	(revision 572)
+++ src/generic/odcombo.cpp	(local)
@@ -41,6 +41,8 @@
 // implementation
 // ============================================================================
 
+// time in milliseconds before partial completion buffer drops
+#define wxODCB_PARTIAL_COMPLETION_TIME 1000
 
 // ----------------------------------------------------------------------------
 // wxVListBoxComboPopup is a wxVListBox customized to act as a popup control
@@ -65,6 +67,7 @@
     m_value = -1;
     m_itemHover = -1;
     m_clientDataItemsType = wxClientData_None;
+    m_partialCompletionString = wxEmptyString;
 }
 
 bool wxVListBoxComboPopup::Create(wxWindow* parent)
@@ -183,6 +186,8 @@
 
 void wxVListBoxComboPopup::DismissWithEvent()
 {
+    StopPartialCompletion();
+
     int selection = wxVListBox::GetSelection();
 
     Dismiss();
@@ -223,27 +228,79 @@
 }
 
 // returns true if key was consumed
-bool wxVListBoxComboPopup::HandleKey( int keycode, bool saturate )
+bool wxVListBoxComboPopup::HandleKey( int keycode, bool saturate, wxChar unicode )
 {
     int value = m_value;
     int itemCount = GetCount();
+    int comboStyle = m_combo->GetWindowStyle();
 
+    // this is the character equivalent of the code
+    wxChar keychar=0;
+    if ((keycode >= WXK_SPACE) && (keycode <=255) && (keycode != WXK_DELETE) && wxIsprint(keycode))
+    {
+        keychar = keycode;
+    }
+    else if (unicode>0)
+    {
+        keychar = unicode; 
+    }
+
     if ( keycode == WXK_DOWN || keycode == WXK_RIGHT )
     {
         value++;
+        StopPartialCompletion();
     }
     else if ( keycode == WXK_UP || keycode == WXK_LEFT )
     {
         value--;
+        StopPartialCompletion();
     }
     else if ( keycode == WXK_PAGEDOWN )
     {
         value+=10;
+        StopPartialCompletion();
     }
     else if ( keycode == WXK_PAGEUP )
     {
         value-=10;
+        StopPartialCompletion();
     }
+    else if ( comboStyle && wxCB_READONLY )
+    {
+        // Try partial completion
+
+        // find the new partial completion string
+        if (m_partialCompletionTimer.IsRunning())
+            m_partialCompletionString+=wxString(keychar);
+        else
+            m_partialCompletionString=wxString(keychar);
+
+        // now search through the values to see if this is found
+        int found = -1;
+        unsigned int length=m_partialCompletionString.Length();
+        int i;
+        for (i=0; i<itemCount; i++)
+        {
+            wxString item=GetString(i);
+            if (( item.Length() >=length) && (!  m_partialCompletionString.CmpNoCase(item.Left(length))))
+            {
+                found=i;
+                break;
+            }
+        }
+
+        if (found<0)
+        {
+            StopPartialCompletion();
+            ::wxBell();
+            return true; // to stop the first value being set
+        }
+        else
+        {
+            value=i;
+            m_partialCompletionTimer.Start(wxODCB_PARTIAL_COMPLETION_TIME, true);
+        }
+    }
     else
         return false;
 
@@ -277,6 +334,13 @@
     return true;
 }
 
+// stop partial completion
+void wxVListBoxComboPopup::StopPartialCompletion()
+{
+    m_partialCompletionString = wxEmptyString;
+    m_partialCompletionTimer.Stop();
+}
+
 void wxVListBoxComboPopup::OnComboDoubleClick()
 {
     // Cycle on dclick (disable saturation to allow true cycling).
@@ -289,7 +353,13 @@
 void wxVListBoxComboPopup::OnComboKeyEvent( wxKeyEvent& event )
 {
     // Saturated key movement on
-    if ( !HandleKey(event.GetKeyCode(),true) )
+    if ( !HandleKey(event.GetKeyCode(),true,
+#if wxUSE_UNICODE
+        event.GetUnicodeKey()
+#else
+        0
+#endif
+        ) )
         event.Skip();
 }
 
@@ -341,9 +411,24 @@
     }
     // Hide popup if ESC is pressed
     else if ( event.GetKeyCode() == WXK_ESCAPE )
+    {
+        StopPartialCompletion();
         Dismiss();
+    }
     else
-        event.Skip();
+    {
+        int comboStyle = m_combo->GetWindowStyle();
+        int keycode = event.GetKeyCode();
+        // Process partial completion key codes here, but not the arrow keys as the base class will do that for us
+        if ((comboStyle && wxCB_READONLY) &&
+            (keycode >= WXK_SPACE) && (keycode <=255) && (keycode != WXK_DELETE) && wxIsprint(keycode))
+        {
+            OnComboKeyEvent(event);
+            SetSelection(m_value); // ensure the highlight bar moves
+        }
+        else
+            event.Skip();
+    }
 }
 
 void wxVListBoxComboPopup::Insert( const wxString& item, int pos )

 	  	 
