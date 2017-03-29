/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Inet client
 *
 * $Id: XFcInetClientWin.h,v 1.13 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.13 $
 */

#ifndef XFCINETCLIENTWIN_H_INCLUDED
#define XFCINETCLIENTWIN_H_INCLUDED


#include <xfcore/net/XFcCommunicationConstants.h>
#include <xfcore/net/XFcClientCommWin.h>

class XFcObjectPacketBase;
class XFcSingleDataPacket;
class XFcInetAddress;
class XFcDgramSocket;
class XFcPacketCreator;
class XFcObjectDataQueue;
class XFcAddress;
class XFcInetHostResolver;


//! XFcInetClientWin is inet client and its responsipilty is handle data flow to inet client.
/*!
 * Its sends or receives data from client that is bind for this client window class. 
 * It handles data flow and try to avoid to choke this client with data. 
 */
class XFCDLLEXPORT XFcInetClientWin : public XFcClientCommWin
{
private:

    //! Holds connection status <not needed for now>.
    INT mConnectionStatus;

    //! Holds client priority.
    INT mPriority;

    //! Holds time when client is able to get new data.
    INT32 mNextPacketTime;

    
    //! Local communication data for client.
    struct LocalWindow
    {
        // For test //// set by host 
        INT mAckFlagi;
        ////////////////
    
        UINT8 mSlidingWin;  // Sliding window for communication 
        // mSlidingWin <= (mLastSent - mLastAct+1)
        // server can adjust this value to handle 
        // client send buffer                  
        UINT16 mLastAck;     // Last sent packet which is acked
        // ACK field from recv packet can increase this 
        UINT16 mLastSent;    // last sent sequency number
        // increase this before sendin and add value to outgoing packets seqnum field
        UINT32 mPacketTime;  // time when last packet was sent    

        UINT16 mNewSeqNum;

        UINT32 mRttSendTime;

        INT32 mRttFlag;

        UINT16 mRttSeqNum;

        UINT32 mPacketCount;

        UINT32 mPacketLostCount;

        UINT16 mPrevAck;

    } mLocalWindow;


    //! Host communication data "server".
    struct HostWindow
    {
        // for test //// set by client
        INT mAckFlagi;
        ////////////////
    
        UINT8 mSlidingWin;  // receive ack window size
        // mSlidingWin <= (mLastAct - mLastSent + 1)
        UINT16 mLastAck;     // Last acknowledged. Tells what is the last sent ACK field
        UINT16 mLastRecv;    // Last received. seqnum field from last incoming packet
        // add ack value to outgoing packet "if ((mLastRecv - mLastAct) > 5)" 
        INT32 mPacketTime;  // time when last packet was received    

        UINT16 mNextRecv;

        UINT16 mSeed;

        INT32 mRttFlag;

        UINT32 mHostReplyTime;

        UINT32 mPacketCount;

        INT32 mTestPacket;

        UINT32 mPacketLostCount;

    } mHostWindow;


    //! Holds object data priority queue.
    XFcObjectDataQueue *mPriorityQueue;

    //! Holds current packet creator.
    XFcPacketCreator *mPacketCreator; 

    //! Holds inet address resolver.
    XFcInetHostResolver *mResolver;

protected:

    //! Initializes class.
    XFCIMPORT INT init(const CHAR8 *aAddress, UINT16 aPort, INT32 aGranularity, INT32 aPacketMaxSize);

    //! Initializes class.
    XFCIMPORT INT init(INT32 aGranularity, INT32 aPacketMaxSize);

    //! Counts local window size.
    XFCIMPORT INT countLocalWindow();

    //! Counts host window size.
    XFCIMPORT INT countHostWindow();

    //! Counts next packet time.
    XFCIMPORT void countNextPacketTime(INT aPacketSize);

    //! Protected constructor.
    XFCIMPORT XFcInetClientWin();    
    
public:

    //! Static constructor.
    /*!
     * \param aAddress client address, address can be given with syntax "127.0.0.1" or 
     *        "www.fathammer.com". If address is syntax is "127.0.0.1" reverse arp is not 
     *        used and address is accepted as is.
     * \param aPort client port.
     * \param aGranularity packet queue size.
     * \param aPacketMaxSize maximum size for packet.
     * \return new object if successful, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcInetClientWin * create(const CHAR8 *aAddress, UINT16 aPort,
                                               INT32 aGranularity = XFCNET_PACKETQUEUE_DEFAULT_SIZE,
                                               INT32 aPacketMaxSize = 1024);

    //! Static constructor.
    /*!
     * \return pointer to XFcInetClientWin
     */
    XFCIMPORT static XFcInetClientWin * create(INT32 aGranularity = XFCNET_PACKETQUEUE_DEFAULT_SIZE,
                                               INT32 aPacketMaxSize = 1024);

    //! Sets priority for this client.
    XFCIMPORT void setPriority(INT aPriority);

    //! Gets priority.
    XFCIMPORT INT getPriority();

    //! Gets client activity status.
    XFCIMPORT INT isClientActive();

    //! Returns recv error %.
    XFCIMPORT INT getRecvErrorValue();

    //! Return send error %.
    XFCIMPORT INT getSendErrorValue();

    //! Adds address.
    /*!
     * \param add client address.
     */
    XFCIMPORT virtual void setAddress(const XFcAddress &aAddress);

    //! Address check.
    /*!
     * \param address where to compare.
     */
    XFCIMPORT virtual INT testAddress(const XFcAddress &aAddress);

    //! Clients bandwidth check.
    /*! 
     * \return 1 if successful, or 0 otherwise.
     */
    XFCIMPORT virtual INT bandwidthCheck();

    //! Clients protocol settings management.
    XFCIMPORT void clientProtocolManager();

    //! Changes packet creator.
    /*!
     * \param aPacketCreator packet creator enumeration.
     */
    XFCIMPORT INT changePacketCreator(INT aPacketCreator);

    //! Creates protocol packet.
    /*!
     * \param aPacket packet buffer.
     * \return outgoing packet size. On error return value is -1 and error reason is set. 
     */
    XFCIMPORT virtual INT32 outgoing(XFcObjectPacketBase &aPacket);

    //! Uncreates incoming packet.
    /*!
     * \param aPacket packet buffer.
     * \return handled packet size.
     */
    XFCIMPORT virtual INT32 incoming(XFcObjectPacketBase &aPacket);

    //! Gets packet frame.
    /*!
     * \param aSlot message identifier.
     * \return packet frame class
     */
    XFCIMPORT virtual XFcObjectDataFrame * getPacketFrame(INT aSlot);

    //! Gets recent state frame.
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

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcInetClientWin();

};


#endif // !XFCINETCLIENTWIN_H_INCLUDED

