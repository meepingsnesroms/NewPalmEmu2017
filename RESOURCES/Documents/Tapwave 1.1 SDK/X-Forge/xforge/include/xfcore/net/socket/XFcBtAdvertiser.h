/*! \file -*-C++-*-
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Bluetooth advertise
 *
 * $Id: XFcBtAdvertiser.h,v 1.7 2003/08/12 13:33:49 lars Exp $
 * $Date: 2003/08/12 13:33:49 $
 * $Revision: 1.7 $
 */
#ifndef XFCBTADVERTISER_H_INCLUDED
#define XFCBTADVERTISER_H_INCLUDED

#include <xfcore/net/socket/XFcAdvertiser.h>

class XFcBtAddress;
class XFcAddress;
class XFcHostEntry;


class XFcBtAdvertiser : public XFcAdvertiser
{
private:

    INT mAvailability;    

protected:

    XFcBtAdvertiser();

    INT init(const XFcAddress &aAddress, const CHAR8 *aMessage, INT32 aMessageLength);

    INT init(const CHAR8 *aMessage, INT32 aMessageLength);

    INT init(const XFcHostEntry &aHostEntry);

    INT init();

public:

    //! Holds advertice receive address, this address can be used for game play.
    XFcHostEntry *mHostEntry;

    //! Virtual destructor.
    virtual ~XFcBtAdvertiser();

    //! Creates bt advertiser with address and message.
    static XFcBtAdvertiser * create(const XFcAddress &aAddress, const CHAR8 *aMessage, INT32 aMessageLength);
    
    //! Creates bt advertiser with message.
    static XFcBtAdvertiser * create(const CHAR8 *aMessage, INT32 aMessageLength);
    
    //! Creates bt advertiser with bt hostentry.
    static XFcBtAdvertiser * create(const XFcHostEntry &aHostEntry);

    //! Creates empty bt advertiser, availability is set to fully used.
    static XFcBtAdvertiser * create();

    //! Sets availability status.
    /*!
     * \param 0x00 means fully used and 0xff fully unused.
     */
    void setAvailability(INT32 aAvailable);

    //! Gets availability.
    INT32 getAvailability() const;

    //! Test if address is set.
    XFCIMPORT virtual INT isAddress() const;

};


#endif // !XFCBTADVERTISER_H_INCLUDED

