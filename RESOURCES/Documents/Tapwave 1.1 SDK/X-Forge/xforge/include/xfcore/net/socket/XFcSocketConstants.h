/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Redefines supported socket flags for every supported platforms
 *
 * $Id: XFcSocketConstants.h,v 1.14.2.1 2003/10/17 07:54:51 jetro Exp $
 * $Date: 2003/10/17 07:54:51 $
 * $Revision: 1.14.2.1 $
 */

#ifndef XFCNETDEFINES_H_INCLUDED
#define XFCNETDEFINES_H_INCLUDED


//!
enum XFCSOCKETFLAGS
{
    //! socket type
    XFCNET_SOCKSTREAM  = 1,     // SOCK_STREAM
    XFCNET_SOCKDGRAM = 2,       // SOCK_DGRAM
    XFCNET_AFINET = 3,          // AF_INET
    XFCNET_AFBT = 4,            // Bluetooth

    //! ioctl commands
    //! the nonblocking mode of socket
    XFCNET_FIONBIO = 5,         // FIONBIO
    //! Use to determine the amount of data pending in the network's input buffer that can be read from socket
    XFCNET_FIONREAD = 6,        // FIONREAD

    //! setsockopt/getsockopt level values
    //! socket level
    XFCNET_SOLSOCKET = 7,       // SOL_SOCKET
    XFCNET_IPPROTOTCP = 8,      // IPPROTO_TCP
    XFCNET_IPPROTOUDP = 9,      // IPPROTO_UDP
    XFCNET_IPPROTOIP = 10,      // IPPROTO_IP

    //! set sockopt options
    //! level = SOL_SOCKET
    XFCNET_BROADCAST = 11,       // SO_BROADCAST // get/setsockopt
    XFCNET_SOKEEPALIVE = 12,     // SO_KEEPALIVE // get/setsockopt
    XFCNET_SOREUSEADDR = 13,     // SO_REUSEADDR // get/setsockopt
    XFCNET_SOSNDBUF = 14,        // SO_SNDBUF    // get/setsockopt
    XFCNET_SODEBUG = 15,         // SO_DEBUG     // getsockopt
    XFCNET_SORCVBUF = 16,        // SO_RCVBUF    // getsockopt

    //! level = IPPROTO_TCP
    XFCNET_TCPNODELAY = 17,      // TCP_NODELAY // get/setsockopt
    XFCNET_BTNODELAY = 18,       // BT_NODELAY  // get/setsockopt

    XFCNET_SOBTHCI = 19,         // bluetooth hci layer

    XFCNET_SOBROADCAST = 20,     // SO_BROADCAST // get/setsockopt

};

#endif // !XFCNETDEFINES_H_INCLUDED

