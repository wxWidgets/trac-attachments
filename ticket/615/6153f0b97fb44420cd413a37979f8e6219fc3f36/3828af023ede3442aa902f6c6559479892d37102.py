from wxPython.wx import *
import weakref

class EXScript:
	name = "hi"
	

def getScripts( ):
	"""Retrieve the current set of scripts"""
	return [ EXScript(), EXScript(),EXScript()]

class ScriptMenu( wxMenu ):
	def __init__( self, parent, *arguments, **namedarguments ):
		wxMenu.__init__( self, *arguments, **namedarguments)
		self.parent = weakref.ref( parent )
		self.items = []
		# add an item because updateUI isn't called without children
		ID = wxNewId()
		mitem = wxMenuItem ( self, ID, "sdf","whatever")
		self.AppendItem( mitem )
		self.items.append( mitem)
		EVT_UPDATE_UI( parent, ID, self.OnUpdateUI )
	def OnUpdateUI( self, event=None ):
		"""Handle the request to update the UI by updating this menu"""
		# self.Clear()
		parent = self.parent()
		if parent:
			menuitems = []
			for item in getScripts():
				mitem = None
				if hasattr( item, '_v_scriptID'):
					mitem = self.FindItemById( item._v_scriptID )
				if not mitem:
					# build a new item for it
					item._v_scriptID = ID = wxNewId()
					label = item.name
					description = "Run the script %s"%(label)
					mitem = wxMenuItem ( self, ID, label,description)
					self.AppendItem( mitem )
					self.SetHelpString( ID, description )
					EVT_MENU( parent, ID, self.OnSelection )
				menuitems.append( mitem )
			bad = []
			for item in self.items:
				if item not in menuitems:
					print item
					# crashes here...
					self.RemoveItem( item )
			self.items = menuitems
		# do this eventually...
##		EVT_UPDATE_UI( parent, ID, self.OnUpdateUI )
				
	def OnSelection( self, event ):
		"""A script was selected to be run"""
		print 'on selection', event


class TestFrame( wxFrame ):
	def menu( self ):
		menuSet = wxMenuBar()
		menu = ScriptMenu( self )
		menuSet.Append( menu, "Scripts" )
		self.SetMenuBar( menuSet )

if __name__ == "__main__":
	class TestApplication (wxPySimpleApp):
		def OnInit(self):
			frame =TestFrame(NULL, -1, "Test", size = (300,300))
			frame.menu()
			frame.Show (1)
			self.SetTopWindow(frame)
			return 1
	
	app = TestApplication ()
	app.MainLoop()


 	  	 
