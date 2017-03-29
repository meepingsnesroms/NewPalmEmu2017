/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Automatic packet frame attach to packet MTU
 *
 * $Id: XFcAutoDataPacket.h,v 1.7 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.7 $
 */
#ifndef XFCAUTODATAPACKET_H_INCLUDED
#define XFCAUTODATAPACKET_H_INCLUDED


#include <xfcore/net/XFcPacketCreator.h>

class XFcObjectDataPacket;
class XFcObjectDataQueue;


//! Creates packet automatically from queue and includes as many packet as it can to one sendable packet.
class XFcAutoDataPacket : public XFcPacketCreator
{
protected:

    //! Protected constructor.
    XFcAutoDataPacket();

public:

    //! Static constructor.
    static XFcAutoDataPacket *create();

    //! Creates a packet.
    /*! 
     * \param aQueue packet queue.
     * \param aSeqNum sequence number.
     * \param aOdata data packet.
     * \return 1 if successful, or 0 otherwise.
     */
    virtual INT32 createPacket(XFcObjectDataQueue *aQueue, INT32 aSeqNum, XFcObjectDataPacket *aOdata);
    
    //! Gets packet status.
    virtual INT32 getPacketStatus();

    //! Virtual destructor.
    virtual ~XFcAutoDataPacket();

};


#endif // !XFCAUTODATAPACKET_H_INCLUDED

