void wxNativeFontInfo::SetFamily(wxFontFamily family)
{
    wxArrayString facename;

    // the list of fonts associated with a family was partially
    // taken from http://www.codestyle.org/css/font-family

    switch ( family )
    {
        case wxFONTFAMILY_SCRIPT:
            // corresponds to the cursive font family in the page linked above
            facename.Add(wxS("URW Chancery L"));
            facename.Add(wxS("Comic Sans MS"));
            break;

        case wxFONTFAMILY_DECORATIVE:
            // corresponds to the fantasy font family in the page linked above
            facename.Add(wxS("Impact"));
            break;

        case wxFONTFAMILY_ROMAN:
            // corresponds to the serif font family in the page linked above
            facename.Add(wxS("Serif"));
            facename.Add(wxS("DejaVu Serif"));
            facename.Add(wxS("DejaVu LGC Serif"));
            facename.Add(wxS("Bitstream Vera Serif"));
            facename.Add(wxS("Liberation Serif"));
            facename.Add(wxS("FreeSerif"));
            facename.Add(wxS("Luxi Serif"));
            facename.Add(wxS("Times New Roman"));
            facename.Add(wxS("Century Schoolbook L"));
            facename.Add(wxS("URW Bookman L"));
            facename.Add(wxS("URW Palladio L"));
            facename.Add(wxS("Times"));
            break;

        case wxFONTFAMILY_TELETYPE:
        case wxFONTFAMILY_MODERN:
            // corresponds to the monospace font family in the page linked above
            facename.Add(wxS("Monospace"));
            facename.Add(wxS("DejaVu Sans Mono"));
            facename.Add(wxS("DejaVu LGC Sans Mono"));
            facename.Add(wxS("Bitstream Vera Sans Mono"));
            facename.Add(wxS("Liberation Mono"));
            facename.Add(wxS("FreeMono"));
            facename.Add(wxS("Luxi Mono"));
            facename.Add(wxS("Courier New"));
            facename.Add(wxS("Lucida Sans Typewriter"));
            facename.Add(wxS("Nimbus Mono L"));
            facename.Add(wxS("Andale Mono"));
            facename.Add(wxS("Courier"));
            break;

        case wxFONTFAMILY_SWISS:
        case wxFONTFAMILY_DEFAULT:
        default:
            // corresponds to the sans-serif font family in the page linked above
            facename.Add(wxS("Sans"));
            facename.Add(wxS("DejaVu Sans"));
            facename.Add(wxS("DejaVu LGC Sans"));
            facename.Add(wxS("Bitstream Vera Sans"));
            facename.Add(wxS("Liberation Sans"));
            facename.Add(wxS("FreeSans"));
            facename.Add(wxS("Luxi Sans"));
            facename.Add(wxS("Arial"));
            facename.Add(wxS("Lucida Sans"));
            facename.Add(wxS("Nimbus Sans L"));
            facename.Add(wxS("URW Gothic L"));
            break;
    }

    SetFaceName(facename);
}
