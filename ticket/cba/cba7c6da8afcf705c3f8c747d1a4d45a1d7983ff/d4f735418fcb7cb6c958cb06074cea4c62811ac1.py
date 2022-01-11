#Boa:Frame:Frame1

import os
import wx

import wx.lib.agw.aui as aui
##import wx.aui as aui

print wx.__version__

def create(parent):
    return Frame1(parent)

[wxID_FRAME1] = [wx.NewId() for _init_ctrls in range(1)]

class Frame1(wx.Frame):
    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_FRAME1, name='', parent=prnt,
              pos=wx.Point(394, 128), size=wx.Size(677, 469),
              style=wx.DEFAULT_FRAME_STYLE,
              title='The Wine Cellar Book - prototype recipe')
        self.SetClientSize(wx.Size(661, 433))
        self.Bind(wx.EVT_SIZE, self.OnFrame1Size)

    def __init__(self, parent):
        self._init_ctrls(parent)

        # tell FrameManager to manage this frame
        self._mgr = aui.AuiManager(self)

        self._mgr.SetDockSizeConstraint(0.5, 0.5)        
        
        self.searchPanel = wx.Panel(self)

        self._mgr.AddPane(self.searchPanel, aui.AuiPaneInfo().
                          Name("RecipeSearch").Caption('Search').
                          Top().MinimizeButton(True).MaximizeButton(True))

        self._mgr.Update()

    def OnFrame1Size(self, event):
        dlg = wx.MessageDialog(self, 'Got a size event', 'Event', wx.OK | wx.ICON_INFORMATION)
        try:
            result = dlg.ShowModal()
        finally:
            dlg.Destroy()
        event.Skip()

        
from wx.lib.mixins.inspection import InspectionMixin
class BoaApp(wx.App, InspectionMixin):
    def OnInit(self):
        self.Init()

        self.main = create(None)
        self.main.Show();self.main.Hide();self.main.Show()
        self.SetTopWindow(self.main)
        self.main.Maximize()
        wx.GetApp().GetTopWindow().Update()

        return True

if __name__ == '__main__':
    app = BoaApp(0)
    app.MainLoop()
