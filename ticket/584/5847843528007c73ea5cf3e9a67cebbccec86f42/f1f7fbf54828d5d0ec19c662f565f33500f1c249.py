from wxPython.wx import *
#from wxPython.lib.rightalign import wxRightTextCtrl
#import wxPython.lib.rightalign

import sys

class MyList(wxListCtrl):
	def __init__(self, parent, id, pos = wxDefaultPosition, size = wxDefaultSize, style = wxLC_ICON, validator = wxDefaultValidator, name = "listCtrl"):
		wxListCtrl.__init__(self, parent, id, pos, size, style, validator, name)

	def OnGetItemText(self, item, column):
		return "Item: %d, column %d" % (item, column)

#	def OnGetItemImage(item):
#		return -1

class MyFrame(wxFrame):
	def __init__(self, parent, ID, title, pos=wxDefaultPosition,
				 size=wxDefaultSize, style=wxDEFAULT_FRAME_STYLE):

		wxFrame.__init__(self, parent, ID, title, pos, size, style)

		# Panel
		panel = wxPanel(self, -1)

		sizer = wxBoxSizer(wxVERTICAL)
		panel.SetSizer(sizer)

		# List
		list = MyList(panel, 1004, style = wxLC_REPORT | wxLC_VIRTUAL)
		#list.SetWindowStyleFlag(list.GetWindowStyleFlag() | wxLC_VIRTUAL)
		sizer.Add(
		    list,
		    1, # make vertically stretchable
		    wxEXPAND | # make horizontally stretchable
		    wxALL, # and make border all around
		    10 ); # set border width to 10

		list.InsertColumn(0, "alpha")
		list.InsertColumn(1, "beta")
		list.InsertColumn(2, "gamma")

		list.SetItemCount(3)

# Every wxWindows application must have a class derived from wxApp
class MyApp(wxApp):

	# wxWindows calls this method to initialize the application
	def OnInit(self):

		# Create an instance of our customized Frame class
		frame = MyFrame(NULL, -1, "This is a test")
		frame.Show(true)

		# Tell wxWindows that this is our main window
		self.SetTopWindow(frame)

		# Return a success flag
		return true

def main():
	app = MyApp(0)     # Create an instance of the application class
	app.MainLoop()     # Tell it to start processing events


if __name__ == "__main__":
	main()

 	  	 
