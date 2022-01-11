
import wx

class resultdlg1 ( wx.Dialog ):
   def __init__( self, parent ):
      wx.Dialog.__init__ ( self, parent, id = -1, title = u"Results", style = wx.DEFAULT_DIALOG_STYLE|wx.RESIZE_BORDER )

      sizer = wx.BoxSizer( wx.VERTICAL )

      b1 = wx.Button( self, wx.ID_ANY, "The buttons", wx.DefaultPosition, wx.DefaultSize, 0 )
      b2 = wx.Button( self, wx.ID_ANY, "disappear", wx.DefaultPosition, wx.DefaultSize, 0 )
      b3 = wx.Button( self, wx.ID_ANY, "as you resize the window", wx.DefaultPosition, wx.DefaultSize, 0 )

      sizer.Add( b1, 0, wx.ALL, 5 )
      sizer.Add( b2, 0, wx.ALL, 5 )
      sizer.Add( b3, 0, wx.ALL, 5 )

      # the strange behavior only happens if the panel has a sunken, raised, or double border. 
      borderstyle = wx.STATIC_BORDER
      borderstyle = wx.SUNKEN_BORDER  # broken
      #borderstyle = wx.SIMPLE_BORDER
      #borderstyle = wx.RAISED_BORDER  # broken
      #borderstyle = wx.DOUBLE_BORDER  # broken
      #borderstyle =  0
      panel = wx.Panel( self, -1, style=borderstyle)
      panel.SetMinSize( wx.Size( 230,100 ) )
      sizer.Add( panel, 1, wx.EXPAND, 0 )

      self.SetSizer( sizer )

      self.Layout()
      sizer.Fit( self )

		


app = wx.PySimpleApp()
dlg = resultdlg1(None)
dlg.ShowModal()
dlg.Destroy()
