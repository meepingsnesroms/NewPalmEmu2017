/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * $Id: XFcCommunicationConstants.h,v 1.9 2003/09/05 07:42:26 slehti Exp $
 * $Date: 2003/09/05 07:42:26 $
 * $Revision: 1.9 $
 */

#ifndef XFCNETDEFINE_H_INCLUDED
#define XFCNETDEFINE_H_INCLUDED

// timeout for local data flow
#define XFCNET_LOCALTIMELIMIT 10000
// timeout for receiving data
#define XFCNET_HOSTCONNECTIONTIMELIMIT 50000

#define XFCNET_HOSTREPLYTIMELIMIT 5000
// max packet size
#define XFCNET_MAXBUFFERSIZE 0x000005aa    // 1450
//#define MAXBUFFERSIZE 2500

//listen buffer max size
#define XFCNET_LISTENBUFFERSIZE 1500


#define XFCNET_MAGICSEQNUM 123

// no seq number set
#define XFCNET_NO_SEQ_NUM 0xffffffff

/// default protocol header size
#define XFCNET_DEFAULT_HEADER_SIZE 9

/// default client queue size
#define XFCNET_DEFAULT_QUEUE_SIZE 150

/// default udp header size
#define XFCNET_UDP_HEADER_SIZE 28

#define XFCNET_COMMINUCATION_DEFAULT_PRIORITY 1000

//#define XFCNET_DEFAULT_NETWORK_PRIORITY 1000

#define XFCNET_PACKETQUEUE_DEFAULT_SIZE 150

#define XFCNET_DEFAULT_CLIENT_COUNT 10

#define XFCNET_INADDR_ANY (UINT32)0x00000000

//! Basic error argument.
#define XFCNET_ERROR -1

//! Not supported error.
#define XFCNET_NOT_SUPPORTED -2

// message slots
enum XFCNET_MESSAGE_SLOT
{
    XFCNET_NONGUARANTEED,
    XFCNET_GUARANTEED,
    XFCNET_RECENTSTATE,
    XFCNET_QUICKGUARANTEED,
    XFCNET_NOSLOT
};

// packet priority enumeration
enum XFCNET_PACKET_PRIORITY
{
    XFCNET_HIGH_PRIORITY  = 0x00000032, // 50
    XFCNET_LOW_PRIORITY   = 0x00000064, // 100
    XFCNET_NO_PRIORITY    = 0x000003e8  // 1000
};

// packet add enumeration
enum XFCNET_OBJECTQUEUE_STATUS
{
    XFCNET_QUEUE_ADD_OK    =    0x00000000,
    XFCNET_QUEUE_ADD_FAILD =    0x00000001,
    XFCNET_QUEUE_EMPTY     =    0x00000002,
    XFCNET_QUEUE_NOT_EMPTY =    0x00000004,
    XFCNET_QUEUE_FULL      =    0x00000008,
    XFCNET_QUEUE_NOT_FULL  =    0x00000010,
    XFCNET_QUEUE_UNKNOWN_PACKET =    0x00000020,
    XFCNET_QUEUE_ALL_FLAGS =    0xffffffff
};


//! Packet handling type.
enum XFCNET_PACKET_STATUS
{
    //! Packets are send alone, one frame/sent packet.
    XFCNET_ALONE,
    //! Packets are send on chunks, multiple frames/sent packet.
    XFCNET_MULTI,
    //! Engine decides how to send packets.
    XFCNET_AUTO
};



enum XFCNET_SCHEDULER_ERROR
{
    XFCNET_SCHEDULER_RUN = -1,
    XFCNET_CLIENTADD_ERROR = -2,
    XFCNET_COMMHANDLERADD_ERROR = -3,
};


enum XFCNET_INET_VALUE
{
    //! Client is unrecognized.
    XFCNET_UNKNOWN_CLIENT = -1
};

//! Connection types.
enum XFCNET_CONNECTIONTYPE
{
    //! Connection type is inet.
    XFCNET_CONNECTIONTYPE_INET = 1,
    XFCNET_CONNECTIONTYPE_IRDA = 2, // not supported
    //! Connection type is bluetooth.
    XFCNET_CONNECTIONTYPE_BLUETOOTH = 3
};

enum XFCNET_CLIENT_ACTIVE
{
    //! Resolving given address was unsuccessful.
//    XFCNET_ADDRESS_ERROR,
    //! Client is active.
    XFCNET_CLIENT_ACTIVE = 1,
    //! Client is not active.
    XFCNET_CLIENT_NOTACTIVE = -2,
    //! Client activity check failed.
    XFCNET_CLIENT_ACTIVE_ERROR = -3
};


// Connection manager communication header
struct CommunicationHeader
{
    UINT32 mVersion;
    INT16 mSeqNum;
    INT16 mAckNum;
    
    // flags where from the left first 4 bits is a window size
    // 5 th is the window flag if value is 0 then window size is for host else for local
    // 6 th is the ack flag. if value is 1 then host is missed some packets
    CHAR8 mFlags;
    /*
    CHAR8 mWin : 4;
    CHAR8 mWinFlag : 1;
    CHAR8 mAckFlag : 1;
    CHAR8 mRtt : 1;
    CHAR8 mReserved : 1;
    */
};


#endif // !XFCNETDEFINE_H_INCLUDED

