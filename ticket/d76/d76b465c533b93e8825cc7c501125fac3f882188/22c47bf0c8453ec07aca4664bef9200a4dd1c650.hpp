#ifndef WXSVGFILEDCWITHCLIPPING_HPP
#define WXSVGFILEDCWITHCLIPPING_HPP

#include <wx/dcsvg.h>

class WXDLLIMPEXP_FWD_CORE wxSVGFileDCWithClipping;

class WXDLLIMPEXP_CORE wxSVGFileDCWithClippingImpl : public wxSVGFileDCImpl
{
public:
	wxSVGFileDCWithClippingImpl( wxSVGFileDCWithClipping *owner, const wxString &filename,
					 int width=320, int height=240, double dpi=72.0 )
		: wxSVGFileDCImpl((wxSVGFileDC*)owner,filename,width,height,dpi)
	{
		itsClipCtr = 0;
	}

	virtual ~wxSVGFileDCWithClippingImpl() {}


	void DoSetClippingRegion(int x,  int y, int width, int height)
	{
		itsClipCtr++;

		wxString str;
		str << "</g> <!-- SJB end previous group -->\n"
			<< "<defs>\n"
			<< "<clipPath id=\"clip" << itsClipCtr << "\">\n"
			<< "<rect id=\"cliprect" << itsClipCtr << "\" x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\" style=\"stroke: gray; fill: none;\"/>\n"
			<< "</clipPath>\n"
			<< "</defs>\n"
			<< "<g style=\"clip-path: url(#clip" << itsClipCtr << ");\"> <!-- SJB group for clipped objects -->\n"
			<< "<g> <!-- SJB to counteract end group that is added below by wxSVGFileDCImpl -->\n";
		write(str);
	}

	void DestroyClippingRegion(void)
	{
		wxString str;
		str << "</g> <!-- SJB end group for clipped objects -->\n";
		write(str);
	}

private:
	size_t itsClipCtr;
};

class WXDLLIMPEXP_CORE wxSVGFileDCWithClipping : public wxDC
{
public:
	wxSVGFileDCWithClipping(const wxString& filename,
				int width = 320,
				int height = 240,
				double dpi = 72.0)
		: wxDC(new wxSVGFileDCWithClippingImpl(this, filename, width, height, dpi)) // wxSVGFileDC(filename,width,height,dpi)
	{
	}
};

#endif // WXSVGFILEDCWITHCLIPPING_HPP
