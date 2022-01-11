import wx
import wx.lib.agw.aui as aui

class MyFrame(wx.Frame):
    def __init__(self):
        super(MyFrame, self).__init__(None, title="Test Frame")

        style = aui.AUI_NB_DEFAULT_STYLE | \
                aui.AUI_NB_WINDOWLIST_BUTTON | \
                aui.AUI_NB_SMART_TABS | \
                aui.AUI_NB_USE_IMAGES_DROPDOWN | \
                aui.AUI_NB_TAB_EXTERNAL_MOVE | \
                aui.AUI_NB_TAB_FIXED_WIDTH
        self.nb = aui.AuiNotebook(self, agwStyle=style)
        for x in range(4):
            p = wx.Panel(self.nb)
            self.nb.AddPage(p, "Page %d" % x)

        self.Bind(aui.EVT_AUINOTEBOOK_TAB_MIDDLE_DOWN, self.OnMDown)
        self.Bind(aui.EVT_AUINOTEBOOK_TAB_MIDDLE_UP, self.OnMUp)

    def OnMDown(self, event):
        sel = event.GetSelection()
        self.nb.SetSelection(sel)
        print "MIDDLE DOWN:", sel

    def OnMUp(self, event):
        print "MIDDLE UP:", event.GetSelection()

app = wx.App(False)
f = MyFrame()
f.Show()
app.MainLoop()
