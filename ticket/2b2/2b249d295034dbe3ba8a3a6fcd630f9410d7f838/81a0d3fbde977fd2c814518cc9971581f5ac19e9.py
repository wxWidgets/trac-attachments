import wx
from wx.lib.masked import NumCtrl

print wx.version()

class Problem(wx.Dialog):
    def __init__(self, title, num2):
	wx.Dialog.__init__(self, None, -1, title)
	vbox = wx.BoxSizer(wx.VERTICAL)
	vslot1 = wx.BoxSizer(wx.VERTICAL)
	vbox.Add(vslot1, 1, wx.GROW)
	vslot2 = wx.FlexGridSizer(rows=4, cols=2, hgap=5, vgap=5)
	vbox.Add(vslot2)
	label = wx.StaticText(self, -1, 
		"""
		Typing a date and pressing enter will not yield the 
		correct date.
		""")
	vslot1.Add(label, 1, wx.ALIGN_CENTER | wx.BOTTOM, 20)
	label.SetForegroundColour("Blue")
	date_label = wx.StaticText(self, -1,
		"Date ")
	self.dpc = wx.DatePickerCtrl(self, -1, size=(120,-1),
		style=wx.TAB_TRAVERSAL|wx.TE_PROCESS_ENTER)
	self.Bind(wx.EVT_DATE_CHANGED, self.OnDateChanged, self.dpc)
	vslot2.Add(date_label)
	vslot2.Add(self.dpc)
	
	num1_label = wx.StaticText(self, -1,
		"Number 1 ")
	self.num1_numctrl = NumCtrl(self, -1, 
		fractionWidth=6, selectOnEntry=False)
	vslot2.Add(num1_label)
	vslot2.Add(self.num1_numctrl)
	
	num2_label = wx.StaticText(self, -1,
		"Number 2 ")
	self.num2_numctrl = NumCtrl(self, -1, 
		value=num2, fractionWidth=6, selectOnEntry=True)
	vslot2.Add(num2_label)
	vslot2.Add(self.num2_numctrl)

	num3_label = wx.StaticText(self, -1,
		"Number 3 ")
	self.num3_numctrl = NumCtrl(self, -1, 
		fractionWidth=2, selectOnEntry=False)
	vslot2.Add(num3_label)
	vslot2.Add(self.num3_numctrl)
	sizer = self.CreateSeparatedButtonSizer(wx.OK | wx.CANCEL)
	vbox.Add(sizer, 0, wx.GROW)
	self.SetSizer(vbox)
	self.Fit()
	self.dpc.SetFocus()
    
    def OnDateChanged(self, event):
	print self.dpc.GetValue()
	print "OnDateChanged: %s\n" % event.GetDate()

if __name__ == '__main__':
    app=wx.PySimpleApp()
    dialog = Problem('DatePicker Problem', 50.00)
    result = dialog.ShowModal()
    if result == wx.ID_OK:
	print "OK"
	print dialog.dpc.GetValue()
    else:
	print "Cancel"
    dialog.Destroy()
