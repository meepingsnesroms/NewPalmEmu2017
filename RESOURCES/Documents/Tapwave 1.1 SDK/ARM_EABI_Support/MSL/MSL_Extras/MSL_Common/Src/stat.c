/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/07/24 20:15:10 $
 * $Revision: 1.4.2.1 $
 */

#include <stat.h> 					

_MSL_POSIX_PARAMS __new_umask = 0;

/*  	if !_MSL_POSIX _MSL_POSIX_PARAMS is an int else it is of type mode_t
 *
 *		_MSL_POSIX_PARAMS _umask( _MSL_POSIX_PARAMS __pmode )
 *
 *		Sets the file permission mask so that all future
 *      files will be created to the mode specified by __pmode 
 */

_MSL_POSIX_PARAMS _MSL_CDECL umask(_MSL_POSIX_PARAMS __pmode) _MSL_CANT_THROW
{
	_MSL_POSIX_PARAMS __oldmask = __new_umask;
	
	__new_umask = __pmode;
	
	return __oldmask;
}

/* Change record:
 * cc  000404 Removed io.h and added stdio.h and unix.h 
 * cc  000517 Cleanup of umask return type 
 * cc  000517 Changed #include to cstdio 
 * cc  010622 Removed _ on umask and renamed posixparams to _MSL_POSIX_PARAMS
 * JWW 010927 Renamed from unix.c to stat.c
 * cc  011203 Added _MSL_CDECL for new name mangling 
 */