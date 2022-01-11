import wxversion
#wxversion.select('2.8')
wxversion.select('2.9')
import wx

def on_radio(event=None):
    print 'in on_radio for', event.EventObject.Label
    enable_apply_button()

def on_apply_button(event=None):
    print 'entering on_apply_button'
    enable_apply_button(False)
    print 'leaving on_apply_button'

def enable_apply_button(enable=True):
    print 'entering enable_apply_button({})'.format(enable)
    #import pdb ; pdb.set_trace()
    print 'selection at start:', selected()
    controls['apply_button'].Enable(enable)
    print 'selection at end:', selected()
    print 'leaving enable_apply_button({})'.format(enable)

def selected():
    for name in radios:
        if controls[name].Value:
            return name
    else:
        return 'unknown'

radios = ('A', 'B', 'C')
controls = {}

def main():
    print wx.version()
    app = wx.PySimpleApp()
    parent = wx.Dialog(None, title='Button/Radio Interaction Test')
    sizer = wx.BoxSizer(wx.VERTICAL)
    for (row, name) in enumerate(radios):
        if row == 0:
            kwargs = {'style': wx.RB_GROUP}
        else:
            kwargs = {}
        radio = controls[name] = wx.RadioButton(parent, -1, name, **kwargs)
        radio.Bind(wx.EVT_RADIOBUTTON, on_radio)
        sizer.Add(radio, 0, wx.ALL, border=5)
    button = controls['apply_button'] = wx.Button(parent, -1, 'Apply')
    button.Bind(wx.EVT_BUTTON, on_apply_button)
    button.Disable()
    sizer.Add(button, 0, wx.ALL, border=5)
    parent.SetSizer(sizer)
    parent.ShowModal()
    app.MainLoop()

main()
