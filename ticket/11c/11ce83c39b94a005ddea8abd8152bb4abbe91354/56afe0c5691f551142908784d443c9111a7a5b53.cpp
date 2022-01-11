#include <string>
#include <vector>
#include <memory>
#include <map>

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/filepicker.h>
#include <wx/graphics.h>


/* XPM */
static const char * Red_x_xpm[] = {
"64 64 2 1",
" 	c None",
".	c #E04006",
"           .                                        .           ",
"          ...                                      ...          ",
"         .....                                    .....         ",
"        .......                                  .......        ",
"       .........                                .........       ",
"      ...........                              ...........      ",
"     .............                            .............     ",
"    ...............                          ...............    ",
"   .................                        .................   ",
"  ...................                      ...................  ",
" .....................                    ..................... ",
".......................                  .......................",
" .......................                ....................... ",
"  .......................              .......................  ",
"   .......................            .......................   ",
"    .......................          .......................    ",
"     .......................        .......................     ",
"      .......................      .......................      ",
"       .......................    .......................       ",
"        .......................  .......................        ",
"         ..............................................         ",
"          ............................................          ",
"           ..........................................           ",
"            ........................................            ",
"             ......................................             ",
"              ....................................              ",
"               ..................................               ",
"                ................................                ",
"                 ..............................                 ",
"                  ............................                  ",
"                   ..........................                   ",
"                    ........................                    ",
"                    ........................                    ",
"                   ..........................                   ",
"                  ............................                  ",
"                 ..............................                 ",
"                ................................                ",
"               ..................................               ",
"              ....................................              ",
"             ......................................             ",
"            ........................................            ",
"           ..........................................           ",
"          ............................................          ",
"         ..............................................         ",
"        .......................  .......................        ",
"       .......................    .......................       ",
"      .......................      .......................      ",
"     .......................        .......................     ",
"    .......................          .......................    ",
"   .......................            .......................   ",
"  .......................              .......................  ",
" .......................                ....................... ",
".......................                  .......................",
" .....................                    ..................... ",
"  ...................                      ...................  ",
"   .................                        .................   ",
"    ...............                          ...............    ",
"     .............                            .............     ",
"      ...........                              ...........      ",
"       .........                                .........       ",
"        .......                                  .......        ",
"         .....                                    .....         ",
"          ...                                      ...          ",
"           .                                        .           "};


class GbSelectEvent ;
wxDECLARE_EVENT(GB_SELECT_TYPE, GbSelectEvent);

class GbSelectEvent : public wxCommandEvent {
public:
	GbSelectEvent(int winid = 0, unsigned ant = 0, wxEventType eventType = GB_SELECT_TYPE) :
		wxCommandEvent(eventType, winid),
		mAntNum(ant) {}

	void setAntNum(unsigned ant) { mAntNum = ant ; }
	unsigned getAntNum() const { return mAntNum ; }

	GbSelectEvent(const GbSelectEvent& event) :
		wxCommandEvent(event),
		mAntNum(0)
	{
		this->setAntNum(event.getAntNum()) ;
	}

	virtual wxEvent *Clone() const
	{
		return new GbSelectEvent(*this);
	}

private:
	unsigned mAntNum ;
} ;

typedef void (wxEvtHandler::*GbSelectEventFunction)(GbSelectEvent &);
#define GbSelectEventHandler(func) wxEVENT_HANDLER_CAST(GbSelectEventFunction, func)
#define EVT_GB_SELECT(id, func) \
    wx__DECLARE_EVT1(GB_SELECT_TYPE, id, (&func))


class GbSelect : public wxWindow {
public:
	GbSelect(wxWindow* parent, wxWindowID id, unsigned numAntennas = 3, unsigned unitSize = 20) ;
	virtual ~GbSelect() {}

protected:
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void render(wxDC& dc, wxGraphicsContext *gc);
    void mouseDown(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void mouseLeftWindow(wxMouseEvent& event);

protected:
	virtual void updateSelection(unsigned ant) ;

private:
    unsigned mNumAntennas ;
    unsigned mSelected;
    unsigned mSize ;
    unsigned mWidth ;
    unsigned mHeight ;
    bool mPainted ;
    bool mPressedDown;

    DECLARE_EVENT_TABLE()
};

class GbPageBase {
public:
	GbPageBase(wxWindow* parent) ;
	virtual ~GbPageBase() {}

