//////////////////////////////////////////////////////////////////////////////
// File:        LexLambdaCalc.cpp
// Purpose:     External lambda calculus lexer for wxStyledTextCtrl
// Author:      New Pagodi
// Created:     2016-04-05
// Copyright:   (c) wxGuide
// Licence:     wxWindows licence
//////////////////////////////////////////////////////////////////////////////


// The following definitins give the call type and export directive used for
// the factory functions.  For a regular scintilla external lexer, these
// functions would be defined to use the stdcall calling convention on windows.
// However for use with wxStyledTextCtrl we must NOT do this.
#ifdef _WIN32
#define EXT_LEXER_DECL __declspec( dllexport )
#else
#define EXT_LEXER_DECL
#endif

#include <string.h>
#include <assert.h>

#include <ILexer.h>
#include <Scintilla.h>
#include <LexAccessor.h>
#include <Accessor.h>
#include <StyleContext.h>
#include <LexerModule.h>
#include <PropSetSimple.h>
#include <LexerBase.h>

#ifdef SCI_NAMESPACE
using namespace Scintilla;
#endif

///////////////////////////////////////////////
// To build an external lexer, at a minimum we need to
// 1) derive a class from LexerBase and implement at least the 2 pure virtual
//    methods: LexerBase::Lex and LexerBase::Fold.  Care should be taken to
//    ensure that no exceptions are thrown out of these methods.
// 2) add a factory function and two helper functions needed to pull lexer
//    objects out of the library: GetLexerCount, GetLexerName, GetLexerFactory.
// This example also impliments 1 additional method, LexerBase::PrivateCall,
// to demonstrate how a lexer can interact with a wxSTC.

/////////////////////////////////////////////
// Part1: Impliment the lexer

#define SCE_LC_DEFAULT  0
#define SCE_LC_ERROR    1
#define SCE_LC_LAMBDA   2
#define SCE_LC_DOT      3
#define SCE_LC_PAREN    4
#define SCE_LC_OPERATOR 5
#define SCE_LC_VARIABLE 6
#define SCE_LC_NUMBER   7

static inline bool IsAVar(int ch) {
    return 96<ch && ch<123;
}

class LexerLambdaCalculus : public LexerBase {
public:
    LexerLambdaCalculus():drctPtr(NULL),drctFncn(NULL),font(NULL) {}
    ~LexerLambdaCalculus() {if (font!=NULL) delete[] font;}
    void SCI_METHOD Lex(unsigned int, int, int, IDocument *);
    void SCI_METHOD Fold(unsigned int, int, int, IDocument *);
    void * SCI_METHOD PrivateCall(int operation, void *pointer);

    static ILexer *LexerFactoryLambdaCalculus() {
        try {
            return new LexerLambdaCalculus();
        } catch (...) {
            // Should not throw into caller
            return 0;
        }
    }
private:
    void* drctPtr;
    void* drctFncn;
    char* font;
};

void SCI_METHOD LexerLambdaCalculus::Lex(unsigned int startPos, int length,
                                         int initStyle, IDocument *pAccess) {
    try {
        // We'll simply run through the characters 1 by 1 and assign the state
        // based on the the character's type.

        Accessor styler(pAccess, &props);
        styler.StartAt(startPos);

        StyleContext sc(startPos, length, initStyle, styler);

        for (; sc.More(); sc.Forward()) {
            if (sc.ch == 0x03BB)
                sc.SetState(SCE_LC_LAMBDA);
            else if (sc.ch == ')' || sc.ch == '(')
                sc.SetState(SCE_LC_PAREN);
            else if (sc.ch == '.')
                sc.SetState(SCE_LC_DOT);
            else if (sc.ch == '+' || sc.ch == '-' || sc.ch == '*'
                     || sc.ch == '/' )
                sc.SetState(SCE_LC_OPERATOR);
            else if (IsAVar(sc.ch) && !IsAVar(sc.chPrev) )
                sc.SetState(SCE_LC_VARIABLE);
            else if (sc.ch == ' ' || sc.ch == '\r' || sc.ch == '\n')
                sc.SetState(SCE_LC_DEFAULT);
            else if (47<sc.ch && sc.ch<58 )
                sc.SetState(SCE_LC_NUMBER);
            else
                sc.SetState(SCE_LC_ERROR);
        }
        sc.Complete();
        styler.Flush();

    } catch (...) {
        // Should not throw into caller
        pAccess->SetErrorStatus(SC_STATUS_FAILURE);
    }
}

