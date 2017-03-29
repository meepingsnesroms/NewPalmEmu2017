/* Metrowerks Standard Library
 * Copyright � 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/01/13 15:25:41 $
 * $Revision: 1.3 $
 */

#ifndef	_MSL_UNIX_H
#define	_MSL_UNIX_H

#include <ansi_parms.h>     							/*- hh 971206 -*/
#include <stat.h>
#include <utime.h>

#if (__dest_os == __mac_os)
	#include <unix.mac.h>
#endif

#endif /* _MSL_UNIX_H */

/* Change record:
 * mm  960927 Inserted setting of __dest_os to __mac_os when not otherwise set.
 * hh  971206 added #include <ansi_parms.h>
 * cc  000517 Cleaned _umask and #include of header files
 * cc  000817 fixed posixparams to be set to mode_t only when on mac or win
 *            and the POSIX flag is on. Under all other cases posixparams is
 *            an int (mode_t is set in stat.h according to OS).
 * JWW 000928 balanced align directives (align=native needs align=reset)
 * cc  010405 removed pragma options align native and reset
 * cc  010409 updated defines to JWW new namespace macros
 * JWW 010618 Use cname headers exclusively to prevent namespace pollution in C++
 * JWW 010927 Moved chmod and umask into stat.h header from previously unstandard unix.h header
 */