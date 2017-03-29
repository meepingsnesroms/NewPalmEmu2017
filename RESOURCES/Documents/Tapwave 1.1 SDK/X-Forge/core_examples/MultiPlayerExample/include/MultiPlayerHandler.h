/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: MultiPlayerHandler.h,v 1.2 2003/08/01 07:53:10 lars Exp $
 * $Date: 2003/08/01 07:53:10 $
 * $Revision: 1.2 $
 */

#ifndef MULTIPLAYERHANDLER_H_INCLUDED
#define MULTIPLAYERHANDLER_H_INCLUDED

#define MP_INET_ADVERTISER_PORT     55054
#define MP_INET_PORT                55055

#define MP_BT_PORT                  0

#define MP_GAME_TOKEN               8877
#define MP_INVALID_GAME_TOKEN       9988

#define MP_DATA_RECEIVER_ID         9999

#define MP_MAX_CLIENTS              3

#include <xfutil/XFuDynamicArray.h>
#include <xfcore/net/XFcDataReceiver.h>

#include <xfutil/XFuNetworkEventHandler.h>
#include <xfutil/XFuInetNetwork.h>
#include <xfutil/XFuBluetoothNetwork.h>
#include <xfutil/XFuBluetoothMultiNetwork.h>

#include "AppStates.h"
#include "ClientStateEntry.h"
#include "Packets.h"

enum MP_ROLES
{
    MP_ROLE_UNKNOWN,
    MP_ROLE_INITIATOR,
    MP_ROLE_PARTICIPANT
};

enum MP_STATE
{
    MP_STATE_UNKNOWN,
    MP_STATE_INITIALIZED,
    MP_STATE_CONNECTING,
    MP_STATE_CONNECTED,
    MP_STATE_DISCONNECTED
};

class ClientListEntry;
class GameState;

class MultiPlayerHandler : public XFuNetworkEventHandler,
                           public XFcDataReceiver

//class MultiPlayerHandler : public XFcDataReceiver
{

public:

//    static MultiPlayerHandler * create(XFeGameGraph *aGameGraph);
    static MultiPlayerHandler * create(XFuNetwork *aNetwork);

    ~MultiPlayerHandler();

    virtual void handleClientAccepted(INT32 aClientId);
    virtual void handleClientLost(INT32 aClientId);
    virtual void handleAdvertiseDiscovered(const XFcAdvertiser *aAdvertiser);

    void initAsInitiator();
    void initAsParticipant();

    void connectToClient(XFcAddress *aAddress);

    void close();

    INT32 getClientListSize();
    ClientListEntry * getClientListEntry(INT32 aNum);

    INT32 getState() { return mState; }
    void setState(INT32 aState) { mState = aState; }

    INT32 getRole() { return mRole; }

    virtual void addData(INT32 aClientId, const CHAR8 *aData, INT32 aLen);

    void onTick();

    INT32 getClientCount() { return mClientCount; }
    ClientStateEntry * getClient(INT32 aNum) { return &mClientStates[aNum]; }
    ClientStateEntry * getClientById(INT32 aClientId)
    {
        INT32 i;
        for (i = 0; i < mClientCount; i++)
        {
            if (mClientStates[i].getClientId() == aClientId)
                return &mClientStates[i];
        }
        return NULL;
    }

    INT32 getPlayerId();
    void setPlayerId(INT32 aPlayerId);
    INT32 getPlayerCount();
    void setPlayerCount(INT32 aPlayerCount);
    GameState * getGameState(INT32 aPlayerId);

    void scheduleClose(INT32 aDelay = 0);

    void sendDisconnectPacket();

protected:

    MultiPlayerHandler();

    void handleDisconnect(INT32 aClientId);

    void setRole(INT32 aRole) { mRole = aRole; }

    void clearClientList();
    void addClientListEntry(ClientListEntry *aEntry);

    void resetClientStates();

#ifdef NETWORK_INET
    XFuInetNetwork *mNetwork;
#else
    XFuBluetoothMultiNetwork *mNetwork;
#endif

    INT32 mRole;
    INT32 mState;

    XFuDynamicArray<ClientListEntry*> *mClientList;
    XFcMutex *mClientListMutex;

    INT32 mClientCount;
    ClientStateEntry mClientStates[MP_MAX_CLIENTS];

    INT32 mGameConnectTick;
    INT32 mScheduledCloseTick;
    INT32 mGameStateUpdateTick;

};

#endif // !MULTIPLAYERHANDLER_H_INCLUDED


