/////////////////////////////////////////////////////////////////////////////
// Name:        fontdlgce.cpp
// Purpose:     wxFontDialog class
// Author:      Vince Harron
// Modified by: 
// Created:     2007-27-03
// RCS-ID:      
// Copyright:   Copyright 2007 Vendant Software
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_FONTDLG

#include "wx/fontdlg.h"
#include "wx/fontutil.h"

#ifndef WX_PRECOMP
    #include "wx/choice.h"
    #include "wx/combobox.h"
    #include "wx/stattext.h"
#endif

#include <stdlib.h>

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(wxNativeFontSpecList);

static wxString GetCharSetName( int charSet );
static wxString GetCharSetSample( int charSet );

/*!
 * wxFontDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( wxFontDialog, wxFontDialogBase )

/*!
 * wxFontDialog event table definition
 */

BEGIN_EVENT_TABLE( wxFontDialog, wxFontDialogBase )
    EVT_ACTIVATE( wxFontDialog::OnActivate )
    EVT_CHOICE( ID_FONT, wxFontDialog::OnFontChanged )
    EVT_COMBOBOX( ID_SIZE, wxFontDialog::OnFontChanged )
    EVT_TEXT( ID_SIZE, wxFontDialog::OnFontChanged )
    EVT_CHECKBOX( ID_BOLD, wxFontDialog::OnFontChanged )
    EVT_CHECKBOX( ID_ITALIC, wxFontDialog::OnFontChanged )
    EVT_CHECKBOX( ID_CLEARTYPE, wxFontDialog::OnFontChanged )
    EVT_CHOICE( ID_SAMPLE_CHOICE, wxFontDialog::OnSampleChoice )
END_EVENT_TABLE()

/*!
 * wxFontDialog constructors
 */

wxFontDialog::wxFontDialog()
{
    Init();
}

wxFontDialog::wxFontDialog(wxWindow* parent)
{
    Init();
    Create(parent);
}

wxFontDialog::wxFontDialog(wxWindow* parent, const wxFontData& data)
{
    Init();
    Create(parent, data);
}

/*!
 * wxFontDialog creators
 */

bool wxFontDialog::Create(wxWindow *parent)
{
    wxFontData fontData;
    return Create(parent, fontData);
}

bool wxFontDialog::Create( wxWindow* parent, const wxFontData& data)
{
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);

    if ( !wxDialog::Create( parent , wxID_ANY , _T("Choose Font") , wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE,
        _T("fontdialog") ) )
    {
        wxFAIL_MSG( wxT("wxFontDialog creation failed") );
        return false;
    }

    m_fontData = data;

    CreateControls();

    RefreshFontList();

    wxFont initialFont = m_fontData.GetInitialFont();
    if ( initialFont.IsOk() )
    {
        SelectFaceByName( initialFont.GetFaceName() );
        m_fontSize->SetValue( wxString::Format(wxT("%i"),initialFont.GetPointSize()) );
        m_fontBold->SetValue( initialFont.GetWeight()==wxFONTWEIGHT_BOLD );
        m_fontItalic->SetValue( initialFont.GetStyle()==wxFONTSTYLE_ITALIC );

        bool clearType = true;
        const wxNativeFontInfo* nfi = initialFont.GetNativeFontInfo();
        if ( nfi )
        {
            clearType = nfi->lf.lfQuality == CLEARTYPE_QUALITY;
        }
        m_fontClearType->SetValue(clearType);
    }
    else
    {
        m_fontFace->SetSelection(0);
    }

    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
    return true;
}

