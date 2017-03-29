/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __ARPA_INET_H__
#define __ARPA_INET_H__

#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

in_addr_t inet_addr(const char * name);
int       inet_aton(const char * name, struct in_addr * addr);
char*     inet_ntoa(struct in_addr addr);

#ifdef __cplusplus
};
#endif

#endif /* __ARPA_INET_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
