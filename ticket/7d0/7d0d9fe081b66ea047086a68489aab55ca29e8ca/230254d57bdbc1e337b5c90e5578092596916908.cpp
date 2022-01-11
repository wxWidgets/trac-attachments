/////////////////////////////////////////////////////////////////////////////
// Name:        src/common/artprov.cpp
// Purpose:     wxArtProvider class
// Author:      Vaclav Slavik
// Modified by:
// Created:     18/03/2002
// Copyright:   (c) Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#if defined(__BORLANDC__)
    #pragma hdrstop
#endif

#include "wx/artprov.h"

#ifndef WX_PRECOMP
    #include "wx/list.h"
    #include "wx/log.h"
    #include "wx/hashmap.h"
    #include "wx/image.h"
    #include "wx/module.h"
#endif

// ===========================================================================
// implementation
// ===========================================================================

#include "wx/listimpl.cpp"
WX_DECLARE_LIST(wxArtProvider, wxArtProvidersList);
WX_DEFINE_LIST(wxArtProvidersList)

// ----------------------------------------------------------------------------
// Cache class - stores already requested bitmaps
// ----------------------------------------------------------------------------

WX_DECLARE_EXPORTED_STRING_HASH_MAP(wxBitmap, wxArtProviderBitmapsHash);
WX_DECLARE_EXPORTED_STRING_HASH_MAP(wxIconBundle, wxArtProviderIconBundlesHash);

class WXDLLEXPORT wxArtProviderCache
{
public:
    bool GetBitmap(const wxString& full_id, wxBitmap* bmp);
    void PutBitmap(const wxString& full_id, const wxBitmap& bmp)
        { m_bitmapsHash[full_id] = bmp; }

    bool GetIconBundle(const wxString& full_id, wxIconBundle* bmp);
    void PutIconBundle(const wxString& full_id, const wxIconBundle& iconbundle)
        { m_iconBundlesHash[full_id] = iconbundle; }

    void Clear();

    // JACS: add bitmapScale
    static wxString ConstructHashID(const wxArtID& id,
                                    const wxArtClient& client,
                                    const wxSize& size,
                                    const double bitmapScale = 1.0);

    // JACS: add bitmapScale
    static wxString ConstructHashID(const wxArtID& id,
                                    const wxArtClient& client,
                                    const double bitmapScale = 1.0);

private:
    wxArtProviderBitmapsHash m_bitmapsHash;         // cache of wxBitmaps
    wxArtProviderIconBundlesHash m_iconBundlesHash; // cache of wxIconBundles
};

bool wxArtProviderCache::GetBitmap(const wxString& full_id, wxBitmap* bmp)
{
    wxArtProviderBitmapsHash::iterator entry = m_bitmapsHash.find(full_id);
    if ( entry == m_bitmapsHash.end() )
    {
        return false;
    }
    else
    {
        *bmp = entry->second;
        return true;
    }
}

bool wxArtProviderCache::GetIconBundle(const wxString& full_id, wxIconBundle* bmp)
{
    wxArtProviderIconBundlesHash::iterator entry = m_iconBundlesHash.find(full_id);
    if ( entry == m_iconBundlesHash.end() )
    {
        return false;
    }
    else
    {
        *bmp = entry->second;
        return true;
    }
}

void wxArtProviderCache::Clear()
{
    m_bitmapsHash.clear();
    m_iconBundlesHash.clear();
}

// JACS
/* static */ wxString
wxArtProviderCache::ConstructHashID(const wxArtID& id,
                                    const wxArtClient& client,
                                    const double bitmapScale)
{
    return id + wxT('-') + client + wxT("-") + wxString::Format(wxT("%.2f"), bitmapScale);
}


