///////////////////////////////////////////////////////////////////////////////
// Name:        wx/datetime.h
// Purpose:     implementation of time/date related classes
// Author:      Vadim Zeitlin
// Modified by:
// Created:     11.05.99
// RCS-ID:      $Id: datetime.cpp,v 1.1 2005/01/18 18:52:35 jkay Exp $
// Copyright:   (c) 1999 Vadim Zeitlin <zeitlin@dptmaths.ens-cachan.fr>
//              parts of code taken from sndcal library by Scott E. Lee:
//
//               Copyright 1993-1995, Scott E. Lee, all rights reserved.
//               Permission granted to use, copy, modify, distribute and sell
//               so long as the above copyright and this permission statement
//               are retained in all copies.
//
// Licence:     wxWindows license
///////////////////////////////////////////////////////////////////////////////

/*
 * Implementation notes:
 *
 * 1. the time is stored as a 64bit integer containing the signed number of
 *    milliseconds since Jan 1. 1970 (the Unix Epoch) - so it is always
 *    expressed in GMT.
 *
 * 2. the range is thus something about 580 million years, but due to current
 *    algorithms limitations, only dates from Nov 24, 4714BC are handled
 *
 * 3. standard ANSI C functions are used to do time calculations whenever
 *    possible, i.e. when the date is in the range Jan 1, 1970 to 2038
 *
 * 4. otherwise, the calculations are done by converting the date to/from JDN
 *    first (the range limitation mentioned above comes from here: the
 *    algorithm used by Scott E. Lee's code only works for positive JDNs, more
 *    or less)
 *
 * 5. the object constructed for the given DD-MM-YYYY HH:MM:SS corresponds to
 *    this moment in local time and may be converted to the object
 *    corresponding to the same date/time in another time zone by using
 *    ToTimezone()
 *
 * 6. the conversions to the current (or any other) timezone are done when the
 *    internal time representation is converted to the broken-down one in
 *    wxDateTime::Tm.
 */

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#ifdef __GNUG__
    #pragma implementation "datetime.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if !defined(wxUSE_DATETIME) || wxUSE_DATETIME

#ifndef WX_PRECOMP
    #include "wx/string.h"
    #include "wx/log.h"
#endif // WX_PRECOMP

#include "wx/intl.h"
#include "wx/thread.h"
#include "wx/tokenzr.h"
#include "wx/module.h"

#define wxDEFINE_TIME_CONSTANTS // before including datetime.h

#include <ctype.h>

#include "wx/datetime.h"
#include "wx/timer.h"           // for wxGetLocalTimeMillis()

// ----------------------------------------------------------------------------
// conditional compilation
// ----------------------------------------------------------------------------

#if defined(HAVE_STRPTIME) && defined(__LINUX__)
    // glibc 2.0.7 strptime() is broken - the following snippet causes it to
    // crash (instead of just failing):
    //
    //      strncpy(buf, "Tue Dec 21 20:25:40 1999", 128);
    //      strptime(buf, "%x", &tm);
    //
    // so don't use it
    #undef HAVE_STRPTIME
#endif // broken strptime()

#if !defined(WX_TIMEZONE) && !defined(WX_GMTOFF_IN_TM)
    #if defined(__BORLANDC__) || defined(__MINGW32__) || defined(__VISAGECPP__)
        #define WX_TIMEZONE _timezone
    #elif defined(__MWERKS__)
        long wxmw_timezone = 28800;
        #define WX_TIMEZONE wxmw_timezone
    #elif defined(__DJGPP__)
        #include <sys/timeb.h>
        #include <values.h>
        static long wxGetTimeZone()
        {
            static long timezone = MAXLONG; // invalid timezone
            if (timezone == MAXLONG)
            {
                struct timeb tb;
                ftime(&tb);
                timezone = tb.timezone;
            }
            return timezone;
        }
        #define WX_TIMEZONE wxGetTimeZone()
    #elif defined(__DARWIN__)
        #define WX_GMTOFF_IN_TM
    #else // unknown platform - try timezone
        #define WX_TIMEZONE timezone
    #endif
