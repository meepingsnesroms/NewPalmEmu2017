/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Inet advertise
 *
 * $Id: XFcInetAdvertiser.h,v 1.10 2003/08/12 13:33:50 lars Exp $
 * $Date: 2003/08/12 13:33:50 $
 * $Revision: 1.10 $
 */
#ifndef XFCINETADVERTISER_H_INCLUDED
#define XFCINETADVERTISER_H_INCLUDED

#include <xfcore/net/socket/XFcAdvertiser.h>

class XFcHostEntry;


#define XFCNET_MAX_ELEMET_ID 0x05


//! Inet advertiser.
/*!
 * Protocol description:
 * \li id is always one octet long.
 * \li 0x02 header element, element length will follow.
 * \li 0x03 port element, element length is 2 octets.
 * \li 0x04 data element, element length will follow.
 * \li Length field is always 1 octet. One field can be only 255 octets long.  
 * [0x02][0x06][HEADER][0x03][0xffff][0x04][0x04][DATA]
 */
class XFCDLLEXPORT XFcInetAdvertiser : public XFcAdvertiser
{
private:
    
    CHAR8 mTmpMessage[XFC_MAXBUFFERSIZE];

    INT32 mTmpLength;

protected:

    /*
    class XFcAdvertiseElement
    {
    private:

        CHAR8 *mElemStart;

    public:

        XFcAdvertiseElement();

        void setElementStart(CHAR8 *aElemStart);

        UINT8 getId();
        void setId(UINT8 aId);
        UINT8 getLength();
        void setLength(UINT8 aLength);

        const CHAR8 * getData();
        INT setData(const CHAR8 *aData);

        ~XFcAdvertiseElement();

    };
    */

    //! Protected constructor.
    XFcInetAdvertiser();

    INT init(const XFcAddress &aAddress, const CHAR8 *aMessage, INT32 aMessageLength);

    INT init(const CHAR8 *aMessage, INT32 aMessageLength);

    INT init(const XFcHostEntry &aHostEntry);

    INT init();

    //! Returns pointer to beginning of the data chunck.
    CHAR8 * getElement(CHAR8 *aBuffer, UINT8 aElement);

    const CHAR8 * getElement(const CHAR8 *aBuffer, UINT8 aElement) const;
 
    INT32 getElementLength(const CHAR8 *aBuffer, UINT8 aElement) const;

    INT32 addElement(CHAR8 *aElement, UINT8 aElementLength, UINT8 aElementId);

public:

    //! Holds advertice receive address.
    XFcHostEntry *mHostEntry;

    XFCIMPORT virtual ~XFcInetAdvertiser();

    XFCIMPORT static XFcInetAdvertiser * create(const XFcAddress &aAddress, const CHAR8 *aMessage,
                                                INT32 aMessageLength);
    
    XFCIMPORT static XFcInetAdvertiser * create(const CHAR8 *aMessage, INT32 aMessageLength);
    
    XFCIMPORT static XFcInetAdvertiser * create(const XFcHostEntry &aHostEntry);

    XFCIMPORT static XFcInetAdvertiser * create();

    //! Sets game play port.
    XFCIMPORT virtual void setGamePort(UINT16 aGamePort);

    //! Gets game play port.
    XFCIMPORT virtual UINT16 getGamePort() const;

    //! Sets message header, e.g. "X-Forge Game: GeoPod".
    XFCIMPORT virtual INT setMessageHeader(const CHAR8 *aHeader, INT32 aLength);
    
    //! Gets message header, e.g. "X-Forge Game: GeoPod".
    XFCIMPORT virtual void getMessageHeader(CHAR8 *aHeader, INT32 &aLength) const;
    
    //! Sets other data to message.
    XFCIMPORT virtual INT setMessageData(const CHAR8 *aData, INT32 aLength); 
    
    //! Gets other message data.
    XFCIMPORT virtual void getMessageData(CHAR8 *aData, INT32 &aLength) const;

    //! Test if address is set.
    XFCIMPORT virtual INT isAddress() const;

};


#endif // !XFCINETADVERTISER_H_INCLUDED

