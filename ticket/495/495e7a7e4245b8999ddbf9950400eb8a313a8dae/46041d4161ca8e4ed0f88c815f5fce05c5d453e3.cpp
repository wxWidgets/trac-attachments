/////////////////////////////////////////////////////////////////////////////
// Name:        touchtest.cpp
// Purpose:     Multitouch sample
// Author:      Martin Koegler
// Modified by:
// Created:     2015-07-29
// Copyright:   (c) Martin Koegler
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"

// Define a new application
class MyApp: public wxApp
{
public:
    bool OnInit();
};

DECLARE_APP(MyApp)

#define TOUCH_POINTS 16

#ifndef EVT_TOUCH_BEGIN
#include "wx/treectrl.h"
#define wxTouchPointId wxTreeItemId
#endif


class MyFrame: public wxFrame
{
private:
    typedef struct
    {
        wxTouchPointId id;
        wxPoint last;
        wxPen pen;
    } TouchState;
    TouchState m_TouchPoints[TOUCH_POINTS];
    wxTouchPointId m_MouseId;
    
    void DrawStart(const wxTouchPointId& id, wxPoint pos);
    void DrawUpdate(const wxTouchPointId& id, wxPoint pos);
    void DrawEnd(const wxTouchPointId& id, wxPoint pos);
	
public:
    MyFrame(wxFrame *parent, const wxString& title,
        const wxPoint& pos, const wxSize& size, const long style);

#ifdef EVT_TOUCH_BEGIN
    void OnTouchBegin(wxTouchEvent& event);
    void OnTouchMove(wxTouchEvent& event);
    void OnTouchEnd(wxTouchEvent& event);
#endif

