/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Network socket stream communication, "client" side connection.
 *
 * $Id: XFcClientStreamSocket.h,v 1.5 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.5 $
 */

#ifndef XFCCLIENTSTREAMSOCKET_H_INCLUDED
#define XFCCLIENTSTREAMSOCKET_H_INCLUDED

#include <xfcore/XFcSocket.h>


//! Network socket stream communication, "client" side connection.
class XFCDLLEXPORT XFcClientStreamSocket : public XFcSocket
{
private:

    //! Network address where to connect.
    XFcAddress *mAddr;

protected:

    //! Protected constructor.
    XFcClientStreamSocket();

public:

    //! Static constructor.
    XFCIMPORT static XFcClientStreamSocket *New();

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcClientStreamSocket();

    //! Opens connection to given address.
    XFCIMPORT INT32 Open(XFcAddress *aAddress);

    //! Sends data to address where connected. 
    /*!
     * \param aBuf data to send.
     * \param aLen bytes to send.
     * \param aFlags send flags.
     * \return number of sent bytes if successful, or -1 otherwise.
     */
    XFCIMPORT INT32 Send(const CHAR8 *aBuf, INT32 aLen, INT32 aFlags);

    //! Receives aLen bytes data from connected socket.
    /*!
     * \param aBuf receive data buffer.
     * \param aLen length of receive data buffer.
     * \param aFlags receive flags.
     * \return number of received bytes if successful, or -1 otherwise.
     */
    XFCIMPORT INT32 Recv(CHAR8 *aBuf, INT32 aLen, INT32 aFlags);

    //! Disables send or receive operations on a socket.
    /*! \note Doesn't release any system resources used by the socket.
     */
    XFCIMPORT INT32 Shutdown(INT32 aHow); 

    //! Connects the socket to host.
    /*! If socket is connected, new address reconnects socket to the new address.
     * \param aAddress address where to connect.
     */
    XFCIMPORT INT32 Connect(XFcAddress *aAddress = NULL);
    
};


#endif // !XFCCLIENTSTREAMSOCKET_H_INCLUDED

