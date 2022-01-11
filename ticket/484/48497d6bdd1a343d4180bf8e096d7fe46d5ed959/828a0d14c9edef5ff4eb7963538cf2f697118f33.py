# -*- coding: utf-8 -*-
import wx, wx.html

class BorderTest(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, style = wx.DEFAULT_FRAME_STYLE)
        
        panel = wx.Panel(self, -1)
        
        self.demoWindow = wx.html.HtmlWindow(panel, -1, style = wx.BORDER_THEME)
        close = wx.Button(panel, -1, 'Change', size=(50, 20))
        
        self.SetTitle('Border Test')

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer2 = wx.BoxSizer(wx.VERTICAL)
        sizer2.Add(self.demoWindow, 1, wx.EXPAND|wx.ALL, 10)
        sizer2.Add(close, 0, wx.ALIGN_RIGHT|wx.TOP|wx.BOTTOM|wx.RIGHT, 5)
        panel.SetSizer(sizer2)
        sizer.Add(panel, 1, wx.EXPAND, 0)
        self.SetSizer(sizer)
        self.Layout()
        
        self.Bind(wx.EVT_BUTTON, self.OnGo, close)
        

        t = '''Enough text to scroll past the pane. Enough text to scroll past the pane. Enough text to scroll past the pane. 
        Enough text to scroll past the pane. Enough text to scroll past the pane. Enough text to scroll past the pane. 
        Enough text to scroll past the pane. Enough text to scroll past the pane. Enough text to scroll past the pane. 
        Enough text to scroll past the pane. Enough text to scroll past the pane. Enough text to scroll past the pane. 
        Enough text to scroll past the pane. Enough text to scroll past the pane. Enough text to scroll past the pane. 
        Enough text to scroll past the pane. Enough text to scroll past the pane. Enough text to scroll past the pane. 
        '''
        
        self.demoWindow.SetPage(t)
        
        
    def OnGo(self, event):
        style = self.demoWindow.GetWindowStyleFlag()
        #print style
        
        if style & wx.BORDER_SIMPLE:
            
            # This will allow selecting text to scroll past pane but looks bad.
            style ^= wx.BORDER_SIMPLE
            style |= wx.BORDER_THEME
            
            # This looks good but will not allow selecting text to scroll past pane.
            #style = wx.BORDER_THEME
            
        elif style & wx.BORDER_THEME:
            
            # This will allow selecting text to scroll past pane but looks bad.
            style ^= wx.BORDER_THEME
            style |= wx.BORDER_SIMPLE
            
            # This looks good but will not allow selecting text to scroll past pane.
            #style = wx.BORDER_SIMPLE
        
        self.demoWindow.SetWindowStyle(style)
        self.Refresh()
        

class MyApp(wx.App):
    def OnInit(self):
        wx.InitAllImageHandlers()
        Demo = BorderTest(None)
        self.SetTopWindow(Demo)
        Demo.Show()
        return 1

if __name__ == "__main__":
    app = MyApp(0)
    app.MainLoop()