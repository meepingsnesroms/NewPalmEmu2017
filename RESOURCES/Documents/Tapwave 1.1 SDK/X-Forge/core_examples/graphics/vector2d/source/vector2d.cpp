/*! \file 
 * X-Forge Core Example <br>
 * Copyright 2002,2003 Fathammer Ltd
 * 
 * \brief 2D vector drawing example.
 * 
 * $Id: vector2d.cpp,v 1.2 2003/10/17 11:28:47 kkallio Exp $
 * $Date: 2003/10/17 11:28:47 $
 * $Revision: 1.2 $
 */

#include <xforge.h>
#include "XForgeLogo.h"
#include "button.h"

#define BUTTON_X 10
#define BUTTON_Y 10
#define BUTTON_SIZE 16

// Application class, also acting as input and renderer.
class MyApp : public XFcApp, public XFcInput, public XFcRenderer
{
public:    
    // Renderer function which will be called in every frame.
    virtual void render();
    // Called by XFcCore when stylus or mouse button is pressed.
    virtual void onPointerDown(INT32 aX, INT32 aY);
    // Called by XFcCore when stylus or mouse button is lifted.
    virtual void onPointerUp(INT32 aX, INT32 aY);
    // Called by XFcCore when a key is released.
    virtual void onControlUp(INT32 aKey);
    // Called when application is started.
    virtual void onAppInit();
    // Called when application is terminated.
    virtual void onAppDeinit();
    
    // Pointer to X-Forge core graphics library.
    XFcGL *mGL;

    // Pointer to the X-Forge logo
    XForgeLogo *mLogo;

    // Pointer to the button
    button *mButton;

    // Is the button pressed?
    INT mButtonPressed;
};


// Rendering function of the application.
void MyApp::render()
{
    mGL->clear(0xffffff);

    // X-Forge logo is a class that draws X-Forge logo to the screen.
    // It can be animated by changing the zoom level and fade.

    // The animation loops in five seconds. The first second is fade in,
    // the last second is fade out, and the zoom is from 0.01 to 2.25 during
    // the animation.

    INT32 tick = XFcCore::getTick() % 5000;

    INT32 fade = 0xff;
    if (tick < 1000)
    {
        fade = (tick * 0xff) / 1000;
    }
    else if (tick > 4000)
    {
        fade = ((5000 - tick) * 0xff) / 1000;
    }
    mLogo->setFade(0xffffff,fade);

    REAL zoom = (REALf(0.1) + (REALf(1.4) * tick) / 5000);
    zoom = zoom * zoom;
    mLogo->setZoom(zoom);
    
    XFcGLSurface *target = mGL->getSecondary();
    mLogo->render(target);

    mButton->setPressed(mButtonPressed);
    mButton->render(target);
}

// Called by XFcCore when stylus or mouse button is pressed.
void MyApp::onPointerDown(INT32 aX, INT32 aY)
{
    INT32 xDiff = aX - (BUTTON_X + BUTTON_SIZE / 2);
    INT32 yDiff = aY - (BUTTON_Y + BUTTON_SIZE / 2);

    INT32 diffSq = xDiff * xDiff + yDiff * yDiff;
    if (diffSq < (BUTTON_SIZE * BUTTON_SIZE))
        mButtonPressed = 1;
    else
        mButtonPressed = 0;
}

// Called by XFcCore when stylus or mouse button is lifted.
void MyApp::onPointerUp(INT32 aX, INT32 aY)
{
    INT32 xDiff = aX - (BUTTON_X + BUTTON_SIZE / 2);
    INT32 yDiff = aY - (BUTTON_Y + BUTTON_SIZE / 2);

    INT32 diffSq = xDiff * xDiff + yDiff * yDiff;
    if (diffSq < (BUTTON_SIZE * BUTTON_SIZE))
    {
        if (mButtonPressed)
           XFcCore::quit();
    }
    else
        mButtonPressed = 0;
}

// Called by XFcCore when a key is released.
void MyApp::onControlUp(INT32 /*aKey*/)
{
    // Don't accept control-up input within the first half a second;
    // this will ignore any accidental key-up messages that may happen
    // if you use the device buttons to launch the application.
    if (XFcCore::getTick() > 500)
        XFcCore::quit();
}


// Called when application is started.
// Initializes the texture and creates the cube.
void MyApp::onAppInit()
{   
    // For every input action XFcCore calls control.
    XFcCore::setController(this);
    
    // In every frame XFcCore calls cuberender to draw the image.
    XFcCore::setRenderer(this);

    // Create renderer.
    mGL = XFcGL::create();
    XFCASSERT(mGL && "Out of memory allocating GL.");

    mLogo = new XForgeLogo();
    mButton = new button(BUTTON_X,BUTTON_Y,BUTTON_SIZE);
}


// Called when application is terminated.
// Frees the allocated memory.
void MyApp::onAppDeinit()
{   
    delete mGL;
    delete mLogo;
    delete mButton;
}



/*
 * Initialization of the application works via two global functions:
 *
 * void xfcAppPref(XFcAppPrefs &xfcAppPrefs)
 * - Specifies the system resources application will use.
 * 
 * INT xfcAppInit()
 * - Initializes the application.
 */


// Initializes application's resource allocation:
// Total memory is 1M from which resources will take a maximum of 1M.
void xfcAppPref(XFcAppPrefs &aAppPrefs)
{
    aAppPrefs.mTotalMemoryLimit = 1 * 1024 * 1024;   // Total memory
    aAppPrefs.mResourceMemoryLimit = 1 * 1024 * 1024;// Max. memory resources may take
    aAppPrefs.mUID = 0x101F4F86; // Symbian application unique ID
    aAppPrefs.mMinimumExtraMemory = 128 * 1024; // Minimum extra free memory on the system
}


// Initializes the application.
INT xfcAppInit() 
{
    //  We could use xfcUseDefaults() here to link with all typically used
    //  core features, which would lead to an executable size of about
    //  346k on arm release on wince.
    //xfcUseDefaults();
    //  However, as we don't use any 3d functionality in this example, we
    //  can don only the following. Note that this should always be called
    //  before 2D vector graphics can be used.
    xfcUse2DVectorGraphics();

    new MyApp;
        
    return 0;
}
