--- thread_orig.cpp	2008-06-03 21:36:59.656355000 -0500
+++ thread.cpp	2008-06-04 20:21:54.479771200 -0500
@@ -400,6 +400,9 @@
         m_state = STATE_NEW;
         m_priority = WXTHREAD_DEFAULT_PRIORITY;
         m_nRef = 1;
+
+        // set to true only when the thread starts waiting on m_semSuspend
+        m_isPaused = false;
     }
 
     ~wxThreadInternal()
@@ -432,9 +435,10 @@
     // kill the thread unconditionally
     wxThreadError Kill();
 
-    // suspend/resume/terminate
-    bool Suspend();
-    bool Resume();
+    // run/pause/resume/terminate
+    wxThreadError Run();
+    void Pause();
+    void Resume();
     void Cancel() { m_state = STATE_CANCELED; }
 
     // thread state
@@ -471,6 +475,10 @@
             delete m_thread;
     }
 
+    // the pause flag
+    void SetReallyPaused(bool paused) { m_isPaused = paused; }
+    bool IsReallyPaused() const { return m_isPaused; }
+
 private:
     // the thread we're associated with
     wxThread *m_thread;
@@ -480,6 +488,14 @@
     unsigned int  m_priority;   // thread priority in "wx" units
     DWORD         m_tid;        // thread id
 
+    // this flag is set when the thread is blocking on m_semSuspend
+    bool m_isPaused;
+
+    // this one is signaled when the thread should resume after having been
+    // Pause()d
+    wxSemaphore m_semSuspend;
+
+
     // number of threads which need this thread to remain alive, when the count
     // reaches 0 we kill the owning wxThread -- and die ourselves with it
     LONG m_nRef;
@@ -866,40 +882,50 @@
                                         : wxTHREAD_NO_ERROR;
 }
 
-bool wxThreadInternal::Suspend()
+void wxThreadInternal::Pause()
 {
-    DWORD nSuspendCount = ::SuspendThread(m_hThread);
-    if ( nSuspendCount == (DWORD)-1 )
+    // the state is set from the thread which pauses us first, this function
+    // is called later so the state should have been already set
+    wxCHECK_RET( m_state == STATE_PAUSED,
+                 wxT("thread must first be paused with wxThread::Pause().") );
+
+    // wait until the semaphore is Post()ed from Resume()
+    m_semSuspend.Wait();
+}
+
+void wxThreadInternal::Resume()
+{
+    wxCHECK_RET( m_state == STATE_PAUSED,
+                 wxT("can't resume thread which is not suspended.") );
+
+    // the thread might be not actually paused yet - if there were no call to
+    // TestDestroy() since the last call to Pause() for example
+    if ( IsReallyPaused() )
     {
-        wxLogSysError(_("Can not suspend thread %x"), m_hThread);
+        // wake up Pause()
+        m_semSuspend.Post();
 
-        return false;
+        // reset the flag
+        SetReallyPaused(false);
     }
 
-    m_state = STATE_PAUSED;
-
-    return true;
+    SetState(STATE_RUNNING);
 }
 
-bool wxThreadInternal::Resume()
+wxThreadError wxThreadInternal::Run()
 {
     DWORD nSuspendCount = ::ResumeThread(m_hThread);
     if ( nSuspendCount == (DWORD)-1 )
     {
         wxLogSysError(_("Can not resume thread %x"), m_hThread);
-
-        return false;
+        return wxTHREAD_MISC_ERROR;
     }
-
-    // don't change the state from STATE_EXITED because it's special and means
-    // we are going to terminate without running any user code - if we did it,
-    // the code in WaitForTerminate() wouldn't work
-    if ( m_state != STATE_EXITED )
+    else
     {
-        m_state = STATE_RUNNING;
+        SetState(STATE_RUNNING);
+        return wxTHREAD_NO_ERROR;
     }
 
-    return true;
 }
 
 // static functions
@@ -1088,24 +1114,59 @@
     }
 
     // the thread has just been created and is still suspended - let it run
-    return Resume();
+    return m_internal->Run();
+
 }
 
-// suspend/resume thread
+// pause thread
 // ---------------------
 
 wxThreadError wxThread::Pause()
 {
+    wxCHECK_MSG( This() != this, wxTHREAD_MISC_ERROR,
+                 _T("a thread can't pause itself") );
+
     wxCriticalSectionLocker lock(m_critsect);
 
-    return m_internal->Suspend() ? wxTHREAD_NO_ERROR : wxTHREAD_MISC_ERROR;
+    if ( m_internal->GetState() != STATE_RUNNING )
+    {
+        wxLogDebug(wxT("Can't pause thread which is not running."));
+
+        return wxTHREAD_NOT_RUNNING;
+    }
+
+    // just set a flag, the thread will be really paused only during the next
+    // call to TestDestroy()
+    m_internal->SetState(STATE_PAUSED);
+
+    return wxTHREAD_NO_ERROR;
 }
 
+// resume thread
+// ---------------------
+
 wxThreadError wxThread::Resume()
 {
+    wxCHECK_MSG( This() != this, wxTHREAD_MISC_ERROR,
+                 _T("a thread can't resume itself") );
+
     wxCriticalSectionLocker lock(m_critsect);
 
-    return m_internal->Resume() ? wxTHREAD_NO_ERROR : wxTHREAD_MISC_ERROR;
+    wxThreadState state = m_internal->GetState();
+
+    switch ( state )
+    {
+        case STATE_PAUSED:
+            m_internal->Resume();
+            return wxTHREAD_NO_ERROR;
+
+        case STATE_EXITED:
+            return wxTHREAD_NO_ERROR;
+
+        default:
+            wxLogDebug(_T("Attempt to resume a thread which is not paused."));
+            return wxTHREAD_MISC_ERROR;
+    }
 }
 
 // stopping thread
@@ -1223,7 +1284,26 @@
 
 bool wxThread::TestDestroy()
 {
-    wxCriticalSectionLocker lock((wxCriticalSection &)m_critsect); // const_cast
+    wxASSERT_MSG( This() == this,
+                  _T("wxThread::TestDestroy() can only be called in the context of the same thread") );
+
+    m_critsect.Enter();
+
+    if ( m_internal->GetState() == STATE_PAUSED )
+    {
+        m_internal->SetReallyPaused(true);
+        // leave the crit section or the other threads will stop too if they
+        // try to call any of (seemingly harmless) IsXXX() functions while we
+        // sleep
+        m_critsect.Leave();
+
+        m_internal->Pause();
+    }
+    else
+    {
+        // thread wasn't requested to pause, nothing to do
+        m_critsect.Leave();
+    }
 
     return m_internal->GetState() == STATE_CANCELED;
 }
