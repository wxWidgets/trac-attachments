#include "app.h"

bool App::OnInit() {
	MyFrame1 *mainFrame = new MyFrame1();
	mainFrame->Show();
	SetTopWindow(mainFrame);

	return TRUE;
}

int App::OnExit() {
	return 0;
}

IMPLEMENT_APP(App)

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : 
	wxFrame( parent, id, title, pos, size, style )
{
	tree = new MyTree(this);
	
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(tree, 1, wxEXPAND);
	SetSizer(sizer);

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->Centre( wxBOTH );
}

void MyTree::onLeftDown(wxMouseEvent &evt)
{
	state = DRAG_START;
}

void MyTree::onMouseMotion(wxMouseEvent &evt)
{
	this;
	wxPoint evtPos = evt.GetPosition();
	MyTree *mt = (MyTree*)evt.GetEventObject();
	wxTreeItemId itemHovered = HitTest(evtPos);

	// switch to dragging mode if mouseDown was on item
	if (state == DRAG_START){
		itemDragging = HitTest(evtPos);
		if (itemDragging){
			// create dragImage
			if (dragImg)
				delete dragImg;
			dragImg = new wxDragImage(this, itemDragging);

			// position the dragImage right on top of the dragged item and
			// start dragging
			wxRect rect;
			GetBoundingRect(itemDragging, rect, true);
			dragImg->BeginDrag(evtPos - rect.GetLeftTop(), this);
			dragImg->Show();

			state = DRAGGING;
		}
		else
			state = DRAG_NONE;
	}

	// show markers only when dragging over an item
	bool showMarkers = state == DRAGGING && itemHovered && itemHovered != GetRootItem();
	posMarkerLeft->Show(showMarkers);
	posMarkerRight->Show(showMarkers);

	if (showMarkers){
		dragImg->Hide();

		wxRect rect;
		GetBoundingRect(itemHovered, rect, true);

		if (evtPos.y > rect.GetTop() + rect.GetHeight() / 2){
			// below
			posMarkerLeft->SetPosition(rect.GetBottomLeft() - wxPoint(7, 3));
			posMarkerRight->SetPosition(rect.GetBottomRight() - wxPoint(0, 3));
		}
		else {
			// above
			posMarkerLeft->SetPosition(rect.GetTopLeft() - wxPoint(7, 3));
			posMarkerRight->SetPosition(rect.GetTopRight() - wxPoint(0, 3));
		}

		mt->Refresh(false);
		mt->Update();

		dragImg->Show();
		dragImg->Move(evtPos);
	}
}

void MyTree::onLeftUp(wxMouseEvent &evt)
{
	wxPoint evtPos = evt.GetPosition();
	wxTreeItemId itemUnderMouse = HitTest(evtPos), previous;

	if (itemUnderMouse && itemUnderMouse != GetRootItem()){
		wxRect rect;
		GetBoundingRect(itemUnderMouse, rect, true);

		if (evtPos.y > rect.GetTop() + rect.GetHeight() / 2){
			// below
			previous = itemUnderMouse;
		}
		else {
			// above
			previous = GetPrevSibling(itemUnderMouse);
		}

		InsertItem(GetRootItem(), previous, GetItemText(itemDragging));
		Delete(itemDragging);
	}

	if (dragImg)
		endDragging();
}
