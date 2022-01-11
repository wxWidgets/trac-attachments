from wxPython.wx import *



app = wxPySimpleApp()
frame = wxFrame(None,-1,'title')

sizer = wxBoxSizer(wxVERTICAL)
frame.SetSizer(sizer)

replacetext = "TEXT NOT REPLACED"
removetext = "TEXT NOT REMOVED"

text1 = wxTextCtrl(frame,-1,replacetext)
text2 = wxTextCtrl(frame,-1,removetext)

text1.Replace(4,9," ")

val = text1.GetValue()
if val == "TEXT REPLACED":
    print "Replace succeeded"
else:
    print "Replace failed"

val = text2.GetValue()
text2.Remove(5,9)
if text2.GetValue() == "TEXT REMOVED":
    print "Remove succeeded"
else:
    print "Remove failed"


sizer.Add(text1,1,wxEXPAND)
sizer.Add(text2,1,wxEXPAND)


    
frame.Show()
app.MainLoop()

 	  	 
