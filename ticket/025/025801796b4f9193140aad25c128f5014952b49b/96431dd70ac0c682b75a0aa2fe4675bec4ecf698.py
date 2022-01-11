import wx

# Change this to wherver you import the dev version of aui from:
from garlicsim_wx.general_misc.third_party import aui


class Frame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, size=(700, 700))
        self.aui_manager = aui.AuiManager(self)
        
        self.text_ctrl_1 = wx.TextCtrl(self, value='Text ctrl 1',
                                       size=(300, 300))
        self.text_ctrl_2 = wx.TextCtrl(self, value='Text ctrl 2',
                                       size=(300, 300))
        self.text_ctrl_3 = wx.TextCtrl(self, value='Text ctrl 3',
                                       size=(300, 300))
        
        self.aui_manager.AddPane(
            self.text_ctrl_1,
            aui.AuiPaneInfo().Caption('Text ctrl 1').Center()
        )
        self.aui_manager.AddPane(
            self.text_ctrl_2,
            aui.AuiPaneInfo().Caption('Text ctrl 2').Right().BestSize(300, 300)
        )
        self.aui_manager.AddPane(
            self.text_ctrl_3,
            aui.AuiPaneInfo().Caption('Text ctrl 3').Right().BestSize(300, 300)
        )
        
        def reshow(event=None):
            self.aui_manager.GetPaneByWidget(self.text_ctrl_3).Show()
            self.aui_manager.Update()
            
        self.timer = wx.Timer(self)
        self.timer.Start(3000)
        self.Bind(
            wx.EVT_TIMER,
            reshow,
            self.timer
        )
            
        
        self.aui_manager.Update()
        self.Show()
        
        
app = wx.App()
frame = Frame(None)
app.MainLoop()