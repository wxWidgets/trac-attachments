/////////////////////////////////////////////////////////////////////////////
// Name:        src/mac/carbon/artmac.cpp
// Purpose:     Stock wxArtProvider instance with native Mac stock icons
// Author:      Cody Precord
// Created:     2007-08-30
// RCS-ID:      $Id: $
// Copyright:   (c) Cody Precord
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
// Headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#if defined(__BORLANDC__)
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/image.h"
#endif

#ifdef __DARWIN__
    #include <ApplicationServices/ApplicationServices.h>
#else
    #include <PictUtils.h>
#endif

#include "wx/artprov.h"
#include "wx/image.h"

// ----------------------------------------------------------------------------
// wxMacArtProvider
// ----------------------------------------------------------------------------

class wxMacArtProvider : public wxArtProvider
{
protected:
    virtual wxBitmap CreateBitmap(const wxArtID& id, const wxArtClient& client,
                                  const wxSize& size);
};

void wxArtProvider::InitNativeProvider()
{
    wxArtProvider::Push(new wxMacArtProvider);
}

// ----------------------------------------------------------------------------
// CreateBitmap
// ----------------------------------------------------------------------------

OSType wxArtIDToMacID(const wxArtID& id)
{
    #define ART(wxid, macid) \
           if (id == wxid) return macid;

    ART(wxART_ERROR,                               kAlertStopIcon)
    ART(wxART_INFORMATION,                         kAlertNoteIcon)
    ART(wxART_QUESTION,                            kAlertCautionIcon)
    ART(wxART_WARNING,                             kAlertCautionIcon)

    //ART(wxART_MISSING_IMAGE,                       )

    //ART(wxART_ADD_BOOKMARK,                        )
    //ART(wxART_DEL_BOOKMARK,                        )

    ART(wxART_GO_BACK,                             kBackwardArrowIcon)
    ART(wxART_GO_FORWARD,                          kForwardArrowIcon)
    //ART(wxART_GO_UP,                               kSortAscendingIcon)
    //ART(wxART_GO_DOWN,                             kSortDescendingIcon)
    //ART(wxART_GO_TO_PARENT,                        kSortAscendingIcon)
    ART(wxART_GO_HOME,                             kUserFolderIcon)

    //ART(wxART_HELP,                                )
    //ART(wxART_HELP_SIDE_PANEL,                     )
    ART(wxART_HELP_SETTINGS,                       kGenericFontIcon)
    //ART(wxART_HELP_BOOK,                           )
    ART(wxART_HELP_FOLDER,                         kHelpFolderIcon)
    ART(wxART_HELP_PAGE,                           kGenericDocumentIcon)

    //ART(wxART_TIP,                                 )
    //ART(wxART_REPORT_VIEW,                         )
    //ART(wxART_LIST_VIEW,                           )
    ART(wxART_PRINT,                               kPrintMonitorFolderIcon)

   // ART(wxART_NEW_DIR,                             )
    ART(wxART_FOLDER,                              kGenericFolderIcon)
    ART(wxART_FOLDER_OPEN,                         kOpenFolderIcon)
    //ART(wxART_GO_DIR_UP,                           )
    //ART(wxART_EXECUTABLE_FILE,                     )
    ART(wxART_NORMAL_FILE,                         kGenericDocumentIcon)
    //ART(wxART_FILE_OPEN,                           )
    //ART(wxART_FILE_SAVE,                           )
    //ART(wxART_FILE_SAVE_AS,                        )

    //ART(wxART_TICK_MARK,                           )
    //ART(wxART_CROSS_MARK,                          )

    ART(wxART_FLOPPY,                              kGenericFloppyIcon)
    ART(wxART_CDROM,                               kGenericCDROMIcon)
    ART(wxART_HARDDISK,                            kGenericHardDiskIcon)
    ART(wxART_REMOVABLE,                           kGenericRemovableMediaIcon)

    //ART(wxART_COPY,                                )
    //ART(wxART_CUT,                                 )
    //ART(wxART_PASTE,                               )
    ART(wxART_DELETE,                              kTrashIcon)
    //ART(wxART_NEW,                                 )

    //ART(wxART_UNDO,                                kBackwardArrowIcon)
    //ART(wxART_REDO,                                kForwardArrowIcon)

    //ART(wxART_QUIT,                                kShutdownItemsFolderIcon)

    //ART(wxART_FIND,                                
    //ART(wxART_FIND_AND_REPLACE,                    )

    return NULL;

    #undef ART
}

// ----------------------------------------------------------------------------
// CreateBitmap
// ----------------------------------------------------------------------------

wxBitmap wxMacArtProvider::CreateBitmap(const wxArtID& id,
                                        const wxArtClient& client,
                                        const wxSize& reqSize)
{
    wxSize size;
    if (reqSize == wxDefaultSize)
    {
        if (client == wxART_CMN_DIALOG || \
            client == wxART_MESSAGE_BOX)
            size = wxSize(64, 64);
        else if (client == wxART_TOOLBAR)
            size = wxSize(32, 32);
        else
            size = wxSize(16, 16);
    }
    else
        size = reqSize;

    OSType artId = wxArtIDToMacID(id);
    if ( artId )
    {
        IconRef macIconRef = NULL;
        verify_noerr( GetIconRef(kOnSystemDisk, kSystemIconsCreator, artId, &macIconRef) );
        if ( macIconRef )
        {
            // Succeeded getting native icon so return it
            wxIcon macIcon((WXHICON)macIconRef, size);
            wxBitmap macBmp(macIcon);
            ReleaseIconRef(macIconRef);
            return macBmp;
        }
    }
    return wxNullBitmap;
}

 	  	 
