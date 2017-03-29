/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/07/22 22:00:43 $
 * $Revision: 1.1.2.3 $
 */

#ifndef _MSL_EXTRAS_TIME_H
#define _MSL_EXTRAS_TIME_H
      					
#include <ansi_parms.h>
#include <size_t.h>
#include <null.h>

#if (__dest_os == __win32_os || __dest_os == __wince_os)
	#include <extras_time_win32.h>
#endif

_MSL_BEGIN_EXTERN_C	

#ifndef _No_Time_OS_Support	
	_MSL_IMP_EXP_C  char * _MSL_CDECL strdate(char *str) _MSL_CANT_THROW;
#endif	

_MSL_END_EXTERN_C
	
#endif  /* _MSL_EXTRAS_TIME_H */

/* Change record:
 * cc  030620 Extras split to reduce namespace pollution
 * ejs 030721 Remove <unistd.h> include
 * cc  030722 Moved underscored functions out of extras common headers/source.  
 *            They now live in the extras_xxxx_win32.h headers/source.
 */