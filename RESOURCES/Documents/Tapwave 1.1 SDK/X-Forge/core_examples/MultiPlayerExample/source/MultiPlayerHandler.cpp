/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: MultiPlayerHandler.cpp,v 1.2.4.1 2003/10/31 13:27:51 slehti Exp $
 * $Date: 2003/10/31 13:27:51 $
 * $Revision: 1.2.4.1 $
 */

#include <xforge.h>

#include <xfcore/net/socket/XFcInetHostResolver.h>
#include <xfcore/net/XFcClientCommWin.h>
#include <xfcore/net/socket/XFcBtAddress.h>
#include <xfcore/net/socket/XFcHostEntry.h>
#include <xfcore/net/socket/XFcInetHostEntry.h>
#include <xfcore/net/socket/XFcBtHostEntry.h>
#include <xfcore/net/socket/XFcInetAdvertiser.h>
#include <xfcore/net/socket/XFcBtAdvertiser.h>
#include <xfcore/net/socket/XFcBtUUID.h>
#include <xfcore/net/XFcCommunicationHandler.h>

#include "ClientListEntry.h"
#include "MultiPlayerExample.h"
#include "MultiPlayerHandler.h"


MultiPlayerHandler * MultiPlayerHandler::create(XFuNetwork *aNetwork)
{
    MultiPlayerHandler *mph = new MultiPlayerHandler();
    if (mph)
    {
        mph->setState(MP_STATE_INITIALIZED);
        mph->setRole(MP_ROLE_UNKNOWN);
        mph->resetClientStates();
        mph->mClientList = XFuDynamicArray<ClientListEntry*>::create();
        mph->mClientListMutex = XFcMutex::create();
#if 1
#ifdef NETWORK_INET
        mph->mNetwork = (XFuInetNetwork *)aNetwork;
#else
        mph->mNetwork = (XFuBluetoothMultiNetwork *)aNetwork;
#endif
#endif
    }
    return mph;

}


MultiPlayerHandler::MultiPlayerHandler()
{
    
}

MultiPlayerHandler::~MultiPlayerHandler()
{
    delete mClientList;
    delete mClientListMutex;
}


// Starts the session in initiator role
void MultiPlayerHandler::initAsInitiator()
{

    close();

    clearClientList();

    mScheduledCloseTick = -1;
    mGameConnectTick = -1;
    mGameStateUpdateTick = -1;

    setRole(MP_ROLE_INITIATOR);
    setState(MP_STATE_INITIALIZED);

    getGameState(getPlayerId())->setLedState(0);

    mNetwork->addEventHandler(this);
    mNetwork->addDataReceiver(MP_DATA_RECEIVER_ID, this);

    mNetwork->setAcceptGameToken(MP_INVALID_GAME_TOKEN);

    // start service and advertiser discovery

#ifdef NETWORK_INET
    mNetwork->enableService(MP_MAX_CLIENTS, 0, XFcClientCommWin::XFCNET_WLAN_2MB);
    mNetwork->startServerDiscovery(NULL, MP_INET_ADVERTISER_PORT);
#else
    mNetwork->enableHostService();
    XFcBtUUID uuid(0x4dba5eb0, 0xeb5546c1, 0x9a080a32, 0x948669d5);
    mNetwork->startClientDiscovery(uuid, NULL);
#endif

}


// Starts the session in participant role
void MultiPlayerHandler::initAsParticipant()
{

    close();

    clearClientList();

    mScheduledCloseTick = -1;
    mGameConnectTick = -1;
    mGameStateUpdateTick = -1;

    setRole(MP_ROLE_PARTICIPANT);
    setState(MP_STATE_INITIALIZED);

    mNetwork->addEventHandler(this);
    mNetwork->addDataReceiver(MP_DATA_RECEIVER_ID, this);

    mNetwork->setAcceptGameToken(MP_GAME_TOKEN);

    // start service and advertiser

#ifdef NETWORK_INET
    mNetwork->enableService(1, MP_INET_PORT, XFcClientCommWin::XFCNET_WLAN_2MB);
    mNetwork->startAdvertiser(NULL, MP_INET_ADVERTISER_PORT);
#else
    mNetwork->enableClientService(MP_BT_PORT);
    
    XFcBtUUID uuid(0x4dba5eb0, 0xeb5546c1, 0x9a080a32, 0x948669d5);
    mNetwork->startAdvertiser(uuid, NULL);
#endif

}


