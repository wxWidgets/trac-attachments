Index: src/gtk/window.cpp
===================================================================
RCS file: /pack/cvsroots/wxwidgets/wxWidgets/src/gtk/window.cpp,v
retrieving revision 1.548.2.13
diff -u -r1.548.2.13 window.cpp
--- src/gtk/window.cpp	2006/03/18 21:58:19	1.548.2.13
+++ src/gtk/window.cpp	2006/05/09 13:11:48
@@ -4145,6 +4145,8 @@
 #ifdef __WXGTK20__
     if (m_wxwindow && GTK_PIZZA(m_wxwindow)->bin_window)
         gdk_window_process_updates( GTK_PIZZA(m_wxwindow)->bin_window, FALSE );
+    if (m_widget && m_widget->window)
+        gdk_window_process_updates( m_widget->window, FALSE );
 #else
     if (!m_updateRegion.IsEmpty())
         GtkSendPaintEvents();

 	  	 
