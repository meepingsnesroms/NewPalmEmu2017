/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: MultiPlayerExample.h,v 1.6 2003/10/09 14:46:25 niko Exp $
 * $Date: 2003/10/09 14:46:25 $
 * $Revision: 1.6 $
 */

#ifndef MULTIPLAYER_EXAMPLE_H_INCLUDED
#define MULTIPLAYER_EXAMPLE_H_INCLUDED

#if defined(XFC_PLATFORM_DESKTOPWINDOWS) || defined(XFC_PLATFORM_WINCE)
    #define NETWORK_INET
#else
    #define NETWORK_BT
#endif

#include "AppStates.h"
#include "GameState.h"

#define MAX_PLAYERS 4

class XFuInetNetwork;
class XFuBluetoothMultiNetwork;
class MainMenuScreen;
class ConnectingScreen;
class GameScreen;
class Screen;
class MultiPlayerHandler;
class XFuPrinter;

class MultiPlayerExample : public XFcApp
{

public:
    MultiPlayerExample();

    virtual void onTick();

    virtual void onAppInit();
    virtual void onAppDeinit();

    virtual void handleStateChange(INT32 aOldState, INT32 aNewState);

    void resetGameStates()
    {
        INT32 i;
        for (i = 0; i < MAX_PLAYERS; i++)
            mGameStates[i].reset();
    }
    GameState * getGameState(INT32 aPlayerId) { return &mGameStates[aPlayerId]; }

    INT32 getPlayerId() { return mPlayerId; }
    void setPlayerId(INT32 aPlayerId) { mPlayerId = aPlayerId; }
    INT32 getPlayerCount() { return mPlayerCount; }
    void setPlayerCount(INT32 aPlayerCount) { mPlayerCount = aPlayerCount; }

    void setState(APP_STATES aState);
    void setScreen(Screen * aScreen);

private:

    XFcGL *mGL;

#ifdef NETWORK_INET
    XFuInetNetwork *mNetwork;
#else
    XFuBluetoothMultiNetwork *mNetwork;
#endif

    MultiPlayerHandler *mMultiPlayerHandler;

    XFuPrinter *mPrinter;

    MainMenuScreen *mMainMenuScreen;
    ConnectingScreen *mConnectingScreen;
    GameScreen *mGameScreen;

    INT32 mPlayerId;
    INT32 mPlayerCount;
    GameState mGameStates[MAX_PLAYERS];

    INT32 mState, mNewState;

    INT mSwitchState, mSwitchScreen;    

    Screen *mCurrentScreen;

};

#endif // !MULTIPLAYER_EXAMPLE_H_INCLUDED

