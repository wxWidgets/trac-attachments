"""
Illustrates a problem with SetSelection and ChangeSelection on wx.Notebook
Tested with wxPython Phoenix 3.0.2.dev77707
9/15/2014
Adam Pletcher
adam@volition-inc.com
"""
import wx

class Test_Panel( wx.Panel ):
    def __init__( self, parent ):
        wx.Panel.__init__( self, parent, -1 )

        self.parent = parent

        # Controls
        main_sizer = wx.BoxSizer( wx.VERTICAL )
        self.SetSizer( main_sizer )

        self.nbk_notebook = wx.Notebook( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize )
        self.pnl_panel = wx.Panel( self.nbk_notebook, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL | wx.BORDER_NONE )

        self.nbk_notebook.AddPage( self.pnl_panel, 'Page 1' )
        self.nbk_notebook.AddPage( self.pnl_panel, 'Page 2' )

        # Prints "2" as expected
        print( 'page count = {}'.format( self.nbk_notebook.GetPageCount( ) ) )

        # This next line will throw a wxAssertionError, saying it's out of range
        self.nbk_notebook.SetSelection( 1 )

        self.btn_close = wx.Button( self, wx.ID_CLOSE )
        main_sizer.Add( self.btn_close, 0, wx.ALL, 5 )

        # Event bindings
        self.btn_close.Bind( wx.EVT_BUTTON, self.on_close_pressed )

    def on_close_pressed( self, event ):
        self.parent.Close( )


### MAIN ###

if __name__ == '__main__':
    app = wx.App( redirect = False )
    frame = wx.Frame( None, -1, "Test Frame" )

    Test_Panel( frame )
    frame.Show( )

    app.MainLoop( )
