/***********************************************************************************************************************
*
* FILENAME: msLogger.h
*
* AUTHOR:   Richard Bennett of Systems4Silicon Limited
*
* Copyright (c) 2017 Systems4Silicon Limited.
* Proprietary and Confidential Information.
* All rights reserved.
* Not to be copied or distributed.
*
* EXPLANATION: Creates a logging mechanism with a timestamp of millisecond precision
* It uses the underlying wxWidgets logging facility. By default this uses timestamps with 1 second precision.
* Moreover the timestamp appears to be generated at the time of writing to file in a bacground thread, not 
* the time of calling the log function. It is therefore necessary get the timestamp before calling the
* wxWidgets log function
* 
* SYSTEM REQUIREMENTS: None
*
* LIMITATIONS: 
* Currently calling msLogger::write with a format string including the %s formatting parameter leads to no outpuy
* 
*
************************************************************************************************************************

************************************************************************************************************************
* MODIFICATION HISTORY:
*
* $Revision: $ $Date: $ $Author: $
*
***********************************************************************************************************************/

#ifndef _MSLOGGER
#define _MSLOGGER                        // #define flag to indicate this file has been included

#include <stdarg.h>
#include <stdio.h>
#include <wx/log.h>
#include <wx/string.h>
#include <wx/datetime.h>



// Class to implement logging with millisecond timestamps
class msLogger
{
public:

   msLogger(const char *logFileName)
   {
      m_logFile = fopen(logFileName, "w");
      // Note: (from https://wiki.wxwidgets.org/WxLog) When setting a new target must delete the old one (returned from function)
      // Need to do the reverse on shutdown
      wxLog *logTarget = new wxLogStderr(m_logFile);         // Don't need to save logTarget - stored internally
      delete wxLog::SetActiveTarget(logTarget);
      logTarget->DisableTimestamp();
   };

   ~msLogger()
   {
      // Delete the objects associated with logging.    
      wxLog *target = wxLog::SetActiveTarget(NULL);   // Stop logging and return the log target
      delete target;                                        // Delete the log target object
      fclose(m_logFile);                                    // Close the logging file 
     
   };


   static inline void write(const char* fmtStr, ...)
   {
      va_list args;
      va_start(args, fmtStr);

      wxDateTime timeObj = wxDateTime::UNow();


      wxString str(timeObj.Format("%H:%M:%S.%l"));
      str.Append(": ");
      str.Append(fmtStr);

      wxVLogMessage(str, args);
//      wxVLogMessage(fmtStr, args); // Applying fmtstr dircetly also does not work with %s
//      vprintf(fmtStr, args);

      va_end(args);
   };

   FILE  *m_logFile = NULL;
};


#define CONTROLLER_LOG(...)    msLogger::write(__VA_ARGS__)


#endif