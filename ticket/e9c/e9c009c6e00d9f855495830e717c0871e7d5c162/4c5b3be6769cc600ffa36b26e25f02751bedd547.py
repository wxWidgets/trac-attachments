import os, sys 
import wx 

import wx.lib.agw.aui as aui 

class MyFrame(wx.Frame): 
    def __init__(self, parent, title): 
        wx.Frame.__init__(self, parent, -1, title, pos=(150, 150), size=(640, 480)) 


        self.CreateStatusBar() 


        self._auiMgr = aui.AuiManager(self) 


        client_size = self.GetClientSize() 
        self._noteBook = aui.AuiNotebook(self, -1) 
        self._panelA = wx.Panel(self._noteBook, -1) 
        self._panelB = wx.Panel(self._noteBook, -1) 
        self._panelC = wx.Panel(self._noteBook, -1) 
        self._panelD = wx.Panel(self._noteBook, -1) 
        self._noteBook.AddPage(self._panelA, u"PanelA", False) 
        self._noteBook.AddPage(self._panelB, u"PanelB", False) 
        self._noteBook.AddPage(self._panelC, u"PanelC", False) 
        self._noteBook.AddPage(self._panelD, u"PanelD", False) 
        self._auiMgr.AddPane(self._noteBook, aui.AuiPaneInfo().CenterPane().PaneBorder(False)) 


        try: 
            self._noteBook.LoadPerspective(open(u'perspective.txt').read()) 
        except: 
            pass 


        self._auiMgr.Update() 


        self.Bind(wx.EVT_CLOSE, self.__OnClose) 


        self._noteBook.Bind(aui.EVT_AUINOTEBOOK_PAGE_CLOSE, 
self.__OnPageClose) 


    def __OnPageClose(self, e): 
        idx = e.GetSelection() 
        self.RemovePanel(idx) 
        e.Veto() 


    def  AddPanel(self, panel): 
        self._noteBook.AddPage(panel, panel.GetLabel(), False) 
        panel.Show() 
        self._noteBook.Update() 


    def RemovePanel(self, idx): 
        page = self._noteBook.GetPage(idx) 
        page.Hide() 
        self._noteBook.RemovePage(idx) 
        self._noteBook.Update() 


    def __OnClose(self, e): 
        open(u'perspective.txt', 'w').write(self._noteBook.SavePerspective()) 
        self._auiMgr.UnInit() 
        self.Destroy() 


class MyApp(wx.App): 
    def OnInit(self): 
        frame = MyFrame(None, "Simple wxPython App") 
        self.SetTopWindow(frame) 


        frame.Show(True) 
        return True 


app = MyApp(redirect=False) 
app.MainLoop() 


