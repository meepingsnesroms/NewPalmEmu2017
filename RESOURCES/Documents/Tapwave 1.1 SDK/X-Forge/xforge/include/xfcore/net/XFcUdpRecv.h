/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief UDP data receiver
 *
 * $Id: XFcUdpRecv.h,v 1.11 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.11 $
 */

#ifndef XFCUDPRECV_H_INCLUDED
#define XFCUDPRECV_H_INCLUDED


class XFcInetAddress;
class XFcDgramSocket;
class XFcObjectPacketBase;


//! XFcUdpRecv is a helper class for receiving data to XFcObjectPacketBase.
class XFcUdpRecv
{
private:

    //! Holds communication socket.
    XFcDgramSocket *mSocket;

protected:

    //! Protected constructor.
    XFcUdpRecv(/*XFcCommunicationHandler &aCommHandler*/);

    //! Initializes.
    /*! 
     * \param aSocket datagram socket.
     */
    INT32 init(XFcDgramSocket *aSocket);

public:

    //! Destructor.
    ~XFcUdpRecv();

    //! Static constructor.
    static XFcUdpRecv * create(XFcDgramSocket *aSocket/*, XFcCommunicationHandler &aCommHandler*/);

    //! Receives data.
    /*!
     * \param aAddress incoming address.
     * \param aIncomingBuffer incoming buffer handler.
     * \return length of received data in bytes if successful, or XFCNET_ERROR if unsuccessful.
     */
    INT32 recv(XFcInetAddress *aAddress, XFcObjectPacketBase *aIncomingBuffer);
};


#endif // !XFCUDPRECV_H_INCLUDED

