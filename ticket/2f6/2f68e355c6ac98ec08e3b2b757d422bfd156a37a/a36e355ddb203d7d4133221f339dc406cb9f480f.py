# -*- coding: iso-8859-1 -*-

import wx

class MenuBar1(wx.MenuBar):
    def __init__(self):
        wx.MenuBar.__init__(self)
        menu = wx.Menu()
        menu.Append(wx.ID_EXIT, "Exit 1", "Quit the program 1")
        self.Append(menu, "File 1") 

class MenuBar2(wx.MenuBar):
    def __init__(self):
        wx.MenuBar.__init__(self)
        menu = wx.Menu()
        menu.Append(wx.ID_EXIT, "Exit 2", "Quit the program 2")
        self.Append(menu, "File 2")


class MyNotebook(wx.Notebook):
    def __init__(self, parent):
        self.parent = parent
        wx.Notebook.__init__(self, parent)
        self.AddPage(wx.Panel(self), 'first page')
        self.AddPage(wx.Panel(self), 'seconde one')
        self.Bind(wx.EVT_NOTEBOOK_PAGE_CHANGED, self.change)
        self.menubars = [MenuBar1(), MenuBar2()]

    def change(self, event):
        event.Skip()
        self.parent.SetMenuBar(self.menubars[event.GetSelection()])

class MyFrame(wx.Frame):
    def __init__(self, app):
        wx.Frame.__init__(self, parent = None)
        self.nbook = MyNotebook(self)
        self.SetMenuBar(self.nbook.menubars[0])
        self.Bind(wx.EVT_MENU, self.menuExit, id = wx.ID_EXIT)
        
    def menuExit(self, event):
        wx.MessageBox('Not implemented.', 'Quit ?')
        

app = wx.PySimpleApp()
frame = MyFrame(app)
frame.Show(True)
app.MainLoop()

