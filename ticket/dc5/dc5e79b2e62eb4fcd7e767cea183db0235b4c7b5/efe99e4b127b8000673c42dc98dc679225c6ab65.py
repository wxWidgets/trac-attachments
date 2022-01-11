#!/usr/bin/python

import wx

class GUI(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent)
        self.make_menu()
        self.make_toolbar()
        self.do_bindings()
        
        # comment out the bind to see how it causes my problem
        self.Bind(wx.EVT_MENU_OPEN, lambda x: x)
        self.SetExtraStyle(wx.WS_EX_PROCESS_UI_UPDATES)


    def make_menu(self):
        menu = wx.MenuBar()
        edit = wx.Menu()
        edit.Append(wx.ID_UNDO, "Undo")
        edit.Append(wx.ID_REDO, "Redo")
        menu.Append(edit, "Edit")
        self.SetMenuBar(menu)


    def make_toolbar(self):
        self.toolbar = self.CreateToolBar()

        ids = [wx.ID_UNDO, wx.ID_REDO]
        arts = [wx.ART_UNDO, wx.ART_REDO]

        for _id, art_id in zip(ids, arts):
            art = wx.ArtProvider.GetBitmap(art_id, wx.ART_TOOLBAR)
            self.toolbar.AddSimpleTool(_id, art)
        self.toolbar.Realize()


    def do_bindings(self):
        self.Bind(wx.EVT_UPDATE_UI, self.update_menus, id=wx.ID_UNDO)
        self.Bind(wx.EVT_UPDATE_UI, self.update_menus, id=wx.ID_REDO)


    def update_menus(self, event):
        event.Enable(False)

#------------------------------------------

app = wx.App()
frame = GUI(None)
frame.Show()
app.MainLoop()
