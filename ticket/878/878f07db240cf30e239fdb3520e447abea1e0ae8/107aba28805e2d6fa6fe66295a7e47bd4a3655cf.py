################################################################################
# file: printout.py
################################################################################

import wx

class Printout(wx.Printout):

    def __init__(self,
                 canvas,
                 size=(500, 500)):

        wx.Printout.__init__(self)

        self.print_canvas = canvas
        self.print_size = size

    def OnBeginDocument(self, start, end):
        return super(Printout, self).OnBeginDocument(start, end)

    def OnEndDocument(self):
        super(Printout, self).OnEndDocument()

    def OnBeginPrinting(self):
        super(Printout, self).OnBeginPrinting()

    def OnEndPrinting(self):
        super(Printout, self).OnEndPrinting()

    def OnPreparePrinting(self):
        super(Printout, self).OnPreparePrinting()

    def HasPage(self, page):
        if page <= 2:
            return True
        else:
            return False

    def GetPageInfo(self):
        return (1, 2, 1, 2)

    def OnPrintPage(self, page):
        dc = self.GetDC()

        #-------------------------------------------
        # One possible method of setting scaling factors...
        maxX, maxY = self.print_size

        # Let's have at least 50 device units margin
        marginX = 50
        marginY = 50

        # Add the margin to the graphic size
        maxX = maxX + (2 * marginX)
        maxY = maxY + (2 * marginY)

        # Get the size of the DC in pixels
        (w, h) = dc.GetSizeTuple()

        # Calculate a suitable scaling factor
        scaleX = float(w) / maxX
        scaleY = float(h) / maxY

        # Use x or y scaling factor, whichever fits on the DC
        actualScale = min(scaleX, scaleY)

        # Calculate the position on the DC for centering the graphic
        #posX = (w - (self.print_canvas.getWidth() * actualScale)) / 2.0
        #posY = (h - (self.print_canvas.getHeight() * actualScale)) / 2.0
        posX = (w - (maxX * actualScale)) / 2.0
        posY = (h - (maxY * actualScale)) / 2.0

        # Set the scale and origin
        dc.SetUserScale(actualScale, actualScale)
        dc.SetDeviceOrigin(int(posX), int(posY))

        #-------------------------------------------

        self.print_canvas.DoDrawing(dc)
        dc.DrawText("Page: %d" % page, marginX/2, maxY-marginY)

        return True

class Printable:
    """
    Mixin for printable windows.
    """

    def __init__(self,
                 print_canvas=None,
                 print_size=(1100, 850)):

        self.print_canvas = print_canvas
        self.print_size = print_size

        # setup printing:
        self.printData = wx.PrintData()
        self.printData.SetPaperId(wx.PAPER_LETTER)
        self.printData.SetPrintMode(wx.PRINT_MODE_PRINTER)


    def PrintButton(self, event):
        pdd = wx.PrintDialogData(self.printData)
        pdd.SetToPage(2)
        printer = wx.Printer(pdd)
        printout = Printout(self.print_canvas)

        if not printer.Print(None, printout, True):
            wx.MessageBox("There was a problem printing.", "Printing", wx.OK)
        else:
            self.printData = wx.PrintData(printer.GetPrintDialogData().GetPrintData())
        printout.Destroy()


    def PrintPreview(self, event):
        data = wx.PrintDialogData(self.printData)
        printout = Printout(self.print_canvas)
        printout2 = Printout(self.print_canvas)
        self.preview = wx.PrintPreview(printout, printout2, data)

        if not self.preview.Ok():
            print "Houston, we have a problem...\n"
            return

        pfrm = wx.PreviewFrame(self.preview, None, "This is a print preview")

        pfrm.Initialize()
        #pfrm.SetPosition(self.frame.GetPosition())
        #pfrm.SetSize(self.frame.GetSize())
        pfrm.SetPosition((300, 200))
        pfrm.SetSize((400, 500))
        
        pfrm.Show(True)

    def PageSetup(self, evt):
        psdd = wx.PageSetupDialogData(self.printData)
        psdd.CalculatePaperSizeFromId()
        dlg = wx.PageSetupDialog(self, psdd)
        dlg.ShowModal()

        # this makes a copy of the wx.PrintData instead of just saving
        # a reference to the one inside the PrintDialogData that will
        # be destroyed when the dialog is destroyed
        self.printData = wx.PrintData(dlg.GetPageSetupData().GetPrintData())
        dlg.Destroy()
