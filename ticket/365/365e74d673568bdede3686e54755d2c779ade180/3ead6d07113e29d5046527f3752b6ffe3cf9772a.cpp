#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/dataview.h"

class MyModel: public wxDataViewVirtualListModel {
public:
    MyModel() : wxDataViewVirtualListModel() { Reset(10); }
    virtual unsigned int GetColumnCount() const { return 3; }
    virtual wxString GetColumnType( unsigned int) const {return wxT("string");}
    virtual void GetValueByRow( wxVariant &variant, unsigned int row, unsigned int col ) const {
        variant = wxString::Format("row-%d, col=%d", row, col);
    }
    virtual bool GetAttrByRow( unsigned int row, unsigned int col, wxDataViewItemAttr &attr ) const { return false; }
    virtual bool SetValueByRow( const wxVariant &variant, unsigned int row, unsigned int col ) { return true;}
};



class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
private:
    wxObjectDataPtr<MyModel> m_model;
	wxDataViewCtrl *m_dv;
};
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;
    MyFrame *frame = new MyFrame("Minimal wxWidgets App");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title)
{
    wxPanel *p = new wxPanel(this);
    m_model = new MyModel();

    m_dv = new wxDataViewCtrl(p, wxID_ANY);
    m_dv->AssociateModel(m_model.get());

// here is where it fails. If I use 0 as the model_column is OK. But any number greater than 0, result in
// array out of bound error.
// the patch submitted solve the problem.

    m_dv->AppendTextColumn("Column 0 to model column 2", 2, wxDATAVIEW_CELL_EDITABLE, wxCOL_WIDTH_AUTOSIZE);

    wxSizer *sz = new wxBoxSizer(wxVERTICAL);
    sz->Add(m_dv, 1, wxEXPAND);
    p->SetSizer(sz);
}