// Completely close the session and reset the communication manager
void MultiPlayerHandler::close()
{
    mNetwork->setAcceptGameToken(MP_INVALID_GAME_TOKEN);
    resetClientStates();
    mNetwork->removeDataReceiver(MP_DATA_RECEIVER_ID);
    mNetwork->reset();
    setRole(MP_ROLE_UNKNOWN);
    setState(MP_STATE_DISCONNECTED);
}


void MultiPlayerHandler::resetClientStates()
{
    mClientCount = 0;
    INT32 i;
    for (i = 0; i < MP_MAX_CLIENTS; i++)
        mClientStates[i].reset();
}


INT32 MultiPlayerHandler::getPlayerCount()
{
    return ((MultiPlayerExample*)XFcCore::getApp())->getPlayerCount();
}


void MultiPlayerHandler::setPlayerCount(INT32 aPlayerCount)
{
    ((MultiPlayerExample*)XFcCore::getApp())->setPlayerCount(aPlayerCount);
}


INT32 MultiPlayerHandler::getPlayerId()
{
    return ((MultiPlayerExample*)XFcCore::getApp())->getPlayerId();
}


void MultiPlayerHandler::setPlayerId(INT32 aPlayerId)
{
    ((MultiPlayerExample*)XFcCore::getApp())->setPlayerId(aPlayerId);
}


GameState * MultiPlayerHandler::getGameState(INT32 aPlayerId)
{
    return ((MultiPlayerExample*)XFcCore::getApp())->getGameState(aPlayerId);
}


// Connect to a client
// A ClientStateEntry is initialized with the specified address and into
// the MP_CONNECTION_STATE_CONNECTING connection state, which will cause
// the MultiPlayerHandler to try to establish a connection to this client.
void MultiPlayerHandler::connectToClient(XFcAddress *aAddress)
{
    INT32 clientId = mNetwork->addClient(aAddress);
    INT32 connectionState = (clientId == XFCNET_CLIENTADD_ERROR) ? MP_CONNECTION_STATE_DISCONNECTED : MP_CONNECTION_STATE_CONNECTING;
    mClientStates[mClientCount].init(aAddress, connectionState, clientId, mClientCount + 1);  // +1, because initiator is player 0
    mClientCount++;
}


// Clears the client list
void MultiPlayerHandler::clearClientList()
{
    mClientListMutex->lock();
    while (!mClientList->isEmpty())
        delete mClientList->remove();
    mClientListMutex->unlock();
}


// Returns the number of clients in the client list
INT32 MultiPlayerHandler::getClientListSize()
{
    mClientListMutex->lock();
    INT32 size = mClientList->size();
    mClientListMutex->unlock();
    return size;
}


ClientListEntry * MultiPlayerHandler::getClientListEntry(INT32 aNum)
{
    return mClientList->get(aNum);
}


void MultiPlayerHandler::addClientListEntry(ClientListEntry *aEntry)
{
    mClientListMutex->lock();
    mClientList->put(aEntry);
    mClientListMutex->unlock();
}


// Called when an advertiser has been discovered
void MultiPlayerHandler::handleAdvertiseDiscovered(const XFcAdvertiser *aAdvertiser)
{

    if (!aAdvertiser)
        return;

#ifdef NETWORK_INET
    XFcInetAdvertiser *inetAdvertiser = (XFcInetAdvertiser*)aAdvertiser;
    XFcInetHostEntry *tEntry = XFcInetHostEntry::create(*(inetAdvertiser->mHostEntry));
    ((XFcInetAddress*)tEntry->getAddress())->setPort(MP_INET_PORT);
    addClientListEntry(new ClientListEntry(tEntry));
    delete tEntry;
#else
    XFcBtAdvertiser *btAdvertiser = (XFcBtAdvertiser *)aAdvertiser;
    XFcBtHostEntry *tEntry = XFcBtHostEntry::create(*(btAdvertiser->mHostEntry));
    addClientListEntry(new ClientListEntry(tEntry));
    delete tEntry;
#endif

}


