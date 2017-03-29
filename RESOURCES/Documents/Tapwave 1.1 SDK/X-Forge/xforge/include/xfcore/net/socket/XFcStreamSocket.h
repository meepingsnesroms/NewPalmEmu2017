/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief streaming socket (tcp/ip)
 *
 * $Id: XFcStreamSocket.h,v 1.3 2003/08/12 13:33:50 lars Exp $
 * $Date: 2003/08/12 13:33:50 $
 * $Revision: 1.3 $
 */

#ifndef XFCSTREAMSOCKET_H_INCLUDED
#define XFCSTREAMSOCKET_H_INCLUDED

#include <xfcore/net/socket/XFcSocket.h>

class XFcAsyncCallBack;
class XFcAddress;


//! RFCOMM socket holds connection creation to other bt socket.
/*!
 * One is able to create RFCOMM server socket or client socket.
 * If socket is changed to asynchronous, XFcAsyncCallBack interface pointer must be given.
 * Default socket is created to blocking mode.
 */
class XFCDLLEXPORT XFcStreamSocket : public XFcSocket
{

protected:

    //! Protected constructor.
    XFcStreamSocket();

    //! Initializes XFcL2CAPSocket.
    /*!
     * \return 1 if success else 0
     */
    INT init(INT aPlank);

public:

    //! Creates RFCOMM Socket.
    /*!
     * \return new XFcStreamSocket object if successful, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcStreamSocket *create(INT aPlank = 0);

    //! Opens connection to destination address.
    /*!
     * \param aAddress address where to connect.
     * \param aCallBack callback object.
     * \return 0 if successful, or -1 if unsuccesful.
     */
    XFCIMPORT INT open(const XFcAddress &aAddress, XFcAsyncCallBack *aCallBack = NULL);

    //! Listens connection from other device.
    /*!
      * \param aSocket listen socket.
      * \param aCallBack callback object.
      * \return 0 if successful, or -1 if unsuccessful.
      */
    XFCIMPORT INT open(XFcSocket &aSocket, XFcAsyncCallBack *aCallBack = NULL);


    //! Binds the socket if used as server.
    /*!
     * \param aAddress address where to bind (only port is needed).
     * \return 0 if successful, or -1 if unsuccessful.
     */
    XFCIMPORT INT bind(XFcAddress &aAddress);


    //! Sets up a socket to listen for incoming connections.
    /*! Creates backbuffer for incoming connection.
     * \param aListen is backbuffer size
     * \return 0 if successful, or -1 if unsuccessful.
     */
    XFCIMPORT INT listen(INT aListen);

    //! Sends data, socket ready messages are signaled througth aCallBack.
    /*!
     * \param aData is pointer to data buffer.
     * \param aLen is data buffer length in bytes.
     * \param aCallBack is signaling interface.
     * \return 0 if successful, or -1 if unsuccessful. 0 does not mean that data is delivered successfully.
     */
    XFCIMPORT INT send(const CHAR8 *aData, INT aLen, XFcAsyncCallBack *aCallBack);

    //! Receives data, uses callback for receiving data.
    /*!
     * \param aCallBack is callback interface for received data.
     * \return 0 if successful, or -1 if unsuccessful.
     */
    XFCIMPORT INT recv(XFcAsyncCallBack *aCallBack);

    //! Receives data from socket, not supported if socket is in listen mode.
    /*!
     * \param aData buffer for the incoming data.
     * \param aLen length of buffer.
     * \param aFlags read flags.
     * \return length of read data if successful, or -1 if unsuccessful.
     */
    XFCIMPORT INT recv(CHAR8 *aData, INT32 aLen, INT aFlags);

    //! Sends data to socket, not supported if socket is in listen mode.
    /*!
     * \param aData buffer for outgoing data.
     * \param aLen length of buffer.
     * \param aFlags send flags.
     * \return length of sent data if successful, or -1 if unsuccessful.
     */
    XFCIMPORT INT send(const CHAR8 *aData, INT32 aLen, INT aFlags);

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcStreamSocket();

};
#endif // !XFCRFCOMMSOCKET_H_INCLUDED

