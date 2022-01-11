from wxPython.wx import *
from wxPython.gizmos import *

app = wxPySimpleApp()
frame = wxFrame(None, wxNewId(), "TestFrame")

scroller = wxSplitterScrolledWindow(frame, -1, style=wxCLIP_CHILDREN |
                                    wxVSCROLL)
splitter = wxThinSplitterWindow(scroller, -1)
splitter.SetSashSize(2)

tree = wxRemotelyScrolledTreeCtrl(splitter, wxNewId()
                                  # Uncomment this to cause the crash
                                  #, style=wxTR_HIDE_ROOT
                                  )
tree.AddRoot("root")
comp = wxTreeCompanionWindow(splitter, wxNewId())

splitter.SplitVertically(tree, comp, 150)
scroller.SetTargetWindow(tree)
scroller.EnableScrolling(False, False)

comp.SetTreeCtrl(tree)
tree.SetCompanionWindow(comp)

box = wxBoxSizer(wxHORIZONTAL)
box.Add(scroller, 1, wxEXPAND | wxALL, 0)
frame.SetAutoLayout(True)
frame.SetSizer(box)

frame.Show(True)
app.MainLoop()

 	  	 
