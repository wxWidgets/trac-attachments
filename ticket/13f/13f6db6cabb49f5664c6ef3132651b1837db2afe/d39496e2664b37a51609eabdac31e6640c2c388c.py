# wxPython test-application for reproducing wxWidgets issue 14564:
#
# Raise() on wxFrame with wxFRAME_NO_TASKBAR raises all such frames
# http://trac.wxwidgets.org/ticket/14654
import wx
import wx.aui

app = wx.PySimpleApp()
mainFrame = wx.Frame(None, title='#14654 Raise() on wxFrame with wxFRAME_NO_TASKBAR raises all such frames', size=(600,200), pos =(600,400))

panel = wx.Panel(mainFrame)
button_show_A = wx.Button(panel, label="Raise A", pos=(50,120))
button_show_A.Bind(wx.EVT_BUTTON, lambda evt : frame_A.Raise())

button_show_B = wx.Button(panel, label="Raise B", pos=(150,120))
button_show_B.Bind(wx.EVT_BUTTON, lambda evt : frame_B.Raise())

frame_A = wx.Frame(mainFrame, size=(200,100), title='A', style=(wx.DEFAULT_FRAME_STYLE | wx.FRAME_NO_TASKBAR) )
wx.Panel(parent=frame_A)

frame_B = wx.Frame(mainFrame, size=(200,100), title='B', style=(wx.DEFAULT_FRAME_STYLE | wx.FRAME_NO_TASKBAR) )
wx.Panel(parent=frame_B)

frame_C = wx.Frame(mainFrame, size=(200,100), title='C', style=(wx.DEFAULT_FRAME_STYLE | wx.FRAME_NO_TASKBAR) )
wx.Panel(parent=frame_C)

app.SetTopWindow(mainFrame)
mainFrame.Show()
frame_A.Show()
frame_A.SetPosition(mainFrame.GetPosition() - [value / 2 for value in frame_A.GetSize()])
frame_B.Show()
frame_B.SetPosition(frame_A.GetPosition() + ( frame_A.GetSize().width, 0) )
frame_C.Show()
frame_C.SetPosition(mainFrame.GetPosition())
mainFrame.Raise()
app.MainLoop()
