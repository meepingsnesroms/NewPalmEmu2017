/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/05/19 21:46:15 $
 * $Revision: 1.6 $
 */

#ifndef __ansi_prefix__
#define __ansi_prefix__

#include <os_enum.h>
#define __dest_os __arm_bare


#ifndef _MSL_FLT_EVAL_METHOD
	#define _MSL_FLT_EVAL_METHOD  0
#endif

#ifndef _MSL_C99
	#define _MSL_C99 1
#endif

#ifndef _MSL_LONGLONG
	#define _MSL_LONGLONG 1
#endif

#ifndef _MSL_WIDE_CHAR
	#define _MSL_WIDE_CHAR 1
#endif

#if _MSL_LONGLONG && !defined(__MSL_LONGLONG_SUPPORT__)
	/* The __MSL_LONGLONG_SUPPORT__ flag will disappear with MSL 10.  Use _MSL_LONGLONG instead. */
	#define __MSL_LONGLONG_SUPPORT__
#endif

#ifndef _MSL_C_LOCALE_ONLY
	#define _MSL_C_LOCALE_ONLY 1
#endif

#ifndef _MSL_USES_SUN_MATH_LIB
	#define _MSL_USES_SUN_MATH_LIB 1
#endif

#ifndef _MSL_USES_EXIT_PROCESS
	#define _MSL_USES_EXIT_PROCESS 1
#endif

#if defined(__cplusplus) && __embedded_cplusplus == 0
    #define _MSL_USING_NAMESPACE	
#endif

#define __ANSI_OVERLOAD__

#define _MSL_INTEGRAL_MATH

#ifdef __PALMOS_ARMLET__
	#undef _No_Time_OS_Support

	#undef	_No_Disk_File_OS_Support

	#define _MSL_OS_DIRECT_MALLOC

	#define _MSL_MALLOC_0_RETURNS_NON_NULL
#else
	#define _No_Time_OS_Support

	#define _No_Alloc_OS_Support

	#define _No_Disk_File_OS_Support
#endif

/* Define _MSL_CLASSIC_MALLOC if you wish to use that previous method. */
/* Please see alloc.c for more details */
/*#define _MSL_CLASSIC_MALLOC*/

/* The new allocation method has some optional configuration.  Please */
/* see alloc.c for more details.  By default, the fastest allocation */
/* method has been chosen.  In particular, you may want to define */
/* _MSL_NO_FIX_MALLOC_POOLS if your heap is smaller than 64k. */
#ifndef _MSL_CLASSIC_MALLOC
	/* define _MSL_NO_MALLOC_DESIGN_2 if you want lower overhead but */
	/* somewhat slower allocation. */
	/* #define _MSL_NO_MALLOC_DESIGN_2 */
	/* define _MSL_NO_FIX_MALLOC_POOLS if your heap will be less than 64k */
	/* #define _MSL_NO_FIX_MALLOC_POOLS */
#endif

#define NEWMODE NEWMODE_MALLOC		/* always use malloc for new */

#endif /*	__ansi_prefix__	  */

/*#pragma once on*/
/* Switching this pragma on, can improve compilation speed but it may cause problems with the
   use of assert.h, which generally depends upon being actually included more than once during
   compilation. */


/* Change record:
 * cc  021022 Turned on the _MSL_C_LOCALE_ONLY flag
 * JWW 030224 Changed __MSL_LONGLONG_SUPPORT__ flag into the new more configurable _MSL_LONGLONG
 */
