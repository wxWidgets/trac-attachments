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
    int orient;
    int max_x, max_y;
    int pageAmount;
    
    static const int brush_size = 3;
    
    int margin_left, margin_right, margin_top, margin_bottom;
    
public:
    QuickPrint(int pageAmount, wxString title) : wxPrintout( title )
    {
        QuickPrint::pageAmount = pageAmount;
        orient = wxPORTRAIT;
        
        margin_left   = 16;
        margin_right  = 16;
        margin_top    = 32;
        margin_bottom = 32;
    }
    
    
    /** shows the page setup dialog, OR sets up defaults */
    void performPageSetup(const bool showPageSetupDialog)
    {
        // don't show page setup dialog, use default values
        wxPrintData printdata;
        printdata.SetPrintMode( wxPRINT_MODE_PRINTER );
        printdata.SetOrientation( wxPORTRAIT ); // wxPORTRAIT, wxLANDSCAPE
        printdata.SetNoCopies(1);
        printdata.SetPaperId( wxPAPER_LETTER ); 
        
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
            }
            else
            {
                std::cout << "user canceled at first dialog" << std::endl;
                exit(1);
            }
        }

        orient = page_setup.GetPrintData().GetOrientation();

    }
    
    /** Called when printing starts */
    void OnBeginPrinting()
    {
        // set-up coordinate system however we want
        // we'll use it when drawing
        
        // here i'm using arbitrary an size, use whatever you wish
        if (orient == wxPORTRAIT)
        {
            max_x = 680;
            max_y = 880;
        }
        else 
        {
            max_x = 880;
            max_y = 680;
        }
    }
    
    /** returns the data obtained from the page setup dialog (or the defaults, if dialog was not shown) */
    wxPrintData getPrintData()
    {
        return page_setup.GetPrintData();
    }
    
    /** Called when starting to print a document */
    bool OnBeginDocument(int startPage, int endPage)
    {
        std::cout << "beginning to print document, from page " << startPage << " to " << endPage << std::endl;
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
    
    /** called by wx everytime it's time to render a specific page onto the printing device context */
    bool OnPrintPage(int pageNum)
    {
        std::cout << "printing page " << pageNum << std::endl;
        
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
        
        /*
        // get bounds information, to know where to render stuff
        wxRect bounds = GetLogicalPageRect();
        const int x0 = bounds.x;
        const int y0 = bounds.y;
        const int width = bounds.width;
        const int height = bounds.height;
        const int x1 = x0 + width;
        const int y1 = y0 + height;
        */
        
        
        const int x0 = 0;
        const int y0 = 0;
        const int width = max_x;
        const int height = max_y;
        const int x1 = x0 + width;
        const int y1 = y0 + height;
        
        const int center_x = x0 + width/2;
        const int center_y = y0 + height/2;
        
        std::cout << "printable area : (" << x0 << ", " << y0 << ") to (" << x1 << ", " << y1 << ")" << std::endl;
        
        dc.Clear();
        
        dc.SetPen(  wxPen( wxColour(0,0,0), brush_size ) );
        dc.SetBrush( *wxTRANSPARENT_BRUSH );
        
        // draw a rectangle to show its bounds.
        dc.DrawRectangle(x0, y0, width, height);
        
        // draw wxWidgets logo
        dc.SetBrush( *wxRED_BRUSH );
        dc.DrawRectangle(center_x-45-38, center_y, 76, 76);
        dc.SetBrush( *wxBLUE_BRUSH );
        dc.DrawRectangle(center_x-38, center_y-45, 76, 76);
        dc.SetBrush( wxBrush( wxColor(255,244,0) ) );
        dc.DrawRectangle(center_x+45-38, center_y-10, 76, 76);
        
        // draw page number label
        wxString label( wxT("This is page #") );
        label << pageNum;
        dc.SetTextBackground( wxColour(255,255,0) );
        dc.SetTextForeground( wxColour(0,0,0) );
        dc.DrawText( label, x0 + width/5, y0 + height - 50 );
        
        return true;
    }  
    
    /** Called when printing is done. I have nothing to do in this case in this example. */
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
    myprint->performPageSetup(true);
    
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