/* static */ wxString
wxArtProviderCache::ConstructHashID(const wxArtID& id,
                                    const wxArtClient& client,
                                    const wxSize& size,
                                    const double bitmapScale)
{
    return ConstructHashID(id, client, bitmapScale) + wxT('-') +
            wxString::Format(wxT("%d-%d"), size.x, size.y);
    

// ============================================================================
// wxArtProvider class
// ============================================================================

wxIMPLEMENT_ABSTRACT_CLASS(wxArtProvider, wxObject);

wxArtProvidersList *wxArtProvider::sm_providers = NULL;
wxArtProviderCache *wxArtProvider::sm_cache = NULL;
// JACS
wxArtProvider::BitmapSelectionMode wxArtProvider::sm_bitmapSelectionMode = wxArtProvider::BitmapSelection_NearestSize;

// ----------------------------------------------------------------------------
// wxArtProvider ctors/dtor
// ----------------------------------------------------------------------------

wxArtProvider::~wxArtProvider()
{
    Remove(this);
}

// ----------------------------------------------------------------------------
// wxArtProvider operations on provider stack
// ----------------------------------------------------------------------------

/*static*/ void wxArtProvider::CommonAddingProvider()
{
    if ( !sm_providers )
    {
        sm_providers = new wxArtProvidersList;
        sm_cache = new wxArtProviderCache;
    }

    sm_cache->Clear();
}

/*static*/ void wxArtProvider::Push(wxArtProvider *provider)
{
    CommonAddingProvider();
    sm_providers->Insert(provider);
}

/*static*/ void wxArtProvider::PushBack(wxArtProvider *provider)
{
    CommonAddingProvider();
    sm_providers->Append(provider);
}

/*static*/ bool wxArtProvider::Pop()
{
    wxCHECK_MSG( sm_providers, false, wxT("no wxArtProvider exists") );
    wxCHECK_MSG( !sm_providers->empty(), false, wxT("wxArtProviders stack is empty") );

    delete sm_providers->GetFirst()->GetData();
    sm_cache->Clear();
    return true;
}

/*static*/ bool wxArtProvider::Remove(wxArtProvider *provider)
{
    wxCHECK_MSG( sm_providers, false, wxT("no wxArtProvider exists") );

    if ( sm_providers->DeleteObject(provider) )
    {
        sm_cache->Clear();
        return true;
    }

    return false;
}

/*static*/ bool wxArtProvider::Delete(wxArtProvider *provider)
{
    // provider will remove itself from the stack in its dtor
    delete provider;

    return true;
}

/*static*/ void wxArtProvider::CleanUpProviders()
{
    if ( sm_providers )
    {
        while ( !sm_providers->empty() )
            delete *sm_providers->begin();

        wxDELETE(sm_providers);
        wxDELETE(sm_cache);
    }
}

// ----------------------------------------------------------------------------
// wxArtProvider: retrieving bitmaps/icons
// ----------------------------------------------------------------------------

void wxArtProvider::RescaleBitmap(wxBitmap& bmp, const wxSize& sizeNeeded)
{
    wxCHECK_RET( sizeNeeded.IsFullySpecified(), wxS("New size must be given") );

#if wxUSE_IMAGE
    wxImage img = bmp.ConvertToImage();
    img.Rescale(sizeNeeded.x, sizeNeeded.y);
    bmp = wxBitmap(img);
#else // !wxUSE_IMAGE
    // Fallback method of scaling the bitmap
    wxBitmap newBmp(sizeNeeded, bmp.GetDepth());
#if defined(__WXMSW__) || defined(__WXOSX__)
    // wxBitmap::UseAlpha() is used only on wxMSW and wxOSX.
    newBmp.UseAlpha(bmp.HasAlpha());
#endif // __WXMSW__ || __WXOSX__
    {
        wxMemoryDC dc(newBmp);
        double scX = (double)sizeNeeded.GetWidth() / bmp.GetWidth();
        double scY = (double)sizeNeeded.GetHeight() / bmp.GetHeight();
        dc.SetUserScale(scX, scY);
        dc.DrawBitmap(bmp, 0, 0);
    }
    bmp = newBmp;
#endif // wxUSE_IMAGE/!wxUSE_IMAGE
}

/*static*/ wxBitmap wxArtProvider::GetBitmap(const wxArtID& id,
                                             const wxArtClient& client,
                                             const wxSize& size)
{
    // safety-check against writing client,id,size instead of id,client,size:
    wxASSERT_MSG( client.Last() == wxT('C'), wxT("invalid 'client' parameter") );

    wxCHECK_MSG( sm_providers, wxNullBitmap, wxT("no wxArtProvider exists") );

    wxString hashId = wxArtProviderCache::ConstructHashID(id, client, size);

    wxBitmap bmp;
    if ( !sm_cache->GetBitmap(hashId, &bmp) )
    {
        for (wxArtProvidersList::compatibility_iterator node = sm_providers->GetFirst();
             node; node = node->GetNext())
        {
            bmp = node->GetData()->CreateBitmap(id, client, size);
            if ( bmp.IsOk() )
                break;
        }

        wxSize sizeNeeded = size;
        if ( !bmp.IsOk() )
        {
            // no bitmap created -- as a fallback, try if we can find desired
            // icon in a bundle
            wxIconBundle iconBundle = DoGetIconBundle(id, client);
            if ( iconBundle.IsOk() )
            {
                if ( sizeNeeded == wxDefaultSize )
                    sizeNeeded = GetNativeSizeHint(client);

                wxIcon icon(iconBundle.GetIcon(sizeNeeded));
                if ( icon.IsOk() )
                {
                    // this icon may be not of the correct size, it will be
                    // rescaled below in such case
                    bmp.CopyFromIcon(icon);
                }
            }
        }

        // if we didn't get the correct size, resize the bitmap
        if ( bmp.IsOk() && sizeNeeded != wxDefaultSize )
        {
            if ( bmp.GetSize() != sizeNeeded )
            {
                RescaleBitmap(bmp, sizeNeeded);
            }
        }

        sm_cache->PutBitmap(hashId, bmp);
    }

    return bmp;
}

// JACS

/*static*/ wxBitmap wxArtProvider::GetScaledBitmap(const wxArtID& id,
                                             const wxArtClient& client,
                                             const wxSize& szDIP, wxWindow* win)
{
    // safety-check against writing client,id,size instead of id,client,size:
    wxASSERT_MSG( client.Last() == wxT('C'), wxT("invalid 'client' parameter") );

    wxCHECK_MSG( sm_providers, wxNullBitmap, wxT("no wxArtProvider exists") );
    
    wxBitmap bmp;

    // The new method whereby art providers define ProvideBitmap to return an unscaled
    // bitmap, and wxWidgets does the scaling.
    for (wxArtProvidersList::compatibility_iterator node = sm_providers->GetFirst();
         node; node = node->GetNext())
    {
        bmp = node->GetData()->CreateScaledBitmap(id, client, szDIP, win);
        if (bmp.IsOk())
            break;
    }
    
    // The old, default method where CreateBitmap returns a possibly scaled
    // bitmap
    if (!bmp.IsOk())
        bmp = GetBitmap(id, client, szDIP);
    
    return bmp;
}

// JACS
wxBitmap wxArtProvider::CreateScaledBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& szDIP, wxWindow* win)
{
    // GetScaledBitmapSize uses knowledge provided to the art provider to find what actual
    // bitmap will be returned. It can be overridden to provide an application-specific algorithm.
    
    double bitmapScale = 1.0;

    // On Mac, always returns szDIP but potentially with a bitmapScale to indicate
    // a scaled bitmap can be created.
    // bitmapScale is always 1.0 for Windows and GTK+2. GTK+3 not considered yet.
    wxSize szPixels = GetScaledBitmapSize(id, client, szDIP, win, bitmapScale);
    
    // Accessing the cache has to be done here rather than in GetScaledBitmap, because
    // we need to distinguish between wxBitmaps with a scaling factor and those without.
    // And we don't know the scaling factor until we've computed an appropriate scaled size
    // consistent with current settings, window PPI, etc.
    // We use szPixels rather than the original size because the relationship between
    // szDIP and szPixels might change during the program lifetime.
    wxString hashId = wxArtProviderCache::ConstructHashID(id, client, szPixels, bitmapScale);

    wxBitmap bmp;
    if (!sm_cache->GetBitmap(hashId, &bmp))
    {
        wxSize actualSize(int(szPixels.x*bitmapScale), int(szPixels.y*bitmapScale));
        
        // Now we get the bitmap required - e.g. a 2x bitmap if we found above that
        // we need it.
        
        if (!BitmapSizeExists(id, client, actualSize) && GetAvailableBitmapCount() > 0)
        {
            // Scale if we don't have this bitmap.
            // Assume in descending order of size, so use the largest.
            wxSize largestSize(GetAvailableBitmapSize(GetAvailableBitmapCount()-1, id, client));
            bmp = ProvideBitmap(id, client, largestSize);
            if (bmp.IsOk())
                RescaleBitmap(bmp, actualSize);
        }
        else
            bmp = ProvideBitmap(id, client, actualSize);
        
        if (bmp.IsOk())
        {
            // On Mac, convert to a scaled bitmap if necessary. GTK+3 not yet supported.
            if (bitmapScale > 1.0)
            {
                // Need a more efficient way to convert to a scaled bitmap.
                wxImage image(bmp.ConvertToImage());
                wxBitmap newBitmap(image, -1, bitmapScale);
                
                // The new bitmap now has e.g. 2x size internally, but with a scale factor of e.g. 2.0 to allow
                // it to be drawn at a logical szDIP size.
                if (newBitmap.IsOk())
                    bmp = newBitmap;
            }
            
            sm_cache->PutBitmap(hashId, bmp);
        }
    }
    
    return bmp;
}

