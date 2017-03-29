/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/13 15:23:23 $
 * $Revision: 1.20 $
 */

#ifndef _MSL_MISC_IO_H
#define _MSL_MISC_IO_H

#include <ansi_parms.h>

_MSL_BEGIN_EXTERN_C

	void _MSL_CDECL	__stdio_atexit(void) _MSL_CANT_THROW;

_MSL_END_EXTERN_C

#endif /* _MSL_MISC_IO_H */

/* Change record:
 * hh  971206 expanded _extern macro
 * cc  010405 removed pragma options align native and reset	
 * cc  010409 updated defines to JWW new namespace macros
 * cc  011212 added msl cdecl
 * hh  020603 Added no throw spec to functions
 */