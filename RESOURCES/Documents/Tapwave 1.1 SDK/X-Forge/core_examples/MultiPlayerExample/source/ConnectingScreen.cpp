/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: ConnectingScreen.cpp,v 1.3 2003/08/01 07:53:10 lars Exp $
 * $Date: 2003/08/01 07:53:10 $
 * $Revision: 1.3 $
 */

#include <xforge.h>
#include <xfutil/XFuPrinter.h>

#include "Screen.h"
#include "Widget.h"
#include "AppStates.h"
#include "ClientListEntry.h"
#include "MultiPlayerHandler.h"
#include "MultiPlayerExample.h"
#include "ConnectingScreen.h"


ConnectingScreen * ConnectingScreen::create(XFcGL *aGL,
                                            XFuPrinter *aPrinter,
                                            MultiPlayerHandler *aMultiPlayerHandler)
{       
    ConnectingScreen *screen = new ConnectingScreen();
    if (screen)
    {
        screen->mGL = aGL;
        screen->mPrinter = aPrinter;
        screen->mMultiPlayerHandler = aMultiPlayerHandler;
    }
    return screen;
}


ConnectingScreen::ConnectingScreen() 
{
    mStatusString[0] = '\0';
    mShowTruncated = 0;
}

ConnectingScreen::~ConnectingScreen() {}


void ConnectingScreen::onActivate()
{

    mMultiPlayerState = MP_STATE_UNKNOWN;

    mRole = mMultiPlayerHandler->getRole();
    mListedClientCount = 0;


    if (mRole == MP_ROLE_INITIATOR)
    {

        INT32 lineHeight = 16;

        // create checkboxes and labels for client list
        INT32 i;
        for (i = 0; i < MAX_LIST_ENTRIES; i++)
        {

            mClientCheckbox[i] = addWidget(10, (i * lineHeight) + 30, 150, 16, XFCSTR("ABCDEF"), 
                                         MPE_FIRST_CHECKBOX + i, MPE_CHECKBOX_WIDGET);
            mClientCheckbox[i]->setVisible(0);
        }

        mStatusY = 10;
        setStatus(XFCSTR(""));

        mStartButton = addWidget(13, 140, 150, 27, XFCSTR("START"), MPE_START_BUTTON, MPE_BUTTON_WIDGET);
        mCancelButton = addWidget(13, 170, 150, 27, XFCSTR("CANCEL"), MPE_CANCEL_BUTTON, MPE_BUTTON_WIDGET);
    }
    else
    {
        mStatusY = 75;
        setStatus(XFCSTR("WAITING FOR HOST"));

        addWidget(13, 170, 150, 27, XFCSTR("CANCEL"), MPE_CANCEL_BUTTON, MPE_BUTTON_WIDGET);        
    }

}

void ConnectingScreen::onDeactivate()
{
}


void ConnectingScreen::setStatus(const CHAR *aStatus)
{
    INT32 w, h;

    // copy status string
    INT i;
    for (i = 0; i < 64 && aStatus[i] != '\0'; i++) 
    {
        mStatusString[i] = aStatus[i];
    }
    mStatusString[i] = '\0';

    mPrinter->stringMetrics(aStatus, w, h);
    mStatusX = (XFcCore::getDeviceWidth() - w) / 2;
}


void ConnectingScreen::onButtonPressed(INT32 aButton)
{

    if (aButton == MPE_START_BUTTON)
    {
        if (mMultiPlayerHandler->getState() == MP_STATE_INITIALIZED)
        {

            INT32 connectingClientCount = 0;
            INT32 i;
            for (i = 0; (i < MAX_LIST_ENTRIES) && (connectingClientCount < MP_MAX_CLIENTS); i++)
            {
                if (mClientCheckbox[i]->getState() == MPE_CHECKBOX_CHECKED)
                {
                    ClientListEntry *clEntry = mMultiPlayerHandler->getClientListEntry(i);
                    XFcAddress *address = clEntry->getHostEntry()->getAddress();
                    mMultiPlayerHandler->connectToClient(address);
                    connectingClientCount++;
                }
            }

            if (connectingClientCount != 0)
            {
                // lock the checkboxes so they can't be toggled
                for (i = 0; i < MAX_LIST_ENTRIES; i++)
                {
                    mClientCheckbox[i]->setEnabled(0);
                }
                mMultiPlayerHandler->setState(MP_STATE_CONNECTING);
            }

        }
    }
    else if (aButton == MPE_CANCEL_BUTTON)
    {
        mMultiPlayerHandler->close();
        mApp->setState(APP_STATE_MAIN_MENU);
    }

}


void ConnectingScreen::onTick()
{

    if (mRole == MP_ROLE_INITIATOR)
    {
        // update the status message based on the multiplayer state
        INT32 mpState = mMultiPlayerHandler->getState();
        if (mpState != mMultiPlayerState || mpState == MP_STATE_CONNECTING)
        {

            mMultiPlayerState = mpState;

            if (mpState == MP_STATE_INITIALIZED)
            {
                setStatus(XFCSTR("SELECT PARTICIPANTS"));
            }
            else if (mpState == MP_STATE_DISCONNECTED)
            {
                setStatus(XFCSTR("FAILED TO CONNECT"));
                mStartButton->setEnabled(0);
            }
            else if (mpState == MP_STATE_CONNECTING)
            {
                CHAR str[64];
                INT32 connectedCount = 0;
                INT32 totalCount = mMultiPlayerHandler->getClientCount();
                INT32 i;
                for (i = 0; i < totalCount; i++)
                {
                    ClientStateEntry *csEntry = mMultiPlayerHandler->getClient(i);
                    if (csEntry->getConnectionState() == MP_CONNECTION_STATE_CONNECTED)
                        connectedCount++;
                }
                XFcStringToolkit::format(str, XFCSTR("CONNECTING (%i/%i)"), connectedCount, totalCount);
                setStatus(str);
            }
            else if (mpState == MP_STATE_CONNECTED)
            {
                mApp->setState(APP_STATE_GAME);
            }

        }
        // update client list if more clients have been discovered
        INT32 clientListSize = mMultiPlayerHandler->getClientListSize();
        if (clientListSize > mListedClientCount)
        {
            INT32 i;
            for (i = mListedClientCount; (i < clientListSize) && (i < MAX_LIST_ENTRIES); i++)
            {
                mClientCheckbox[i]->setVisible(1);
                mClientCheckbox[i]->setText(mMultiPlayerHandler->getClientListEntry(i)->getName());
                mListedClientCount++;
            }
            if (i >= MAX_LIST_ENTRIES)
            {
                mShowTruncated = 1;
            }
        }
    }
    else
    {
        INT32 mpState = mMultiPlayerHandler->getState();
        if (mpState == MP_STATE_CONNECTED)
        {
            mApp->setState(APP_STATE_GAME);
        }
    }

}


void ConnectingScreen::render()
{
    mGL->clear();

    // render status message
    if (mStatusString) 
    {
        mPrinter->print(mGL->getSecondary(), mStatusX, mStatusY, mStatusString);
    }

    if (mShowTruncated)
    {
        mPrinter->print(mGL->getSecondary(), mStatusX, 30 + 5 * 16, "LIST TRUNCATED");        
    }

    Screen::render();
    XFcCore::sleep(20);
}