// JACS
// Returns the bitmap size we should retrieve.
wxSize wxArtProvider::GetScaledBitmapSize(const wxArtID& id, const wxArtClient& client, const wxSize& szDIP, wxWindow* win, double& scale)
{
    if (szDIP == wxDefaultSize)
        return szDIP;
        
#if defined(__WXOSX_COCOA__)
    double scaleFactor = GetBitmapScale();
    if (scaleFactor > 1.0)
    {
        // Round the scale factor since it might be e.g. 1.9
        scaleFactor = double(int(scaleFactor + 0.5));
        wxSize szScaled(szPixels.x*scaleFactor, szPizels.y*scaleFactor);
        if (BitmapSizeExists(id, client, szScaled))
        {
            scale = scaleFactor;
            return szDIP;
        }
        else if (scaleFactor > 2.0)
        {
            // Fall back to 2x bitmap if we didn't have the required larger bitmap
            scaleFactor = 2.0;
            szScaled = wxSize(szPixels.x*scaleFactor, szPizels.y*scaleFactor);
            if (BitmapSizeExists(id, client, szScaled))
            {
                scale = scaleFactor;
                return szDIP;
            }
        }
    }
    
    // Assume the original size is available
    scale = 1.0;
    return szDIP;
#else
    // Windows, GTK+2: find the best size for the bitmap, possibly scaled up if on a HiDPI monitor.
    scale = 1.0;
    wxSize scaledSize = FromDIP(szDIP, win);
    int idx = FindIndexOfNearestSize(id, client, scaledSize);
    if (idx != -1)
        return GetAvailableBitmapSize(idx, id, client);
    else
        return scaledSize;
#endif
}

