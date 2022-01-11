////////////////////////////////////////////////////////////////////////////
// Name:        imagxbm.cpp
// Purpose:     wxXBMHandler
// Author:      Troels K
// Modified by:
// Created:     11/10/2006
// Copyright:   (c) Troels K
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "imagxbm.h"

IMPLEMENT_DYNAMIC_CLASS(wxXBMHandler,wxImageHandler)

////////////////////////////////////////////////////////////////////////////
// C compatible code (except for 'bool' which MSVC considers C++). Nothing really calls for C++ here.

static bool
ParseSize(const char* str, size_t* n)
{
    const char* sep = strrchr(str, ' ');
    bool ok = (NULL != sep);
    if (ok) *n = atoi(sep+1);
    if (ok) ok = (*n > 0);
    return ok;
}

typedef struct _XBM_STRUCT
{
   unsigned char* bits;
   size_t width;
   size_t height;
} XBM_STRUCT;

static bool
xbm_load(char* xbm_buffer, XBM_STRUCT* xbm)
{
    bool ok = true;
    const char* seps = "\n\r";
    unsigned char* bits = NULL;
    size_t buf_len = 0;
    size_t pos = 0;
    int line;
    char* token;

    for (token = strtok(xbm_buffer, seps), line = 0;
         token && ok; 
         token = strtok(NULL, seps), line++)
    {
       if (*token == 0) continue;
       switch (line)
       {
           case 0:
               ok = ParseSize(token, &xbm->width);
               break;
           case 1:
               ok = ParseSize(token, &xbm->height);
               if (ok)
               {
                   buf_len = ((xbm->width + 7)/8) * xbm->height;
                   bits = (unsigned char*)malloc(buf_len);
               }
               break;
           default:
           {
               const char* prev = token;
               while (ok && (pos < buf_len))
               {
                   int x;
                   const char* next = strpbrk(prev, ",");
                   if (1 == sscanf(prev, "%x", &x))
                   {
                  #if defined (__WXMSW__) && (wxVERSION_NUMBER < 2701)
                       bits[pos++] = ~(unsigned char)x;
                  #else
                       bits[pos++] = (unsigned char)x;
                  #endif
                   }
                   if (next == NULL) break;
                   prev = next+1;
               }
               break;
           }
       }
    }
    if (ok) ok = (pos == buf_len); // final sanity check
    if (ok)
    {
        xbm->bits = bits;
    }
    else
    {
        free(bits);
    }
    return ok;
}

__inline int 
Grey(unsigned char r, unsigned char g, unsigned char b)
{
   return ((( b * 11 ) + ( g * 59 ) + ( r * 30 )) / 100 );
}

bool 
bin2c(int (*fprintf_impl)(FILE* stream, const char* fmt, ...), 
         FILE* stream,
         const void* buf,
         size_t buf_len,
         size_t bytes_per_line,
         const char* name,
         const char* newline,
         bool begin,
         bool end,
         bool const_keyword
         )
{
    size_t i;
    const unsigned char* bytes = (unsigned char*)buf;

    bool ok = true;
    
    if (begin) ok = ok && (*fprintf_impl)(stream, "static %sunsigned char %s[] = {%s", 
       const_keyword ? "const " : "",
       name, 
       newline);
 
    for (i = 0; i < buf_len && ok; )
    {
       BOOL final = end && (i == (buf_len-1));
       ok = ok && (*fprintf_impl)(stream, "0x%02x%s", bytes[i], final ? "" : ", ");
       i++;
       if ((i % bytes_per_line) == 0)
       {
           ok = ok && (*fprintf_impl)(stream, newline);
       }
    }
    if (bytes_per_line && (i % bytes_per_line))
    {
        ok = ok && (*fprintf_impl)(stream, newline);
    }
    if (end) ok = ok && (*fprintf_impl)(stream, "};%s", newline);
    return ok;
}

