/***************************************************************************
                          wxMemoryMappedFile.h  -  description
                             -------------------
    copyright           : (C) 2006 by Blake Madden
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the BSD License.                                *
 *                                                                         *
 ***************************************************************************/

#ifndef __MEMMAPPEDFILE_H__
#define __MEMMAPPEDFILE_H__

#ifdef __WXMSW__
	#include <windows.h>
#endif
#include <exception>

///exceptions that can be thrown when mapping a file
class wxMemoryMappedFileException : public std::exception {};
class wxMemoryMappedFileEmptyException : public std::exception {};
class wxMemoryMappedFileShareViolationException : public std::exception {};
class wxMemoryMappedInvalidFileType : public std::exception {};

class wxMemoryMappedFile
	{
public:
	wxMemoryMappedFile() :
		m_hFile(INVALID_HANDLE_VALUE),
		m_hsection(NULL),
		m_data(NULL),
		m_fileLength(0),
		m_open(false)
		{}
	wxMemoryMappedFile(const wxString& filePath) :
		m_hFile(INVALID_HANDLE_VALUE),
		m_hsection(INVALID_HANDLE_VALUE),
		m_data(NULL),
		m_fileLength(0),
		m_open(false)
		{
		MapFile(filePath);
		}
	bool IsOpen() const { return m_open; }
	bool MapFile(const wxString& filePath, bool readOnly = true)
		{
		if (m_open)
			{ return false; }
		m_open = true;
		m_filePath = filePath;
		unsigned long dwDesiredFileAccess = GENERIC_READ;
		if (!readOnly)
			dwDesiredFileAccess |= GENERIC_WRITE;
		//get the handle to the file...
		m_hFile = ::CreateFile(filePath.c_str(), dwDesiredFileAccess, FILE_SHARE_READ,
                     0, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN|SECURITY_SQOS_PRESENT|SECURITY_IDENTIFICATION, 0);
		if (INVALID_HANDLE_VALUE == m_hFile)
			{
			Reset();
			if (ERROR_SHARING_VIOLATION == ::GetLastError() )
				{
				throw wxMemoryMappedFileShareViolationException();
				}
			else
				{
				throw wxMemoryMappedFileException();
				}
			}
        //this will fail if the file path was really a drive or printer (don't want to map that!)
        else if (FILE_TYPE_DISK != ::GetFileType(m_hFile))
            {
            ::CloseHandle(m_hFile);
            Reset();
            throw wxMemoryMappedInvalidFileType();
            }

        m_fileLength = GetFileSize64(m_hFile);
        if (m_fileLength == INVALID_FILE_SIZE)
            { m_fileLength = ::SetFilePointer(m_hFile, 0, NULL, FILE_END); }
		::SetFilePointer(m_hFile, 0, NULL, FILE_BEGIN);
		if (m_fileLength == 0)
			{
			::CloseHandle(m_hFile);
			Reset();
			throw wxMemoryMappedFileEmptyException();
			}
		//now, we create a file mapping object for that file
		m_hsection = ::CreateFileMapping(m_hFile, 0, (readOnly) ? PAGE_READONLY : PAGE_READWRITE, 0, 0, 0);
		if (NULL == m_hsection)
			{
			::CloseHandle(m_hFile);
			Reset();
			throw wxMemoryMappedFileException();
			}
		m_data = (char*)::MapViewOfFile(m_hsection, (readOnly) ? FILE_MAP_READ : FILE_MAP_WRITE, 0, 0, 0);
		return true;
		}
    ///returns the raw byte stream of the file
	char* GetText()
		{ return m_data; }
    ///returns a 64-bit length of the file. Just use the Low part of the return value of non-huge files
	wxULongLong GetFileLength() const
		{ return m_fileLength; }
    ///returns the path of the file currently mapped
	wxString GetFilePath() const
		{ return m_filePath; }
	~wxMemoryMappedFile()
		{ UnmapFile(); }
	///closes the handles and mappings
	void UnmapFile()
		{
		if (INVALID_HANDLE_VALUE != m_hFile)
			{
			::CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
			}
		if (m_hsection)
			{
			::CloseHandle(m_hsection);
			m_hsection = NULL;
			}
		if (m_data)
			{
			::FlushViewOfFile(m_data, 0);
			::UnmapViewOfFile(m_data);
			m_data = NULL;
			}
		m_open = false;
		m_fileLength = 0;
		m_filePath = wxEmptyString;
		}

    //***********************************************
    static wxULongLong GetFileSize64(const HANDLE hFile)
        {
	    if (hFile == INVALID_HANDLE_VALUE)
            { return INVALID_FILE_SIZE; }
        //this will fail if the file path was really a drive or printer
        if (FILE_TYPE_DISK != ::GetFileType(hFile))
            { return INVALID_FILE_SIZE; }

	    try
	        {
		    unsigned long Lo = 0, Hi = 0;
            Lo = ::GetFileSize(hFile, &Hi);

            if (Lo == INVALID_FILE_SIZE)
		        { return wxULongLong(INVALID_FILE_SIZE); }
		    else
		        {
			    return wxULongLong(Hi, Lo);
		        }
	        }
	    catch(...)
	        { return wxULongLong(INVALID_FILE_SIZE); }
        }
private:
	void Reset()
		{
		m_hFile = INVALID_HANDLE_VALUE;
		m_hsection = NULL;
		m_data = NULL;
		m_fileLength = 0;
		m_open = false;
		m_filePath = wxEmptyString;
		}
	HANDLE m_hFile;
	HANDLE m_hsection;
	char* m_data;
	wxULongLong m_fileLength;
	wxString m_filePath;
	bool m_open;
	};

#endif //__MEMMAPPEDFILE_H__

 	  	 
