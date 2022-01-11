/*
 * =====================================================================================
 * 
 *        Filename:  main.cpp
 * 
 *
 *     Description:  
 * 
 *         Version:  1.0
 *         Created:  17.06.2005 19:13:49 CEST
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:   (), 
 *         Company:  
 * 
 * =====================================================================================
 */

#include <iostream>
#include <ctime>
#include <wx/wx.h>

using namespace std;

class stopwatch
{
	public:

		stopwatch() : start(std::clock()),m_msg(NULL)
		{
			cout << "starting: " << m_msg << endl;
		} //start counting time
		stopwatch(const char *msg) : start(std::clock()),m_msg(msg)
		{
			cout << "starting: " << m_msg << endl;
		} //start counting time
		~stopwatch();
		clock_t getcurrent();
	private:
		std::clock_t start;
		const char *m_msg;
};


stopwatch::~stopwatch()
{
	clock_t total = clock()-start; //get elapsed time
	cout<<m_msg<<" finished:"<<endl;
	cout<<"total of ticks for this activity: "<<total<<endl;
	cout<<"in seconds: "<<double(total)/CLOCKS_PER_SEC<<endl;
}

clock_t stopwatch::getcurrent()
{
	return clock()-start;
}



class MyApp : public wxApp
{
		virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxFrame *frame = new wxFrame(NULL, -1, "Mandelbrot",
	                             wxPoint(10,10), wxSize(720,576));
	frame->Show(true);
	wxClientDC dc(frame);
	frame->SetBackgroundColour( *wxWHITE );
	dc.Clear();
	dc.SetPen( *wxBLACK_PEN );
	dc.SetBrush( *wxBLACK_BRUSH );
	wxPoint pt[4];
	pt[0].x = 100;
	pt[0].y = 200;
	pt[1] = pt[0] + wxPoint( 14, 0 );
	pt[2] = pt[1] + wxPoint( 1, -10 );
	pt[3] = pt[2] + wxPoint( -10, 0 );

	for (int i = 0 ; i < 3; ++i) {
		{
			stopwatch sw("polyline");
			for (int i = 0; i != 1000000; ++i) {
				dc.SetBrush( *wxBLUE_BRUSH );
				dc.DrawLines(4,pt);
			}
		}
		{
			stopwatch sw("polyline untransformed");
			for (int i = 0; i != 1000000; ++i) {
				dc.SetBrush( *wxBLUE_BRUSH );
				dc.DrawLines_untransformed(4,pt);
			}
		}
		{
			stopwatch sw("polygons");
			for (int i = 0; i != 1000000; ++i) {
				dc.SetBrush( *wxBLUE_BRUSH );
				dc.DrawPolygon(4,pt);
			}
		}
		{
			stopwatch sw("polygons untransformed");
			for (int i = 0; i != 1000000; ++i) {
				dc.SetBrush( *wxBLUE_BRUSH );
				dc.DrawPolygon_untransformed(4,pt);
			}
		}
	}
	exit(0);
	return true;
}

 	  	 
