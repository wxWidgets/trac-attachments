# import wxPython
import wx

print "wx version:", wx.version()


if __name__ == '__main__':
    __builtins__._ = wx.GetTranslation


# Import Python's os and sys modules
import os, sys


class UsernameandPassword(wx.Dialog):
    """ Username, Password, Database Server, and Database Name Dialog """
    def __init__(self, parent):
        """ This is the Username, Password, Database Server, and Database Name Dialog """
        # For single-user Transana, all we need it the Database Name.  For multi-user Transana,
        # we need UserName, Password, Database Server, and Database Name.

        # First, let's set up some variables depending on whether we are in single-user or multi-user
        # mode.
        # Dialog Title
        dlgTitle = _("Username and Password")

        # Define the main Dialog Box
        wx.Dialog.__init__(self, parent, -1, dlgTitle, style=wx.CAPTION | wx.RESIZE_BORDER)

        # To look right, the Mac needs the Small Window Variant.
        if "__WXMAC__" in wx.PlatformInfo:
            self.SetWindowVariant(wx.WINDOW_VARIANT_SMALL)

        # Create a BoxSizer for the main elements to go onto the Panel
        box = wx.BoxSizer(wx.VERTICAL)

        # Place a Panel on the Dialog Box.  All Controls will go on the Panel.
        # (Panels can have DefaultItems, enabling the desired "ENTER" key functionality.
        panel = wx.Panel(self, -1, name='UserNamePanel')

        # Let's use a FlexGridSizer for the data entry fields.
        # for MU, we want 5 rows with 2 columns
        box2 = wx.FlexGridSizer(5, 2, 6, 0)
        # We want to be flexible horizontally
        box2.SetFlexibleDirection(wx.HORIZONTAL)
        # We want the data entry fields to expand
        box2.AddGrowableCol(1)

        # Username Label        
        lblUsername = wx.StaticText(panel, -1, _("Username:"))

        # User Name TextCtrl
        self.txtUsername = wx.TextCtrl(panel, -1, style=wx.TE_LEFT)

        # Host / Server Label
        lblDBServer = wx.StaticText(panel, -1, _("Server:"))

        choicelist = ['']
           
        # Host / Server Combo Box, with a list of servers from the Databases Object if appropriate
        self.chDBServer = wx.ComboBox(panel, -1, choices=choicelist, style = wx.CB_DROPDOWN | wx.CB_SORT)

        # Set the value to the default value provided by the Configuration Data
        self.chDBServer.SetValue('')

        # Let's add the MU controls we've created to the Data Entry Sizer
        box2.AddMany([(lblUsername, 1, wx.RIGHT, 10),
                      (self.txtUsername, 2, wx.EXPAND),
                      (lblDBServer, 1, wx.RIGHT, 10),
                      (self.chDBServer, 2, wx.EXPAND)
                     ])

        # Now add the Data Entry sizer to the Main sizer
        box.Add(box2, 6, wx.EXPAND | wx.LEFT | wx.RIGHT, 10)

        # Create another sizer for the buttons, with a horizontal orientation
        box4 = wx.BoxSizer(wx.HORIZONTAL)

        # Define the "OK" button
        btnOK = wx.Button(panel, wx.ID_OK, _("OK"))

        # Define the Default Button for the dialog.  This allows the "ENTER" key
        # to fire the OK button regardless of which widget has focus on the form.
        self.SetDefaultItem(btnOK)
        
        # Define the Cancel Button
        btnCancel = wx.Button(panel, wx.ID_CANCEL, _("Cancel"))

        # Lets have some space between this button and  the others.
        box4.Add((30, 1), 1, wx.EXPAND)
        # Add the OK button to the lower right corner
        box4.Add(btnOK, 2, wx.ALIGN_RIGHT | wx.ALIGN_BOTTOM | wx.RIGHT | wx.BOTTOM, 10)
        # Add the Cancel button to the lower right corner, bumping the OK button to the left
        box4.Add(btnCancel, 2, wx.ALIGN_RIGHT | wx.ALIGN_BOTTOM | wx.RIGHT | wx.BOTTOM, 10)
        # Add the Button sizer to the main sizer
        box.Add(box4, 2, wx.EXPAND)

        # Lay out the panel and the form, request AutoLayout for both.
        panel.Layout()
        panel.SetAutoLayout(True)

        # Set the main Panel's sizer to the main sizer and "fit" it.
        panel.SetSizer(box)
        panel.Fit()

        # Let's stick the panel on a sizer to fit in the Dialog
        panSizer = wx.BoxSizer(wx.VERTICAL)
        panSizer.Add(panel, 1, wx.EXPAND)
        self.SetSizer(panSizer)
        self.Fit()

        # Lay out the dialog box, and tell it to resize automatically
        self.Layout()
        self.SetAutoLayout(True)

        # Set minimum window size
        dlgSize = self.GetSizeTuple()
        self.SetSizeHints(dlgSize[0], dlgSize[1], -1, round(dlgSize[1]))

        # Center the dialog on the screen
        self.CentreOnScreen()

        # Show the Form modally, process if OK selected        
        self.ShowModal()
        return None


if __name__ == '__main__':

    __builtins__._ = wx.GetTranslation

    class MyApp(wx.App):
        def OnInit(self):
            self.frame = UsernameandPassword(None)
            self.frame.Destroy()
            return(True)

    app = MyApp(0)
    app.MainLoop()
