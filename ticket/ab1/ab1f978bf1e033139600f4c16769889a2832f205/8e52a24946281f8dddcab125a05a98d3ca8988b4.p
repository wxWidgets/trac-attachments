=== include/wx/aui/framemanager.h
==================================================================
--- include/wx/aui/framemanager.h	(revision 1102)
+++ include/wx/aui/framemanager.h	(local)
@@ -44,6 +44,10 @@
     wxAUI_MGR_TRANSPARENT_DRAG      = 1 << 2,
     wxAUI_MGR_TRANSPARENT_HINT      = 1 << 3,
     wxAUI_MGR_TRANSPARENT_HINT_FADE = 1 << 4,
+    // The venetian blind effect is ONLY used when the wxAUI_MGR_TRANSPARENT_HINT has been used, but
+    // at runtime we determine we cannot use transparency (because, for instance, the OS does not support it).
+    // setting this flag drops back in such circumstances (only) to the behaviour without wxAUI_MGR_TRANSPARENT_HINT
+    wxAUI_MGR_DISABLE_VENETIAN_BLINDS = 1 << 5,
 
     wxAUI_MGR_DEFAULT = wxAUI_MGR_ALLOW_FLOATING |
                         wxAUI_MGR_TRANSPARENT_HINT |
@@ -540,6 +544,7 @@
     wxFrame* m_hint_wnd;         // transparent hint window, if supported by platform
     wxTimer m_hint_fadetimer;    // transparent fade timer
     wxByte m_hint_fadeamt;       // transparent fade amount
+    wxByte m_hint_fademax;       // maximum value of hint fade
 
 #ifndef SWIG
     DECLARE_EVENT_TABLE()
=== include/wx/gtk/toplevel.h
==================================================================
--- include/wx/gtk/toplevel.h	(revision 1102)
+++ include/wx/gtk/toplevel.h	(local)
@@ -129,6 +129,8 @@
     // is the frame currently grabbed explicitly
     // by the application?
     bool m_grabbed;
+
+    static wxCachedEnvironmentVariable s_TransparencyOverride;
 };
 
 #endif // __GTKTOPLEVELH__
=== include/wx/utils.h
==================================================================
--- include/wx/utils.h	(revision 1102)
+++ include/wx/utils.h	(local)
@@ -477,6 +477,62 @@
 // remove the env var from environment
 inline bool wxUnsetEnv(const wxString& var) { return wxSetEnv(var, NULL); }
 
+// This class provides a fast way of reading environment variables. As
+// by assumption these don't change during the execution of the program,
+// we are careful to cache the reads. We also cache their converted
+// values as the assumption is these may be read very many times.
+class wxCachedEnvironmentVariable : public wxObject
+{
+public:
+    // The constructor can be called at static initialization time
+    // so we have to be careful about what we do here
+    wxCachedEnvironmentVariable(const wxString Name) : 
+        m_bHasRead(false),
+        m_bHasValue(false),
+        m_bValue(false),
+        m_lValue(0),
+        m_dValue(0.0), // note m_sValue automatically initialized empty
+        m_Name(Name)
+        {}
+
+    bool ToBool() { if (!m_bHasRead) DoRead(); return m_bValue; }
+    long ToLong() { if (!m_bHasRead) DoRead(); return m_lValue; }
+    double ToDoublel() { if (!m_bHasRead) DoRead(); return m_dValue; }
+    wxString ToString() { if (!m_bHasRead) DoRead(); return m_sValue; }
+    bool IsPresent() {  if (!m_bHasRead) DoRead(); return m_bHasValue; }
+
+private:
+    void DoRead()
+    {
+        // we rely on the fact that m_HasValue etc are all initialised to false
+
+        // don't call us again
+        m_bHasRead = true;
+
+        // If no environment variable specified in constructor, return
+        if (m_Name.IsEmpty())
+            return;
+
+        wxString env_value;
+        if (wxGetEnv(m_Name, &env_value) && !env_value.empty())
+        {
+            m_bHasValue = true;
+            env_value.ToLong(&m_lValue);
+            env_value.ToDouble(&m_dValue);
+            m_bValue = (m_lValue != 0);
+            m_sValue = env_value;
+        }
+    }
+
+    bool m_bHasRead;
+    bool m_bHasValue;
+    bool m_bValue;
+    long m_lValue;
+    double m_dValue;
+    wxString m_sValue;
+    wxString m_Name;
+};
+
 // ----------------------------------------------------------------------------
 // Network and username functions.
 // ----------------------------------------------------------------------------
