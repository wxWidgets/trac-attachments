
# To change this template, choose Tools | Templates
# and open the template in the editor.
# PromptingComboBox code from
# http://wiki.wxpython.org/Combo%20Box%20that%20Suggests%20Options

import wx
import wx.lib.inspection

class PromptingComboBox(wx.ComboBox) :
    def __init__(self, parent, value, choices=[], style=0, **par):
        wx.ComboBox.__init__(self, parent, wx.ID_ANY, value, style=style|wx.CB_DROPDOWN, choices=choices, **par)
        self.choices = choices
        self.Bind(wx.EVT_TEXT, self.EvtText)
        self.Bind(wx.EVT_CHAR, self.EvtChar)
        self.Bind(wx.EVT_COMBOBOX, self.EvtCombobox)
        self.ignoreEvtText = False

    def EvtCombobox(self, event):
        self.ignoreEvtText = True
        event.Skip()

    def EvtChar(self, event):
        if event.GetKeyCode() == 8:
            self.ignoreEvtText = True
        event.Skip()

    def EvtText(self, event):
        if self.ignoreEvtText:
            self.ignoreEvtText = False
            return
        currentText = event.GetString()
        found = False
        for choice in self.choices :
            if choice.startswith(currentText):
                self.ignoreEvtText = True
                self.SetValue(choice)
                self.SetInsertionPoint(len(currentText))
                self.SetMark(len(currentText), len(choice))
                found = True
                break
        if not found:
            event.Skip()


class MyFrame(wx.Frame):

    def __init__(self,*args,**kwds):
        wx.Frame.__init__(self,*args,**kwds)
        self.abox = PromptingComboBox(self,"",choices=["Item1","Item2","Item3"])
        self.Bind(wx.EVT_COMBOBOX,lambda event, caller=self.abox:self.on_component_comobobox_select(event,caller),self.abox )
        self.asizer = wx.GridSizer(1,2,10,10)
        self.asizer.Add(self.abox)
        self.SetSizer(self.asizer)
        self.asizer.Layout()


    def on_component_comobobox_select(self,event,caller):
        print "CLICKED ME ",event.GetString()
        event.Skip()


if __name__=="__main__":
    print wx.version()
    app = wx.PySimpleApp()
    af = MyFrame(parent=None,title="Prompting PEG400 test")
    
    af.Show()
    wx.lib.inspection.InspectionTool().Show()
    app.MainLoop()
