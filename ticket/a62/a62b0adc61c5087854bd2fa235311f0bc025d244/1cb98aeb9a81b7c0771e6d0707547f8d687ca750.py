#
# 11/30/2003 - Jeff Grimmett (grimmtooth@softhome.net)
#
# o Some issues with the listbox example; I tried correcting
#   it but it's still not working the way it should. Commented
#   out for now, as I found it.
#

import  wx

havePopupWindow = 1
if wx.Platform == '__WXMAC__':
    havePopupWindow = 0
    wx.PopupWindow = wx.PopupTransientWindow = wx.Window

#---------------------------------------------------------------------------

class TestTransientPopup(wx.PopupTransientWindow):
    """Adds a bit of text and mouse movement to the wx.PopupWindow"""
    def __init__(self, parent, style, log):
        wx.PopupTransientWindow.__init__(self, parent, style)
        self.log = log
        panel = wx.Panel(self, -1)
        panel.SetBackgroundColour("#FFB6C1")
        st = wx.StaticText(panel, -1,
                          "wx.PopupTransientWindow is a\n"
                          "wx.PopupWindow which disappears\n"
                          "automatically when the user\n"
                          "clicks the mouse outside it or if it\n"
                          "(or its first child) loses focus in \n"
                          "any other way."
                          ,
                          pos=(10,10))
        sz = st.GetBestSize()
        panel.SetSize( (sz.width+20, sz.height+20) )
        self.SetSize(panel.GetSize())

    def ProcessLeftDown(self, evt):
        self.log.write("ProcessLeftDown\n")
        return False

    def OnDismiss(self):
        self.log.write("OnDismiss\n")



class TestDialog(wx.Dialog):
    def __init__(self, parent, log):
        wx.Dialog.__init__(self, parent, -1, "dlg", size=wx.DefaultSize, pos=wx.DefaultPosition, style=wx.DEFAULT_DIALOG_STYLE)
        self.log = log

        b = wx.Button(self, -1, "Show wx.PopupTransientWindow", (25, 95))
        self.Bind(wx.EVT_BUTTON, self.OnShowPopupTransient, b)

    def OnShowPopupTransient(self, evt):
        win = TestTransientPopup(self, wx.SIMPLE_BORDER, self.log)

        # Show the popup right below or above the button
        # depending on available screen space...
        btn = evt.GetEventObject()
        pos = btn.ClientToScreen( (0,0) )
        sz =  btn.GetSize()
        win.Position(pos, (0, sz[1]))

        win.Popup()

class TestPanel(wx.Panel):
    def __init__(self, parent, log):
        wx.Panel.__init__(self, parent, -1)
        self.log = log

        b = wx.Button(self, -1, "Show wx.PopupTransientWindow", (25, 95))
        self.Bind(wx.EVT_BUTTON, self.OnShowPopupTransient, b)

        b = wx.Button(self, -1, "Show dlg", (25, 240))
        self.Bind(wx.EVT_BUTTON, self.OnShowDialog, b)



    def OnShowPopupTransient(self, evt):
        win = TestTransientPopup(self, wx.SIMPLE_BORDER, self.log)

        # Show the popup right below or above the button
        # depending on available screen space...
        btn = evt.GetEventObject()
        pos = btn.ClientToScreen( (0,0) )
        sz =  btn.GetSize()
        win.Position(pos, (0, sz[1]))

        win.Popup()


    def OnShowDialog(self, evt):
        dlg = TestDialog(self, self.log)
        dlg.CenterOnScreen()

        # this does not return until the dialog is closed.
        print dlg.ShowModal()

#---------------------------------------------------------------------------

def runTest(frame, nb, log):
    if havePopupWindow:
        win = TestPanel(nb, log)
        return win
    else:
        from Main import MessagePanel
        win = MessagePanel(nb, 'wx.PopupWindow is not available on this platform.',
                           'Sorry', wx.ICON_WARNING)
        return win

#---------------------------------------------------------------------------


overview = """\
"""


if __name__ == '__main__':
    import sys,os
    import run
    run.main(['', os.path.basename(sys.argv[0])] + sys.argv[1:])


 	  	 
