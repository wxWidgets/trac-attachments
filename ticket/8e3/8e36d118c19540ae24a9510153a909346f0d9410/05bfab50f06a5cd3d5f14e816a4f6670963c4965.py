'''
Created on Oct 4, 2010

@author: davidsj2
'''

import wx
import wx.lib.buttons as btns

class TestButton(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, wx.ID_ANY)
        
        sizer = wx.BoxSizer(wx.VERTICAL)
        
        goBmp = wx.Bitmap("goDisabled.png")
        pressBmp = wx.Bitmap("goPress.png")

        button = wx.BitmapButton(self, wx.ID_ANY, goBmp, style=wx.NO_BORDER)
        button.SetBitmapSelected(pressBmp)
                    
        sizer.Add(button)    
        
        self.SetSizerAndFit(sizer)
        

if __name__ == "__main__":
    app = wx.App(0)
    frame = wx.Frame(None, wx.ID_ANY, "Blah")
    sizer = wx.BoxSizer(wx.VERTICAL)
    
    panel = TestButton(frame)
    sizer.Add(panel, 1, wx.EXPAND)
        
    
    frame.SetSizerAndFit(sizer)
    frame.SetSize((640, 480))
    
    frame.Show()
    app.MainLoop()