// JACS
// Allows customisation of scaling for Windows and GTK+2.
// On GTK+2, querying the DPI doesn't seem a reliable way to do scaling for HiDIP.
// So instead, it's helpful to apply a further custom scale factor calculated from
// the height of text on a standard monitor versus the current monitor, e.g.:
//
//    int standardFontHeight = 16;
//    wxFont standardFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
//    wxScreenDC dc;
//    dc.SetFont(standardFont);
//    wxCoord x, y;
//    dc.GetTextExtent(wxT("X"), & x, & y);
//    double autoScale = wxMax(1.0, double(y)/double(standardFontHeight));
//
// By overriding FromDIP in your wxArtProvider, you can apply this scale factor
// calculated when initialising the main window. However, this is not an official
// fix, so it's not provided by default.

wxSize wxArtProvider::FromDIP(const wxSize& szDIP, wxWindow* win)
{
    return (win != NULL) ? win->FromDIP(szDIP) : wxWindow::FromDIP(szDIP);
}    

// JACS
// Does this bitmap size exist?
bool wxArtProvider::BitmapSizeExists(const wxArtID& id, const wxArtClient& client, const wxSize& sz)
{
    size_t i;
    for (i = 0; i < GetAvailableBitmapCount(); i++)
    {
        if (GetAvailableBitmapSize(i, id, client) == sz)
            return true;
    }
    return false;
}

