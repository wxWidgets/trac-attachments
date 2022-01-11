"""
A test application to show that wx.combo.BitmapComboBox controls ignore
wx.EVT_TEXT_ENTER events if they have data in their choice lists, even if the
control has the wx.TE_PROCESS_ENTER style flag set.

In actuality it appears as if the wx.TE_PROCESS_ENTER style flag is unnecessary
on any/all wx.ComboBox class controls, contrary to the wxPython documentation
that says it must be set on Windows to have the wx.EVT_TEXT_ENTER event
properly emitted.

The first six ComboBox class controls have wx.EVT_TEXT_ENTER bound to them.
The last two controls do not. What this test is designed to demonstrate is that
wx.combo.BitmapComboBox controls *THAT HAVE CHOICE ITEMS ADDED TO THEM* ignore
any wx.EVT_TEXT_ENTER events bound to them. wx.combo.BitmapComboBox controls
with empty choice lists properly respect and utilize any wx.EVT_TEXT_ENTER
events bound to them.

To reiterate: wx.combo.BitmapComboBox controls with data in their choice lists
ignore wx.EVT_TEXT_ENTER events bound to them, regardless of whether or not
style=wx.TE_PROCESS_ENTER is set.

The last two controls create instances of the EnterWatcher() class, which
pushes a wx.EVT_CHAR_HOOK event onto the control's event stack. Note, this
event has to work from wx.EVT_CHAR_HOOK as attempting to bind wx.EVT_TEXT_ENTER
to the wx.combo.BitmapComboBox via this method either does not work or exhibits
the same issues as binding it via ctrl.Bind(). Conversely attempting to bind
wx.EVT_CHAR_HOOK to a wx.combo.BitmapComboBox via ctrl.Bind either does not
work or exhibits the same problem as attempting to bind wx.EVT_TEXT_ENTER
to the control.

The UI presents a grid of ComboBox class controls, each with different
combinations of style flags, choice data, and event handlers. By row the
ComboBox class controls are:

(controls with wx.EVT_TEXT_ENTER bound)
wx.ComboBox with choice data						|	wx.ComboBox with the
                                                wx.TE_PROCESS_ENTER style flag
                                                and choice data

wx.combo.BitmapComboBox with no choice data	|	wx.combo.BitmapComboBox with
                                                the wx.TE_PROCESS_ENTER style
                                                flag and no choice data

wx.combo.BitmapComboBox with choice data		|	wx.combo.BitmapComboBox with
                                                the wx.TE_PROCESS_ENTER style
                                                flag and choice data


(controls added to the EnterWatcher class, without wx.EVT_TEXT_ENTER bound)
wx.combo.BitmapComboBox with choice data		|	wx.combo.BitmapComboBox with
                                                the wx.TE_PROCESS_ENTER style
                                                flag and choice data

The log window at the bottom of the frame will display the following
information on a properly executed event: Control Name, Event Type, Value of
the ComboBox

The test application clearly shows that populated wx.combo.BitmapComboBox's
ignore wx.EVT_TEXT_ENTER events, while unpopulated wx.combo.BitmapComboBox's
do not. It also shows that in all instances setting the wx.TE_PROCESS_ENTER
style flag does nothing substantial to affect the events emitted by a
wx.ComboBox class control. Finally it shows that pushing a wx.EVT_CHAR_HOOK
onto the event handler stack for a populated wx.combo.BitmapComboBox control
is an effective, albeit clunky, workaround for the bug in
wx.combo.BitmapComboBox that prevents wx.EVT_TEXT_ENTER events from being
emitted.

*Examples:* ::

	Enter code examples here. (optional field)

*Todo:*
	* Enter thing to do. (optional field)

*Author:*
	* Jeff Hanna, jeff.hanna@dsvolition.com, 6/3/2014 10:01:12 AM
	* Andrew Dour, andrew.dour@dsvolition.com, 6/3/2014 10:01:12 AM
"""

import wx
import wx.combo


