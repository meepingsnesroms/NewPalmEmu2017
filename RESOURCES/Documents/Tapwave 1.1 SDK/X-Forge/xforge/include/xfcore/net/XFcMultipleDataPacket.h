/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Adds multiple packet frames to packet MTU
 *
 * $Id: XFcMultipleDataPacket.h,v 1.7 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.7 $
 */

#ifndef XFEMULTIPLEDATAPACKET_H_INCLUDED
#define XFEMULTIPLEDATAPACKET_H_INCLUDED

#include <xfcore/net/XFcPacketCreator.h>

class XFcObjectDataPacket;
class XFcObjectDataQueue;


//! XFcMultipleDataPacket collects one or more data frames to on sendable packet.
/*!
 * It creates sendable data frame from object data queue. It try to add as meny packet frames to 
 * object data packet as it can. 
 */
class XFcMultipleDataPacket : public XFcPacketCreator
{
protected:

    //! Protected constructor.
    XFcMultipleDataPacket();

public:

    //! Static constructor.
    static XFcMultipleDataPacket *create();

    //! Creates a packet.
    /*! 
     * \param aQueue packet queue.
     * \param aSeqNum sequence number.
     * \param aOdata data packet.
     * \return 1 if successful, or 0 otherwise.
     */
    virtual INT32 createPacket(XFcObjectDataQueue *aQueue, INT32 aSeqNum, XFcObjectDataPacket *aOdata);
    
    //! Gets packet status.
    /*!
     * \return packet status.
     */
    virtual INT32 getPacketStatus();

    //! Virtual destructor.
    virtual ~XFcMultipleDataPacket();
};


#endif // !XFEMULTIPLEDATAPACKET_H_INCLUDED

