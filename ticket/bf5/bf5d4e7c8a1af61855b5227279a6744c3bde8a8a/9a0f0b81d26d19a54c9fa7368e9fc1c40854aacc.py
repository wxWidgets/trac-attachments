import wx

#----------------------------------------------------------------------------

class OnAddFileFromDrop(wx.FileDropTarget):
    def __init__(self, parent):
        wx.FileDropTarget.__init__(self)
        self.parent = parent
        parent.SetDropTarget(self)

    def OnDropFiles(self, x, y, filenames):
        result = self.parent.SetValue(filenames[0])

#----------------------------------------------------------------------------

class MyApp(wx.App):
    
    def OnInit(self):
        wx.InitAllImageHandlers()
        frame = wx.Frame( None, -1, "Drop File In TextCtrl")
        #--------------------------------------------
        problem = False
        if problem:
            # wx.SystemOptions.SetOptionInt("msw.staticbox.optimized-paint", 0)
            sb = wx.StaticBox( frame, -1, "Text" )
            sizer = wx.StaticBoxSizer( sb, wx.HORIZONTAL )
        else:
            sizer = wx.BoxSizer( wx.HORIZONTAL )
        #--------------------------------------------
        textCtrl = wx.TextCtrl( frame, -1, "", wx.DefaultPosition, [300,-1], 0 )
        sizer.Add( textCtrl, 1, wx.ALIGN_CENTER|wx.ALL, 5 )
        frame.SetSizer( sizer )
        sizer.SetSizeHints( frame )
        OnAddFileFromDrop(textCtrl)
        frame.Show(True)
        return True

#----------------------------------------------------------------------------

app = MyApp(False)
app.MainLoop()


 	  	 
