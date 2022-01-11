/////////////////////////////////////////////////////////////////////////////
// Name:        dataview.cpp
// Purpose:     wxDataViewCtrl wxWidgets sample
// Author:      Robert Roebling
// Modified by: Francesco Montorsi, Bo Yang
// Created:     06/01/06
// Copyright:   (c) Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif


#include "wx/dataview.h"
#include "wx/odcombo.h"

// ----------------------------------------------------------------------------
// MyApp
// ----------------------------------------------------------------------------

class MyApp: public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};

// ----------------------------------------------------------------------------
// Model
// ----------------------------------------------------------------------------

class Model : public wxDataViewVirtualListModel 
{
public:

  enum 
  {
    COLUMN_TEST
  };

  Model()
  {

  }

  void Init()
  {
    this->Reset(10);
  }


private:
  virtual unsigned int GetColumnCount() const 
  {
    return 1;
  }

  virtual wxString GetColumnType(unsigned int ) const 
  {
    return "string";
  }

  virtual void GetValueByRow(wxVariant& ,
    unsigned int ,
    unsigned int ) const
  {

  }

  virtual bool GetAttrByRow(unsigned int ,
    unsigned int ,
    wxDataViewItemAttr& ) const
  {
    return false;
  }

  virtual bool SetValueByRow(const wxVariant& ,
    unsigned int ,
    unsigned int )
  {
    return false;
  }
};
// ----------------------------------------------------------------------------
// MyFrame
// ----------------------------------------------------------------------------
class MyFrame : public wxFrame
{
private:
  wxDataViewCtrl* m_dataViewCtrl;
  wxObjectDataPtr<Model> m_model;

public:

  MyFrame( wxWindow* parent, 
    wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, 
    const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), 
    long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

  ~MyFrame();

};
// ----------------------------------------------------------------------------
// wxPenStyleComboBox from combo sample
// ----------------------------------------------------------------------------
class wxPenStyleComboBox : public wxOwnerDrawnComboBox
{
public:
  virtual void OnDrawItem( wxDC& dc,
    const wxRect& rect,
    int item,
    int flags ) const wxOVERRIDE
  {
    if ( item == wxNOT_FOUND )
      return;

    wxRect r(rect);
    r.Deflate(3);
    r.height -= 2;

    wxPenStyle penStyle = wxPENSTYLE_SOLID;
    if ( item == 1 )
      penStyle = wxPENSTYLE_TRANSPARENT;
    else if ( item == 2 )
      penStyle = wxPENSTYLE_DOT;
    else if ( item == 3 )
      penStyle = wxPENSTYLE_LONG_DASH;
    else if ( item == 4 )
      penStyle = wxPENSTYLE_SHORT_DASH;
    else if ( item == 5 )
      penStyle = wxPENSTYLE_DOT_DASH;
    else if ( item == 6 )
      penStyle = wxPENSTYLE_BDIAGONAL_HATCH;
    else if ( item == 7 )
      penStyle = wxPENSTYLE_CROSSDIAG_HATCH;
    else if ( item == 8 )
      penStyle = wxPENSTYLE_FDIAGONAL_HATCH;
    else if ( item == 9 )
      penStyle = wxPENSTYLE_CROSS_HATCH;
    else if ( item == 10 )
      penStyle = wxPENSTYLE_HORIZONTAL_HATCH;
    else if ( item == 11 )
      penStyle = wxPENSTYLE_VERTICAL_HATCH;

    wxPen pen( dc.GetTextForeground(), 3, penStyle );

    // Get text colour as pen colour
    dc.SetPen( pen );

    if ( !(flags & wxODCB_PAINTING_CONTROL) )
    {
      dc.DrawText(GetString( item ),
        r.x + 3,
        (r.y + 0) + ( (r.height/2) - dc.GetCharHeight() )/2
        );

      dc.DrawLine( r.x+5, r.y+((r.height/4)*3), r.x+r.width - 5, r.y+((r.height/4)*3) );
    }
    else
    {
      dc.DrawLine( r.x+5, r.y+r.height/2, r.x+r.width - 5, r.y+r.height/2 );
    }
  }

  virtual void OnDrawBackground( wxDC& dc, const wxRect& rect,
    int item, int flags ) const wxOVERRIDE
  {

    // If item is selected or even, or we are painting the
    // combo control itself, use the default rendering.
    if ( (flags & (wxODCB_PAINTING_CONTROL|wxODCB_PAINTING_SELECTED)) ||
      (item & 1) == 0 )
    {
      wxOwnerDrawnComboBox::OnDrawBackground(dc,rect,item,flags);
      return;
    }

    // Otherwise, draw every other background with different colour.
    wxColour bgCol(240,240,250);
    dc.SetBrush(wxBrush(bgCol));
    dc.SetPen(wxPen(bgCol));
    dc.DrawRectangle(rect);
  }

