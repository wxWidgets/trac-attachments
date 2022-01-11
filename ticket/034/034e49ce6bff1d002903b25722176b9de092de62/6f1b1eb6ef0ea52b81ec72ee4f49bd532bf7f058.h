/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/wince/fontdlgce.h
// Purpose:     wxFontDialog class
// Author:      Vince Harron
// Modified by: 
// Created:     2007-27-03
// RCS-ID:      
// Copyright:   Copyright 2007 Vendant Software
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_WINCE_FONTDLG_H_
#define _WX_WINCE_FONTDLG_H_

#include <wx/dynarray.h>

class wxNativeFontSpec
{
public:
    ENUMLOGFONT m_enumLogFont;
    union
    {
        TEXTMETRIC    m_textMetric;
        NEWTEXTMETRIC m_newTextMetric;
    };
    ULONG   m_fontType;
};
WX_DECLARE_OBJARRAY(wxNativeFontSpec, wxNativeFontSpecList);

// ----------------------------------------------------------------------------
// wxFontDialog
// ----------------------------------------------------------------------------

#define ID_SCROLLEDWINDOW 10110
#define ID_FONT 10111
#define ID_SIZE 10113
#define ID_BOLD 10114
#define ID_ITALIC 10115
#define ID_CLEARTYPE 10116
#define ID_SAMPLE_CHOICE 10117

/*!
 * wxFontDialog class declaration
 */

class WXDLLEXPORT wxFontDialog : public wxFontDialogBase
{
public:
    wxFontDialog();
    wxFontDialog(wxWindow *parent);
    wxFontDialog(wxWindow *parent, const wxFontData& data);

    bool Create(wxWindow *parent);
    bool Create(wxWindow *parent, const wxFontData& data);

#if WXWIN_COMPATIBILITY_2_6
    // deprecated interface, don't use
    wxDEPRECATED( wxFontDialog(wxWindow *parent, const wxFontData *data) );
#endif // WXWIN_COMPATIBILITY_2_6

protected:
    DECLARE_DYNAMIC_CLASS_NO_COPY(wxFontDialog)
    DECLARE_EVENT_TABLE()

private:
    static int CALLBACK
    EnumFontFamiliesCallbackStatic(
	    const LOGFONT *pLogFont, 
	    const TEXTMETRIC *pTextMetric, 
	    ULONG FontType, 
	    LPARAM lParam
	    );

    int
    EnumFontFamiliesCallback(
	    const LOGFONT *pLogFont, 
	    const TEXTMETRIC *pTextMetric, 
	    ULONG FontType
	    );

    void Init();
    void CreateControls();
    void UpdateSample();
    void RefreshFontList();
    void SelectFaceByName( const wxString& faaceName );

    void OnActivate( wxActivateEvent& event );
    void OnFontChanged( wxCommandEvent& event );
    void OnSampleChoice( wxCommandEvent& event );

    wxScrolledWindow* m_scrolledWindow;
    wxChoice* m_fontFace;
    wxStaticText* m_outOfRange;
#ifdef FONTDLG_SIZE_COMBOBOX
    wxComboBox* m_fontSize;
#else
    wxTextCtrl* m_fontSize;
#endif
    wxCheckBox* m_fontBold;
    wxCheckBox* m_fontItalic;
    wxCheckBox* m_fontClearType;
    wxStaticText* m_fontSample;
    wxNativeFontSpecList m_systemFonts;
    wxString m_faceName; // selected face name
    bool m_ready; // set to true when initialization is complete
};

#if WXWIN_COMPATIBILITY_2_6
    // deprecated interface, don't use
inline wxFontDialog::wxFontDialog(wxWindow *parent, const wxFontData *data)
        : wxFontDialogBase(parent) { InitFontData(data); Create(parent); }
#endif // WXWIN_COMPATIBILITY_2_6

#endif
    // _WX_WINCE_FONTDLG_H_

 	  	 
