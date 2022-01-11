/* 
 * $Log: wxWidgetsWxGridAutoSizeCrash.cxx,v $
 * Revision 1.3  2006/10/06 10:12:48  bachmap3
 * Again changed format of CVS log comment.
 *
 * Revision 1.2  2006/10/06 10:11:03  bachmap3
 * Changed format of CVS log comment.
 *
 * Revision 1.1  2006/10/06 10:09:10  bachmap3
 * This project shows an issue with either wxWidgets or the code itself. See the comment in the main implementation file for configuration information.
 */

static char rcsid_[]="$Id: wxWidgetsWxGridAutoSizeCrash.cxx,v 1.3 2006/10/06 10:12:48 bachmap3 Exp $";

/**
 * With wxWidgets-2.7.0 (configured with
 * "--with-msw --enable-debug --enable-debug_gdb --disable-precomp-headers --disable-unicode --enable-std_iostreams"),
 * Cygwin-1.5.18-1 (which comes with g++-3.4.4), MS Windows XP SP2 the following code throws a failed assertion within the
 * call to "wxGrid::AutoSize()":
 * "warning: 11:18:33: ../include/wx/dynarray.h(809): assert "uiIndex < m_nCount" failed in Item().".
 * Clicking "Yes" soon will crash the application.
 * With gdb "wxGrid::GetColWidth()" could be narrowed down as the cause of the crash.
 * 
 * Substituting the choice cell by a simple string cell will result in no failed assertion.
 * 
 * Further configuration information:
 * "$ wx-config --cppflags --libs
 *  -I/usr/local/lib/wx/include/msw-ansi-debug-2.7 -I/usr/local/include/wx-2.7 -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES
 *  -D__WXDEBUG__ -DWXUSINGDLL -D__WXMSW__
 *  -L/usr/local/lib   -lwx_mswd_aui-2.7 -lwx_mswd_xrc-2.7 -lwx_mswd_qa-2.7 -lwx_mswd_html-2.7 -lwx_mswd_adv-2.7
 *  -lwx_mswd_core-2.7 -lwx_based_xml-2.7 -lwx_based_net-2.7 -lwx_based-2.7"
 */

#include <wx/wx.h>
#include <wx/grid.h>

struct wxWidgetsWxGridAutoSizeCrash : public wxApp
{
	bool OnInit();
};

class GridFrame : public wxFrame {
	DECLARE_EVENT_TABLE()
public:
	explicit GridFrame(const wxString &);
};


using namespace std;

bool wxWidgetsWxGridAutoSizeCrash::OnInit()
{
	if(!wxApp::OnInit())
		return false;

	wxFrame *const frame=new GridFrame(_T("AutoSize"));
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}

BEGIN_EVENT_TABLE(GridFrame, wxFrame)
END_EVENT_TABLE()

GridFrame::GridFrame(const wxString &title) : wxFrame(0,wxID_ANY,title)
{
	wxGrid *const grid=new wxGrid(this,wxID_ANY);
	grid->CreateGrid( 1, 1 );
	
	{
		const wxString choice[] =
			{
				_T("Please select a choice"),
				_T("This takes two cells"),
				_T("Another choice"),
			};
		grid->SetCellEditor(0, 0, new wxGridCellChoiceEditor(WXSIZEOF(choice), choice));
		grid->SetCellSize(0, 0, 1, 2);
		grid->SetCellValue(0, 0, choice[0]);
		grid->SetCellOverflow(0, 0, false);
	}
	
	grid->AutoSize();
}

IMPLEMENT_APP(wxWidgetsWxGridAutoSizeCrash)

 	  	 