class EnterWatcher(wx.EvtHandler):
    """
    A wrapper class push wx.EVT_CHAR_HOOK onto the Event handler stack for
    whatever control is supplied in the class's contructor. That event is
    bound to this class's _on_key_down() member function.

    *Arguments:*
    	* ``ctrl``        The control to receive the pushed the wx.EVT_CHAR_HOOK.
    	* ``log_func``    A supplied output function that takes three string
                        variables for arguments.

    *Keyword Arguments:*
    	* ``<None>``

    *Examples:* ::

    	EnterWatcher(self.ddl_combo, self.write_to_log)

    *Todo:*
    	* Enter thing to do. (optional field)

    *Author:*
    	* Andrew Dour, andrew.dour@dsvolition.com, 6/3/2014 10:01:24 AM
    """

    def __init__(self, ctrl, log_func):
        wx.EvtHandler.__init__(self)

        self.ctrl = ctrl
        self.ctrl.PushEventHandler(self)
        self.log_func = log_func

        self.Bind(wx.EVT_CHAR_HOOK, self._on_key_down)


    def _on_key_down(self, event):
        """
        Event handler for the wx.EVT_CHAR_HOOK event bound to this class.
        The control's name, the event type, and the value of the control are
        written to the supplied log_func function.

        *Arguments:*
        	* ``event``	The emitted wx.Event

        *Keyword Arguments:*
        	* ``<None>``

        *Returns:*
        	* ``<None>``

        *Examples:* ::

        	Enter code examples here. (optional field)

        *Todo:*
        	* Enter thing to do. (optional field)

        *Author:*
        	* Andrew Dour, andrew.dour@dsvolition.com, 6/3/2014 10:01:38 AM
        """

        if event.GetKeyCode() in [wx.WXK_RETURN, wx.WXK_NUMPAD_ENTER]:
            ctrl = event.GetEventObject()
            val = ctrl.GetValue()
            if val == wx.EmptyString:
                val = '<Empty String>'
            self.log_func(ctrl.GetName(), 'wx.EVT_CHAR_HOOK', val)

        event.Skip()



