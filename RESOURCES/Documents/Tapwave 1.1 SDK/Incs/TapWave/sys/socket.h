/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __SYS_SOCKET_H__
#define __SYS_SOCKET_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AF_INET         2
#define PF_INET         AF_INET

#define SOCK_STREAM     1       /* stream socket */
#define SOCK_DGRAM      2       /* datagram socket */
#define SOCK_RAW        3       /* raw-protocol interface */
#define SOCK_RDM        4       /* reliable message */

struct sockaddr {
    int16_t sa_family;      /* address family, AF_xxx   */
    uint8_t sa_data[14];    /* 14 bytes of protocol address */
};

typedef int32_t socklen_t;

int accept(int socket, struct sockaddr* addr, socklen_t addrlen);
int bind(int socket, struct sockaddr* addr, socklen_t addrlen);
int closesocket(int socket);
int connect(int socket, struct sockaddr* addr, socklen_t addrlen);
int getpeername(int socket, struct sockaddr* name, socklen_t* namelen);
int getsockname(int socket, struct sockaddr* name, socklen_t* namelen);
int getsockopt(int socket, int level, int opt, void* optval, socklen_t* optlen);
int ioctl(int fildes, int request, ...);
int listen(int socket, int backlog);
int recv(int socket, void* buffer, int buflen, int flags);
int recvfrom(int socket, void* buffer, int buflen, int flags, struct sockaddr* from, socklen_t* fromlen);
int send(int socket, void* buf, int buflen, int flags);
int sendto(int socket, void* buf, int buflen, int flags, struct sockaddr* to, socklen_t tolen);
int setsockopt(int socket, int level, int opt, void* optval, socklen_t optlen);
int shutdown(int socket, int direction);
int socket(int domain, int type, int protocol);

#ifdef __cplusplus
}
#endif

#endif /* __SYS_SOCKET_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
