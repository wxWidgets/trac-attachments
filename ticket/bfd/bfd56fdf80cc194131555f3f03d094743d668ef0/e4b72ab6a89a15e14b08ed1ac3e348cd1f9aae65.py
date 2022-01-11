# -*- coding:utf-8 -*-
import os
import wx
from wx.lib.agw import aui

from win32api import GetCurrentProcess 
from win32con import GR_GDIOBJECTS 
from win32process import GetGuiResources

def GDIReport():
    """ Report the number of GDI Resources in use by Transana """ 
    # Get the number of GDI Resources in use from the Operating System 
    numGDI = GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS) 
    # Return the number of GDI Resources in use 
    return numGDI 

N_PAGES = 50
OPEN_ONLY = False
AUTO_MODE = True
RELOAD_PERSPECTIVE = True

default_layout = """
layout2|
name=Panel 1;caption=Panel 1;state=201590780;dir=6;layer=0;row=0;pos=0;prop=100000;bestw=400;besth=419;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=769;floaty=798;floatw=400;floath=419;notebookid=0;transparent=255|
name=Panel 2;caption=Panel 2;state=201590780;dir=6;layer=0;row=0;pos=2;prop=100000;bestw=400;besth=419;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=994;floaty=815;floatw=400;floath=419;notebookid=0;transparent=255|
name=Panel 3;caption=Panel 3;state=201590780;dir=6;layer=0;row=0;pos=1;prop=100000;bestw=400;besth=400;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1;notebookid=0;transparent=255|
name=Panel 4;caption=Panel 4;state=201590780;dir=3;layer=0;row=0;pos=1;prop=100000;bestw=400;besth=419;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=400;floath=419;notebookid=-1;transparent=255|
name=Panel 5;caption=Panel 5;state=201590780;dir=5;layer=0;row=0;pos=0;prop=100000;bestw=400;besth=400;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1;notebookid=-1;transparent=255|
name=__notebook_0;caption=List;state=201345020;dir=3;layer=0;row=0;pos=0;prop=100000;bestw=400;besth=400;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1;notebookid=0;transparent=255|
dock_size(3,0,0)=421|dock_size(5,0,0)=402|dock_size(6,0,0)=402|
"""

class MyManager(aui.AuiManager):
    pass
        
class MyView(wx.Panel):
    
    def __init__(self, *args, **kwargs):
        super(MyView, self).__init__(*args, **kwargs)
        
        # create the layout
        self.manager = MyManager(self, agwFlags=aui.AUI_MGR_DEFAULT)
        
        nbStyle = (
            aui.AUI_NB_TOP | 
            aui.AUI_NB_TAB_MOVE | 
            aui.AUI_NB_SCROLL_BUTTONS | 
            aui.AUI_NB_NO_TAB_FOCUS 
        )
        self.manager.SetAutoNotebookStyle(nbStyle)
        
        # creating 5 empty panels
        for i in range(0, 5) :
            panel = wx.Panel(self)
            info = aui.AuiPaneInfo().Center().Name("Panel %s" % (i + 1)).Caption("Panel %s" % (i + 1)).MaximizeButton(True).MinimizeButton(True).PinButton(True)
            info.DestroyOnClose(True)
            self.manager.AddPane(panel, info)
            self.manager.Update()
        
        if RELOAD_PERSPECTIVE :
            layout_path = "./layout.txt"
            if os.path.exists(layout_path) :
                _file = open(layout_path, "r")
                layout = _file.read()
                _file.close() 
            else :
                layout = default_layout
            self.manager.LoadPerspective(layout, True)
    
    def Destroy(self):
        # release resources occupied by AuiManager
        # objects relative to each AuiNotebook
        for nb in self.manager.GetNotebooks() :
            nb._mgr.UnInit()
            nb._mgr.Destroy()
            nb.Destroy()
        
        # release resources occupied by the AuiManager
        # relative to the notebook itself
        self.manager.UnInit()
        self.manager.Destroy()
        
        super(MyView, self).Destroy()
           
class MyNotebook(aui.AuiNotebook):
    n_pages = 0
    
    def __init__(self, parent):
        default = (
            aui.AUI_NB_TOP | 
            aui.AUI_NB_TAB_MOVE | 
            aui.AUI_NB_SCROLL_BUTTONS | 
            aui.AUI_NB_CLOSE_ON_ACTIVE_TAB | 
            aui.AUI_NB_MIDDLE_CLICK_CLOSE | 
            aui.AUI_NB_CLOSE_ON_ALL_TABS
        )
        style = (
            default | 
            aui.AUI_NB_WINDOWLIST_BUTTON | 
            aui.AUI_NB_NO_TAB_FOCUS | 
            aui.AUI_NB_SMART_TABS | 
            aui.AUI_NB_USE_IMAGES_DROPDOWN | 
            aui.AUI_NB_ORDER_BY_ACCESS  
        )
        
        super(MyNotebook, self).__init__(parent, agwStyle=style)
        self.Bind(aui.EVT_AUINOTEBOOK_PAGE_CLOSE, self.OnPageClosing)
        self.Bind(aui.EVT_AUINOTEBOOK_PAGE_CLOSED, self.OnPageClosed)
        
        # create the timer used to
        # open / close the current page
        self._counter = 0
        self._timer = wx.Timer(self)
        if AUTO_MODE :
            self._timer.Start()
        self.Bind(wx.EVT_TIMER, self.OnTimer)
    
    def OnTimer(self, evt):
        """
        Delete the current page and add a new one to effectively show the memory leak.
        """
        if (self.GetPageCount() >= N_PAGES) and not OPEN_ONLY :
            while self.GetPageCount() :
                self.DeletePage(self.GetSelection())
        else :
            self.AddNewPage()
        if self._counter > 1000 :
            self._timer.Stop()
        self._counter += 1
    
    def AddNewPage(self):
        """
        Add a new page inside the notebook.
        """
        MyNotebook.n_pages += 1
        page = MyView(self)
        caption = "Page %s" % MyNotebook.n_pages 
        self.AddPage(page, caption, True)
    
    def OnPageClosing(self, evt):
        """
        Save the layout before closing a tab.
        """
        i_page = evt.GetSelection()
        page = self.GetPage(i_page)
        layout = open("./layout.txt", "w")
        layout.write(page.manager.SavePerspective())
        layout.close()
        evt.Skip()
    
    def OnPageClosed(self, evt):
        """
        Add a new page when the current one is closed.
        """
        self.AddNewPage()
        evt.Skip()

class MyFrame(wx.Frame) :
    
    def __init__(self, *args, **kwargs):
        super(MyFrame, self).__init__(*args, **kwargs)
        self.notebook = MyNotebook(self)

class MyApp(wx.App):
    
    def OnInit(self) :
        frame = MyFrame(None, size=(1024, 768))
        frame.CenterOnScreen()
        frame.Show(True)
        if not AUTO_MODE :
            frame.notebook.AddNewPage()
        return True
        
if __name__ == "__main__" :
    app = MyApp(False)
    app.MainLoop()
    print "finished"