	virtual wxPanel* getPanel() ;

protected:
	virtual wxPanel* createPanel() =0 ;

protected:
	virtual void setPanel(wxPanel* panel) ;
	virtual wxWindow* getParent() ;

private:
	wxWindow* mParent ;
	wxPanel* mPanel ;

} ;

class GbPageSetup : public GbPageBase {
public:
	GbPageSetup(wxWindow* parent) ;
	virtual ~GbPageSetup() {}

protected:
	virtual wxPanel* createPanel() override ;

private:
	// events
	void onSelect(GbSelectEvent& event) ;
} ;

class GbPageTest : public GbPageBase {
public:
	GbPageTest(wxWindow* parent) ;
	virtual ~GbPageTest() {}

protected:
	virtual wxPanel* createPanel() override ;

} ;

class GtkBugFrame : public wxFrame
{
public:
    GtkBugFrame();
    virtual ~GtkBugFrame() {}

protected:
    enum Pages {
        PAGE_MEAS_TEST = 0,
        PAGE_SETUP,

    	PAGE_START = PAGE_MEAS_TEST,
    	PAGE_END = PAGE_SETUP
    };

    std::shared_ptr<GbPageBase> CreatePage(Pages page) ;

protected:
    static std::string pageStr(Pages page) ;

private:
    // Controls
    wxPanel *mPanel; // Panel containing notebook and other controls
    wxNotebook *mNotebook;
    wxBoxSizer *mSizerFrame;
    std::map<Pages, std::shared_ptr<GbPageBase>> mPages ;
};

//-------------------------------------------------------------------------------------------------
wxDEFINE_EVENT(GB_SELECT_TYPE, GbSelectEvent);

BEGIN_EVENT_TABLE(GbSelect, wxWindow)

    EVT_LEFT_DOWN(GbSelect::mouseDown)
    EVT_LEFT_UP(GbSelect::mouseReleased)
    EVT_LEAVE_WINDOW(GbSelect::mouseLeftWindow)
    EVT_PAINT(GbSelect::paintEvent)

END_EVENT_TABLE()

namespace {
	static unsigned totalWidth(unsigned unitSize, unsigned numAntennas)
	{
		unsigned drawWidth = numAntennas * unitSize ;

		// Must allow for label width

		if (numAntennas < 4)
			return 4 * unitSize ;

		return drawWidth ;
	}

	static unsigned totalHeight(unsigned unitSize)
	{
		return 2 * unitSize ;
	}

}

GbSelect::GbSelect(wxWindow* parent, wxWindowID id, unsigned numAntennas, unsigned unitSize) :
	wxWindow(parent, id),

	mNumAntennas(numAntennas),
	mSelected(0),

	mSize(unitSize),
    mWidth(totalWidth(unitSize, numAntennas)),
    mHeight(totalHeight(unitSize)),
	mPainted(false),
	mPressedDown(false)
{
	SetMinSize( wxSize(mWidth, mHeight) );
}

void GbSelect::paintEvent(wxPaintEvent& evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc)
    	render(dc, gc);
}

void GbSelect::paintNow()
{
	if (!mPainted)
		return ;

    wxClientDC dc(this);
    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc)
    	render(dc, gc);
}

void GbSelect::render(wxDC& dc, wxGraphicsContext* gc)
{
	dc.Clear();
	mPainted = true ;

    if (!gc)
    	return ;

	wxGraphicsPath path = gc->CreatePath() ;

	path.MoveToPoint(2, 2) ;
	path.AddLineToPoint(mSize-2, mSize-2) ;
	path.MoveToPoint(2, mSize-2) ;
	path.AddLineToPoint(mSize-2, 2) ;

	for (unsigned ant=0; ant < mNumAntennas; ++ant)
	{
		const wxColour* colour(wxBLACK) ;
		if (mSelected == ant)
			colour = wxRED ;

		gc->PushState();
		gc->SetPen(wxPen(*colour));
		gc->SetBrush(wxBrush(*colour));

		gc->Translate(ant * mSize, 0); // reposition the context origin
		gc->StrokePath(path);
		gc->PopState();
	}

    dc.SetTextForeground(*wxBLACK);
	dc.DrawText("Port " + std::to_string(mSelected+1), 0, mSize);
}

