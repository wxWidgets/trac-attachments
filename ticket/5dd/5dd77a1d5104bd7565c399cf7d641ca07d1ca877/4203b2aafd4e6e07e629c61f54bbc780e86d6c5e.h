#ifndef __app_h__
#define __app_h__

#include <wx/treectrl.h>
#include <wx/dragimag.h>
#include <wx/dcbuffer.h>

// little red arrow to the left/right to mark the drag position
class PositionMarker : public wxPanel {
public:
	PositionMarker(wxWindow *par, bool isRight) : 
			wxPanel(par, wxID_ANY, wxDefaultPosition, wxSize(7, 7)){
		Connect(wxEVT_PAINT, wxPaintEventHandler(PositionMarker::onPaint));

		if (isRight){
			points[0] = wxPoint(7, 0);
			points[1] = wxPoint(7, 7);
			points[2] = wxPoint(0, 3);
		}
		else {
			points[0] = wxPoint(0, 0);
			points[1] = wxPoint(7, 3);
			points[2] = wxPoint(0, 7);
		}
	}
private:
	void onPaint(wxPaintEvent &evt){
		wxBufferedPaintDC dc(this);
		dc.SetBrush(*wxWHITE_BRUSH);
		dc.SetPen(*wxTRANSPARENT_PEN);
		dc.DrawRectangle(wxPoint(0, 0), GetClientSize());

		// draw arrow
		dc.SetBrush(*wxRED_BRUSH);
		dc.DrawPolygon(3, points);
	}

	wxPoint points[3] = {};
};

// custom wxTreeCtrl for handling the mouse events
class MyTree : public wxTreeCtrl {
public:
	// this is to separate a single click on an item from
	// dragging so that dragging only really starts in EVT_MOTION
	typedef enum {
		DRAG_NONE,
		DRAG_START,
		DRAGGING
	} TDragState;

	MyTree(wxWindow *par) : wxTreeCtrl(par, wxID_ANY, wxDefaultPosition, wxSize(200, -1),
		wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_EDIT_LABELS){
		Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(MyTree::onLeftDown));
		Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MyTree::onLeftUp));
		Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(MyTree::onLeaveWindow));
		Connect(wxEVT_MOTION, wxMouseEventHandler(MyTree::onMouseMotion));

		AddRoot(_("root"));
		AppendItem(GetRootItem(), _("one"));
		AppendItem(GetRootItem(), _("two"));
		AppendItem(GetRootItem(), _("three"));
		AppendItem(GetRootItem(), _("four"));
		AppendItem(GetRootItem(), _("five"));
		Expand(GetRootItem());

		posMarkerLeft = new PositionMarker(this, false);
		posMarkerLeft->Hide();
		posMarkerRight = new PositionMarker(this, true);
		posMarkerRight->Hide();
	}
	~MyTree(){
		delete posMarkerLeft;
		delete posMarkerRight;
	}

	// two red arrows to mark the insert position
	PositionMarker *posMarkerLeft = nullptr, *posMarkerRight = nullptr;

	// the image of the item being dragged shown under the cursor
	wxDragImage *dragImg = nullptr;
private:
	TDragState state = DRAG_NONE;

	// the item being dragged at the moment
	wxTreeItemId itemDragging = nullptr;

	void onLeftDown(wxMouseEvent &evt);
	void onLeftUp(wxMouseEvent &evt);
	void onLeaveWindow(wxMouseEvent &evt){
		if (dragImg)
			endDragging();
	}

	// finish the drag action 
	void endDragging(){
		state = DRAG_NONE;
		dragImg->EndDrag();
		dragImg->Hide();
		if (dragImg)
			delete dragImg;
		dragImg = nullptr;
		itemDragging = nullptr;
	}

	void onMouseMotion(wxMouseEvent &evt);
};


class MyFrame1 : public wxFrame 
{
public:
	MyFrame1( wxWindow* parent = NULL, 
		wxWindowID id = wxID_ANY, 
		const wxString& title = wxEmptyString, 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxSize( 300,300 ), 
		long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

private:
	MyTree *tree = nullptr;
	
};

class App : public wxApp {
	virtual bool OnInit();
	virtual int OnExit();
};
#endif