// Called once per iteration of the main loop
void MultiPlayerHandler::onTick()
{

    INT32 tick = XFcCore::getTick();

    if (mState == MP_STATE_CONNECTING)
    {
        if (tick > mGameConnectTick && mRole == MP_ROLE_INITIATOR)
        {
            INT32 i;
            for (i = 0; i < mClientCount; i++)
            {
                ClientStateEntry *csEntry = getClient(i);
                if (csEntry->getConnectionState() == MP_CONNECTION_STATE_CONNECTING)
                {
                    // send game connect packet to any participant that is in
                    // the MP_CONNECTION_STATE_CONNECTING connecion state
                    mNetwork->sendGameConnectPacket(csEntry->getClientId(), MP_GAME_TOKEN);
                }
            }
            mGameConnectTick = tick + 2000;
        }
    }
    else if (mState == MP_STATE_CONNECTED)
    {
        // send game state (every 250 ms)
        // - participants send to initiator
        // - initiator sends each participants state to all
        //   to participants (except the one whose state it is)
        if (tick > mGameStateUpdateTick)
        {
    
            ClientStateEntry *csEntry;
            GameStateUpdatePacket gameStateUpdatePacket;
            INT32 playerId;
            
            if (mRole == MP_ROLE_INITIATOR)
            {

                // initiator sends everyones states to all participants
                INT32 count = getPlayerCount();
                for (playerId = 0; playerId < count; playerId++)
                {
    
                    gameStateUpdatePacket.mPlayerId = (INT8)playerId;
                    gameStateUpdatePacket.mLedState = (INT8)getGameState(playerId)->getLedState();
    
                    INT32 i;
                    for (i = 0; i < mClientCount; i++)
                    {
                        csEntry = getClient(i);
                        if (csEntry->getConnectionState() == MP_CONNECTION_STATE_CONNECTED &&
                            csEntry->getPlayerId() != playerId)
                        {
                            mNetwork->send(csEntry->getClientId(), MP_DATA_RECEIVER_ID, XFCNET_NONGUARANTEED, &gameStateUpdatePacket);
                        }
                    }
    
                }

            }
            else
            {

                // participants send to initiator
                playerId = getPlayerId();
                gameStateUpdatePacket.mPlayerId = (INT8)playerId;
                gameStateUpdatePacket.mLedState = (INT8)getGameState(playerId)->getLedState();

                csEntry = getClient(0);
                mNetwork->send(csEntry->getClientId(), MP_DATA_RECEIVER_ID, XFCNET_NONGUARANTEED, &gameStateUpdatePacket);

            }

            mGameStateUpdateTick = tick + 250;
        }

    }

    // check if a close has been scheduled
    if (mScheduledCloseTick != -1 && (tick > mScheduledCloseTick))
    {
        close();
        mScheduledCloseTick = -1;
    }

}


// Called when a packet arrives to the data receiver (we are receiver MP_DATA_RECEIVER_ID)
void MultiPlayerHandler::addData(INT32 aClientId, const CHAR8 *aData, INT32 aLen)
{

    INT8 type = Packet::getType(aData);

    if (type == PACKET_HANDSHAKE)
    {

        XFCASSERT(mRole == MP_ROLE_INITIATOR);

        // initiator gets handshake packet from participator and sets the
        // participator an init packet

        InitPacket initPacket;
        initPacket.mParticipantCount = (INT8)mClientCount + 1;
        initPacket.mYourPlayerId = -1;

        // count how many clients are connected, and figure out the
        // player id for this client at the same time
        INT32 connectedClients = 0;
        INT32 i;
        for (i = 0; i < mClientCount; i++)
        {
            ClientStateEntry *csEntry = getClient(i);
            if (csEntry->getClientId() == aClientId)
            {
                csEntry->setConnectionState(MP_CONNECTION_STATE_CONNECTED);
                initPacket.mYourPlayerId = (INT8)csEntry->getPlayerId();
                // initialize led
                getGameState(csEntry->getPlayerId())->setLedState(0);
            }

            if (csEntry->getConnectionState() == MP_CONNECTION_STATE_CONNECTED)
                connectedClients++;
        }

        XFCASSERT(initPacket.mYourPlayerId != -1);

        mNetwork->send(aClientId, MP_DATA_RECEIVER_ID, XFCNET_GUARANTEED, &initPacket);

        // all clients have now connected - switch to connected state
        if (connectedClients == mClientCount)
        {
            setPlayerCount(mClientCount + 1);
            setState(MP_STATE_CONNECTED);
        }

    }
    else if (type == PACKET_INIT)
    {

        XFCASSERT(mRole == MP_ROLE_PARTICIPANT);

        // participant receives init packet

        InitPacket initPacket;
        initPacket.deserialize(aData, aLen);

        // set our player id and initialize our led light
        setPlayerId(initPacket.mYourPlayerId);
        getGameState(getPlayerId())->setLedState(0);

        // set the participant count
        setPlayerCount(initPacket.mParticipantCount);

        // we're now connected
        setState(MP_STATE_CONNECTED);

    }
    else if (type == PACKET_DISCONNECT)
    {

        DisconnectPacket disconnectPacket;
        disconnectPacket.deserialize(aData, aLen);

        handleDisconnect(aClientId);

    }
    else if (type == PACKET_GAME_STATE_UPDATE)
    {

        GameStateUpdatePacket gameStateUpdatePacket;
        gameStateUpdatePacket.deserialize(aData, aLen);

        // update game state - the initiator propagates the state between participants
        // during onTick() whenever the game state update is scheduled
        getGameState(gameStateUpdatePacket.mPlayerId)->setLedState(gameStateUpdatePacket.mLedState);

    }
}


