
import wx
import wx.lib.scrolledpanel

class DrawTestFrame ( wx.Frame ):

	def __init__(self, parent, ID, title):
		wx.Frame.__init__(self, parent, ID, title, size=(300, 250))

		self.Bind ( wx.EVT_PAINT, self.on_paint )

		self.SetAutoLayout(True)
		self.Layout()


	def on_paint ( self, event=None ):

		max_width, max_height = self.GetClientSizeTuple()
		center_x = max_width / 2
		center_y = max_height / 2
		if ( max_width < max_height ):
			circle_width = 0.9 * max_width / 2
		else:
			circle_width = 0.9 * max_height / 2

		inner_color = "RED"
		border_color = "BLACK"
		outer_color = "YELLOW"

		dc = wx.PaintDC ( self )
		dc.Clear()
		dc.BeginDrawing()

		# draw the outer circle first #
		dc.SetBrush ( wx.Brush ( outer_color ) )
		dc.DrawCircle ( center_x, center_y, 100 )

		# now draw the inner circle with a border #
		dc.SetPen ( wx.Pen ( border_color, width=10 ) )
		dc.SetBrush ( wx.Brush ( inner_color ) )
		dc.DrawCircle ( center_x, center_y, 95 )


		dc.EndDrawing()



app = wx.PySimpleApp()
frame = DrawTestFrame ( None, -1, "Draw Test" )
frame.Show()
app.MainLoop()
 	  	 
