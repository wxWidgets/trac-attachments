#include<wx/wx.h>
#include<wx/bitmap.h>
#include<wx/dcmemory.h>

class MyApp: public wxApp
{
	public:
		virtual bool OnInit()
		{
			wxDisableAsserts();
			wxApp::OnInit();
			wxInitAllImageHandlers();
			wxBitmap bmp(100,100,1);
			wxMemoryDC dc(bmp);
#if 1
			dc.SetBackground(*wxBLACK_BRUSH);
			dc.SetTextForeground(*wxWHITE);
			dc.SetTextBackground(*wxBLACK);
#else
			dc.SetBackground(*wxWHITE_BRUSH);
			dc.SetTextForeground(*wxBLACK);
			dc.SetTextBackground(*wxWHITE);
#endif

			wxFont font(75,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL);
			dc.Clear();
			dc.SetFont(font);
			dc.DrawText("A",0,0);
			bmp.SaveFile(wxString("test.png"),wxBITMAP_TYPE_PNG);
			return false;
		};
};

IMPLEMENT_APP(MyApp)
