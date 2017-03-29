/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd          
 *
 * \brief Single packet frame attach to packet MTU.
 *
 * $Id: XFcSingleDataPacket.h,v 1.8 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.8 $
 */

#ifndef XFCSINGLEDATAPACKET_H_INCLUDED
#define XFCSINGLEDATAPACKET_H_INCLUDED

#include <xfcore/net/XFcPacketCreator.h>

class XFcObjectDataQueue;
class XFcObjectDataPacket;


//! XFcSingleDataPacket creates data packet from queue only with one frame.
class XFcSingleDataPacket : public XFcPacketCreator
{
protected:

    //! Protected constructor.
    XFcSingleDataPacket();

public:

    //! Static constructor.
    static XFcSingleDataPacket * create();

    //! Creates a packet.
    /*! 
     * \param aQueue packet queue.
     * \param aSeqNum sequency number.
     * \param aOdata packet buffer.
     */
    virtual INT32 createPacket(XFcObjectDataQueue *aQueue, INT32 aSeqNum, XFcObjectDataPacket *aOdata);

    //! Returns packet status.
    virtual INT32 getPacketStatus();

    //! Virtual destructor.
    virtual ~XFcSingleDataPacket();

};


#endif // !XFCSINGLEDATAPACKET_H_INCLUDED