// JACS
// Returns the index of a bitmap that matches the size and options,
// or -1 if no criteria matched (and therefore should use scaled size)
int wxArtProvider::FindIndexOfNearestSize(const wxArtID& id, const wxArtClient& client, const wxSize& targetSize)
{
    int smaller, smallerDiff, larger, largerDiff;
    // Finds the indexes of the nearest bitmaps with percentage difference from target
    if (!FindNearestBitmaps(id, client, targetSize.x, smaller, smallerDiff, larger, largerDiff))
        return -1;
        
    if (smaller == targetSize.x)
        return smaller;
    else if (larger == targetSize.x)
        return larger;
        
    if (GetBitmapSelectionMode() != BitmapSelection_Scale)
    {
        if (smaller != -1 && larger != -1 && smallerDiff == largerDiff)
        {
            if (GetBitmapSelectionMode() == BitmapSelection_SmallerSize)
                return smaller;
            else
                return larger;
            }
        }
        else if (smaller != -1 && larger != -1 && smallerDiff != largerDiff)
        {
            if (GetBitmapSelectionMode() == BitmapSelection_SmallerSize)
                return smaller;
            else if (GetBitmapSelectionMode() == BitmapSelection_LargerSize)
                return larger;
            else if (GetBitmapSelectionMode() == BitmapSelection_NearestSize)
                return (smallerDiff < largerDiff) ? smaller : larger;
        }
        else if (smaller != -1)
            return smaller;
        else if (larger != -1)
            return larger;
    }

    return -1;
}

// JACS
// Finds the indexes of the nearest bitmaps with percentage difference from target.
// Assumes sizes are in ascending order.
bool wxArtProvider::FindNearestBitmaps(const wxArtID& id, const wxArtClient& client, const wxSize& targetSize, int& smaller, int& smallerDiff, int& larger, int& largerDiff)
{
    const int targetWidth = targetSize.x;
    smaller = -1;
    smallerDiff = 0;
    larger = -1;
    largerDiff = 0;

    if (targetWidth == 0)
        return false;

    int smallerWidth = -1;
    int largerWidth = -1;

    size_t i;
    for (i = 0; i < GetAvailableBitmapCount(); i++)
    {
        int w = GetAvailableBitmapSize(i, id, client).x;
        if (w <= targetWidth)
        {
            if ((smaller == -1) || ((targetWidth - w) < (targetWidth - smallerWidth)))
            {
                smallerWidth = w;
                smaller = i;
                smallerDiff = wxRound(100.0*(targetWidth - smallerWidth)/double(targetWidth));
            }
        }

        if (w >= targetWidth)
        {
            if ((larger == -1) || ((w - targetWidth) < (largerWidth - targetWidth)))
            {
                largerWidth = w;
                larger = i;
                largerDiff = wxRound(100.0*(largerWidth - targetWidth)/double(targetWidth));
            }
        }
    }

    return largerWidth != -1 || smallerWidth != -1;
}

// JACS
// Override to always/never/conditionally use hi-def bitmaps on Mac.
double wxArtProvider::GetBitmapScale(wxWindow *win)
{
    double scaleFactor = 1.0;
#if defined(__WXOSX_COCOA__)
    if (win)
        scaleFactor = win->GetContentScaleFactor();
    else if (wxTheApp && wxTheApp->GetTopWindow())
        scaleFactor = wxTheApp->GetTopWindow()->GetContentScaleFactor();
    else
        scaleFactor wxOSXGetMainScreenContentScaleFactor();
#endif
    return scaleFactor;
}

/*static*/
wxIconBundle wxArtProvider::GetIconBundle(const wxArtID& id, const wxArtClient& client)
{
    wxIconBundle iconbundle(DoGetIconBundle(id, client));

    if ( iconbundle.IsOk() )
    {
        return iconbundle;
    }
    else
    {
        // fall back to single-icon bundle
        return wxIconBundle(GetIcon(id, client));
    }
}

/*static*/
wxIconBundle wxArtProvider::DoGetIconBundle(const wxArtID& id, const wxArtClient& client)
{
    // safety-check against writing client,id,size instead of id,client,size:
    wxASSERT_MSG( client.Last() == wxT('C'), wxT("invalid 'client' parameter") );

    wxCHECK_MSG( sm_providers, wxNullIconBundle, wxT("no wxArtProvider exists") );

    wxString hashId = wxArtProviderCache::ConstructHashID(id, client);

    wxIconBundle iconbundle;
    if ( !sm_cache->GetIconBundle(hashId, &iconbundle) )
    {
        for (wxArtProvidersList::compatibility_iterator node = sm_providers->GetFirst();
             node; node = node->GetNext())
        {
            iconbundle = node->GetData()->CreateIconBundle(id, client);
            if ( iconbundle.IsOk() )
                break;
        }

        sm_cache->PutIconBundle(hashId, iconbundle);
    }

    return iconbundle;
}

