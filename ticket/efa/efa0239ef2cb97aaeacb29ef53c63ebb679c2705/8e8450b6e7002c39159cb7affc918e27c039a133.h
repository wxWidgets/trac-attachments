#include "wx/osx/private.h"

#define iappurl "com.apple.itunes.iappurl"

class ITunesFileDataObject : public wxFileDataObject
{
public:
    ITunesFileDataObject() {}
    
    virtual void AddSupportedTypes( void* cfarray)
    {
        CFArrayAppendValue((CFMutableArrayRef)cfarray, CFSTR(iappurl));
        wxFileDataObject::AddSupportedTypes(cfarray);
    }
    
    virtual size_t GetFormatCount(Direction dir) const
    {
        int nFormats = wxFileDataObject::GetFormatCount(dir);
        
        if ( dir == Set )
            nFormats += 1;

        return nFormats;
    }
    
    virtual void GetAllFormats(wxDataFormat *formats, Direction dir) const
    {
        if ( dir == Set )
            *formats++ = wxDataFormat(iappurl);
            
        wxFileDataObject::GetAllFormats(formats);
    }
    
    virtual bool SetData(const wxDataFormat&format , size_t len, const void *buf)
    {
        if ( format.GetType() == wxDF_PRIVATE && format.GetId() == iappurl )
        {
            while (len > 0  &&  ((char*)buf)[len - 1] == 0)
                --len;
            
            wxCFRef<CFURLRef> url(CFURLCreateWithBytes( kCFAllocatorDefault, (const UInt8*)buf, len, kCFStringEncodingUTF8, NULL ));
            wxCFStringRef cfString(CFURLCopyFileSystemPath( url, kCFURLPOSIXPathStyle));
            wxString path = wxCFStringRef::AsStringWithNormalizationFormC(cfString);
            AddFile(path);
            return true;
        }
        else
            return wxFileDataObject::SetData(format, len, buf);
    }
};
