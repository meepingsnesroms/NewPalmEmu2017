/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Interface to use data section of communication packet
 *
 * $Id: XFcObjectDataPacket.h,v 1.10 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.10 $
 */

#ifndef XFCOBJECTDATAPACKET_H_INCLUDED
#define XFCOBJECTDATAPACKET_H_INCLUDED


#include <xfcore/net/XFcCommPacketBase.h>

class XFcObjectDataQueue;
class XFcDataReceiverHashtable;
class XFcObjectDataServant;
class XFcObjectPacketBase;


//! XFcObjectDataPackets purpose is to give easy interface to use data section of communication packet.
class XFcObjectDataPacket  : public XFcCommPacketBase
{
private:

    //! Start address is packet address + header size.
    CHAR8 *mMemoryBlock;

    //! Holds object packet base.
    XFcObjectPacketBase *mOBase;

    //! Holds packet type.
    INT mPacketType;

public:

    //! Constructor.
    XFcObjectDataPacket(XFcObjectPacketBase *aOBase);

    //! Creates data packet.
    /*!
     * \param aDataQueue object data queue.
     * \param aSeqNum seq number.
     * \param aStyle style.
     */
    INT32 createMultiPacket(XFcObjectDataQueue *aDataQueue, INT32 aSeqNum, INT aStyle);

    //! Creates packet where is only one data packet.
    /*!
     * \param aDataQueue object data queue.
     * \param aSeqNum seq number.
     * \param aStyle style.
     */
    INT32 createOnePacket(XFcObjectDataQueue *aDataQueue, INT32 aSeqNum, INT aStyle);

    //! Creates packet where is automatically one or more packets.
    /*!
     * \param aDataQueue object data queue.
     * \param aSeqNum seq number.
     * \param aStyle style.
     */
    INT32 createAutoPacket(XFcObjectDataQueue *aDataQueue, INT32 aSeqNum, INT aStyle);

    //! Uncreates data packet.
    /*!
     * \param aClientId is identidfier about client where data comes from.
     * \param aObjectServant object servant.
     */
    INT32 uncreatePacket(INT32 aClientId, XFcObjectDataServant *aObjectServant);

    //! Gets data block ptr.
    const CHAR8 * const getDataBlock() const;

    //! Adds data block.
    INT32 addDataBlock(const CHAR8 *aDataBlock, INT16 aLen);

    //! Sets packet type.
    void setPacketType(INT aPacketType);

    //! Gets packet type.
    INT getPacketType() const;

    //! Virtual destructor.
    virtual ~XFcObjectDataPacket();

};


#endif // !XFCOBJECTDATAPACKET_H_INCLUDED

