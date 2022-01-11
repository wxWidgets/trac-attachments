{\rtf1\ansi\ansicpg1252\cocoartf1038\cocoasubrtf360
{\fonttbl\f0\fnil\fcharset0 Menlo-Regular;}
{\colortbl;\red255\green255\blue255;\red63\green110\blue116;\red170\green13\blue145;\red92\green38\blue153;
\red46\green13\blue110;\red196\green26\blue22;\red28\green0\blue207;\red100\green56\blue32;}
\margl1440\margr1440\vieww17540\viewh11620\viewkind0
\deftab560
\pard\tx560\pardeftab560\ql\qnatural\pardirnatural

\f0\fs22 \cf0 \CocoaLigature0 	\cf2 m_panel\cf0  = \cf3 new\cf0  \cf4 wxWizardPageSimple\cf0 ( parent );\
	\cf4 wxTheColourDatabase\cf0 ->\cf5 AddColour\cf0 ( \cf6 "NAVY"\cf0 , \cf4 wxColour\cf0 ( \cf7 0\cf0 , \cf7 0\cf0 , \cf7 58\cf0  ) );\
	\cf2 m_label\cf0  = \cf3 new\cf0  \cf4 wxStaticText\cf0 ( \cf2 m_panel\cf0 , \cf5 wxID_ANY\cf0 , \cf6 "Select League"\cf0  );\
	\cf2 m_labelLogo\cf0  = \cf3 new\cf0  \cf4 wxStaticBitmap\cf0 ( \cf2 m_panel\cf0 , \cf5 wxID_ANY\cf0 , \cf8 wxBITMAP_PNG\cf0 ( \cf7 27330\cf0 AOP1 ) );\
	\cf2 m_label1\cf0  = \cf3 new\cf0  \cf4 wxStaticText\cf0 ( \cf2 m_panel\cf0 , \cf5 wxID_ANY\cf0 , \cf6 "Mode: Demo"\cf0  );\
	\cf2 m_label2\cf0  = \cf3 new\cf0  \cf4 wxStaticText\cf0 ( \cf2 m_panel\cf0 , \cf5 wxID_ANY\cf0 , \cf6 "Version: 1.0"\cf0  );\
	\cf2 m_url\cf0  = \cf3 new\cf0  \cf4 wxHyperlinkCtrl\cf0 ( \cf2 m_panel\cf0 , \cf5 wxID_ANY\cf0 , \cf6 "www.google.com"\cf0 , \cf6 "http://www.google.com"\cf0  );\
	\cf2 m_leagues\cf0  = \cf3 new\cf0  \cf4 wxListBox\cf0 ( \cf2 m_panel\cf0 , \cf5 wxID_ANY\cf0  );\
	\cf2 m_new\cf0  = \cf3 new\cf0  \cf4 wxButton\cf0 ( \cf2 m_panel\cf0 , \cf5 wxID_ANY\cf0 , \cf6 "Create New League"\cf0  );\
	\cf2 m_edit\cf0  = \cf3 new\cf0  \cf4 wxButton\cf0 ( \cf2 m_panel\cf0 , \cf5 wxID_ANY\cf0 , \cf6 "Edit Existing League"\cf0  );\
	\cf2 m_delete\cf0  = \cf3 new\cf0  \cf4 wxButton\cf0 ( \cf2 m_panel\cf0 , \cf5 wxID_ANY\cf0 , \cf6 "Delete League"\cf0  );\
	\cf4 wxFont\cf0  font = \cf2 m_label\cf0 ->\cf5 GetFont\cf0 ();\
	font.\cf5 SetWeight\cf0 ( \cf5 wxFONTWEIGHT_BOLD\cf0  );\
	font.\cf5 SetPointSize\cf0 ( \cf7 24\cf0  );\
	\cf2 m_label\cf0 ->\cf5 SetFont\cf0 ( font );\
	\cf4 wxSizer\cf0  *horz1 = \cf3 new\cf0  \cf4 wxBoxSizer\cf0 ( \cf5 wxHORIZONTAL\cf0  );\
	\cf4 wxSizer\cf0  *vert1 = \cf3 new\cf0  \cf4 wxBoxSizer\cf0 ( \cf5 wxVERTICAL\cf0  );\
	\cf4 wxSizer\cf0  *holder = \cf3 new\cf0  \cf4 wxFlexGridSizer\cf0 ( \cf7 3\cf0 , \cf7 2\cf0 , \cf7 5\cf0 , \cf7 5\cf0  );\
	\cf4 wxSizer\cf0  *logo = \cf3 new\cf0  \cf4 wxBoxSizer\cf0 ( \cf5 wxVERTICAL\cf0  );\
	\cf4 wxSizer\cf0  *buttons = \cf3 new\cf0  \cf4 wxBoxSizer\cf0 ( \cf5 wxVERTICAL\cf0  );\
	horz1->\cf5 Add\cf0 ( \cf7 5\cf0 , \cf7 5\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	vert1->\cf5 Add\cf0 ( \cf7 5\cf0 , \cf7 5\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	holder->\cf5 Add\cf0 ( \cf2 m_labelLogo\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	logo->\cf5 Add\cf0 ( \cf2 m_label1\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	logo->\cf5 Add\cf0 ( \cf7 5\cf0 , \cf7 5\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	logo->\cf5 Add\cf0 ( \cf2 m_label2\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	logo->\cf5 Add\cf0 ( \cf7 5\cf0 , \cf7 5\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	logo->\cf5 Add\cf0 ( \cf2 m_url\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	holder->\cf5 Add\cf0 ( logo, \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	holder->\cf5 Add\cf0 ( \cf2 m_label\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	holder->\cf5 Add\cf0 ( \cf7 5\cf0 , \cf7 5\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	holder->\cf5 Add\cf0 ( \cf2 m_leagues\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	buttons->\cf5 Add\cf0 ( \cf2 m_new\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	buttons->\cf5 Add\cf0 ( \cf7 5\cf0 , \cf7 5\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	buttons->\cf5 Add\cf0 ( \cf2 m_edit\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	buttons->\cf5 Add\cf0 ( \cf7 5\cf0 , \cf7 5\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	buttons->\cf5 Add\cf0 ( \cf2 m_delete\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	holder->\cf5 Add\cf0 ( buttons, \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	vert1->\cf5 Add\cf0 ( holder, \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	vert1->\cf5 Add\cf0 ( \cf7 5\cf0 , \cf7 5\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	horz1->\cf5 Add\cf0 ( vert1, \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	horz1->\cf5 Add\cf0 ( \cf7 5\cf0 , \cf7 5\cf0 , \cf7 0\cf0 , \cf5 wxEXPAND\cf0 , \cf7 0\cf0  );\
	\cf3 for\cf0 ( \cf4 std\cf0 ::\cf4 vector\cf0 <\cf4 std\cf0 ::\cf4 string\cf0 >::\cf4 iterator\cf0  it = leagues.\cf5 begin\cf0 (); it < leagues.\cf5 end\cf0 (); it++ )\
		\cf2 m_leagues\cf0 ->\cf5 Append\cf0 ( *it );\
	\cf2 m_panel\cf0 ->\cf5 SetSizerAndFit\cf0 ( horz1 );\
	\cf2 m_leagues\cf0 ->\cf5 SetFocus\cf0 ();\
	\cf2 m_leagues\cf0 ->\cf5 SetSelection\cf0 ( \cf7 0\cf0  );\
	\cf3 return\cf0  \cf2 m_panel\cf0 ;\
}