class wxComboBoxTest(wx.Frame):
    """
    Test application to demonstrate three things:
    	The inability to bind wx.EVT_TEXT_ENTER events to wx.combo.BitmapComboBox
      controls that contain choice data. The ineffectiveness of the
      wx.TE_PROCESS_ENTER style flag
    	A workable, but inelegant workaround to the wx.EVT_TEXT_ENTER event bug
      on wx.combo.BitmapComboBox controls

    *Arguments:*
    	* ``Arguments``   wx.Frame() constructor arguments. Refer to the class
                        docstring for wx.Frame() for more information.

    *Keyword Arguments:*
    	* ``Argument``    wx.Frame() constructor keyword arguments. Refer to the
                        class docstring for wx.Frame() for more information.

    *Examples:* ::

    	Enter code examples here. (optional field)

    *Todo:*
    	* Enter thing to do. (optional field)

    *Author:*
    	* Jeff Hanna, jeff.hanna@dsvolition.com, 6/3/2014 10:01:29 AM
    """

    def __init__(self, parent):
        wx.Frame.__init__ (self, parent, id = wx.ID_ANY,
                            title = u'ComboBox & BitmapComboBox Test',
                            pos = wx.DefaultPosition,
                            size = wx.Size(1000, 400),
                            style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL)

        self.SetSizeHintsSz(wx.Size(1000, 400), wx.Size(1000, 400))
        self.SetBackgroundColour(
            wx.SystemSettings.GetColour(wx.SYS_COLOUR_BTNFACE))

        szr_main = wx.BoxSizer(wx.VERTICAL)

        szr_combo_boxes = wx.GridSizer(4, 2, 0, 0)
        ddl_choices = ['Volition', 'CTG', 'UX', 'Component UI']


        # ComboBox without wxTE_PROCESS_ENTER style
        szr_combo = wx.BoxSizer(wx.VERTICAL)
        self.lbl_combo = wx.StaticText(self, wx.ID_ANY, u'ComboBox',
                                        wx.DefaultPosition, wx.DefaultSize, 0)
        szr_combo.Add(self.lbl_combo, 0,
                       wx.ALIGN_CENTER_HORIZONTAL|wx.ALIGN_CENTER_VERTICAL|\
                       wx.TOP, 5)

        self.ddl_combo = wx.ComboBox(self, wx.ID_ANY, wx.EmptyString,
                                      wx.DefaultPosition, wx.DefaultSize,
                                      ddl_choices, 0)
        self.ddl_combo.Name = self.lbl_combo.GetLabelText()
        self.ddl_combo.Bind(wx.EVT_COMBOBOX, self._on_combo_selected)
        self.ddl_combo.Bind(wx.EVT_TEXT, self._on_text_changed)
        self.ddl_combo.Bind(wx.EVT_TEXT_ENTER, self._on_enter)

        szr_combo.Add(self.ddl_combo, 0, wx.ALIGN_CENTER_HORIZONTAL|\
                       wx.ALIGN_CENTER_VERTICAL|wx.BOTTOM, 5)
        szr_combo_boxes.Add(szr_combo, 1, wx.EXPAND, 5)


        # ComboBox with wxTE_PROCESS_ENTER style
        szr_combo_style = wx.BoxSizer(wx.VERTICAL)
        self.lbl_combo_style = \
            wx.StaticText(self, wx.ID_ANY,
                           u'ComboBox with wxTE_PROCESS_ENTER',
                           wx.DefaultPosition, wx.DefaultSize, 0)
        szr_combo_style.Add(self.lbl_combo_style, 0,
                             wx.ALIGN_CENTER_HORIZONTAL|\
                             wx.ALIGN_CENTER_VERTICAL|wx.TOP, 5)

        self.ddl_combo_style = wx.ComboBox(self, wx.ID_ANY, wx.EmptyString,
                                            wx.DefaultPosition, wx.DefaultSize,
                                            ddl_choices, wx.TE_PROCESS_ENTER)
        self.ddl_combo_style.Name = self.lbl_combo_style.GetLabelText()
        self.ddl_combo_style.Bind(wx.EVT_COMBOBOX, self._on_combo_selected)
        self.ddl_combo_style.Bind(wx.EVT_TEXT, self._on_text_changed)
        self.ddl_combo_style.Bind(wx.EVT_TEXT_ENTER, self._on_enter)

        szr_combo_style.Add(self.ddl_combo_style, 0,
                             wx.ALIGN_CENTER_HORIZONTAL|\
                             wx.ALIGN_CENTER_VERTICAL|wx.BOTTOM, 5)
        szr_combo_boxes.Add(szr_combo_style, 1, wx.EXPAND, 5)


        # Unpopulated BitmapComboBox without wxTE_PROCESS_ENTER style
        szr_bmp_combo = wx.BoxSizer(wx.VERTICAL)
        self.lbl_bmp_combo = wx.StaticText(self, wx.ID_ANY,
                                            u'BitmapComboBox',
                                            wx.DefaultPosition,
                                            wx.DefaultSize, 0)
        szr_bmp_combo.Add(self.lbl_bmp_combo, 0, wx.ALIGN_CENTER_HORIZONTAL|\
                           wx.ALIGN_CENTER_VERTICAL|wx.TOP, 5)

        self.ddl_bmp_combo = wx.combo.BitmapComboBox(self, wx.ID_ANY,
                                                      wx.EmptyString,
                                                      wx.DefaultPosition,
                                                      wx.DefaultSize, '', 0)
        self.ddl_bmp_combo.Name = self.lbl_bmp_combo.GetLabelText()
        self.ddl_bmp_combo.Bind(wx.EVT_COMBOBOX, self._on_combo_selected)
        self.ddl_bmp_combo.Bind(wx.EVT_TEXT, self._on_text_changed)
        self.ddl_bmp_combo.Bind(wx.EVT_TEXT_ENTER, self._on_enter)

        szr_bmp_combo.Add(self.ddl_bmp_combo, 0, wx.ALIGN_CENTER_HORIZONTAL|\
                           wx.ALIGN_CENTER_VERTICAL|wx.BOTTOM, 5)
        szr_combo_boxes.Add(szr_bmp_combo, 1, wx.EXPAND, 5)


        # Unpopulated BitmapComboBox with wxTE_PROCESS_ENTER style
        szr_bmp_combo_style = wx.BoxSizer(wx.VERTICAL)
        self.lbl_bmp_combo_style = \
            wx.StaticText(self, wx.ID_ANY,
                           u'BitmapComboBox with wxTE_PROCESS_ENTER',
                           wx.DefaultPosition, wx.DefaultSize, 0)
        szr_bmp_combo_style.Add(self.lbl_bmp_combo_style, 0,
                                 wx.ALIGN_CENTER_HORIZONTAL|\
                                 wx.ALIGN_CENTER_VERTICAL|wx.TOP, 5)

        self.ddl_bmp_combo_style = \
            wx.combo.BitmapComboBox(self, wx.ID_ANY, wx.EmptyString,
                                     wx.DefaultPosition, wx.DefaultSize,
                                     '', wx.TE_PROCESS_ENTER)
        self.ddl_bmp_combo_style.Name = \
            self.lbl_bmp_combo_style.GetLabelText()
        self.ddl_bmp_combo_style.Bind(wx.EVT_COMBOBOX,
                                       self._on_combo_selected)
        self.ddl_bmp_combo_style.Bind(wx.EVT_TEXT, self._on_text_changed)
        self.ddl_bmp_combo_style.Bind(wx.EVT_TEXT_ENTER, self._on_enter)

        szr_bmp_combo_style.Add(self.ddl_bmp_combo_style, 0,
                                 wx.ALIGN_CENTER_HORIZONTAL|\
                                 wx.ALIGN_CENTER_VERTICAL|wx.BOTTOM, 5)
        szr_combo_boxes.Add(szr_bmp_combo_style, 1, wx.EXPAND, 5)


        empty_bmp = wx.EmptyBitmap(16, 16)

        # Populated BitmapComboBox without wxTE_PROCESS_ENTER style
        szr_pop_bmp_combo = wx.BoxSizer(wx.VERTICAL)
        self.lbl_pop_bmp_combo = wx.StaticText(self, wx.ID_ANY,
                                                u'Populated BitmapComboBox',
                                                wx.DefaultPosition, wx.DefaultSize, 0)
        szr_pop_bmp_combo.Add(self.lbl_pop_bmp_combo, 0,
                               wx.ALIGN_CENTER_HORIZONTAL|\
                               wx.ALIGN_CENTER_VERTICAL|wx.TOP, 5)

        self.ddl_pop_bmp_combo = \
            wx.combo.BitmapComboBox(self, wx.ID_ANY, wx.EmptyString,
                                     wx.DefaultPosition, wx.DefaultSize, '', 0)
        for dc in ddl_choices:
            self.ddl_pop_bmp_combo.Append(dc, empty_bmp, dc)
        self.ddl_pop_bmp_combo.Name = self.lbl_pop_bmp_combo.GetLabelText()
        self.ddl_pop_bmp_combo.Bind(wx.EVT_COMBOBOX, self._on_combo_selected)
        self.ddl_pop_bmp_combo.Bind(wx.EVT_TEXT, self._on_text_changed)
        self.ddl_pop_bmp_combo.Bind(wx.EVT_TEXT_ENTER, self._on_enter)

        szr_pop_bmp_combo.Add(self.ddl_pop_bmp_combo, 0,
                               wx.ALIGN_CENTER_HORIZONTAL|\
                               wx.ALIGN_CENTER_VERTICAL|wx.BOTTOM, 5)
        szr_combo_boxes.Add(szr_pop_bmp_combo, 1, wx.EXPAND, 5)


        # Populated BitmapComboBox with wxTE_PROCESS_ENTER style
        szr_pop_bmp_combo_style = wx.BoxSizer(wx.VERTICAL)

        self.lbl_pop_bmp_combo_style = \
            wx.StaticText(self, wx.ID_ANY,
                           u'Populated BitmapComboBox with wxTE_PROCESS_ENTER',
                           wx.DefaultPosition, wx.DefaultSize, 0)
        szr_pop_bmp_combo_style.Add(self.lbl_pop_bmp_combo_style, 0,
                                     wx.ALIGN_CENTER_HORIZONTAL|\
                                     wx.ALIGN_CENTER_VERTICAL|wx.TOP, 5)

        self.ddl_pop_bmp_combo_style = \
            wx.combo.BitmapComboBox(self, wx.ID_ANY, wx.EmptyString,
                                     wx.DefaultPosition, wx.DefaultSize, '',
                                     wx.TE_PROCESS_ENTER)
        for dc in ddl_choices:
            self.ddl_pop_bmp_combo_style.Append(dc, empty_bmp, dc)
        self.ddl_pop_bmp_combo_style.Name = \
            self.lbl_pop_bmp_combo_style.GetLabelText()
        self.ddl_pop_bmp_combo_style.Bind(wx.EVT_COMBOBOX,
                                           self._on_combo_selected)
        self.ddl_pop_bmp_combo_style.Bind(wx.EVT_TEXT, self._on_text_changed)
        self.ddl_pop_bmp_combo_style.Bind(wx.EVT_TEXT_ENTER, self._on_enter)

        szr_pop_bmp_combo_style.Add(self.ddl_pop_bmp_combo_style, 0,
                                     wx.ALIGN_CENTER_HORIZONTAL|\
                                     wx.ALIGN_CENTER_VERTICAL|wx.BOTTOM, 5)
        szr_combo_boxes.Add(szr_pop_bmp_combo_style, 1, wx.EXPAND, 5)


        # Populated BitmapComboBox without wxTE_PROCESS_ENTER style and with dedicated enter handler
        szr_pop_hndl_bmp_combo = wx.BoxSizer(wx.VERTICAL)
        self.lbl_pop_hndl_bmp_combo = \
            wx.StaticText(self, wx.ID_ANY,
                           u'Populated BitmapComboBox with dedicated Enter handler',
                           wx.DefaultPosition, wx.DefaultSize, 0)
        szr_pop_hndl_bmp_combo.Add(self.lbl_pop_hndl_bmp_combo, 0,
                                    wx.ALIGN_CENTER_HORIZONTAL|\
                                    wx.ALIGN_CENTER_VERTICAL|wx.TOP, 5)

        self.ddl_pop_hndl_bmp_combo = \
            wx.combo.BitmapComboBox(self, wx.ID_ANY, wx.EmptyString,
                                     wx.DefaultPosition, wx.DefaultSize,
                                     '', 0)
        for dc in ddl_choices:
            self.ddl_pop_hndl_bmp_combo.Append(dc, empty_bmp, dc)
        EnterWatcher(self.ddl_pop_hndl_bmp_combo, self.write_to_log)
        self.ddl_pop_hndl_bmp_combo.Name = \
            self.lbl_pop_hndl_bmp_combo.GetLabelText()
        self.ddl_pop_hndl_bmp_combo.Bind(wx.EVT_COMBOBOX,
                                          self._on_combo_selected)
        self.ddl_pop_hndl_bmp_combo.Bind(wx.EVT_TEXT, self._on_text_changed)

        szr_pop_hndl_bmp_combo.Add(self.ddl_pop_hndl_bmp_combo, 0,
                                    wx.ALIGN_CENTER_HORIZONTAL|\
                                    wx.ALIGN_CENTER_VERTICAL|wx.BOTTOM, 5)
        szr_combo_boxes.Add(szr_pop_hndl_bmp_combo, 1, wx.EXPAND, 5)


        # Populated BitmapComboBox with wxTE_PROCESS_ENTER style and with a
        # dedicated enter handler
        szr_pop_hndl_bmp_combo_style = wx.BoxSizer(wx.VERTICAL)

        self.lbl_pop_hndl_bmp_combo_style = \
            wx.StaticText(self, wx.ID_ANY,
                           u'Populated BitmapComboBox with wxTE_PROCESS_ENTER and dedicated Enter handler',
                           wx.DefaultPosition, wx.DefaultSize, 0)
        szr_pop_hndl_bmp_combo_style.Add(self.lbl_pop_hndl_bmp_combo_style, 0,
                                          wx.ALIGN_CENTER_HORIZONTAL|\
                                          wx.ALIGN_CENTER_VERTICAL|wx.TOP, 5)

        self.ddl_pop_hndl_bmp_combo_style = \
            wx.combo.BitmapComboBox(self, wx.ID_ANY, wx.EmptyString,
                                     wx.DefaultPosition, wx.DefaultSize,
                                     '', wx.TE_PROCESS_ENTER)
        for dc in ddl_choices:
            self.ddl_pop_hndl_bmp_combo_style.Append(dc, empty_bmp, dc)
        EnterWatcher(self.ddl_pop_hndl_bmp_combo_style, self.write_to_log)
        self.ddl_pop_hndl_bmp_combo_style.Name = \
            self.lbl_pop_hndl_bmp_combo_style.GetLabelText()
        self.ddl_pop_hndl_bmp_combo_style.Bind(wx.EVT_COMBOBOX,
                                                self._on_combo_selected)
        self.ddl_pop_hndl_bmp_combo_style.Bind(wx.EVT_TEXT,
                                                self._on_text_changed)

        szr_pop_hndl_bmp_combo_style.Add(self.ddl_pop_hndl_bmp_combo_style,
                                          0, wx.ALIGN_CENTER_HORIZONTAL|\
                                          wx.ALIGN_CENTER_VERTICAL|wx.BOTTOM,
                                          5)
        szr_combo_boxes.Add(szr_pop_hndl_bmp_combo_style, 1, wx.EXPAND, 5)


        szr_main.Add(szr_combo_boxes, 3, wx.EXPAND, 5)

        # Output Window
        szr_log = wx.BoxSizer(wx.HORIZONTAL)

        self.txt_log_window = wx.TextCtrl(self, wx.ID_ANY, wx.EmptyString,
                                           wx.DefaultPosition, wx.DefaultSize,
                                           wx.TE_MULTILINE|wx.TE_READONLY|\
                                           wx.HSCROLL)
        szr_log.Add(self.txt_log_window, 1, wx.ALL|wx.EXPAND, 5)

        szr_main.Add(szr_log, 2, wx.EXPAND, 5)


        self.SetSizer(szr_main)
        self.Layout()

        self.Centre(wx.BOTH)


    def write_to_log(self, ctrl_name, event_type, val):
        """
        Writes three provided values to the frame's log window.

        *Arguments:*
        	* ``ctrl_name``	The name of the control last accessed.
        	* ``event_type``	The event type of the event last emitted.
        	* ``val``			The value of the control last accessed.

        *Keyword Arguments:*
        	* ``<None>``

        *Returns:*
        	* ``<None>``

        *Examples:* ::

        	Enter code examples here. (optional field)

        *Todo:*
        	* Enter thing to do. (optional field)

        *Author:*
        	* Jeff Hanna, jeff.hanna@dsvolition.com, 6/3/2014 10:02:01 AM
        """

        self.txt_log_window.write('CONTROL: {0}, EVENT: {1}, VALUE: {2}\n'.\
                                   format(ctrl_name, event_type, val))


    def _on_combo_selected(self, event):
        """
        Event handler for selecting an item from a choice list in a combobox.
        The emitting control is accessed, its name and value are retrieved.
        Those two items and the event type are written to the frame's
        log window.

        *Arguments:*
        	* ``event``    The emitted wx.Event, more than likely a
                        wx.EVT_COMBOBOX event.

        *Keyword Arguments:*
        	* ``<None>``

        *Returns:*
        	* ``<None>``

        *Examples:* ::

        	Enter code examples here. (optional field)

        *Todo:*
        	* Enter thing to do. (optional field)

        *Author:*
        	* Jeff Hanna, jeff.hanna@dsvolition.com, 6/3/2014 10:02:04 AM
        """

        ctrl = event.GetEventObject()
        selection = ctrl.GetSelection()
        val = ctrl.Items[selection]
        self.write_to_log(ctrl.GetName(), 'wx.EVT_COMBOBOX', val)


    def _on_enter(self, event):
        """
        Event handler for pressing the return or enter key while in a combobox.
        The emitting control is accessed, its name and value are retrieved.
        Those two items and the event type are written to the frame's
        log window.

        *Arguments:*
        	* ``event``    The emitted wx.Event, more than likely a
                        wx.EVT_TEXT_ENTER event.

        *Keyword Arguments:*
        	* ``<None>``

        *Returns:*
        	* ``<None>``

        *Examples:* ::

        	Enter code examples here. (optional field)

        *Todo:*
        	* Enter thing to do. (optional field)

        *Author:*
        	* Jeff Hanna, jeff.hanna@dsvolition.com, 6/3/2014 10:02:04 AM
        """

        ctrl = event.GetEventObject()
        val = ctrl.GetValue()
        if val == wx.EmptyString:
            val = '<Empty String>'
        self.write_to_log(ctrl.GetName(), 'wx.EVT_TEXT_ENTER', val)


    def _on_text_changed(self, event):
        """
        Event handler for typing text in a combobox. The emitting control is
        accessed, its name and value are retrieved. Those two items and the
        event type are written to the frame's log window.

        *Arguments:*
        	* ``event``    The emitted wx.Event, more than likely a
                        wx.EVT_TEXT event.

        *Keyword Arguments:*
        	* ``<None>``

        *Returns:*
        	* ``<None>``

        *Examples:* ::

        	Enter code examples here. (optional field)

        *Todo:*
        	* Enter thing to do. (optional field)

        *Author:*
        	* Jeff Hanna, jeff.hanna@dsvolition.com, 6/3/2014 10:02:04 AM
        """

        ctrl = event.GetEventObject()
        val = ctrl.GetValue()
        if val == wx.EmptyString:
            val = '<Empty String>'
        self.write_to_log(ctrl.GetName(), 'wx.EVT_TEXT', val)



if __name__ == '__main__':
    app = wx.App(False)
    frame = wxComboBoxTest(None)
    frame.Show(True)
    app.MainLoop()