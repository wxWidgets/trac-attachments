import wx

def assertEquals(expected, input):
    assert expected == input, \
        '\n\nExpected: %s\nbut got: %s' % (expected, input)

input_title = 'Dialog Test Title'
app = wx.PySimpleApp()
frame = wx.Frame(None)

dialog = wx.Dialog(frame, title=input_title)
assertEquals(input_title, dialog.Label)
