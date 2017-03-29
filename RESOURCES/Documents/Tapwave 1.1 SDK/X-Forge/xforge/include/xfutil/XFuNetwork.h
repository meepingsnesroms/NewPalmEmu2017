/*!
 * \file
 * X-Forge Engine <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Base class for all communication managers for game graphs.
 *
 * $Id: XFuNetwork.h,v 1.3 2003/10/02 11:43:01 slehti Exp $
 * $Date: 2003/10/02 11:43:01 $
 * $Revision: 1.3 $
 */

#ifndef XFUNETWORK_H_INCLUDED
#define XFUNETWORK_H_INCLUDED

class XFuNetworkEventHandler;
class XFcDataReceiver;
class XFcAddress;

#include <xfcore/net/XFcCommunicationConstants.h>


//! Base class for all network handlers.
class XFuNetwork
{

public:

    //! Virtual destructor.
    virtual ~XFuNetwork() {}

    //! Closes the currently active service (communication handler).
    virtual void closeService() = 0;

    //! Returns the specified client.
    virtual XFcClientCommWin * getClient(INT32 aClientId) = 0;

    //! Adds a client with the specific address.
    /*! \return The client id or XFCNET_CLIENTADD_ERROR if failed.
     */
    virtual INT32 addClient(XFcAddress *aAddress, INT32 aTimeoutTime = 15000) = 0;

    //! Removes the specified client.
    virtual void removeClient(INT32 aClientId) = 0;

    //! Removes all clients.
    virtual void removeAllClients() = 0;

    //! Returns a pointer to the default data receiver.
    virtual XFcDataReceiver * getDefaultDataReceiver() = 0;

    //! Sets the default data receiver.
    virtual void setDefaultDataReceiver(XFcDataReceiver *aReceiver) = 0;

    //! Returns the specified data receiver.
    virtual XFcDataReceiver * getDataReceiver(UINT32 aId) = 0;

    //! Adds a new data receiver.
    virtual INT addDataReceiver(UINT32 aId, XFcDataReceiver *aReceiver) = 0;

    //! Removes a data receiver.
    virtual XFcDataReceiver * removeDataReceiver(UINT32 aId) = 0;

    //! Get packet frame.
    virtual XFcObjectDataFrame * getPacketFrame(INT32 aClientId, XFCNET_MESSAGE_SLOT aSlot) = 0;

    //! Get recent state frame.
    virtual XFcObjectDataFrame * getRecentStateFrame(INT32 aClientId, INT32 aRecentId) = 0;

    //! Remove recent state frame.
    virtual void removeRecentStateFrame(INT32 aClientId, INT32 aRecentId) = 0;
    
    //! Adds a communication event handler.
    virtual void addEventHandler(XFuNetworkEventHandler *aHandler) = 0;

    //! Removes a communication event handler.
    virtual void removeEventHandler(XFuNetworkEventHandler *aHandler) = 0;

    //! Removes all communication event handlers.
    virtual void removeAllEventHandlers() = 0;

    //! Runs the communication scheduler.
    virtual void runCommunicationScheduler() = 0;
    
};


#endif // !XFUNETWORK_H_INCLUDED

