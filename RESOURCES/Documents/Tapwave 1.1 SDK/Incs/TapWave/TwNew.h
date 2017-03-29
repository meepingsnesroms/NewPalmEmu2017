/* Copyright (c) 2002-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWNEW_H__
#define __TWNEW_H__

#ifndef USE_TAPWAVE_NEW
#define USE_TAPWAVE_NEW         1
#endif

#if defined(__cplusplus) && USE_TAPWAVE_NEW

/*
 * We have to define operator new and delete that call into regular
 * PalmOS Memory Manager APIs. Otherwise, C++ compilers will call into
 * C runtime library functions, which are not supported under PalmOS.
 */

#include <new.h>

/* new */
inline void* operator new(size_t size) {
    return MemPtrNew(size);
}

/* delete */
inline void operator delete(void* ptr) throw() {
    if (ptr) MemPtrFree(ptr);
}

/* array new */
inline void* operator new[](size_t size) {
    return MemPtrNew(size);
}

/* array delete */
inline void operator delete[](void* ptr) throw() {
    if (ptr) MemPtrFree(ptr);
}

#endif /* #if defined(__cplusplus) && USE_TAPWAVE_NEW */

#endif /* __TWNEW_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
