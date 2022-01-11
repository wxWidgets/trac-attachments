import wx
import wx.lib.customtreectrl as CT

class MyFrame(wx.Frame):
    def __init__(self, *args, **kwds):
        kwds["style"] = wx.DEFAULT_FRAME_STYLE
        wx.Frame.__init__(self, *args, **kwds)
        self.window_1 = CT.CustomTreeCtrl(self, -1, style=wx.TR_DEFAULT_STYLE | wx.TR_HAS_VARIABLE_ROW_HEIGHT | wx.TR_EDIT_LABELS)

        self.__set_properties()
        self.__do_layout()

    def __set_properties(self):
        self.SetTitle("Window")
        self.root = self.window_1.AddRoot("Root")
        self.window_1.AppendItem(self.root, "Child1")
        self.combo_box_1 = wx.ComboBox(self.window_1, -1, choices=["1", "2", "3"], style=wx.CB_READONLY|wx.CB_DROPDOWN, size=wx.Size(100,20))
        self.window_1.AppendItem(self.root, "Child2", wnd=self.combo_box_1)

    def __do_layout(self):
        sizer_1 = wx.BoxSizer(wx.VERTICAL)
        sizer_1.Add(self.window_1, 1, wx.EXPAND, 0)
        self.SetSizer(sizer_1)
        sizer_1.Fit(self)
        self.Layout()

if __name__ == "__main__":
    app = wx.PySimpleApp(0)
    wx.InitAllImageHandlers()
    frame_1 = MyFrame(None, -1, "")
    app.SetTopWindow(frame_1)
    frame_1.Show()
    app.MainLoop()
