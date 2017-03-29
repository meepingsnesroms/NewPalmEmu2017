/*! \file
* GameScreen.h <br>
* Copyright 2003 Fathammer Ltd
*
* $Id: GameScreen.h,v 1.7 2003/08/06 11:42:45 jari Exp $
* $Date: 2003/08/06 11:42:45 $
* $Revision: 1.7 $
*/

#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED

class XFuFPSCount;
class XFuRandom;
class XFuPrinter;

class Screen;
class Sprite;
class Plane;
class Level;
class StuntPlane;

// Key pressed bitmasks.

#define SP_LEFT     1
#define SP_RIGHT    2
#define SP_UP       4
#define SP_DOWN     8

#define SP_ROTATE_LEFT       16
#define SP_ROTATE_RIGHT      32


//! Screen used for the ingame parts of StuntPlane.
class GameScreen : public Screen
{

public:
    //! Static constructor.
    static GameScreen * create(XFcGL *aGL, XFuPrinter *aPrinter);

    ~GameScreen();

// Inherited from XFcInput:

    //! Callback: control pressed.
    virtual void onControlDown(INT32 aCode);

    //! Callback: control released.
    virtual void onControlUp(INT32 aCode);

    //! Callback: control pressed.
    virtual void onKeyDown(INT32 aCode);

    void onJoystickMoved(INT32 aX, INT32 aY);

// Inherited from XFcRenderer:

    //! Renders the game screen.
    virtual void render();

    //! Called when this object is set as current renderer.
    virtual void initRenderer();

    //! Called when another object is set as current renderer.
    virtual void deinitRenderer();

    //! Save current game state to a file.
    INT saveGameState(const CHAR *aFileName);

    //! Load saved game state from a file.
    INT loadGameState(const CHAR *fileName);

    //! Load and parse a level definition file.
    INT loadLevel(INT aLevel);
    
    //! Initialize gameplay.
    void initGameLogic();

    //! Starts playing a sound if sound effects are enabled.
    void playSound(XFcAudioBuffer *mSound);

private:
    // Private constructor.
    GameScreen(XFcGL *aGL);

// Private member functions.

    //! Printer centered text string at given y coordinate.
    void centerString(INT aY, const CHAR *aString);

    //! Update plane orientation, check collisions etc.
    void updateGameLogic();

    //! Updated status display at the top of the screen.
    void updateStatusDisplay(XFcGLSurface *fb);    
    
    //! Render the wind indicator at the bottom of the screen.
    void renderWindIndicator();


    //! Vertex buffer used for drawing the wind indicator.
    XFcGLVertexBuffer *mVB; 

    //! Random number generator used.
    XFuRandom   *mRand;

    //! Printer class used to draw ingame text (statusbar etc).
    XFuPrinter  *mPrinter;

    //! Sound effect audio buffers.
    XFcAudioBuffer *mBiplaneSound, *mBonusSound, *mCrashSound;
    
    //! The plane class. Code for loading and rendering the plane mesh.
    Plane *mPlane;

    //! The level class. Code for loading and rendering levels.
    Level *mLevel;

    //! Key pressed bitmask.
    INT32 mKeys;

    //! Current level coordinates.
    REAL mX, mY, mZ;
    
    //! Current plane speed.
    REAL mSpeedX, mSpeedY;

    //! Current plane orientation.
    REAL mCurrentAngleX, mCurrentAngleY, mCurrentAngleZ;
    
    //! Wanted plane orientation.
    REAL mWantedAngleX, mWantedAngleY, mWantedAngleZ;

    //! Extra tilt in Z-direction when turning.
    REAL mCurrentTiltZ, mWantedTiltZ;

    //! The plane roll angle when passing through last hoop.
    REAL mRollAtLastHoop;

    //! Wanted plane roll in 45-degree steps.
    INT mRoll;

    //! Current score.
    INT32 mScore;

    //! Number of times we have failed to go through a hoop.
    INT mMisses;

    INT mShowMessage;

    //! Number of collected bonus items collected in a row.
    INT mBonusInARow;

    //! Just draw the plane every other frame if > 0.
    INT mFlashing;
    
    //! Do crash animation if > 0.
    INT mCrash;

    //! Direction of current wind gust.
    REAL mGustAngle;

    //! Indicated that a windgust is currently taking place if > 0.
    INT mGustInProgress;

    //! Incremented every frame. Used to make the plane flicker on a miss.
    INT32 mFrames;
    
    //! Current time (in ticks) of game logic.
    INT32 mLogicTick;
        
    //! Used for debugging.
    REAL  mDir;    
    XFuFPSCount *mFPS;

    //! Joystick position.
    REAL mJoystickX, mJoystickY;

    const CHAR *mMessage;
};


#endif // !GAMESCREEN_H_INCLUDED
