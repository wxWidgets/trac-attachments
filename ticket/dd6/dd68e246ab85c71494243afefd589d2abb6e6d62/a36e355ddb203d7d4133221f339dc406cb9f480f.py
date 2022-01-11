
from wxPython.wx import *
from wxPython.lib.mixins.listctrl import wxColumnSorterMixin, wxListCtrlAutoWidthMixin

musicdata = {
1 : ("Bad English", "The Price Of Love", "Rock"),
2 : ("DNA featuring Suzanne Vega", "Tom's Diner", "Rock"),
3 : ("George Michael", "Praying For Time", "Rock"),
4 : ("Gloria Estefan", "Here We Are", "Rock"),
5 : ("Linda Ronstadt", "Don't Know Much", "Rock"),
6 : ("Michael Bolton", "How Am I Supposed To Live Without You", "Blues"),
7 : ("Paul Young", "Oh Girl", "Rock"),
8 : ("Paula Abdul", "Opposites Attract", "Rock"),
9 : ("Richard Marx", "Should've Known Better", "Rock"),
10: ("Rod Stewart", "Forever Young", "Rock"),
11: ("Roxette", "Dangerous", "Rock"),
12: ("Sheena Easton", "The Lover In Me", "Rock"),
13: ("Sinead O'Connor", "Nothing Compares 2 U", "Rock"),
14: ("Stevie B.", "Because I Love You", "Rock"),
15: ("Taylor Dayne", "Love Will Lead You Back", "Rock"),
16: ("The Bangles", "Eternal Flame", "Rock"),
17: ("Wilson Phillips", "Release Me", "Rock"),
18: ("Billy Joel", "Blonde Over Blue", "Rock"),
19: ("Billy Joel", "Famous Last Words", "Rock"),
20: ("Billy Joel", "Lullabye (Goodnight, My Angel)", "Rock"),
21: ("Billy Joel", "The River Of Dreams", "Rock"),
22: ("Billy Joel", "Two Thousand Years", "Rock"),
23: ("Janet Jackson", "Alright", "Rock"),
24: ("Janet Jackson", "Black Cat", "Rock"),
25: ("Janet Jackson", "Come Back To Me", "Rock"),
26: ("Janet Jackson", "Escapade", "Rock"),
27: ("Janet Jackson", "Love Will Never Do (Without You)", "Rock"),
28: ("Janet Jackson", "Miss You Much", "Rock"),
29: ("Janet Jackson", "Rhythm Nation", "Rock"),
30: ("Janet Jackson", "State Of The World", "Rock"),
31: ("Janet Jackson", "The Knowledge", "Rock"),
32: ("Spyro Gyra", "End of Romanticism", "Jazz"),
33: ("Spyro Gyra", "Heliopolis", "Jazz"),
34: ("Spyro Gyra", "Jubilee", "Jazz"),
35: ("Spyro Gyra", "Little Linda", "Jazz"),
36: ("Spyro Gyra", "Morning Dance", "Jazz"),
37: ("Spyro Gyra", "Song for Lorraine", "Jazz"),
38: ("Yes", "Owner Of A Lonely Heart", "Rock"),
39: ("Yes", "Rhythm Of Love", "Rock"),
40: ("Cusco", "Dream Catcher", "New Age"),
41: ("Cusco", "Geronimos Laughter", "New Age"),
42: ("Cusco", "Ghost Dance", "New Age"),
43: ("Blue Man Group", "Drumbone", "New Age"),
44: ("Blue Man Group", "Endless Column", "New Age"),
45: ("Blue Man Group", "Klein Mandelbrot", "New Age"),
46: ("Kenny G", "Silhouette", "Jazz"),
47: ("Sade", "Smooth Operator", "Jazz"),
48: ("David Arkenstone", "Papillon (On The Wings Of The Butterfly)", "New Age"),
49: ("David Arkenstone", "Stepping Stars", "New Age"),
50: ("David Arkenstone", "Carnation Lily Lily Rose", "New Age"),
51: ("David Lanz", "Behind The Waterfall", "New Age"),
52: ("David Lanz", "Cristofori's Dream", "New Age"),
53: ("David Lanz", "Heartsounds", "New Age"),
54: ("David Lanz", "Leaves on the Seine", "New Age"),
}



class cvs(wxApp):

    def OnInit(self):
        c = HoofdframeCVS()
        return True

class HoofdframeCVS(wxFrame):

    def __init__(self):
        wxFrame.__init__(self, id = -1, name = 'HoofdframeCVS', parent = NULL, 
                            pos = wxPoint(24, 161), size = wxSize(1106, 722), style = wxDEFAULT_FRAME_STYLE,
                             title = 'Client Volgsysteem')
        self.SetToolTipString('Client Volgsysteem')
        self.SetClientSize(wxSize(1106, 698))

        self.CVSHoofdschermNoteBook = wxNotebook(id = -1, name = 'CVSHoofdschermNoteBook', parent = self, pos = wxPoint(0, 0), style = 0)
#        def OnCVSframeSize(evt):
#            self.CVSHoofdschermNoteBook.SetSize(evt.GetSize())

#        EVT_SIZE(self.CVSHoofdschermNoteBook, OnCVSframeSize)

        pnl1 = ClientenScrn(self)
        self.CVSHoofdschermNoteBook.AddPage(pnl1, 'Test1', True, imageId = -1)          

        pnl2 = wxPanel(self.CVSHoofdschermNoteBook, -1, style=wxCLIP_CHILDREN)
        p = wxStaticText(pnl2, -1,"zomaar tekst")
        self.CVSHoofdschermNoteBook.AddPage(pnl2, 'hp2', False, imageId = -1)          

        pnl3 = ClientenScrn(self)
        self.CVSHoofdschermNoteBook.AddPage(pnl3, 'Test2', True, imageId = -1)          

        pnl4 = ClientenScrn(self)
        self.CVSHoofdschermNoteBook.AddPage(pnl4, 'Test3', True, imageId = -1)          

        self.Show(True)

