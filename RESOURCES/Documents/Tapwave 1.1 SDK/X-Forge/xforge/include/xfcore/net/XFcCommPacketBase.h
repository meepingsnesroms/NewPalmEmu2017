/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Base for communication packet
 *
 * $Id: XFcCommPacketBase.h,v 1.9 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.9 $
 */

#ifndef XFCCOMMPACKETBASE_H_INCLUDED
#define XFCCOMMPACKETBASE_H_INCLUDED


//! XFcCommPacketBase is base class for communication packet.
/*!
 * Its purpose is only hold buffer size and buffer max size information.
 */
class XFcCommPacketBase
{
protected:

    //! Packet size.
    INT32 mSize;

    //! Max packet size.
    INT32 mMaxSize;

    //! Protected constructor.
    XFcCommPacketBase();

public:

    //! Gets packet size.
    /*!
     * \return size of buffer in bytes.
     */
    virtual INT32 getSize();

    //! Sets packet size.
    /*!
     * \param aSize size of buffer in bytes.
     */
    virtual void setSize(INT32 aSize);

    //! Sets max packet size.
    /*!
     * \param aSize max size of allocated buffer in bytes.
     */
    virtual void setMaxSize(INT32 aSize);

    //! Gets max packet size.
    /*!
     * \return max size of allocated buffer.
     */
    virtual INT32 getMaxSize(); 

    //! Virtual destructor.
    virtual ~XFcCommPacketBase();
};


#endif // !XFCCOMMPACKETBASE_H_INCLUDED

