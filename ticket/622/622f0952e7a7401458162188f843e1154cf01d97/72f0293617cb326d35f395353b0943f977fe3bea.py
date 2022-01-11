
import  wx
import random
#----------------------------------------------------------------------

class FrameParent(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self,None,-1,'calendario',size=(400,300),pos=(-1,-1))
        self.Centre(wx.CENTER_FRAME|wx.BOTH)

        panel = wx.Panel(self,-1)
        self.tree = wx.TreeCtrl(panel,pos=(1,1),size=(200,200),style=wx.BORDER|wx.TR_DEFAULT_STYLE)
        self.rootTree = self.tree.AddRoot('Sqlite')
        
        button = wx.Button(panel, label="Open", pos=(225, 10),size=(50,50))
        self.Bind(wx.EVT_BUTTON, self.onprova, button)
        self.Bind(wx.EVT_TREE_SEL_CHANGED, self.OnSelChanged)       

    def OnSelChanged(self,evt):
        print 'OnSelChanged', __name__
        
    def onprova(self,evt):
        st = random.randrange(1, 1000)
        newItem = self.tree.InsertItemBefore(self.rootTree,0,str(st))                    
        self.tree.SelectItem(newItem, select=True) #mi posizion sul nuovo dato
        self.tree.Expand(self.rootTree)                           
        #self.frameChild.Destroy()
        
if __name__ == '__main__':
    app = wx.PySimpleApp()
    #frame = wx.Frame(None,-1,'calendario',size=(250,200))
    testpanel = FrameParent()
    testpanel.Show()
    app.MainLoop()
