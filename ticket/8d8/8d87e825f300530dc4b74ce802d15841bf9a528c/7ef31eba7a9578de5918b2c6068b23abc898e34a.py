import wx
import numarray

class ColorBox(wx.Panel):

    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_SIZE, self.OnSize)

        self.color = [0.0, 0.0, 0.0, 1.0]
        self.UpdateBitmap()


    def SetColor(self, color):
        self.color = color
        self.UpdateBitmap()


    def UpdateBitmap(self):
        size = self.GetSize()
        arr = numarray.array(shape=(size[0], size[1], 4), typecode='u1')
        arr[:, :, 0] = self.color[0] * 255
        arr[:, :, 1] = self.color[1] * 255
        arr[:, :, 2] = self.color[2] * 255
        arr[:, :, 3] = self.color[3] * 255
        self.bitmap = wx.BitmapFromBufferRGBA(size[0], size[1], arr)
        self.Refresh()
    

    def OnSize(self, evt):
        self.UpdateBitmap()

    def OnPaint(self, evt):
        dc = wx.PaintDC(self)
        dc.DrawBitmap(self.bitmap, 0, 0, True)


class MainPanel(wx.Panel):

    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)

        self.colorBox = ColorBox(self)
        self.colorBox.SetSize((50, 50))
        self.colorBox.SetColor([1.0, 0.0, 0.0, 1.0])

        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(self.colorBox, 10, wx.ALIGN_LEFT)
        self.SetSizer(sizer)


class MyFrame(wx.Frame):

    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, -1, title, pos=(150, 150), size=(350, 200))
        
        panel = MainPanel(self)


class MyApp(wx.App):

    def OnInit(self):
        frame = MyFrame(None, "BitmapFromBufferRGBA bug tester")
        self.SetTopWindow(frame)        

        print "Print statements go to this stdout window by default."

        frame.Show(True)
        return True


app = MyApp(redirect=True, filename="output.txt")
app.MainLoop()

 	  	 
