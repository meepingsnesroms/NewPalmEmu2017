/*!
 * \file
 * X-Forge Engine <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Default implementation for a inetcommunication manager.
 *
 * $Id: XFuInetNetwork.h,v 1.4 2003/10/08 11:08:34 slehti Exp $
 * $Date: 2003/10/08 11:08:34 $
 * $Revision: 1.4 $
 */

#ifndef XFUINETNETWORK_H_INCLUDED
#define XFUINETNETWORK_H_INCLUDED

#include <xfcore/net/XFcUnknownSender.h>
#include <xfcore/net/XFcClientLost.h>
#include <xfcore/net/socket/XFcInetAddress.h>
#include <xfcore/net/XFcCommunicationConstants.h>
#include <xfcore/net/XFcDeviceDiscovery.h>
#include <xfcore/XFcHashtable.h>
#include <xfutil/XFuDynamicArray.h>
#include <xfutil/XFuNetwork.h>


class XFuSerializable;
class XFcCommunicationScheduler;
class XFcUnknownSender;
class XFcClientLost;
class XFcDataReceiver;
class XFcObjectDataFrame;
class XFcInetCommService;
class XFcHostEntry;
class XFcHostResolver;
class XFcAdvertiser;
class XFcInetHandler;
class XFcInetClientWin;
class XFcInetHostResolver;
class XFcInetCommService;
class XFcName;

//! Default implementation for a communication manager.

