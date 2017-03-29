/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Holds prioritized packets.
 *
 * $Id: XFcObjectDataQueue.h,v 1.8 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.8 $
 */

#ifndef XFCOBJECTDATAQUEUE_H_INCLUDED
#define XFCOBJECTDATAQUEUE_H_INCLUDED


#include <xfcore/XFcLinkedList.h>
#include <xfcore/XFcPriorityList.h>
#include <xfcore/net/XFcObjectDataPriorityHelp.h>

class XFcObjectDataFrame;
class XFcObjectDataPacket;
class XFcObjectDataBuffer;


//! XFcObjectDataQueue holds prioritized packets.
/*!
 * It holds list of locked and unlocked packet frames. If packet frame is locked
 * list does not add it to sendable packet frame. If packet is unlocked and contains
 * data it can be added to sendable packet frame. Its purpose is to keep added packet
 * frames on prioritized order and update order if wanted. XFcObjectDataQueue owns all
 * the data added to it, delete of queue will remove all XFcObjectDataFrame allocated.
 * XFcObjectDataFrame allocation is made with given granularity. After send of packet frame
 * queue does not delete packet, it marks frame free for later use.
 *
 */
class XFcObjectDataQueue
{
private:

    //! Holds recent state handle.
    INT32 mRecentStateHandle;

    //! Holds queue max size.
    UINT32 mMaxSize;

    //! Holds buffer size.
    INT mBufferSize;

    //! Holds reset flag.
    INT mReset;

protected:

    //! Holds lists of data send/sendable packets.
    XFcObjectDataPriorityHelp mHelp;

    XFcPriorityList <XFcObjectDataFrame *> mObjectUnlockedData;

    //! Holds list of unlocked packet frames.
    XFcLinkedList <XFcObjectDataFrame *> mObjectLockedData;

    //! Initializes list.
    INT32 init(INT32 aMaxSize, INT aBufferSize);

    //! Adds new packet to list.
    INT32 addPacket(XFcObjectDataFrame *aPacket);

    //! Gets locked frame.
    INT32 getIndexOfLockedFrame(XFcLinkedList<XFcObjectDataFrame *> *aList);

    //! Gets unlocked frame.
    INT32 getIndexOfUnlockedFrame(XFcLinkedList<XFcObjectDataFrame *> *aList);

    //! Gets index of negative buffer size.
    INT32 getIndexOfNegativeBufferSize(XFcLinkedList<XFcObjectDataFrame *> *aList);

    //! Gets frame.
    XFcObjectDataFrame *getFrameByIndex(XFcLinkedList<XFcObjectDataFrame *> *aList, INT32 aIndex);

    //! Protected constructor.
    XFcObjectDataQueue();

public:

    //! Gets packet frame.
    /*!
     * \param aSlot message identifier (RECENTSTATE ...).
     * \return packet frame class.
     */
    XFcObjectDataFrame *getPacketFrame(INT aSlot);

    //! Gets packet frame.
    /*!
     * \param aRecentId message identifier (RECENTSTATE ...).
     * \return packet frame class.
     */
    XFcObjectDataFrame *getRecentStateFrame(INT32 aRecentId);

    //! Reorders frames, will reorder packet to priority order and moves empty frames to empty list.
    void reorderFrames();

    //! Removes recent state frame.
    /*!
     * \param aRecentId recent state id.
     */
    void removeRecentStateFrame(INT32 aRecentId);


    //! Static constructor.
    /*!
     * \param aMaxSize max queue size.
     * \param aBufferSize max buffer size.
     * \return new object if successful, or NULL if unsuccessful.
     */
    static XFcObjectDataQueue *create(INT32 aMaxSize, INT aBufferSize);


    //! Packs data and sets it as send.
    /*!
     * \param aPacket object data packet.
     * \param aSeqNum sequence number.
     */
    void createUnsentMultiPacket(XFcObjectDataPacket *aPacket, INT32 aSeqNum, INT aStyle);


    //! Gets first unsent alone going packet and set it's as send.
    /*!
     * \param aPacket object data packet.
     * \param aSeqNum sequence number.
     */
    void createUnsentOnePacket(XFcObjectDataPacket *aPacket, INT32 aSeqNum, INT aStyle);

    //! Packs data and sets it as send.
    /*!
     * \param aPacket object data packet.
     * \param aSeqNum sequence number.
     */
    void createUnsentAutoPacket(XFcObjectDataPacket *aPacket, INT32 aSeqNum, INT aStyle);

    //! Resets queue, this does not delete packets. Sets given seqnum packets as unsend.
    void resetQueue(INT32 aStatus);

    //! Resets queue, this does not delete packets. Sets all packets as unsend.
    void reset();


    //! Deletes queue.
    void deleteQueue();


    //! Deletes sent non guaranteed packets.
    void deleteNonGuaranteedSent();


    //! Removes packets by seqnum.
    /*!
     * \param aSeqNum sequence number.
     */
    void removeSeqNum(INT32 aSeqNum);


    //! Removes packet by index.
    /*!
     * \param aIndex list index.
     */
    void removeByIndex(INT32 aIndex);


    //! Returns first index of given seqnum.
    /*!
     * \param aSeqNum sequency number.
     * \return list index.
     */
    INT32 getFirstIndex(INT32 aSeqNum);


    //! Return first index of given seqnum.
    /*!
     * \return list index.
     */
    INT32 getFirstNonguaranteedIndex();


    //! Is queue full.
    /*!
     * \return 1 if queue is full, or 0 if not.
     */
    INT32 isFull();


    //! Is queue empty.
    /*!
     * \return 1 if queue is empty, or 0 if not.
     */
    INT32 isEmpty();


    //! Sets queue size.
    /*!
     * \param aQueueSize queue size.
     */
    void setQueueSize(UINT32 aQueueSize);


    //! Updates send priority.
    void updatePriority();

    //! Virtual destructor.
    virtual ~XFcObjectDataQueue();

};


#endif // !XFCOBJECTDATAQUEUE_H_INCLUDED

