import wxversion
wxversion.select("2.9")
import wx.grid

class TheFrame(wx.Frame):
    def __init__(self,*args,**kwargs):
        wx.Frame.__init__(self,*args,**kwargs)

        self.gr = gr = wx.grid.Grid(self, -1)
        gr.CreateGrid(1, 2)
        gr.SetCellEditor(0, 1, wx.grid.GridCellFloatEditor())
        but = wx.Button(self, -1, "Button")
        but.Bind(wx.EVT_BUTTON, self.OnButton)
        sz = wx.BoxSizer(wx.VERTICAL)
        sz.Add(gr, 1, wx.EXPAND)
        sz.Add(but)
        self.SetSizer(sz)

    def OnButton(self, event):
        self.gr.SetCellValue(0, 1, "3.1415926535")

app = wx.App(redirect=False)
fr = TheFrame(None, -1, "demo")
fr.Show(True)
app.MainLoop()
