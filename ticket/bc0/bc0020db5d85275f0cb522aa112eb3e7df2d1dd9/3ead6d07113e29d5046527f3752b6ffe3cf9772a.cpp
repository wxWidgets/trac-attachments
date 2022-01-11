/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWindows sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: minimal.cpp,v 1.57.2.1 2003/06/01 12:04:23 JS Exp $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources)
#if defined(__WXGTK__) || defined(__WXMOTIF__) || defined(__WXMAC__) || defined(__WXMGL__) || defined(__WXX11__)
    #include "mondrian.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
            long style = wxDEFAULT_FRAME_STYLE);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    // any class wishing to process wxWindows events must use this macro
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = 1,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWindows
// ----------------------------------------------------------------------------

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWindows to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // create the main application window
    MyFrame *frame = new MyFrame(_T("Minimal wxWindows App"),
                                 wxPoint(50, 50), wxSize(450, 340));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(TRUE);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned FALSE here, the
    // application would exit immediately.
    return TRUE;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, long style)
       : wxFrame(NULL, -1, title, pos, size, style)
{
    // set the frame icon
    SetIcon(wxICON(mondrian));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *menuFile = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    menuFile->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWindows!"));
#endif // wxUSE_STATUSBAR
}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // TRUE is to force the frame to close
    Close(TRUE);
}


#ifdef va_copy
    static wxString s_supported=wxT(">>>Congratulations, your compiler already supports va_copy!<<<");
#else
    static wxString s_supported=wxT(">>>Your compiler does not yet support va_copy.<<<");
#endif

// Uncomment the following line to try how your code would work
// if there aren't any va_copy calls at all
//#define va_copy(d,s)

//---------------------------------------------------------------------------
/*
 * THE CODE BELOW SHOULD GO INTO DEFS.H OR A SIMILAR PLACE
 */

// The following #ifndef va_copy section is used to implement
// compiler specific va_copy solutions. Add your compiler specific
// macro here.
#ifndef va_copy
#  ifdef __WATCOMC__
#    if defined(__PPC__)
#      if defined(__NT__)
         // typedef char * __va_list;
#        define va_copy(d,s) memcpy(&(d),&(s),sizeof(va_list));
#      else
         // typedef struct {
         //   char  __gpr;
         //   char  __fpr;
         //   char  __reserved[2];
         //   char *__input_arg_area;
         //   char *__reg_save_area;
         // } __va_list;
#        define va_copy(d,s) memcpy(&(d),&(s),sizeof(va_list));
#      endif
#    elif defined(__AXP__)
       // typedef struct {
       //   char *__base;
       //   int   __offset;
       // } __va_list;
#      define va_copy(d,s) memcpy(&(d),&(s),sizeof(va_list));
#    elif defined(__HUGE__) || defined(__SW_ZU)
       // typedef char _WCFAR *__va_list[1];
#      define va_copy(d,s) memcpy((d),(s),sizeof(va_list));
#    else
       // typedef char *__va_list[1];
#      define va_copy(d,s) memcpy((d),(s),sizeof(va_list));
#    endif
#  endif /* __WATCOMC__ */

#  ifdef __BORLANDC__ 
     // typedef void _FAR *va_list;
#    define va_copy(d,s) memcpy(&(d),&(s),sizeof(va_list));
#  endif /* __BORLANDC__ */

/* Add more compiler macros here! */

#endif /* va_copy */


//---------------------------------------------------------------------------
/* If we there's still no va_copy (no C99 compiler and no compiler macro) */
#ifndef va_copy
  // This must be a function and it is possible to put this into
  // a header (though its ugly)
  // Keep in mind that it will expand to code only once and only
  // if you didn't define a va_copy macro for your compiler.
  static int __HWGva_copy_isarray(va_list arg, va_list *argp)
  {
      // Check if a well initialized va_list argument is
      // really referring to an array.
      if(memcmp(&arg, &argp, sizeof(va_list)) == 0)
      {
          // If the value of a name is equal to its address,
          // we assume it is an array because a self reference
          // is unthinkable due to the way pointer equivalence
          // works and if an array is passed to a function, you
          // really get the pointer to it as the value.
          return(1);
      } /* if */

      return(0);

  } /* __HWGva_copy_isarray */

  // This needs to be a function, too - just like the above function.
  // Adding it to a block within the macro just increases code size
  // without providing any added value.
  static int __AWIva_copy_isarray_helper(int dummy, ...)
  {
      int res;
      va_list testlist;

      // Check if an auto va_list is really defined as an
      // array type or not.
      va_start(testlist, dummy);
      res=__HWGva_copy_isarray(testlist, &testlist);
      va_end(testlist);

      return (res);

  } /* __AWIva_copy_isarray_helper */

  // Unfortunately, this macro throws warnings on some compilers.
  // However, if you just implement a va_copy macro specific to your
  // compiler as shown above, those warnings will be gone.
  // Don't try to use typecasts to get rid of the warning, unless
  // you know exactely what you are doing! It might work on
  // your compiler, but on other compilers the code might not
  // work anymore, resulting into unexpected behaviour or
  // crashes.