void GbSelect::mouseDown(wxMouseEvent& event)
{
    int x,y ;
    event.GetPosition(&x,&y);

    unsigned ant = x / mSize ;
	mPressedDown = true ;

	// Set selection
	updateSelection(ant) ;
}

void GbSelect::mouseReleased(wxMouseEvent& event)
{
	if (!mPressedDown)
		return ;

    mPressedDown = false;
    paintNow();

}

void GbSelect::mouseLeftWindow(wxMouseEvent& event)
{
	if (!mPressedDown)
		return ;

    mPressedDown = false;
    paintNow();
}

void GbSelect::updateSelection(unsigned ant)
{
	bool changed(ant != mSelected) ;

	mSelected = ant ;
	if (ant >= mNumAntennas)
		return ;

	// skip generating event on no change
	if (mPainted && !changed)
		return ;

	paintNow();

	// Propagate event
	GbSelectEvent antEvent(GetId(), ant);
	wxPostEvent(this, antEvent) ;
}


GbPageBase::GbPageBase(wxWindow* parent) :
	mParent(parent),
	mPanel(nullptr)
{
}

wxPanel* GbPageBase::getPanel()
{
	if (!mPanel)
	{
		mPanel = createPanel() ;
	}
	return mPanel ;
}

void GbPageBase::setPanel(wxPanel* panel)
{
	mPanel = panel ;
}

wxWindow* GbPageBase::getParent()
{
	return mParent ;
}


GbPageSetup::GbPageSetup(wxWindow* parent) :
	GbPageBase(parent)
{
}

wxPanel* GbPageSetup::createPanel()
{
    wxPanel *panel = new wxPanel(getParent(), wxID_ANY );
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    //---------------------------------------------------------
    wxFlexGridSizer* ctrlSizer = new wxFlexGridSizer(1, 9, 0, 0) ;
	sizer->Add(ctrlSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);


    //---------------------------------------------------------
    wxBoxSizer* listSizer = new wxBoxSizer(wxHORIZONTAL) ;
    sizer->Add(listSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5) ;

	GbSelect* sel = new GbSelect(panel, wxID_ANY) ;
    listSizer->Add(sel, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL|wxALL, 5) ;
    sel->Bind(GB_SELECT_TYPE, &GbPageSetup::onSelect, this) ;

	//---------------------------------------------------
    panel->SetSizer(sizer);
    panel->Layout();

    return panel;
}

void GbPageSetup::onSelect(GbSelectEvent& event)
{
	// Show an info dialog to ensure the fibres are plugged in for the new sector
	wxString warnMsg("Ensure fibres are reconnected to sector ") ;
	wxMessageDialog warnDialog(NULL,
		warnMsg,
		wxT("Warning"),
		wxOK | wxICON_EXCLAMATION) ;
	warnDialog.ShowModal() ;
}


GbPageTest::GbPageTest(wxWindow* parent) :
	GbPageBase(parent)
{
}

