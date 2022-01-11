import wx
import wx.richtext as rt

class MyFrame(wx.Frame):
    def __init__(self, *args, **kwds):
        kwds["style"] = kwds.get("style", 0) | wx.DEFAULT_FRAME_STYLE
        wx.Frame.__init__(self, *args, **kwds)
        self.SetSize((300, 200))
        self.SetTitle("RichTextCtrl")

        self.main_panel = wx.Panel(self, wx.ID_ANY)
        main_sizer = wx.BoxSizer(wx.VERTICAL)
        self.rtc = rt.RichTextCtrl(self.main_panel, wx.ID_ANY, style=rt.RE_MULTILINE)
        main_sizer.Add(self.rtc, 1, wx.EXPAND, 0)
        self.main_panel.SetSizer(main_sizer)
        self.Layout()

        self.rtc.BeginFontSize(14)
        self.rtc.WriteText("The quick brown fox")
        self.rtc.EndFontSize()

        # Apply waved underline?
        attr = rt.RichTextAttr()
        attr.SetFontUnderlineType(wx.TEXT_ATTR_UNDERLINE_SPECIAL, colour=wx.RED)
        self.rtc.SetStyle(10, 15, attr)

class MyApp(wx.App):
    def OnInit(self):
        self.frame = MyFrame(None, wx.ID_ANY, "")
        self.SetTopWindow(self.frame)
        self.frame.Show()
        return True

if __name__ == "__main__":
    app = MyApp(0)
    app.MainLoop()

