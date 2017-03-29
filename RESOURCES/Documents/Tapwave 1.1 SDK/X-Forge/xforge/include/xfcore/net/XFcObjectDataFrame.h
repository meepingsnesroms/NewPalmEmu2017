/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief 
 *            
 * $Id: XFcObjectDataFrame.h,v 1.11 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.11 $
 */

#ifndef XFCOBJECTDATAFRAME_H_INCLUDED
#define XFCOBJECTDATAFRAME_H_INCLUDED


#include <xfcore/net/XFcObjectDataBuffer.h>

class XFcObjectDataFrameBuffer;
class XFcObjectDataFramePacket;
class XFcObjectDataPacket;


class XFCDLLEXPORT XFcObjectDataFrame
{
private:

    //! Sequence number of packet.
    INT32 mSeqNum;

    //! Packet priority.
    INT32 mPriority;

    //! Packet message slot.
    INT mSlot;

    //! Packet status (do we wan't to send this packet alone).
    INT mPacketStatus;

    //! Recent state id.
    INT32 mRecentStateId;
    
    //! Lock status.
    INT32 mLock;

protected:

    //! Initializes class.
    /*!
     * \param aSlot message slot.
     * \param aBufferSize buffer size.
     * \return 1 if successful, or 0 otherwise.
     */
    XFCIMPORT INT32 init(INT aSlot, INT aBufferSize);

    //! Data buffer.
    XFcObjectDataBuffer *mData;

    //! Protected constructor.
    XFcObjectDataFrame();

public:

    //! Static constructor.
    /*! 
     * \return new object if successful, or NULL if unsuccessful.
     */
    static XFcObjectDataFrame *create(INT aSlot, INT aBufferSize);
    

    //! Sets sequence number.
    /*!
     * \param aSeqNum sequence number
     */
    XFCIMPORT void setSeqNum(INT32 aSeqNum);

    //! Gets sequence number.
    /*!
     * \return sequence number.
     */
    XFCIMPORT INT32 getSeqNum() const;

    //! Sets packet priority.
    /*!
     * \param aPriority packet priority.
     */
    XFCIMPORT void setPriority(INT32 aPriority);

    //! Gets packet priority.
    /*!
     * \return packet priority.
     */
    XFCIMPORT INT32 getPriority() const;

    //! Gets packet message slot.
    /*!
     * \return packet message slot.
     */
    XFCIMPORT INT getMessageSlot() const;


    //! Sets packet status.
    /*!
     * \param aPacketStatus packet status.
     */
    XFCIMPORT void setPacketStatus(INT aPacketStatus);
    
    //! Gets packet status.
    /*!
     * \return packet status.
     */
    XFCIMPORT INT getPacketStatus() const;

    //! Sets recent state id.
    /*!
     * \param recent state id.
     */
    XFCIMPORT void setRecentState(INT32 aId);

    //! Gets recent state id.
    /*!
     * \return recent state id.
     */
    XFCIMPORT INT32 getRecentStateId() const;


    //! Creates a packet.
    /*!
     * \param aPacket object data packet.
     * \return 1 if successful, or 0 otherwise.
     */
    XFCIMPORT INT32 createPacket(XFcObjectDataPacket *aPacket);


    //! Locks buffer.
    /*!
     * \return locked buffer.
     */
    XFCIMPORT void * lock();


    //! Unlocks buffer.
    XFCIMPORT void unlock();


    //! Checks if buffer is locked.
    /*!
     * \return 1 if buffer is locked, or 0 otherwise.
     */
    XFCIMPORT INT32 isLock() const;


    //! Sets packet size.
    /*!
     * \param aPacketSize packet size.
     */
    XFCIMPORT void setPacketSize(INT32 aPacketSize);


    //! Gets size of buffer.
    /*!
     * \return size of buffer.
     */
    XFCIMPORT INT32 sizeofBuffer() const;


    //! Gets size of packet.
    /*!
     * \return size of packet.
     */
    XFCIMPORT INT32 sizeofPacket() const;

    //! Sets message slot.
    /*!
     * \param aSlot message slot.
     */
    XFCIMPORT void setMessageSlot(INT aSlot);


    //! Sets receiver id.
    /* 
     * \param aId receiver id.
     */
    XFCIMPORT void setReceiverId(UINT32 aId);


    //! Resets the frame.
    XFCIMPORT void reset();
    
    //! Virtual destructor.
    XFCIMPORT virtual ~XFcObjectDataFrame();

};


#endif // !XFCOBJECTDATAFRAME_H_INCLUDED

