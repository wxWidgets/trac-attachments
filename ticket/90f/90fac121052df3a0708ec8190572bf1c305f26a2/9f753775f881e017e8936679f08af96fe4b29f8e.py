import wx, wx.stc

app = wx.PySimpleApp()
frame = wx.Frame(None)

stc = wx.stc.StyledTextCtrl(frame)
stc.StyleSetSpec(wx.stc.STC_STYLE_DEFAULT, 'fore:#000000,back:#FFFFFF,face:Serif,size:19')
stc.Text = "fi" * 20
stc.SetSelection(3,10)

frame.Show()
app.MainLoop()