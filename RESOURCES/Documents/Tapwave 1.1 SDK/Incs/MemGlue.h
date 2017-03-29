/******************************************************************************
 *
 * Copyright (c) 2001-2002 Palmsource, Inc. All rights reserved.
 *
 * File: MemGlue.h
 *
 * Release: Palm OS 5 SDK (68K) R2.
 *
 * Description:
 *    Glue providing compatibility for applications that wish to make calls to
 *    some recent list functions, but which might actually be running on a
 *    system which does not support these newer calls.
 *
 * History:
 *		2002-10-29	oge	Created.
 *
 *****************************************************************************/

#ifndef __MEMGLUE_H__
#define __MEMGLUE_H__

#ifdef __cplusplus
extern "C" {
#endif

extern MemPtr MemGluePtrNew(UInt32 size);

#ifdef __cplusplus
}
#endif

#endif
