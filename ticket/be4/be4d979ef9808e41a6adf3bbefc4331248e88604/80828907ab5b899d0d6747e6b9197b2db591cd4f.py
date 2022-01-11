from wxPython.wx import *

###########################################################
###########################################################

# A Class used to dynamically add buttons, currently only supports Horizontal
class DynamicButtonPanel(wxPanel):

	def __init__(self, parent, ButtonCB = None):
		wxPanel.__init__(self, parent, -1)

		# keep track of the parent
		self.parent = parent

		# Create the button sizer
		self.btnSizer = wxBoxSizer(wxHORIZONTAL)

		# Set the Panel's sizer
		self.SetSizer(self.btnSizer)
		self.SetAutoLayout(true)

		# a call back routine for creating a button
		self.__buttonCB = ButtonCB
		

	def SetButtonCB(self, CB):
		self.__buttonCB = CB

	# Get the sizer of dynamic button panel
	def GetSizer(self):
		return self.btnSizer

	# Make the buttons Added to the Right side
	def ShiftRight(self):
		self.btnSizer.Add(0,0,1)
		
	# Add a button to our lower button panel, return its Id
	# it will use the button callback if one has been specified
	# durring the callback it is not neccessary to use the
	# event an szToolTip, b/c this function will still take
	# care of it
	def AddButton( self, Caption, event, szToolTip=None, sizerTup=(0,wxEXPAND|wxEAST|wxWEST,5) ,**wxButtonArgs):

		if not self.__buttonCB:
			# Create new button, add to sizer
			wxBtn = wxButton( self, -1, Caption,**wxButtonArgs )
		else:
			wxBtn = self.__buttonCB(self, Caption, event, szToolTip)

		apply(self.btnSizer.Add, (wxBtn,) + sizerTup)
		# Layout the buttons
		self.Layout()
		# Create the event
		EVT_BUTTON(self, wxBtn.GetId(), event)

		# try to Add the tool tip
		try:        
			# If tool tip specified
			if szToolTip != None:
				wxBtn.SetToolTip(wxToolTip(szToolTip))
		except:
			pass
		
		return wxBtn
		

	 # Remove a button from the lower button panel (by its Id)
	def RemoveButton( self, Id ):
		# Find the child window button
		wzBtn = self.FindWindowById( Id )
		# Remove from the sizer
		self.btnSizer.Remove( wzBtn )
		# Destroy the button
		wzBtn.Destroy()
		# Re-Layout the ButtonPanel
		self.Layout()

class TestFrame2(wxFrame):
	def __init__(self):
		wxFrame.__init__(self, None, -1, "Spec", size=(640, 480))
		self.PSpanel = wxPanel(self, -1)
		self.PSpanel.SetBackgroundColour(wxRED)
		
		# ** Set AddButton to be a reference to the button panel's Add Button function **
		
		self.btnPanel = DynamicButtonPanel(self)
		self.btnPanel.SetBackgroundColour(wxBLUE)
		
		EVT_CLOSE(self, self.OnCloseWindow)


		# THESE ITEMS SHOW UP
		#xsizer = wxBoxSizer(wxHORIZONTAL)
		#xsizer.Add(wxButton(self, -1, 'A'), 0, wxEXPAND)
		#xsizer.Add(wxButton(self, -1, 'B'), 0, wxEXPAND)

		sizer = wxBoxSizer(wxVERTICAL)
		sizer.AddMany( [
				(self.PSpanel, 1, wxEXPAND),
				(self.btnPanel, 0, wxEXPAND),
				#(xsizer, 0, wxEXPAND)
			] )
		self.SetAutoLayout(true)
		self.SetSizer(sizer)

		self.Layout()

		# I am adding buttons here, but in my app 
		# they can be called after the init completely
		self.btnPanel.AddButton("Test",self.Evt)
		self.btnPanel.AddButton("Test2",self.Evt2)
		self.btnPanel.AddButton("Test3",self.Evt3)


	def Evt(self,evt):
		print 'evt 1'
		
	def Evt2(self, evt):	
		print 'evt 2'

	def Evt3(self, evt):
		print 'evt 3'
		
	def OnCloseWindow(self, event):
		self.Destroy()



app = wxPySimpleApp()
frame = TestFrame2()
frame.Show(true)
app.MainLoop()
		

 	  	 
