/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Encapsulates byte buffer usage.
 *            
 * $Id: XFcObjectDataBuffer.h,v 1.9 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.9 $
 */

#ifndef XFCOBJECTDATABUFFER_H_INCLUDED
#define XFCOBJECTDATABUFFER_H_INCLUDED


//! XFcObjectDataBuffer encapsulates byte buffer usage.
class XFcObjectDataBuffer 
{
protected:

    //! Holds packet data size.
    INT32 mDataPacketSize;
    
    //! Holds packet data.
    CHAR8 *mDataPacket;

    //! Holds buffer max size.
    INT32 mMaxBufferSize;

    //! Initializes object.
    /*!
     * \param aMaxBufferSize max buffer size.
     * \return 1 if successful, or 0 otherwise.
     */
    INT32 init(INT32 aMaxBufferSize);

    //! Protected constructor.
    XFcObjectDataBuffer();

public:

    //! Static constructor.
    /*!
     * \param aMaxBuffer max buffer size.
     * \return new object if successful, or NULL if unsuccessful.
     */
    static XFcObjectDataBuffer *create(INT32 aMaxBufferSize);
    

    //! Locks the buffer.
    /*!
     * \return pointer to locked buffer.
     */
    void * lock();


    //! Unlocks the buffer.
    void unlock();


    //! Sets packet size.
    /*!
     * \param aPacketSize packet size.
     */
    void setPacketSize(INT32 aPacketSize);

    //! Appends packet size.
    /*! 
     * \param aPacketSize append value.
     */
    void appendPacketSize(INT32 aPacketSize);

    //! Gets the packet size.
    /*!
     * \return packet size inside buffer.
     */
    INT32 sizeofPacket() const;


    //! Gets buffer max size.
    /*! 
     * \return size of locked buffer.
     */
    INT32 sizeofBuffer() const;


    //! Virtual destructor.
    /*! Releases all allocated buffers.
     */
    virtual ~XFcObjectDataBuffer();

};


#endif // !XFCOBJECTDATABUFFER_H_INCLUDED

