/*! \file
 * StuntPlane.cpp <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: StuntPlane.cpp,v 1.14.2.1 2003/10/31 14:54:13 niko Exp $
 * $Date: 2003/10/31 14:54:13 $
 * $Revision: 1.14.2.1 $
 */

#include <xforge.h>
#include <xfutil/XFuPrinter.h>
#include <xfutil/XFuXMPlayer.h>

#include "Plane.h"
#include "Screen.h"
#include "SplashScreen.h"
#include "GameScreen.h"
#include "MenuScreen.h"
#include "StuntPlane.h"


//! Initializes the application.
INT32 xfcAppInit()
{    
    // Initialize default core features.
    xfcUseGLDefault();
    xfcUseImageFilterPCX();
    xfcUseAudioDefault();
    xfcUseCFLFilterZlib();

    // Create an instance of the application class.    
    StuntPlane::create();
    return 0;
}


//! Configures the application.
void xfcAppPref(XFcAppPrefs &aPrefs)
{
#ifdef SP_DEBUG
    aPrefs.mResourceMemoryLimit = 2 * 1024 * 1024;
    aPrefs.mTotalMemoryLimit = 2 * 1024 * 1024;
#else
    aPrefs.mResourceMemoryLimit = (INT32)(1.8f * 1024 * 1024);
    aPrefs.mTotalMemoryLimit = (INT32)(1.8f * 1024 * 1024);
#endif
    aPrefs.mMinimumExtraMemory = 128 * 1024;

#ifdef XFC_PLATFORM_DESKTOPWINDOWS
    aPrefs.mPreferredWidth = 176 * 1;
    aPrefs.mPreferredHeight = 220 * 1;
#endif

#ifdef SP_TAPWAVE_VERSION
    // We need more memory for the big bitmaps used on tapwave.
    aPrefs.mResourceMemoryLimit = (INT32)(4.5f * 1024 * 1024);
    aPrefs.mTotalMemoryLimit = (INT32)(4.5f * 1024 * 1024);
    aPrefs.mPreferredWidth = 480;
    aPrefs.mPreferredHeight = 320;
#endif
#ifdef SP_SMARTPHONE_VERSION
    aPrefs.mResourceMemoryLimit = (INT32)(1.23 * 1024 * 1024);
    aPrefs.mTotalMemoryLimit = (INT32)(1.23 * 1024 * 1024);
    aPrefs.mPreferredWidth = 176;
    aPrefs.mPreferredHeight = 220;
#endif
#ifdef SP_S60_VERSION
    aPrefs.mPreferredWidth = 176;
    aPrefs.mPreferredHeight = 208;
#endif
#ifdef SP_POCKETPC_VERSION
    aPrefs.mResourceMemoryLimit = (INT32)(2.0f * 1024 * 1024);
    aPrefs.mTotalMemoryLimit = (INT32)(2.0f * 1024 * 1024);
    aPrefs.mPreferredWidth = 240;
    aPrefs.mPreferredHeight = 320;
#endif
    aPrefs.mUID = 0x101F90A3;
}


//! Static constructor.
StuntPlane * StuntPlane::create()
{
    return new StuntPlane();
}


StuntPlane::StuntPlane()
{
    mLevel = 0;
    mPlayerId = 0;
    mSwitchScreen = 0;

    mGL = NULL;
    mPrinter = NULL;
    mMenuScreen = NULL;
    mGameScreen = NULL;
    mSplashScreen = NULL;
    mCurrentScreen = NULL;
    mPlayer = NULL;
}


//! Called when the application is being initialized.
void StuntPlane::onAppInit()
{
    // Create the GL.
    mGL = XFcGL::create();
    XFCASSERT(mGL);

    // Open Compressed File Library.
    if (!XFcCore::openCFL(SP_CFL_FILE))
    {
        XFcCore::systemPanic(XFCSTR("Can't open CFL file!'"));
    }
    // Create menu text printer.
    mPrinter = XFuPrinter::create(XFCSTR("stunt_font.pcx"), 0xffffffff);
    XFCASSERT(mPrinter);

    initAudio();

    // Try to load configurarion.
    if (!loadConfig(XFCSTR("stuntplane.cfg")))
    {
        // Not found, use default configuration.
        mMusic = ~0;
        mSound = ~0;
        mPilot = 0;
        mHighScore = 0;
    }

    // Create game screen.
    mMenuScreen = MenuScreen::create(mGL, mPrinter);
    if (mMenuScreen == NULL)
    {
        XFcCore::systemPanic(XFCSTR("Can't open create menu screen."));
    }

    mSplashScreen = SplashScreen::create(mGL);
    XFCASSERT(mSplashScreen);

    initMusic();
    
    // Start in 'SPLASH' mode.
    setScreen(mSplashScreen);
    setState(SP_STATE_SPLASH);
}            


