--- ../wxWidgets/src/gtk/app.cpp	2006-02-22 18:27:27.000000000 -0800
+++ ./src/gtk/app.cpp	2006-03-06 20:24:13.000000000 -0800
@@ -249,11 +249,11 @@
         wxTheApp->m_idleTag = 0;
     }
 
-    bool moreIdles = false;
+    bool moreIdles;
 
     // Send idle event to all who request them as long as
     // no events have popped up in the event queue.
-    while (moreIdles = wxTheApp->ProcessIdle() && (gtk_events_pending() == 0))
+    while ((moreIdles = wxTheApp->ProcessIdle()) && gtk_events_pending() == 0)
         ;
 
     // Release lock again

 	  	 
