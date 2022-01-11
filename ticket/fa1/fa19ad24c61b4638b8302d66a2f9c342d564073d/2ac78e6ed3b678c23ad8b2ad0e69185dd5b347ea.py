import wx

class MainFrame(wx.Frame):    

    def __init__(self, parent, title):
        super(MainFrame, self).__init__(parent, -1, title,
                          pos=(150, 150), size=(640, 400))
        
        sayhello= wx.NewId()
        self.Bind(wx.EVT_MENU, self.SayHello)
        
        self.SetAcceleratorTable(wx.AcceleratorTable([(wx.ACCEL_NORMAL, ord('h'), sayhello)]))
    
    def SayHello(self, event):
        print "Hello"
        wx.MessageBox('Hello')

class MyApp(wx.App):    
    def OnInit(self):        
        frame= MainFrame(None, 'Accell Test')
        self.SetTopWindow(frame)
        frame.Show(True)
        return True

TheApp = MyApp(redirect= False, useBestVisual= True)
TheApp.MainLoop()
