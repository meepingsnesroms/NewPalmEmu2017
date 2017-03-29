/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Communication header serialization
 *
 * $Id: XFcCommHeaderPacket.h,v 1.8 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.8 $
 */

#ifndef XFCCOMMHEADERPACKET_H_INCLUDED
#define XFCCOMMHEADERPACKET_H_INCLUDED

#include <xfcore/net/XFcCommPacketBase.h>


class XFcObjectPacketBase;
struct CommunicationHeader;


//! XFcCommHeaderPacket is usage class for communication header data used with datagram packets.
/*!
 * Its created for easy access to communication header data. 
 */
class XFcCommHeaderPacket : public XFcCommPacketBase
{
private:

    //! Start ptr for header.
    CommunicationHeader *mHeader;

public:

    //! Constructor.
    XFcCommHeaderPacket(XFcObjectPacketBase *aOBase);

    //! Gets ack number.
    /*!
     * \return ack number.
     */
    INT32 getAckNumber() const;

    //! Gets seq number.
    /*!
     * \return seq number.
     */
    INT32 getSeqNumber() const;
     
    //! Tests for ack flag.
    /*!
     * \return 1 if nack flag is set else 0.
     */
    INT32 isNackFlag() const;
    
    //! Sets header ack number.
    /*!
     * \param aNumber ack number.
     */
    void setAckNumber(INT32 aNumber);

    //! Sets header seq number.
    /*!
     * \param aNumber seq number.
     */
    void setSeqNumber(INT32 aNumber);
    
    //! Sets version number of protocol.
    /*!
     * \param aVersion version number of protocol
     */
    void setVersionNumber(UINT32 aVersion);

    //! Gets version number of protocol.
    /*! 
     * \return version number.
     */
    UINT32 getVersionNumber();

    //! Sets nack flag.
    void setNackFlag();

    //! Clears nack flag.
    void clearNackFlag();

    //! Sets packet type.
    /*!
     * \param aPacketType packet type.
     */
    void setPacketType(INT aPacketType);
    
    //! Gets packet type.
    /*!
     * \return packet type.
     */
    INT getPacketType() const;

    //! Sets rtt flag.
    void setRtt();

    //! Tests for rtt flag.
    INT32 isRtt() const;

    //! Virtual destructor.
    virtual ~XFcCommHeaderPacket();

};


#endif // !XFCCOMMHEADERPACKET_H_INCLUDED

