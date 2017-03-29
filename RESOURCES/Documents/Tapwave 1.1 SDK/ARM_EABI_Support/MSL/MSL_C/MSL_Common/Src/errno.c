/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/13 15:23:40 $
 * $Revision: 1.17 $
 */

#include <errno.h>

#if !(_MSL_THREADSAFE && (__dest_os == __win32_os || __dest_os == __wince_os))
	#if !__MACH__
		_MSL_TLS int errno;											/*- cc 011128 -*/
	#endif
	
	#if ((__dest_os == __mac_os) || (__dest_os == __mac_os_x))      /*- mm 010412 -*/
		_MSL_TLS short __MacOSErrNo;								/*- mm 010412 -*/	/*- cc 011128 -*/
	#endif															/*- mm 010412 -*/
#endif

/* Change record:
 * JFH 950612 First code release.
 * CVT 960415 Add TLS support for Win32
 * mf  980512 wince changes
 * mm  010412 Added global for storing MacOS OSErr values
 * JWW 011027 Added case for Mach-O to use a single errno storage location from the BSD C
 * cc  011128 Made __tls _MSL_TLS
 * JWW 020130 Changed _MWMT to _MSL_THREADSAFE for consistency's sake
 */