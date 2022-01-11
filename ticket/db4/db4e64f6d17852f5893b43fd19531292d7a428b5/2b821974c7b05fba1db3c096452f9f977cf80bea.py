import sys, wx, os

class MainFrame(wx.Frame):

    def __init__(self, *args, **kwargs):
        wx.Frame.__init__(self, *args, **kwargs)

        sizer = wx.BoxSizer(wx.VERTICAL)

        panel = wx.Panel(self, -1, style=wx.TAB_TRAVERSAL)

        link1 = wx.HyperlinkCtrl(panel, -1, 
				 style=wx.HL_ALIGN_LEFT|wx.NO_BORDER,
				 label="Link #1", url="")

        link2 = wx.HyperlinkCtrl(panel, -1, 
				 style=wx.HL_ALIGN_LEFT,
				 label="Link #2", url="")

        link1.SetToolTipString("Tooltip for link 1")
        link2.SetToolTipString("Tooltip for link 2")

        btn3 = wx.Button(panel, -1, "Bottom Button 3")
        btn4 = wx.Button(panel, -1, "Bottom Button 4")
        self.Bind(wx.EVT_BUTTON, self.OnClick, btn3)
        self.Bind(wx.EVT_BUTTON, self.OnClick, btn4)


        sizer.Add(link1, 0, wx.ALL | wx.ALIGN_LEFT, 5)
        sizer.Add(link2, 0, wx.ALL | wx.ALIGN_LEFT, 5)
        sizer.Add(btn3, 0, wx.ALL | wx.ALIGN_LEFT, 5)
        sizer.Add(btn4, 0, wx.ALL | wx.ALIGN_LEFT, 5)

        panel.SetSizer(sizer)
        sizer.Fit(self)

        link1.SetFocus()


    def OnClick(self, event):
        print "Button Pressed."



def main(argv=None):
    app = wx.App(0)
    frame = MainFrame(None, -1, 'Mouseless Test')
    frame.Center(wx.BOTH)
    frame.Show()
    app.MainLoop()


if __name__ == '__main__':

    main()