void MultiPlayerHandler::sendDisconnectPacket()
{

    DisconnectPacket disconnectPacket;
    disconnectPacket.mPlayerId = (INT8)getPlayerId();

    // participants send to initiator - the initiator sends to all participants
    INT32 i;
    INT32 count = (mRole == MP_ROLE_PARTICIPANT) ? 1 : mClientCount;
    for (i = 0; i < count; i++)
    {
        ClientStateEntry *csEntry = getClient(i);
        mNetwork->send(csEntry->getClientId(), MP_DATA_RECEIVER_ID, XFCNET_GUARANTEED, &disconnectPacket);
    }

}


// Called when a new client has been accepted
void MultiPlayerHandler::handleClientAccepted(INT32 aClientId)
{

    XFCASSERT(mRole == MP_ROLE_PARTICIPANT);

    // initiator player id is always 0 - the initiator address isn't needed
    // for anything so we just set it to NULL
    ClientStateEntry *csEntry = getClient(0);
    csEntry->init(NULL, MP_CONNECTION_STATE_CONNECTED, aClientId, 0);
    mClientCount = 1;

    // send handshake packet to initiator
    HandshakePacket handshakePacket;
    mNetwork->send(aClientId, MP_DATA_RECEIVER_ID, XFCNET_GUARANTEED, &handshakePacket);

    mNetwork->stopAdvertiser();
    mNetwork->setAcceptGameToken(MP_INVALID_GAME_TOKEN);

}


// Called when a client times out or has disconnceted
void MultiPlayerHandler::handleClientLost(INT32 aClientId)
{
    handleDisconnect(aClientId);
}


// Schedules a close to occur in aDelay milliseconds
void MultiPlayerHandler::scheduleClose(INT32 aDelay)
{
    setState(MP_STATE_DISCONNECTED);
    mScheduledCloseTick = XFcCore::getTick() + aDelay;
}


// Called from handleClientLost() and when a disconnect packet is received
// to handle the loss of one client. If this is the last / only client that
// we are connected to, we schedule a close to happen immediately at the
// next iteration of the main loop (this way we don't reset the communication
// manager immediately since we are being called from a callback from within
// the communication manager).
void MultiPlayerHandler::handleDisconnect(INT32 aClientId)
{

    // disable the led light
    ClientStateEntry *csEntry = getClientById(aClientId);
    if (csEntry == NULL)
    {
        // no such client - we're probably already disconnected
        return;
    }

    // switch the led state for the player that disconnected
    getGameState(csEntry->getPlayerId())->setLedState(-1);

    if (mRole == MP_ROLE_INITIATOR)
    {

        // mark the client as disconnected
        csEntry->setConnectionState(MP_CONNECTION_STATE_DISCONNECTED);

        // check if anyone is still connected
        INT32 connectedCount = 0;
        INT32 i;
        for (i = 0; i < mClientCount; i++)
        {
            csEntry = getClient(i);
            if (csEntry->getConnectionState() == MP_STATE_CONNECTED)
                connectedCount++;
        }

        // any open connections?
        if (connectedCount == 0)
            scheduleClose();

    }
    else
    {
        // participant can't continue without initiator
        scheduleClose();
    }

}


