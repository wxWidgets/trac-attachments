#!/usr/bin/env python
# -*- coding: utf-8 -*- 
# SuperTofu
# Copyright (C) 2008  Ferraro Luciano (aka Lux) <luciano.ferraro@gmail.com>
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

__author__     = "Ferraro Luciano"
__url__        = ""
__version__    = "0.1"
__cvsversion__ = "$Revision: 1 $"
__date__       = "$Date: 2008/07/29 12:14:38 $"
__copyright__  = "Copyright (c) 2008 Luciano Ferraro"
__license__    = "GPL v3"

import sys
import os
import inspect
import string
import codecs
import zlib
import time
import __builtin__
try: import cStringIO as StringIO
except: import StringIO
try: import cPickle as pickle
except: import pickle
from ctypes import *

import wx
print wx.__version__
import wx.aui
from wx.lib.flashwin import *

_ = lambda x: x

class PRNT:
    streams = []
    head = ""
    debug = True
    def write (self, data, mode=-1):
        if mode == 1: self.head = data
        elif mode == 0: data = self.head+" "+data
        for stream in self.streams:
            stream(data+"\n")
        if self.debug: print data
Prnt = PRNT()
prnt = Prnt.write

if os.name == "nt":
    user32 = windll.user32
    def Click ():
        user32.mouse_event(0x00000002, 0, 0, 0 ,0)
        user32.mouse_event(0x00000004, 0, 0, 0 ,0)

def cdir (*args):
    filename = os.path.join(*args)
    prnt(filename,0)
    path = os.path.join(os.path.dirname(inspect.getfile(sys._getframe(1))), filename)
    return os.path.abspath(path)

class FlashInstance (FlashWindow):
    debug = False
    def __init__ (self, num, name):
        self.num = num
        row = int(num/3)
        
        self.panel = wx.Panel(gui)
        self.vbox = wx.BoxSizer(wx.VERTICAL)
        self.panel.SetSizer(self.vbox)
        self.bestsize = self.getoptsize()
        self.minsize = self.getminsize()
        
        paneinfo = wx.aui.AuiPaneInfo().Caption(name)\
        .MaximizeButton(True).CloseButton(True).MinimizeButton(True)\
        .BestSize(self.minsize).FloatingSize(self.minsize)\
        .PinButton(True).Row(row).MinSize(self.minsize).Name(name)
        if row == 2: paneinfo = paneinfo.Float()
        else: paneinfo = paneinfo.Top()
        gui.wm.AddPane(self.panel, paneinfo)
        
        FlashWindow.__init__(self, self.panel, style=wx.SUNKEN_BORDER)
    
    def getminsize (self):
        return int(self.bestsize[0]/2), int(self.bestsize[1]/2)
    def getoptsize (self):
        fs = map(lambda x:int(x)-150, gui.GetSize())
        size = 2048
        while (size>fs[0]) or (int(size*0.77)>fs[1]):
            size -= 15
        return (size, int(size*0.77))
    
    def close (self):
        self.Stop()
        time.sleep(.01)
        self.Close()
    
    def click (self, x,y):
        self.panel.SetFocus()
        self.panel.WarpPointer(x,y)
        Click()
        
    def load (self, swf):
        prnt("Loading swf: "+swf)
        self.swf = swf
        
        wx.BeginBusyCursor()
        self.LoadMovie(0, swf)
        wx.EndBusyCursor()
        self.panel.SetSize(self.minsize)
        
        self.vbox.Add(self, 1, wx.EXPAND)
        
        if self.debug:
            entry = wx.TextCtrl(self.panel)
            button = wx.Button(self.panel, label="Execute")
            button.Bind(wx.EVT_BUTTON, lambda x: evaluate(entry))
            hbox = wx.BoxSizer(wx.HORIZONTAL)
            hbox.Add(entry, 1, wx.EXPAND)
            hbox.Add(button, 0)
            self.vbox.Add(hbox, 1, wx.EXPAND)
        
        self.SetAutoLayout(True)
        paneinfo = gui.wm.GetPane(self.panel)
        gui.wm.Update()
        self.SetFocus()
        return paneinfo

def evaluate (entry):
    exec entry.GetValue() in globals()

class Frame (wx.Frame):
    def __init__ (self, gui, title):
        toolbar_items = [
            ["New","Create new Dofus instance", gui.on_new], 
            ["Edit", "Edit current Dofus instance", gui.on_edit], 
            #["Remove", "Remove current Dofus instance", gui.on_remove], 
            "<sep>",
            ["Login", "Login current Dofus instance", gui.on_login], 
            ["Login all", "Login all dofus instances", gui.on_login_all]]
        wx.Frame.__init__(self, None, -1, title, wx.DefaultPosition)
        self.Maximize()
        
        self.toolbar = self.CreateToolBar()
        prnt("Loading toolbar pixmaps ...",1)
        for item in toolbar_items:
            if item == "<sep>":
                self.toolbar.AddSeparator()
                continue
            id = wx.NewId()
            item.append(id)
            self.toolbar.AddSimpleTool(
                id, 
                wx.Image(cdir("pixmaps",item[0].lower()+".png"), wx.BITMAP_TYPE_PNG).ConvertToBitmap(),
                _(item[0]), _(item[1]))
            if item[2]: self.Bind(wx.EVT_TOOL, item[2], id=id)
        self.toolbar.SetToolBitmapSize((32,32))
        self.toolbar.Realize()
        
        self.wm = wx.aui.AuiManager(self) 
        self.wm.Bind(wx.aui.EVT_AUI_PANE_CLOSE, gui.on_pane_close)       
        
        self.Bind(wx.EVT_CLOSE, gui.on_close)
        
class GUI (wx.App):
    def OnInit (self):
        gui = Frame(self, "SuperTofu")
        __builtin__.gui = gui
        gui.Show(True)
        self.SetTopWindow(gui)
        return True
    
    def on_pane_close (self, event):
        del st.flash_instances[event.pane.name]
    def on_new (self, event):
        st.new()
    def on_edit (self, event):
        return
    def on_login (self, event):
        return
    def on_login_all (self, event):
        return
    def on_close (self, event):
        gui.wm.UnInit()
        gui.Destroy()
        st.quit()

class Core:
    def __init__ (self):
        self.gui = GUI(0, useBestVisual=True)
        self.gui.base = self
        self.flash_instances, self.panes_info = {}, []
    
    def new (self):
        name = "Dofus"+str(len(self.flash_instances)+1)
        instance = FlashInstance(len(self.flash_instances), name)
        self.flash_instances[name] = instance
        ppaths = ("C:\\Programmi\\Dofus\\", "D:\\Dofus\\",
                  "D:\\Programmi\\Dofus\\")
        dofus_path = filter(lambda x: os.path.isfile(x+"loader.swf"), ppaths)[0]
        self.panes_info.append(instance.load(dofus_path+"loader.swf"))
        return instance

    def quit (self):
        time.sleep(.1)
        sys.exit()
    def run (self):
        self.gui.MainLoop()

def main ():
    st = Core()
    return st

if __name__ == "__main__":
    st = main()
    st.run()
