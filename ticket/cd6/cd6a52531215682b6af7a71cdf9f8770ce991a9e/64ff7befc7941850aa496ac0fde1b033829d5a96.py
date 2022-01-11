import wx

class TestFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title="TestFrame", size=(300, 300))
        
        self._btn = wx.Button(self, label="Open FontDialog")
        sizer = wx.BoxSizer()
        sizer.Add(self._btn, 1, wx.ALIGN_CENTER)
        sizer2 = wx.BoxSizer(wx.VERTICAL)
        sizer2.Add(sizer, 1, wx.ALIGN_CENTER)
        self.SetSizer(sizer2)
        self.Bind(wx.EVT_BUTTON, self.OnButton, self._btn)

    def OnButton(self, evt):
        fontdata = wx.FontData()
        dlg = wx.FontDialog(self, fontdata)
        dlg.ShowModal()
        fontdata = dlg.GetFontData()
        font = fontdata.GetChosenFont()
        print "Face: ", font.GetFaceName().encode('utf-8')
        dlg.Destroy()

if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = TestFrame()
    frame.Show()
    app.MainLoop()


 	  	 
