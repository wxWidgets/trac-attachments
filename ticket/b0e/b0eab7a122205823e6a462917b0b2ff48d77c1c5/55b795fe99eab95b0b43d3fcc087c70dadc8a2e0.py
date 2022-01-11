""" GridBug.py
    Failure environment: W2k, Python 2.3, wxPython 2.4.2.4
    
Displays a problem in restricted input fields on a grid.
The grid editor captures keystrokes from the user, making it
impossible to do data entry using the obvious method of typing
the value desired.
  An outragous example is show by the "TwoChar Select" column
  below, which requires the typist to strike the "8" key eleven
  times in order to enter the value "89".

(note: as you may suspect, the original program from which this
example was taken is a card game analyser.)
"""

import wx
import wx.grid

#define legal characters for encoding card values.
#Aces are coded as '1', Tens,Queens&Jacks are coded as '0'
CardChars = ['0','1','2','3','4','5','6','7','8','9']
#build a list of possible two-card combinations for the
#gambler's hand.
HandChars = []
for c in CardChars:
    for d in CardChars:
        HandChars.append(c+d)

#name the grid colums for easy access below
TopBet = 0
BetAmount = 1
DealerCard = 2
PlayerHand = 3
PlayerDecision = 4
AllCardsDealt = 5

#---------------------------------------------------------------------------

class RaPGrid(wx.grid.Grid):

    #the __init__ method defines the layout and operations of
    #the grid, which does all the editing work for the program
    def __init__(self, parent):
        wx.grid.Grid.__init__(self, parent, -1)
        self.moveTo = None

        self.CreateGrid(150, 6)

        # cell formatting
        self.SetColLabelValue(TopBet, "Default\nEdit")
        self.SetColLabelValue(BetAmount, "Normal\nNumeric")
        self.SetColLabelValue(DealerCard, "TwoChar\nSelect")
        self.SetColLabelValue(PlayerHand, "Range\n0 to 99")
        self.SetColLabelValue(PlayerDecision, "Four\nValues")
        self.SetColLabelValue(AllCardsDealt, "Normal\nNumeric")
        self.SetColLabelAlignment(wx.ALIGN_LEFT, wx.ALIGN_BOTTOM)
        #define the attributes of each column
        attr = wx.grid.GridCellAttr()
        attr.SetEditor(wx.grid.GridCellNumberEditor())
        self.SetColAttr(BetAmount,attr)
        attr = wx.grid.GridCellAttr()
        attr.SetEditor(wx.grid.GridCellChoiceEditor(HandChars))
        self.SetColAttr(DealerCard,attr)
        attr = wx.grid.GridCellAttr()
        attr.SetEditor(wx.grid.GridCellNumberEditor(0,99))
        self.SetColAttr(PlayerHand,attr)
        attr = wx.grid.GridCellAttr()
        attr.SetEditor(wx.grid.GridCellChoiceEditor(['S ','H ','DD','SP']))
        self.SetColAttr(PlayerDecision,attr)
        attr = wx.grid.GridCellAttr()
        attr.SetEditor(wx.grid.GridCellNumberEditor())
        self.SetColAttr(AllCardsDealt,attr)
        
#---------------------------------------------------------------------------

class TestFrame(wx.Frame):
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, -1, "GridBug Test", size=(640,480))
        grid = RaPGrid(self)

#---------------------------------------------------------------------------

if __name__ == '__main__':
    import sys
    app = wx.PySimpleApp()
    frame = TestFrame(None)
    frame.Show(True)
    app.MainLoop()

#---------------------------------------------------------------------------

 	  	 