static bool 
xbm_save(int (*fprintf_impl)(FILE* stream, const char* fmt, ...), 
         FILE* stream,
         const XBM_STRUCT* xbm,
         const char* name,
         unsigned char color_threshold, 
         size_t bytes_per_line)
{
    const char* newline = "\r\n";
    const unsigned char* bits = xbm->bits;
    size_t x, y;
    bool ok = true;
    unsigned char* buf = (unsigned char*)malloc(bytes_per_line);
    size_t pos = 0;

    ok = ok && (*fprintf_impl)(stream, "#define %s_width %d%s"               , name, xbm->width , newline);
    ok = ok && (*fprintf_impl)(stream, "#define %s_height %d%s"              , name, xbm->height, newline);
    ok = ok && (*fprintf_impl)(stream, "static unsigned char %s_bits[] = {%s", name             , newline);
 
    for (y = 0; (y < xbm->height) && ok; y++)
    {
        const bool final_y = (y == (xbm->height - 1));
        unsigned char byte = 0;

        for (x = 0; (x < xbm->width) && ok; x++)
        {
            const bool final_x = (x == (xbm->width - 1));
            unsigned char r, g, b;

            r = *(bits++);
            g = *(bits++);
            b = *(bits++);
            byte|=(Grey(r,g,b) >= color_threshold) ? 0 : (1 << (x % 8));

            if (((x % 8) == 7) || final_x)
            {
                const bool final = final_x && final_y;
                buf[pos % bytes_per_line] = byte;
                byte = 0;
                pos++;
                if (final || ((pos % bytes_per_line) == 0))
                {
                    size_t bytes = (pos % bytes_per_line) ? (pos % bytes_per_line) : bytes_per_line;
                    ok = bin2c(fprintf_impl, stream, buf, bytes, bytes_per_line, NULL, newline, false, final, false);
                }
            }
        }
    }
    free(buf);
    return ok;
}

////////////////////////////////////////////////////////////////////////////
// C++ code (wx)

bool 
wxXBMHandler::DoCanRead(wxInputStream& stream)
{
    const size_t len = 8;
    unsigned char hdr[len];

    bool ok = (len == stream.Read(hdr, len).LastRead());
    if (ok) ok = (0 == memcmp(hdr, "#define ", len));
    return ok;
}

bool
wxXBMHandler::LoadFile(wxImage* image,
                       wxInputStream& stream,
                       bool WXUNUSED(verbose),
                       int WXUNUSED(index))
{
    const size_t length = stream.GetSize();
    wxCHECK_MSG( length != 0, false, wxT("Cannot read XBM from stream of unknown size") );

    wxCharBuffer buffer(length /*implicit +1 (room for zero-termination) */);

    char* buf_ptr = buffer.data();
    bool ok = (length == stream.Read(buf_ptr, length).LastRead());
    if (ok)
    {
        XBM_STRUCT xbm;

        buf_ptr[length] = 0;
        ok = ::xbm_load(buf_ptr, &xbm);
        if (ok)
        {
            // char* cast because otherwise the wrong ctor is chosen (the xpm ctor)
            wxBitmap bmp((char*)xbm.bits, xbm.width, xbm.height, 1); // xbm ctor
            ok = bmp.Ok();
            if (ok) image->operator=(bmp.ConvertToImage()); 
            free(xbm.bits);
        }
    }
    return ok;
}

static void 
c_syntax_fixup(wxString* str)
{
    const wxString no_good = wxT("-=+!#%&()^,.\"|~;<>");
    for (size_t i = 0; i < str->Length(); i++)
    {
        if (wxNOT_FOUND != no_good.Find(str->GetChar(i)))
        {
            str->SetChar(i, '_');
        }
    }
}

static int 
fprintf_impl(FILE* stream, const char* fmt, ...)
{
    va_list args;
    char sz[512];

    va_start(args, fmt);
#ifdef _MSC_VER
    // vsnprintf not declared in MSVC6
    const int len = _vsnprintf(sz, sizeof(sz), fmt, args);
#else
    const int len = vsnprintf(sz, sizeof(sz), fmt, args);
#endif
    va_end(args);
    bool ok = (len && (((wxOutputStream*)stream)->Write(sz, len).LastWrite() == (size_t)len));
    return ok ? len : 0;
}

bool wxXBMHandler::SaveFile(wxImage* image, wxOutputStream& stream, bool WXUNUSED(verbose) )
{
    const unsigned char color_threshold = 128;
    const size_t bytes_per_line = 12;
    wxString sName = wxT("xbm");

    if (image->HasOption(wxIMAGE_OPTION_FILENAME))
    {
        wxSplitPath(image->GetOption(wxIMAGE_OPTION_FILENAME), NULL, &sName, NULL);
    }
    c_syntax_fixup(&sName);
    XBM_STRUCT xbm;
    xbm.bits   = image->GetData();
    xbm.width  = image->GetWidth();
    xbm.height = image->GetHeight();
    wxOutputStream* stream_ptr = &stream;
    return ::xbm_save(fprintf_impl, (FILE*)stream_ptr, &xbm, sName.mb_str(), color_threshold, bytes_per_line);
}

////////////////////////////////////////////////////////////////////////////

 	  	 
