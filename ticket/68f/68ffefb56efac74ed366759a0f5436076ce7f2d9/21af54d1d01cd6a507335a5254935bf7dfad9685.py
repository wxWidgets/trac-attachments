#import wxversion
#wxversion.select("2.6-msw-ansi")
import wx

#not working on:
#wxPython 2.6.2.1 and wxPython 2.6.0
#on Windows XP
#After pressing AppendMenu, two(!) radio items are checked
class MyFrame(wx.Frame):

    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, title=title)

        self.menuBar = wx.MenuBar()
        self.menu = wx.Menu()
        self.menu.Append(2000,"Radio1",'',wx.ITEM_RADIO) 
        self.menu.Append(2001,"Radio2",'',wx.ITEM_RADIO) 
        self.menuBar.Append (self.menu, "Menu")
        self.SetMenuBar(self.menuBar)
        button = wx.Button(self, label = "Append Menu")
        button.Bind(wx.EVT_BUTTON, self.AppendMenuDynamic)

    def AppendMenuDynamic(self, evt):
        self.menu.Append(2002,"Radio3",'',wx.ITEM_RADIO) 
        self.menu.Append(2003,"Radio4",'',wx.ITEM_RADIO) 

        #doesn't work either
        #self.DoMenuUpdates()
        #self.menu.Check(2002, False)
        #self.menu.AppendRadioItem (2003,"Radio4")

app = wx.App(0)
win = MyFrame(None, title="Radio Menus, wxPy: " + wx.VERSION_STRING)
win.Show()
app.MainLoop()
 	  	 
