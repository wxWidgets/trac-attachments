
import wx
import os

class App(wx.App):

   def OnInit(self):
      frame = wx.Frame(None,id=wx.ID_ANY, title='Dir Dialog Path Problem')
      panel = wx.Panel(frame, id=wx.ID_ANY)
      curdir = os.getcwd()
      dd=wx.DirDialog(panel,curdir, curdir,style=wx.DD_DEFAULT_STYLE|wx.DD_CHANGE_DIR)
      dd.ShowModal()
      #frame.Show()	 
      #self.SetTopWindow(frame)
      #return True
      return False



app = App()   
app.MainLoop()