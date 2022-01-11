import os
import wx
from wx import xrc

#This class presents the wx application interface
class InteractiveWxApp(wx.App):

  def __init__(self):

    #Initialize wx GUI application 
    wx.App.__init__(self,0)

  def OnInit(self):
    'Create the main window and insert the custom frame'
    respath = os.path.join(os.path.dirname(__file__), 'bug_size_wx.xrc')
    self.res = xrc.XmlResource(respath)
    
    self.frame = self.res.LoadFrame(None, 'InteractiveWxApp')
    self.frame.Show(True)
    return True
  
wxApp = InteractiveWxApp()
wxApp.MainLoop()
    
