/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __STDINT_H__
#define __STDINT_H__

typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef signed long int32_t;
typedef unsigned long uint32_t;

#ifdef _MSC_VER
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
#endif

typedef signed long intptr_t;
typedef unsigned long uintptr_t;

#endif /* __STDINT_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
