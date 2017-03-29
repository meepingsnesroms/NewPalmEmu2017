/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWUTILS_H__
#define __TWUTILS_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The following functions are compliant to ANSI and POSIX standard.
 * Applications can use them in place of calloc/malloc/realloc/strdup/free.
 */

void* Calloc(size_t count, size_t size);

void* Malloc(size_t size);

void* Realloc(void* ptr, size_t size);

char* Strdup(const char* str);

void  Free(void* ptr);

#ifdef __cplusplus
}
#endif

#endif /* __TAPWAVE_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
