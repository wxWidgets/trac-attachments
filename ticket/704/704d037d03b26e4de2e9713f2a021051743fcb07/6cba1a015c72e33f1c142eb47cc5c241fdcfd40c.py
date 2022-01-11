
import wx
import os

print wx.version()
#import faulthandler
#faulthandler.enable()

app = wx.App(False)

frame = wx.Frame(None)
frame.Show()

def dialog_func(frame):
    dlg = wx.FileDialog(frame, "msg", defaultDir=os.getcwd(), defaultFile='foo.txt', wildcard="Foo (*.txt)|*.txt", style=wx.SAVE|wx.OVERWRITE_PROMPT)
    if dlg.ShowModal() == wx.ID_OK:
        print "Dialog OK"
    else:
        print "Dialog not OK"

wx.CallLater(10, dialog_func, frame)

app.MainLoop()
