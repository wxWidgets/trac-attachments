#if __cplusplus >= 201103L 
// C11 std::chrono timers are available.
//	Note: Visual Studio 2013 incorrectly defines __cplusplus as an old version (C99);
//	but it is ok since we have a Windows implementation below that works.
#include <chrono>				

#elif _WIN32
#include <windows.h>			// for GetSystemTimeAsFileTime
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
#endif

#include "timeHiRes.hpp"			

/////////////////////////////////////////////////////
//
// Return high resolution wall clock time (seconds)
//	
//////////////////////////////////////////////////////
double GetTimeHiRes(void)
{
	#if __cplusplus >= 201103L 
	// Use the standard C11 method to return the time in seconds since Jan 1 1970 (the Unix Epoch Time)
	auto timenow = std::chrono::high_resolution_clock::now();
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timenow.time_since_epoch()).count();
	double seconds = (double)(milliseconds) / 1000.;
	return seconds;

	#elif _WIN32
	// Define a structure to receive the current Windows filetime
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	// The GetSystemTimeAsFileTime returns the number of 100 nanosecond 
	// intervals since Jan 1, 1601 in a structure. Copy the high bits to 
	// the 64 bit tmpres, shift it left by 32 then or in the low 32 bits.
	unsigned __int64 tmpres = ft.dwHighDateTime;
	tmpres <<= 32;
	tmpres |= ft.dwLowDateTime;

	// Convert to microseconds by dividing by 10
	tmpres /= 10;

	// The Unix epoch starts on Jan 1 1970.  Need to subtract the difference 
	// in seconds from Jan 1 1601.
	tmpres -= DELTA_EPOCH_IN_MICROSECS;

	// Finally change microseconds to seconds and place in the seconds value. 
	// The modulus picks up the microseconds.
	const double nano2seconds = 1.0 / 1000000.0;
	return((double)tmpres * nano2seconds);
	
	#else
	return 0;
    #endif
}
