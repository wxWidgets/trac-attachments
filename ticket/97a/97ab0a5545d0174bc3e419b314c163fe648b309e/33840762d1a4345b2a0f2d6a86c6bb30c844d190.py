""" ~Minimal example of unexpected behaviour of the "Choice"
editor.
0-eth option of the Choice dropdown menu initially does not respond to selection when used
as editor with wx.propgrid.PyEnumProperty
When overriding OnSetValue in wx.propgrid.PyEnumProperty the problem persists;
if OnSetValue is not overridden the 0-eth option becomes selectable after one other option has first been selected.


System used:
Ubuntu 
wx.version: 2.9.3.1 gtk2 (classic)
Python 2.7.3 (default, Apr 20 2012, 22:39:59) 
[GCC 4.6.3]

EXPECTED BEHAVIOR:
I would expect all fields to respond to selection from initialization.
Also, according to 
http://wxpropgrid.sourceforge.net/docs/pg14/classwxBaseEnumProperty.htm#a04c13f797615778c3359e81c8155200c
the default version of the method OnSetValue does nothing, so overriding it with an empty 
method should have no effect.

OBSERVED BEHAVIOUR:
When simply setting the editor type to Choice, the 0-eth option does not respond to clicks 
in the dropdown menu until another option has first been selected; 
the 0-eth option then reponds to selection in the same way as the other fields.

When overriding OnSetValue (e.g. to convert the value to another representation),
the 0-eth option remains unselectable even when another option has first been selected.

"""

import wx
_ = wx.GetTranslation
import wx.propgrid as wxpg
import sys

############################################################################
#
# Using "Choice" as editor, and overriding OnSetValue.
# The 0-eth option in the dropdown now does not 
# respond to clicks by being selected

class Wildtype(wxpg.PyEnumProperty):
	
	def GetEditor(self):
		return "Choice"

class Mutant(wxpg.PyEnumProperty):
	
	def GetEditor(self):
		return "Choice"
	
	def OnSetValue(): 
		pass
		

############################################################################
class Frame(wx.Frame):
	def __init__(self):
		 wx.Frame.__init__(self, None, -1, "Example", size=(520,180))
		 panel = TestPanel(self)

class SmallApp(wx.App):

	def OnInit(self):
		frame = Frame()
		frame.Show()
		return True 

#
# MAIN PROPERTY GRID TEST PANEL
#
############################################################################

class TestPanel( wx.Panel ):

    def __init__( self, parent, log=sys.stdout ):
        wx.Panel.__init__(self, parent, wx.ID_ANY)

        self.panel = panel = wx.Panel(self, wx.ID_ANY)
        topsizer = wx.BoxSizer(wx.VERTICAL)

        # Difference between using PropertyGridManager vs PropertyGrid is that
        # the manager supports multiple pages and a description box.
        self.pg = pg = wxpg.PropertyGridManager(panel,
                        style=wxpg.PG_SPLITTER_AUTO_CENTER |
                              wxpg.PG_AUTO_SORT |
                              wxpg.PG_TOOLBAR)

        # Adding the property
        pg.AddPage( "Page 1" )
	
        pg.Append( wxpg.PropertyCategory("Example of unexpected behaviour of the \"Choice\" editor") )
	
	pg.Append( Wildtype("Enum with Choice as editor","Enum",
                                     ['wxPython Rules',
                                      'wxPython Rocks',
                                      'wxPython Is The Best'],
                                     [10,11,12],
                                     0) )
				     
	pg.Append( Mutant("Same with overridden OnSetValue",
					"Overridden OnSetValue",
                                     ['wxPython Rules',
                                      'wxPython Rocks',
                                      'wxPython Is The Best'],
                                     [10,11,12],
                                     0) )
	""" wxPython Is The Best, and does indeed Rock without issue, 
	but under these conditions it fails to Rule when that option is selected."""

        topsizer.Add(pg, 1, wx.EXPAND)

        panel.SetSizer(topsizer)
        topsizer.SetSizeHints(panel)

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(panel, 1, wx.EXPAND)
        self.SetSizer(sizer)
        self.SetAutoLayout(True)

#----------------------------------------------------------------------

def runTest( frame, nb, log ):
    win = TestPanel( nb, log )
    return win

#----------------------------------------------------------------------



if __name__ == '__main__':
	import sys,os 
	
	app = SmallApp()
	app.MainLoop()
