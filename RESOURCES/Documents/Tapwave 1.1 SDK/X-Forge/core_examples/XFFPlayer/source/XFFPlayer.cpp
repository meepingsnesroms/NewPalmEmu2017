/*! \file
 * XFFPlayer.cpp <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: XFFPlayer.cpp,v 1.4 2003/10/03 12:10:22 jari Exp $
 * $Date: 2003/10/03 12:10:22 $
 * $Revision: 1.4 $
 */

#include <xforge.h>
#include <xfutil/XFuPrinter.h>
#include "GameGraph.h"

// Application running states.
enum STATE
{
    STATE_PAUSED = 0,
    STATE_RUNNING,
};


class XFFPlayer : public XFcApp, public XFcInput, public XFcRenderer
{

public:

    // Static constructor.
    static XFFPlayer * create();

// Inherited from XFcApp:

    // Called when application is initialized.
    virtual void onAppInit();

    // Called on application quit (cleanup).
    virtual void onAppDeinit();

    // Called when a device state event occurs.
    virtual INT onDeviceStateEvent(INT32 aEvent, INT32 aSeverity, void *aMoreInfo);

// Inherited from XFcInput:

    // Callback: control pressed.
    virtual void onControlDown(INT32 aCode);

    // Callback: pointer touches screen.
    virtual void onPointerDown(INT32 aX, INT32 aY);

// Inherited from XFcRenderer:

    // Renders the game graph.
    virtual void render();

private:

    // Private constructor.
    XFFPlayer();

    // Initializes audio, can be also used to reinitialize it.
    void initAudio();
    
    // Pointer to graphics library.
    XFcGL *mGL;

    // Pointer to game graph.
    GameGraph *mGameGraph;

    // Application state.
    STATE mState;

    XFuPrinter *mPrinter;
    
};


// Initializes the application.
INT32 xfcAppInit()
{
    // Initialize default core features.
    xfcUseDefaults();
    // Create an instance of the application class.
    XFFPlayer::create();
    return 0;
}


// Configures the application.
void xfcAppPref(XFcAppPrefs &aPrefs)
{
#ifdef XFE_DEBUG
    aPrefs.mResourceMemoryLimit = 4 * 1024 * 1024;
    aPrefs.mTotalMemoryLimit = 4 * 1024 * 1024;
#else // or no XFE_DEBUG
    aPrefs.mResourceMemoryLimit = (INT32)(1.2f * 1024 * 1024);
    aPrefs.mTotalMemoryLimit = (INT32)(1.2f * 1024 * 1024);
#endif // no XFE_DEBUG
    aPrefs.mMinimumExtraMemory = 128 * 1024;

    aPrefs.mUID = 0x101f4f8c;
}


XFFPlayer::XFFPlayer() :
mGL(NULL),
mGameGraph(NULL),
mState(STATE_PAUSED),
mPrinter(NULL)
{
}


void XFFPlayer::onAppInit()
{
    // Create the GL.
    mGL = XFcGL::create();
    
    mPrinter = XFuPrinter::create(XFCSTR("font16.pcx"), 0);
    XFcProfiler::initEventLog();
    
    // Create the game graph and rendering contexts.
    mGameGraph = GameGraph::create(mGL);
    XFCASSERT(mGameGraph);
    
	// Disable dynamic lighting
    mGL->setStateI(XFCGLRS_LIGHTING, 0);
    
    // Load the game graph from an XFF file and quit if loading fails.
    if(!mGameGraph->loadFromXFF("scene.xff"))
    {
        XFCASSERT("Scene load failed!" && 0);
    }
    
    initAudio();
    
    // Define viewport:
    // For 240x320, objects in X=0..239, Y=0..319, Z=0..1 will be drawn.
    XFcGLViewport vp;
    vp.mXScreenOffset = 0;
    vp.mYScreenOffset = 0;
    vp.mAreaWidth = XFcCore::getDeviceWidth();
    vp.mAreaHeight = XFcCore::getDeviceHeight();
    vp.mMinZ = REALf(0.0);
    vp.mMaxZ = REALf(1.0);
    mGL->setViewport(vp);
    

    XFcCore::setController(this);
    XFcCore::setRenderer(this);

    mState = STATE_RUNNING;
}


void XFFPlayer::onAppDeinit()
{
    delete mGameGraph;

    delete mPrinter;
    delete mGL;
}


XFFPlayer * XFFPlayer::create()
{
    return new XFFPlayer();
}


INT XFFPlayer::onDeviceStateEvent(INT32 aEvent, INT32 aSeverity, void * /*aMoreInfo*/)
{
    if (aEvent == XFCDSE_FOCUSLOST)
    {
        XFcExclusiveModeSettings settings;
        XFcCore::setExclusiveMode(0, settings);
        XFcAudio::stopAll();
        XFcAudio::closeAudio();
        mState = STATE_PAUSED;
    }
    if (aEvent == XFCDSE_FOCUSGAIN)
    {
        mState = STATE_RUNNING;
        XFcExclusiveModeSettings settings;
        XFcCore::setExclusiveMode(1, settings);
        initAudio();
    }

    if (aSeverity == XFCDSE_SEVERITY_CRITICAL)
        XFcCore::quit();

    return 0;
}


void XFFPlayer::initAudio()
{
    XFcAudio::setAudioFormat(NULL, 8, XFCAUDIO_INTERPOLATION_NONE);
}


void XFFPlayer::onControlDown(INT32 /*aCode*/)
{
    // Quit when a control is pressed.
    XFcCore::quit();
}


void XFFPlayer::onPointerDown(INT32 /*aX*/, INT32 /*aY*/)
{
    if  (mState == STATE_RUNNING)
    {
        // Quit when screen is tapped with stylus (or clicked with mouse).
        XFcCore::quit();
    }
    else
    {
        mState = STATE_RUNNING;
        XFcExclusiveModeSettings settings;
        XFcCore::setExclusiveMode(1, settings);
        initAudio();
    }
}


void XFFPlayer::render()
{
    if (mState == STATE_RUNNING)
    {
        XFcProfiler::addEvent("clear");
        // Clear the screen..
        mGL->clear(0x7090a0);
        
        XFcProfiler::addEvent("render");
        // ..and render the game graph.
        mGL->beginRender();
        mGameGraph->render();
        mGL->endRender();
        
        XFcProfiler::frameEvent();
        
        XFcGLSurface *fb = mGL->getSecondary();

        // If you want to see debug output, uncomment this line and put font16.pcx to the program directory
//        mPrinter->print(fb, 0, 0, XFcProfiler::getEventLog());
        XFcProfiler::resetEvent("print", "core ");
    }
}
