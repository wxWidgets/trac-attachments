# Demo of bug with RadioButtons and embedded Panels: if a RadioButton is created
# in the same panel where there is an embedded panel, the RadioButton will cause
# the program to hang when selected.  This affects Windows only.


import sys
import wx


class MyFrame ( wx.Frame ):

	def __init__ ( self, parent, title):
		wx.Frame.__init__ ( self, parent, -1, title, (-1, -1), ( 640, 480 ) )

		mainsizer = wx.BoxSizer ( wx.VERTICAL )

		testpanel = wx.Panel ( self, style=wx.SIMPLE_BORDER )
		testsizer = wx.GridBagSizer ( 10, 10 )
		testsizer.Add ( wx.RadioButton ( testpanel, -1, "1", style=wx.RB_GROUP ), ( 0, 0 ) )
		testsizer.Add ( wx.RadioButton ( testpanel, -1, "2" ), ( 0, 1 ) )

		# embedded Panel with a widget: this will crash the program when a RadioButton is selected #
		panel2 = wx.Panel ( testpanel )
		sizer2 = wx.BoxSizer ( wx.VERTICAL )
		# if the following line is removed then the RadioButtons work without errors #
		sizer2.Add ( wx.StaticText ( panel2, -1, "Label" ) )
		panel2.SetSizer ( sizer2 )
		testsizer.Add ( panel2, ( 1, 0 ) )

		testpanel.SetSizer ( testsizer )
		testpanel.Layout()
		mainsizer.Add ( testpanel, 1, flag=wx.EXPAND )

		self.SetSizer ( mainsizer )
		self.Layout()






print "platform: %s\npython version: %s\nwxPython version: %s" % ( sys.platform, sys.version, wx.__version__ )
app = wx.PySimpleApp ( redirect=0 )
frame = MyFrame ( None, "RadioButton and Embedded Panel Test" )
frame.Show()
app.MainLoop()

 	  	 
