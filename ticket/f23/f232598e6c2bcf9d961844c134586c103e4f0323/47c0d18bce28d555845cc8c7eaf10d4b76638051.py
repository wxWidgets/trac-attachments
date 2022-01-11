import wx

#import wx.lib.ogl as ogl
from wx.lib.ogl import *
       

class AppFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__( self,
                          None, -1, "Demo",
                          size=(600,400),
                          style=wx.DEFAULT_FRAME_STYLE )

        sizer = wx.BoxSizer( wx.VERTICAL )
        # put stuff into sizer

        canvas = ShapeCanvas( self )
        sizer.Add( canvas, 1, wx.GROW )

        canvas.SetBackgroundColour( "WHITE" )

        diagram = Diagram()
        canvas.SetDiagram( diagram )
        diagram.SetCanvas( canvas )
                  
        
        
        shape = RectangleShape(40,50)
        shape.SetX(140)
        shape.SetY(60)
	shape.SetShadowMode(SHADOW_RIGHT)
        canvas.AddShape( shape )
    
	shape2 = RectangleShape(40,50)
        shape2.SetX(340)
        shape2.SetY(90)
	shape2.SetShadowMode(SHADOW_RIGHT)
        canvas.AddShape( shape2 )

	line = LineShape()
	line.SetTo(shape)
	line.SetFrom(shape2)
	canvas.AddShape(line)
        diagram.ShowAll( 1 )
        
        # apply sizer
        self.SetSizer(sizer)
        self.SetAutoLayout(1)
        self.Show(1)

app = wx.PySimpleApp()
OGLInitialize()
frame = AppFrame()
app.MainLoop()

 	  	 
