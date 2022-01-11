--- src/gtk/msgdlg-o.cpp	2007-07-02 12:53:23.000000000 +0200
+++ src/gtk/msgdlg.cpp	2007-07-16 02:35:16.000000000 +0200
@@ -149,7 +149,16 @@
     if (m_parent)
         gtk_window_present( GTK_WINDOW(m_parent->m_widget) );
 
-    gdk_pointer_ungrab(GDK_CURRENT_TIME);
+    // It is no good showing a modal dialog while we have mouse capture.
+    // If so, release it and send event to app.
+    //gdk_pointer_ungrab(GDK_CURRENT_TIME);
+    wxWindow *wnd_capt = GetCapture();
+    if( wnd_capt ){
+        wnd_capt->ReleaseMouse( );
+        wxMouseCaptureLostEvent evt( wnd_capt->GetId() );
+        wnd_capt->ProcessEvent( evt );
+    }
+    
     gint result = gtk_dialog_run(GTK_DIALOG(m_widget));
     gtk_widget_destroy(m_widget);
     m_widget = NULL;
--- src/gtk/dialog-o.cpp	2007-07-02 12:52:51.000000000 +0200
+++ src/gtk/dialog.cpp	2007-07-16 02:28:33.000000000 +0200
@@ -112,6 +112,15 @@
        return GetReturnCode();
     }
 
+    // It is no good showing a modal dialog while we have mouse capture.
+    // If so, release it and send event to app.
+    wxWindow *wnd_capt = GetCapture();
+    if( wnd_capt ){
+        wnd_capt->ReleaseMouse( );
+        wxMouseCaptureLostEvent evt( wnd_capt->GetId() );
+        wnd_capt->ProcessEvent( evt );
+    }
+    
     // use the apps top level window as parent if none given unless explicitly
     // forbidden
     if ( !GetParent() && !(GetWindowStyleFlag() & wxDIALOG_NO_PARENT) )

 	  	 
