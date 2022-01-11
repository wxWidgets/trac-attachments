Index: include/wx/gtk/window.h
===================================================================
RCS file: /pack/cvsroots/wxwidgets/wxWidgets/include/wx/gtk/window.h,v
retrieving revision 1.142
diff -u -r1.142 window.h
--- include/wx/gtk/window.h	2006/05/05 17:04:40	1.142
+++ include/wx/gtk/window.h	2006/05/18 16:52:28
@@ -109,6 +109,12 @@
     virtual void AddChild( wxWindowBase *child );
     virtual void RemoveChild( wxWindowBase *child );
 
+#ifdef __WXGTK20__
+#if wxABI_VERSION >= 20603 /* 2.6.3+ only */
+    void SetDoubleBuffered( bool on );
+#endif
+#endif
+
     // implementation
     // --------------
 
Index: src/gtk/window.cpp
===================================================================
RCS file: /pack/cvsroots/wxwidgets/wxWidgets/src/gtk/window.cpp,v
retrieving revision 1.602
diff -u -r1.602 window.cpp
--- src/gtk/window.cpp	2006/05/10 16:36:31	1.602
+++ src/gtk/window.cpp	2006/05/18 16:52:32
@@ -3079,6 +3079,16 @@
         UpdateWindowUI(wxUPDATE_UI_FROMIDLE);
 }
 
+#ifdef __WXGTK20__
+void wxWindowGTK::SetDoubleBuffered( bool on )
+{
+  wxCHECK_RET( (m_widget != NULL), wxT("invalid window") );
+
+  if (m_wxwindow)
+    gtk_widget_set_double_buffered( m_wxwindow, on );
+}
+#endif // __WXGTK20__
+
 void wxWindowGTK::DoGetSize( int *width, int *height ) const
 {
     wxCHECK_RET( (m_widget != NULL), wxT("invalid window") );

 	  	 
