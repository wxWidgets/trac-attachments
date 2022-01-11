import pdb
#coding:utf-8

import wx

class App(wx.App):
    def __init__(self,redirect=False,*args,**kwargs):
        super(App,self).__init__(redirect,*args,**kwargs);

    def OnInit(self):
        self.mainFrame = Frame(None,size=(400,300))
        self.mainFrame.Show()
        self.SetTopWindow(self.mainFrame)
        return True

class Frame(wx.Frame):
    def __init__(self,*args,**kwargs):
        super(Frame,self).__init__(*args,**kwargs)
        self.createMainPanel()

    def createMainPanel(self):
        self.mainPanel = wx.Panel(self,wx.ID_ANY)
        button   = wx.Button(self.mainPanel,label='Button',pos=(20,20))
        self.mainPanel.Bind(wx.EVT_LEFT_DOWN,self.onFramePress)
        self.Bind(wx.EVT_BUTTON,self.onButtonClick)
        button.Bind(wx.EVT_LEFT_DOWN,self.onLButtonPress)

    def onLButtonPress(self,event):
        wx.MessageBox('LEFT Button pressed')
        event.Skip()
    def onButtonClick(self,event):
        wx.MessageBox('CLICK Button')
    def onFramePress(self,event):
        wx.MessageBox('Frame pressed')

    def onClose(self,event):
        self.Destroy()

if __name__=='__main__':
    app = App()
    app.MainLoop()
