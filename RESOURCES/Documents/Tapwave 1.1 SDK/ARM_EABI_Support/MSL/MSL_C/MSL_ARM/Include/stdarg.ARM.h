/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/07/03 20:35:56 $
 * $Revision: 1.3.2.1 $
 */

#ifndef _MSL_STDARG_ARM_H
#define _MSL_STDARG_ARM_H

_MSL_BEGIN_EXTERN_C

	/*	NB: It is safe to ignore endian in these macros. The standard requires that scalar	*/
	/*	types smaller than 'int' (including enum types) be extracted via va_arg(ap,int).	*/
	
	#define	__fourbytealign(n)		((((unsigned long) (n)) + 3U) & ~3U)
   	#define __va_start(parm)		((__std(va_list)) ((char*) ((unsigned long)(&parm) & ~3U) + __fourbytealign(sizeof(parm))))
   	
	#define va_start(ap, parm)		((ap) = __va_start(parm))
	#define va_arg(ap, type)		(*(type *) ((ap += __fourbytealign(sizeof(type))) - __fourbytealign(sizeof(type))))
	#define va_end(ap)				((void) 0)
	#define va_copy(dest, src)		dest = src

_MSL_END_EXTERN_C

#endif /* _MSL_STDARG_ARM_H */

/* Change record:
 * JMM 020423 New file to make stdarg information platform independent
 */