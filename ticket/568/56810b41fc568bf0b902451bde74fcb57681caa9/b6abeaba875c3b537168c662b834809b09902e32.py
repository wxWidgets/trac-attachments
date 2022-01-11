import wx
import wx.lib.agw.hypertreelist as HTL
import wx.lib.customtreectrl as CT


class mainWindow(wx.Frame):
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self,parent,wx.ID_ANY, title='Test', size=(400,200), pos=(200,100), style=wx.DEFAULT_FRAME_STYLE)
       
        self.list=HyperTreeList(self, wx.ID_ANY)
       
       

class HyperTreeList(HTL.HyperTreeList):
    def __init__(self, parent, id=wx.ID_ANY, pos=wx.DefaultPosition, size=wx.DefaultSize, style=wx.SUNKEN_BORDER | wx.TR_HAS_BUTTONS | wx.TR_HAS_VARIABLE_ROW_HEIGHT): #| CT.TR_AUTO_CHECK_CHILD| CT.TR_AUTO_CHECK_PARENT):
        HTL.HyperTreeList.__init__(self, parent, id, pos, size, style)
       
        self.AddColumn("Column0")
        self.AddColumn("Column1",edit=True)
        self.AddColumn("Column2",edit=True)
       
        self.SetMainColumn(0)
       
        root=self.AddRoot('root')
        self.GetMainWindow().SetItemText(root,"1",1)
        self.GetMainWindow().SetItemText(root,"2",2)
        self.ExpandAll()
     


if __name__ == "__main__":
    app=wx.PySimpleApp()
     
    frame=mainWindow(None, wx.ID_ANY, "GUI")
    frame.Show()    
    app.MainLoop()
