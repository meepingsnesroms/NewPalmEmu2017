/*!
 * \file
 * X-Forge Engine <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Default implementation for a Bluetooth communication manager.
 *
 * $Id: XFuBluetoothMultiNetwork.h,v 1.5 2003/10/02 11:43:01 slehti Exp $
 * $Date: 2003/10/02 11:43:01 $
 * $Revision: 1.5 $
 */

#ifndef XFUBLUETOOTHMULTINETWORK_H_INCLUDED
#define XFUBLUETOOTHMULTINETWORK_H_INCLUDED

#include <xfcore/net/XFcUnknownSender.h>
#include <xfcore/net/XFcClientLost.h>
#include <xfcore/net/socket/XFcAddress.h>
#include <xfcore/net/XFcCommunicationConstants.h>
#include <xfcore/net/XFcDeviceDiscovery.h>
#include <xfutil/XFuDynamicArray.h>


class XFuSerializable;
class XFcCommunicationScheduler;
class XFcUnknownSender;
class XFcClientLost;
class XFcDataReceiver;
class XFcObjectDataFrame;
class XFcBtCommService;
class XFcHostEntry;
class XFcBtHostResolver;
class XFcAdvertiser;
class XFcBtClientWin;
class XFcBtServerSearch;
class XFcBtAddress;
class XFcBtHandler;
class XFcName;

class XFuBluetoothMultiNetwork : public XFuNetwork,
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
    XFcBtHandler *mCommunicationHandler;

    //! Holds pointer to the Bluetooth communication services.
    XFcBtCommService *mCommunicationService;

    //! Pointer to the default data receiver.
    XFcDataReceiver *mDefaultDataReceiver;

    //! Holds pointer to bt server search.
    XFcBtServerSearch *mBtServerSearch;

    //! Holds pointer to bt host resolver.
    XFcBtHostResolver *mHostResolver;

    //! Id of the communication handler.
    INT32 mCommunicationHandlerId;

    //! Array of pointers to clients.
    XFcHashtable<UINT32, XFcBtClientWin *> mClients;

    //! Holds ClientId, only one client is supported for now.
    INT32 mSlaveClientId;

    //! Game token that is checked before new clients are allowed to connect.
    UINT32 mAcceptGameToken;

    //! Holds game port.
    UINT16 mGamePort;

    //! Holds bluetooth communication service, needed for bluetooth SDP and first free server port query.
    XFcBtCommService *mService;

    //! Holds bluetooth uuid for this game.
    XFcBtUUID mUUID;
protected:

    //! Deletes all clients.
    virtual void deleteAllClients();

    //! Protected constructor.
    XFuBluetoothMultiNetwork();

    //! Initializes this Bluetooth communication manager.
    INT init();

    //! Initializes enable service.
    INT initEnable(UINT16 aPort, INT aIsServer);

public:

    //! Static constructor.
    static XFuBluetoothMultiNetwork * create();

    //! Enables the Bluetooth communication handler and opens it for service.  Opens device as bluetooth slave.
    /*!
     * \param aPort is clients BT-Slave port. If port is set to 0 the port is selected by system. 
     */
    virtual INT enableClientService(UINT16 aPort);

    //! Enables the Bluetooth communication handler and opens it for service. Opens device as bluetooth master.
    virtual INT enableHostService();

    //! Closes the currently active service (communication handler).
    virtual void closeService();

    //! Resets the communication manager.
    virtual void reset();

    //! Runs the communication scheduler.
    virtual void runCommunicationScheduler();

    //! Connection lost handler (XFuClientLost) (callback).
    virtual void clientLost(INT32 aClientId);

    //! Adds a client with the specific address.
    /*! \return The client id or XFCNET_CLIENTADD_ERROR if failed.
     */
    virtual INT32 addClient(XFcAddress *aAddress, INT32 aTimeoutTime = 15000);

    //! Returns the specified client.
    virtual XFcClientCommWin * getClient(INT32 aClientId);

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

    //! Returns the specified data receiver.
    virtual XFcDataReceiver * getDataReceiver(UINT32 aId);

    //! Adds a new data receiver.
    virtual INT addDataReceiver(UINT32 aId, XFcDataReceiver *aReceiver);

    //! Sets the default data receiver.
    virtual void setDefaultDataReceiver(XFcDataReceiver *aReceiver);

    //! Removes a data receiver.
    virtual XFcDataReceiver * removeDataReceiver(UINT32 aId);

     //! Handle data from an unknown client (callback).
    virtual INT handleSender(const void *aAddress, const CHAR8 *aData, INT32 aLen);

    //! Get packet frame.
    virtual XFcObjectDataFrame * getPacketFrame(INT32 aClientId, XFCNET_MESSAGE_SLOT aSlot);

    //! Get recent state frame.
    virtual XFcObjectDataFrame * getRecentStateFrame(INT32 aClientId, INT32 aRecentId);

    //! Remove recent state frame.
    virtual void removeRecentStateFrame(INT32 aClientId, INT32 aRecentId);

    //! Returns the round trip time for the specified client.
    virtual INT32 getRoundTripTime(INT32 aClientId);

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

    //! Stops device discovery.
    virtual void stopDeviceDiscovery();

    //! Stops server discovery.
    virtual void stopClientDiscovery();

    //! Stops server advertiser.
    virtual void stopAdvertiser();

    //! Starts device discovery.
    virtual INT startDeviceDiscovery();

    //! Starts server discovery, if address is NULL engine will search througth all available bt devices.
    virtual INT startClientDiscovery(const XFcBtUUID &aUuid, const XFcBtAddress *aAddress);

    //! Starts advertiser, if message is NULL default message is used.
    virtual INT startAdvertiser(const XFcBtUUID &aUuid, const CHAR8 *aMessage);

    //! Callback for device discovery.
    virtual void deviceDiscovery(const XFcLinkedList<XFcHostEntry *> &aHostEntry);
    
    //! Callback for server discovery.
    virtual void deviceDiscovery(const XFcLinkedList<XFcAdvertiser *> &aAdvertiser);

    //! Gets device local name 
    virtual INT deviceLocalName(XFcName &aName);
    
    //! Virtual destructor. Closes all open tasks and deletes all created objects.
    virtual ~XFuBluetoothMultiNetwork();

};


#endif // !XFUBLUETOOTHMULTINETWORK_H_INCLUDED

