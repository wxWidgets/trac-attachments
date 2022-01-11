import string
import random
import wx
from wx.lib.scrolledpanel import ScrolledPanel


class ListCtrl(wx.ListCtrl):
	def OnGetItemText(self, item, column):
		return random.choice(string.ascii_letters) * 3


app = wx.App()
dialog = wx.Dialog(None, size=(250, 250))
panel = wx.Panel(dialog)
listctrl = ListCtrl(panel, style=wx.LC_VRULES|wx.LC_HRULES|wx.LC_REPORT|wx.LC_VIRTUAL, size=(1000, 100), pos=(10, 20))
listctrl.AppendColumn("Column #1")
listctrl.AppendColumn("Column #2")
listctrl.AppendColumn("Column #3")
listctrl.AppendColumn("Column #4")
listctrl.AppendColumn("Column #5")
listctrl.SetItemCount(200)

label = wx.StaticText(panel, label="Test", pos=(0, 0))
textctrl = wx.TextCtrl(panel, size=(200, 20), pos=(50, 0))
textctrl.SetValue("Drrrrr")

dialog.Show()
app.MainLoop()
