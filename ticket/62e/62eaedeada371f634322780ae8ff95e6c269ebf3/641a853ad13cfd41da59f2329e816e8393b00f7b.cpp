/********** wxDb::DispAllErrors() **********/
bool wxDb::DispAllErrors(HENV aHenv, HDBC aHdbc, HSTMT aHstmt)
/*
 * This function is called internally whenever an error condition prevents the user's
 * request from being executed.  This function will query the datasource as to the
 * actual error(s) that just occured on the previous request of the datasource.
 *
 * The function will retrieve each error condition from the datasource and
 * Printf the codes/text values into a string which it then logs via logError().
 * If in DBDEBUG_CONSOLE mode, the constructed string will be displayed in the console
 * window and program execution will be paused until the user presses a key.
 *
 * This function always returns a FALSE, so that functions which call this function
 * can have a line like "return (DispAllErrors(henv, hdbc));" to indicate the failure
 * of the users request, so that the calling code can then process the error msg log
 */
{
    wxString odbcErrMsg;
    // local error inf                                   // added by TZ
    SWORD  my_cbErrorMsg = 0;                            // added by TZ
    wxChar my_errorMsg[SQL_MAX_MESSAGE_LENGTH];          // added by TZ
    SDWORD my_nativeError = 0;                           // added by TZ
    wxChar my_sqlState[20];                              // added by TZ

    while (SQLError(aHenv, aHdbc, aHstmt, (UCHAR FAR *) sqlState, &nativeError, (UCHAR FAR *) errorMsg, SQL_MAX_MESSAGE_LENGTH - 1, &cbErrorMsg) == SQL_SUCCESS)
    {
        my_cbErrorMsg = cbErrorMsg;                      // added by TZ
        wxStrcpy(my_errorMsg, errorMsg);                 // added by TZ 
        wxStrcpy(my_sqlState, sqlState);                 // added by TZ
        my_nativeError = nativeError;                    // added by TZ 
        
        odbcErrMsg.Printf(wxT("SQL State = %s\nNative Error Code = %li\nError Message = %s\n"), sqlState, nativeError, errorMsg);
        logError(odbcErrMsg, sqlState);
        if (!silent)
        {
#ifdef DBDEBUG_CONSOLE
            // When run in console mode, use standard out to display errors.
            cout << odbcErrMsg.c_str() << endl;
            cout << wxT("Press any key to continue...") << endl;
            getchar();
#endif

#ifdef __WXDEBUG__
            wxLogDebug(odbcErrMsg,wxT("ODBC DEBUG MESSAGE from DispAllErrors()"));
#endif
        }
    }
    cbErrorMsg = my_cbErrorMsg;                          // added by TZ
    wxStrcpy(errorMsg, my_errorMsg);                     // added by TZ
    wxStrcpy(sqlState, my_sqlState);                     // added by TZ
    nativeError = my_nativeError;                        // added by TZ
        

    return(FALSE);  // This function always returns FALSE.

} // wxDb::DispAllErrors()


 	  	 
