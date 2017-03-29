/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: ClientStateEntry.h,v 1.1 2003/07/11 11:25:19 lars Exp $
 * $Date: 2003/07/11 11:25:19 $
 * $Revision: 1.1 $
 */

#ifndef CLIENTSTATEENTRY_H_INCLUDED
#define CLIENTSTATEENTRY_H_INCLUDED

#include <xfcore/net/socket/XFcAddress.h>
#include <xfcore/net/socket/XFcInetAddress.h>
#include <xfcore/net/socket/XFcBtAddress.h>

enum MP_CONNECTION_STATES
{
    MP_CONNECTION_STATE_DISCONNECTED,
    MP_CONNECTION_STATE_CONNECTING,
    MP_CONNECTION_STATE_CONNECTED
};

// ClientStateEntry represents the state of one client that there is a
// connection to. It holds the connection state, which tells the application
// if there is a connection to the client, it holds the client id, which is
// used to send the client packets, and it holds the player id, which is used
// to map the client to the local game state data for that client.

class ClientStateEntry
{

public:

    ClientStateEntry()
    {
        mAddress = NULL;
        reset();
    }

    ~ClientStateEntry()
    {
        delete mAddress;
    }

    void init(XFcAddress *aAddress,
              INT32 aConnectionState,
              INT32 aClientId,
              INT32 aPlayerId)
    {
        setAddress(aAddress);
        setConnectionState(aConnectionState);
        setClientId(aClientId);
        setPlayerId(aPlayerId);
    }

    void reset()
    {
        init(NULL, MP_CONNECTION_STATE_DISCONNECTED, -1, -1);
    }

    XFcAddress * getAddress()
    {
        return mAddress;
    }

    void setAddress(XFcAddress *aAddress)
    {
        delete mAddress;
        if (mAddress)
        {
#ifdef NETWORK_INET
            mAddress = XFcInetAddress::create(*aAddress);
#else
            mAddress = XFcBtAddress::create(*aAddress);
#endif
        }
        else
        {
            mAddress = NULL;
        }
    }

    INT32 getConnectionState() { return mConnectionState; }
    void setConnectionState(INT32 aState) { mConnectionState = aState; }
    
    INT32 getClientId() { return mClientId; }
    void setClientId(INT32 aClientId) { mClientId = aClientId; }

    INT32 getPlayerId() { return mPlayerId; }
    void setPlayerId(INT32 aPlayerId) { mPlayerId = aPlayerId; }

protected:

    XFcAddress *mAddress;
    INT32 mConnectionState;
    INT32 mClientId;
    INT32 mPlayerId;

};

#endif // !CLIENTSTATEENTRY_H_INCLUDED

