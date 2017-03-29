/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Datagram socket
 *
 * $Id: XFcDgramSocket.h,v 1.6 2003/08/12 13:33:50 lars Exp $
 * $Date: 2003/08/12 13:33:50 $
 * $Revision: 1.6 $
 */

#ifndef XFCDGRAMSOCKET_H_INCLUDED
#define XFCDGRAMSOCKET_H_INCLUDED

#include <xfcore/net/socket/XFcSocket.h>
#include <xfcore/net/socket/XFcAddress.h>


//! Network socket datagram communication.
/*!
 * Its purpose is to give socket interface for datagram packets.
 */
class XFCDLLEXPORT XFcDgramSocket : public XFcSocket
{

protected:

    //! Protected constructor.
    XFcDgramSocket();
    
    //! Initializes datagram socket.
    /*!
     * \return 1 if succesful, or 0 otherwise.
     */
    INT init();

public:

    //! Static constructor.
    /*!
     * \return new object if successful, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcDgramSocket * create();

    //! Opens connection.
    /*! 
     * \param aAddress where to accept packets.
     */
    XFCIMPORT INT32 open(const XFcAddress &aAddress);

    //! Sends bytes.
    /*!
     * \param aBuf data buffer.
     * \param aLen length of data buffer in bytes.
     * \param aFlags reserved, set to 0.
     * \param aAddress where to send data.
     * \return length of sent data if successful, or XFCNET_ERROR if unsuccessful.
     */
    XFCIMPORT INT32 sendTo(const CHAR8 *aBuf, INT32 aLen, INT32 aFlags,
                           const XFcAddress &aAddress); 

    //! Receives data.
    /*!
     * \param aBuf buffer where data is received.
     * \param aLen length of buffer.
     * \param aFlags reserved, set to 0.
     * \param aAddress where data is received from.
     * \return length of received data if successful, or XFCNET_ERROR if unsuccessful.
     */
    XFCIMPORT INT32 recvFrom(CHAR8 *aBuf, INT32 aLen, INT32 aFlags, XFcAddress &aAddress); 

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcDgramSocket();

};


#endif // !XFCDGRAMSOCKET_H_INCLUDED

