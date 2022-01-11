# test of the wx.SHAPED and wx.EXPAND flags with proportions
# results:
# - expand does not seem to work at all
# - proportion with shaped positions the widget horizontally correctly with proportion 0,
#   but is offset to the left for higher proportions
# - vertical positioning with shaped only works with proportion 0

import sys
import wx

class MyFrame ( wx.Frame ):

	def __init__ ( self, parent, title ):

		wx.Frame.__init__ ( self, parent, -1, title )
		panel = wx.Panel ( self )

		sizer = wx.BoxSizer ( wx.VERTICAL )
		sizer.Add ( wx.StaticText ( panel, -1, "Flag test in a BoxSizer" ) )
		sizer.Add ( wx.StaticText ( panel, -1, "Expand, centered, 0 proportion" ), 0, flag=wx.EXPAND|wx.ALIGN_CENTER|wx.ALIGN_CENTER_VERTICAL )
		sizer.Add ( wx.StaticText ( panel, -1, "Shaped, centered, 0 proportion" ), 0, flag=wx.SHAPED|wx.ALIGN_CENTER|wx.ALIGN_CENTER_VERTICAL )
		sizer.Add ( wx.StaticText ( panel, -1, "Expand, centered, 1 proportion" ), 1, flag=wx.EXPAND|wx.ALIGN_CENTER|wx.ALIGN_CENTER_VERTICAL )
		sizer.Add ( wx.StaticText ( panel, -1, "Shaped, centered, 1 proportion" ), 1, flag=wx.SHAPED|wx.ALIGN_CENTER|wx.ALIGN_CENTER_VERTICAL )
		sizer.Add ( wx.StaticText ( panel, -1, "Expand, centered, 2 proportion" ), 2, flag=wx.EXPAND|wx.ALIGN_CENTER|wx.ALIGN_CENTER_VERTICAL )
		sizer.Add ( wx.StaticText ( panel, -1, "Shaped, centered, 2 proportion" ), 2, flag=wx.SHAPED|wx.ALIGN_CENTER|wx.ALIGN_CENTER_VERTICAL )
		sizer.Add ( wx.StaticText ( panel, -1, "Expand, centered, 3 proportion" ), 3, flag=wx.EXPAND|wx.ALIGN_CENTER|wx.ALIGN_CENTER_VERTICAL )
		sizer.Add ( wx.StaticText ( panel, -1, "Shaped, centered, 3 proportion" ), 3, flag=wx.SHAPED|wx.ALIGN_CENTER|wx.ALIGN_CENTER_VERTICAL )
		sizer.Add ( wx.StaticText ( panel, -1, "Expand, Shaped, centered, 0 proportion" ), 0, flag=wx.EXPAND|wx.SHAPED|wx.ALIGN_CENTER|wx.ALIGN_CENTER_VERTICAL )
		sizer.Add ( wx.StaticText ( panel, -1, "Expand, Shaped, centered, 1 proportion" ), 1, flag=wx.EXPAND|wx.SHAPED|wx.ALIGN_CENTER|wx.ALIGN_CENTER_VERTICAL )

		panel.SetSizer ( sizer )
		panel.Layout()

print "platform: %s\npython version: %s\nwxPython version: %s" % ( sys.platform, sys.version, wx.__version__ )
app = wx.PySimpleApp ( redirect=0 )
frame = MyFrame ( None, "Shaped Flag Test" )
frame.Show()
app.MainLoop()

 	  	 
