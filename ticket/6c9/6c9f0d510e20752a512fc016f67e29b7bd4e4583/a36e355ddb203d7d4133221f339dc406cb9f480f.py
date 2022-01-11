import wx
import wx.aui
import wx.grid




class myframe1(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self,None,-1,'Test Frame',size=wx.Size(500,500))

        self._mgr = wx.aui.AuiManager()
        self._mgr.SetManagedWindow(self)

        CreatePane(self)
        self.Show()

class myframe2(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self,None,-1,'Test Window',size=wx.Size(500,500))
        win = mywindow(self)
        self.Show()

class mywindow(wx.Window):
    def __init__(self,parent):
        wx.Window.__init__(self,parent)

        self._mgr = wx.aui.AuiManager()
        self._mgr.SetManagedWindow(self)

        CreatePane(self)

def CreatePane(window):
    window._mgr.AddPane(CreateGrid(window), wx.aui.AuiPaneInfo().Name("grid_content1").Left().BestSize(wx.Size(200,200)).MinSize(wx.Size(50,100)))
    window._mgr.AddPane(CreateGrid(window), wx.aui.AuiPaneInfo().Name("grid_content2").CenterPane())
    window._mgr.AddPane(CreateGrid(window), wx.aui.AuiPaneInfo().Name("grid_content3").Bottom().BestSize(wx.Size(200,200)).MinSize(wx.Size(100,50)))
    window._mgr.Update()

def CreateGrid(parent):
    grid = wx.grid.Grid(parent, -1, wx.Point(0, 0), wx.Size(300, 250),
                        wx.NO_BORDER | wx.WANTS_CHARS)
    grid.CreateGrid(50, 20)
    return grid


class myapp(wx.App):
    def OnInit(self):
        frame = myframe1()
        frame = myframe2()
        return True


if __name__ == '__main__':
    app = myapp()
    app.MainLoop()