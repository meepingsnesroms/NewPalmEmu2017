/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Socket base
 *
 * $Id: XFcSocket.h,v 1.6 2003/08/12 13:33:50 lars Exp $
 * $Date: 2003/08/12 13:33:50 $
 * $Revision: 1.6 $
 */

#ifndef XFCSOCKET_H_INCLUDED
#define XFCSOCKET_H_INCLUDED

class XFcAddress;


//! NetworkCommBase, defines abstract socket layer for communication.
class XFCDLLEXPORT XFcSocket
{
protected:

    //! Socket handle.
    void *mSocket;

public:

    //! Opens a socket. Returns -1 if error or 0 if success.
    /*! 
     * Wrapper around socket command.
     * If socket is already created recall will close existing socket and 
     * create a new one.
     */
    XFCIMPORT INT32 open(INT32 aProtocolFamily, INT32 aType, INT32 aProtocol
                         /*, INT aReuse = 0*/);

    //! Gets handle for device.
    /*!
     * \return device handle - socket.
     */
    XFCIMPORT void * getHandle();

    //! Set handle for device - socket.
    XFCIMPORT void setHandle(void *aSocket);

    //! Release handle for reuse. 
    /*!
     * \warning Socket object is not valid for reuse after caling close(). This behavior is inherited from 
     *          epoc where close() function call means socket close and closing communication
     *          channel to socket server. After close() call XFcSocket class must be deleted.
     */
    XFCIMPORT void close();

    //! Gets local address. Returns -1 if error else 0.
    XFCIMPORT INT32 getLocalAddress(XFcAddress &);

    //! Gets remote address. Returns -1 if error else 0.
    XFCIMPORT INT32 getRemoteAddr(XFcAddress &);

    //! Sets socket options. Wrapper around setsockoption.
    XFCIMPORT INT32 setOption(INT32 aLevel, 
                              INT32 aOptname, 
                              const void *aOptval,
                              INT32 aOptlen);

    //! Gets socket options. Wrapper around getsockoption.
    XFCIMPORT INT32 getOption(INT32 aLevel, 
                              INT32 aOptname, 
                              void *aOptval,
                              INT32 *aOptlen);

    //! Ioctl socket. Wrapper around ioctl socket command.
    XFCIMPORT INT32 ioctl(INT32 aCmd, UINT32 *aArgp); 

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcSocket();

protected:

    //! Protected constructor.
    /*! Ensure abstract use of the class as there is no public static constructor.
     */
    XFcSocket();
};


#endif // !XFCSOCKET_H_INCLUDED

