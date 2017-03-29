/* Metrowerks Standard Library
 * Copyright � 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/07/22 22:02:31 $
 * $Revision: 1.1.2.3 $
 */

#ifndef _MSL_EXTRAS_MALLOC_H
#define _MSL_EXTRAS_MALLOC_H
      					
#include <ansi_parms.h>

#if (__dest_os == __win32_os || __dest_os == __wince_os)
	#include <extras_malloc_win32.h>
#endif

_MSL_BEGIN_EXTERN_C

	_MSL_IMP_EXP_C  int _MSL_CDECL heapmin(void) _MSL_CANT_THROW;

_MSL_END_EXTERN_C
	
#endif  /* _MSL_EXTRAS_MALLOC_H */

/* Change record:
 * cc  030620 Extras split to reduce namespace pollution
 * ejs 030721 Remove <unistd.h>, <null.h>, <size_t.h> includes
 * cc  030722 Moved underscored functions out of extras common headers/source.  
 *            They now live in the extras_xxxx_win32.h headers/source.
 */