void RocGuiFrame::OnCellLeftClick( wxGridEvent& event ){
  if( event.GetEventObject() == m_ActiveLocs || event.GetEventObject() == NULL ) {
    m_iLcRowSelection = event.GetRow();
    m_ActiveLocs->SelectRow(event.GetRow());
    m_ActiveLocs->MakeCellVisible( event.GetRow(), 0 );
    wxString str = m_ActiveLocs->GetCellValue( event.GetRow(), 0 );
    StrOp.free(m_LocID);
    m_LocID = StrOp.dup((const char*)str.mb_str(wxConvUTF8));
    TraceOp.trc( "frame", TRCLEVEL_DEBUG, __LINE__, 9999, "OnCellLeftClick %s", (const char*)str.mb_str(wxConvUTF8) );
    iONode lc = findLoc(str.mb_str(wxConvUTF8));

    // Dispatching Throttle in the mode column if dispatchmode is on
    if( event.GetCol() == LOC_COL_MODE && wGui.isdispatchmode( m_Ini )) {
      OnLocDispatch( event);
    }
    // TODO: Block if the event is not initiated from the mouse.
    //else if( event.GetCol() == LOC_COL_ID && event.GetEventType() == wxEVT_LEFT_DOWN  ) {
    // 10217 seems to be the mouse event
    else if( !m_FakeLeftClick && event.GetCol() == LOC_COL_ID && lc != NULL ) {
      TraceOp.trc( "frame", TRCLEVEL_INFO, __LINE__, 9999, "D&D eventtype [%d]", event.GetEventType() );

      wxString my_text = _T("moveto:")+wxString(wLoc.getid(lc),wxConvUTF8)+_T("::");
      TraceOp.trc( "frame", TRCLEVEL_INFO, __LINE__, 9999, "D&D text [%s]", (const char*)my_text.mb_str(wxConvUTF8) );
      wxTextDataObject my_data(my_text);
      wxDropSource dragSource( this );
      dragSource.SetData( my_data );
      wxDragResult result = dragSource.DoDragDrop(wxDrag_CopyOnly);
    }

    m_LC->setLocProps( lc );
    m_CV->setLocProps( lc );

    if( lc != NULL ) {
      wxCommandEvent event( wxEVT_COMMAND_MENU_SELECTED, UPDATE_LOC_IMAGE_EVENT );
      event.SetClientData( NodeOp.base.clone( lc ) );
      wxPostEvent( this, event );
    }

  }
  else {
    if(m_CV!=NULL)
      m_CV->OnGrid( event );
  }

  m_FakeLeftClick = false;

  event.Skip(true);
}



