/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/07/24 20:15:11 $
 * $Revision: 1.5.2.1 $
 */

#include <stdio.h>  
#include <stdio.posix.h>  /* need this for fileno */

/*
 *	int fileno(FILE *stream)
 *
 *		Returns the file number associated with a stream.
 */
 
int _MSL_CDECL fileno(FILE *stream) _MSL_CANT_THROW
{
	return (stream->handle);
}

/* Change record:
 * cc  000404 Removed io.h and added stdio.h and unix.h 
 * cc  000517 Cleanup of umask return type 
 * cc  000517 Changed #include to cstdio 
 * cc  010622 Removed _ on umask and renamed posixparams to _MSL_POSIX_PARAMS
 * JWW 010927 Moved fileno to new stdio_posix.c file
 * cc  011203 Added _MSL_CDECL for new name mangling 
 * cc  020221 Added #include
 */