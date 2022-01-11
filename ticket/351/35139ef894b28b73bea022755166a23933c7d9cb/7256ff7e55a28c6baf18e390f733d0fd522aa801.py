from wxPython.wx import *

class BuggySpin(wxFrame):
	def __init__(self, parent, ID):
		wxFrame.__init__(self, parent, ID, "Bug demonstration")
		top_layout = wxBoxSizer(wxVERTICAL)

		spin = wxSpinCtrl(self, -1, style = wxSP_ARROW_KEYS | wxSP_WRAP, max = 59, min = 0, size = (40, 20))

		# The following works: 
		# spin.SetValue(5)

		# The following does not work
		spin.SetValue(0)

		top_layout.Add(spin, 0, wxALL, 8)

		self.SetAutoLayout(true)
		self.SetSizer(top_layout)
		top_layout.Fit(self)
		top_layout.SetSizeHints(self)

		self.Centre

if __name__ == "__main__":
	class BugApp(wxApp):
		def OnInit(self):
			frame = BuggySpin(NULL, -1)
			frame.Show(true)
			self.SetTopWindow(frame)
			return true

	app = BugApp(0)
	app.MainLoop()


 	  	 
