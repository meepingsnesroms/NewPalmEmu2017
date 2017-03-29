/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Bluetooth client
 *
 * $Id: XFcBtClientWin.h,v 1.12 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.12 $
 */

#ifndef XFCBTCLIENTWIN_H_INCLUDED
#define XFCBTCLIENTWIN_H_INCLUDED


//! Size of the buffer allocated for packet (MTU).
static const UINT32 XFCNET_QUEUE_BUFFER_SIZE = 128;
//! Granularity of queue.
static const UINT32 XFCNET_QUEUE_BUFFER_COUNT = 10;

#include <xfcore/net/XFcClientCommWin.h>
#include <xfcore/net/socket/XFcAsyncCallBack.h>

class XFcObjectDataQueue;
class XFcPacketCreator;
class XFcObjectDataFrame;
class XFcRFCOMMSocket;
class XFcAddress;
class XFcSocket;


//! Holds bluetooth line status.
enum XFCNET_BT_LINESTATUS
{
    //! Socket disconnected.
    XFCNET_BT_LINESTATUS_DISCONNECT = -1,
    //! Connection failed.
    XFCNET_BT_LINESTATUS_FAILED = -2,
    //! Socket connecting to server.
    XFCNET_BT_LINESTATUS_CONNECTING = -3,
    //! Socket connected to server.
    XFCNET_BT_LINESTATUS_OK = 1,
    //! Socket connection canceled.
    XFCNET_BT_LINESTATUS_CANCEL = -4,
    //! Socket waits client to connect.
    XFCNET_BT_LINESTATUS_WAIT = -5,
    //! Socket connected but not accepted.
    XFCNET_BT_LINESTATUS_ONHOLD = -6,
};


//! Holds bluetooth client data that is used to keep up data flow from/to server.
/*!
 * XFcBtClientWin is used to hide connected RFCOMM socket behavior to work as connectionless socket.
 * It can be created to listen or to connection mode. If it's created to connection mode it will try to make
 * connection to a "server" device. In listen mode it starts to wait if someone binds connection to it.
 * \par
 * After connection is established there's no difference between connected or bound client
 * while sending or receiving data. Every bound connection must be accepted or rejected with acceptConnection(),
 * otherwise connection is unusable.
 * \par
 * Object holds priority queue which is used to hold sendable data to other device. It also stores data
 * until it is sent and data has reached it's destination (only XFCNET_GUARANTEED and XFCNET_QUICKGUARANTEED
 * are hold). XFcPacketCreator implements how data is going to be sent. Data can be sent in one big packet frame
 * when it will copy as much data it can to one sendable packet, or data can be sent in single packet frames.
 */
class XFCDLLEXPORT XFcBtClientWin : public XFcClientCommWin,
                                    public XFcAsyncCallBack
{
private:

    //! Holds communication socket.
    XFcRFCOMMSocket *mSocket;

    //! Object data priority queue.
    XFcObjectDataQueue *mPriorityQueue;

    //! Current packet creator.
    XFcPacketCreator *mPacketCreator;

    //! Holds client ativity status.
    INT mLineStatus;

protected:

    //! Initializes XFcBtClientWin.
    /*!
     * \param aAddress server address where to connect.
     * \param aGranularity packet list granularity. Max size for packet list.
     * \param aBufferMaxSize max size for buffer. 
     * \return 1 if succesful, or 0 otherwise.
     */
    XFCIMPORT INT init(const XFcAddress *aAddress, INT32 aGranularity, INT32 aBufferMaxSize);

    //! Protected constructor.
    XFCIMPORT XFcBtClientWin();

    //! Bt action failed.
    /*! \note Inherited from XFcAsyncCallBack.
     */
    XFCIMPORT virtual void actionFailed(INT32 aStatus = 0);

    //! Bt action ready.
    XFCIMPORT virtual void actionReady(INT32 aStatus = 0);

    //! Bt action canceled.
    XFCIMPORT virtual void actionCancel(INT32 aStatus = 0);

    //! Not needed
    XFCIMPORT virtual void actionReceive(const CHAR8 *, INT32){return;}

    //! Not needed
    XFCIMPORT virtual void actionSend(INT32){return;}
    

public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcBtClientWin();

    //! Static constructor.
    /*!
     * \param aAddress where client is going to connect, can be set to NULL.
     * \param aGranularity packet list granularity. Max size for packet list.
     * \param aBufferMaxSize max size for buffer.  
     * \return new object if successful, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcBtClientWin * create(const XFcAddress *aAddress,
                                             INT32 aGranularity = XFCNET_QUEUE_BUFFER_COUNT,
                                             INT32 aBufferMaxSize = XFCNET_QUEUE_BUFFER_SIZE);

    //! Opens client connection to address given by create. Connection open is a asynchronous.
    XFCIMPORT INT openClient();

    //! Opens connection to client (listening mode). Connection open is a asynchronous.
    XFCIMPORT INT openClient(XFcSocket &aSocket, XFcAsyncCallBack *aCallBack);

    //! Accepts this connection.
    XFCIMPORT void acceptConnection(INT aEnable);

    //! Close client connection.
    XFCIMPORT void closeClient();

    //! Receives packet buffer from server.
    /*! \note Inherited from XFcClientCommWin.
     */
    XFCIMPORT virtual INT32 incoming(XFcObjectPacketBase &mRecvBuffer);

    //! Sends packet to server.
    XFCIMPORT virtual INT32 outgoing(XFcObjectPacketBase &mSendBuffer);

    //! Gets packet frame for sendable data.
    /*!
     * \param aSlot packet slot id.
     * \return data frame.
     */
    XFCIMPORT virtual XFcObjectDataFrame * getPacketFrame(INT aSlot);

    //! Gets recent state frame for sendable data.
    /*!
     * \param aRecentId recent state id.
     * \return recent state frame.
     */
    XFCIMPORT virtual XFcObjectDataFrame * getRecentStateFrame(INT32 aRecentId);

    //! Removes recent state frame.
    /*!
     * \param aRecentId recent state id.
     */
    XFCIMPORT virtual void removeRecentStateFrame(INT32 aRecentId);

    //! Sets address.
    /*!
     * \param aAddress address where to connect.
     */
    XFCIMPORT virtual void setAddress(const XFcAddress &aAddress);
    
    //! Gets client status.
    XFCIMPORT virtual INT isClientActive();

    //! Tests address.
    /*!
     * \param aAddress address to test.
     * \return 1 if address is same, or 0 otherwise.
     */
    XFCIMPORT virtual INT testAddress(const XFcAddress &aAddress);

    //! Checks if we are able to send any data.
    XFCIMPORT virtual INT bandwidthCheck();

    //! Runtime initialize.
    XFCIMPORT virtual void initializeClient();

    //! Runtime deinitialize.
    XFCIMPORT virtual void deinitializeClient();

};


#endif // !XFCBTCLIENTWIN_H_INCLUDED

