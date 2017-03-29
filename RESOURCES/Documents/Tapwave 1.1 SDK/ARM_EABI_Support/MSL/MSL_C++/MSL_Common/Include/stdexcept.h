/* Metrowerks Standard Library
 * Copyright � 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/14 21:40:13 $
 * $Revision: 1.16 $
 */

// stdexcept.h

#ifndef _STDEXCEPT_H
#define _STDEXCEPT_H

#include <stdexcept>

#ifndef _MSL_NO_CPP_NAMESPACE
	using std::logic_error;
	using std::domain_error;
	using std::invalid_argument;
	using std::length_error;
	using std::out_of_range;
	using std::runtime_error;
	using std::range_error;
	using std::overflow_error;
	using std::underflow_error;
#endif

#endif  // _STDEXCEPT_H

// hh 971206  File created.
// hh 990120 changed name of MSIPL flags
// hh 991113 modified using policy
