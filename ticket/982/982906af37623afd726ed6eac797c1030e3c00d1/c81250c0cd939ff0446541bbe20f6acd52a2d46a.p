=== src/aui/framemanager.cpp
==================================================================
--- src/aui/framemanager.cpp	(revision 244)
+++ src/aui/framemanager.cpp	(local)
@@ -61,6 +61,106 @@
 #endif
 
 
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
+        SetTransparency(0);
+    }
+
+    void SetTransparency(int amount)
+    {
+        if (m_CanSetShape)
+        {
+            int w=100; // some defaults
+            int h=100;
+            GetClientSize(&w, &h);
+            if ((amount != m_Amount) || (m_MaxWidth<w) | (m_MaxHeight<h))
+            {
+                // Make the region at least double the height and width so we don't have
+                // to rebuild if the size changes.
+                m_MaxWidth=w*2;
+                m_MaxHeight=h*2;
+                m_Amount = amount;
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
+    void OnWindowCreate(wxWindowCreateEvent& WXUNUSED(event)) {m_CanSetShape=true; SetTransparency(0);}
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
 // -- static utility functions --
 
 static wxBitmap wxPaneCreateStippleBitmap()
@@ -81,45 +181,57 @@
     dc.DrawRectangle(rect);
 }
 
-#ifdef __WXMSW__
-
 // on supported windows systems (Win2000 and greater), this function
 // will make a frame window transparent by a certain amount
 static void MakeWindowTransparent(wxWindow* wnd, int amount)
 {
-    // this API call is not in all SDKs, only the newer ones, so
-    // we will runtime bind this
-    typedef DWORD (WINAPI *PSETLAYEREDWINDOWATTR)(HWND, DWORD, BYTE, DWORD);
-    static PSETLAYEREDWINDOWATTR pSetLayeredWindowAttributes = NULL;
-    static HMODULE h = NULL;
-    HWND hwnd = (HWND)wnd->GetHWND();
-
-    if (!h)
-        h = LoadLibrary(_T("user32"));
-
-    if (!pSetLayeredWindowAttributes)
+    bool realtransparency = !(wnd && wnd->IsKindOf(CLASSINFO(wxPseudoTransparentFrame)));
+    if (realtransparency)
     {
-        pSetLayeredWindowAttributes =
-         (PSETLAYEREDWINDOWATTR)GetProcAddress(h,
+#ifdef __WXMSW__
+        // this API call is not in all SDKs, only the newer ones, so
+        // we will runtime bind this
+    
+        typedef DWORD (WINAPI *PSETLAYEREDWINDOWATTR)(HWND, DWORD, BYTE, DWORD);
+        static PSETLAYEREDWINDOWATTR pSetLayeredWindowAttributes = NULL;
+        static HMODULE h = NULL;
+        HWND hwnd = (HWND)wnd->GetHWND();
+    
+        if (!h)
+            h = LoadLibrary(_T("user32"));
+    
+        if (!pSetLayeredWindowAttributes)
+        {
+            pSetLayeredWindowAttributes =
+            (PSETLAYEREDWINDOWATTR)GetProcAddress(h,
 #ifdef __WXWINCE__
-                                                 wxT("SetLayeredWindowAttributes")
+                                                    wxT("SetLayeredWindowAttributes")
 #else
-                                                 "SetLayeredWindowAttributes"
+                                                    "SetLayeredWindowAttributes"
 #endif
-                                               );
+                                                );
+        }
+    
+        if (pSetLayeredWindowAttributes == NULL)
+            return;
+    
+        LONG exstyle = GetWindowLong(hwnd, GWL_EXSTYLE);
+        if (0 == (exstyle & 0x80000) /*WS_EX_LAYERED*/)
+            SetWindowLong(hwnd, GWL_EXSTYLE, exstyle | 0x80000 /*WS_EX_LAYERED*/);
+    
+        pSetLayeredWindowAttributes(hwnd, 0, (BYTE)amount, 2 /*LWA_ALPHA*/);
+#endif
     }
-
-    if (pSetLayeredWindowAttributes == NULL)
-        return;
-
-    LONG exstyle = GetWindowLong(hwnd, GWL_EXSTYLE);
-    if (0 == (exstyle & 0x80000) /*WS_EX_LAYERED*/)
-        SetWindowLong(hwnd, GWL_EXSTYLE, exstyle | 0x80000 /*WS_EX_LAYERED*/);
-
-    pSetLayeredWindowAttributes(hwnd, 0, (BYTE)amount, 2 /*LWA_ALPHA*/);
+    else
+    {
+        if (wnd)
+        {
+            ((wxPseudoTransparentFrame *)wnd)->SetTransparency(amount);
+            wnd->Refresh();
+        }
+    }
 }
 
-#endif
 
 
 // CopyDocksAndPanes() - this utility function creates copies of
@@ -2412,148 +2524,112 @@
 
 void wxFrameManager::OnHintFadeTimer(wxTimerEvent& WXUNUSED(event))
 {
-#ifdef __WXMSW__
-    if (!m_hint_wnd || m_hint_fadeamt >= 50)
+    bool realtransparency = !(m_hint_wnd && m_hint_wnd->IsKindOf(CLASSINFO(wxPseudoTransparentFrame)));
+    if (!m_hint_wnd || m_hint_fadeamt >= (realtransparency?50:128))
     {
         m_hint_fadetimer.Stop();
         return;
     }
-
+    
     m_hint_fadeamt += 5;
     MakeWindowTransparent(m_hint_wnd, m_hint_fadeamt);
-#endif
 }
 
 void wxFrameManager::ShowHint(const wxRect& rect)
 {
-#ifdef __WXMSW__
 
+    static bool realtransparency = false;
     // First, determine if the operating system can handle transparency.
     // Transparency is available on Win2000 and above
-
+#ifdef __WXMSW__
     static int os_type = -1;
     static int ver_major = -1;
 
     if (os_type == -1)
         os_type = ::wxGetOsVersion(&ver_major);
 
+    realtransparency = (m_flags & wxAUI_MGR_TRANSPARENT_HINT) && os_type == wxWINDOWS_NT && ver_major >= 5;
+#endif
+
     // If the transparent flag is set, and the OS supports it,
     // go ahead and use a transparent hint
 
-    if ((m_flags & wxAUI_MGR_TRANSPARENT_HINT) != 0 &&
-        os_type == wxWINDOWS_NT && ver_major >= 5)
+    if (m_last_hint == rect)
+        return;
+    m_last_hint = rect;
+
+    int initial_fade = realtransparency?50:128;
+    if (m_flags & wxAUI_MGR_TRANSPARENT_HINT_FADE)
+        initial_fade = 0;
+
+
+    if (m_hint_wnd == NULL)
     {
-        if (m_last_hint == rect)
-            return;
-        m_last_hint = rect;
+        wxPoint pt = rect.GetPosition();
+        wxSize size = rect.GetSize();
 
-        int initial_fade = 50;
-        if (m_flags & wxAUI_MGR_TRANSPARENT_HINT_FADE)
-            initial_fade = 0;
-
-        if (m_hint_wnd == NULL)
+        if (realtransparency)
         {
-            wxPoint pt = rect.GetPosition();
-            wxSize size = rect.GetSize();
+#ifdef __WXMSW__
             m_hint_wnd = new wxFrame(m_frame, -1, wxEmptyString, pt, size,
-                                     wxFRAME_TOOL_WINDOW |
-                                     wxFRAME_FLOAT_ON_PARENT |
-                                     wxFRAME_NO_TASKBAR |
-                                     wxNO_BORDER);
-
-            MakeWindowTransparent(m_hint_wnd, initial_fade);
+                                        wxFRAME_TOOL_WINDOW |
+                                        wxFRAME_FLOAT_ON_PARENT |
+                                        wxFRAME_NO_TASKBAR |
+                                        wxNO_BORDER);
             m_hint_wnd->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
-            m_hint_wnd->Show();
-
-            // if we are dragging a floating pane, set the focus
-            // back to that floating pane (otherwise it becomes unfocused)
-            if (m_action == actionDragFloatingPane && m_action_window)
-                m_action_window->SetFocus();
-
+#endif
         }
-         else
+        else
         {
-            MakeWindowTransparent(m_hint_wnd, initial_fade);
-            m_hint_wnd->SetSize(rect);
+            m_hint_wnd = new wxPseudoTransparentFrame (m_frame, -1, wxEmptyString, pt, size,
+                                        wxFRAME_TOOL_WINDOW |
+                                        wxFRAME_FLOAT_ON_PARENT |
+                                        wxFRAME_NO_TASKBAR |
+                                        wxNO_BORDER);
         }
 
-        if (m_flags & wxAUI_MGR_TRANSPARENT_HINT_FADE)
-        {
-            // start fade in timer
-            m_hint_fadeamt = 0;
-            m_hint_fadetimer.SetOwner(this, 101);
-            m_hint_fadetimer.Start(5);
-        }
+        MakeWindowTransparent(m_hint_wnd, initial_fade);
+        m_hint_wnd->Show();
 
-        return;
+        // if we are dragging a floating pane, set the focus
+        // back to that floating pane (otherwise it becomes unfocused)
+        if (m_action == actionDragFloatingPane && m_action_window)
+            m_action_window->SetFocus();
+
     }
-#endif
-
-    if (m_last_hint != rect)
+    else
     {
-        // remove the last hint rectangle
-        m_last_hint = rect;
-        m_frame->Refresh();
-        m_frame->Update();
+        MakeWindowTransparent(m_hint_wnd, initial_fade);
+        m_hint_wnd->SetSize(rect);
     }
 
-    wxScreenDC screendc;
-    wxRegion clip(1, 1, 10000, 10000);
-
-    // clip all floating windows, so we don't draw over them
-    int i, pane_count;
-    for (i = 0, pane_count = m_panes.GetCount(); i < pane_count; ++i)
+    if (m_flags & wxAUI_MGR_TRANSPARENT_HINT_FADE)
     {
-        wxPaneInfo& pane = m_panes.Item(i);
-
-        if (pane.IsFloating() &&
-            pane.frame->IsShown())
-        {
-            wxRect rect = pane.frame->GetRect();
-            #ifdef __WXGTK__
-            // wxGTK returns the client size, not the whole frame size
-            rect.width += 15;
-            rect.height += 35;
-            rect.Inflate(5);
-            #endif
-
-            clip.Subtract(rect);
-        }
+        // start fade in timer
+        m_hint_fadeamt = 0;
+        m_hint_fadetimer.SetOwner(this, 101);
+        m_hint_fadetimer.Start(5);
     }
 
-    screendc.SetClippingRegion(clip);
-
-    wxBitmap stipple = wxPaneCreateStippleBitmap();
-    wxBrush brush(stipple);
-    screendc.SetBrush(brush);
-    screendc.SetPen(*wxTRANSPARENT_PEN);
-
-    screendc.DrawRectangle(rect.x, rect.y, 5, rect.height);
-    screendc.DrawRectangle(rect.x+5, rect.y, rect.width-10, 5);
-    screendc.DrawRectangle(rect.x+rect.width-5, rect.y, 5, rect.height);
-    screendc.DrawRectangle(rect.x+5, rect.y+rect.height-5, rect.width-10, 5);
+    return;
 }
 
 void wxFrameManager::HideHint()
 {
     // hides a transparent window hint (currently wxMSW only)
-#ifdef __WXMSW__
     if (m_hint_wnd)
     {
         MakeWindowTransparent(m_hint_wnd, 0);
         m_hint_fadetimer.Stop();
         m_last_hint = wxRect();
+        m_hint_wnd->Hide();
+
+        // We don't need to destroy the hint window here, as it gets reused, but let's try.
+        m_hint_wnd->Destroy();
+        m_hint_wnd=NULL;
+
         return;
     }
-#endif
-
-    // hides a painted hint by redrawing the frame window
-    if (!m_last_hint.IsEmpty())
-    {
-        m_frame->Refresh();
-        m_frame->Update();
-        m_last_hint = wxRect();
-    }
 }
 
 

 	  	 
