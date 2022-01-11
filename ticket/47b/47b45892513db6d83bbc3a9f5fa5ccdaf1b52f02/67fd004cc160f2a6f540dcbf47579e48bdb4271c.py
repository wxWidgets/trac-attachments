#!/usr/bin/env python
#
# Based on wx.StaticBox demo in wxPython demos
#
import sys
import wx
import wx.lib.scrolledpanel

#----------------------------------------------------------------------

class TestPanel(wx.lib.scrolledpanel.ScrolledPanel):
    def __init__(self, parent, log):
        self.log = log
        wx.lib.scrolledpanel.ScrolledPanel.__init__(self, parent, -1)
        
        self.SetAutoLayout(True)
        border = wx.BoxSizer(wx.VERTICAL)
        box = wx.StaticBox(self, -1, "This is a wx.StaticBox")
        bsizer = wx.StaticBoxSizer(box, wx.VERTICAL)
        flexGridSizer  = wx.FlexGridSizer( 5, 2, 0, 0 )

        for i in range(1,100):
            label = wx.StaticText(self, -1, "Label %i"%i)
            field = wx.CheckBox(self, -1)
            #field = wx.TextCtrl(self, -1, "Field %i"%i)
            field.Label = "Field %i"%i  
            flexGridSizer.AddWindow(label)
            flexGridSizer.AddWindow(field)

        bsizer.AddSizer(flexGridSizer)
        border.Add(bsizer) 
        #border.Add(bsizer, 1, wx.EXPAND|wx.ALL, 25)  # NOTE: THIS WORKS FINE AND CANNOT REPRODUCE IF THIS IS USED INSTEAD
        # NOTE: A Resize window event seems to correct the issue
        
        self.SetSizer(border)
        self.SetupScrolling()

#       WORKAROUND -----------------
        # WORKAROUND: OSX and Linux issue with correctly refreshing controls when scrolling
        enableWorkaround = False
        if (enableWorkaround) and (sys.platform == 'darwin' or sys.platform[:5] == 'linux'):
            self.Bind(wx.EVT_SCROLLWIN, self.OnScroll)

    def OnScroll(self, event):
        #   A resize event seems to correct it.
        print "Workaround: Resizing to 'burp' controls backin to place" 
        self.SetSize( self.GetSize()+(1,1))
        self.SetSize( self.GetSize()-(1,1))
        event.Skip()
        
        
if __name__ == '__main__':
    app = wx.App(redirect=False)
    frame = wx.Frame(None, -1, size=(400,600))
    panel = TestPanel(frame, -1)
    frame.Show()
    app.MainLoop()



 	  	 
