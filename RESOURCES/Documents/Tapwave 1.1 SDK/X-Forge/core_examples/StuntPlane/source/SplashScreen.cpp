/*! \file
 * SplashScreen.cpp <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: SplashScreen.cpp,v 1.2 2003/07/09 14:25:44 lars Exp $
 * $Date: 2003/07/09 14:25:44 $
 * $Revision: 1.2 $
 */

#include <xforge.h>

#include "Screen.h"
#include "SplashScreen.h"
#include "StuntPlane.h"


//! Static constructor.
SplashScreen * SplashScreen::create(XFcGL *aGL)
{
    SplashScreen *m = new SplashScreen(aGL);
    XFCASSERT(m);
    return m;
}


SplashScreen::SplashScreen(XFcGL *aGL) : Screen(aGL)
{
    mSplash = NULL;
}


SplashScreen::~SplashScreen()
{
}


//! Called when this screen is set as current renderer.
void SplashScreen::initRenderer()
{
    mSplash = XFcImageLoader::load(XFCSTR("xforge.pcx"));
    XFCASSERT(mSplash);
}


//! Called when another screen is set as current renderer.
void SplashScreen::deinitRenderer()
{
    delete mSplash;
    mSplash = NULL;
}


//! Called when a control key is pressed.
void SplashScreen::onKeyDown(INT32 /*aCode*/)
{
    mApp->setState(SP_STATE_MENU);
}


//! Called when a control key is pressed.
void SplashScreen::onPointerDown(INT32 /*aX*/, INT32 /*aY*/)
{
    mApp->setState(SP_STATE_MENU);
}


//! The SplashScreen renderer.
void SplashScreen::render()
{
    XFcGLSurface *fb;        

    mGL->clear();

    // ask GL for the secondary buffer.
    fb = mGL->getSecondary();

    // draw splash image.
    fb->drawImage(mSplash, (XFcCore::getDeviceWidth() - mSplash->getWidth()) / 2, 0, 
                  mSplash->getWidth(), XFcCore::getDeviceHeight());
}


