// A program to test wxMBConvUTF*

#include <wx/wx.h>
#include <iostream>
#include <iomanip>

void dump_wxString(std::string name, const wxString& str)
{
    std::cout << name << ": " << std::flush;
    std::wstring ws = str.ToStdWstring();
    for (wchar_t c : ws) {
        std::cout << std::hex << std::setw(4) << std::setfill('0') << static_cast<unsigned int>(c) << " ";
    }
    std::cout << std::endl;
}

void dump_mbstring(std::string name, std::string str)
{
    std::cout << name << ": ";
    for (char c : str) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(c)) << " ";
    }
    std::cout << std::endl;
}

/* wxString::mb_str() returns a wxScopedCharBuffer, which is not convertible to std::string */
void dump_mbstring(std::string name, wxScopedCharBuffer const& str)
{
    dump_mbstring(name, std::string(str.data(), str.length()));
}


int main()
{
    // U+1F363 (UTF-16: D83C DF63, UTF-8: F0 9F 8D A3) sushi (emoji)
    // U+732B (UTF-8: E7 8C AB) cat (kanji)
    // U+1F408 (UTF-16: D83D DC08, UTF-8: F0 9F 90 88) cat (emoji)
    // U+845B U+E0101 (UTF-16: 845B DB40 DD01, UTF-8: E8 91 9B F3 A0 84 81) (kanji + IVS)
    const char u8[] =
        "\xF0\x9F\x8D\xA3" /* U+1F363 */
        "\xE7\x8C\xAB\xF0\x9F\x90\x88" /* U+732B U+1F408 */
        "\xE8\x91\x9B\xF3\xA0\x84\x81"; /* U+845B U+E0101 */
    size_t u8_len = 18;
    const wxChar16 u16[] = {
        0xD83C, 0xDF63,
        0x732B, 0xD83D, 0xDC08,
        0x845B, 0xDB40, 0xDD01,
        0};
    size_t u16_len = 8;
    const wxChar32 u32[] = {
        0x1F363,
        0x732B, 0x1F408,
        0x845B, 0xE0101,
        0};
    size_t u32_len = 5;
#if SIZEOF_WCHAR_T == 2
    wxString wxstr(u16, u16_len);
#else
    wxString wxstr(u32, u32_len);
#endif

    {
        /* Test UTF-8 conversion */
        std::cout << "UTF-8 -> WChar:" << std::endl;
        dump_wxString("Expected         ", wxstr);
        dump_wxString("wxMBConvUTF8     ", wxString(u8, wxMBConvUTF8(), u8_len));
        dump_wxString("wxMBConvUTF8(PUA)", wxString(u8, wxMBConvUTF8(wxMBConvUTF8::MAP_INVALID_UTF8_TO_PUA), u8_len));
        std::cout << std::endl;

        std::cout << "WChar -> UTF-8:" << std::endl;
        dump_mbstring("Expected         ", std::string(u8, u8_len));
        dump_mbstring("wxMBConvUTF8     ", wxstr.mb_str(wxMBConvUTF8()));
        dump_mbstring("wxMBConvUTF8(PUA)", wxstr.mb_str(wxMBConvUTF8(wxMBConvUTF8::MAP_INVALID_UTF8_TO_PUA)));
        std::cout << std::endl;
    }

    {
        /* Test UTF-16LE conversion */
        char u16le[sizeof(u16)];
        for (size_t i = 0; i < sizeof(u16)/2; ++i) {
            u16le[2*i]   = (char)(unsigned char)(u16[i] & 0xFF);
            u16le[2*i+1] = (char)(unsigned char)((u16[i] >> 8) & 0xFF);
        }

        std::cout << "UTF-16LE -> WChar:" << std::endl;
        dump_wxString("Expected       ", wxstr);
        dump_wxString("wxMBConvUTF16LE", wxString(u16le, wxMBConvUTF16LE(), sizeof(u16le)-2));
        std::cout << std::endl;

        std::cout << "WChar -> UTF-16LE:" << std::endl;
        dump_mbstring("Expected       ", std::string(u16le, sizeof(u16le)-2));
        dump_mbstring("wxMBConvUTF16LE", wxstr.mb_str(wxMBConvUTF16LE()));
        std::cout << std::endl;
    }

    {
        /* Test UTF-16BE conversion */
        char u16be[sizeof(u16)];
        for (size_t i = 0; i < sizeof(u16)/2; ++i) {
            u16be[2*i+1] = (char)(unsigned char)(u16[i] & 0xFF);
            u16be[2*i]   = (char)(unsigned char)((u16[i] >> 8) & 0xFF);
        }

        std::cout << "UTF-16BE -> WChar:" << std::endl;
        dump_wxString("Expected       ", wxstr);
        dump_wxString("wxMBConvUTF16BE", wxString(u16be, wxMBConvUTF16BE(), sizeof(u16be)-2));
        std::cout << std::endl;

        std::cout << "WChar -> UTF-16BE:" << std::endl;
        dump_mbstring("Expected       ", std::string(u16be, sizeof(u16be)-2));
        dump_mbstring("wxMBConvUTF16BE", wxstr.mb_str(wxMBConvUTF16BE()));
        std::cout << std::endl;
    }

    {
        /* Test UTF-32LE conversion */
        char u32le[sizeof(u32)];
        for (size_t i = 0; i < sizeof(u32)/4; ++i) {
            u32le[4*i]   = (char)(unsigned char)(u32[i] & 0xFF);
            u32le[4*i+1] = (char)(unsigned char)((u32[i] >> 8) & 0xFF);
            u32le[4*i+2] = (char)(unsigned char)((u32[i] >> 16) & 0xFF);
            u32le[4*i+3] = (char)(unsigned char)((u32[i] >> 24) & 0xFF);
        }

        std::cout << "UTF-32LE -> WChar:" << std::endl;
        dump_wxString("Expected       ", wxstr);
        dump_wxString("wxMBConvUTF32LE", wxString(u32le, wxMBConvUTF32LE(), sizeof(u32le)-4));
        std::cout << std::endl;

        std::cout << "WChar -> UTF-32LE:" << std::endl;
        dump_mbstring("Expected       ", std::string(u32le, sizeof(u32le)-4));
        dump_mbstring("wxMBConvUTF32LE", wxstr.mb_str(wxMBConvUTF32LE()));
        std::cout << std::endl;
    }

    {
        /* Test UTF-32BE conversion */
        char u32be[sizeof(u32)];
        for (size_t i = 0; i < sizeof(u32)/4; ++i) {
            u32be[4*i]   = (char)(unsigned char)((u32[i] >> 24) & 0xFF);
            u32be[4*i+1] = (char)(unsigned char)((u32[i] >> 16) & 0xFF);
            u32be[4*i+2] = (char)(unsigned char)((u32[i] >> 8) & 0xFF);
            u32be[4*i+3] = (char)(unsigned char)(u32[i] & 0xFF);
        }

        std::cout << "UTF-32BE -> WChar:" << std::endl;
        dump_wxString("Expected       ", wxstr);
        dump_wxString("wxMBConvUTF32BE", wxString(u32be, wxMBConvUTF32BE(), sizeof(u32be)-4));
        std::cout << std::endl;

        std::cout << "WChar -> UTF-32BE:" << std::endl;
        dump_mbstring("Expected       ", std::string(u32be, sizeof(u32be)-4));
        dump_mbstring("wxMBConvUTF32BE", wxstr.mb_str(wxMBConvUTF32BE()));
        std::cout << std::endl;
    }
}
