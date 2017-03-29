/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * $Id: XFcL2CAPSocket.h,v 1.6 2003/08/12 13:33:50 lars Exp $
 * $Date: 2003/08/12 13:33:50 $
 * $Revision: 1.6 $
 */

#ifndef XFCL2CAPSOCKET_H_INCLUDED
#define XFCL2CAPSOCKET_H_INCLUDED

#include <xfcore/net/socket/XFcSocket.h>
#include <xfcore/net/socket/XFcAsyncCallBack.h>


//! Interface to L2CAP socket bluetooth socket layer.
/*!
 * \note You do not need this at all.
 */
class XFCDLLEXPORT XFcL2CAPSocket : public XFcSocket
{
protected:

    XFcL2CAPSocket();
    
    //! Initializes XFcL2CAPSocket.
    /*!
     * \return 1 if successful, or 0 otherwise.
     */
    INT init(INT aPlank);
    
public:
    
    //! Creates L2CAPSocket.
    /*!
     * \return returns XFcL2CAPSocket if successful, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcL2CAPSocket *create(INT aPlank = 0);

    //! Opens connection to destination address.
    /*!
     * \param aAddress holds address where to connect.
     * \return 0 if successful, or -1 if unsuccessful.
     */
    XFCIMPORT INT open(const XFcAddress &aAddress, XFcAsyncCallBack *aCallBack = NULL);

    //! Listens connection from other device.
    /*! 
     * \param aSocket socket to listen.
     * \param aAddress callback object.
     * \return 0 if successful, or -1 if unsuccessful.
     */
    XFCIMPORT INT open(XFcSocket &aSocket, XFcAsyncCallBack *aCallBack = NULL);


    //! Binds the socket if used as server.
    /*!
     * \param aAddress is the address where to bind (only port is needed).
     * \return 0 if successful, or -1 if unsuccessful.
     */
    XFCIMPORT INT bind(XFcAddress &aAddress);


    //! Sets up a socket to listen for incoming connections.
    /*! Creates backbuffer for incoming connection.
     */
    XFCIMPORT INT listen(INT aListen);

    // Reads data from socket, not supported if socket is in listen mode.
    /*
     * \param aData buffer for the incoming data.
     * \param aLen length of buffer.
     * \return -1 if error else length of read data.
     */
    //INT read(CHAR8 *aData, INT aLen);

    //! Receives data from socket, not supported if socket is in listen mode.
    /*!
     * \param aData buffer for the incoming data.
     * \param aLen length of buffer.
     * \param aFlags receive flags.
     * \return length of read data if successful, or -1 if unsuccessful.
     */
    XFCIMPORT INT32 recv(CHAR8 *aData, INT aLen, INT aFlags);

//    INT recvNoNagle(RSocket &aSocket, TDes8 aDesc, TUint aFlags);
//    INT recvFrom(RSocket &aSocket, TDes8 &aDesc, TSockAddr &aAddr, TUint aFlags);

    // Writes data to socket, not supported if socket is in listen mode.
    /*
     * \param aData buffer for outgoing data.
     * \param aLen length of buffer.
     * \return length of sent data if successful, or -1 if unsuccessful.
     */
    //INT write(const CHAR8 *aData, INT aLen);

    //! Sends data to socket, not supported if socket is in listen mode.
    /*!
     * \param aData buffer for outgoing data.
     * \param aLen length of buffer.
     * \param aFlags send flags.
     * \return length of sent data if successful, or -1 if unsuccessful.
     */
    XFCIMPORT INT32 send(const CHAR8 *aData, INT aLen, INT aFlags);

//    INT sendTo(RSocket &aSocket, const TDesC8 &aDesc, TSockAddr &aAddr, TUint aFlags);

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcL2CAPSocket();

};


#endif // !XFCL2CAPSOCKET_H_INCLUDED

