diff -ru2 --ignore-all-space wxWidgets-2.6.3.orig\src/msw/main.cpp wxWidgets-2.6.3\src/msw/main.cpp
--- wxWidgets-2.6.3.orig\src/msw/main.cpp	Sun Aug 28 15:11:18 2005
+++ wxWidgets-2.6.3\src/msw/main.cpp	Mon Apr 03 09:47:27 2006
@@ -144,5 +144,5 @@
 #ifdef __VISUALC__

-static void wxSETranslator(unsigned int WXUNUSED(code), EXCEPTION_POINTERS *ep)
+void wxSETranslator(unsigned int WXUNUSED(code), EXCEPTION_POINTERS *ep)
 {
     switch ( wxGlobalSEHandler(ep) )
diff -ru2 --ignore-all-space wxWidgets-2.6.3.orig\src/msw/thread.cpp wxWidgets-2.6.3\src/msw/thread.cpp
--- wxWidgets-2.6.3.orig\src/msw/thread.cpp	Fri Jul 01 15:38:58 2005
+++ wxWidgets-2.6.3\src/msw/thread.cpp	Mon Apr 03 09:44:46 2006
@@ -38,4 +38,5 @@
 #include "wx/msw/missing.h"

+#include "wx/except.h"
 #include "wx/module.h"
 #include "wx/thread.h"
@@ -87,4 +88,25 @@
 #endif

+#if wxUSE_ON_FATAL_EXCEPTION
+extern unsigned long wxGlobalSEHandler(EXCEPTION_POINTERS *pExcPtrs);
+extern void wxSETranslator(unsigned int WXUNUSED(code), EXCEPTION_POINTERS *ep);
+
+#if defined(__VISUALC__) && !defined(__WXWINCE__)
+    // See main.cpp
+    // As every thread maintains its own SE translator we need to register our
+    // translator for every thread we create
+    #include <eh.h>
+
+    #if _MSC_VER <= 1310
+        #pragma warning(disable:4535)
+    #endif
+
+    // note that the SE translator must be called wxSETranslator!
+    #define DisableAutomaticSETranslator() _set_se_translator(wxSETranslator)
+#else // !__VISUALC__
+    #define DisableAutomaticSETranslator()
+#endif // __VISUALC__/!__VISUALC__
+#endif // wxUSE_ON_FATAL_EXCEPTION
+
 // ----------------------------------------------------------------------------
 // constants
@@ -434,4 +456,5 @@
     // thread function
     static THREAD_RETVAL THREAD_CALLCONV WinThreadStart(void *thread);
+    static THREAD_RETVAL WinThreadStart2(wxThread * const thread, const bool exitOnly);

     void KeepAlive()
@@ -476,8 +499,40 @@
 };

+THREAD_RETVAL wxThreadInternal::WinThreadStart2(wxThread * const thread, const bool exitOnly)
+{
+    THREAD_RETVAL rc = (THREAD_RETVAL)-1;
+
+    wxTRY
+    {
+        class CallOnExit
+        {
+        public:
+            CallOnExit(wxThread * const thread) : m_thread(thread) { }
+            ~CallOnExit()                                          { m_thread->OnExit(); }
+        protected:
+            wxThread * const m_thread;
+        } callOnExit(thread);
+
+        if ( !exitOnly )
+        {
+            // store the thread object in the TLS
+            if ( !::TlsSetValue(gs_tlsThisThread, thread) )
+            {
+                wxLogSysError(_("Can not start thread: error writing TLS."));
+
+                return (THREAD_RETVAL)-1;
+            }
+
+        rc = (THREAD_RETVAL)thread->Entry();
+        }
+    }
+    wxCATCH_ALL(wxTheApp->OnUnhandledException();)
+
+    return rc;
+}

 THREAD_RETVAL THREAD_CALLCONV wxThreadInternal::WinThreadStart(void *param)
 {
-    THREAD_RETVAL rc;
+    THREAD_RETVAL rc = (THREAD_RETVAL)-1;

     wxThread * const thread = (wxThread *)param;
@@ -487,22 +542,27 @@
     const bool hasExited = thread->m_internal->GetState() == STATE_EXITED;

-    if ( hasExited )
-    {
-        rc = (THREAD_RETVAL)-1;
-    }
-    else // do run thread
-    {
-        // store the thread object in the TLS
-        if ( !::TlsSetValue(gs_tlsThisThread, thread) )
+    DisableAutomaticSETranslator();
+
+#if wxUSE_ON_FATAL_EXCEPTION
+    __try
         {
-            wxLogSysError(_("Can not start thread: error writing TLS."));
+#endif // wxUSE_ON_FATAL_EXCEPTION

-            return (DWORD)-1;
-        }
+        rc = WinThreadStart2(thread, hasExited);

-        rc = (THREAD_RETVAL)thread->Entry();
+#if wxUSE_ON_FATAL_EXCEPTION
     }
+    __except ( wxGlobalSEHandler(GetExceptionInformation()) )
+    {
+        // use the same exit code as abort()
+        ::ExitProcess(3);

-    thread->OnExit();
+#if !defined(_MSC_VER) || defined(__WXDEBUG__) || (defined(_MSC_VER) && _MSC_VER <= 1200)
+        // this code is unreachable but put it here to suppress warnings in some compilers
+        // and disable for others to supress warnings too
+        return (THREAD_RETVAL)-1;
+#endif // !__VISUALC__ in release build
+    }
+#endif // wxUSE_ON_FATAL_EXCEPTION

     // save IsDetached because thread object can be deleted by joinable
@@ -513,6 +573,7 @@
     {
         // enter m_critsect before changing the thread state
-        wxCriticalSectionLocker lock(thread->m_critsect);
+        thread->m_critsect.Enter();
         thread->m_internal->SetState(STATE_EXITED);
+        thread->m_critsect.Leave();
     }



 	  	 
