#include <wx/wx.h>
#include <stdint.h>

typedef enum
{
  BINARY,
  HEX
} input_type_t;


class HexView : public wxFrame
{
public:
   HexView(const wxString& title);

   // Value entry fields.
   void OnBinaryUpdate(wxCommandEvent & event);
   void OnHexUpdate(wxCommandEvent & event);

private:

   uint64_t           value_bits;
   int unsigned       bin_counter;
   int unsigned       hex_counter;

   // Layout elements,
   wxPanel           *top_panel;       // Top-level container.
   wxBoxSizer        *top_sizer;       // Top-level sizer.
   wxFlexGridSizer   *entry_sizer;     // Data entry sizer.

   // Labels.
   wxStaticText      *binary_label;    // Binary label.
   wxStaticText      *hex_label;       // Hex label.

   // Data entry fields.
   wxTextCtrl        *binary_data;     // Binary data.
   wxTextCtrl        *hex_data;        // Hex data.

   // Parsing functions.
   void ParseBinary();
   void ParseHex();

   // Update functions.
   void UpdateBinary();
   void UpdateHex();
   void DoUpdate(input_type_t  type);
};



// Top-level graphical container of the program.
HexView::HexView(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxRESIZE_BORDER | wxCAPTION)
{
   long   event_id;

   bin_counter = 0;
   hex_counter = 0;

   // Top-level panel and sizers.
   top_panel       = new wxPanel(this, wxID_ANY);
   top_sizer       = new wxBoxSizer(wxVERTICAL);
   entry_sizer     = new wxFlexGridSizer(6, 2, 5, 5);

   // Data entry labels.
   binary_label    = new wxStaticText(top_panel, wxID_ANY, wxT("Binary:"));
   hex_label       = new wxStaticText(top_panel, wxID_ANY, wxT("Hex:"));

   // Binary entry field.
   wxArrayString   binary_chars;
   binary_chars.Add(wxT("0"));
   binary_chars.Add(wxT("1"));
   wxTextValidator   binary_validator(wxFILTER_INCLUDE_CHAR_LIST, NULL);
   binary_validator.SetIncludes(binary_chars);

   event_id        = wxNewId();
   binary_data     = new wxTextCtrl(top_panel, event_id, wxT("0000000000000000"), wxDefaultPosition, wxDefaultSize, 0, binary_validator);
   binary_data->Connect(event_id, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(HexView::OnBinaryUpdate), NULL, this);
   binary_data->SetMaxLength(16);

   // Hex entry field.
   wxArrayString   hex_chars;
   hex_chars.Add(wxT("0"));
   hex_chars.Add(wxT("1"));
   hex_chars.Add(wxT("2"));
   hex_chars.Add(wxT("3"));
   hex_chars.Add(wxT("4"));
   hex_chars.Add(wxT("5"));
   hex_chars.Add(wxT("6"));
   hex_chars.Add(wxT("7"));
   hex_chars.Add(wxT("8"));
   hex_chars.Add(wxT("9"));
   hex_chars.Add(wxT("a"));   hex_chars.Add(wxT("A"));
   hex_chars.Add(wxT("b"));   hex_chars.Add(wxT("B"));
   hex_chars.Add(wxT("c"));   hex_chars.Add(wxT("C"));
   hex_chars.Add(wxT("d"));   hex_chars.Add(wxT("D"));
   hex_chars.Add(wxT("e"));   hex_chars.Add(wxT("E"));
   hex_chars.Add(wxT("f"));   hex_chars.Add(wxT("F"));
   wxTextValidator   hex_validator(wxFILTER_INCLUDE_CHAR_LIST, NULL);
   hex_validator.SetIncludes(hex_chars);

   event_id        = wxNewId();
   hex_data        = new wxTextCtrl(top_panel, event_id, wxT("0000"), wxDefaultPosition, wxDefaultSize, 0, hex_validator);
   hex_data->Connect(event_id, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(HexView::OnHexUpdate), NULL, this);
   hex_data->SetMaxLength(4);

   // Add data entry components.  
   entry_sizer->Add(binary_label, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
   entry_sizer->Add(binary_data, 1, wxEXPAND);
   entry_sizer->Add(hex_label, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
   entry_sizer->Add(hex_data, 1, wxEXPAND);

   // Set right column to grow when window is resized.
   entry_sizer->AddGrowableCol(1, 1);

   // Add to top-level.
   top_sizer->Add(entry_sizer, 1, wxALL | wxEXPAND, 5);

   // Fix height and minimum width.
   int    app_height      = top_sizer->GetMinSize().GetHeight();
   int    app_width_min   = top_sizer->GetMinSize().GetWidth();
   SetSizeHints(app_width_min, app_height, -1, app_height);    // min_w, min_h, max_w, max_h.

   // Set top-level sizer to handle width resize.
   top_panel->SetSizer(top_sizer);

   // Center the application on screen.
   Center();
}


//void HexView::OnBinaryUpdate(wxKeyEvent & event)
void HexView::OnBinaryUpdate(wxCommandEvent & event)
{
   printf("\n  OnBinaryUpdate()");
   fflush(stdout);
   DoUpdate(BINARY);
}


//void HexView::OnHexUpdate(wxKeyEvent & event)
void HexView::OnHexUpdate(wxCommandEvent & event)
{
   printf("\n  OnHexUpdate()");
   fflush(stdout);
   DoUpdate(HEX);
}


void HexView::ParseBinary()
{
   int unsigned   string_index;
   int unsigned   bit_index        = 0;
   wxString       value_string     = binary_data->GetValue();

   // Reset value.
   value_bits = 0ULL;

   // Get string length (to find end of input string).
   string_index = value_string.Len();

   // Parse binary value.
   while (string_index--)
   {
      if (value_string[string_index] == wxT('1'))
      {
         value_bits |= ((uint64_t)1 << bit_index);
      }
      bit_index++;
   }
}


void HexView::ParseHex()
{
   int unsigned   string_index;
   int unsigned   nibble_index     = 0;
   wxString       value_string     = binary_data->GetValue();

   // Reset value.
   value_bits = 0ULL;

   // Get string length (to find end of input string).
   string_index = value_string.Len();

   // Parse binary value.
   while (string_index--)
   {
      wxChar  c = value_string[string_index];

      // Numerical characters.
      if ((c >= wxT('0')) && (c <= wxT('9')))
      {
         value_bits |= (uint64_t)(c-wxT('0')) << (nibble_index*4);
      }

      // Lower-case hex characters.
      else if ((c >= wxT('a')) && (c <= wxT('f')))
      {
         value_bits |= (uint64_t)(c-wxT('a')+10) << (nibble_index*4);
      }

      // Upper-case hex characters.
      else if ((c >= wxT('A')) && (c <= wxT('F')))
      {
         value_bits |= (uint64_t)(c-wxT('A')+10) << (nibble_index*4);
      }
      nibble_index++;
   }
}


void HexView::UpdateBinary()
{
   wxString   temp_string;

   // Start at MSB.
   int unsigned     bit_index = 16;

   // Loop through all bits.
   while (bit_index--)
   {
      if ((1 << bit_index) & value_bits)
      {
         temp_string += wxT("1");
      }
      else
      {
         temp_string += wxT("0");
      }
   }

   binary_data->ChangeValue(temp_string);
}


void HexView::UpdateHex()
{
   // Parse hex string, based on expected format.
   wxString   temp_string;
   temp_string.Printf(wxT("%04X"), value_bits);
   hex_data->ChangeValue(temp_string);
}



void HexView::DoUpdate(input_type_t  type)
{
   // Parse either binary of hex input data and update other field.
   if (type == BINARY)
   {
      printf("\n  DoUpdate(): BINARY: %0d", bin_counter++);
      fflush(stdout);
      ParseBinary();
      UpdateHex();
   }
   else
   {
      printf("\n  DoUpdate(): HEX: %0d", hex_counter++);
      fflush(stdout);
      ParseHex();
      UpdateBinary();
   }
}



class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    HexView *float_view = new HexView(wxT("Float viewer"));
    float_view->Show(true);

    return true;
}





