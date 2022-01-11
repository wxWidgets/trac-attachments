#!/usr/bin/python

import wx

class Example(wx.Frame):
           
    def __init__(self, *args, **kw):
        super(Example, self).__init__(*args, **kw) 
        
        self.InitUI()
        
    def InitUI(self):   
            
        pnl = wx.Panel(self)

        # this is one group
        self.rb1 = wx.RadioButton(pnl, label='Value A', pos=(10, 10), style=wx.RB_GROUP)
        self.rb2 = wx.RadioButton(pnl, label='Value B', pos=(10, 40))
        self.rb3 = wx.RadioButton(pnl, label='Value C', pos=(10, 70))

        # this should be another group
        self.rb4 = wx.RadioButton(pnl, label='Value 1', pos=(10, 100), style=wx.RB_GROUP)
        self.rb5 = wx.RadioButton(pnl, label='Value 2', pos=(10, 130))

        self.SetSize((210, 250))
        self.SetTitle('wx.RadioButton')
        self.Centre()
        self.Show(True)     
       
        
def main():
    
    ex = wx.App()
    Example(None)
    ex.MainLoop()    

if __name__ == '__main__':
    main()   