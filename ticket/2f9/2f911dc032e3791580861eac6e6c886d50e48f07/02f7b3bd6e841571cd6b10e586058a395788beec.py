import wx

class MyApp(wx.App):
    def OnInit(self):
        frame = wx.Frame(None, -1, "Hello from wxPython")

	sizer = wx.BoxSizer(wx.VERTICAL)
	panel = wx.Panel(frame, -1, style=wx.TAB_TRAVERSAL)

	btn1 = wx.Button(panel, -1, "Button 1")
        list=wx.ListCtrl(panel, -1, size=(495, 85), style=wx.LC_REPORT|wx.SUNKEN_BORDER)
	btn2 = wx.Button(panel, -1, "Button 2")

        list.Show(True)

	col_info = wx.ListItem()
	col_info.m_mask = wx.LIST_MASK_TEXT | wx.LIST_MASK_IMAGE | wx.LIST_MASK_FORMAT
	col_info.m_image = -1
 
	col_info.m_text = "   "
	col_info.m_format = wx.LIST_FORMAT_CENTER
        list.InsertColumnInfo(0, col_info)
        list.SetColumnWidth(0, 30)

	col_info.m_text = "New Software and Add-Ons"
	col_info.m_format = wx.LIST_FORMAT_LEFT
        list.InsertColumnInfo(1, col_info)
        list.SetColumnWidth(1, 305)

	col_info.m_text = "Version"
	col_info.m_format = wx.LIST_FORMAT_LEFT
        list.InsertColumnInfo(2, col_info)
        list.SetColumnWidth(2, 60)

	sizer.Add(btn1, 0, wx.ALL | wx.ALIGN_LEFT, 5)
	sizer.Add(list, 1, wx.ALL | wx.EXPAND, 5)
	sizer.Add(btn2, 0, wx.ALL | wx.ALIGN_LEFT, 5)
  
  
	#frame.SetSize((520, 700))
	panel.SetSizer(sizer)
	sizer.Fit(frame)

        frame.Show(True)

        return True
  
app = MyApp(0)
app.MainLoop()