/*static*/ wxIcon wxArtProvider::GetIcon(const wxArtID& id,
                                         const wxArtClient& client,
                                         const wxSize& size)
{
    wxBitmap bmp = GetBitmap(id, client, size);

    if ( !bmp.IsOk() )
        return wxNullIcon;

    wxIcon icon;
    icon.CopyFromBitmap(bmp);
    return icon;
}

// JACS
/*static*/ wxIcon wxArtProvider::GetScaledIcon(const wxArtID& id,
                                         const wxArtClient& client,
                                         const wxSize& size,
                                         wxWindow* window)
{
    wxBitmap bmp = GetScaledBitmap(id, client, size, window);

    if ( !bmp.IsOk() )
        return wxNullIcon;

    wxIcon icon;
    icon.CopyFromBitmap(bmp);
    return icon;
}

/* static */
wxArtID wxArtProvider::GetMessageBoxIconId(int flags)
{
    switch ( flags & wxICON_MASK )
    {
        default:
            wxFAIL_MSG(wxT("incorrect message box icon flags"));
            wxFALLTHROUGH;

        case wxICON_ERROR:
            return wxART_ERROR;

        case wxICON_INFORMATION:
            return wxART_INFORMATION;

        case wxICON_WARNING:
            return wxART_WARNING;

        case wxICON_QUESTION:
            return wxART_QUESTION;
    }
}

/*static*/ wxSize wxArtProvider::GetSizeHint(const wxArtClient& client,
                                         bool platform_dependent)
{
    if (!platform_dependent)
    {
        wxArtProvidersList::compatibility_iterator node = sm_providers->GetFirst();
        if (node)
            return node->GetData()->DoGetSizeHint(client);
    }

    return GetNativeSizeHint(client);
}

#ifndef wxHAS_NATIVE_ART_PROVIDER_IMPL
/*static*/
wxSize wxArtProvider::GetNativeSizeHint(const wxArtClient& WXUNUSED(client))
{
    // rather than returning some arbitrary value that doesn't make much
    // sense (as 2.8 used to do), tell the caller that we don't have a clue:
    return wxDefaultSize;
}

/*static*/
void wxArtProvider::InitNativeProvider()
{
}
#endif // !wxHAS_NATIVE_ART_PROVIDER_IMPL


/* static */
bool wxArtProvider::HasNativeProvider()
{
#ifdef __WXGTK20__
    return true;
#else
    return false;
#endif
}

// ----------------------------------------------------------------------------
// deprecated wxArtProvider methods
// ----------------------------------------------------------------------------

#if WXWIN_COMPATIBILITY_2_8
/* static */ void wxArtProvider::Insert(wxArtProvider *provider)
{
    PushBack(provider);
}
#endif // WXWIN_COMPATIBILITY_2_8

// ============================================================================
// wxArtProviderModule
// ============================================================================

class wxArtProviderModule: public wxModule
{
public:
    bool OnInit() wxOVERRIDE
    {
        // The order here is such that the native provider will be used first
        // and the standard one last as all these default providers add
        // themselves to the bottom of the stack.
        wxArtProvider::InitNativeProvider();
#if wxUSE_ARTPROVIDER_TANGO
        wxArtProvider::InitTangoProvider();
#endif // wxUSE_ARTPROVIDER_TANGO
#if wxUSE_ARTPROVIDER_STD
        wxArtProvider::InitStdProvider();
#endif // wxUSE_ARTPROVIDER_STD
        return true;
    }
    void OnExit() wxOVERRIDE
    {
        wxArtProvider::CleanUpProviders();
    }

    wxDECLARE_DYNAMIC_CLASS(wxArtProviderModule);
};

wxIMPLEMENT_DYNAMIC_CLASS(wxArtProviderModule, wxModule);
