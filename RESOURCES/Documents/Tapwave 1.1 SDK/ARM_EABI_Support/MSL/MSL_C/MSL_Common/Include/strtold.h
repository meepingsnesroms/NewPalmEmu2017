/* Metrowerks Standard Library
 * Copyright � 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/13 15:23:26 $
 * $Revision: 1.28 $
 */

#ifndef _MSL_STRTOLD_H
#define _MSL_STRTOLD_H

#include <ansi_parms.h>
#include <cstdio>

_MSL_BEGIN_EXTERN_C

	extern long double _MSL_CDECL __strtold(int max_width,
								 int (_MSL_CDECL *ReadProc)(void *, int, int), 	/*- mm 990325 -*/ /*- cc 020109 -*/
								 void * ReadProcArg,							/*- mm 990325 -*/
								 int	* chars_scanned,
								 int	* overflow) _MSL_CANT_THROW;

_MSL_END_EXTERN_C

#endif /* _MSL_STRTOLD_H */

/* Change record:
 * mm  970905 added include of stdio.h to allow this header to be included first.
 * hh  971206 namespace support
 * hh  990121 Fixed __std
 * mm  990325 Made to work with input functions passed by pointers
 * mf  990420 had to provide k6 wrap internal function __strtold as well
 * cc  010405 removed pragma options align native and reset
 * cc  010409 updated defines to JWW new namespace macros
 * JWW 010618 Use cname headers exclusively to prevent namespace pollution in C++
 * cc  020109 Added _MSL_CDECL
 * hh  020603 Added no throw spec to functions
 */