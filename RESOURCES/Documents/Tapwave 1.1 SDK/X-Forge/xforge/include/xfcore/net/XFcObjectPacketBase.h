/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd       
 *
 * \brief Sendable packet buffer 
 *
 * $Id: XFcObjectPacketBase.h,v 1.10 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.10 $
 */

#ifndef XFCOBJECTPACKETBASE_H_INCLUDED
#define XFCOBJECTPACKETBASE_H_INCLUDED


class XFcCommPacketBase;

//! XFcObjectPacketBase holds sendable packet buffer and offers header and packet interface to it.
class XFcObjectPacketBase  
{
protected:

    //! Holds data pointer.
    CHAR8 *mMemoryBlock;

    //! Holds max buffer size.
    INT32 mBufferSize;

    //! Holds header size.
    INT32 mHeaderSize;

    //! Holds packet size.
    INT32 mPacketSize;

    //! Holds data block size.
    INT32 mDataBlockSize;

    //! Holds send status.
    INT32 mSendStatus;

    //! Initializes class.
    /*!
     * \param aMaxSize max size of buffer.
     */
    INT32 initObjectBase(INT32 aMaxSize);
    
    //! Protected constructor.
    XFcObjectPacketBase();

public:

    //! Static constructor.
    /*!
     * \param aMaxSize max size of buffer.
     * \return new object if successful, or NULL if unsuccessful.
     */
    static XFcObjectPacketBase * create(INT32 aMaxSize);

    //! Resets memory block.
    void resetMemoryBlock();
    
    //! Sets packet size.
    /*!
     * \param aSize packet size.
     */
    void setPacketSize(INT32 aSize);

    //! Sets header size.
    /*!
     * \param aSize header size.
     */
    void setHeaderSize(INT32 aSize);

    //! Returns header size.
    /*!
     * \return header size.
     */
    INT32 getHeaderSize() const;

    //! Returns packet size.
    /*!
     * \return packet size.
     */
    INT32 getPacketSize() const;

    //! Sets data block size.
    /*!
     * \param aSize data block size.
     */
    void setDataBlockSize(INT32 aSize);

    //! Locks header.
    /*!
     * \return pointer to beginning of header.
     */
    void * lockHeader();

    //! Unlocks header.
    void unlockHeader();

    //! Locks packet.
    /*!
     * \return pointer to beginning of packet
     */
    void * lockPacket();

    //! Unlocks packet.
    void unlockPacket();

    //! Gets max size of data block.
    /*!
     * \return max size of data block.
     */
    INT32 getDataBlockMaxSize() const;

    //! Gets memory block.
    /*!
     * \return pointer to beginning of buffer.
     */
    void * lock(); 

    //! Unlocks memory block.
    void unlock();
    
    //! Gets data block size.
    /*!
     * \return data block size in bytes.
     */
    INT32 getDataBlockSize() const;

    //! Gets memory block size.
    /*!
     * \return memory block size in bytes.
     */
    INT32 getMemoryBlockSize() const;

    //! Sets send status.
    /*!
     * \param aValue send status.
     */
    void sendStatus(INT aValue);

    //! Gets send status.
    /*!
     * \return send status.
     */
    INT32 getSendStatus() const;

    //! Virtual destructor.
    virtual ~XFcObjectPacketBase();

};
    

#endif // !XFCOBJECTPACKETBASE_H_INCLUDED

