'''
Created on 17.03.2013

@author: ralf
'''
import wx

class DrawPanel(wx.Panel):

    def __init__(self,
                 parent,
                 ID=-1,
                 pos = wx.DefaultPosition,
                 size = wx.DefaultSize
                ):
        wx.Panel.__init__(self,parent,ID, pos, size)
        self.Bind(wx.EVT_PAINT, self.onPaint)
        self.Buffer = None

    def drawtobuffer(self):
        Size  = self.GetClientSize()
        self.Buffer = wx.EmptyBitmap(Size.width, Size.height, 32)
        mdc = wx.MemoryDC()
        mdc.SelectObject(self.Buffer)
        dc = wx.GCDC(mdc)
        
        #dc.SetBackground(wx.Brush(wx.Colour(0,0,0,0)))
        dc.SetBackground(wx.Brush(wx.Colour(0,0,0,255)))
        dc.Clear()
        
        color = wx.Colour( 35, 142,  35, 128)
        dc.SetBrush(wx.Brush(color))
        dc.SetPen(wx.Pen('CADET BLUE', 2))
        dc.DrawRectangle(50,50,100,50)
        mdc.SelectObject(wx.NullBitmap)
        self.Refresh()


#    def drawtobuffer(self):
#        Size  = self.GetClientSize()
#        self.Buffer = wx.EmptyBitmapRGBA(Size.width, Size.height, 0, 0, 0, 128)
#        mdc = wx.MemoryDC()
#        mdc.SelectObject(self.Buffer)
#        dc = wx.GCDC(mdc)
#        color = wx.Colour( 35, 142,  35, 128)
#        dc.SetBrush(wx.Brush(color))
#        dc.SetPen(wx.Pen('CADET BLUE', 2))
#        dc.DrawRectangle(50,50,100,50)
#        mdc.SelectObject(wx.NullBitmap)
#        self.Refresh()
        
    def onPaint(self,event):
        if self.Buffer:
            dc = wx.PaintDC(self)
            dc = wx.GCDC(dc)
            dc.DrawBitmap(self.Buffer, 0, 0, True)
        else:
            event.Skip()

class TestFrame(wx.Frame):

    def __init__(self,
                 parent=None,
                 ID=-1,
                 title="Pan Test",
                 pos=wx.DefaultPosition,
                 size=wx.DefaultSize,
                 style=wx.DEFAULT_FRAME_STYLE):
        wx.Frame.__init__(self,parent,ID,title,pos,size,style)
        self.canvas = DrawPanel(self, pos = (0,0), size = wx.Size(400,280))
        self.MakeNewDataButton = wx.Button(self, wx.ID_ANY, "Make TestData and Draw")

        ButtonSizer = wx.BoxSizer(wx.HORIZONTAL)
        ButtonSizer.Add(self.MakeNewDataButton)
        
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.SetSizer(self.sizer)
        self.sizer.Add(ButtonSizer)
        self.sizer.Add(self.canvas, proportion = 1, flag = wx.ALL | wx.EXPAND)
        self.sizer.SetSizeHints(self)
        
        self.Bind(wx.EVT_CLOSE, self.onClose)
        self.MakeNewDataButton.Bind(wx.EVT_BUTTON, self.onClickMakeNewDataButton)


    def onClose(self,event):
        self.Show(False)
        self.Destroy()

    def onClickMakeNewDataButton(self, event):
        #print "onClick"
        print wx.version()
        self.canvas.drawtobuffer()







def main():
    app = wx.App(False)
    frame = TestFrame()
    frame.Show(True)
    app.MainLoop()

if __name__ == '__main__':
    main()