void SCI_METHOD LexerLambdaCalculus::Fold(unsigned int startPos, int length,
                                          int, IDocument *pAccess) {
    // The fold tracking for this lexer does 3 things
    // 1) Set fold level for non whitespace lines to the indentation level.
    // 2) Set fold level for whitespace lines to the default level
    // 3) Set header flag whenever the fold level increases.

    // this implimentation is heavily based on and is basically a low power
    // version of the fold function from the python lexer.

    try {
        Accessor styler(pAccess, &props);

        // Gather initial info
        const int maxPos = startPos + length;
        const int maxLines = (maxPos == styler.Length())
        ? styler.GetLine(maxPos): styler.GetLine(maxPos - 1); // Requested last
        const int docLines = styler.GetLine(styler.Length()); // Available last

        // Get the current line and then backup 1 line (if not at the start)
        // because the lexer may need to set the header flag of previous when
        // indentation changes on the current line.
        int lineCurrent = styler.GetLine(startPos);
        if (lineCurrent > 0) lineCurrent--;

        // other variables needed for the loop
        int spaceFlags(0), lev(0), lineNext(0), indentNext(0);
        int indentCurrent = styler.IndentAmount(lineCurrent, &spaceFlags, NULL);

        // Process all lines to end of requested range.
        while ((lineCurrent <= docLines) && (lineCurrent <= maxLines)) {
            // Gather info
            lev = indentCurrent;
            lineNext = lineCurrent + 1;
            indentNext = indentCurrent;
            if (lineNext <= docLines)
                indentNext = styler.IndentAmount(lineNext, &spaceFlags, NULL);

            // set whitespace lines to default and set header flag if needed
            if (indentCurrent & SC_FOLDLEVELWHITEFLAG) {
                lev = SC_FOLDLEVELBASE;
            } else {
                if ((indentCurrent & SC_FOLDLEVELNUMBERMASK)
                    < (indentNext & SC_FOLDLEVELNUMBERMASK))
                    lev |= SC_FOLDLEVELHEADERFLAG;
            }

            // Set fold level for this line and move to next line
            styler.SetLevel(lineCurrent, lev);
            indentCurrent = indentNext;
            lineCurrent = lineNext;
        }

        styler.Flush();
    } catch (...) {
        // Should not throw into caller
        pAccess->SetErrorStatus(SC_STATUS_FAILURE);
    }
}

