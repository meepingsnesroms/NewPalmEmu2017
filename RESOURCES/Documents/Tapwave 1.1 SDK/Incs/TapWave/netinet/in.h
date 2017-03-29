/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __NETINET_IN_H__
#define __NETINET_IN_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IPPROTO_IP      0       /* dummy for IP */
#define IPPROTO_ICMP    1       /* control message protocol */
#define IPPROTO_IGMP    2       /* group control protocol */
#define IPPROTO_GGP     3       /* gateway^2 (deprecated) */
#define IPPROTO_TCP     6       /* tcp */
#define IPPROTO_EGP     8       /* exterior gateway protocol */
#define IPPROTO_PUP     12      /* pup */
#define IPPROTO_UDP     17      /* user datagram protocol */
#define IPPROTO_IDP     22      /* xns idp */
#define IPPROTO_HELLO   63      /* "hello" routing protocol */
#define IPPROTO_ND      77      /* UNOFFICIAL net disk proto */

#define IPPROTO_RAW     255     /* raw IP packet */
#define IPPROTO_MAX     256

#define INADDR_ANY      0

#define IPPORT_USERRESERVED     5000

#if defined(__MC68K__) || defined(__m68k)

#define ntohl(x)    (x)
#define ntohs(x)    (x)
#define htonl(x)    (x)
#define htons(x)    (x)

#else

#define ntohl(x)    ((((x) >> 24) & 0x00FF) | (((x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8) | (((x) & 0x00FF) << 24))
#define ntohs(x)    ((((x) >> 8) & 0xFF) | (((x) & 0xFF) << 8))
#define htonl(x)    ((((x) >> 24) & 0x00FF) | (((x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8) | (((x) & 0x00FF) << 24))
#define htons(x)    ((((x) >> 8) & 0xFF) | (((x) & 0xFF) << 8))

#endif

typedef uint32_t in_addr_t;

struct in_addr
{
    in_addr_t s_addr;
};

struct sockaddr_in
{
    int16_t         sin_family;     /* address family */
    uint16_t        sin_port;       /* port number */
    struct in_addr  sin_addr;       /* internet address */
    int8_t          sin_zero[8];    /* zero padding */
};

#ifdef __cplusplus
}
#endif

#endif /* __NETINET_IN_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
