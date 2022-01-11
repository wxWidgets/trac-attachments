# demonstration of sizer spacing bug with wx.GridBagSizer
# the GridBagSizer always adds 4 pixels to every border
# the bug is not found in any other sizer (BoxSizer and FlexGridSizer are demonstrated to work correctly)
# resolution: spacing issue can be fixed by setting the EmptyCellSize to ( 0, 0 )
# TO DO: file a bug report, since the empty cell size should not uniformly affect default cell spacing #


import sys
import wx


class MyFrame ( wx.Frame ):

	def __init__ ( self, parent, title ):

		wx.Frame.__init__ ( self, parent, -1, title )
		panel = wx.Panel ( self )

		border = 0
		number_items = 15
		sizer = wx.BoxSizer ( wx.HORIZONTAL )

		boxsizer = wx.BoxSizer ( wx.VERTICAL )
		boxsizer.Add ( wx.StaticText ( panel, -1, "BoxSizer" ), border=border, flag=wx.BOTTOM )
		for index in range ( number_items ):
			boxsizer.Add ( wx.StaticText ( panel, -1, "%d" % ( index ) ), border=border, flag=wx.BOTTOM )
		sizer.Add ( boxsizer, border=10, flag=wx.ALL )

		gbsizer = wx.GridBagSizer ( border, border )
		gbsizer.Add ( wx.StaticText ( panel, -1, "GridBagSizer" ), ( 0, 0 ) )
		for index in range ( number_items ):
			gbsizer.Add ( wx.StaticText ( panel, -1, "%d" % ( index ) ), ( index+1, 0 ) )
		sizer.Add ( gbsizer, border=10, flag=wx.ALL )

		offset = 4
		boxsizer2 = wx.BoxSizer ( wx.VERTICAL )
		boxsizer2.Add ( wx.StaticText ( panel, -1, "BoxSizer+%s" % ( offset ) ), border=border+offset, flag=wx.BOTTOM )
		for index in range ( number_items ):
			boxsizer2.Add ( wx.StaticText ( panel, -1, "%d" % ( index ) ), border=border+offset, flag=wx.BOTTOM )
		sizer.Add ( boxsizer2, border=10, flag=wx.ALL )

		gbsizer = wx.GridBagSizer ( border, border )
		gbsizer.SetEmptyCellSize ( ( 0, 0 ) )
		gbsizer.Add ( wx.StaticText ( panel, -1, "GBSizer (fixed empty cell size)" ), ( 0, 0 ) )
		for index in range ( number_items ):
			gbsizer.Add ( wx.StaticText ( panel, -1, "%d" % ( index ) ), ( index+1, 0 ) )
		sizer.Add ( gbsizer, border=10, flag=wx.ALL )

		fgsizer = wx.FlexGridSizer ( number_items+1, 1, border, border )
		fgsizer.Add ( wx.StaticText ( panel, -1, "FlexGridSizer" ) )
		for index in range ( number_items ):
			fgsizer.Add ( wx.StaticText ( panel, -1, "%d" % ( index ) ) )
		sizer.Add ( fgsizer, border=10, flag=wx.ALL )

		panel.SetSizer ( sizer )
		panel.Layout()


print "platform: %s\npython version: %s\nwxPython version: %s" % ( sys.platform, sys.version, wx.__version__ )
app = wx.PySimpleApp ( redirect=0 )
frame = MyFrame ( None, "Sizer Spacing Test" )
frame.Show()
app.MainLoop()

 	  	 
