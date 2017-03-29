/* Metrowerks Standard Library
 * Copyright � 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/14 21:40:34 $
 * $Revision: 1.8 $
 */

// stringfwd.h

// WARNING
//
// stringfwd.h is a non-standard, non-portable header.
//
// WARNING

#ifndef _STRINGFWD_H
#define _STRINGFWD_H

#include <stringfwd>

#ifndef _MSL_NO_CPP_NAMESPACE

	using std::allocator;
	using std::char_traits;
	using std::basic_string;
	using std::string;
#ifndef _MSL_NO_WCHART_CPP_SUPPORT
	using std::wstring;
#endif

#endif

#endif // _STRINGFWD_H

// hh 991114 Created
