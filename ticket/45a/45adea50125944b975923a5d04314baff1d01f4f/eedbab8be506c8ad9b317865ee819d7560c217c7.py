
import wx
import wx.lib.agw.aui as aui
import wx.py

class MyApp(wx.App):
    def OnInit(self):
        self.frame = MyFrame(None)
        self.frame.Show()
        import wx.lib.inspection
        wx.lib.inspection.InspectionTool().Show()
        return True

class MyFrame(wx.Frame):
    def __init__(self, parent):
        super(MyFrame, self).__init__(parent, title="AUI TEST")

        self.nb = aui.AuiNotebook(self)

        bpanel = wx.Panel(self.nb)
        bpanel.SetBackgroundColour(wx.BLUE)
        rpanel = wx.Panel(self.nb)
        rpanel.SetBackgroundColour(wx.RED)
        gpanel = wx.Panel(self.nb)
        gpanel.SetBackgroundColour(wx.GREEN)

        # Add 3 pages
        self.nb.AddPage(bpanel, "BLUE")
        self.nb.AddPage(rpanel, "RED")
        self.nb.AddPage(gpanel, "GREEN")

if __name__ == '__main__':
    app = MyApp(False)
    app.MainLoop()
