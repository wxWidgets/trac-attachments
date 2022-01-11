'''
Created on Apr 18, 2012

@author: john.evans
'''
import wx
import wx.xrc as xrc

app = wx.App(False)

res = xrc.XmlResource('test_dlg.xrc')
dlg = res.LoadDialog(None, 'test_dlg')
text = xrc.XRCCTRL(dlg, 'text_ctrl')

# It fails executing the following line:
text.SetValue( 'Bang' )

dlg.ShowModal()
dlg.Destroy()
