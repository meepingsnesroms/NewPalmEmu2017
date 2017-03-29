/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/14 21:36:58 $
 * $Revision: 1.17 $
 */

// list.h               // hh 971207 Changed filename from list to list.h

#if __PALMOS_TRAPS__
#error The wrong List.h is being included.  You should set your access paths so that "{Compiler}/Palm OS Support" appears before any MSL access paths.
#endif

#ifndef _LIST_H             // hh 971207 added standard include guards
#define _LIST_H

#include <list>

#ifndef _MSL_NO_CPP_NAMESPACE           // hh 971207 Added backward compatibility
	using std::list;
#endif

#endif  // _LIST_H

// hh 971207 Changed filename from list to list.h
// hh 971207 added standard include guards
// hh 971207 Added backward compatibility
// hh 990120 changed name of MSIPL flags
// hh 991113 modified using policy
