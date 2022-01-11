
import wx
import wx.dataview as dv
import wx.lib.inspection
import wx.lib.mixins.inspection
import sys, os

# stuff for debugging
print "Python", sys.version
print "wx.version:", wx.version()
print "pid:", os.getpid()

assertMode = wx.PYAPP_ASSERT_DIALOG
##assertMode = wx.PYAPP_ASSERT_EXCEPTION

import random

testdata = {
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
20: ("Janet Jackson", "State Of The World", "Rock"),
21: ("Janet Jackson", "The Knowledge", "Rock"),
22: ("Spyro Gyra", "End of Romanticism", "Jazz"),
23: ("Spyro Gyra", "Heliopolis", "Jazz"),
24: ("Spyro Gyra", "Jubilee", "Jazz"),
25: ("Spyro Gyra", "Little Linda", "Jazz"),
26: ("Spyro Gyra", "Morning Dance", "Jazz"),
27: ("Spyro Gyra", "Song for Lorraine", "Jazz"),
28: ("Yes", "Owner Of A Lonely Heart", "Rock"),
29: ("Yes", "Rhythm Of Love", "Rock"),
30: ("Billy Joel", "Lullabye (Goodnight, My Angel)", "Rock"),
31: ("Billy Joel", "The River Of Dreams", "Rock"),
32: ("Billy Joel", "Two Thousand Years", "Rock"),
33: ("Janet Jackson", "Alright", "Rock"),
34: ("Janet Jackson", "Black Cat", "Rock"),
35: ("Janet Jackson", "Come Back To Me", "Rock"),
36: ("Janet Jackson", "Escapade", "Rock"),
37: ("Janet Jackson", "Love Will Never Do (Without You)", "Rock"),
38: ("Janet Jackson", "Miss You Much", "Rock"),
39: ("Janet Jackson", "Rhythm Nation", "Rock"),
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


#----------------------------------------------------------------------

def makeBlank(self):
    # Just a little helper function to make an empty image for our
    # model to use.
    empty = wx.EmptyBitmap(16, 16, 32)
    dc = wx.MemoryDC(empty)
    dc.SetBackground(wx.Brush((0, 0, 0, 0)))
    dc.Clear()
    del dc
    return empty


class RunDemoApp(wx.App, wx.lib.mixins.inspection.InspectionMixin):

    def OnInit(self):
        wx.Log.SetActiveTarget(wx.LogStderr())

        self.SetAssertMode(assertMode)
        self.InitInspection()  # for the InspectionMixin base class

        frame = wx.Frame(None, -1, "Dataview DND Test", pos=(50, 50), size=(200, 100),
                        style=wx.DEFAULT_FRAME_STYLE, name="run a sample")
        frame.CreateStatusBar()

        menuBar = wx.MenuBar()
        menu = wx.Menu()
        item = menu.Append(-1, "&Widget Inspector\tF6", "Show the wxPython Widget Inspection Tool")
        self.Bind(wx.EVT_MENU, self.OnWidgetInspector, item)
        item = menu.Append(wx.ID_EXIT, "E&xit\tCtrl-Q", "Exit demo")
        self.Bind(wx.EVT_MENU, self.OnExitApp, item)
        menuBar.Append(menu, "&File")
       
        frame.SetMenuBar(menuBar)
        frame.Show(True)
        frame.Bind(wx.EVT_CLOSE, self.OnCloseFrame)

        win = runTest(frame, frame)

        # a window will be returned if the demo does not create
        # its own top-level window
        if win:
            # so set the frame to a good size for showing stuff
            frame.SetSize((640, 480))
            win.SetFocus()
            self.window = win
            frect = frame.GetRect()

        else:
            # It was probably a dialog or something that is already
            # gone, so we're done.
            frame.Destroy()
            return True

        self.SetTopWindow(frame)
        self.frame = frame
        #wx.Log_SetActiveTarget(wx.LogStderr())
        #wx.Log_SetTraceMask(wx.TraceMessages)
                    
        return True


    def OnExitApp(self, evt):
        self.frame.Close(True)


    def OnCloseFrame(self, evt):
        if hasattr(self, "window") and hasattr(self.window, "ShutdownDemo"):
            self.window.ShutdownDemo()
        evt.Skip()

    def OnWidgetInspector(self, evt):
        wx.lib.inspection.InspectionTool().Show()


class Song(object):
    def __init__(self, id, artist, title, genre):
        self.id = id
        self.artist = artist
        self.title = title
        self.genre = genre
        self.like = False
        # get a random date value
        d = random.choice(range(27)) + 1
        m = random.choice(range(12))
        y = random.choice(range(1980, 2005))
        self.date = wx.DateTimeFromDMY(d, m, y)
        
    def __repr__(self):
        return 'Song: %s-%s' % (self.artist, self.title)
    

class Genre(object):
    def __init__(self, name):
        self.name = name
        self.songs = []
        
    def __repr__(self):
        return 'Genre: ' + self.name

#----------------------------------------------------------------------

# This model provides these data columns:
#
#     0. Genre :  string
#     1. Artist:  string
#     2. Title:   string
#     3. id:      integer
#     4. Aquired: date
#     5. Liked:   bool
#

class MyTreeListModel(dv.PyDataViewModel):
    def __init__(self, data):
        dv.PyDataViewModel.__init__(self)
        self.data = data
       
        self.objmapper.UseWeakRefs(True)
                
    # Report how many columns this model provides data for.
    def GetColumnCount(self):
        return 6

    # Map the data column numbers to the data type
    def GetColumnType(self, col):
        mapper = { 0 : 'string',
                   1 : 'string',
                   2 : 'string',
                   3.: 'string',
                   4 : 'datatime',
                   5 : 'bool',
                   }
        return mapper[col]
        
    
    def GetChildren(self, parent, children):  
        if not parent:
            for genre in self.data:
                children.append(self.ObjectToItem(genre))
            return len(self.data)
        
        node = self.ItemToObject(parent)
        if isinstance(node, Genre):
            for song in node.songs:
                children.append(self.ObjectToItem(song))
            return len(node.songs)
        return 0
    

    def IsContainer(self, item):
      
        if not item:
            return True
        node = self.ItemToObject(item)
        if isinstance(node, Genre):
            return True
        return False    
    
    def GetParent(self, item): 
        if not item:
            return dv.NullDataViewItem

        node = self.ItemToObject(item)        
        if isinstance(node, Genre):
            return dv.NullDataViewItem
        elif isinstance(node, Song):
            for g in self.data:
                if g.name == node.genre:
                    return self.ObjectToItem(g)
            
        
    def GetValue(self, item, col):
        node = self.ItemToObject(item)
        
        if isinstance(node, Genre):
            mapper = { 0 : node.name,
                       1 : "",
                       2 : "",
                       3 : "",
                       4 : wx.DateTimeFromTimeT(0),
                       5 : False,
                       }
            return mapper[col]
            
        
        elif isinstance(node, Song):
            mapper = { 0 : node.genre,
                       1 : node.artist,
                       2 : node.title,
                       3 : node.id,
                       4 : node.date,
                       5 : node.like,
                       }
            return mapper[col]
        
        else:
            raise RuntimeError("unknown node type")
        


    def GetAttr(self, item, col, attr):
        node = self.ItemToObject(item)
        if isinstance(node, Genre):
            attr.SetColour('blue')
            attr.SetBold(True)
            return True
        return False
    
    
    def SetValue(self, value, item, col):       
        node = self.ItemToObject(item)
        if isinstance(node, Song):
            if col == 1:
                node.artist = value
            elif col == 2:
                node.title = value
            elif col == 3:
                node.id = value
            elif col == 4:
                node.date = value
            elif col == 5:
                node.like = value
    
#----------------------------------------------------------------------

class TestPanel(wx.Panel):
    def __init__(self, parent, data=None, model=None):
        wx.Panel.__init__(self, parent, -1)

        # Create a dataview control
        self.dvc = dv.DataViewCtrl(self,
                                   style=wx.BORDER_THEME
                                   | dv.DV_ROW_LINES 
                                   | dv.DV_VERT_RULES
                                   | dv.DV_MULTIPLE
                                   )
        
        # Create an instance of our model...
        if model is None:
            self.model = MyTreeListModel(data)
        else:
            self.model = model            

        # Tel the DVC to use the model
        self.dvc.AssociateModel(self.model)

        # Define the columns that we want in the view.  Notice the 
        # parameter which tells the view which col in the data model to pull
        # values from for each view column.
        if 1:
            self.tr = tr = dv.DataViewTextRenderer()
            c0 = dv.DataViewColumn("Genre", # title
                                   tr, # renderer
                                   0, # data model column
                                   width=80)
            self.dvc.AppendColumn(c0)
        else:
            self.dvc.AppendTextColumn("Genre", 0, width=80)
            
        c1 = self.dvc.AppendTextColumn("Artist", 1, width=170)
        c2 = self.dvc.AppendTextColumn("Title", 2, width=260)
        c3 = self.dvc.AppendDateColumn('Acquired', 4, width=100, mode=dv.DATAVIEW_CELL_ACTIVATABLE)
        c4 = self.dvc.AppendToggleColumn('Like', 5, width=40, mode=dv.DATAVIEW_CELL_ACTIVATABLE)
        
        c5 = self.dvc.AppendTextColumn("id", 3, width=40)
        c5.Alignment = wx.ALIGN_RIGHT
        
        # Set some additional attributes for all the columns
        for c in self.dvc.Columns:
            c.Sortable = True
            c.Reorderable = True

        # Enable drag and drop
        self.dvc.EnableDragSource(wx.DataFormat(wx.DF_TEXT))
        self.dvc.EnableDropTarget(wx.DataFormat(wx.DF_TEXT))
            
        self.Sizer = wx.BoxSizer(wx.VERTICAL)
        self.Sizer.Add(self.dvc, 1, wx.EXPAND)
        
        self.Bind(dv.EVT_DATAVIEW_ITEM_BEGIN_DRAG, self.OnBeginDrag)
        #self.Bind(dv.EVT_DATAVIEW_ITEM_DROP, self.OnDrop)
        
        
    def OnBeginDrag(self, event):
        print "On Begin Drag"
        self.dragDataObject = wx.TextDataObject("TestDragText")
        event.SetDataObject(self.dragDataObject)
        
    def OnDrop(self, event):
        print "On Drop"
        buffer = event.GetDataBuffer()
                    
#----------------------------------------------------------------------

def runTest(frame, nb):

    musicdata = testdata.items()
    musicdata.sort()

    data = dict()
    for key, val in musicdata:
        song = Song(str(key), val[0], val[1], val[2])
        genre = data.get(song.genre)
        if genre is None:
            genre = Genre(song.genre)
            data[song.genre] = genre
        genre.songs.append(song)
    data = data.values()

    win = TestPanel(nb, data=data)
    return win

#----------------------------------------------------------------------


if __name__ == '__main__':
    import sys, os
    app = RunDemoApp(False)
    app.MainLoop()
