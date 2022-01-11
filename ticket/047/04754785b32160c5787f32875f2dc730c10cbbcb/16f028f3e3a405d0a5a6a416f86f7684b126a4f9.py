from wxPython import wx
import os 

class MyApp(wx.wxApp):

    def OnInit(self):
        frame = wx.wxFrame(None, -1, "GIF image test", size=(200, 300))
        panel = wx.wxPanel(frame, -1)
        self.panel = panel
        
        frame.Show(1)
        
        wx.wxInitAllImageHandlers()

        path = os.path.split(os.path.abspath(__file__))[0]

        bmp = wx.wxBitmap(os.path.join(path, 'lrggumby.gif'), wx.wxBITMAP_TYPE_GIF)
        self.img1 = wx.wxBitmapButton(panel, -1, bmp, (10, 10))

        bmp = wx.wxBitmap(os.path.join(path, 'sillywalk.gif'), wx.wxBITMAP_TYPE_GIF)        self.img2 = wx.wxBitmapButton(panel, -1, bmp, (10, 150))
        
        self.SetTopWindow(frame)
        return 1


app = MyApp(0)
app.MainLoop()



 	  	 
