
import wx
import wx.aui
import sys, os

APP_NAME="PerspectiveDemoApp"

class PerspectivePanel(wx.Panel):
  def __init__(self, *args, **kwargs):
    wx.Panel.__init__(self, *args, **kwargs)
    
    sizer = wx.GridBagSizer()
    sizer.AddGrowableCol(0)
    sizer.AddGrowableRow(0)
    
    self._text = wx.TextCtrl(self, -1)
    
    sizer.Add(self._text, wx.GBPosition(0,0), wx.GBSpan(1,1), flag=wx.EXPAND)
    
    self.SetSizer(sizer) 
    
    return

class PerspectiveFrame(wx.Frame):
  def __init__(self, *args, **kwargs):
    wx.Frame.__init__(self, *args, **kwargs)
    ##
    ## File Menu
    ##
    menuBar = wx.MenuBar()
    fileMenu = wx.Menu()
    
    item = fileMenu.Append(-1, "&Save Perspective")
    self.Bind(wx.EVT_MENU, self.SavePerspective, item)
    
    item = fileMenu.Append(-1, "&Load Perspective")
    self.Bind(wx.EVT_MENU, self.LoadPerspective, item)
    
    item = fileMenu.Append(-1, "&Clear Perspective")
    self.Bind(wx.EVT_MENU, self.ClearPerspective, item)
    
    fileMenu.AppendSeparator()
    
    item = fileMenu.Append(-1, "E&xit")
    self.Bind(wx.EVT_MENU, self.Exit, item)
    
    menuBar.Append(fileMenu, "&File")
    
   
    self.SetMenuBar(menuBar)
    
    
    self._manager = wx.aui.AuiManager(self)
    
    ##
    ## Panels
    ## 
    
    for i in range(0,6):
      panel = PerspectivePanel(self, -1)
      auiInfo = wx.aui.AuiPaneInfo()
      auiInfo.CloseButton(False)
      auiInfo.Right()
      auiInfo.MinSize(wx.Size(60,60))
      auiInfo.Caption("Panel %03d" % i)
      
      self._manager.AddPane(panel, auiInfo)
      
    self._manager.Update()
      
    
    
    return
  
  def SavePerspective(self, evt):
    config = wx.Config(APP_NAME)
    
    config.Write("perspective", self._manager.SavePerspective())
    
    return
  
  def LoadPerspective(self, evt):
    
    config = wx.Config(APP_NAME)
    
    self._manager.LoadPerspective(config.Read("perspective"))
    
    return
  
  def ClearPerspective(self, evt):

    config = wx.Config(APP_NAME)
    
    config.DeleteAll()
    
    return
  
  def Exit(self, evt):
    sys.exit(0)
    return
  
class PerspectiveApp(wx.App):
  def __init__(self, *args, **kwargs):
    wx.App.__init__(self, *args, **kwargs)
    return
  
  def OnInit(self):
    self._frame = PerspectiveFrame(None, -1, "Perspective", size=wx.Size(640, 480))
    
    
    self._frame.Show()
    
    return True
      
  
  
if __name__ == "__main__":
  app = PerspectiveApp()
  
  app.MainLoop()
  
  