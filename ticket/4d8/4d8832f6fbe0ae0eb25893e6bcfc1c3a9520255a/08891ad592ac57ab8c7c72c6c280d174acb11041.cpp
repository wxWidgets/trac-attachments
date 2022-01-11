#include <wx/clipbrd.h>
#include <wx/dataobj.h>
#include <wx/app.h>

static void setClipboard(const wxString& text) {
   wxTheClipboard->Open();
   wxTheClipboard->SetData(new wxTextDataObject(text));
   wxTheClipboard->Flush();
   wxTheClipboard->Close();
}

static void setPrimarySelection(const wxString& text) {
   wxTheClipboard->UsePrimarySelection(true);
   setClipboard(text);
   wxTheClipboard->UsePrimarySelection(false);
}

static bool getClipboard(wxString& text)
{
   bool result=false;
   if (wxTheClipboard->Open()) {
      if (wxTheClipboard->IsSupported(wxDF_TEXT)) {
         wxTextDataObject data;
         if (wxTheClipboard->GetData(data)) {
            text=data.GetText();
            result=true;
         }
      }
      wxTheClipboard->Close();
   }
   return result;
}

static bool getPrimarySelection(wxString& text)
{
   wxTheClipboard->UsePrimarySelection(true);
   bool result=getClipboard(text);
   wxTheClipboard->UsePrimarySelection(false);
   return result;
}

class ClipboardTest: public wxApp
{
   virtual bool OnInit();
};

IMPLEMENT_APP(ClipboardTest)

bool ClipboardTest::OnInit()
{
   wxString a=L"Hello",b=L"World",c;

   setClipboard(a);
   if ((!getClipboard(c))||(c!=a)) {
      printf("Initial setClipboard failed\n");
      return false;
   }

   setPrimarySelection(b);
   if ((!getPrimarySelection(c))||(c!=b)) {
      printf("Initial setPrimarySelection failed\n");
      return false;
   }
   if ((!getClipboard(c))||(c!=a)) {
      printf("setPrimarySelection destroyed the clipboard\n");
      return false;
   }

   printf("ok\n");

   return true;
}

 	  	 
