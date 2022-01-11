#!/usr/bin/env python

import pygtk
pygtk.require('2.0')
import gtk

class Test:

    def settransparent(self, widget, data=None):
        #set opacity after main loop, this works as well
        self.window.set_opacity(0.5)
        if self.window.get_opacity()<1:
            self.window.set_opacity(1)
        else:
            self.window.set_opacity(0.5)

    def __init__(self):
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
    
        self.window.set_border_width(10)
        self.button = gtk.Button("Set Transparent")
        self.button.connect("clicked", self.settransparent, None)
        self.window.add(self.button)
        self.button.show()
        self.window.show()

        #set opacity before main loop, this works
        self.window.set_opacity(0.5)

    def main(self):
        gtk.main()

if __name__ == "__main__":
    test = Test()
    test.main()
