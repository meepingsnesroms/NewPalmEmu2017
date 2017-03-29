/* Metrowerks ARM Runtime Support Library 
 * Copyright © 1995-2003 Metrowerks Corporation. All rights reserved. 
 * 
 * $Date 
 * $Revision
 */


#include <stdlib.h>

extern void *__vla_alloc(size_t size);
extern void __vla_free(void *ptr);


/*
 *	__vla_alloc		-	variable length array (VLA) allocation function,
 *						allocate "size" bytes buffer and return pointer to it.
 *
 */

void *__vla_alloc(size_t size)
{
	return malloc(size);
}


/*
 *	__vla_free		-	variable length array (VLA) deallocation function,
 *						free previously allocated buffer.
 *
 */

void __vla_free(void *ptr)
{
	free(ptr);
}
