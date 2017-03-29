/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/13 15:25:45 $
 * $Revision: 1.2 $
 */

#ifndef	_MSL_TIMEB_H
#define	_MSL_TIMEB_H

#include <ansi_parms.h>
#include <stat.h>

_MSL_BEGIN_EXTERN_C
	
#pragma options align=native
		
struct timeb
{
	__std(time_t)		time;			/* Seconds in the current time					*/
	unsigned short		millitm;		/* Milliseconds in the current time				*/
	short				timezone;		/* The difference,in minutes, between local time 
										   and Greenwich Mean time						*/
	short				dstflag;		/* 1 if Daylight Savings time is in effect 		*/
};
		
#pragma options align=reset

#if (__dest_os == __win32_os || __dest_os == __wince_os)
	#include <timeb.win32.h>
#endif
		
	
_MSL_END_EXTERN_C

#endif /* _MSL_TIMEB_H */

/* Change record:
 * cc  020711 Added timeb struct
 */