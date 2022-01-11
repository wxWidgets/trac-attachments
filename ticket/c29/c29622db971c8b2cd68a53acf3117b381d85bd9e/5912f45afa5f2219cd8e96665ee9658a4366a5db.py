import wx
from wx.lib.wordwrap import wordwrap

class Frame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None)
        checkbox = wx.CheckBox(self, label=wordwrap("tex gfd dgfg fdg dfg fdgfd fd gdfgdf gdt texttt gtrfd gdfg dfgdf gfd df gtfd gfd gfd dgf", 350, wx.ClientDC(self)))



app = wx.App(redirect=False)
f = Frame()
f.Show()

app.MainLoop()