  virtual wxCoord OnMeasureItem( size_t item ) const wxOVERRIDE
  {
    // Simply demonstrate the ability to have variable-height items
    if ( item & 1 )
      return 36;
    else
      return 24;
  }

  virtual wxCoord OnMeasureItemWidth( size_t WXUNUSED(item) ) const wxOVERRIDE
  {
    return -1; // default - will be measured from text width
  }

};
// ----------------------------------------------------------------------------
// MyCustomRenderer
// ----------------------------------------------------------------------------
class MyCustomRenderer: public wxDataViewCustomRenderer
{
public:
    // This renderer can be either activatable or editable, for demonstration
    // purposes. In real programs, you should select whether the user should be
    // able to activate or edit the cell and it doesn't make sense to switch
    // between the two -- but this is just an example, so it doesn't stop us.
    explicit MyCustomRenderer(wxDataViewCellMode mode)
        : wxDataViewCustomRenderer("string", mode, wxALIGN_CENTER)
       { }

    virtual bool Render( wxRect rect, wxDC *dc, int  ) wxOVERRIDE
    {
        dc->SetBrush( *wxLIGHT_GREY_BRUSH );
        dc->SetPen( *wxTRANSPARENT_PEN );

        rect.Deflate(2);
        dc->DrawRoundedRectangle( rect, 5 );

        return true;
    }

    virtual bool ActivateCell(const wxRect& WXUNUSED(cell),
                              wxDataViewModel *WXUNUSED(model),
                              const wxDataViewItem &WXUNUSED(item),
                              unsigned int WXUNUSED(col),
                              const wxMouseEvent *WXUNUSED(mouseEvent)) wxOVERRIDE
    {
        return false;
    }

    virtual wxSize GetSize() const wxOVERRIDE
    {
        return wxSize(60,20);
    }

    virtual bool SetValue( const wxVariant &WXUNUSED(value) ) wxOVERRIDE 
    {
        return true;
    }

    virtual bool GetValue( wxVariant &WXUNUSED(value) ) const wxOVERRIDE 
    { 
      return true; 
    }

    virtual bool HasEditorCtrl() const wxOVERRIDE 
    { 
      return true; 
    }

    virtual wxWindow* CreateEditorCtrl(wxWindow* parent,
                     wxRect labelRect,
                     const wxVariant& WXUNUSED(value)) wxOVERRIDE
    {
      wxPenStyleComboBox* odc = new wxPenStyleComboBox();
      odc->Create(parent, wxID_ANY, wxEmptyString, labelRect.GetTopLeft(),
                wxSize(labelRect.GetWidth(), -1), wxCB_READONLY);
      
      wxArrayString m_arrItems;
      m_arrItems.Add( "Solid" );
      m_arrItems.Add( "Transparent" );
      m_arrItems.Add( "Dot" );
      m_arrItems.Add( "Long Dash" );
      m_arrItems.Add( "Short Dash" );
      m_arrItems.Add( "Dot Dash" );
      m_arrItems.Add( "Backward Diagonal Hatch" );
      m_arrItems.Add( "Cross-diagonal Hatch" );
      m_arrItems.Add( "Forward Diagonal Hatch" );
      m_arrItems.Add( "Cross Hatch" );
      m_arrItems.Add( "Horizontal Hatch" );
      m_arrItems.Add( "Vertical Hatch" );
      odc->Append(m_arrItems);

      odc->SetSelection(0);
      return odc;
    }

    virtual bool GetValueFromEditorCtrl(wxWindow* , wxVariant& ) wxOVERRIDE
    {
      return false;
    }
};


// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// MyApp
// ----------------------------------------------------------------------------

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{   
  if ( !wxApp::OnInit() )
      return false;

  MyFrame *frame = new MyFrame(NULL);

  frame->Show(true);
  return true;
}



// ----------------------------------------------------------------------------
// MyFrame
// ----------------------------------------------------------------------------

MyFrame::MyFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) 
  : wxFrame( parent, id, title, pos, size, style ), 
    m_model(new Model())
{
  this->SetSizeHints( wxDefaultSize, wxDefaultSize );

  wxBoxSizer* bSizer1;
  bSizer1 = new wxBoxSizer( wxVERTICAL );

  m_dataViewCtrl = new wxDataViewCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

  m_dataViewCtrl->AssociateModel(m_model.get());
  m_dataViewCtrl->AppendColumn(new wxDataViewColumn(
    wxT("test"),
    new MyCustomRenderer(wxDATAVIEW_CELL_EDITABLE),
    Model::COLUMN_TEST));


  bSizer1->Add( m_dataViewCtrl, 1, wxALL|wxEXPAND, 5 );


  this->SetSizer( bSizer1 );
  this->Layout();

  this->Centre( wxBOTH );

  m_model->Init();
}

MyFrame::~MyFrame()
{
}