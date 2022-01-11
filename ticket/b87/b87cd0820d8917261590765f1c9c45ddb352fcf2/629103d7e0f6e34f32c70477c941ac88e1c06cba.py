import wx

class Box(wx.Panel):

    def __init__(self, parent):
        wx.Panel.__init__(self, parent, pos=(100, 100), style=wx.SIMPLE_BORDER)


        self.SetBackgroundColour("purple")
        self.SetCursor(wx.StockCursor(wx.CURSOR_SIZENESW))
        self.SetSize((150, 100))

app = wx.App(0)

frame = wx.Frame(None, title="HELLO")

panel = wx.Panel(frame)
panel.SetBackgroundColour('pink')
sizer = wx.BoxSizer(wx.VERTICAL)
sizer.Add(panel, 1, wx.EXPAND)
frame.SetSizer(sizer)

m = Box(panel)

frame.SetSize((600, 400))
frame.Show()
app.MainLoop()
