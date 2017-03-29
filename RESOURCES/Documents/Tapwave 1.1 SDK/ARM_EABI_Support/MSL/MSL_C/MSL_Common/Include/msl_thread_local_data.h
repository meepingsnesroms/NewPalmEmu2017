/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/13 17:09:25 $
 * $Revision: 1.3 $
 */

#ifndef _MSL_THREAD_LOCAL_DATA_H
#define _MSL_THREAD_LOCAL_DATA_H

#include <ansi_parms.h>

#if _MSL_THREADSAFE
	#if __dest_os == __mac_os_x
		#include <thread_local_data_mac.h>
	#elif (__dest_os == __win32_os) || (__dest_os == __wince_os)
		#include <ThreadLocalData.h>
	#endif
#endif /* _MSL_THREADSAFE */

#endif /* _MSL_THREAD_LOCAL_DATA_H */

/* Change record:
 * JWW 021031 Created new "spooooky" file for handling platform independent thread local data
 */