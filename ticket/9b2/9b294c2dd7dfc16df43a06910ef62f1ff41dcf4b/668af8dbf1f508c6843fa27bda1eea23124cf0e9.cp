#include <iostream>
#include "wx/wx.h"
#include "wx/print.h"
#include "wx/printdlg.h"
#include <cmath>

/**
 * Shows a basic example of how to print stuff in wx.
 */


class QuickPrint : public wxPrintout
{
    wxPageSetupDialogData page_setup;
    wxPaperSize paper_type;
    int orient;
    int max_x, max_y;
    int pageAmount;
    
    static const int brush_size = 3;
    
    int margin_left, margin_right, margin_top, margin_bottom;
    
public:
    QuickPrint(int pageAmount, wxString title) : wxPrintout( title )
    {
        QuickPrint::pageAmount = pageAmount;
        orient = wxPORTRAIT; // wxPORTRAIT, wxLANDSCAPE
        paper_type = wxPAPER_LETTER;
        margin_left   = 16;
        margin_right  = 16;
        margin_top    = 32;
        margin_bottom = 32;
    }
    
    
    /** shows the page setup dialog, OR sets up defaults */
    bool performPageSetup(const bool showPageSetupDialog)
    {
        // don't show page setup dialog, use default values
        wxPrintData printdata;
        printdata.SetPrintMode( wxPRINT_MODE_PRINTER );
        printdata.SetOrientation( orient );
        printdata.SetNoCopies(1);
        printdata.SetPaperId( paper_type ); 
        
        page_setup = wxPageSetupDialogData(printdata);
        page_setup.SetMarginTopLeft    (wxPoint(margin_left,  margin_top));
        page_setup.SetMarginBottomRight(wxPoint(margin_right, margin_bottom)); 
        
        if (showPageSetupDialog)
        {
            wxPageSetupDialog dialog( NULL, &page_setup );
            if (dialog.ShowModal() == wxID_OK)
            {
                
                page_setup = dialog.GetPageSetupData();
                orient = page_setup.GetPrintData().GetOrientation();
                paper_type = page_setup.GetPrintData().GetPaperId();
                
                wxPoint marginTopLeft = page_setup.GetMarginTopLeft();
                wxPoint marginBottomRight = page_setup.GetMarginBottomRight();
                margin_left   = marginTopLeft.x;
                margin_right  = marginBottomRight.x;
                margin_top    = marginTopLeft.y;
                margin_bottom = marginBottomRight.y;
            }
            else
            {
                std::cout << "user canceled at first dialog" << std::endl;
                return false;
            }
        }
        return true;
    }
    
    /** Called when printing starts */
    void OnBeginPrinting()
    {
        // set-up coordinate system however we want, we'll use it when drawing
        
        // take paper size and margin sizes into account when setting up coordinate system
        // so that units are "square" (1 unit x is a wide as 1 unit y is high)
        // (actually, if we don't make it square, on some platforms wx will even resize your
        //  margins to make it so)
        wxSize paperSize = page_setup.GetPaperSize();
        const int largePaperSide = std::max(paperSize.GetHeight(), paperSize.GetWidth());
        const int smallPaperSide = std::min(paperSize.GetHeight(), paperSize.GetWidth());
        
        // here i'm using an arbitrary size, use whatever you wish
        if (orient == wxPORTRAIT)
        {
            float ratio = float(largePaperSide - margin_top  - margin_bottom) /
            float(smallPaperSide - margin_left - margin_right);
            
            max_x = 6000;
            max_y = max_x*ratio;
        }
        else 
        {
            float ratio = float(largePaperSide - margin_left - margin_right) /
            float(smallPaperSide - margin_top  - margin_bottom);
            
            max_y = 6000;
            max_x = max_y*ratio;
        }
    }
    
    /** returns the data obtained from the page setup dialog (or the defaults,
     * if dialog was not shown) */
    wxPrintData getPrintData()
    {
        return page_setup.GetPrintData();
    }
    
    /** Called when starting to print a document */
    bool OnBeginDocument(int startPage, int endPage)
    {
        std::cout << "beginning to print document, from page " << startPage
        << " to " << endPage << std::endl;
        return wxPrintout::OnBeginDocument(startPage, endPage);
    }
    
    /** wx will call this to know how many pages can be printed */
    void GetPageInfo(int *minPage, int *maxPage, int *pageSelFrom, int *pageSelTo)
    {
        *minPage = 1;
        *maxPage = pageAmount;
        
        *pageSelFrom = 1;
        *pageSelTo = pageAmount;
    }
    
    /** called by wx to know what pages this document has */
    bool HasPage(int pageNum)
    {
        // wx will call this to know how many pages can be printed
        if (pageNum >= 1 && pageNum <= pageAmount)
            return true;
        else
            return false;
    }
    
    
    /** called by wx everytime it's time to render a specific page onto the
     * printing device context */
    bool OnPrintPage(int pageNum)
    {
        std::cout << "printing page " << pageNum << std::endl;
        
        // ---- setup DC with coordinate system ----
        FitThisSizeToPageMargins(wxSize(max_x, max_y), page_setup);
        
        wxRect fitRect = GetLogicalPageMarginsRect(page_setup);
        
        wxCoord xoff = (fitRect.width - max_x) / 2;
        wxCoord yoff = (fitRect.height - max_y) / 2;
        OffsetLogicalOrigin(xoff, yoff);
        
        wxDC* ptr = GetDC();
        if (ptr==NULL || !ptr->IsOk())
        {
            std::cout << "DC is not Ok, interrupting printing" << std::endl;
            return false;
        }
        wxDC& dc = *ptr;
        
        // ---- A couple helper variables to help us during draw within paper area -----
        const int x0 = 0;
        const int y0 = 0;
        const int width = max_x;
        const int height = max_y;
        const int x1 = x0 + width;
        const int y1 = y0 + height;
        
        const int center_x = x0 + width/2;
        const int center_y = y0 + height/2;
        
        std::cout << "printable area : (" << x0 << ", " << y0 << ") to ("
        << x1 << ", " << y1 << ")" << std::endl;
        
        // ---- Draw to the print DC ----
        dc.Clear();
        
        for (int n=0; n<12; n++)
        {
            dc.SetPen(  wxPen( wxColour(255,0,0), n ) );
            
            const int y_from = y0 + height/12.0*n;
            const int y_to   = y0 + height/12.0*(n+1);
            dc.DrawLine(x0 + width/2, y_from, x0 + width/2, y_to);
        }
        
        return true;
    }  
    
    /** Called when printing is done. I have nothing to do in this case
     * in this example. */
    void OnEndPrinting()
    {
    }
};

// -------------------------------------------------------------------------------------
//                                HOW TO INVOKE THIS TEST
// -------------------------------------------------------------------------------------

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};


IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
    QuickPrint*  myprint = new QuickPrint( 5, wxT("wxPrint test") );
    if (!myprint->performPageSetup(true))
    {
        // user cancelled
        exit(0);
    }
    
    wxPrintDialogData data(myprint->getPrintData());
    wxPrinter printer(&data);
    const bool success = printer.Print(NULL, myprint, true /* show dialog */);
    
    delete myprint;
    
    if (!success)
    {
        std::cerr << "Failed!!\n";
        return false;
    }
    exit(0);
    return true;
}