//! Called when the application quit.
void StuntPlane::onAppDeinit()
{
    delete mGameScreen;
    delete mMenuScreen;

    delete mPrinter;
    delete mGL;

    delete mPlayer;

    closeAudio();
}


//! Called to change game state.
void StuntPlane::setState(SP_GAME_STATE aState) 
{ 
    mStateSetAtTick = XFcCore::getTick();
    mState = aState;

    switch (aState) 
    {
    case SP_STATE_MENU:
        setScreen(mMenuScreen);
        initMusic();
        break;
    case SP_STATE_OPTIONS:
        break;
    case SP_STATE_LOADING:
        // Switch over rendering and control to game screen now.
        XFcCore::setController(mGameScreen);
        XFcCore::setRenderer(mGameScreen);    
        mCurrentScreen = mGameScreen;
        break;
    }
}


//! Schedule screen change for next tick.
void StuntPlane::setScreen(Screen *aScreen)
{
    if (mCurrentScreen != aScreen) 
    {
        mCurrentScreen = aScreen;
        mSwitchScreen = 1;
    }
}        


//! Delete gamescreen in a safe way.
void StuntPlane::quitPlaying()
{

    /* Set renderer to NULL. This is done so that the "deinitRender()" 
     * in the soon to be deleted GameScreen object is not called when
     * we switch back to the main menu renderer.
     */
    XFcCore::setController(NULL);
    XFcCore::setRenderer(NULL);    
    mCurrentScreen = NULL;
    
    delete mGameScreen;
    mGameScreen = NULL;
}


//! Load XM player and start playing.
void StuntPlane::initMusic()
{
    // Create XM player:
    if (mPlayer == NULL) 
    {
        mPlayer = XFuXMPlayer::create(XFCSTR("grl01.xm"), 8000, 0);
        XFCASSERT(mPlayer);
    }

    // Start playing
    if (!XFcAudio::isPlaying(mPlayerId) && playMusic()) 
    {
        mPlayerId = XFcAudio::play(mPlayer);
    }
}


//! Stop and deallocate XM player.
void StuntPlane::deinitMusic()
{
    if (mPlayer) 
    {
        XFcAudio::stop(mPlayerId);
        delete mPlayer;
        mPlayer = NULL;
    }
}


//! Called from the main loop before the rendering starts.
void StuntPlane::onTick()
{
    // Switch to new screen if neccessary.
    if (mSwitchScreen) 
    {
        XFcCore::setController(mCurrentScreen);
        XFcCore::setRenderer(mCurrentScreen);    
        mSwitchScreen = 0;
    }    

    switch (mState) 
    {

        case SP_STATE_SPLASH:
            // Show splashscreens for a while.
            if (currentStateDuration() > 2500)
            {
                setState(SP_STATE_MENU);
            }
            break;
                
        
        case SP_STATE_GAMECOMPLETE:
                
            delete mGameScreen;
            mGameScreen = NULL;    

            if (currentStateDuration() > 3000) 
            {
                if (mScore > mHighScore) 
                {
                    setState(SP_STATE_HIGHSCORE);
                }
                else 
                {
                    setState(SP_STATE_MENU);
                }
            }
            break;

        // Show loading screen for 2.5 seconds.
        case SP_STATE_LOADING:
            if (currentStateDuration() > 2500) 
            {            
                setState(SP_STATE_PLAYING);
                mGameScreen->initGameLogic();
            }
            break;

        // Jump to next level...
        case SP_STATE_NEXTLEVEL:

            mLevel++;

            if (mLevel == 1) 
            {
                mScore = 0;
                deinitMusic();
            }

            quitPlaying();

            // Last level finished?
            if (mLevel > SP_NR_LEVELS) 
            {   
                setScreen(mMenuScreen);
                setState(SP_STATE_GAMECOMPLETE);

                break;
            }        

            mGameScreen = GameScreen::create(mGL, mPrinter);

            if (mGameScreen == NULL)
            {
                XFcCore::systemPanic(XFCSTR("Can't create game screen."));
            }        
            
            if (!mGameScreen->loadLevel(mLevel))
            {
                XFcCore::systemPanic(XFCSTR("Can't load level."));
            }        

            setState(SP_STATE_LOADING);            
            break;

        case SP_STATE_CONTINUE:
            // Try to continue a previously saved game...

            if (mMenuScreen->savedGameFound()) {

                // Delete old gamescreen if there is one.
                delete mGameScreen;
                XFcCore::setRenderer(NULL);
                mCurrentScreen = NULL;

                //Try loading game state.
                mGameScreen = GameScreen::create(mGL, mPrinter);        
                mLevel = mGameScreen->loadGameState(XFCSTR("saved.bin"));
                if (mLevel == -1) 
                {
                    // Didn't work, go back to menu.
                    delete mGameScreen;
                    mGameScreen = NULL;
                    setState(SP_STATE_MENU);
                }
                else 
                {
                    // Start playing using loaded game state.
                    XFcFile::remove(XFCSTR("saved.bin"));
                    deinitMusic();
                    mGameScreen->loadLevel(mLevel);
                    setState(SP_STATE_LOADING);
                }
            }
            else 
            {
                // Not found, go back to menu mode.
                setState(SP_STATE_MENU);
            }
            break;

        case SP_STATE_LEVELCOMPLETE:
            if (currentStateDuration() > 3000)
            {
                setState(SP_STATE_NEXTLEVEL);
            }
            break;

        // Game Over. Show overlay for 3 seconds and continue.
        case SP_STATE_GAMEOVER:
            if (currentStateDuration() > 3000) 
            {

                quitPlaying();
                XFcCore::setController(mMenuScreen);
                XFcCore::setRenderer(mMenuScreen);    
                mCurrentScreen = mMenuScreen;

                if (mScore >= mHighScore) 
                {
                    setState(SP_STATE_HIGHSCORE);
                }
                else 
                { 
                    setState(SP_STATE_MENU);
                }
            }            
            break;

        case SP_STATE_HIGHSCORE:
            if (mScore < mHighScore) 
            {
                setState(SP_STATE_MENU);
            }
            else 
            {
                mHighScore = mScore;
                if (currentStateDuration() > 3000) setState(SP_STATE_MENU);
            }
            break;

        case SP_STATE_PAUSE:
            if (mGameScreen) 
            {
                mGameScreen->saveGameState(XFCSTR("saved.bin"));        
                quitPlaying();                
                setState(SP_STATE_MENU);
            }
            break;

        case SP_STATE_CREDITS:
            if (currentStateDuration() > 25000) 
            {
                setState(SP_STATE_QUIT);
            }            
            break;

        case SP_STATE_QUIT:
            saveConfig(XFCSTR("stuntplane.cfg"));
            XFcFile::remove(XFCSTR("saved.bin"));
            XFcCore::quit();
            break;
    }

}


