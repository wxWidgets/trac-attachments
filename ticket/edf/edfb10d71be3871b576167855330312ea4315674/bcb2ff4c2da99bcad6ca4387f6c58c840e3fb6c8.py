#!/usr/bin/env python

import wx

class TestListBox(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1)

        # listbox items; it is essential that these are not sorted
        sampleList = [('item 1', 'data 1'),
                        ('item 4', 'data 4'),
                        ('item 3', 'data 3'),
                        ('item 5', 'data 5'),
                        ('item 2', 'data 2')]

        wx.StaticText(self, -1, "This example uses the wx.ListBox control.", (45, 10))
        wx.StaticText(self, -1, "Select one:", (15, 50))
        
        # listbox with LB_SORT style (otherwise everything works OK)
        self.lb1 = wx.ListBox(self, 60, (100, 50), (90, 120), style=wx.LB_SORT)
        #self.lb1 = wx.ListBox(self, 60, (100, 50), (90, 120))


        # none of these 2 methods work properly
        #method 1
        for item in sampleList:
            self.lb1.Append(item[0], item[1]);
        #method 2
        #for item in sampleList:
        #    pos = self.lb1.Append(item[0])
        #    self.lb1.SetClientData(pos, item[1])
        
        #print item's Client Data on click
        self.Bind(wx.EVT_LISTBOX, self.EvtListBox, self.lb1)
        

    def EvtListBox(self, event):
        print 'EvtListBox: %s, %s, %s, %s' % (event.GetString(),
                            event.IsSelection(),
                            event.GetSelection(),
                            event.GetClientData())

                
if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = TestListBox()
    frame.Show()
    app.MainLoop()
 	  	 