=== samples/aui/auidemo.cpp
==================================================================
--- samples/aui/auidemo.cpp	(revision 1102)
+++ samples/aui/auidemo.cpp	(local)
@@ -913,12 +913,12 @@
 {
     unsigned int flag = 0;
 
-#if !defined(__WXMSW__) && !defined(__WXMAC__)
+#if !defined(__WXMSW__) && !defined(__WXMAC__) && !defined(__WXGTK__)
     if (event.GetId() == ID_TransparentDrag ||
         event.GetId() == ID_TransparentHint ||
         event.GetId() == ID_TransparentHintFade)
     {
-        wxMessageBox(wxT("This option is presently only available on wxMSW and wxMac"));
+        wxMessageBox(wxT("This option is presently only available on wxGTK, wxMSW and wxMac"));
         return;
     }
 #endif
=== src/aui/framemanager.cpp
==================================================================
--- src/aui/framemanager.cpp	(revision 1102)
+++ src/aui/framemanager.cpp	(local)
@@ -64,7 +64,108 @@
 
 IMPLEMENT_DYNAMIC_CLASS(wxFrameManagerEvent, wxEvent)
 
+class wxPseudoTransparentFrame : public wxFrame
+{
+public:
+    wxPseudoTransparentFrame(wxWindow* parent = NULL,
+                wxWindowID id = -1,
+                const wxString& title = wxT(""),
+                const wxPoint& pos = wxDefaultPosition,
+                const wxSize& size = wxDefaultSize,
+                long style = wxDEFAULT_FRAME_STYLE,
+                const wxString &name = wxT("frame"))
+                    : wxFrame(parent, id, title, pos, size, style | wxFRAME_SHAPED, name)
+    {
+        SetBackgroundStyle(wxBG_STYLE_CUSTOM);
+        m_Amount=0;
+        m_MaxWidth=0;
+        m_MaxHeight=0;
+#ifdef __WXGTK__
+        m_CanSetShape = false; // have to wait for window create event on GTK
+#else
+        m_CanSetShape = true;
+#endif
+        SetTransparent(0);
+    }
 
+    virtual bool SetTransparent(wxByte alpha)
+    {
+        if (m_CanSetShape)
+        {
+            int w=100; // some defaults
+            int h=100;
+            GetClientSize(&w, &h);
+            if ((alpha != m_Amount) || (m_MaxWidth<w) | (m_MaxHeight<h))
+            {
+                // Make the region at least double the height and width so we don't have
+                // to rebuild if the size changes.
+                m_MaxWidth=w*2;
+                m_MaxHeight=h*2;
+                m_Amount = alpha;
+                m_Region.Clear();
+//				m_Region.Union(0, 0, 1, m_MaxWidth);
+                if (m_Amount)
+                {
+                    for (int y=0; y<m_MaxHeight; y++)
+                    {
+                        // Reverse the order of the bottom 4 bits
+                        int j=((y&8)?1:0)|((y&4)?2:0)|((y&2)?4:0)|((y&1)?8:0);
+                        if ((j*16+8)<m_Amount)
+                            m_Region.Union(0, y, m_MaxWidth, 1);
+                    }
+                }
+                SetShape(m_Region);
+                Refresh();
+            }
+        }
+        return true;
+    }
+
+    void OnPaint(wxPaintEvent & event)
+    {
+        wxPaintDC dc(this);
+        
+        dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
+        dc.SetPen(*wxTRANSPARENT_PEN);
+        
+        wxRegionIterator upd(GetUpdateRegion()); // get the update rect list
+        
+        while (upd)
+        {
+            wxRect rect(upd.GetRect());
+            dc.DrawRectangle(rect.x, rect.y, rect.width, rect.height);
+
+            upd++;
+        }
+    }
+
+#ifdef __WXGTK__
+    void OnWindowCreate(wxWindowCreateEvent& WXUNUSED(event)) {m_CanSetShape=true; SetTransparent(0);}
+#endif
+
+private:
+    int m_Amount;
+    int m_MaxWidth;
+    int m_MaxHeight;
+    bool m_CanSetShape;
+
+    wxRegion m_Region;
+
+    DECLARE_DYNAMIC_CLASS(wxPseudoTransparentFrame);
+    DECLARE_EVENT_TABLE();
+};
+
+
+IMPLEMENT_DYNAMIC_CLASS( wxPseudoTransparentFrame, wxFrame )
+
+BEGIN_EVENT_TABLE(wxPseudoTransparentFrame, wxFrame)
+    EVT_PAINT(wxPseudoTransparentFrame::OnPaint)
+#ifdef __WXGTK__
+    EVT_WINDOW_CREATE(wxPseudoTransparentFrame::OnWindowCreate)
+#endif
+END_EVENT_TABLE()
+
+
 // -- static utility functions --
 
 static wxBitmap wxPaneCreateStippleBitmap()
@@ -496,7 +597,7 @@
 #endif
 
     // Make a window to use for a transparent hint
-#if defined(__WXMSW__)
+#if defined(__WXMSW__) || defined(__WXGTK__)
     m_hint_wnd = new wxFrame(m_frame, -1, wxEmptyString, wxDefaultPosition, wxSize(1,1),
                              wxFRAME_TOOL_WINDOW |
                              wxFRAME_FLOAT_ON_PARENT |
@@ -523,11 +624,23 @@
     p->SetBackgroundColour(*wxBLUE);
 #endif
 
+    m_hint_fademax=50;
+
     if (m_hint_wnd && !m_hint_wnd->CanSetTransparent())
     {
+
         m_hint_wnd->Close();
         m_hint_wnd->Destroy();
         m_hint_wnd = NULL;
+
+        // If we can convert it to a PseudoTransparent window, do so
+        m_hint_wnd = new wxPseudoTransparentFrame (m_frame, -1, wxEmptyString, wxDefaultPosition, wxSize(1,1),
+                                                wxFRAME_TOOL_WINDOW |
+                                                wxFRAME_FLOAT_ON_PARENT |
+                                                wxFRAME_NO_TASKBAR |
+                                                wxNO_BORDER);
+        
+        m_hint_fademax = 128;
     }    
 }
 
@@ -2462,25 +2575,29 @@
 
 void wxFrameManager::OnHintFadeTimer(wxTimerEvent& WXUNUSED(event))
 {
-    if (!m_hint_wnd || m_hint_fadeamt >= 50)
+    if (!m_hint_wnd || m_hint_fadeamt >= m_hint_fademax)
     {
         m_hint_fadetimer.Stop();
         return;
     }
 
-    m_hint_fadeamt += 5;
+    m_hint_fadeamt += 4;
     m_hint_wnd->SetTransparent(m_hint_fadeamt);
 }
 
 void wxFrameManager::ShowHint(const wxRect& rect)
 {
-    if ((m_flags & wxAUI_MGR_TRANSPARENT_HINT) != 0 && m_hint_wnd)
+    if ((m_flags & wxAUI_MGR_TRANSPARENT_HINT) != 0
+        && m_hint_wnd
+        // Finally, don't use a venetian blind effect if it's been specifically disabled
+        && !((m_hint_wnd->IsKindOf(CLASSINFO(wxPseudoTransparentFrame))) && (m_flags & wxAUI_MGR_DISABLE_VENETIAN_BLINDS))
+       )
     {
         if (m_last_hint == rect)
             return;
         m_last_hint = rect;
 
-        wxByte initial_fade = 50;
+        wxByte initial_fade = m_hint_fademax;
         if (m_flags & wxAUI_MGR_TRANSPARENT_HINT_FADE)
             initial_fade = 0;
 
@@ -2565,6 +2682,7 @@
     // hides a transparent window hint, if there is one
     if (m_hint_wnd)
     {
+        m_hint_wnd->Show(false);
         m_hint_wnd->SetTransparent(0);
         m_hint_fadetimer.Stop();
         m_last_hint = wxRect();
=== src/gtk/toplevel.cpp
==================================================================
--- src/gtk/toplevel.cpp	(revision 1102)
+++ src/gtk/toplevel.cpp	(local)
@@ -68,6 +68,9 @@
 // send any activate events at all
 static int g_sendActivateEvent = -1;
 
+// Override for transparency
+wxCachedEnvironmentVariable wxTopLevelWindowGTK::s_TransparencyOverride(wxT("WX_TRANSPARENCY_OVERRIDE"));
+
 //-----------------------------------------------------------------------------
 // RequestUserAttention related functions
 //-----------------------------------------------------------------------------
@@ -1328,6 +1331,12 @@
     if (!m_widget || !m_widget->window)
         return false;
 
+    // We attempt to set transparency even if we don't know we can use
+    // it, as it should be harmless. However, don't do this if we have
+    // specifically been overriden from doing so
+    if (s_TransparencyOverride.IsPresent() && !s_TransparencyOverride.ToBool())
+        return false;
+
     Display* dpy = GDK_WINDOW_XDISPLAY (m_widget->window);
     // We need to get the X Window that has the root window as the immediate parent
     // and m_widget->window as a child. This should be the X Window that the WM manages and
@@ -1349,6 +1358,10 @@
 
 bool wxTopLevelWindowGTK::CanSetTransparent()
 {
+    // If an override is specified, return it
+    if (s_TransparencyOverride.IsPresent())
+        return s_TransparencyOverride.ToBool();
+
 #if GTK_CHECK_VERSION(2,10,0)
     if (!gtk_check_version(2,10,0))
     {

 	  	 
