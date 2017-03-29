/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Base for advertise
 *
 * $Id: XFcAdvertiser.h,v 1.9 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.9 $
 */

#ifndef XFCADVERTICER_H_INCLUDED
#define XFCADVERTICER_H_INCLUDED


static const UINT32 XFC_MAXBUFFERSIZE = 512;


//! XFcAdvertiser is base class for service adverticement.
/*! 
 * Its used to hold advertice information that is needed
 * to advertice used server.
 */
class XFCDLLEXPORT XFcAdvertiser
{
private:

    //! Holds advertiser type.
    INT mType;

protected:

    //! Holds game port, will advertise this as game server port.
    UINT16 mGamePort;

    //! Holds advertise port, inet advertiser can be found in this port.
    UINT16 mAdvertisePort;

    //! Initialises advertiser with advertiser type.
    INT init(INT aType);

    //! Protected constructor.
    XFCIMPORT XFcAdvertiser();

    //! Holds header length.
    INT32 mHeaderLength;

    //! Holds data length.
    INT32 mDataLength;

    
public:

    //! Virtual destructor.
    XFCIMPORT virtual ~XFcAdvertiser();

    //! Gets advertiser type.
    XFCIMPORT INT getType() const;

    //! Advertise message length.
    XFCIMPORT INT32 mMessageLength;

    //! Advertise message.
    XFCIMPORT CHAR8 mMessage[XFC_MAXBUFFERSIZE];

    //! Set game play port.
    XFCIMPORT virtual void setGamePort(UINT16 aGamePort);

    //! Get game play port.
    XFCIMPORT virtual UINT16 getGamePort() const;

    //! Sets message header, e.g. "X-Forge Game: GeoPod".
    XFCIMPORT virtual INT setMessageHeader(const CHAR8 *aHeader, INT32 aLength);

    //! Gets message header, e.g. "X-Forge Game: GeoPod".
    XFCIMPORT virtual void getMessageHeader(CHAR8 *aHeader, INT32 &aLength) const;

    //! Sets other data to message.
    XFCIMPORT virtual INT setMessageData(const CHAR8 *aData, INT32 aLength); 

    //! Gets other message data.
    XFCIMPORT virtual void getMessageData(CHAR8 *aData, INT32 &aLength) const;
    
    //! Set advertiser port, not used with bt.
    XFCIMPORT void setAdvertisePort(UINT16 aAdvertisePort);

    //! Test if address is set.
    XFCIMPORT virtual INT isAddress() const; 
    
    //! Get advertiser port.
    XFCIMPORT UINT16 getAdvertisePort() const;

};


#endif // !XFCADVERTICER_H_INCLUDED

