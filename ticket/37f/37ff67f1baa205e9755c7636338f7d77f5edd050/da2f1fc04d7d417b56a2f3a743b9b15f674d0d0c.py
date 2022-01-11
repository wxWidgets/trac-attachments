import wx
from wx.tools.dbg import Logger
dbg = Logger()
dbg(enable=1)
class MainWindow(wx.Frame):
    """ We simply derive a new class of Frame. """
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title, size=(200,20))
        self.control = wx.TextCtrl(self, 1, "azertyuiop")
        self.Show(True)
app = wx.PySimpleApp()
frame=MainWindow(None, wx.ID_ANY, 'Small test')
frame.control.SetInsertionPoint(2)
dbg('pos:',frame.control.GetInsertionPoint())
frame.control.SetSelection(2,4)
dbg('pos:',frame.control.GetInsertionPoint())
app.MainLoop()