# wxPython test-application for reproducing wxWidgets issue 13217:
#
# wxAuiNotebook incorrect tab order after drag and drop or split
# http://trac.wxwidgets.org/ticket/13217
import wx
import wx.aui

panelText="""1. Drag and drop the tabs, for the sake of example
place them in the order Green, Blue, Red

2. Click inside the colored panel to set correct focus for
allowing tabbing through tabs (this seems glitchy, but
is unrelated to this issue).

3. Use Ctrl+Tab and Ctrl+Shift+Tab to cycle tabs

Expected: The tabs will cycle in the order they're currently placed
Ctrl+Tab: Green->Blue->Red
Ctrl+Shift+Tab: Red->Blue->Green

Observed: The selected tab jumps around the original order,
Red->Green->Blue.

The tabs can also be split by drag and drop, which makes the
incorrect cycling appear worse."""

def add_panel(notebook, name, color):
    panel = wx.Panel(notebook)
    text = wx.StaticText(panel, label=panelText, pos=(20,30))
    childPanel = wx.Panel(panel, size=(600,20), pos=(0,0))
    childPanel.SetBackgroundColour(color)
    notebook.AddPage(panel, caption=name)
    return panel

app = wx.PySimpleApp()
frame = wx.Frame(None, title='#13217 wxAuiNotebook incorrect tab order after drag and drop or split', size=(600,400))
notebook = wx.aui.AuiNotebook(frame)
add_panel(notebook, "Red", (255,0,0))
add_panel(notebook, "Green", (0,255,0))
add_panel(notebook, "Blue", (0,0,255))
frame.Show()
app.MainLoop()