void wxFontDialog::CreateControls()
{
    wxFontDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    m_scrolledWindow = new wxScrolledWindow( itemDialog1, ID_SCROLLEDWINDOW, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
    itemBoxSizer2->Add(m_scrolledWindow, 1, wxGROW, 5);
    m_scrolledWindow->SetScrollbars(1, 1, 0, 0);
    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    m_scrolledWindow->SetSizer(itemBoxSizer4);

    wxStaticText* itemStaticText5 = new wxStaticText( m_scrolledWindow, wxID_STATIC, _("Font:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemStaticText5, 0, wxALIGN_LEFT|wxALL|wxADJUST_MINSIZE, 1);

    wxString* itemChoice6Strings = NULL;
    m_fontFace = new wxChoice( m_scrolledWindow, ID_FONT, wxDefaultPosition, wxDefaultSize, 0, itemChoice6Strings, 0 );
    itemBoxSizer4->Add(m_fontFace, 0, wxGROW|wxALL, 1);

    wxStaticText* itemStaticText7 = new wxStaticText( m_scrolledWindow, wxID_STATIC, _("Size:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemStaticText7, 0, wxALIGN_LEFT|wxALL|wxADJUST_MINSIZE, 1);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer4->Add(itemBoxSizer3, 0, wxALIGN_LEFT|wxALL|wxADJUST_MINSIZE, 1);

#ifdef FONTDLG_SIZE_COMBOBOX
    // when the combo box is used, delete all of the text from it and try to type "11"
    // After the first "1" the field it filled with "10" and the second "1" leaves you
    // with "110" very frustrating, maybe someone else knows how to fix this
    wxString sizeStrings[] = {
        wxT("8"),
        wxT("10"),
        wxT("12"),
        wxT("16"),
        wxT("20"),
        wxT("24")
    };
    m_fontSize = new wxComboBox( m_scrolledWindow, ID_SIZE, wxT("8"), wxDefaultPosition, wxSize(80, -1), WXSIZEOF(sizeStrings), sizeStrings, wxCB_DROPDOWN );
    m_fontSize->SetStringSelection(_("9"));
#else
    m_fontSize = new wxTextCtrl( m_scrolledWindow, ID_SIZE, wxT("8"), wxDefaultPosition, wxSize(50, -1) );
    m_fontSize->SetValue(wxT("9"));
#endif
    itemBoxSizer3->Add(m_fontSize, 0, wxALIGN_TOP|wxALL, 1);

    m_outOfRange = new wxStaticText( m_scrolledWindow, wxID_ANY, _("(out of range)") );
    itemBoxSizer3->Add(m_outOfRange, 0, wxALIGN_TOP|wxALL, 1);

    m_fontBold = new wxCheckBox( m_scrolledWindow, ID_BOLD, _("Bold"), wxDefaultPosition, wxDefaultSize, 0 );
    m_fontBold->SetValue(false);
    itemBoxSizer4->Add(m_fontBold, 0, wxALIGN_LEFT|wxALL, 1);

    m_fontItalic = new wxCheckBox( m_scrolledWindow, ID_ITALIC, _("Italic"), wxDefaultPosition, wxDefaultSize, 0 );
    m_fontItalic->SetValue(false);
    itemBoxSizer4->Add(m_fontItalic, 0, wxALIGN_LEFT|wxALL, 1);

    m_fontClearType = new wxCheckBox( m_scrolledWindow, ID_CLEARTYPE, _("ClearType"), wxDefaultPosition, wxDefaultSize, 0 );
    m_fontClearType->SetValue(false);
    itemBoxSizer4->Add(m_fontClearType, 0, wxALIGN_LEFT|wxALL, 1);

    wxStaticText* itemStaticText11 = new wxStaticText( m_scrolledWindow, wxID_STATIC, _("Sample:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemStaticText11, 0, wxALIGN_LEFT|wxALL|wxADJUST_MINSIZE, 1);

    static const wxString scriptNames[] =
    {
        // WARNING: every change in this array must be mirrored in scriptSamples array
        _("Arabic"),             
        _("Central Europe"),     
        _("Cyrillic"),           
        _("Greek"),              
        _("Hebrew"),             
        _("Japanese"),           
        _("Korean"),             
        _("Simplified Chinese"), 
        _("Traditional Chinese"),
        _("Turkish"),            
        _("Vietnamese"),         
        _("Western European"),   
    };
    wxChoice* sampleChoice = new wxChoice( m_scrolledWindow, ID_SAMPLE_CHOICE, wxDefaultPosition, wxDefaultSize, WXSIZEOF(scriptNames), scriptNames, 0 );
    itemBoxSizer4->Add(sampleChoice, 0, wxGROW|wxALL, 1);

    // TODO: default to sample appropriate for Pocket PC default language
    sampleChoice->SetSelection(WXSIZEOF(scriptNames)-1); // use Western European

    m_fontSample = new wxStaticText( m_scrolledWindow, wxID_STATIC, _("AaBbYyZz"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(m_fontSample, 0, wxGROW|wxALL, 1);

    m_scrolledWindow->FitInside();

    m_ready = true;
}

/*!
 * Member initialisation 
 */

void wxFontDialog::Init()
{
    m_scrolledWindow = NULL;
    m_fontFace = NULL;
    m_fontSize = NULL;
    m_fontBold = NULL;
    m_fontItalic = NULL;
    m_fontClearType = NULL;
    m_fontSample = NULL;
    m_ready = false;
}

/* static */
int CALLBACK
wxFontDialog::EnumFontFamiliesCallbackStatic(
	const LOGFONT *pLogFont, 
	const TEXTMETRIC *pTextMetric, 
	ULONG FontType, 
	LPARAM lParam
	)
{
    wxFontDialog* fontDialog = (wxFontDialog*)lParam;
    return fontDialog->EnumFontFamiliesCallback( pLogFont, pTextMetric, FontType );
}

int
wxFontDialog::EnumFontFamiliesCallback(
	const LOGFONT *pLogFont, 
	const TEXTMETRIC *pTextMetric, 
	ULONG FontType
	)
{
    if ( pLogFont->lfCharSet == SYMBOL_CHARSET && !m_fontData.GetAllowSymbols() )
    {
        // skip this font
        return 1;
    }

    wxNativeFontSpec spec;
    memcpy( &spec.m_enumLogFont, pLogFont, sizeof(ENUMLOGFONT) );
    if ( FontType == TRUETYPE_FONTTYPE )
    {
        memcpy( &spec.m_newTextMetric, pTextMetric, sizeof(NEWTEXTMETRIC) );
    }
    else
    {
        memcpy( &spec.m_textMetric, pTextMetric, sizeof(TEXTMETRIC) );
    }
    spec.m_fontType = FontType;

    size_t index = m_systemFonts.Count();

    m_systemFonts.Add( spec );

    wxString charSetName = GetCharSetName( spec.m_enumLogFont.elfLogFont.lfCharSet );

    wxString comboItemString;
    if ( charSetName.empty() )
    {
        comboItemString = spec.m_enumLogFont.elfLogFont.lfFaceName;
    }
    else
    {
        comboItemString = wxString::Format( wxT("%s (%s)"), 
            spec.m_enumLogFont.elfLogFont.lfFaceName, 
            charSetName.c_str()
            );
    }
    m_fontFace->Append( comboItemString, (void*)index );

	return 1;
}

void wxFontDialog::OnActivate( wxActivateEvent& event )
{
    if ( !event.GetActive() )
    {
        return;
    }

    int selectedFace = m_fontFace->GetSelection();
    wxString faceName = m_systemFonts[selectedFace].m_enumLogFont.elfLogFont.lfFaceName;

    RefreshFontList();

    SelectFaceByName( faceName );

    UpdateSample();
}

void wxFontDialog::RefreshFontList()
{
    m_fontFace->Clear();
    m_systemFonts.Empty();
	EnumFontFamilies( ScreenHDC(), 0, &EnumFontFamiliesCallbackStatic, (LPARAM)this );
}

void wxFontDialog::OnFontChanged( wxCommandEvent& WXUNUSED(event) )
{
    UpdateSample();
}

void wxFontDialog::SelectFaceByName( const wxString& faceName )
{
    // make sure the same face is selected after the refresh
    // default to index 0 if the font is not found
    size_t selectedFace = 0;
    for ( size_t i = 0; i < m_systemFonts.Count(); i++ )
    {
        wxNativeFontSpec& spec = m_systemFonts[i];
        if ( 0 == faceName.Cmp( spec.m_enumLogFont.elfLogFont.lfFaceName ) )
        {
            // found the face we were looking for
            selectedFace = i;
            break;
        }
    }
    m_fontFace->SetSelection(selectedFace);
}

void wxFontDialog::UpdateSample()
{
    if ( !m_ready )
    {
        return;
    }
    int selectedFace = m_fontFace->GetSelection();
    wxNativeFontSpec& spec = m_systemFonts[selectedFace];

    wxNativeFontInfo info;
    memcpy( &info.lf, &spec.m_enumLogFont.elfLogFont, sizeof(LOGFONT) );

    int PointSize = wxAtoi(m_fontSize->GetValue().c_str());
    if ( PointSize < 6 || PointSize > 99 )
    {
        PointSize = 9;
        m_outOfRange->Show();
    }
    else
    {
        m_outOfRange->Hide();
    }

    const int pixelsPerInch = ::GetDeviceCaps(ScreenHDC(), LOGPIXELSY);
    // 72 points per inch
    info.lf.lfHeight = -PointSize*pixelsPerInch/72;
    info.lf.lfWidth = 0;
    info.lf.lfItalic = m_fontItalic->GetValue()?1:0;
    info.lf.lfWeight = m_fontBold->GetValue()?FW_BOLD:FW_NORMAL;

    // we get better font quality if we use this instead of 
    // DEFAULT_QUALITY apparently without any drawbacks 
    info.lf.lfQuality = m_fontClearType->GetValue()?CLEARTYPE_QUALITY:DEFAULT_QUALITY;

    // if the quality (ClearType) value changes, SetFont is ignored
    // changing the width value forces the font to change
    {
        info.lf.lfWidth = 1;
        wxFont font(info);
        m_fontSample->SetFont(font);
        info.lf.lfWidth = 0;
    }
    wxFont font(info);

    m_fontData.SetChosenFont(font);

    m_fontSample->SetFont(font);
    m_scrolledWindow->FitInside();
}

static wxString GetCharSetName( int charSet )
{
    class CharSetName
    {
    public:
        int      m_charSet;
        wxString m_charSetName;
    };
    static const CharSetName charSetName[] = 
    {
        { SHIFTJIS_CHARSET,    _("Japanese") }, 
        { HANGEUL_CHARSET,     _("Korean Hangul") }, 
        { GB2312_CHARSET,      _("Simplified Chinese") }, 
        { CHINESEBIG5_CHARSET, _("Traditional Chinese") }, 
        { JOHAB_CHARSET,       _("Korean Johab") }, 
        { HEBREW_CHARSET,      _("Hebrew") }, 
        { ARABIC_CHARSET,      _("Arabic") },
        { GREEK_CHARSET,       _("Greek") }, 
        { TURKISH_CHARSET,     _("Turkish") },
        { VIETNAMESE_CHARSET,  _("Vietnamese") },
        { THAI_CHARSET,        _("Thai") },
        { EASTEUROPE_CHARSET,  _("Eastern Europe") },
        { RUSSIAN_CHARSET,     _("Russian") },
        { MAC_CHARSET,         _("Macintosh") },
        { BALTIC_CHARSET,      _("Baltic") },
    };

    for ( size_t i = 0; i < WXSIZEOF(charSetName); i++ )
    {
        if ( charSetName[i].m_charSet == charSet )
        {
            // found it
            return charSetName[i].m_charSetName;
        }
    }
    return wxEmptyString;
}

void wxFontDialog::OnSampleChoice( wxCommandEvent& event )
{
    static const wxString scriptSamples[] =
    {
        // WARNING: every change in this array must be mirrored in scriptNames array
        /*Arabic*/               wxT("AbBb\x627\x628\x62c\x62f\x647\x648\x632"),
        /*Central Europe*/       wxT("AbBb\xc1\xe1\xd4\xf4"),
        /*Cyrillic*/             wxT("AbBb\x411\x431\424\444"),
        /*Greek*/                wxT("AbBb\x391\x3b1\x392\x3b2"),
        /*Hebrew*/               wxT("AbBb\x5ea\x5e9\x5e1\x5e0"),
        /*Japanese*/             wxT("AbBb\x3042\x30a2\x96ea\x5973"), // hiragana A, katakana A, yuki(snow), onna(woman), maybe a native speaker knows better characters
        /*Korean*/               wxT("AbBb\xad83\xaf7e"), // these characters chosen at random, maybe a native speaker knows better characters
        /*Simplified Chinese*/   wxT("AbBb\x4ecf\x4eb9"), // these characters chosen at random, maybe a native speaker knows better characters
        /*Traditional Chinese*/  wxT("AbBb\x775b\x745e"), // these characters chosen at random, maybe a native speaker knows better characters
        /*Turkish*/              wxT("AbBb\x11e\x11f\x15e\x15f"),
        /*Vietnamese*/           wxT("AbBb\x1a0\x1a1\x1af\x1b0"),
        /*Western European*/     wxT("AbBbYyZz"),
    };

    m_fontSample->SetLabel( scriptSamples[event.GetSelection()] );
    m_scrolledWindow->FitInside();
}

#endif // wxUSE_FONTDLG

 	  	 
