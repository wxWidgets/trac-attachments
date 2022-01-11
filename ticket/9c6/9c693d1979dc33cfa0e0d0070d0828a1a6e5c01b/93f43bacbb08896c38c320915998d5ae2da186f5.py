import wx

class MyApp(wx.App):

    def OnInit(self):
        frame = wx.Frame(None, -1, "minimal", size=(200, 200))
        panel = wx.Panel(frame, -1)
        self.panel = panel
        
        frame.Show(1)

        borderStyle = 0 #wx.wxNO_BORDER
        tstyle = wx.TE_RICH2 | wx.TE_PROCESS_TAB | wx.TE_MULTILINE | borderStyle | \
                wx.NO_FULL_REPAINT_ON_RESIZE | wx.CLIP_SIBLINGS

        self.text1 = wx.TextCtrl(panel, -1, 'Hello PythonCard', (5, 30), (150, 86), style=tstyle, name="text1")

        wx.EVT_CLOSE(frame, self.OnClose)
        wx.EVT_TEXT(panel, self.text1.GetId(), self.OnTextUpdate)
        wx.EVT_SET_FOCUS(self.text1, self.OnSetFocus)
        wx.EVT_KILL_FOCUS(self.text1, self.OnKillFocus)

        self.SetTopWindow(frame)

        print "end of init"
        return 1

    def OnClose(self, evt):
        print "OnClose"
        evt.Skip()

    def OnSetFocus(self, evt):
        target = evt.GetEventObject()
        print "OnSetFocus", target
        # if the line below is commented out, the field still gets
        # focus, but there is no selection rectangle
        evt.Skip()

    # if field has focus when App is quit, then we'll get
    # a bus error crash
    def OnKillFocus(self, evt):
        target = evt.GetEventObject()
        print "OnKillFocus", target
        # the line below is apparently the problem
        # i'm assuming the C++ object has already been destroyed
        # or something like that
        # commenting out the line below will get rid of the crash
        # but that isn't an acceptable solution
        print target.IsModified()
        evt.Skip()

    def OnTextUpdate(self, evt):
        print "OnTextUpdate", self.text1.GetValue()


app = MyApp(0)
app.MainLoop()

 	  	 
