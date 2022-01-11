import wx
import time

class MainFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, wx.ID_ANY)
        startBut = wx.Button(self, wx.ID_ANY, "Start")
        self.Bind(wx.EVT_BUTTON, self._onStart, startBut)

        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(startBut, 1, wx.EXPAND)
        self.SetSizer(sizer)

    def _onStart(self, evt):
        calDlg = MyDialog(self)
        print "going modal"
        calDlg.ShowModal()
        calDlg.Destroy()
        print "do work"

class MyDialog(wx.Dialog):
    def __init__(self, parent):
        wx.Dialog.__init__(self, parent, wx.ID_ANY, "MyDialog")

        stopBut = wx.Button(self, wx.ID_ANY, "Stop")
        self.Bind(wx.EVT_BUTTON, self._onStopClick, stopBut)
        stopBut.SetDefault()
        stopBut.SetFocus()

        selfSizer = wx.BoxSizer(wx.VERTICAL)
        selfSizer.Add(stopBut, 0, wx.ALIGN_CENTER|wx.ALL, 10)
        self.SetSizerAndFit(selfSizer)

        self.Center()
        
    def _onStopClick(self, evt):
        time.sleep(1)
        self.EndModal(123)


def main():
    app = wx.App(False)
    frame = MainFrame()
    frame.Show()
    app.MainLoop()

if __name__=="__main__":
    main()