class ClientenScrn(wxPanel):
 
    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wxID_CLIENTENSCRN = wxNewId()
        wxPanel.__init__(self, id = wxID_CLIENTENSCRN, name = 'ClientenScrn', 
                        parent = prnt, size = prnt.GetClientSize(),
                        style = wxCLIP_CHILDREN | wxDEFAULT_FRAME_STYLE)
        self.SetAutoLayout(True)

    def __init__(self, parentscrn):
        
        self._init_ctrls(parentscrn.CVSHoofdschermNoteBook)
        self.CLIENTENSPLITTER = wxNewId()
        self.CLIENTENDETAILS_SCRN_ID = wxNewId()
        self.CLIENTLIST_ID = wxNewId()
        
        self.parent = parentscrn
        self.splitter = wxSplitterWindow(self, self.CLIENTENSPLITTER, 
                    size = parentscrn.CVSHoofdschermNoteBook.GetClientSize(), style=wxNO_3D)

        self.nb = wxNotebook(self.splitter, self.CLIENTENDETAILS_SCRN_ID, style=wxCLIP_CHILDREN|wxNB_BOTTOM)
        self.clientlist = TestListCtrlPanel(self.splitter)
        self.splitter.SetMinimumPaneSize(20)
        self.splitter.SplitHorizontally(self.clientlist,self.nb,0)

        pnl1 = wxPanel(self.nb, -1, style=wxCLIP_CHILDREN)
        p = wxStaticText(pnl1, -1,"zomaar tekst")
        self.nb.AddPage(pnl1, 'hlptekst', False, imageId = -1)          

        pnl2 = wxPanel(self.nb, -1, style=wxCLIP_CHILDREN)
        p = wxStaticText(pnl2, -1,"zomaar tekst 2****************")
        self.nb.AddPage(pnl2, '2E PANEL', False, imageId = -1)          

        def OnReSize(evt):
            self.splitter.SetSize(evt.GetSize())
        EVT_SIZE(self, OnReSize)

        def EmptyHandler(evt): pass
        EVT_ERASE_BACKGROUND(self, EmptyHandler)

        self.nb.Layout()
        return


#----------------------------------------------------------------------------
# Name:         ListCtrl.py
# Purpose:      Testing lots of stuff, controls, window types, etc.
#
# Author:       Robin Dunn & Gary Dumer
#
# Created:
# RCS-ID:       $Id: wxListCtrl.py,v 1.26.2.12 2003/07/31 17:12:36 RD Exp $
# Copyright:    (c) 1998 by Total Control Software
# Licence:      wxWindows license
#----------------------------------------------------------------------------

#---------------------------------------------------------------------------


class TestListCtrl(wxListCtrl, wxListCtrlAutoWidthMixin):
    def __init__(self, parent, ID, pos=wxDefaultPosition,
                 size=wxDefaultSize, style=0):
        wxListCtrl.__init__(self, parent, ID, pos, size, style)
        wxListCtrlAutoWidthMixin.__init__(self)



class TestListCtrlPanel(wxPanel, wxColumnSorterMixin):
    def __init__(self, parent):
        wxPanel.__init__(self, parent, -1, style=wxWANTS_CHARS)

        tID = wxNewId()


        self.list = TestListCtrl(self, tID,
                                 style=wxLC_REPORT | wxSUNKEN_BORDER
                                 | wxLC_EDIT_LABELS
                                 #| wxLC_NO_HEADER
                                 #| wxLC_VRULES | wxLC_HRULES
                                 )
        self.PopulateList()

        # Now that the list exists we can init the other base class,
        # see wxPython/lib/mixins/listctrl.py
        self.itemDataMap = musicdata
        wxColumnSorterMixin.__init__(self, 3)
        #self.SortListItems(0, True)

        EVT_SIZE(self, self.OnSize)
        # for wxGTK


    def PopulateList(self):
        self.list.InsertColumn(0, "Artist")
        self.list.InsertColumn(1, "Title", wxLIST_FORMAT_RIGHT)
        self.list.InsertColumn(2, "Genre")
        items = musicdata.items()
        for x in range(len(items)):
            key, data = items[x]
            self.list.InsertStringItem(x, data[0])
            self.list.SetStringItem(x, 1, data[1])
            self.list.SetStringItem(x, 2, data[2])
            self.list.SetItemData(x, key)

        self.list.SetColumnWidth(0, wxLIST_AUTOSIZE)
        self.list.SetColumnWidth(1, wxLIST_AUTOSIZE)
        self.list.SetColumnWidth(2, 100)

        # show how to select an item
        self.list.SetItemState(5, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED)

        # show how to change the colour of a couple items
        item = self.list.GetItem(1)
        item.SetTextColour(wxBLUE)
        self.list.SetItem(item)
        item = self.list.GetItem(4)
        item.SetTextColour(wxRED)
        self.list.SetItem(item)

        self.currentItem = 0


    # Used by the wxColumnSorterMixin, see wxPython/lib/mixins/listctrl.py
    def GetListCtrl(self):
        return self.list

    def OnSize(self, event):
        w,h = self.GetClientSizeTuple()
        self.list.SetDimensions(0, 0, w, h)


if __name__ == '__main__':
    k=cvs()
    k.MainLoop()

    
 	  	 
