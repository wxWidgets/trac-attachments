import wx 


import wx.lib.agw.aui as aui 
import wx.lib.mixins.inspection 


class TheApp(wx.App, wx.lib.mixins.inspection.InspectionMixin): 
    def OnInit(self): 
        frame = MyFrame() 
        frame.Show() 
        self.Init() 
        return True 


class MyPanel(wx.Panel): 
    def __init__(self, parent): 
        wx.Panel.__init__(self, parent, -1) 


        sizer = wx.BoxSizer(wx.VERTICAL) 
        tb = aui.AuiToolBar(self, -1, wx.DefaultPosition, wx.DefaultSize, 
                            aui.AUI_TB_DEFAULT_STYLE) 
        tb.SetToolBitmapSize(wx.Size(16, 16)) 


        tb.AddSeparator() 
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
        sizer.Add(tb, 0, wx.EXPAND) 


        self.SetSizer(sizer) 
        sizer.Fit(self) 


    def OnToolbar(self, event): 
        print 
        print event.GetEventObject() 
        print event.GetId() 


class MyFrame(wx.Frame): 
    def __init__(self): 
        wx.Frame.__init__(self, None, -1, size=(800,600), 
                          style=wx.DEFAULT_FRAME_STYLE) 


        MyPanel(self) 
        self.Show() 


if __name__ == '__main__': 
    app = TheApp(redirect=False) 
    app.MainLoop() 


