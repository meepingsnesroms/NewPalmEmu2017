/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: GameScreen.cpp,v 1.2 2003/08/28 14:25:04 niko Exp $
 * $Date: 2003/08/28 14:25:04 $
 * $Revision: 1.2 $
 */

#include <xforge.h>

#include "Screen.h"
#include "Widget.h"
#include "UIImageFactory.h"
#include "MultiPlayerHandler.h"
#include "MultiPlayerExample.h"
#include "AppStates.h"
#include "GameScreen.h"


GameScreen * GameScreen::create(XFcGL *aGL,
                                XFuPrinter *aPrinter,
                                MultiPlayerHandler *aMultiPlayerHandler)
{
    GameScreen *screen = new GameScreen();

    if (screen) 
    {
        screen->mGL = aGL;
        screen->mPrinter = aPrinter;
        screen->mMultiPlayerHandler = aMultiPlayerHandler;
    }
    return screen;
}


GameScreen::GameScreen() {}
GameScreen::~GameScreen() {}


void GameScreen::onActivate()
{
    mLedOn = XFcImageLoader::load(XFCSTR("on.pcx"));
    mLedOff = XFcImageLoader::load(XFCSTR("off.pcx"));
    XFCASSERT(mLedOn && mLedOff);

    addWidget(13, 140, 150, 27, XFCSTR("TOGGLE LED"), MPE_LED_BUTTON, MPE_BUTTON_WIDGET);
    addWidget(13, 170, 150, 27, XFCSTR("LEAVE GAME"), MPE_LEAVE_BUTTON, MPE_BUTTON_WIDGET);
}


void GameScreen::onDeactivate()
{
    delete mLedOn;
    delete mLedOff;
}


INT32 GameScreen::getPlayerCount()
{
    return ((MultiPlayerExample*)XFcCore::getApp())->getPlayerCount();
}


INT32 GameScreen::getPlayerId()
{
    return ((MultiPlayerExample*)XFcCore::getApp())->getPlayerId();
}


GameState * GameScreen::getGameState(INT32 aPlayerId)
{
    return ((MultiPlayerExample*)XFcCore::getApp())->getGameState(aPlayerId);
}


void GameScreen::onButtonPressed(INT32 aButton)
{
    if (aButton == MPE_LED_BUTTON)
    {
        // toggle our led
        GameState *gs = getGameState(getPlayerId());
        if (gs->getLedState())
            gs->setLedState(0);
        else
            gs->setLedState(1);
    }
    else if (aButton == MPE_LEAVE_BUTTON)
    {
        // send disconnect packet and schedule a close to occur 1000 ms from now
        // this should be enough to ensure the delivery of the disconnect packet
        mMultiPlayerHandler->sendDisconnectPacket();
        mMultiPlayerHandler->scheduleClose(1000);
        mApp->setState(APP_STATE_MAIN_MENU);
    }
}


void GameScreen::onTick()
{
}


void GameScreen::render()
{

    mGL->clear();
    Screen::render();

    XFcGLSurface *backBuffer = mGL->getSecondary();

    // draw the player leds
    INT32 playerCount = getPlayerCount();
    INT32 i;

    INT32 ledSourceWidth = mLedOn->getWidth();
    INT32 ledSourceHeight = mLedOn->getHeight();
    INT32 ledWidth = XFcCore::getDeviceWidth() / playerCount;
    INT32 ledHeight = (REAL)ledWidth / (REAL)ledSourceWidth * (REAL)ledSourceHeight;
    INT32 yMargin = (XFcCore::getDeviceHeight() - 63 - ledHeight) / 2;
 
    for (i = 0; i < playerCount; i++)
    {
        INT32 ledState = getGameState(i)->getLedState();
        if (ledState == 1)
            backBuffer->drawImage(mLedOn, i * ledWidth, yMargin, ledWidth, ledHeight);
        else if (ledState == 0)
            backBuffer->drawImage(mLedOff, i * ledWidth, yMargin, ledWidth, ledHeight);
    }

}

