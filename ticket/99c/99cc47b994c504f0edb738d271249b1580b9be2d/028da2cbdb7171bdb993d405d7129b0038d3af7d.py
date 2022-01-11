#!/usr/bin/python

import wx
import wx.lib.mixins.listctrl  as  listmix
import wx.lib.mixins.treemixin as treemixin
import wx.gizmos


'''
Description: Fatal crash using wx.gizmos.TreeListCtrl when collapsing an item after expanding it

Version tested : python 2.5, wxPython 2.8.7.1
Platform tested: OSX 10.5

Steps to Reproduce:
1) run this script
2) expand a line
3) collapse the line
Result: Crash
Expected: No Crash

Note: If the # of columns is reduced (to say 4) then the crash will not occur.

Process:         Python [784]
Path:            /Library/Frameworks/Python.framework/Versions/2.5/Resources/Python.app/Contents/MacOS/Python
Identifier:      org.python.python
Version:         2.5a0 (2.5alpha0)
Code Type:       X86 (Native)
Parent Process:  bash [237]

Date/Time:       2008-04-25 21:16:28.803 -0700
OS Version:      Mac OS X 10.5.2 (9C7010)
Report Version:  6

Exception Type:  EXC_BAD_ACCESS (SIGBUS)
Exception Codes: KERN_PROTECTION_FAILURE at 0x0000000000ffdff0
Crashed Thread:  0

Thread 0 Crashed:
0   libSystem.B.dylib             	0xffff0b1a __memcpy + 890
1   libwx_macd-2.8.0.dylib        	0x01dedc65 wxBaseArrayShort::Realloc(unsigned long) + 59
2   libwx_macd-2.8.0.dylib        	0x01deec2b wxBaseArrayShort::Grow(unsigned long) + 65
3   libwx_macd-2.8.0.dylib        	0x01deee6a wxBaseArrayShort::Add(short, unsigned long) + 48
4   _gizmos.so                    	0x1a2bb7c7 wxTreeListMainWindow::SetItemImage(wxTreeItemId const&, int, int, wxTreeItemIcon) + 407 (dynarray.h:993)
5   _gizmos.so                    	0x1a2db63d _wrap_TreeListCtrl_SetItemImage + 739 (wxPython.h:48)
6   org.python.python             	0x003f3ceb PyObject_Call + 45 (abstract.c:1860)
7   org.python.python             	0x0047c5d4 PyEval_EvalFrameEx + 14801 (ceval.c:3846)
8   org.python.python             	0x0047f482 PyEval_EvalCodeEx + 1819 (ceval.c:2833)
9   org.python.python             	0x0047d108 PyEval_EvalFrameEx + 17669 (ceval.c:3662)
10  org.python.python             	0x0047e2e4 PyEval_EvalFrameEx + 22241 (ceval.c:3652)
11  org.python.python             	0x0047e2e4 PyEval_EvalFrameEx + 22241 (ceval.c:3652)
12  org.python.python             	0x0047e2e4 PyEval_EvalFrameEx + 22241 (ceval.c:3652)
13  org.python.python             	0x0047f482 PyEval_EvalCodeEx + 1819 (ceval.c:2833)
14  org.python.python             	0x0047d108 PyEval_EvalFrameEx + 17669 (ceval.c:3662)
15  org.python.python             	0x0047f482 PyEval_EvalCodeEx + 1819 (ceval.c:2833)
16  org.python.python             	0x00414dfb function_call + 320 (funcobject.c:517)
17  org.python.python             	0x003f3ceb PyObject_Call + 45 (abstract.c:1860)
18  org.python.python             	0x003fb80c instancemethod_call + 401 (classobject.c:2493)
19  org.python.python             	0x003f3ceb PyObject_Call + 45 (abstract.c:1860)
20  org.python.python             	0x00477d7e PyEval_CallObjectWithKeywords + 112 (ceval.c:3435)
21  _core_.so                     	0x0180affa wxPyCallback::EventThunker(wxEvent&) + 234 (helpers.cpp:1666)
22  libwx_macd-2.8.0.dylib        	0x01e73a4e wxEvtHandler::ProcessEventIfMatches(wxEventTableEntryBase const&, wxEvtHandler*, wxEvent&) + 108
23  libwx_macd-2.8.0.dylib        	0x01e73af4 wxEvtHandler::SearchDynamicEventTable(wxEvent&) + 80
24  libwx_macd-2.8.0.dylib        	0x01e74889 wxEvtHandler::ProcessEvent(wxEvent&) + 225
25  libwx_macd-2.8.0.dylib        	0x01fc0295 wxWindowBase::TryParent(wxEvent&) + 101
26  libwx_macd-2.8.0.dylib        	0x01e74855 wxEvtHandler::ProcessEvent(wxEvent&) + 173
27  _gizmos.so                    	0x1a2c146b wxTreeListMainWindow::Collapse(wxTreeItemId const&) + 359 (treelistctrl.cpp:2574)
28  _gizmos.so                    	0x1a2c4287 wxTreeListMainWindow::OnMouse(wxMouseEvent&) + 1489 (treelistctrl.cpp:2584)
29  libwx_macd-2.8.0.dylib        	0x01e73a4e 
'''
#----------------------------------------------------------------------

class JobList(treemixin.VirtualTree, wx.gizmos.TreeListCtrl):
    def __init__(self, parent, id=-1):
        super(JobList, self).__init__(parent, id, 
            style=wx.TR_DEFAULT_STYLE
                 |wx.TR_FULL_ROW_HIGHLIGHT
                 |wx.TR_HIDE_ROOT
            )

        size = (16,16)
        self.imageList = wx.ImageList(*size)
        for art in wx.ART_FOLDER, wx.ART_FILE_OPEN, wx.ART_NORMAL_FILE:
            self.imageList.Add(wx.ArtProvider.GetBitmap(art, wx.ART_OTHER, 
                                                        size))
        self.AssignImageList(self.imageList)
        
        # Set Columns and Sort
        self.SetColumnHeaders()
        self.RefreshItems()


    # ---------------------
    # Column Functions
    # ---------------------
    def SetColumnHeaders(self):
        for i in range(8):
            self.AddColumn('Column%i'%i)
        return

    # --------------------
    # Virtual List Methods
    # --------------------

    def OnGetChildrenCount(self, indices):
        if len(indices) > 2:
            return 0
        else:
            return 4
        

    def OnGetItemText(self, indices, col=0):
        return "item %s"%str(indices)


    def OnGetItemImage(self, indices, which, column=0):
        return -1
        

# -------------------------------------

class MyApp(wx.App):
    def OnInit(self):
        # create the mainFrame window
        frame = wx.Frame(None, wx.NewId(), "Job List", size=(800,400))
        self.SetTopWindow(frame)

        jobList= JobList(frame, -1)
        frame.Show(True)        
        
        return True

#-- Main Function
if __name__ == '__main__':
    app = MyApp(redirect=False)
    app.MainLoop()


 	  	 
