import wx
from wx.lib.mixins.inspection import InspectableApp

oneshot = False  # Allow interactive experiments, do not exit after initial test

def update_page_texts():
    for n in range(nb.GetPageCount()):
        nb.SetPageText(n, "Page %d" % n)

def on_page_changed(evt):
    page = evt.GetSelection()
    oldpage = evt.GetOldSelection()
    pages = nb.GetPageCount()
    print "Page changed %d -> %d (%d pages)." % (oldpage, page, pages)
    widget = nb.GetPage(page)
    print "Page widget: %r." % widget
    wx.CallAfter(update_page_texts)

def test_page_remove():
    current_page = nb.GetSelection()
    current_page_widget = nb.GetPage(current_page)
    print "Current page before removing it: %d (%r)." % (current_page, current_page_widget)
    def on_page_changed(evt):
        evt.Skip()
        nb.Unbind(wx.EVT_NOTEBOOK_PAGE_CHANGED, handler=on_page_changed)

        if current_page_widget == nb.GetPage(evt.GetSelection()):
            print "Whoops: Removed page still visible to PAGE_CHANGED event and marked as new selection."
    nb.Bind(wx.EVT_NOTEBOOK_PAGE_CHANGED, handler=on_page_changed)
    nb.RemovePage(current_page)
    if oneshot:
        wx.Exit()

print "wx Version: ", wx.VERSION_STRING
app = InspectableApp()
frame = wx.Frame(None, title="Notebook test")

nb = wx.Notebook(frame)
nb.Bind(wx.EVT_NOTEBOOK_PAGE_CHANGED, on_page_changed)
for i in range(10):
    nb.AddPage(wx.Panel(nb), "Page %d" % i)

button = wx.Button(frame, label="Remove current page")
button.Bind(wx.EVT_BUTTON, lambda evt: test_page_remove())

sz = wx.BoxSizer(wx.VERTICAL)
sz.Add(nb, flag=wx.EXPAND, proportion=1)
sz.Add(button, flag=wx.EXPAND)
frame.SetSizer(sz)
frame.SetSize((800, 500))

frame.Show()
wx.CallAfter(test_page_remove)
app.MainLoop()