# define va_copy(dest,src) \
      if(__AWIva_copy_isarray_helper(0,0)) \
      { \
          memcpy((dest), (src), sizeof(va_list)); \
      }\
      else\
      {\
          memcpy(&(dest), &(src), sizeof(va_list));\
      } /* if */
#endif /* va_copy */

/*
 * THE CODE ABOVE SHOULD GO INTO DEFS.H OR A SIMILAR PLACE
 */
//---------------------------------------------------------------------------






void s_getargs(va_list list, wxChar **a1, wxChar **a2, wxChar **a3)
{
    (*a1)=va_arg(list, wxChar *);
    (*a2)=va_arg(list, wxChar *);
    (*a3)=va_arg(list, wxChar *);
}


static wxChar *s_getarg(va_list list)
{
    return (va_arg(list, wxChar *));
}

static wxChar *s_getarg_r(va_list *list)
{
    return (va_arg(*list, wxChar *));
}


static wxString s_test_va_copy(va_list list, va_list *listptr)
{
    // We could write this function with just one wxString variable.
    // But then we'd have to use Printf with long strings, which
    // in version 2.5.2 of wxWidgets causes the code to crash
    // (at least on OpenWatcom MSW). So we're using a safer method here.
    wxString s, s1;
    va_list tmplist;
    // We are expecting 3 arguments in va_list!
    wxChar *a1, *a2, *a3;

    // Copy argument list
    va_copy(tmplist, list);

    // Get the first three args
    s_getargs(list, &a1, &a2, &a3);
    s1.Printf(wxT("=> [1] Counting: %s, %s, %s\n"), a1, a2, a3);
    s=s1;
    s << wxT("THE NEXT COUNT SHOULD BE IDENTICAL!\n");

    // Copy argument list once again
    va_copy(list, tmplist);

    // Get the first three args
    s_getargs(list, &a1, &a2, &a3);
    s1.Printf(wxT("=> [2] Counting: %s, %s, %s\n"), a1, a2, a3);
    s << s1;

    // Copy argument list once again
    va_copy(list, tmplist);
    s << wxT(
        "\nThe next line has been left in the code to make you aware "
        "that you shouldn't call va_arg from within an argument "
        "list, as it might reverse the argument order:\n"
    );
    s1.Printf(wxT("=> [3] Counting: %s, %s, %s\n"), va_arg(list, wxChar *), va_arg(list, wxChar *), va_arg(list, wxChar *));
    s << s1;

    // Copy argument list once again
    va_copy(list, tmplist);
    s << wxT(
        "Have a look at the next line, some compilers will still "
        "count here, while others will count \"one, one, one\"."
        "This is normal behaviour, but you should be aware of it "
        "when writing code with va_list.\n"
    );
    s1.Printf(wxT("=> [4] Counting: %s, %s, %s\n"), s_getarg(list), s_getarg(list), s_getarg(list));
    s << s1;

    // Copy argument list once again
    va_copy(list, tmplist);
    s << wxT(
        "And now look how you can modify the code to still count even "
        "on compilers that didn't count in the last example.\n"
    );
    s1.Printf(wxT("=> [5] Counting: %s, %s, %s\n"), s_getarg_r(listptr), s_getarg_r(listptr), s_getarg_r(listptr));
    s << s1;

    // This time, we won't copy the argument list
    s << wxT(
        "Now we show you what would happen if we didn't call va_copy(). "
        "You will only see a difference if it didn't count \"one, one, one\" above.\n"
    );
    s_getargs(list, &a1, &a2, &a3);
    s1.Printf(wxT("=> [6] Counting: %s, %s, %s\n"), a1, a2, a3);
    s << s1;

    // Print a note
    s << wxT(
        "\nDid you find any \"ERROR\" strings?\n\n"
        "Then please report that, otherwise your code will crash with "
        "future wxWindows versions! You need not report reverse counting "
        "or counting \"one, one, one\".\n"
    );

    return s;
}


static wxString s_prepare_test_va_copy(int dummy, ...)
{
    va_list list;
    wxString s;

    va_start(list, dummy);
    s=s_test_va_copy(list, &list);
    va_end(list);

    return (s);
}


void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the About dialog of the minimal sample.\n")
                _T("Welcome to %s"), wxVERSION_STRING);

    msg <<
        wxT(
            "\n\nWell, this is a changed version of the minimal program, "
            "that is used to test if our va_copy() hack works with every "
            "compiler. "
        ) << s_supported <<
        wxT(
           " Please see if the following output looks reasonable:\n"
        ) <<
        s_prepare_test_va_copy(0,
            wxT("one"),
            wxT("two"),
            wxT("three"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR"),
            wxT("ERROR")
        ) << // We need 15 error arguments here - if va_copy() is a nop
        wxT(
            "Did you notice any warnings while compiling this program? "
            "Please let us know and also tell us which compiler you were "
            "using. Or even better: look at the \"#ifndef va_copy\" section "
            "in this source and add a va_copy define for your compiler that "
            "does the correct kind of memcpy(). Recompile (one warning will "
            "stay) and check if everything works (test the about dialog once "
            "again) and then submit your changes. Be aware, it is very "
            "important to use the correct version of memcpy (with/without "
            "address operator)."
        );

    wxMessageBox(msg, _T("About Minimal"), wxOK | wxICON_INFORMATION, this);
}


 	  	 
