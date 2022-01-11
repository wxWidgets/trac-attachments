import sys
import os
import wx
import random
import math
import images

import wx.lib.mixins.listctrl as listmix

try:
    dirName = os.path.dirname(os.path.abspath(__file__))
except:
    dirName = os.path.dirname(os.path.abspath(sys.argv[0]))

sys.path.append(os.path.split(dirName)[0])

try:
    from agw import ultimatelistctrl as ULC
except ImportError: # if it's not there locally, try the wxPython lib.
    from wx.lib.agw import ultimatelistctrl as ULC


class TestUltimateListCtrl(ULC.UltimateListCtrl, listmix.ListCtrlAutoWidthMixin):
    
    def __init__(self, *args, **kwargs):
        
        ULC.UltimateListCtrl.__init__(self, *args, **kwargs)
        listmix.ListCtrlAutoWidthMixin.__init__(self)
        
        
class UltimateListCtrlPanel(wx.Panel):
    
    def __init__(self, parent, log):

        wx.Panel.__init__(self, parent, -1, style=wx.WANTS_CHARS)

        sizer = wx.BoxSizer(wx.VERTICAL)

        self.log = log        

        self.list = TestUltimateListCtrl(self, -1,
                                         style=wx.LC_REPORT
                                         | wx.BORDER_SUNKEN
                                         #| wx.BORDER_NONE
                                         #| wx.LC_SORT_ASCENDING
                                         #| wx.LC_NO_HEADER
                                         #| wx.LC_VRULES
                                         | ULC.ULC_NO_HEADER
                                         | wx.LC_HRULES,
                                         #| wx.LC_SINGLE_SEL
                                         extraStyle=ULC.ULC_HAS_VARIABLE_ROW_HEIGHT)
        
        sizer.Add(self.list, 1, wx.EXPAND)
       
        bmp = wx.EmptyBitmap(80,80)
        mdc = wx.MemoryDC()
        mdc.SelectObject(bmp)
        mdc.SetBackground(wx.Brush(wx.BLUE))
        mdc.Clear()
        self._bmp = bmp

        self.PopulateList()
        self.SetSizer(sizer)
        self.SetAutoLayout(True)


    def PopulateList(self):

        self.list.Freeze()

        self.list.InsertColumn(0,"")
       
        for i in xrange(15):
            panel = TestPanel(self.list, self._bmp, "Testing")
            index = self.list.InsertStringItem(sys.maxint,"")
            self.list.SetItemWindow(index,0,panel,expand=True)

        self.list.Thaw()
        self.list.Update()


#---------------------------------------------------------------------------

class TestPanel(wx.Panel):
    def __init__(self, parent, bmp, text):
        wx.Panel.__init__(self, parent, size=(200,100))

        self.bmp = wx.StaticBitmap(self, bitmap=bmp)
        self.label = wx.StaticText(self, label=text)
        
        self.layout()

    def layout(self):
        vsizer = wx.BoxSizer(wx.VERTICAL)
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.AddMany([((5, 5), 0), (self.bmp, 0, wx.ALIGN_CENTER_VERTICAL),
                       ((5, 5), 0), (self.label, 0, wx.ALIGN_CENTER_VERTICAL),
                       ((-1, 5), 1, wx.EXPAND)])
        vsizer.AddMany([((10, 10), 0), (sizer, 1, wx.EXPAND), ((10, 10), 0)])
        self.SetSizer(vsizer)
        

class TestFrame(wx.Frame):

    def __init__(self, parent, log):

        wx.Frame.__init__(self, parent, -1, "UltimateListCtrl in torrent style :-D", size=(800, 600))

        self.log = log
        # Create the CustomTreeCtrl, using a derived class defined below
        self.ulc = UltimateListCtrlPanel(self, self.log)
    
        self.SetIcon(images.Mondrian.GetIcon())
        self.CenterOnScreen()
        self.Show()
        
#---------------------------------------------------------------------------

if __name__ == '__main__':
    import sys
    app = wx.PySimpleApp()
    frame = TestFrame(None, sys.stdout)
    frame.Show(True)
    app.MainLoop()


