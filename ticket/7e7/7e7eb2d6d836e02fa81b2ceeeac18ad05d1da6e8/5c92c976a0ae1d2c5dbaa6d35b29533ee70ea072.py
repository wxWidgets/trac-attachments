import wx

USEGCDC = True
CHANGEAXIS = True

class SketchWindow(wx.Window):
    def __init__(self,parent,ID):
        wx.Window.__init__(self,parent,ID)
        self.SetBackgroundColour(wx.WHITE)
        self.color = "Black"
        self.thickness = 1
        self.pen = wx.Pen(self.color,self.thickness,wx.SOLID)
        self.pos = (0,0)
        self.curLine = []

        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_CLOSE, self.OnClose)


    def OnPaint(self, evt):
        print("In OnPaint")


        if(USEGCDC == True):
            print("Using GCDC...")
            pdc = wx.PaintDC(self)            
            try:
                dc = wx.GCDC(pdc)
            except:
                print("GCDC Exception reverting to regular PaintDC...")
                dc = pdc
                
            if (CHANGEAXIS == True):
                print("Change Axis Orientation...")                
                dc.SetAxisOrientation(True,True)
                dc.SetDeviceOrigin(200,200)
                
            dc.SetBackground(wx.Brush(self.GetBackgroundColour()))
            dc.Clear()                

            self.TestPattern(dc)
            
        else:
            print("Using PaintDC")
            dc = wx.PaintDC(self)

            if (CHANGEAXIS == True):
                print("Change Axis Orientation...")
                dc.SetAxisOrientation(True,True)
                dc.SetDeviceOrigin(200,200)
                
            dc.SetBackground(wx.Brush(self.GetBackgroundColour()))            
            dc.Clear()
            
            self.TestPattern(dc)
            

    def TestPattern(self,dc):
        print("In TestPattern")
        dc.SetPen(self.pen)
        dc.DrawLine(10, 10, 50, 40)    #### diag
        dc.DrawLine(50, 10, 10, 40)    #### diag    
        dc.DrawLine(10, 10, 10, 40)    #### Left vertical
        dc.DrawLine(50, 10, 50, 40)    #### Right Vertical
        
        dc.DrawLine(10, 40, 50, 40)    #### Top horiz
        dc.DrawLine(10, 10, 50, 10)    #### Bottom  horiz  
        dc.DrawLine(10, 10, 0, 0)    #### Draw line to zero
        
        

    def OnClose(self,event):
        self.Destroy()

class SketchFrame(wx.Frame):
    def __init__(self,parent):
        wx.Frame.__init__(self,parent,-1, "Sketch Frame", size=(800,600))
        self.sketch = SketchWindow(self, -1)
            
    


if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = SketchFrame(None)
    frame.Show(True)
    app.MainLoop()

 	  	 
