# -*- coding: utf-8 -*-
import wx
import wx.lib.agw.aui as aui
import wx.lib.mixins.inspection

class TheApp(wx.App, wx.lib.mixins.inspection.InspectionMixin):
    def OnInit(self):
        frame = MyFrame()
        frame.Show()
        self.Init()
        return True

class AuiPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)
        self._mgr = aui.AuiManager(self)

        p1 = wx.Panel(self, -1)
        self._mgr.AddPane(p1, aui.AuiPaneInfo().
            Name('content').Caption('Content').CenterPane())
        p2 = wx.Panel(self, -1)
        self._mgr.AddPane(p2, aui.AuiPaneInfo().
            Name('test').Caption('Test Pane'). Left().
            MinSize(wx.Size(200, -1)).CloseButton(True).MaximizeButton(True).
            MinimizeButton(True))

        self._mgr.Update()

class MyFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, size=(800,600),
                          style=wx.DEFAULT_FRAME_STYLE)

        self.mainPanel = wx.Panel(self)
        self._mgr = aui.AuiManager()
        self._mgr.SetManagedWindow(self.mainPanel)

        nb = aui.AuiNotebook(self.mainPanel, -1)
        nbp1 = AuiPanel(nb)
        nb.AddPage(nbp1, 'Notebook - p1', False)
        
        nbp2 = AuiPanel(nb)
        nb.AddPage(nbp2, 'Notebook - p2', False)

        p1 = wx.Panel(self.mainPanel)
        p2 = wx.Panel(self.mainPanel)
        
        self._mgr.AddPane(nb, aui.AuiPaneInfo().
            Name('notebook').Caption('Notebook').CenterPane())
        
        self._mgr.AddPane(p1, aui.AuiPaneInfo().
            Name('content').Caption('Content').CenterPane())

        self._mgr.AddPane(p2, aui.AuiPaneInfo().
            Name('test').Caption('Test Pane'). Left().
            MinSize(wx.Size(200, -1)).CloseButton(True).MaximizeButton(True).
            MinimizeButton(True))

        tb = self.CreateToolBar(self.mainPanel)
        self._mgr.AddPane(tb, aui.AuiPaneInfo().
                          Name("aTB").Caption("The toolbar").
                          ToolbarPane().Top().
                          LeftDockable(False).RightDockable(False))            
            
        self._mgr.Update()

        self.Show()

    def CreateToolBar(self, owner):
        tb = aui.AuiToolBar(owner, -1, wx.DefaultPosition, wx.DefaultSize,
                            aui.AUI_TB_DEFAULT_STYLE)
        tb.SetToolBitmapSize(wx.Size(16, 16))

##        tb.AddSeparator()
        id = wx.NewId()
        tb.AddSimpleTool(id, 'Radio 1',  
                    wx.ArtProvider.GetBitmap(wx.ART_ERROR, wx.ART_OTHER,
                    wx.Size(16, 16)),
                    'Radio 1', aui.ITEM_RADIO)
        self.Bind(wx.EVT_TOOL, self.OnToolbar, id=id)
        id = wx.NewId()
        tb.AddSimpleTool(id, 'Radio 2',
                    wx.ArtProvider.GetBitmap(wx.ART_QUESTION, wx.ART_OTHER,
                    wx.Size(16, 16)),
                    'Radio 2', aui.ITEM_RADIO)
        self.Bind(wx.EVT_TOOL, self.OnToolbar, id=id)                    
        id = wx.NewId()                    
        tb.AddSimpleTool(id, "Radio 3",
                    wx.ArtProvider.GetBitmap(wx.ART_INFORMATION, wx.ART_OTHER,
                    wx.Size(16, 16)),
                    'Radio 3', aui.ITEM_RADIO)
        self.Bind(wx.EVT_TOOL, self.OnToolbar, id=id)                    
        tb.Realize()
        return tb

    def OnToolbar(self, event):
        print event.GetEventObject()
        print event.GetId()
        
if __name__ == '__main__':
    app = TheApp(redirect=False)
    app.MainLoop()