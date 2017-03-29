/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: MainMenuScreen.cpp,v 1.2 2003/07/21 07:07:36 lars Exp $
 * $Date: 2003/07/21 07:07:36 $
 * $Revision: 1.2 $
 */

#include <xforge.h>
#include <xfutil/XFuPrinter.h>

#include "Screen.h"
#include "Widget.h"
#include "AppStates.h"
#include "MultiPlayerExample.h"
#include "MainMenuScreen.h"


MainMenuScreen * MainMenuScreen::create(XFcGL *aGL, XFuPrinter *aPrinter)
{
    MainMenuScreen *screen = new MainMenuScreen();

    if (screen)
    {
        screen->mGL = aGL;
        screen->mPrinter = aPrinter;
    }
    return screen;
}


MainMenuScreen::MainMenuScreen() {}
MainMenuScreen::~MainMenuScreen() {}


void MainMenuScreen::onActivate()
{
    // create main menu buttons
    addWidget(13, 15, 150, 27, XFCSTR("HOST GAME"), MPE_HOST_BUTTON, MPE_BUTTON_WIDGET);
    addWidget(13, 45, 150, 27, XFCSTR("JOIN GAME"), MPE_JOIN_BUTTON, MPE_BUTTON_WIDGET);
    addWidget(13, 75, 150, 27, XFCSTR("QUIT"), MPE_QUIT_BUTTON, MPE_BUTTON_WIDGET);
}


void MainMenuScreen::onDeactivate()
{
}


void MainMenuScreen::onTick()
{
}


//! Called when a button is pressed.
void MainMenuScreen::onButtonPressed(INT32 aButton)
{
    switch (aButton)
    {   
        case MPE_HOST_BUTTON:
            mApp->setState(APP_STATE_GAME_INITIATE);
            break;
        case MPE_JOIN_BUTTON:
            mApp->setState(APP_STATE_GAME_PARTICIPATE);
            break;
        case MPE_QUIT_BUTTON:
            mApp->setState(APP_STATE_SHUTDOWN);
            break;
        default:
            break;
    }
}


void MainMenuScreen::render()
{
    mGL->clear();

    Screen::render();

    // sleep a little before starting to render next frame.
    XFcCore::sleep(20);
}

