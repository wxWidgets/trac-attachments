#----------------------------------------------------------------------------
# Based on wxPython's Demo ListCtrl.py
#----------------------------------------------------------------------------

import sys

import wxversion
wxversion.select('2.8.1.1')

import  wx
import  wx.lib.mixins.listctrl  as  listmix

#---------------------------------------------------------------------------

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

#---------------------------------------------------------------------------

class TestListCtrl(wx.ListCtrl, listmix.ListCtrlAutoWidthMixin):
    def __init__(self, parent, ID, pos=wx.DefaultPosition,
                 size=wx.DefaultSize, style=0):
        wx.ListCtrl.__init__(self, parent, ID, pos, size, style)
        listmix.ListCtrlAutoWidthMixin.__init__(self)


class TestListCtrlPanel(wx.Panel, listmix.ColumnSorterMixin):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1, style=wx.WANTS_CHARS)

        tID = wx.NewId()

        #sizer = wx.BoxSizer(wx.VERTICAL)
        sizer = wx.GridBagSizer()

        self.list = TestListCtrl(self, tID,
                                 style=wx.LC_REPORT
                                 | wx.BORDER_NONE
                                 | wx.LC_EDIT_LABELS
                                 | wx.LC_SORT_ASCENDING
                                 )

        #sizer.Add(self.list, 1, wx.EXPAND)
        sizer.Add(self.list, (0, 0), flag=wx.EXPAND)
        sizer.AddGrowableCol(0)
        sizer.AddGrowableRow(0)

        self.PopulateList()

        self.itemDataMap = musicdata


        self.SetSizer(sizer)
        self.SetAutoLayout(True)

        # On Size Event
        self.list.Bind(wx.EVT_SIZE, self.OnSize)

    def OnSize(self, event):
        print "Resizing event received on: ", event.GetEventObject()
        event.Skip()

    def PopulateList(self):
        if 1:
            # for normal, simple columns, you can add them like this:
            self.list.InsertColumn(0, "Artist")
            self.list.InsertColumn(1, "Title", wx.LIST_FORMAT_RIGHT)
            self.list.InsertColumn(2, "Genre")

        items = musicdata.items()
        for key, data in items:
            index = self.list.InsertStringItem(sys.maxint, data[0])
            self.list.SetStringItem(index, 1, data[1])
            self.list.SetStringItem(index, 2, data[2])
            self.list.SetItemData(index, key)

        self.list.SetColumnWidth(0, wx.LIST_AUTOSIZE)
        self.list.SetColumnWidth(1, wx.LIST_AUTOSIZE)
        self.list.SetColumnWidth(2, 100)

        # show how to select an item
        self.list.SetItemState(5, wx.LIST_STATE_SELECTED, wx.LIST_STATE_SELECTED)

        # show how to change the colour of a couple items
        item = self.list.GetItem(1)
        item.SetTextColour(wx.BLUE)
        self.list.SetItem(item)
        item = self.list.GetItem(4)
        item.SetTextColour(wx.RED)
        self.list.SetItem(item)

        self.currentItem = 0


class MyApp(wx.App):
    def OnInit(self):
        frame = wx.Frame(None, -1, "Testing wx.GridBagSizer and wx.ListCtrl",
                         size=(640, 480))
        self.SetTopWindow(frame)
        panel = TestListCtrlPanel(frame)
        frame.Show(True)
        return True

app = MyApp(redirect=False)
app.MainLoop()



 	  	 
