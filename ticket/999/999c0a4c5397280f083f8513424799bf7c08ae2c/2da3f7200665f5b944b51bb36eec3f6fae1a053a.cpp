#include "wx/wxprec.h"

int main(int argc, char* argv[])
{
  _putenv("TZ=UTC+0"); // for Windows using UTC TZ

  struct tm time;
  time.tm_sec = time.tm_min = 0;
  time.tm_hour = 0;
  time.tm_wday = time.tm_yday = -1;
  time.tm_mday = 1;
  time.tm_mon = 0;
  time.tm_year = 70;
  time.tm_isdst = 0;

  time_t ticks = _mktime64(&time);

  wxDateTime wxdt(ticks);
  time_t wxticks = wxdt.GetTicks();

  for (int year = 70; year <= 1100; ++year) {
    time.tm_year = year;

    ticks = _mktime64(&time);

    wxdt.SetYear(1900 + year);
    wxticks = wxdt.GetValue().GetValue() / 1000;

    char *cs = asctime(&time);
    cs[strlen(cs) - 1] = 0; // why EOL?
    wxString s = wxdt.Format(wxT("%a %b %H:%M:%S %d %m %Y"));
    int diff = ticks - wxticks;
    _RPT3(_CRT_WARN, "Date: %s  - %s %d\n", cs, s.mb_str(), diff);
  }
  return 0;
}
