import wx

class MyApp(wx.App):
	def OnInit(self):
		myframe = wx.Frame(None,-1,'test')
		mytext = wx.TextCtrl(myframe,-1,style=wx.TE_READONLY)	# we display the selection in it
		mytree = wx.TreeCtrl(myframe,-1,style=wx.TR_HAS_BUTTONS|wx.TR_SINGLE)	# only one item can be selected !
		rootItem = mytree.AddRoot('Root')
		# populate the tree
		for i in range(10):
			tmpkey = 'key_%s'%i
			item = mytree.AppendItem(rootItem,tmpkey)
			for j in range(10):
				mytree.AppendItem(item,'tmpkey_%s'%j)
		mytree.Expand(rootItem)
		# set events
		wx.EVT_TREE_BEGIN_DRAG(mytree,mytree.GetId(),lambda evt: evt.Allow())
		wx.EVT_TREE_SEL_CHANGED(mytree,mytree.GetId(),lambda evt: mytext.SetValue(mytree.GetItemText(mytree.GetSelection())))
		# layout
		s = wx.BoxSizer(wx.HORIZONTAL)
		s.Add(mytree,1,wx.EXPAND)
		s.Add(mytext,0,0)
		myframe.SetSizer(s)
		myframe.Layout()
		# show the window
		myframe.Show()
		return True
		
myApp = MyApp()
myApp.MainLoop()

 	  	 
