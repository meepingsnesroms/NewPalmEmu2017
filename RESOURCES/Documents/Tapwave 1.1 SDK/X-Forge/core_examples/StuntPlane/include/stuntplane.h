/*! \file
* StuntPlane.h <br>
* Copyright 2003 Fathammer Ltd
*
* $Id: stuntplane.h,v 1.18.2.1 2003/10/31 13:24:05 niko Exp $
* $Date: 2003/10/31 13:24:05 $
* $Revision: 1.18.2.1 $
*/

#ifndef STUNTPLANE_H_INCLUDED
#define STUNTPLANE_H_INCLUDED

class XFuXMPlayer;
class XFuPrinter;
class Screen;
class MenuScreen;
class GameScreen;
class SplashScreen;


// Uncomment this for some debugging stuff, like shortkeys for quitting, FPS meter etc.

//#define SP_DEBUG
//#define SP_ANALOG_JOYSTICK

//! Defines for different platforms. Uncomment the one you want to compile for.
//#define SP_WINDOWS_VERSION
//#define SP_SMARTPHONE_VERSION
//#define SP_UIQ_VERSION
//#define SP_S60_VERSION
//#define SP_TAPWAVE_VERSION
//#define SP_POCKETPC_VERSION

// The width and height of the level.
#define SP_LEVEL_MAX_XY            160

// Number of levels.
#define SP_NR_LEVELS               8

//! Resolution of the ingame backdrop images.
#if defined(SP_TAPWAVE_VERSION)

    #define SP_BACKDROP_WIDTH      960
    #define SP_BACKDROP_HEIGHT     640
    #define SP_CFL_FILE            XFCSTR("stuntplane480x320.cfl")

    #ifndef XFC_PLATFORM_DESKTOPWINDOWS
        #define SP_ANALOG_JOYSTICK
    #endif

#elif defined(SP_POCKETPC_VERSION)

    #define SP_BACKDROP_WIDTH      480
    #define SP_BACKDROP_HEIGHT     640
    #define SP_CFL_FILE            XFCSTR("stuntplane240x320.cfl")

#else
    #define SP_BACKDROP_WIDTH      352
    #define SP_BACKDROP_HEIGHT     440
    #define SP_CFL_FILE            XFCSTR("stuntplane176x220.cfl")
#endif


// Adjust parameters for landscape view on tapwave devices.
#if defined(SP_TAPWAVE_VERSION)
    #define FLARE_CENTER_X   70
    #define FLARE_CENTER_Y   80
    #define FLARE_RADIUS     400 
#else
    #define FLARE_CENTER_X   116
    #define FLARE_CENTER_Y   128
    #define FLARE_RADIUS     256
#endif


// Nr of allowed misses per level.
#ifdef SP_DEBUG
    #define SP_MAX_MISSES 300
#else
    #define SP_MAX_MISSES 3
#endif

    
// Just some convenient macros.
#define ABS(x)               (x) >= 0 ? (x) : (-(x))
#define MIN(x, y)            ((x) < (y) ? (x) : (y))
#define MAX(x, y)            ((x) > (y) ? (x) : (y))


//! Game application running states.
enum SP_GAME_STATE
{
    SP_STATE_SPLASH = 0,
    SP_STATE_MENU,
    SP_STATE_OPTIONS,
    SP_STATE_NEXTLEVEL,
    SP_STATE_LOADING,
    SP_STATE_LEVELCOMPLETE,
    SP_STATE_GAMECOMPLETE,
    SP_STATE_HIGHSCORE,
    SP_STATE_SHOWSCORE,
    SP_STATE_CONTINUE,
    SP_STATE_RUNNING,    
    SP_STATE_PAUSE,
    SP_STATE_PLAYING,
    SP_STATE_GAMEOVER,
    SP_STATE_CREDITS,
    SP_STATE_QUIT
};


//! The main application class.
/*! Owns the GL and the screens used in the game. This is also a 
 *  "state change handler" for the state machine and controls the 
 *  application flow.
 */
class StuntPlane : public XFcApp
{

public:
    //! Static constructor.
    static StuntPlane * create();

// Inherited from XFcApp:

    //! Called when application is initialized.
    virtual void onAppInit();

    //! Called when application is initialized.
    virtual void onTick();
    
    //! Called on application quit (cleanup).
    virtual void onAppDeinit();

    //! Called when a device state event occurs.
    virtual INT onDeviceStateEvent(INT32 aEvent, INT32 aSeverity, void *aMoreInfo);

    //! Set game state.
    void setState(SP_GAME_STATE aState);

    //! Get game state.
    SP_GAME_STATE getState() { return mState; }

    //! Return the duration of the current state in milliseconds.
    INT32 currentStateDuration() { return XFcCore::getTick() - mStateSetAtTick; }

    //! Return current level.
    INT currentLevel(void) { return mLevel; }

    //! Returns true if menu music should be played.
    INT playMusic(void) { return mMusic; }

    //! Returns true if in game sound effects should be played.
    INT playSounds(void) { return mSound; }

    //! Returns true if pilot controls should be used (i.e reverse vertical controls).
    INT pilotControls(void) { return mPilot; }

    //! Toggle music on/off.    
    void toggleMusic();

    //! Toggle sound on/off.
    void toggleSound() { mSound = ~mSound; }

    //! Toggle pilot mode on/off.
    void togglePilotMode() { mPilot = ~mPilot; }

    //! Set current level.
    void setLevel(INT aLevel) { mLevel = aLevel; }

    //! Set score.
    void setScore(INT32 aScore) { mScore = aScore; }
    
    //! Get current score.
    INT32 getScore() { return mScore; }

    //! Return current highscore.
    INT32 getHighscore() { return mHighScore; }

    //! Load configuration from a file.
    INT loadConfig(const CHAR *aFileName);

    //! Save configuration to a file.
    INT saveConfig(const CHAR *aFileName);

    //! Switch to another screen at next tick.
    void setScreen(Screen *aScreen);
    
    //! Deallocate game screen.
    void quitPlaying();

    //! Load XM player and start playing.
    void initMusic();

    //! Stop and deallocate XM player.
    void deinitMusic();

private:

    //! Private constructor.
    StuntPlane();

    //! Initializes audio, can be also used to reinitialize it.
    void initAudio();

    //! Stops audio.
    void closeAudio();

    
    //! External event settings.
    XFcExclusiveModeSettings settings;

    //! Pointer to graphics library.
    XFcGL *mGL;

    //! Pointer to game screen.  
    GameScreen *mGameScreen;
    
    //! Pointer to menu screen.
    MenuScreen *mMenuScreen;

    //! Pointer to splash screen.
    SplashScreen *mSplashScreen;

    //! Pointer to current active screen.
    Screen *mCurrentScreen;
    
    //! Application state.
    SP_GAME_STATE mState;

    //! The menu screen bitmap font printer.
    XFuPrinter *mPrinter;

    //! The menuscreen XM module player.
    XFuXMPlayer *mPlayer;

    //! Audio id for identifying the menuscreen XM player.
    UINT32 mPlayerId;

    //! Used to indicate that a screen switch is needed next tick.
    INT mSwitchScreen;

    //! Current level.
    INT mLevel;

    //! Current score.
    INT32 mScore;

    //! All time highscore.
    INT32 mHighScore;
  
    //! User preferences.
    INT mPilot, mSound, mMusic;

    //! The tick at which the last state change occured.
    INT32 mStateSetAtTick;
};

#endif // !STUNTPLANE_H_INCLUDED