void* SCI_METHOD LexerLambdaCalculus::PrivateCall(int operation, void *pointer){
    // When operation is 1, it will collect the directpointer pointer.
    // When operation is 2, it will collect the directfunction pointer.
    // When operation is 3, it will collect a font name.
    // When operation is 4, if all the pointers are valid, it will
    //   reconstruct the send message function, and use it to configure
    //   the styled text control.

    try {
        if (operation == 1) {
            drctPtr=pointer;
        }
        else if (operation == 2) {
            drctFncn=pointer;
        }
        else if (operation == 3) {
            char* s = reinterpret_cast<char *>(pointer);
            int i = strlen(s);
            if ( i != 0){
                font=new char[i+1];
                strcpy(font, s);
            }
        }
        else if (operation == 4) {
            if (drctPtr!=NULL && drctFncn!=NULL && font!=NULL) {
                // if all the pointers are valid, build the send message
                // function and use it to configure the styled text control.

                int (* SendMsg)(void*, int, uptr_t, sptr_t)
                =reinterpret_cast<int (*)(void*, int, uptr_t,sptr_t)>(drctFncn);

                // have the styled text only show the horizontal scroll bar
                // when it is needed
                SendMsg(drctPtr, SCI_SETSCROLLWIDTH, 1, 0);
                SendMsg(drctPtr, SCI_SETSCROLLWIDTHTRACKING, 1, 0);

                // set the caret color and add extra pixel to the top
                // and bottom of each line
                SendMsg(drctPtr, SCI_SETCARETFORE, 0xCEF8CD, 0);
                SendMsg(drctPtr, SCI_SETEXTRAASCENT, 1, 0);
                SendMsg(drctPtr, SCI_SETEXTRADESCENT, 1, 0);

                //set the default style to have a charcoal background,
                //a white foreground, and set it to use a fixed width font.
                //then call SCI_STYLECLEARALL to push those values to all
                //other styles.
                SendMsg(drctPtr, SCI_STYLESETFONT, STYLE_DEFAULT,
                        reinterpret_cast<sptr_t>(font));
                SendMsg(drctPtr, SCI_STYLESETSIZE, STYLE_DEFAULT, 10);
                SendMsg(drctPtr, SCI_STYLESETFORE, STYLE_DEFAULT, 0xFFFFFF);
                SendMsg(drctPtr, SCI_STYLESETBACK, STYLE_DEFAULT, 0x393939);
                SendMsg(drctPtr, SCI_STYLECLEARALL, 0, 0);

                //set the colors and other font properties for the various
                //lexer states
                SendMsg(drctPtr, SCI_STYLESETFORE, SCE_LC_DEFAULT, 0xFFFFFF);
                SendMsg(drctPtr, SCI_STYLESETFORE, SCE_LC_ERROR, 0x000000);
                SendMsg(drctPtr, SCI_STYLESETBACK, SCE_LC_ERROR, 0x0000FF);
                SendMsg(drctPtr, SCI_STYLESETFORE, SCE_LC_LAMBDA, 0x4198EA);
                SendMsg(drctPtr, SCI_STYLESETBOLD, SCE_LC_LAMBDA, 1);
                SendMsg(drctPtr, SCI_STYLESETFORE, SCE_LC_DOT, 0xBD8FB0);
                SendMsg(drctPtr, SCI_STYLESETBOLD, SCE_LC_DOT, 1);
                SendMsg(drctPtr, SCI_STYLESETFORE, SCE_LC_PAREN, 0xBD8FB0);
                SendMsg(drctPtr, SCI_STYLESETBOLD, SCE_LC_PAREN, 1);
                SendMsg(drctPtr, SCI_STYLESETFORE, SCE_LC_OPERATOR, 0xEFB29D);
                SendMsg(drctPtr, SCI_STYLESETFORE, SCE_LC_VARIABLE, 0x7ECFF2);
                SendMsg(drctPtr, SCI_STYLESETITALIC, SCE_LC_VARIABLE, 1);
                SendMsg(drctPtr, SCI_STYLESETFORE, SCE_LC_NUMBER, 0x6B987D);

                // set up the magins
                SendMsg(drctPtr, SCI_SETMARGINWIDTHN, 0, 30);
                SendMsg(drctPtr, SCI_SETMARGINWIDTHN, 1, 10);
                SendMsg(drctPtr, SCI_SETMARGINWIDTHN, 2, 14);
                SendMsg(drctPtr, SCI_SETMARGINMASKN, 2, SC_MASK_FOLDERS);
                SendMsg(drctPtr, SCI_SETMARGINSENSITIVEN, 2, 1);

                //set the margin colors
                SendMsg(drctPtr, SCI_STYLESETFORE, STYLE_LINENUMBER, 0x919293);
                SendMsg(drctPtr, SCI_STYLESETBACK, STYLE_LINENUMBER, 0x404040);
                SendMsg(drctPtr, SCI_SETFOLDMARGINCOLOUR, 1, 0x404040);
                SendMsg(drctPtr, SCI_SETFOLDMARGINHICOLOUR, 1, 0x404040);

                //set up the markers for the fold margin
                SendMsg(drctPtr, SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND,
                        SC_MARK_CIRCLEPLUSCONNECTED);
                SendMsg(drctPtr, SCI_MARKERSETFORE, SC_MARKNUM_FOLDEREND,
                        0x454240);
                SendMsg(drctPtr, SCI_MARKERSETBACK, SC_MARKNUM_FOLDEREND,
                        0x6C6D71);

                SendMsg(drctPtr, SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID,
                        SC_MARK_CIRCLEMINUSCONNECTED);
                SendMsg(drctPtr, SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPENMID,
                        0x454240);
                SendMsg(drctPtr, SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPENMID,
                        0x6C6D71);

                SendMsg(drctPtr, SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL,
                        SC_MARK_TCORNER);
                SendMsg(drctPtr, SCI_MARKERSETBACK, SC_MARKNUM_FOLDERMIDTAIL,
                        0x6C6D71);

                SendMsg(drctPtr, SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL,
                        SC_MARK_LCORNER);
                SendMsg(drctPtr, SCI_MARKERSETBACK, SC_MARKNUM_FOLDERTAIL,
                        0x6C6D71);

                SendMsg(drctPtr, SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB,
                        SC_MARK_VLINE);
                SendMsg(drctPtr, SCI_MARKERSETBACK, SC_MARKNUM_FOLDERSUB,
                        0x6C6D71);

                SendMsg(drctPtr, SCI_MARKERDEFINE, SC_MARKNUM_FOLDER,
                        SC_MARK_CIRCLEPLUS);
                SendMsg(drctPtr, SCI_MARKERSETFORE, SC_MARKNUM_FOLDER,
                        0x454240);
                SendMsg(drctPtr, SCI_MARKERSETBACK, SC_MARKNUM_FOLDER,
                        0x6C6D71);

                SendMsg(drctPtr, SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN,
                        SC_MARK_CIRCLEMINUS);
                SendMsg(drctPtr, SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPEN,
                        0x454240);
                SendMsg(drctPtr, SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPEN,
                        0x6C6D71);
            }
        }
    } catch (...) {
        // Should not throw into caller
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////
// part2: Impliment the factory functions

static const char *lexerName = "lambdacalc";

extern "C" {

int EXT_LEXER_DECL GetLexerCount() {
    return 1;
}

void EXT_LEXER_DECL GetLexerName(unsigned int index, char *name,int buflength) {
    *name = 0;
    if ((index == 0) && (buflength > static_cast<int>(strlen(lexerName)))) {
        strcpy(name, lexerName);
    }
}

LexerFactoryFunction EXT_LEXER_DECL GetLexerFactory(unsigned int index) {
    if (index == 0)
        return LexerLambdaCalculus::LexerFactoryLambdaCalculus;
    else
        return 0;
}

}//end extern "C"
