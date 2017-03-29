/*!
 * \file
 * X-Forge Engine <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Interface for receiving communication events.
 *
 * $Id: XFuNetworkEventHandler.h,v 1.2 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.2 $
 */

#ifndef XFUNETWORKEVENTHANDLER_H_INCLUDED
#define XFUNETWORKEVENTHANDLER_H_INCLUDED

class XFcHostEntry;


//! Interface for receiving communication events.
class XFuNetworkEventHandler
{

public:

    //! Virtual destructor.
    virtual ~XFuNetworkEventHandler() {}

    //! Gets called when a new client has been accepted.
    virtual void handleClientAccepted(INT32 /* aClientId */) {}

    //! Gets called when the connection to a client has been lost.
    virtual void handleClientLost(INT32 /* aClientId */) {}

    //! Gets called when the device list is received.
    virtual void handleDeviceDiscovered(const XFcHostEntry * /* aHostEntry */) {}

    //! Gets called when the advertise list is received.
    virtual void handleAdvertiseDiscovered(const XFcAdvertiser * /* aAdvertiser */) {}

};

#endif // !XFUNETWORKEVENTHANDLER_H_INCLUDED

