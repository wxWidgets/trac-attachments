import wx
app = wx.PySimpleApp()

parent = wx.Frame(None)
toolbar = wx.ToolBar(parent)
toolitem = toolbar.AddLabelTool(1234, 'Some Text', wx.NullBitmap)

assert not toolbar.DeleteTool(9999), 'Returns True when no item with corresponding id exists'
assert toolbar.DeleteTool(1234),     'Returns False when item exists'
