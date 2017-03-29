/* Metrowerks Standard Library
 * Copyright � 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/13 15:23:23 $
 * $Revision: 1.21 $
 */
 
#ifndef _MSL_LOCALE_H
#define _MSL_LOCALE_H

#include <ansi_parms.h>

#if !_MSL_USING_MW_C_HEADERS
	#error You must have the non-MSL C header file access path before the MSL access path
#else

#include <clocale>

#if defined(__cplusplus) && defined(_MSL_USING_NAMESPACE)
	using std::lconv;
	using std::localeconv;
	using std::setlocale;
#endif

#endif /* _MSL_USING_MW_C_HEADERS */

#endif /* _MSL_LOCALE_H */

/* Change record: 
 * hh  971206 Created.
 * hh  991112 Fixed using bug.
 * JWW 001208 Added case for targeting Mach-O
 * JWW 011027 Use _MSL_USING_MW_C_HEADERS as generic header test instead of specific Mach-O test
 */