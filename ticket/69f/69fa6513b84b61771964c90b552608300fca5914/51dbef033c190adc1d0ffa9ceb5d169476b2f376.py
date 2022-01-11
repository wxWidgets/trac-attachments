"""(Unfinished) directory-editing control"""
from wxPython.wx import *
##from wxoo import events, objectlist

class DirectorySelection( wxGenericDirCtrl ):
	"""Control for selecting a directory from the local drives

	This is just a minor sub-classing of wxGenericDirCtrl to support
	wxoo events.
	"""
	_currentValue = ""
	def __init__(
		self, parent, id = -1,
		dir = "",
		pos = wxDefaultPosition, size = wxDefaultSize,
		style = wxDIRCTRL_3D_INTERNAL|wxSUNKEN_BORDER| wxDIRCTRL_DIR_ONLY ,
		filter = "",
		defaultFilter = 0,
		name = "directoryselection",
		value = None,
	):
		wxGenericDirCtrl.__init__( self, parent, id, dir, pos, size, style, filter, defaultFilter, name )
		tree = self.GetTreeCtrl()
		EVT_TREE_SEL_CHANGED( tree, tree.GetId(), self.OnSelectionChanged )
		if value is not None:
			self.SetValue(value)
	def GetValue( self ):
		"""Get the current value of the control"""
		return self.GetPath()
	def SetValue( self, value ):
		"""Set the current value of the control"""
		self.SetPath( value )
		self.ExpandPath( value )
		self._currentValue = value
	def OnSelectionChanged( self, event ):
		"""Send a wxoo selection-changed event"""
		print 'selection changed', event
		# Crashes on the following line during shutdown...
		value = self.GetValue()
		return
##		if event and self and events.ValueChangedEvent and self.GetTreeCtrl():
##			print "retrieving value"
##			value = self.GetValue()
##			print "sending event"
##			events.send(
##				self,
##				events.ValueChangedEvent,
##				value,
##				self._currentValue,
##			)
##		print 'finished selection changed'

##class FileList( objectlist.ObjectList ):
##	"""File-list control with icon and view-type support"""


if __name__ == "__main__":
	class TestApplication (wxPySimpleApp):
		def OnChange( self, event ):
			print 'changed', event.object
		def OnInit(self):
			wxInitAllImageHandlers()
			frame =wxFrame (NULL, -1, "test", size = (600,300))
##			events.EVT_VALUECHANGED( frame, -1, self.OnChange )
			panel = DirectorySelection(frame, value= "C:\\Documents and Settings\\" )
			frame.Show (1)
			self.SetTopWindow(frame)
			return 1
	
	app = TestApplication ()
	app.MainLoop()


 	  	 
