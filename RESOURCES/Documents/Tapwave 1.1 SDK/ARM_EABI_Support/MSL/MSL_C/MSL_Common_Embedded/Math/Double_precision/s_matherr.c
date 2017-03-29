
#ifndef _No_Floating_Point  
/* @(#)s_matherr.c 1.2 95/01/04 */
/* $Id: s_matherr.c,v 1.3 2002/02/11 22:54:17 ceciliar Exp $ */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

#include "fdlibm.h"

#ifdef __STDC__
	_INT32 matherr(struct exception *x)  /*- cc 020130 -*/
#else
	_INT32 matherr(x)					/*- cc 020130 -*/
	struct exception *x;
#endif
{
	_INT32 n=0;							/*- cc 020130 -*/
	if(x->arg1!=x->arg1) return 0;
	return n;
}
#endif /* _No_Floating_Point  */