    void OnMouseDown(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseUp(wxMouseEvent& event);

    void OnQuit(wxCommandEvent& event);

DECLARE_EVENT_TABLE()
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    wxFrame* frame = new MyFrame(NULL, wxT("Multi-touch Test"), wxDefaultPosition,
        wxSize(500, 400), wxDEFAULT_FRAME_STYLE | wxHSCROLL | wxVSCROLL);
    SetTopWindow(frame);
    frame->CenterOnScreen();
    frame->Show(true);

    return true;
}

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
#ifdef EVT_TOUCH_BEGIN
    EVT_TOUCH_BEGIN(MyFrame::OnTouchBegin)
    EVT_TOUCH_MOVE(MyFrame::OnTouchMove)
    EVT_TOUCH_END(MyFrame::OnTouchEnd)
    EVT_TOUCH_CANCEL(MyFrame::OnTouchEnd)
#endif
    EVT_LEFT_DOWN(MyFrame::OnMouseDown)
    EVT_MOTION(MyFrame::OnMouseMove)
    EVT_LEFT_UP(MyFrame::OnMouseUp)
wxEND_EVENT_TABLE()

MyFrame::MyFrame(wxFrame *parent, const wxString& title, const wxPoint& pos,
    const wxSize& size, const long style)
    : wxFrame(parent, wxID_ANY, title, pos, size, style),
    m_MouseId(&m_MouseId)
{
    m_TouchPoints[0].pen = wxPen(*wxBLACK, 2);
    m_TouchPoints[1].pen = wxPen(*wxBLUE, 2);
    m_TouchPoints[2].pen = wxPen(*wxCYAN, 2);
    m_TouchPoints[3].pen = wxPen(*wxGREEN, 2);
    m_TouchPoints[4].pen = wxPen(*wxYELLOW, 2);
    m_TouchPoints[5].pen = wxPen(*wxRED, 2);
    m_TouchPoints[6].pen = wxPen(*wxLIGHT_GREY, 2);
    m_TouchPoints[7].pen = wxPen(*wxBLACK, 2, wxPENSTYLE_DOT_DASH);
    m_TouchPoints[8].pen = wxPen(*wxBLUE, 2, wxPENSTYLE_DOT_DASH);
    m_TouchPoints[9].pen = wxPen(*wxCYAN, 2, wxPENSTYLE_DOT_DASH);
    m_TouchPoints[10].pen = wxPen(*wxGREEN, 2, wxPENSTYLE_DOT_DASH);
    m_TouchPoints[11].pen = wxPen(*wxRED, 2, wxPENSTYLE_DOT_DASH);
    m_TouchPoints[12].pen = wxPen(*wxBLACK, 2, wxPENSTYLE_DOT);
    m_TouchPoints[13].pen = wxPen(*wxYELLOW, 2, wxPENSTYLE_DOT);
    m_TouchPoints[14].pen = wxPen(*wxBLUE, 2, wxPENSTYLE_DOT);
    m_TouchPoints[15].pen = wxPen(*wxRED, 2, wxPENSTYLE_DOT);

    wxMenu *file_menu = new wxMenu;

    file_menu->Append(wxID_EXIT, wxT("&Exit"));

    wxMenuBar *menu_bar = new wxMenuBar;

    menu_bar->Append(file_menu, wxT("&File"));
    SetMenuBar(menu_bar);

#ifdef EVT_TOUCH_BEGIN
    EnableTouchEvents();
#endif
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MyFrame::DrawStart(const wxTouchPointId& id, wxPoint pos)
{
    int idx = -1;
    for(unsigned i = 0; i < TOUCH_POINTS; i++)
        if (m_TouchPoints[i].id == id)
            idx = i;
    if (idx == -1)
        for(unsigned i = 0; i < TOUCH_POINTS; i++)
            if (!m_TouchPoints[i].id.IsOk())
	    {
                idx = i;
		break;
	    }
    if (idx == -1)
        return;
    m_TouchPoints[idx].id = id;
    m_TouchPoints[idx].last = pos;
}

void MyFrame::DrawUpdate(const wxTouchPointId& id, wxPoint pos)
{
    int idx = -1;
    for(unsigned i = 0; i < TOUCH_POINTS; i++)
        if (m_TouchPoints[i].id == id)
            idx = i;
    if (idx == -1)
        return;

    wxClientDC dc(this);
    dc.SetPen(m_TouchPoints[idx].pen);
    dc.DrawLine(m_TouchPoints[idx].last, pos);

    m_TouchPoints[idx].last = pos;
}

void MyFrame::DrawEnd(const wxTouchPointId& id, wxPoint pos)
{
    int idx = -1;
    for(unsigned i = 0; i < TOUCH_POINTS; i++)
        if (m_TouchPoints[i].id == id)
            idx = i;
    if (idx == -1)
        return;

    wxClientDC dc(this);
    dc.SetPen(m_TouchPoints[idx].pen);
    dc.DrawLine(m_TouchPoints[idx].last, pos);

    m_TouchPoints[idx].id.Unset();
}

#ifdef EVT_TOUCH_BEGIN
void MyFrame::OnTouchBegin(wxTouchEvent& event)
{
    if (event.IsPrimary())
        return;
    DrawStart(event.GetSequence(), event.GetPosition());
}

void MyFrame::OnTouchMove(wxTouchEvent& event)
{
    if (event.IsPrimary())
        return;
    DrawUpdate(event.GetSequence(), event.GetPosition());
}

void MyFrame::OnTouchEnd(wxTouchEvent& event)
{
    if (event.IsPrimary())
        return;
    DrawEnd(event.GetSequence(), event.GetPosition());
}
#endif

void MyFrame::OnMouseDown(wxMouseEvent& event)
{
    DrawStart(m_MouseId, event.GetPosition());
}

void MyFrame::OnMouseMove(wxMouseEvent& event)
{
    if (event.LeftIsDown())
        DrawUpdate(m_MouseId, event.GetPosition());
}

void MyFrame::OnMouseUp(wxMouseEvent& event)
{
    DrawEnd(m_MouseId, event.GetPosition());
}
