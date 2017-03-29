/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/05/02 18:55:50 $
 * $Revision: 1.22 $
 */

#ifndef _MSL_TIME_H
#define _MSL_TIME_H

#include <ansi_parms.h>

#if !_MSL_USING_MW_C_HEADERS
	#error You must have the non-MSL C header file access path before the MSL access path
#else

#include <ctime>

#if defined(__cplusplus) && defined(_MSL_USING_NAMESPACE)	
	using std::size_t;
	
	using std::clock_t;
	using std::time_t;
	using std::tm;
	
	#ifndef _No_Time_OS_Support
		using std::clock;
		using std::gmtime;
		using std::time;
	#endif
	
	#ifndef _No_Floating_Point
		using std::difftime;
	#endif
	
	using std::asctime;
	using std::ctime;
	using std::localtime;
	using std::mktime;
	using std::strftime;
#endif

#endif /* _MSL_USING_MW_C_HEADERS */

#endif /* _MSL_TIME_H */

/* Change record:
 * hh  971206 Created.
 * hh  991112 Fixed using bug.
 * JWW 001208 Added case for targeting Mach-O
 * JWW 011027 Use _MSL_USING_MW_C_HEADERS as generic header test instead of specific Mach-O test
 */