#endif // !WX_TIMEZONE && !WX_GMTOFF_IN_TM

// ----------------------------------------------------------------------------
// macros
// ----------------------------------------------------------------------------

// debugging helper: just a convenient replacement of wxCHECK()
#define wxDATETIME_CHECK(expr, msg)     \
        if ( !(expr) )                  \
        {                               \
            wxFAIL_MSG(msg);            \
            *this = wxInvalidDateTime;  \
            return *this;               \
        }

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

class wxDateTimeHolidaysModule : public wxModule
{
public:
    virtual bool OnInit()
    {
        wxDateTimeHolidayAuthority::AddAuthority(new wxDateTimeWorkDays);

        return TRUE;
    }

    virtual void OnExit()
    {
        wxDateTimeHolidayAuthority::ClearAllAuthorities();
        wxDateTimeHolidayAuthority::ms_authorities.Clear();
    }

private:
    DECLARE_DYNAMIC_CLASS(wxDateTimeHolidaysModule)
};

IMPLEMENT_DYNAMIC_CLASS(wxDateTimeHolidaysModule, wxModule)

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// some trivial ones
static const int MONTHS_IN_YEAR = 12;

static const int SEC_PER_MIN = 60;

static const int MIN_PER_HOUR = 60;

static const int HOURS_PER_DAY = 24;

static const long SECONDS_PER_DAY = 86400l;

static const int DAYS_PER_WEEK = 7;

static const long MILLISECONDS_PER_DAY = 86400000l;

// this is the integral part of JDN of the midnight of Jan 1, 1970
// (i.e. JDN(Jan 1, 1970) = 2440587.5)
static const long EPOCH_JDN = 2440587l;

// the date of JDN -0.5 (as we don't work with fractional parts, this is the
// reference date for us) is Nov 24, 4714BC
static const int JDN_0_YEAR = -4713;
static const int JDN_0_MONTH = wxDateTime::Nov;
static const int JDN_0_DAY = 24;

// the constants used for JDN calculations
static const long JDN_OFFSET         = 32046l;
static const long DAYS_PER_5_MONTHS  = 153l;
static const long DAYS_PER_4_YEARS   = 1461l;
static const long DAYS_PER_400_YEARS = 146097l;

