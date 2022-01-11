diff -ru2 --ignore-all-space wxWidgets-2.6.3.orig\src/msw/app.cpp wxWidgets-2.6.3\src/msw/app.cpp
--- wxWidgets-2.6.3.orig\src/msw/app.cpp	Sun Feb 05 23:40:47 2006
+++ wxWidgets-2.6.3\src/msw/app.cpp	Mon Apr 03 09:44:46 2006
@@ -221,7 +221,13 @@
 bool wxGUIAppTraits::DoMessageFromThreadWait()
 {
+    MSG msg;
+
     // we should return false only if the app should exit, i.e. only if
     // Dispatch() determines that the main event loop should terminate
-    return !wxTheApp || wxTheApp->Dispatch();
+
+    // Dispatch() should only be called when there are messages in the
+    // queue. Otherwise it would block inside ::GetMessage
+
+    return !wxTheApp || (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE|PM_NOYIELD) && wxTheApp->Dispatch());
 }

diff -ru2 --ignore-all-space wxWidgets-2.6.3.orig\src/msw/thread.cpp wxWidgets-2.6.3\src/msw/thread.cpp
--- wxWidgets-2.6.3.orig\src/msw/thread.cpp	Fri Jul 01 15:38:58 2005
+++ wxWidgets-2.6.3\src/msw/thread.cpp	Mon Apr 03 09:44:46 2006
@@ -742,10 +742,4 @@
                 if ( wxThread::IsMain() )
                 {
-                    // it looks that sometimes WAIT_OBJECT_0 + 1 is
-                    // returned but there are no messages in the thread
-                    // queue -- prevent DoMessageFromThreadWait() from
-                    // blocking inside ::GetMessage() forever in this case
-                    ::PostMessage(NULL, WM_NULL, 0, 0);
-
                     wxAppTraits *traits = wxTheApp ? wxTheApp->GetTraits()
                                                    : NULL;


 	  	 
