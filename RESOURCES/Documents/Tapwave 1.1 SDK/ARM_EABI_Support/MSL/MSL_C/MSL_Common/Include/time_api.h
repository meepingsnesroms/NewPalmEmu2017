/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/02/21 17:37:09 $
 * $Revision: 1.7 $
 */

#ifndef _MSL_TIME_API_H
#define	_MSL_TIME_API_H

#if (__dest_os == __win32_os)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <ansi_parms.h>
#include <ctime>

_MSL_BEGIN_EXTERN_C

	#ifndef _No_Time_OS_Support
		clock_t	__get_clock(void);
		time_t	__get_time(void);
		int		__to_gm_time(time_t * time);
		int		__isdst(void);
		int     __MSL_ISO8601Week(const struct tm* tmptr, int * WYear);		/*- mm 021219 -*/
		time_t  __MSL_ISO8601NewYear(int year);								/*- mm 021219 -*/
		char *  __MSL_extract_name(char * source, int position);			/*- mm 021219 -*/

		#if (__dest_os == __win32_os)
			time_t  __systemtime_to_time_t(SYSTEMTIME * time);
		#endif
	#endif
	
	char * 	__MSL_extract_name(char *, int);	
	time_t 	__MSL_ISO8601NewYear(int);
	int 	__MSL_ISO8601Week(const struct tm*, int *);

_MSL_END_EXTERN_C

#endif /* _MSL_TIME_API_H */

/* Change record:
 * JWW 010905 New file to define the MSL API for the clock and time implementation
 * mm  021219 Added prototypes for __MSL_ISO8601Week(), __MSL_ISO8601NewYear(), and __MSL_extract_name(  used in strftime and wcsftime.
 */