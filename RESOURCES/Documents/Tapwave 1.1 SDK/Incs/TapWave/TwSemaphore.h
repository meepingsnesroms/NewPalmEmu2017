/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWSEMAPHORE_H__
#define __TWSEMAPHORE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef Int32 TwSemaphoreType;

Err TwSemaphoreCreate(TwSemaphoreType* sema, Int32 initValue);

Err TwSemaphoreDelete(TwSemaphoreType sema);

/*
 * The timeout value has the following semantics
 *
 *  -1  wait forever
 *  0   non blocking
 *  >0  wait for specified milli seconds
 */
Err TwSemaphoreAcquire(TwSemaphoreType sema, Int32 timeout);

Err TwSemaphoreRelease(TwSemaphoreType sema);

/*
 * Return current thread id.
 */
Int32 TwThreadCurrent(void);

#ifdef __cplusplus
}
#endif

#endif /* __TWSEMAPHORE_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
