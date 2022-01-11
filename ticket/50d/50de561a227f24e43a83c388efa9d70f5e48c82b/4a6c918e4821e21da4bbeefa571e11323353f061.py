import wx

class Subject:
    def __init__(self):
        print "new subject"
        self.observerList = []
    def attach(self, observer):
        print "attached observer %s" % observer
        self.observerList.append(observer)
    def notify(self, *args):
        print "notify called"
        for observer in self.observerList:
            observer.update(self, *args)


class HexViewWindow(wx.ScrolledWindow, Subject):

    def __init__(self, parent, id):
        wx.ScrolledWindow.__init__(self, parent, id)
        Subject.__init__(self)
        
        wx.EVT_SIZE(self, self.OnSize)
 
    def OnSize(self, event):
        self.update()
        
    def update(self):
        self.notify()


class MainFrame(wx.Frame):

    def __init__(self, *args, **kwds):
        wx.Frame.__init__(self, *args, **kwds)
        self.panel_1 = wx.Panel(self, -1)
        
        self.statusbar = self.CreateStatusBar(2)
        self.hexview = HexViewWindow(self.panel_1, -1)

        self.__do_layout()
        self.hexview.attach(self)

    def __do_layout(self):
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.hexview, 1, wx.EXPAND, 0)
        self.SetSizer(sizer)
        self.Layout()

    def update(self, subject=None):
        self.statusbar.SetStatusText('R6025 crash')
            

class MainApp(wx.App):
    def OnInit(self):
        self.frame_main = MainFrame(None, -1, "")
        self.frame_main.Show(1)
        return True


if __name__ == "__main__":
    app = MainApp(0)
    app.MainLoop()