//! Called when some external event, like a phone call, occurs.
INT StuntPlane::onDeviceStateEvent(INT32 aEvent, INT32 aSeverity, void * /*aMoreInfo*/)
{

    if (aSeverity == XFCDSE_SEVERITY_CRITICAL)
    {
        if (mGameScreen && getState() == SP_STATE_PLAYING)
        {
            mGameScreen->saveGameState(XFCSTR("saved.bin"));
        }
        saveConfig(XFCSTR("stuntplane.cfg"));
        XFcCore::quit();
    }    
    
    switch (aEvent) 
    {
        case XFCDSE_FOCUSLOST:
            XFcCore::setExclusiveMode(0, settings);
        
            deinitMusic();
            closeAudio();

            if (mGameScreen) 
            {
                // Go back to main menu if gamescreen active.
                if (getState() == SP_STATE_PLAYING) 
                {
                    // Save game if playing.  
                    mGameScreen->saveGameState(XFCSTR("saved.bin"));
                }
                quitPlaying();                
                
                // Switch back renderer and controller directly.
                XFcCore::setController(mMenuScreen);
                XFcCore::setRenderer(mMenuScreen);    
                mCurrentScreen = mMenuScreen;

                setState(SP_STATE_MENU);
            }
            break;

        case XFCDSE_FOCUSGAIN:
            XFcCore::setExclusiveMode(1, settings);
            initAudio();
            initMusic();
            break;

        case XFCDSE_AUDIOLOST:
            closeAudio();
            break;
        default:
            break;
    }        
    return 0;
}


//! Initialize audio.
void StuntPlane::initAudio()
{
    XFcAudio::setAudioFormat(NULL, 16, 0);
}


//! Shut down audio.
void StuntPlane::closeAudio()
{
    XFcAudio::stopAll();
    XFcAudio::closeAudio();
}


//! Toggle music on/off.    
void StuntPlane::toggleMusic()
{ 
    mMusic = ~mMusic; 
    if (mMusic) mPlayerId = XFcAudio::play(mPlayer);
    else XFcAudio::stop(mPlayerId);        
}


//! Load game config from file.
INT StuntPlane::loadConfig(const CHAR *aFileName)
{
    XFcFile *file = XFcFile::open(aFileName, XFCSTR("rb"));

    if (file == NULL) return 0;

    file->seek(0, SEEK_SET);

    mMusic = file->readUINT32();
    mSound = file->readUINT32();
    mPilot = file->readUINT32();    

    mHighScore = file->readUINT32();    
    
    file->close();

    return 1;
}


//! Save game config to file.
INT StuntPlane::saveConfig(const CHAR *aFileName)
{
    XFcFile *file = XFcFile::open(aFileName, XFCSTR("wb"));

    if (file == NULL) return 0;

    file->seek(0, SEEK_SET);

    file->writeUINT32(mMusic);
    file->writeUINT32(mSound);
    file->writeUINT32(mPilot);    

    mHighScore = file->writeUINT32(mHighScore);    
    
    file->close();

    return 1;
}
