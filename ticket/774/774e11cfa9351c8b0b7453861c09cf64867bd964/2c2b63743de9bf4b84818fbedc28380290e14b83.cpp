
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/xrc/xmlres.h"
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include "wx/renderer.h"
#include "wx/listctrl.h"
#include "wx/grid.h"
#include "wx/event.h"

using namespace std;

static wxString GetAppRunDirectory()
{
    wxString directory(wxTheApp->argv[0]);
    directory.Replace(wxT("\\"), wxT("/"));
    wxString str = directory.BeforeLast('/');
    if(str.IsEmpty())
    {
      return wxT(".");
    }
    return directory.BeforeLast('/');
}

static wxString GetInstallDirectory()
{
	wxString directory = GetAppRunDirectory();
#ifdef __QXWIN32__
    return directory.BeforeLast('/');
#else
    return directory;
#endif
}

class DhPhotoCheckCellRender: public wxGridCellRenderer
{
public:
	DhPhotoCheckCellRender()
	{
		is_checked_ = 0;
		bitmap_ = NULL;
		check_offset_x_ = 2;
		check_offset_y_ = 120;
		is_check_center_ = false;
	}
	~DhPhotoCheckCellRender()
	{

	}

	inline void SetShowBitmap(wxBitmap* bitmap)
	{
		bitmap_ = bitmap;
	}
	inline void SetShowText(const wxString& text)
	{
		text_ = text;
	}

	// draw a check mark or nothing
	virtual void Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc,
			const wxRect& rect, int row, int col, bool isSelected);

	// return the checkmark size
	virtual wxSize GetBestSize(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc,
			int row, int col);

	virtual DhPhotoCheckCellRender *Clone() const
	{
		return new DhPhotoCheckCellRender;
	}

	inline void ChangeCheckState()
	{
		is_checked_ = !is_checked_;
	}

	inline void Check(bool is_check)
	{
		is_checked_ = is_check;
	}

	inline void CenterCheckOffset()
	{
		is_check_center_ = true;
	}

	inline bool IsChecked()
	{
		return is_checked_;
	}

private:
	wxBitmap* bitmap_;
	wxString text_;

	int check_offset_x_;
	int check_offset_y_;
	bool is_check_center_;

	static wxSize ms_sizeCheckMark;
	int is_checked_;
};

wxSize DhPhotoCheckCellRender::ms_sizeCheckMark;

wxSize DhPhotoCheckCellRender::GetBestSize(wxGrid& grid,
		wxGridCellAttr& WXUNUSED(attr), wxDC& WXUNUSED(dc), int WXUNUSED(row),
		int WXUNUSED(col))
{
	// compute it only once (no locks for MT safeness in GUI thread...)
	if (!ms_sizeCheckMark.x)
	{
		ms_sizeCheckMark = wxRendererNative::Get().GetCheckBoxSize(&grid);
	}
	return ms_sizeCheckMark;
}

void DhPhotoCheckCellRender::Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc,
		const wxRect& rect, int row, int col, bool isSelected)
{
	wxGridCellRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

	static const wxSize kCheckSize = wxRendererNative::Get().GetCheckBoxSize(
			NULL);

	wxRect rect_check = rect;
	rect_check.x = rect_check.x + check_offset_x_;
	if (is_check_center_)
	{
		rect_check.y = rect_check.y + (rect.height - kCheckSize.y) / 2;
	}
	else
	{
		rect_check.y = rect_check.y + check_offset_y_;
	}
	rect_check.width = kCheckSize.x;
	rect_check.height = kCheckSize.y;
	if (is_checked_)
	{
		wxRendererNative::Get().DrawCheckBox(&grid, dc, rect_check, wxCONTROL_CHECKED);
	}else
	{
		wxRendererNative::Get().DrawCheckBox(&grid, dc, rect_check, 0);
	}
}



class MyFrame : public wxFrame
{
public:
    MyFrame( wxWindow* parent=(wxWindow *)NULL);
    ~MyFrame();
    virtual void Init();
	void        DoWork();
	void RefreshAppointCell(wxGrid* grid,int current_row, int drawprogress_column);
	void OnImageCheckClick(wxGridEvent& event);

protected:
  void OnLoadGrid(wxCommandEvent& evt);


private:
    DECLARE_EVENT_TABLE()
    wxListCtrl* list_;
    wxGrid* grid_;
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual int OnExit();
};

IMPLEMENT_APP(MyApp)



// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
	if (!wxApp::OnInit())
	{
		return false;
	}

  wxInitAllImageHandlers();
  wxXmlResource::Get()->InitAllHandlers();
  
  wxString ui_dir = GetInstallDirectory()+wxT("/Themes");
  wxXmlResource::Get()->LoadAllFiles(ui_dir);

  MyFrame *frame = new MyFrame(NULL);
  bool loaded = wxXmlResource::Get()->LoadFrame(frame, NULL, "MyFrame1");
  assert(loaded);
  frame->Init();
  frame->Show(true);

  return true;
}

