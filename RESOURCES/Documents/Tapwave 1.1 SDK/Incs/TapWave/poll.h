/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __POLL_H__
#define __POLL_H__

#ifdef __cplusplus
extern "C" {
#endif

#define	POLLIN		0x001
#define	POLLPRI		0x002
#define	POLLOUT		0x004
#define	POLLERR		0x008

struct pollfd {
	int	    fd;
	short	events;
	short	revents;
};

int poll(struct pollfd *fds, int nfds, int timeout);

#ifdef __cplusplus
}
#endif

#endif /* __POLL_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