class XFuInetNetwork : public XFuNetwork,
		       public XFcUnknownSender,
		       public XFcClientLost,
		       public XFcDeviceDiscovery
{
private:

     //! Pointer to array of communication event handlers.
    XFuDynamicArray<XFuNetworkEventHandler*> *mNetworkEventHandlers;

    //! Pointer to the communication scheduler.
    XFcCommunicationScheduler *mCommunicationScheduler;

    //! Pointer to the communication handler.
    XFcInetHandler *mCommunicationHandler;

    //! Pointer to the default data receiver.
    XFcDataReceiver *mDefaultDataReceiver;

    //! Id of the communication handler.
    INT32 mCommunicationHandlerId;

    //! Array of pointers to clients.
    XFcHashtable<UINT32, XFcInetClientWin *> mClients;

    //! Maximum number of clients.
    INT32 mMaxClients;

    //! Game token that is checked before new clients are allowed to connect.
    UINT32 mAcceptGameToken;

    //! Holds status of advertiser device query.
    INT mAdvertiserStatus;

    //! Holds inet server port.
    UINT16 mGamePort;

    //! Pointer to the communication service.
    XFcInetHostResolver *mHostResolver;

    //! Pointer to the inet communication service.
    XFcInetCommService *mCommService;

protected:

    //! Protected constructor.
    XFuInetNetwork();

    //! Reserves memory for the client array (mClients) and initializes all the client pointers to NULL.
    virtual void initClients(INT32 aMaxClients);

    //! Cleanup of all clients.
    virtual void deleteAllClients();

     //! Initializes default communication manager specific items that would normally be in the constructor.
    virtual INT init();

public:

    //! Static constructor.
    static XFuInetNetwork * create();

    //! Destructor.
    virtual ~XFuInetNetwork();

    //! Resets the communication manager.
    virtual void reset();

    //! Runs the communication scheduler.
    virtual void runCommunicationScheduler();

    //! Connection lost handler (XFuClientLost) (callback).
    virtual void clientLost(INT32 aClientId);

    //! Handle data from an unknown client (callback).
    virtual INT handleSender(const void *aAddress, const CHAR8 *aData, INT32 aLen);

    //! Enables the inet communication handler and opens it for service.
    /*! Use port 0 for random port.
     *  Default speed is one of the XFuNET_CONNECTION_SPEED values (see XFcClientCommWin.h)
     */
    virtual INT enableService(INT32 aMaxClients, UINT16 aPort, INT32 aDefaultSpeed);

    //! Closes the currently active service (communication handler).
    virtual void closeService();

    //! Returns the specified client.
    virtual XFcClientCommWin * getClient(INT32 aClientId);

    //! Adds a client with the specific address.
    /*! \return The client id or XFCNET_CLIENTADD_ERROR if failed.
     */
    virtual INT32 addClient(XFcAddress *aAddress, INT32 aTimeoutTime = 15000);

    //! Removes the specified client.
    virtual void removeClient(INT32 aClientId);

    //! Removes all clients.
    virtual void removeAllClients();

    //! Returns the game token that is checked before new clients are allowed to connect.
    virtual UINT32 getAcceptGameToken();

    //! Sets the game token that is checked before new clients are allowed to connect.
    virtual void setAcceptGameToken(UINT32 aAcceptGameToken);

    //! Sends a game connection packet.
    virtual void sendGameConnectPacket(INT32 aClientId, UINT32 aGameToken);

    //! Returns a pointer to the default data receiver.
    virtual XFcDataReceiver * getDefaultDataReceiver();

    //! Sets the default data receiver.
    virtual void setDefaultDataReceiver(XFcDataReceiver *aReceiver);

    //! Returns the specified data receiver.
    virtual XFcDataReceiver * getDataReceiver(UINT32 aId);

    //! Adds a new data receiver.
    virtual INT addDataReceiver(UINT32 aId, XFcDataReceiver *aReceiver);

    //! Removes a data receiver.
    virtual XFcDataReceiver * removeDataReceiver(UINT32 aId);

    //! Returns the round trip time for the specified client.
    virtual INT32 getRoundTripTime(INT32 aClientId);

    //! Get packet frame.
    virtual XFcObjectDataFrame * getPacketFrame(INT32 aClientId, XFCNET_MESSAGE_SLOT aSlot);

    //! Get recent state frame.
    virtual XFcObjectDataFrame * getRecentStateFrame(INT32 aClientId, INT32 aRecentId);

    //! Remove recent state frame.
    virtual void removeRecentStateFrame(INT32 aClientId, INT32 aRecentId);

    //! Sends a serializable object to the specified client.
    virtual INT32 send(INT32 aClientId, UINT32 aReceiverId, XFCNET_MESSAGE_SLOT aSlot, XFuSerializable *aSerializable);

    //! Sends a serializable object to the specified client as a recent state packet.
    virtual INT32 sendRecentState(INT32 aClientId, UINT32 aReceiverId, INT32 aRecentId, XFuSerializable *aSerializable);

    //! Adds a communication event handler.
    virtual void addEventHandler(XFuNetworkEventHandler *aHandler);

    //! Removes a communication event handler.
    virtual void removeEventHandler(XFuNetworkEventHandler *aHandler);

    //! Removes all communication event handlers.
    virtual void removeAllEventHandlers();

    //! Cretes advertiser for opened service.
    /*!
     * \param aMessage message to be sent to the receiver of the advertise, or NULL to use the default message.
     * \param aAdvertisePort port where advertiser is created and for bt its 0.
     * \return 1 if advertiser service starts successfully, or XFCNET_ERROR otherwise.
     */
    virtual INT startAdvertiser(const CHAR8 *aMessage, UINT16 aAdvertisePort);

    //! Stops the advertiser service.
    virtual void stopAdvertiser();

    //! Starts server device discovery.
    /*!
     * \param aMessage message to be sent to the receiver of the advertise, or NULL to use the default message.
     * \param aAdvertisePort port where advertiser is created and for bt its 0.
     * \return 1 if discovery starts successfully, or XFCNET_ERROR otherwise.
     */
    virtual INT startServerDiscovery(const CHAR8 *aMessage, UINT16 aAdvertisePort);

    //! Stops device discovery.
    virtual void stopServerDiscovery();

    //! Inherited from XFcDeviceDiscovery.
    virtual void deviceDiscovery(const XFcLinkedList<XFcAdvertiser *> &aAdvertiser);
    //! Inherited from XFcDeviceDiscovery.
    virtual void deviceDiscovery(const XFcLinkedList<XFcHostEntry *> &) { return; }

    //! Gets device local name.
    virtual INT deviceLocalName(XFcName &aName);
};

#endif // !XFUINETNETWORK_H_INCLUDED
