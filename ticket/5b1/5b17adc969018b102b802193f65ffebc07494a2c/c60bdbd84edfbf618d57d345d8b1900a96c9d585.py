import wx
import threading

class CursorWindow( wx.Window ):

	def __init__( self, parent, id ):
		wx.Window.__init__( self, parent, id )
		self.__myControlPress = False
		self.__myAltPress = False
		self.__myTimer = None
		self.__myApp = None

		wx.EVT_KEY_DOWN( self, self.OnKeyDown )
		wx.EVT_KEY_UP( self, self.OnKeyUp )


	def MySetCursor( self, cursor ):
		self.__myTimer = threading.Timer( .01, self.OnTimer, [ cursor ] )
		self.__myTimer.start()


	def OnTimer( self, cursor ):
		self.__myTimer.cancel()
		self.__myTimer = None
		self.SetCursor( cursor )


	def OnKeyDown( self, event ):
		if event.ControlDown() and not self.__myControlPress:
			self.__myControlPress = True
			self.MySetCursor( wx.CROSS_CURSOR )
		if event.AltDown() and not self.__myAltPress:
			self.__myAltPress = True
			self.SetCursor( wx.CROSS_CURSOR )


	def OnKeyUp( self, event ):
		if self.__myControlPress:
			self.__myControlPress = False
			self.MySetCursor( wx.STANDARD_CURSOR )
		if self.__myAltPress:
			self.__myAltPress = False
			self.SetCursor( wx.STANDARD_CURSOR )


class CursorFrame( wx.Frame ):

	def __init__( self, parent ):
		wx.Frame.__init__( self, parent, -1, 'Cursor Window', size = ( 400, 300 ) )
		self.__myCursorWindow = CursorWindow( self, -1 )


if __name__ == '__main__':
	app = wx.PySimpleApp()
	frame = CursorFrame( None )
	frame.Show( True )
	app.MainLoop()

 	  	 
