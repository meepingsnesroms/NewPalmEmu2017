/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Bluetooth data handler
 *
 * $Id: XFcBtHandler.h,v 1.15 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.15 $
 */

#ifndef XFCBTHANDLER_H_INCLUDED
#define XFCBTHANDLER_H_INCLUDED

#include <xfcore/net/XFcCommunicationHandler.h>

static const INT32 XFCNET_SEND_BUFFER_SIZE = 512;
static const INT32 XFCNET_RECV_BUFFER_SIZE = 512;

class XFcClientLost;
class XFcObjectPacketBase;
class XFcSocket;
class XFcBtCommService;
class XFcBtAddress;
class XFcAddress;
class XFcBtClientWin;
class XFcBtSecurity;


//! Used to handle data flow thought RFCOMM interface. 
/*!
 * Its responsibility is to be data flow interface for sending/receiving 
 * data througth RFCOMM. It works as RFCOMM server to other clients if needed.
 * Its only binding interface and does not own any client connection. It holds 
 * sending and receiving buffers where data is copied before sending or accessing
 * (receiving) it.
 */
class XFCDLLEXPORT XFcBtHandler : public XFcCommunicationHandler
{
private:

    //! Buffer for sending data.
    XFcObjectPacketBase *mSendBuffer;
    
    //! Buffer for receiving data.
    XFcObjectPacketBase *mRecvBuffer;
    
    //! Holds server socket.
    XFcSocket *mSocket;
    
    //! Holds bt address.
    XFcBtAddress *mAddress;
    
    //! Holds server status.
    INT mServerStatus;
    
    //! Holds bt security manager.
    XFcBtSecurity *mSecurity;
    
protected:

    //! Protected constructor.
    XFCIMPORT XFcBtHandler();
    
    //! Initialize XFcBtHandler.
    XFCIMPORT INT init(INT aIsServer, INT32 aSendMtu, INT32 aRecvMtu);
    

public:
    
    //! Static constructor.
    /*!
     * \param aIsServer must be true if handler is used as a server.
     * \param aSendMtu Maximum MTU size for sendable packet.
     * \param aRecvMtu Maximum MTU size for receivable packet.
     */
    XFCIMPORT static XFcBtHandler *create(INT aIsServer,
                                          INT32 aSendMtu = XFCNET_SEND_BUFFER_SIZE,
                                          INT32 aRecvMtu = XFCNET_RECV_BUFFER_SIZE);
    
    //! Virtual destructor.
    XFCIMPORT virtual ~XFcBtHandler();
    
    //! Opens handlers server behavior.
    /*!
     * \param aAddress address used to bind server service.
     * \param aClientCount client count.
     * \note N7650 does not support more than one client.
     * \return 1 if server is created succesfully, or 0 otherwise.
     */
    XFCIMPORT INT openServer(XFcAddress &aAddress, INT32 aClientCount);

    //! Creates connection to given client.
    /*!
     * \param aClient empty client that is used for incoming connection.
     * \return 1 if listen starts properly, or 0 otherwise.
     */
    XFCIMPORT INT listenConnection(XFcBtClientWin &aClient);

    //! Cancels listen.
    XFCIMPORT void cancelListen();

    //! Determines if handler is a server.
    /*!
     * \return 1 if handler works as server, or 0 otherwise.
     */
    XFCIMPORT INT isServer();
 
    //! Closes handler service.
    XFCIMPORT virtual void closeService();

    //! Sends a packet.
    /*!
     * \return size of sent packet if succesful, or XFCNET_ERROR otherwise.
     */
    XFCIMPORT virtual INT outgoing();
    
    //! Receives a packet frame.
    /*!
     * \return size of received packet if succesful, or XFCNET_ERROR otherwise.
     */
    XFCIMPORT virtual INT incoming();

    //! Sets connection type.
    /*!
     * \param aType connection type.
     */
    XFCIMPORT void setDefaultSpeed(INT aType);
    
    //! Checks client activity.
    XFCIMPORT virtual void checkActivity();
    
    //! Handles data which sender is not known.
    XFCIMPORT virtual void unknownSender(const XFcAddress *aAddress, XFcObjectPacketBase *aPacket);

};


#endif // !XFCBTHANDLER_H_INCLUDED

