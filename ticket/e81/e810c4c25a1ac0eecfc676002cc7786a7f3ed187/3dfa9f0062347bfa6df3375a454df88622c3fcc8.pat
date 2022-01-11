diff -ru2 --ignore-all-space wxWidgets-2.6.3.orig\src/gtk/clipbrd.cpp wxWidgets-2.6.3\src/gtk/clipbrd.cpp
--- wxWidgets-2.6.3.orig\src/gtk/clipbrd.cpp	Tue Mar 21 22:36:02 2006
+++ wxWidgets-2.6.3\src/gtk/clipbrd.cpp	Fri Mar 31 10:50:57 2006
@@ -498,11 +498,10 @@
                         "selection_get",
                         GTK_SIGNAL_FUNC(selection_handler),
-                        GUINT_TO_POINTER(
 #ifdef __WXGTK20__
-                                gtk_get_current_event_time()
+                        GUINT_TO_POINTER(gtk_get_current_event_time())
 #else
-                                gdk_event_get_time(gtk_get_current_event())
+                        GUINT_TO_POINTER(gdk_event_get_time(gtk_get_current_event()))
 #endif
-                                        ) );
+                                        );

 #if wxUSE_THREADS

 	  	 
