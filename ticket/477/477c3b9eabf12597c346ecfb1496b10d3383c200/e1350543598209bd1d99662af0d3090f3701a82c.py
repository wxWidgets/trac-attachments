"""
Sample demonstrating strange behaviour of StyledTextCtrl when destroyed.

Tested on wxPython 2.9.4.0, Win x64, Python 2.7 x32.

Steps to reproduce:
    Press ENTER inside the TextCtrl at the top of the frame

Problem:
    The blinking caret inside the TextCtrl disappears once StyledTextCtrl instance is destroyed.
"""
import wx
from wx import stc
print wx.version()

#event processing function invoked when key is pressed inside the textctrl
def onSearch(event):
    key = event.GetKeyCode()
    if key == wx.WXK_RETURN or key == wx.WXK_NUMPAD_ENTER:
        print "Destroying result panel.."
        wx.CallAfter(styledControl.Destroy)
    event.Skip()

#Create simple main frame
app = wx.App(False)
frame = wx.Frame(None, wx.ID_ANY, "sctrl_test")
masterSizer = wx.BoxSizer(wx.VERTICAL)
frame.SetSizer(masterSizer)

#Add TextCtrl
textField = wx.TextCtrl(frame, size=(200,-1), style=wx.PROCESS_ENTER)
textField.Bind(wx.EVT_KEY_DOWN, onSearch, textField)
masterSizer.Add(textField, 0,wx.EXPAND,0)

#Create a panel that will contain our StyledTextCtrl
#Note that this panel doesn't appear to be part of the problem - the problem manifests even if styledControl is direct
#child of frame.
pane = wx.Panel(frame)
masterSizer.Add(pane, 1, wx.EXPAND, 0)

#Add StyledTextCtrl. It is not in a sizer for simplicity reasons.
styledControl = stc.StyledTextCtrl(pane)
#if we used StaticText or even another TextCtrl, the problem wouldn't appear
#simpleLabel = wx.StaticText(result, -1, "Label")


#Inspection tool snippet
#import wx.lib.inspection
#wx.lib.inspection.InspectionTool().Show()

#Run the sample
frame.Show(True)
app.MainLoop()

