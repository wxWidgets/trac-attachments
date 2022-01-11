#!/usr/local/bin/python
# This demo demonstrates usage of what can be done after my patches 
# have been applied
# I am not sure if the patches will help much for user-edited controls,
# however it solves problem of creating nicely highlighted output windows,
# which according to mailing list is a common problem. And using Scintilla
# just for that is a total overkill!!!


from wxPython.wx import *
from wxPython.lib.layoutf import Layoutf

if wxPlatform == '__WXMSW__':
	InputFont= (10,"Courier New")
	OutputFont= (8,"Courier New")
	TextHeight= 24
else:
	InputFont= (12,"Courier")
	OutputFont= (9,"Courier")
	TextHeight= 20

class TestWind(wxFrame):
	def __init__(self,parent,ID,title):
		wxFrame.__init__(self,parent,ID,title,wxDefaultPosition,wxSize(450,150))
		self.SetAutoLayout(true)
		self.Panel1= wxPanel(self,2)
		c1= wxLayoutConstraints()
		c1.left.SameAs(self,wxLeft)
		c1.top.SameAs(self,wxTop)
		c1.right.SameAs(self,wxRight)
		c1.bottom.SameAs(self,wxBottom);
		self.Panel1.SetConstraints(c1)

		self.Output= wxTextCtrl(self.Panel1,4,style=wxTE_MULTILINE)
		self.Output.SetEditable(1)
#		self.Output.SetBackgroundColour(wxWHITE)
		c4= wxLayoutConstraints()
		c4.left.SameAs(self.Panel1,wxLeft)
		c4.right.SameAs(self.Panel1,wxRight)
		c4.top.SameAs(self.Panel1,wxTop)
		c4.bottom.SameAs(self.Panel1,wxBottom)
		self.Output.SetConstraints(c4)
		# Add some styled text
		self.Output.AppendText('This text was added with default style set on creation of control\n')
		Font1= wxFont(InputFont[0],wxSWISS,wxNORMAL,wxNORMAL,false,InputFont[1])
		TextAttr1= wxTextAttr(wxRED,wxWHITE,Font1)
		TextAttr2= wxTextAttr(wxBLUE,wxWHITE,Font1)
		TextAttr3= wxTextAttr(wxWHITE,wxBLACK,Font1)
		TextAttr4= wxTextAttr(wxGREEN,wxColour(192,192,192),Font1)
		Font2= wxFont(InputFont[0]+5,wxSWISS,wxNORMAL,wxNORMAL,false,InputFont[1])
		TextAttr5= wxTextAttr(wxBLACK,wxWHITE,Font2)
		self.Output.SetDefaultStyle(TextAttr1)
		self.Output.AppendText('This is some RED text\n')
		self.Output.SetDefaultStyle(TextAttr2)
		self.Output.AppendText('This is some BLUE text\n')
		self.Output.SetDefaultStyle(TextAttr2)
		self.Output.AppendText('This is some BLUE ')
		self.Output.SetDefaultStyle(TextAttr1)
		self.Output.AppendText('and RED text\n')
		self.Output.SetDefaultStyle(TextAttr3)
		self.Output.AppendText('This is some WHITE on BLACK text\n')
		p1= self.Output.GetLastPosition()
		self.Output.AppendText('This is some text which was styled AFTER addition\n')
		p2= self.Output.GetLastPosition()
                        # -4 is here cause \n is in the text too, although not visible
		self.Output.SetStyle(p1+3,p2-4,TextAttr4)
		self.Output.SetDefaultStyle(TextAttr5)
		self.Output.AppendText('This is some text in different font\n')
		# lets move position back a bit
		self.Output.SetInsertionPoint(self.Output.GetLastPosition()-5)
		# and test if AppendText does what it is supposed!
		self.Output.AppendText('more text added to  end\n')
		self.Output.SetInsertionPoint(self.Output.GetLastPosition()-5)
		self.Output.SetDefaultStyle(TextAttr1)
		self.Output.WriteText('(oopsa)')
		

class TestApp(wxApp):
	def OnInit(self):
		self.frame= TestWind(NULL,-1,"TestAPP")
		self.frame.Show(true)
		self.SetTopWindow(self.frame)
		return true

App= TestApp(0)

App.MainLoop()

 	  	 
