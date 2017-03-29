/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: MultiPlayerExample.cpp,v 1.4 2003/10/09 11:21:21 niko Exp $
 * $Date: 2003/10/09 11:21:21 $
 * $Revision: 1.4 $
 */

#include <xforge.h>
#include <xfutil/XFuPrinter.h>

#include "Screen.h"
#include "AppStates.h"
#include "MultiPlayerHandler.h"
#include "ConnectingScreen.h"
#include "GameScreen.h"
#include "MainMenuScreen.h"
#include "MultiPlayerExample.h"


//! Initializes the app
INT32 xfcAppInit()
{
    xfcUseDefaults();
    xfcUseNetwork();
    new MultiPlayerExample();
    return 0;
}


//! Configures the app
void xfcAppPref(XFcAppPrefs &aPrefs)
{
#ifdef XFC_PLATFORM_EPOC
    aPrefs.mUID = 0x101F90A2;
#endif
    aPrefs.mResourceMemoryLimit = (INT32)(1.2 * 1024 * 1024);
    aPrefs.mTotalMemoryLimit = (INT32)(1.2 * 1024 * 1024);
    aPrefs.mPreferredWidth = 176;
    aPrefs.mPreferredHeight = 208;
}


MultiPlayerExample::MultiPlayerExample()
{
    mGL = NULL;
    mMainMenuScreen = NULL;
    mConnectingScreen = NULL;
    mGameScreen = NULL;

    mMultiPlayerHandler = NULL;
    mNetwork = NULL;

    mSwitchState = mSwitchScreen = 0;
    mCurrentScreen = NULL;
}


//! Called on application init
void MultiPlayerExample::onAppInit()
{   
    xfcNetworkStartup();

    setPlayerCount(0);
    setPlayerId(-1);
    resetGameStates();

    mGL = XFcGL::create();

    mPrinter = XFuPrinter::create(XFCSTR("font.pcx"), 0x0000ff);
    XFCASSERT(mPrinter);


#ifdef NETWORK_INET
    mNetwork = XFuInetNetwork::create();
#else
    mNetwork = XFuBluetoothMultiNetwork::create();
#endif

    mMultiPlayerHandler = MultiPlayerHandler::create(mNetwork);

    // create screens
    mMainMenuScreen = MainMenuScreen::create(mGL, mPrinter);
    mConnectingScreen = ConnectingScreen::create(mGL, mPrinter, mMultiPlayerHandler);
    mGameScreen = GameScreen::create(mGL, mPrinter, mMultiPlayerHandler);

    // start the state machine
    setState(APP_STATE_START);
}


//! Called on application quit (cleanup)
void MultiPlayerExample::onAppDeinit()
{

    if (mMultiPlayerHandler)
        mMultiPlayerHandler->close();

    delete mMultiPlayerHandler;
    delete mNetwork;

    delete mMainMenuScreen;
    delete mConnectingScreen;
    delete mGameScreen;

    delete mGL;
    
    xfcNetworkCleanup();
}


//! Called to switch global application state.
void MultiPlayerExample::setState(APP_STATES aState)
{
    mSwitchState = 1;
    mNewState = aState;
}


//! Called to switch current screen (XFcRenderer & XFcController)
void MultiPlayerExample::setScreen(Screen * aScreen)
{
    if (mCurrentScreen != aScreen) 
    {
        mSwitchScreen = 1;
        mCurrentScreen = aScreen;
    }
}


//! Called before rendering starts.
void MultiPlayerExample::onTick()
{
    if (mSwitchScreen) 
    {
        XFcCore::setRenderer(mCurrentScreen);
        XFcCore::setController(mCurrentScreen);
        mSwitchScreen = 0;
    }

    if (mSwitchState) 
    {        
        mSwitchState = 0;
        handleStateChange(mState, mNewState);
        mState = mNewState;
    }

    if (mMultiPlayerHandler != NULL)
        mMultiPlayerHandler->onTick();

    //! Call onTick() method of global screen if any.
    if (mCurrentScreen != NULL)
        mCurrentScreen->onTick();
}            


//! Called when the state changes
void MultiPlayerExample::handleStateChange(INT32 /*aOldState*/, INT32 aNewState)
{

    switch (aNewState)
    {

        case APP_STATE_START:
            setState(APP_STATE_MAIN_MENU);
            break;

        case APP_STATE_MAIN_MENU:
            setScreen(mMainMenuScreen);
            break;

        case APP_STATE_GAME_INITIATE:
            resetGameStates();
            setPlayerId(0);
            setPlayerCount(0);
            mMultiPlayerHandler->initAsInitiator();
            setState(APP_STATE_CONNECTING);
            break;

        case APP_STATE_GAME_PARTICIPATE:
            resetGameStates();
            setPlayerId(-1);
            setPlayerCount(0);
            mMultiPlayerHandler->initAsParticipant();
            setState(APP_STATE_CONNECTING);
            break;

        case APP_STATE_CONNECTING:
            setScreen(mConnectingScreen);
            break;

        case APP_STATE_GAME:
            setScreen(mGameScreen);
            break;

        case APP_STATE_SHUTDOWN:
            XFcCore::quit();
            break;

        default:
            break;
    }
}
