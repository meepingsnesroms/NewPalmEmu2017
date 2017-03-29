/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd       
 *
 * \brief Packet creation interface
 *
 * $Id: XFcPacketCreator.h,v 1.9 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.9 $
 */
#ifndef XFCPACKETCREATOR_H_INCLUDED
#define XFCPACKETCREATOR_H_INCLUDED

class XFcObjectDataPacket;
class XFcObjectDataQueue;


//! XFcPacketCreator is base interface for creating packet.
class XFcPacketCreator 
{
protected:
    
    //! Holds packet style.
    INT mPacketStyle;
    
    //! Protected constructor.
    XFcPacketCreator();

public:

    //! Creates data packet.
    /*!
     * \param aQueue packet queue.
     * \param aSeqNum sequency number.
     * \param aOdata data packet buffer.
     */
    virtual INT32 createPacket(XFcObjectDataQueue *aQueue, INT32 aSeqNum, XFcObjectDataPacket *aOdata) = 0;

    //! Gets current status.
    /*!
     * \return packet status (XFCNET_ALONE, XFCNET_MULTI or XFCNET_AUTO).
     */
    virtual INT32 getPacketStatus() = 0;

    //! Virtual destructor.
    virtual ~XFcPacketCreator();

};


#endif // !XFCPACKETCREATOR_H_INCLUDED

