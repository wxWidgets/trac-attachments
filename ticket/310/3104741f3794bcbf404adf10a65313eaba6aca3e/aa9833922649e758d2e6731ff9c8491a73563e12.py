
import wx


class Frame1(wx.Frame):
   def __init__(self, prnt):
      wx.Frame.__init__(self, id=1, name='', parent=prnt,
            pos=wx.Point(322, 188), size=wx.Size(672, 481),
            style=wx.DEFAULT_FRAME_STYLE, title='Frame1')
      self.Bind(wx.EVT_CLOSE, self.OnCloseWindow)
   def OnCloseWindow(self, event):
      self.Destroy()
      
class MyApp(wx.App):
   def OnInit(self):
      wx.InitAllImageHandlers()
      self.main = Frame1(None)
      # needed when running from Boa under Windows 9X
      self.SetTopWindow(self.main)
      self.main.Show()
      return True

def main():
   application = MyApp(0)
   application.MainLoop()

if __name__ == '__main__':
   main()

 	  	 