// this array contains the cumulated number of days in all previous months for
// normal and leap years
static const wxDateTime::wxDateTime_t gs_cumulatedDays[2][MONTHS_IN_YEAR] =
{
    { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
    { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 }
};

// ----------------------------------------------------------------------------
// global data
// ----------------------------------------------------------------------------

// in the fine tradition of ANSI C we use our equivalent of (time_t)-1 to
// indicate an invalid wxDateTime object
const wxDateTime wxDefaultDateTime;

wxDateTime::Country wxDateTime::ms_country = wxDateTime::Country_Unknown;

// ----------------------------------------------------------------------------
// private globals
// ----------------------------------------------------------------------------

// a critical section is needed to protect GetTimeZone() static
// variable in MT case
#if wxUSE_THREADS
    static wxCriticalSection gs_critsectTimezone;
#endif // wxUSE_THREADS

// ----------------------------------------------------------------------------
// private functions
// ----------------------------------------------------------------------------

// debugger helper: shows what the date really is
#ifdef __WXDEBUG__
extern const wxChar *wxDumpDate(const wxDateTime* dt)
{
    static wxChar buf[128];

    wxStrcpy(buf, dt->Format(_T("%Y-%m-%d (%a) %H:%M:%S")));

    return buf;
}
#endif // Debug

// get the number of days in the given month of the given year
static inline
wxDateTime::wxDateTime_t GetNumOfDaysInMonth(int year, wxDateTime::Month month)
{
    // the number of days in month in Julian/Gregorian calendar: the first line
    // is for normal years, the second one is for the leap ones
    static wxDateTime::wxDateTime_t daysInMonth[2][MONTHS_IN_YEAR] =
    {
        { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
    };

    return daysInMonth[wxDateTime::IsLeapYear(year)][month];
}

// returns the time zone in the C sense, i.e. the difference UTC - local
// (in seconds)
static int GetTimeZone()
{
    // set to TRUE when the timezone is set
    static bool s_timezoneSet = FALSE;
#ifdef WX_GMTOFF_IN_TM
    static long gmtoffset = LONG_MAX; // invalid timezone
#endif

    wxCRIT_SECT_LOCKER(lock, gs_critsectTimezone);

    // ensure that the timezone variable is set by calling localtime
    if ( !s_timezoneSet )
    {
        // just call localtime() instead of figuring out whether this system
        // supports tzset(), _tzset() or something else
        time_t t = 0;
	struct tm tm_r;
        struct tm *tm = &tm_r;

        tm = localtime_r(&t,tm);
        s_timezoneSet = TRUE;

#ifdef WX_GMTOFF_IN_TM
        // note that GMT offset is the opposite of time zone and so to return
        // consistent results in both WX_GMTOFF_IN_TM and !WX_GMTOFF_IN_TM
        // cases we have to negate it
        gmtoffset = -tm->tm_gmtoff;
#endif
    }

#ifdef WX_GMTOFF_IN_TM
    return (int)gmtoffset;
#else
    return (int)WX_TIMEZONE;
#endif
}

// return the integral part of the JDN for the midnight of the given date (to
// get the real JDN you need to add 0.5, this is, in fact, JDN of the
// noon of the previous day)
static long GetTruncatedJDN(wxDateTime::wxDateTime_t day,
                            wxDateTime::Month mon,
                            int year)
{
    // CREDIT: code below is by Scott E. Lee (but bugs are mine)

    // check the date validity
    wxASSERT_MSG(
      (year > JDN_0_YEAR) ||
      ((year == JDN_0_YEAR) && (mon > JDN_0_MONTH)) ||
      ((year == JDN_0_YEAR) && (mon == JDN_0_MONTH) && (day >= JDN_0_DAY)),
      _T("date out of range - can't convert to JDN")
                );

    // make the year positive to avoid problems with negative numbers division
    year += 4800;

    // months are counted from March here
    int month;
    if ( mon >= wxDateTime::Mar )
    {
        month = mon - 2;
    }
    else
    {
        month = mon + 10;
        year--;
    }

    // now we can simply add all the contributions together
    return ((year / 100) * DAYS_PER_400_YEARS) / 4
            + ((year % 100) * DAYS_PER_4_YEARS) / 4
            + (month * DAYS_PER_5_MONTHS + 2) / 5
            + day
            - JDN_OFFSET;
}

// this function is a wrapper around strftime(3)
static wxString CallStrftime(const wxChar *format, const tm* tm)
{
    wxChar buf[4096];
    if ( !wxStrftime(buf, WXSIZEOF(buf), format, tm) )
    {
        // buffer is too small?
        wxFAIL_MSG(_T("strftime() failed"));
    }

    return wxString(buf);
}

// if year and/or month have invalid values, replace them with the current ones
static void ReplaceDefaultYearMonthWithCurrent(int *year,
                                               wxDateTime::Month *month)
{
    struct tm tm_r;
    struct tm *tmNow = &tm_r;

    if ( *year == wxDateTime::Inv_Year )
    {
        tmNow = wxDateTime::GetTmNow(tmNow);

        *year = 1900 + tmNow->tm_year;
    }

    if ( *month == wxDateTime::Inv_Month )
    {
        if ( !tmNow )
            tmNow = wxDateTime::GetTmNow(tmNow);

        *month = (wxDateTime::Month)tmNow->tm_mon;
    }
}

// fll the struct tm with default values
static void InitTm(struct tm& tm)
{
    // struct tm may have etxra fields (undocumented and with unportable
    // names) which, nevertheless, must be set to 0
    memset(&tm, 0, sizeof(struct tm));

    tm.tm_mday = 1;   // mday 0 is invalid
    tm.tm_year = 76;  // any valid year
    tm.tm_isdst = -1; // auto determine
}

// parsing helpers
// ---------------

// return the month if the string is a month name or Inv_Month otherwise
static wxDateTime::Month GetMonthFromName(const wxString& name, int flags)
{
    wxDateTime::Month mon;
    for ( mon = wxDateTime::Jan; mon < wxDateTime::Inv_Month; wxNextMonth(mon) )
    {
        // case-insensitive comparison either one of or with both abbreviated
        // and not versions
        if ( flags & wxDateTime::Name_Full )
        {
            if ( name.CmpNoCase(wxDateTime::
                        GetMonthName(mon, wxDateTime::Name_Full)) == 0 )
            {
                break;
            }
        }

        if ( flags & wxDateTime::Name_Abbr )
        {
            if ( name.CmpNoCase(wxDateTime::
                        GetMonthName(mon, wxDateTime::Name_Abbr)) == 0 )
            {
                break;
            }
        }
    }

    return mon;
}

// return the weekday if the string is a weekday name or Inv_WeekDay otherwise
static wxDateTime::WeekDay GetWeekDayFromName(const wxString& name, int flags)
{
    wxDateTime::WeekDay wd;
    for ( wd = wxDateTime::Sun; wd < wxDateTime::Inv_WeekDay; wxNextWDay(wd) )
    {
        // case-insensitive comparison either one of or with both abbreviated
        // and not versions
        if ( flags & wxDateTime::Name_Full )
        {
            if ( name.CmpNoCase(wxDateTime::
                        GetWeekDayName(wd, wxDateTime::Name_Full)) == 0 )
            {
                break;
            }
        }

        if ( flags & wxDateTime::Name_Abbr )
        {
            if ( name.CmpNoCase(wxDateTime::
                        GetWeekDayName(wd, wxDateTime::Name_Abbr)) == 0 )
            {
                break;
            }
        }
    }

    return wd;
}

// scans all digits (but no more than len) and returns the resulting number
static bool GetNumericToken(size_t len, const wxChar*& p, unsigned long *number)
{
    size_t n = 1;
    wxString s;
    while ( wxIsdigit(*p) )
    {
        s += *p++;

        if ( len && ++n > len )
            break;
    }

    return !!s && s.ToULong(number);
}

// scans all alphabetic characters and returns the resulting string
static wxString GetAlphaToken(const wxChar*& p)
{
    wxString s;
    while ( wxIsalpha(*p) )
    {
        s += *p++;
    }

    return s;
}

// ============================================================================
// implementation of wxDateTime
// ============================================================================

// ----------------------------------------------------------------------------
// struct Tm
// ----------------------------------------------------------------------------

wxDateTime::Tm::Tm()
{
    year = (wxDateTime_t)wxDateTime::Inv_Year;
    mon = wxDateTime::Inv_Month;
    mday = 0;
    hour = min = sec = msec = 0;
    wday = wxDateTime::Inv_WeekDay;
}

wxDateTime::Tm::Tm(const struct tm& tm, const TimeZone& tz)
              : m_tz(tz)
{
    msec = 0;
    sec = tm.tm_sec;
    min = tm.tm_min;
    hour = tm.tm_hour;
    mday = tm.tm_mday;
    mon = (wxDateTime::Month)tm.tm_mon;
    year = 1900 + tm.tm_year;
    wday = tm.tm_wday;
    yday = tm.tm_yday;
}

bool wxDateTime::Tm::IsValid() const
{
    // we allow for the leap seconds, although we don't use them (yet)
    return (year != wxDateTime::Inv_Year) && (mon != wxDateTime::Inv_Month) &&
           (mday <= GetNumOfDaysInMonth(year, mon)) &&
           (hour < 24) && (min < 60) && (sec < 62) && (msec < 1000);
}

void wxDateTime::Tm::ComputeWeekDay()
{
    // compute the week day from day/month/year: we use the dumbest algorithm
    // possible: just compute our JDN and then use the (simple to derive)
    // formula: weekday = (JDN + 1.5) % 7
    wday = (wxDateTime::WeekDay)(GetTruncatedJDN(mday, mon, year) + 2) % 7;
}

void wxDateTime::Tm::AddMonths(int monDiff)
{
    // normalize the months field
    while ( monDiff < -mon )
    {
        year--;

        monDiff += MONTHS_IN_YEAR;
    }

    while ( monDiff + mon >= MONTHS_IN_YEAR )
    {