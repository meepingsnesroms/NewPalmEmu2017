/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/13 15:23:43 $
 * $Revision: 1.21 $
 */

/*
 *	Routines
 *	--------
 *		rand
 *		srand
 *
 *	Note
 *	----
 *		This is exactly the function described in the standard, including the
 *		assumption that RAND_MAX == 32767.
 */

#include <stdlib.h>
#include <msl_thread_local_data.h>

#if !_MSL_THREADSAFE || (__dest_os != __win32_os && __dest_os != __wince_os)
	_MSL_TLS static unsigned long int random_next = 1;			/*- cc 011128 -*/
#endif

int _MSL_CDECL rand(void)
{
	_MSL_LOCALDATA(random_next) = _MSL_LOCALDATA(random_next) * 1103515245 + 12345;
	return((int)(_MSL_LOCALDATA(random_next) >> 16) & 0x7FFF);
}

void _MSL_CDECL srand(unsigned int seed)
{
	_MSL_LOCALDATA(random_next) = seed;	/*- cc 010531 -*/
}

/* Change record:
 * JFH 950607 First code release.
 * JFH 960429 Merged Win32 changes in.
 * KO  961219 Changed this file to use the thread local data structure instead
 *            of a global.
 * mf  980512 wince changes
 * mf  990309 use _MWMT instead of _MT for single threaded lib
 * cc  010531 Added _GetThreadLocalData's flag
 * cc  011128 Made __tls _MSL_TLS
 * cc  011203 Added _MSL_CDECL for new name mangling
 * JWW 020130 Changed _MWMT to _MSL_THREADSAFE for consistency's sake
 * BLC 020924 Fixed implicit conversion error when used on Palm OS (2-byte ints)
 * JWW 020604 Added _MSL_LOCALDATA macro to make multithread code easier to read
 * JWW 021031 Made thread local data available for Mach-O
 */