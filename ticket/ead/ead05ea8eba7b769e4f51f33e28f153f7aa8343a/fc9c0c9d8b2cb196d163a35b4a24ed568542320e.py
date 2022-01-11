#! /usr/bin/python

"""Demonstrate strange event phenomenon in wxpython on gtk.

I reproduced this with wxpython 3.0.2 on Ubuntu 15.10 and 16.04.  It did
not happen on a Windows 8 system.  Steps to reproduce follow.

This program opens a window with two elements: A "Go" button, and a
listing.  The button makes a dialog appear.

Select one or more items from the listing.  Then click Go, to open the
dialog.  Complete the dialog by double-clicking one of the choices from
its list.

What happens (at least on my system) depends on where you double-clicked,
*relative to the parent window*!  It's as if the double-click, after
handling by the dialog, is also propagated to the parent window.

If the point where you double-clicked in the dialog happens to be over the
main window's listing, but not over any of the actual items in that list,
then your selection in the main window's listing is mysteriously undone.
This happens when the point under your double-click is below the listed
items, but also when the point under your double-click is to the right of
the listing's one column.

If the double-click happens anywhere else (e.g. when there is no portion
of the main window under that position in the dialog), your selection
remains unchanged as you would expect.  If there's a button or a text
input field underneath the double-click, the double-click does not
activate it.  The problem seems to happen only over empty portions of a
list control.

The same thing seems to happen with a custom wx.Dialog which closes itself
from a double-click handler, even when the handler stops the event from
propagating and/or clears pending events on the parent.
"""


import wx


class MyApp:

    def __init__(self):
        app = wx.App()
        frame = wx.Frame(parent=None, title="Frame.")
        self.panel = wx.Panel(parent=frame)
        self.panel.SetSizer(wx.BoxSizer(wx.VERTICAL))
        button = wx.Button(parent=self.panel, label="Go")
        button.Bind(wx.EVT_BUTTON, self.click)
        self.panel.GetSizer().Add(button)

        listing = wx.ListCtrl(parent=self.panel, style=wx.LC_REPORT)
        listing.InsertColumn(0, heading='column')
        listing.Append(("Aaaaaa",))
        listing.Append(("Bbbbbb",))
        listing.Append(("Cccccc",))

        self.panel.GetSizer().Add(listing, 0, wx.EXPAND)
        frame.Show(True)
        app.MainLoop()

    def click(self, event):
        choices = ["One", "Two"]
        dialog = wx.SingleChoiceDialog(
            parent=self.panel, message="Pick one.", caption="Dialog",
            choices=choices)
        answer = dialog.ShowModal()
        if answer == wx.ID_CANCEL:
            print("Cancel: %s." % answer)
        elif answer == wx.ID_OK:
            print("OK: %s." % answer)
            selection = dialog.GetSelection()
            print("Selection: %s." % selection)
        else:
            print("Other: %s." % answer)


if __name__ == '__main__':
    MyApp()
