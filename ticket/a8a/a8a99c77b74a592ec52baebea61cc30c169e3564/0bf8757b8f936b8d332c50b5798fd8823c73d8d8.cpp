// Connected to the event in wxListCtrl
void TreeListView::OnBeginLabelEdit(wxListEvent& event)
{
	mEditingCancelled = false;
	if (<application allows editing>)
		mEditingLabel = true;				// Used in OnCancel to see if we were editing a label. See also comment in EndEditLabel() below.
	else
		event.Veto();
}


// Connected to the event in wxListCtrl
void TreeListView::OnEndLabelEdit(wxListEvent& event)
{
	if (event.IsEditCancelled()) { // this is true only after a user ESC press.
		event.Skip();
		mEditingLabel = false;
		return;
	}
	
	if (mEditingCancelled) {		// Caused by EndEditLabel()
		mEditingCancelled = false;
		return;
	}

	const long item = event.GetIndex();
	if (!<application allows setting the label to event.GetLabel()>)
		event.Veto();
}


// This is a function, not an event handler
bool TreeListView::OnCancel()
{
	if (mEditingLabel) {
		EndEditLabel(true);
		Refresh();
		SetFocus();					// Restores the look of the control to "non-editing" mode (this almost always works)
		return true;
	}
	else
		return false;
}

// This is the ugly bit: The surrounding dialog must have a call to the
// OnCancel of the tree list to see if the oncancel was for the label
// edit control! The Skip() not executed in this case prevents further
// processing from closing the dialog. This is necessary as the esc to
// wxID_CANCEL message mapping is not performed by wxListCtrl, only by
// wxFrame (I think). This is what needs to be fixed inside wxWidgets
// of course.
void SetupDialog::OnCancel(wxCommandEvent& event)
{
	if (mTree->OnCancel())			// Special ESC of label edit handler.
		return;
	
	event.Skip();
	RemovePanel();
}


// Implementation of EndEditLabel which hides the inferior one in
// wxListCtrl.
void TreeListView::EndEditLabel(bool cancel)
{
	mEditingCancelled = cancel;
	if (mEditingLabel) {
		wxWindow* w = GetEditControl();
		if (w != NULL)
			w->UnsubclassWin();				// IMPORTANT: This is what fixes the problems with getting rid of the editing control!

		wxListView::EndEditLabel(false);
		Refresh();
		mEditingLabel = false;		// Must reset it here as an ESC after NOT changing the label does not cause a call to EndLabelEdit.
	}
}


