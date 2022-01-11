import wx

import wx
import os, sys

try:
    dirName = os.path.dirname(os.path.abspath(__file__))
except:
    dirName = os.path.dirname(os.path.abspath(sys.argv[0]))

sys.path.append(os.path.split(dirName)[0])

from agw import aui


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

        self.Bind(aui.EVT_AUI_PERSPECTIVE_CHANGED, self.OnPerspective)        
        self.aui_manager.Update()

        self.perspective = self.aui_manager.SavePerspective()
        

        def reshow(event=None):

            self.aui_manager.LoadPerspective(self.perspective)
            pane = self.aui_manager.GetPane(self.text_ctrl_3)
            pane.Show()
            self.aui_manager.Update()

        self.timer = wx.Timer(self)
        self.timer.Start(3000)
        self.Bind(
            wx.EVT_TIMER,
            reshow,
            self.timer
        )
                    
        self.Show()
       

    def OnPerspective(self, event):

        pane = self.aui_manager.GetPane(self.text_ctrl_3)
        if not pane.IsShown():
            return
        
        self.perspective = self.aui_manager.SavePerspective()        
                
                    
app = wx.App(0)
frame = Frame(None)
app.MainLoop()