int MyApp::OnExit()
{
	return 0;
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
END_EVENT_TABLE()

void MyFrame::Init()
{
   grid_ = XRCCTRL(*this, "m_grid1", wxGrid);
   

   XRCCTRL(*this, "m_button2", wxButton)->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(MyFrame::OnLoadGrid), this, XRCID("m_button2"));


   grid_->CreateGrid(0, 0);
   grid_->SetColLabelSize(12);
   grid_->SetRowLabelSize(50);
   grid_->SetDefaultRowSize(36);
   grid_->SetScrollLineX(1);
   grid_->SetCellHighlightPenWidth(0);
   grid_->SetSelectionMode(wxGrid::wxGridSelectRows);
   grid_->SetUseNativeColLabels(true);


   grid_->AppendCols();
   grid_->SetColLabelValue(0, wxT("TitleName"));
   grid_->SetColSize(0, 100);
   grid_->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

   grid_->AppendCols();
   grid_->SetColLabelValue(1, wxT("TitleAddress"));
   grid_->SetColSize(1, 100);
   grid_->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

   grid_->AppendCols();
   grid_->SetColLabelValue(2, wxT("TitleBoy"));
   grid_->SetColSize(2, 100);
   grid_->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

   grid_->AppendCols();
   grid_->SetColLabelValue(3, wxT("TitleGirl"));
   grid_->SetColSize(3, 100);
   grid_->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

   grid_->AppendCols();
   grid_->SetColLabelValue(4, wxT("TitleFather"));
   grid_->SetColSize(4, 100);
   grid_->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

   grid_->Connect(wxEVT_GRID_SELECT_CELL,
			wxGridEventHandler(MyFrame::OnImageCheckClick), NULL,
			this);


}

void MyFrame::RefreshAppointCell(wxGrid* grid,int current_row, int drawprogress_column)
{
	wxRect rect = grid->CellToRect(current_row, drawprogress_column);
	if (rect.IsEmpty())
	{
		return;
	}
	int xx = 0, yy = 0;
	grid->CalcScrolledPosition(rect.x, rect.y, &xx, &yy);
	rect.x = xx;
	rect.y = yy;
	grid->GetTargetWindow()->RefreshRect(rect);
}


void MyFrame::OnImageCheckClick(wxGridEvent& event)
{
	int row = event.GetRow();
	int col = event.GetCol();

	if (!col)
	{
		wxObject *obj = event.GetEventObject();
		wxGrid* grid = (wxGrid*) obj;
		DhPhotoCheckCellRender* render =
				(DhPhotoCheckCellRender*) grid->GetCellRenderer(row,col);
		render->DecRef();
		render->ChangeCheckState();
		RefreshAppointCell(grid,event.GetRow(), event.GetCol());
		return;
	}
}

MyFrame::MyFrame(wxWindow* parent)
{

}

MyFrame::~MyFrame()
{
}

void MyFrame::DoWork()
{
	if(grid_->GetNumberRows())
	{
		grid_->DeleteRows(0,grid_->GetNumberRows());
	}
   
   for (int i = 0; i < 200; ++i)
   {
     wxString str;
     str.Printf(wxT("%d"),i);
     grid_->InsertRows(i,1,false);
     
     //name
     grid_->SetCellAlignment(wxALIGN_LEFT, i, 0);
	 DhPhotoCheckCellRender *render = new DhPhotoCheckCellRender();
	 render->SetShowText(wxT("name"));
	 render->CenterCheckOffset();

	 grid_->SetCellRenderer(i,0,render);
     grid_->SetReadOnly(i, 0, true);
     grid_->SetCellValue(i, 0, wxT("  "));

      //backup_date
     grid_->SetCellAlignment(wxALIGN_LEFT, i, 1);
     grid_->SetReadOnly(i, 1, true);
     grid_->SetCellValue(i, 1, wxT("address"));

	 grid_->SetCellAlignment(wxALIGN_LEFT, i, 2);
     grid_->SetReadOnly(i, 2, true);
     grid_->SetCellValue(i, 2, wxT("boy"));

	 grid_->SetCellAlignment(wxALIGN_LEFT, i, 3);
     grid_->SetReadOnly(i, 3, true);
     grid_->SetCellValue(i, 3, wxT("girl"));

	 grid_->SetCellAlignment(wxALIGN_LEFT, i, 4);
     //grid_->SetReadOnly(i, 4, true);
     grid_->SetCellValue(i, 4, wxT("father"));
   }

   
}

void MyFrame::OnLoadGrid(wxCommandEvent& evt)
{
   cout << "OnLoadGrid: " << endl;

   for(int j = 0 ; j < 100 ; ++j)
   {
		DoWork();
   }
   
}

