///////////////////////////////////////////////////////////////////////////////
// Purpose:     test app for testing bitmaps in wxDFB
// Author:      Vaclav Slavik
// Created:     2007-05-07
// Copyright:   (c) 2007 REA GmbH
// Version:     $Id: testbitmap.cpp 157 2007-07-16 19:02:35Z vaclav $
// Licence:
///////////////////////////////////////////////////////////////////////////////

#include <wx/frame.h>
#include <wx/app.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
#include <wx/log.h>
#include <wx/image.h>
#include <wx/dcclient.h>
#include <wx/rawbmp.h>

// --------------------------------------------------------------------------
// bitmap handling helpers
// --------------------------------------------------------------------------

static wxBitmap LoadBitmap(const wxString& name)
{
    wxPathList paths;
    paths.push_back(".");
    paths.push_back("/usr/share/test-bitmap");

    const wxString imgfile = paths.FindValidPath(name);
    if ( imgfile.empty() )
    {
        wxLogError("couldn't find %s", name);
        return wxNullBitmap;
    }

    // load the bitmap; this uses wxImage internally
    wxBitmap bmp(imgfile, wxBITMAP_TYPE_TIF);

    // now convert the bitmap back to wxImage and back to wxBitmap again,
    // to verify that both directions of wxBitmap<->wxImage conversion work:
    wxImage img(bmp.ConvertToImage());

    return wxBitmap(img);
}

static wxBitmap DrawAlphaEffectsOnBitmap(const wxBitmap& orig)
{
    wxBitmap bmp(orig);

    wxAlphaPixelData data(bmp);
    if ( !data )
    {
        wxLogError("Failed to gain raw access to bitmap data");
        return orig;
    }

    wxAlphaPixelData::Iterator p(data);

    for ( int y = 0; y < data.GetHeight(); ++y )
    {
        wxAlphaPixelData::Iterator rowStart = p;

        for ( int x = 0; x < data.GetWidth(); ++x )
        {
            p.Alpha() = wxMax(50, 255 - p.Alpha());
            ++p; // same as p.OffsetX(1)
        }

        p = rowStart;
        p.OffsetY(data, 1);
    }

    return bmp;
}

static wxBitmap DrawRedEffectsOnBitmap(const wxBitmap& orig)
{
    wxBitmap bmp(orig);

    wxNativePixelData data(bmp);
    if ( !data )
    {
        wxLogError("Failed to gain raw access to bitmap data");
        return orig;
    }

/*
    wxNativePixelData::Iterator p(data);

    for ( int y = 0; y < data.GetHeight(); ++y )
    {
        wxNativePixelData::Iterator rowStart = p;

        for ( int x = 0; x < data.GetWidth(); ++x )
        {
            p.Red() = wxMin(int(p.Red() * 1.5), 255);
            ++p; // same as p.OffsetX(1)
        }

        p = rowStart;
        p.OffsetY(data, 1);
    }
*/
    return bmp;
}

// --------------------------------------------------------------------------
// BitmapFrame
// --------------------------------------------------------------------------

class BitmapFrame : public wxFrame
{
public:
    BitmapFrame()
        : wxFrame(NULL, wxID_ANY, _T("Bitmaps"))
    {
        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        SetSizer(sizer);

        sizer->Add(new wxStaticText(this, wxID_ANY,
                   _T("press Q or 1 to quit")),
                   wxSizerFlags().Left());

        AddBitmap(sizer, "image-alpha.tiff", &DrawAlphaEffectsOnBitmap);
        AddBitmap(sizer, "image-noalpha.tiff", &DrawRedEffectsOnBitmap);

        Connect
        (
            wxEVT_KEY_DOWN,
            wxKeyEventHandler(BitmapFrame::OnKeyDown),
            NULL,
            this
        );

        Connect
        (
            wxEVT_PAINT,
            wxPaintEventHandler(BitmapFrame::OnPaint),
            NULL,
            this
        );
    }

private:
    void OnPaint(wxPaintEvent& e)
    {
        wxPaintDC dc(this);

        dc.SetTextForeground("red");
        dc.DrawText("hello, world", 4, 10);

        wxSize sz = GetSize();
        dc.SetPen(wxPen("blue"));
        dc.DrawLine(0, 0, sz.x, sz.y);
        dc.DrawLine(sz.x, 0, 0, sz.y);
    }

    void AddBitmap(wxSizer *sizer, const wxString& name,
                   wxBitmap (*effectsFunc)(const wxBitmap&))
    {
        wxBitmap bmp(LoadBitmap(name));
        if ( bmp.IsOk() )
        {
            wxBoxSizer *sizer2 = new wxBoxSizer(wxHORIZONTAL);

            // without 'bmp.GetSize()' the bitmap isn't visible!??
            sizer2->Add(new wxStaticBitmap(this, wxID_ANY, bmp,
                                           wxDefaultPosition, bmp.GetSize()));
            sizer2->Add(new wxStaticBitmap(this, wxID_ANY, effectsFunc(bmp),
                                           wxDefaultPosition, bmp.GetSize()));

            sizer->Add(sizer2, wxSizerFlags().Left());
        }
    }

    void OnKeyDown(wxKeyEvent& event)
    {
        switch ( event.GetKeyCode() )
        {
            case 'Q':
            case '1':
                Close();

            default:
                event.Skip();
        }
    }
};

// --------------------------------------------------------------------------
// FontsApp
// --------------------------------------------------------------------------

class BitmapApp : public wxApp
{
public:
    BitmapApp() : wxApp() {}

    virtual bool OnInit()
    {
        if ( !wxApp::OnInit() )
            return false;

        wxInitAllImageHandlers();

        wxFrame *frame = new BitmapFrame();
        frame->Maximize();
        frame->Show(true);

        return true;
    }
};

IMPLEMENT_APP(BitmapApp)
