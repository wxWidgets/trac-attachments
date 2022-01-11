---  wxWidgets/branches/WX_2_8_BRANCH/include/wx/xrc/xmlres.h (revision 55504)
+++ wxWidgets/branches/WX_2_8_BRANCH/include/wx/xrc/xmlres.h (working copy)
@@ -228,4 +228,6 @@
     static int GetXRCID(const wxChar *str_id, int value_if_not_found = wxID_NONE);
 
+    static wxChar *GetXRCID(int id);

     // Returns version information (a.b.c.d = d+ 256*c + 256^2*b + 256^3*a).
     long GetVersion() const { return m_version; }
