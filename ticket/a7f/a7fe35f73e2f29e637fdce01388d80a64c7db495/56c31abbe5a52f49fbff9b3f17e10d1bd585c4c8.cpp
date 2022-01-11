void wxWindowGTK::SetFocus()
{
    wxCHECK_RET( m_widget != NULL, wxT("invalid window") );

    // Setting "physical" focus is not immediate in GTK+ and while
    // gtk_widget_is_focus ("determines if the widget is the focus widget
    // within its toplevel", i.e. returns true for one widget per TLW, not
    // globally) returns true immediately after grabbing focus,
    // GTK_WIDGET_HAS_FOCUS (which returns true only for the one widget that
    // has focus at the moment) takes effect only after the window is shown
    // (if it was hidden at the moment of the call) or at the next event loop
    // iteration.
    //
    // Because we want to FindFocus() call immediately following
    // foo->SetFocus() to return foo, we have to keep track of "pending" focus
    // ourselves.

    gs_pendingFocus = this;

    GtkWidget *widget = m_wxwindow ? m_wxwindow : m_focusWidget;

    if ( GTK_IS_CONTAINER(widget) &&
         !gtk_widget_get_can_focus(widget) )
    {
        wxLogTrace(TRACE_FOCUS,
                   wxT("Setting focus to a child of %s(%p, %s)"),
                   GetClassInfo()->GetClassName(), this, GetLabel().c_str());

        // It would be nice if we could use gtk_container_get_focus_child()
        // but it does not exist in older versions of GTK.
        GtkWidget *child = ((GtkContainer *)widget)->focus_child;
        if (child)
        {
            gtk_widget_grab_focus(child);
        }
        else
        {
            gtk_widget_child_focus(widget, GTK_DIR_TAB_FORWARD);
        }
    }
    else
    {
        wxLogTrace(TRACE_FOCUS,
                   wxT("Setting focus to %s(%p, %s)"),
                   GetClassInfo()->GetClassName(), this, GetLabel().c_str());
        gtk_widget_grab_focus(widget);
    }
}
