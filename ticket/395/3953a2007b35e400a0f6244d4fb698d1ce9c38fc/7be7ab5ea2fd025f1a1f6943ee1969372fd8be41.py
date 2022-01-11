# -*- coding: utf-8 -*- 

###########################################################################
## Python code generated with wxFormBuilder (version Jun 17 2015)
## http://www.wxformbuilder.org/
##
## PLEASE DO "NOT" EDIT THIS FILE!
###########################################################################

import wx
import wx.xrc
import wx.grid

###########################################################################
## Class TestFrame
###########################################################################

class TestFrame ( wx.Frame ):
	
	def __init__( self, parent ):
		wx.Frame.__init__ ( self, parent, id = wx.ID_ANY, title = u"Test Manager", pos = wx.DefaultPosition, size = wx.Size( 846,606 ), style = wx.CAPTION|wx.CLOSE_BOX|wx.RESIZE_BORDER|wx.TAB_TRAVERSAL )
		
		self.SetSizeHintsSz( wx.DefaultSize, wx.DefaultSize )
		self.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BTNFACE ) )
		
		TestFrameSizer = wx.BoxSizer( wx.VERTICAL )
		
		self.CommandPanel = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		self.CommandPanel.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_INACTIVECAPTION ) )
		
		SuperUserKeySizer = wx.BoxSizer( wx.VERTICAL )
		
		self.CMDLbl = wx.StaticText( self.CommandPanel, wx.ID_ANY, u"Command Panel", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.CMDLbl.Wrap( -1 )
		self.CMDLbl.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, False, wx.EmptyString ) )
		
		SuperUserKeySizer.Add( self.CMDLbl, 0, wx.ALL|wx.ALIGN_CENTER_HORIZONTAL, 5 )
		
		self.CMDButton = wx.Button( self.CommandPanel, wx.ID_ANY, u"Create RecordSetGrid", wx.DefaultPosition, wx.DefaultSize, 0 )
		SuperUserKeySizer.Add( self.CMDButton, 0, wx.ALL|wx.ALIGN_CENTER_HORIZONTAL|wx.EXPAND, 5 )
		
		
		self.CommandPanel.SetSizer( SuperUserKeySizer )
		self.CommandPanel.Layout()
		SuperUserKeySizer.Fit( self.CommandPanel )
		TestFrameSizer.Add( self.CommandPanel, 0, wx.ALL|wx.EXPAND, 2 )
		
		self.recordSetGridPanel = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		self.recordSetGridPanel.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_WINDOW ) )
		
		recordSetGridSizer = wx.BoxSizer( wx.VERTICAL )
		
		self.recordSetGrid = wx.grid.Grid( self.recordSetGridPanel, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, 0 )
		
		# Grid
		self.recordSetGrid.CreateGrid( 5, 5 )
		self.recordSetGrid.EnableEditing( False )
		self.recordSetGrid.EnableGridLines( True )
		self.recordSetGrid.EnableDragGridSize( False )
		self.recordSetGrid.SetMargins( 0, 0 )
		
		# Columns
		self.recordSetGrid.EnableDragColMove( True )
		self.recordSetGrid.EnableDragColSize( True )
		self.recordSetGrid.SetColLabelSize( 20 )
		self.recordSetGrid.SetColLabelAlignment( wx.ALIGN_CENTRE, wx.ALIGN_CENTRE )
		
		# Rows
		self.recordSetGrid.AutoSizeRows()
		self.recordSetGrid.EnableDragRowSize( False )
		self.recordSetGrid.SetRowLabelSize( 50 )
		self.recordSetGrid.SetRowLabelAlignment( wx.ALIGN_RIGHT, wx.ALIGN_CENTRE )
		
		# Label Appearance
		self.recordSetGrid.SetLabelBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_INACTIVECAPTION ) )
		
		# Cell Defaults
		self.recordSetGrid.SetDefaultCellBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BTNFACE ) )
		self.recordSetGrid.SetDefaultCellAlignment( wx.ALIGN_LEFT, wx.ALIGN_CENTRE )
		recordSetGridSizer.Add( self.recordSetGrid, 1, wx.ALL|wx.EXPAND, 4 )
		
		
		self.recordSetGridPanel.SetSizer( recordSetGridSizer )
		self.recordSetGridPanel.Layout()
		recordSetGridSizer.Fit( self.recordSetGridPanel )
		TestFrameSizer.Add( self.recordSetGridPanel, 1, wx.BOTTOM|wx.EXPAND|wx.LEFT|wx.RIGHT, 5 )
		
		self.ResultPanel = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		self.ResultPanel.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_INACTIVECAPTION ) )
		
		ResultSizer = wx.BoxSizer( wx.VERTICAL )
		
		self.RESLbl = wx.StaticText( self.ResultPanel, wx.ID_ANY, u"Result Panel", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.RESLbl.Wrap( -1 )
		self.RESLbl.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, False, wx.EmptyString ) )
		
		ResultSizer.Add( self.RESLbl, 0, wx.ALL|wx.ALIGN_CENTER_HORIZONTAL, 5 )
		
		self.PBReportText = wx.TextCtrl( self.ResultPanel, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.Size( -1,100 ), wx.TE_MULTILINE )
		ResultSizer.Add( self.PBReportText, 1, wx.ALL|wx.EXPAND, 5 )
		
		
		self.ResultPanel.SetSizer( ResultSizer )
		self.ResultPanel.Layout()
		ResultSizer.Fit( self.ResultPanel )
		TestFrameSizer.Add( self.ResultPanel, 1, wx.ALL|wx.EXPAND, 2 )
		
		self.LicenseManagerPanel = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		self.LicenseManagerPanel.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_INACTIVECAPTION ) )
		
		LicenseManagerSizer = wx.BoxSizer( wx.VERTICAL )
		
		self.LMLbl = wx.StaticText( self.LicenseManagerPanel, wx.ID_ANY, u"Input values", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.LMLbl.Wrap( -1 )
		self.LMLbl.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, False, wx.EmptyString ) )
		
		LicenseManagerSizer.Add( self.LMLbl, 0, wx.ALL|wx.ALIGN_CENTER_HORIZONTAL, 5 )
		
		LMCustomerSizer = wx.BoxSizer( wx.VERTICAL )
		
		LMHostnamesSizer = wx.BoxSizer( wx.HORIZONTAL )
		
		self.CharacterLbl = wx.StaticText( self.LicenseManagerPanel, wx.ID_ANY, u"Character", wx.DefaultPosition, wx.Size( 60,-1 ), 0 )
		self.CharacterLbl.Wrap( -1 )
		LMHostnamesSizer.Add( self.CharacterLbl, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 5 )
		
		self.CharacterText = wx.TextCtrl( self.LicenseManagerPanel, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.CharacterText.SetMinSize( wx.Size( -1,100 ) )
		
		LMHostnamesSizer.Add( self.CharacterText, 1, wx.ALL, 5 )
		
		self.OccursLbl = wx.StaticText( self.LicenseManagerPanel, wx.ID_ANY, u"Occurences", wx.DefaultPosition, wx.Size( 60,-1 ), 0 )
		self.OccursLbl.Wrap( -1 )
		LMHostnamesSizer.Add( self.OccursLbl, 0, wx.ALIGN_CENTER_VERTICAL|wx.ALL, 5 )
		
		self.OccursText = wx.TextCtrl( self.LicenseManagerPanel, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.OccursText.SetMinSize( wx.Size( -1,100 ) )
		
		LMHostnamesSizer.Add( self.OccursText, 1, wx.ALL, 5 )
		
		
		LMCustomerSizer.Add( LMHostnamesSizer, 1, wx.EXPAND, 5 )
		
		
		LicenseManagerSizer.Add( LMCustomerSizer, 1, wx.EXPAND, 5 )
		
		
		self.LicenseManagerPanel.SetSizer( LicenseManagerSizer )
		self.LicenseManagerPanel.Layout()
		LicenseManagerSizer.Fit( self.LicenseManagerPanel )
		TestFrameSizer.Add( self.LicenseManagerPanel, 0, wx.EXPAND |wx.ALL, 2 )
		
		
		self.SetSizer( TestFrameSizer )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.CMDButton.Bind( wx.EVT_BUTTON, self.CMDButtonOnButtonClick )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def CMDButtonOnButtonClick( self, event ):
		event.Skip()
	

