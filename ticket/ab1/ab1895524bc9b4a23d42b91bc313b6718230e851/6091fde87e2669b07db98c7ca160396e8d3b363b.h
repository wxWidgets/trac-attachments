/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/statusbar.h
// Purpose:     wxStatusBar definition for wxGTK
// Author:      Igor Korot
// Id:          
// Copyright:   (c) 1998 Robert Roebling, Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_GTK_STATUSBAR_H_
#define _WX_GTK_STATUSBAR_H_

#include "wx/vector.h"

//-----------------------------------------------------------------------------
// classes
//-----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxStatusBar : public wxStatusBarBase
{
public:
    wxStatusBar();
    wxStatusBar(wxWindow *parent, wxWindowID id = wxID_ANY, long style = wxSTB_DEFAULT_STYLE,
                const wxString &name = wxStatusBarNameStr);
    virtual ~wxStatusBar();
    bool Create(wxWindow *parent, wxWindowID id = wxID_ANY, long style = wxSTB_DEFAULT_STYLE,
                const wxString &name = wxStatusBarNameStr);

/*    int GetFieldsCount() const;
    const wxStatusBarPane& GetField(int n) const;
    wxSize GetBorders() const;
    const wxArrayString& GetStatusStack(int n) const;
    int GetStatusWidth(int n) const;
    int GetStatusStyle(int n) const;
*/    void PopStatusText(int field = 0);
    int GetFieldsCount() const;
    void PushStatusText(const wxString& string, int field = 0);

    virtual void SetFieldsCount(int number = 1, const int* widths = NULL);
/*    virtual wxString GetStatusText(int i = 0) const;
    virtual void SetStatusStyles(int n, const int* styles);
    virtual void SetStatusText(const wxString& text, int i = 0);
*/    virtual void SetStatusWidths(int n, const int* widths_field);
    virtual bool GetFieldRect(int i, wxRect& rect) const;
    virtual void SetMinHeight(int height);
    virtual int GetBorderX() const;
    virtual int GetBorderY() const;

protected:
    void SetFieldsWidth();

private:
    GtkStatusbar* m_statusbar;
    int m_count;
    wxVector<int> m_uid;
    DECLARE_DYNAMIC_CLASS_NO_COPY(wxStatusBar)
};

#endif  // _WX_GTK_STATUSBAR_H_
