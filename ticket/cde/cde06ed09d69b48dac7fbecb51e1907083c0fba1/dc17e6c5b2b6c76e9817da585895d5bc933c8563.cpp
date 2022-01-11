void wxHtmlWindow::CreateLayout()
{
	int ClientWidth, ClientHeight;
		
	if(m_Cell != NULL)
	{
		if(m_Style & wxHW_SCROLLBAR_NEVER)
		{
			SetScrollbars(wxHTML_SCROLL_STEP, 1, m_Cell->GetWidth() / wxHTML_SCROLL_STEP, 0);
			GetClientSize(&ClientWidth, &ClientHeight);
			m_Cell->Layout(ClientWidth);
		}
		else
		{
			GetClientSize(&ClientWidth, &ClientHeight);
			m_Cell->Layout(ClientWidth);
			if(ClientHeight < m_Cell->GetHeight() + GetCharHeight())
			{
				// Line added to prevent the loss of the scroll position -------
				int ScrollX, ScrollY;
				CalcUnscrolledPosition(0, 0, &ScrollX, &ScrollY);
				// -------------------------------------------------------------

				SetScrollbars(wxHTML_SCROLL_STEP, wxHTML_SCROLL_STEP, m_Cell->GetWidth() / wxHTML_SCROLL_STEP, (m_Cell->GetHeight() + GetCharHeight()) / wxHTML_SCROLL_STEP, ScrollX / wxHTML_SCROLL_STEP, ScrollY / wxHTML_SCROLL_STEP);
			}
			else /* we fit into window, no need for scrollbars */
			{
				SetScrollbars(wxHTML_SCROLL_STEP, 1, m_Cell->GetWidth() / wxHTML_SCROLL_STEP, 0); // disable...
				GetClientSize(&ClientWidth, &ClientHeight);
				m_Cell->Layout(ClientWidth); // ...and relayout
			}
		}
	}
}

 	  	 
