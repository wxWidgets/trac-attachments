# demonstration of bug under OSX where widgets created outside of __init__ don't display properly
# when widgets (TextCtrl) are added, they show up blank: once the editable area has been selected, 
#  the value appears and the widget behaves normally


import sys
import wx
import wx.lib.scrolledpanel


class MyFrame ( wx.Frame ):

	def __init__ ( self, parent, title):
		wx.Frame.__init__ ( self, parent, -1, title )

		sizer = wx.BoxSizer ( wx.VERTICAL )

		self.index = 1

		add_button = wx.Button ( self, -1, "Add Item" )
		add_button.Bind ( wx.EVT_BUTTON, self.on_add_item )
		delete_button = wx.Button ( self, -1, "Delete Item" )
		delete_button.Bind ( wx.EVT_BUTTON, self.on_delete_item )

		sizer.Add ( add_button, border=10, flag=wx.ALL )
		sizer.Add ( delete_button, border=10, flag=wx.ALL )

		self.testpanel = wx.Panel ( self, size=(200,70), style=wx.SIMPLE_BORDER )
		self.sizer = wx.GridBagSizer ( 10, 10 )
		self.sizer.Add ( wx.TextCtrl ( self.testpanel, -1, "start" ), ( 0, 0 ) )
		self.testpanel.SetSizer ( self.sizer )
		self.testpanel.SetAutoLayout ( True )
		self.testpanel.Layout()
		sizer.Add ( self.testpanel, 1, border=10, flag=wx.ALL|wx.EXPAND )

		self.SetSizer ( sizer )
		self.Layout()


	def on_add_item ( self, event ):

		self.sizer.Add ( wx.TextCtrl ( self.testpanel, -1, "%d" %( self.index ) ), ( 0, self.index ) )
		self.index += 1
		self.testpanel.Layout()
		for index in range ( self.sizer.GetCols() ):
			widget = self.sizer.FindItemAtPosition ( ( 0, index ) ).GetWindow()
			widget.SetValue ( widget.GetValue() )
			widget.Update()
			widget.Refresh()
			widget.Update()
			widget.Refresh()
		self.testpanel.Layout()


	def on_delete_item ( self, event ):

		if ( self.index == 0 ):
			return
		item = self.sizer.FindItemAtPosition ( (0, self.index-1 ) ).GetWindow()
		self.sizer.Detach ( item )
		item.Destroy()
		self.index -= 1
		self.Layout()


print "platform: %s\npython version: %s\nwxPython version: %s" % ( sys.platform, sys.version, wx.__version__ )
app = wx.PySimpleApp ( redirect=0 )
frame = MyFrame ( None, "Sizer Test" )
frame.Show()
app.MainLoop()

 	  	 
