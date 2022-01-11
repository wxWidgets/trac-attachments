import wx
import wx.lib.agw.aui as aui

class MyFrame(wx.Frame):
    def __init__(self, parent):
        super(MyFrame, self).__init__(parent)

        # Attributes
        style = aui.AUI_NB_DEFAULT_STYLE | \
                aui.AUI_NB_WINDOWLIST_BUTTON | \
                aui.AUI_NB_SMART_TABS | \
                aui.AUI_NB_USE_IMAGES_DROPDOWN | \
                aui.AUI_NB_TAB_EXTERNAL_MOVE | \
                aui.AUI_NB_TAB_FIXED_WIDTH
        self._nb = aui.AuiNotebook(self, style=style)

        # Setup
        self.panel = wx.Panel(self)
        self.panel.SetBackgroundColour(wx.BLACK)

        # Put some pages in the notebook
        for x in range(4):
            panel = wx.Panel(self)
            self._nb.AddPage(panel, u"Page %d" % x)

        # Layout
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(self.panel, 0)
        sizer.Add(self._nb, 1, wx.EXPAND)
        self.SetSizer(sizer)

app = wx.App(False)
f = MyFrame(None)
f.Show()
app.MainLoop()