wxPanel* GbPageTest::createPanel()
{
    wxPanel *panel = new wxPanel(getParent(), wxID_ANY );
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    //---------------------------------------------------------
	wxBoxSizer* fileSizer2 = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(fileSizer2, 0, wxEXPAND |wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* fileLabel2 = new wxStaticText( panel, wxID_STATIC, wxT("Store Report: "), wxDefaultPosition, wxSize(150, -1), 0 );
	fileSizer2->Add(fileLabel2, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL|wxALL, 5);

	// pass an empty string as initial file
	wxFilePickerCtrl* filePicker2 = new wxFilePickerCtrl(panel, wxID_ANY,
			wxEmptyString,
			wxT("Save data"),
			wxT("Setup file (*.data)|*.data"),
			wxDefaultPosition,
			wxSize(500, -1),
			wxFLP_SAVE | wxFLP_OVERWRITE_PROMPT | wxFLP_USE_TEXTCTRL );

	fileSizer2->Add(filePicker2, 1, wxEXPAND | wxALIGN_RIGHT | wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	//---------------------------------------------------------
    {

    wxStaticBox *verifyBox = new wxStaticBox(panel, wxID_ANY, wxT("Verify System"));
    wxStaticBoxSizer* verifySizer = new wxStaticBoxSizer( verifyBox, wxVERTICAL );
    sizer->Add(verifySizer, 0, wxEXPAND |wxALIGN_CENTER_HORIZONTAL| wxALL, 5) ;

    wxFlexGridSizer* flexSizer = new wxFlexGridSizer(2, 1, 0, 0) ;
    flexSizer->AddGrowableCol(0) ;
    verifySizer->Add(flexSizer, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxPanel* ppanel = new wxPanel(panel, wxID_ANY) ;
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL) ;
	ppanel->SetSizer(sizer) ;

	wxButton* button = new wxButton(ppanel, wxID_ANY, wxString("Verify"), wxDefaultPosition, wxDefaultSize, 0 );
	sizer->Add(button, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

	wxGauge* pb = new wxGauge(
			ppanel, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
    sizer->Add(pb, 1, wxGROW|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    pb->SetValue(90) ;


    wxBitmap bitmap(Red_x_xpm) ;
    wxStaticBitmap* staticBitmap = new wxStaticBitmap(ppanel, wxID_ANY, bitmap) ;
    sizer->Add(staticBitmap, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	ppanel->Layout() ;


    flexSizer->Add(ppanel, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    //
	wxBoxSizer* horizSizer2 = new wxBoxSizer(wxHORIZONTAL);
	flexSizer->Add(horizSizer2, 1, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, wxT("This is some static text along the bottom 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890")) ;
	horizSizer2->Add(staticText) ;

    }

    panel->SetSizer(sizer);
    panel->Layout();


    return panel;
}



GtkBugFrame::GtkBugFrame() :
	wxFrame(NULL, wxID_ANY, wxT("GTK Bug?"), wxDefaultPosition, wxDefaultSize),
	mPanel(nullptr),
	mNotebook(nullptr),
	mSizerFrame(nullptr),
	mPages()
{
    wxFlexGridSizer *sizer = new wxFlexGridSizer(2, 1, 0, 0);
    sizer->AddGrowableCol(0) ;
    sizer->AddGrowableRow(1) ;

    mPanel = new wxPanel(this);

    // Set sizers
    mSizerFrame = new wxBoxSizer(wxVERTICAL);

    mNotebook = new wxNotebook(mPanel, wxID_ANY,
    		wxDefaultPosition,
			wxDefaultSize, wxBK_TOP) ;
    mNotebook->Hide() ;

    for (unsigned pg=(unsigned)PAGE_START; pg <= (unsigned)PAGE_END; ++pg)
    {
    	std::shared_ptr<GbPageBase> page(CreatePage((Pages)pg)) ;
    	if (!page)
    		continue ;

    	mPages[ (Pages)pg ] = page ;
	    mNotebook->AddPage(page->getPanel(),
			wxString(pageStr((Pages)pg)),
			(pg == (unsigned)PAGE_START ? true : false)
		) ;
    }

    mSizerFrame->Add(mNotebook, wxSizerFlags(1).Expand());

    mSizerFrame->Show(mNotebook);
    mSizerFrame->Layout();

    mPanel->SetSizer(mSizerFrame);
    mPanel->Layout();

    sizer->Add(mPanel, wxSizerFlags(1).Expand());
    SetSizerAndFit(sizer);
}

std::shared_ptr<GbPageBase> GtkBugFrame::CreatePage(Pages page)
{
	switch (page)
	{
	case PAGE_SETUP:
		return std::make_shared<GbPageSetup>(mNotebook) ;
		break ;

	case PAGE_MEAS_TEST:
		return std::make_shared<GbPageTest>(mNotebook) ;
		break ;

	default:
		return std::shared_ptr<GbPageBase>() ;
	}

	return std::shared_ptr<GbPageBase>() ;
}

std::string GtkBugFrame::pageStr(Pages page)
{
	static std::map<Pages, std::string> PAGE_NAMES{
		{PAGE_SETUP, 			"Advanced Setup"},
		{PAGE_MEAS_TEST, 		"Test"},
	} ;

	if ((unsigned)page > (unsigned)PAGE_END)
		return "" ;

	return PAGE_NAMES[page] ;
}



class GtkBugApp : public wxApp {
public:
    bool OnInit()
    {
        // make sure to call this first
        wxInitAllImageHandlers();

        mFrame = new GtkBugFrame();
        mFrame->Show();
        return true;
    }

private:
    wxFrame *mFrame;
} ;

IMPLEMENT_APP(GtkBugApp)
