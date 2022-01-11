from wxPython import wx

class MyApp(wx.wxApp):

    def OnInit(self):
        frame = wx.wxFrame(None, -1, "minimal", size=(200, 200))
        panel = wx.wxPanel(frame, -1)
        self.panel = panel
        
        frame.Show(1)


        self.btn = wx.wxButton(panel, -1, "set text")
        wx.EVT_BUTTON(panel, self.btn.GetId(), self.OnMouseClick)

        borderStyle = 0 #wx.wxNO_BORDER
        tstyle = wx.wxTE_RICH2 | wx.wxTE_PROCESS_TAB | wx.wxTE_MULTILINE | borderStyle | \
                wx.wxNO_FULL_REPAINT_ON_RESIZE | wx.wxCLIP_SIBLINGS

        self.text1 = wx.wxTextCtrl(panel, -1, '', (0, 30), style=tstyle, name="text1")

        self.line = 1

        wx.EVT_TEXT(panel, self.text1.GetId(), self.OnTextUpdate)

        self.SetTopWindow(frame)

        print "end of init"
        return 1

    def OnMouseClick(self, evt):
        print "OnMouseClick"
        if self.line == 1:
            self.text1.SetValue("%s" % self.line)
        else:
            self.text1.AppendText("\n%s" % self.line)
        self.line += 1

    def OnTextUpdate(self, evt):
        print "OnTextUpdate", self.text1.GetValue()


app = MyApp(0)
app.MainLoop()

 	  	 
