/* Metrowerks ARM Runtime Support Library 
 * Copyright � 1995-2003 Metrowerks Corporation. All rights reserved. 
 * 
 * $Date: 2002/06/20 15:32:51 $ 
 * $Revision: 1.3 $ 
 */ 


/*
 *	rt_div0.c	-	handler for divide-by-zero
 *
 *	This routine is a hack to satisfy the references from the
 *	ADS versions of __rt_divs and __rt_divu (and __ll_divu).
 *
 *	I don't know what we're supposed to do here--ADS raises an
 *	exception--so I'll just wait around doing nothin'
 *
 */

void __rt_div0(void);
void __rt_div0(void)
{
	loop: goto loop;
}
