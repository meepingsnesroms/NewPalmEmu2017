/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __SYS_TIME_H__
#define __SYS_TIME_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct timeval {
  int32_t tv_sec;
  int32_t tv_usec;
};


struct timezone {
  int32_t tz_minuteswest;
  int32_t tz_dsttime;
};

int gettimeofday(struct timeval *tv, struct timezone *tz);
int settimeofday(const struct timeval *tv, const struct timezone *tz);

#ifdef __cplusplus
}
#endif

#endif /* __SYS_TIME_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
