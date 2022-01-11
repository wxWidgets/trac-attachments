// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/app.h>
#include <wx/protocol/ftp.h>
#include <wx/wfstream.h>
#include <wx/cmdline.h>

int main(int argc, char **argv)
{
    wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");

    wxInitializer initializer;
    if ( !initializer )
    {
        fprintf(stderr, "Failed to initialize the wxWidgets library, aborting.");
        return -1;
    }
    wxFTP ftp;
    // if you don't use these lines anonymous login will be used
    // ftp.SetUser("user");
    // ftp.SetPassword("password");
    if ( !ftp.Connect( "ftp.wxwidgets.org" ) )
    {
        wxLogError("Couldn't connect");
        return -1;
    }
    ftp.ChDir("/pub/2.8.9");
    ftp.SetBinary();
    const char *filename = "wxWidgets-2.8.9.tar.bz2";
    int size = ftp.GetFileSize(filename);
    if ( size == -1 )
    {
        wxLogError("Couldn't get the file size for \"%s\"", filename);
    }
    wxInputStream *in = ftp.GetInputStream(filename);
    if ( !in )
    {
        wxLogError("Couldn't get the file");
    }
    else
    {
//        char *data = new char[size];
//        if( !in->Read(data, size) )
//        {
//            wxLogError("Read error: %d", ftp.GetError());
//        }
//        else
//        {
// file data is in the buffer
//		...
            wxOutputStream *out = new wxFileOutputStream( "temp" );
            out->Write( *in );
            wxPrintf( "Do something with the buffer!" );
//        }
//        delete [] data;
        delete in;
        bool result = ftp.ChDir( "/pub/2.9.0" );
    }
    // gracefully close the connection to the server
    ftp.Close();
}
