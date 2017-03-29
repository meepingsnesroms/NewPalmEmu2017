/*! \file
 * GameScreen.cpp <br>
 * Copyright 2003 Fathammer Ltd
 *
 * \brief Main gameplay code for the StuntPlane core example.
 *
 * $Id: GameScreen.cpp,v 1.13 2003/08/07 07:50:42 lars Exp $
 * $Date: 2003/08/07 07:50:42 $
 * $Revision: 1.13 $
 */

#include <xforge.h>
#include <xfcore/XFcVibrate.h>

#include <xfutil/XFuPrinter.h>
#include <xfutil/XFuDynamicArray.h>
#include <xfutil/XFuFPSCount.h>
#include <xfutil/XFuWavLoad.h>
#include <xfutil/XFuRandom.h>

#include "Screen.h"
#include "Sprite.h"
#include "Plane.h"
#include "Level.h"
#include "GameScreen.h"
#include "StuntPlane.h"
#include "Objects.h"


// Game constants. These are just numbers and not measured in any particular unit.
    

// Camera position (X=0). The plane is located at (0,0,0).
#define CAMERA_Y            (8)
#define CAMERA_Z            (-32)


// Number of game state updates per second.
#define LOGIC_FPS           100

// Wingspan of the plane.
#define PLANE_WIDTH         REALf(26.8f)

// Hoop size.
#define HOOP_DIAMETER       40

// Bonus item size.
#define BONUS_DIAMETER      16

// The tolerated deviation from required angle.
#define ANGLE_TOLERANCE     (PI / 20)

// Constand speed ahead.
#define FORWARD_SPEED       REALf(0.28f)

// Plane up/down/left/right acceleration.
#define STRAFE_ACCEL        REALf(0.008f)

// Maximum horizontal/vertical speed.
#define MAX_STRAFE_SPEED    REALf(3.2f)

// Speed of plane rotation and leveling.
#define ROTATION_SPEED      REALf(0.003f)

// Frequency of plane wobbling.
#define WOBBLE_SPEED        REALf(0.002f)

// Convert milliseconds to number of game logic ticks.
#define MS_TO_TICKS(x)      (LOGIC_FPS * (x) / 1000)


//! Constructor.
GameScreen::GameScreen(XFcGL *aGL) : Screen(aGL)
{
#ifdef SP_DEBUG
    mFPS = NULL;
    mDir = REALi(1);
#endif
    mPrinter = NULL;
    mRand = NULL;
    mPlane = NULL;
    mLevel = NULL;
    
    mBiplaneSound = mBonusSound = mCrashSound = NULL;

    mRoll = 0;
    mX = mY = mZ = mSpeedX = mSpeedY = REALi(0);
    mCurrentAngleX = mWantedAngleX = REALi(0);
    mCurrentAngleY = mWantedAngleY = REALi(0);
    mCurrentAngleZ = mWantedAngleZ = REALi(0);

    mCurrentTiltZ = mWantedTiltZ = REALi(0);

    mKeys = 0;
    mJoystickX = 0;
    mJoystickY = 0;

    mFlashing = 0;

    mMisses = 0;
    mCrash = 0;
    mScore = 0;
    mBonusInARow = 0;
    mGustInProgress = 0;

    mShowMessage = 0;
    mRollAtLastHoop = 0;
}


GameScreen::~GameScreen()
{
    XFcAudio::stopAll();

    delete mPlane;
    delete mLevel;

    delete mVB;
    
    delete mBiplaneSound;
    delete mBonusSound;
    delete mCrashSound;

    delete mRand;

#ifdef SP_DEBUG
    delete mFPS;
#endif
}


//! Static creation.
GameScreen * GameScreen::create(XFcGL *aGL, XFuPrinter *aPrinter)
{
    GameScreen *gs = new GameScreen(aGL);
    XFCASSERT(gs);

    gs->mVB = XFcGLVertexBuffer::create(XFCGL_TLVERTEX, sizeof(XFcGLTLVertex), 3);   

#ifdef SP_DEBUG
    gs->mFPS = XFuFPSCount::create(25);
#endif
    
    gs->mPrinter = aPrinter;
    gs->mRand = XFuRandom::create(0xc0cac01a);

    // Load sound effects.
    gs->mBiplaneSound = xfuLoadWav(XFCSTR("biplane.wav"));
    gs->mBonusSound = xfuLoadWav(XFCSTR("click.wav"));
    gs->mCrashSound = xfuLoadWav(XFCSTR("crash.wav"));

    // Create the plane object.
    gs->mPlane = Plane::create(gs->mGL, XFCSTR("stunt_plane.xff"));

    // Create the level object.
    gs->mLevel = Level::create();

    // Make sure everything is ok.
    if (!(gs->mVB && 
          gs->mRand &&
          gs->mBiplaneSound && 
          gs->mBonusSound && 
          gs->mCrashSound &&
          gs->mPlane && 
          gs->mLevel))
    {        
        delete gs;
        return NULL;
    }

    return gs;
}


//! Called when this object is set as current renderer.
void GameScreen::initRenderer()
{

    // Define viewport: leave 24 pixels at the top for the status display.
    XFcGLViewport vp;
    vp.mXScreenOffset = 0;
    vp.mYScreenOffset = 24;
    vp.mAreaWidth = XFcCore::getDeviceWidth();
    vp.mAreaHeight = XFcCore::getDeviceHeight() - 24;
    vp.mMinZ = REALf(0.0f);
    vp.mMaxZ = REALf(1.0f);
    mGL->setViewport(vp);

    // Camera matrix: Place camera behind the plane, looking at the origin.
    XFcMatrix4 cameraMatrix;
    XFcMath::matrixLookAt(cameraMatrix, 
                          XFcVector3(0, CAMERA_Y, CAMERA_Z), 
                          XFcVector3(0, 0, 0), 
                          XFcVector3(0, 1, 0));

    XFcMath::matrixInverseFast(cameraMatrix);
    mGL->setMatrix(XFCGLMAT_VIEW, cameraMatrix);

    // Projection Matrix: Field of view = 90 degrees = PI/2.
    // Nearest z-coordinate to render is 1 and farest 1000.
    XFcMatrix4 matrixProjection;        
    XFcMath::matrixToProjection(matrixProjection,
                                XFcCore::getDeviceHeight(),
                                XFcCore::getDeviceWidth(),
                                PI / 2, 1, 1000);

    // Set Projection matrix.
    mGL->setMatrix(XFCGLMAT_PROJECTION, matrixProjection);

#if (defined(SP_UIQ_VERSION) || defined(SP_TAPWAVE_VERSION))

    XFcRectangle rect;

    /*
     *  Create a grid of screen button to replace joystick.
     *   __ __ __
     *  |  |  |  |
     *  |__|__|__|
     *  |  |  |  |
     *  |__|__|__|
     *  |  |  |  |
     *  |__|__|__|
     *
     *  This is mostly for devices lacking other 
     *  forms of input (like the P800).
     */

    INT x, y;
    REAL width = XFcCore::getDeviceWidth() / 3;
    REAL height = XFcCore::getDeviceHeight() / 3;

    INT scanCode = 10000;

    for (y = 0; y < 3; y++) 
    { 
        for (x = 0; x < 3; x++) 
        {
            
            // We dont need the center button.
            if (x == 1 && y == 1) continue;

            // Create button.
            rect.mX = x * width;
            rect.mY = y * height;
            rect.mWidth = width;
            rect.mHeight = height;
            XFcCore::addScreenButton(rect, scanCode);

            // Map screen buttons to control codes. 
            if (x == 0) 
            {
                XFcCore::mapControlCode(XFCCL_LEFT, scanCode);
            }
            else 
            {
                if (x == 2) XFcCore::mapControlCode(XFCCL_RIGHT, scanCode);
            }

            if (y == 0) 
            {
                XFcCore::mapControlCode(XFCCL_UP, scanCode);
            }
            else 
            {
                if (y == 2) XFcCore::mapControlCode(XFCCL_DOWN, scanCode);
            }

            scanCode++;
        }
    }   
#endif

    mLogicTick = XFcCore::getTick();
}


//! Called when another object is set as renderer.
void GameScreen::deinitRenderer()
{
    // Get rid of virtual buttons and their control key mappings.
    XFcCore::resetScreenButtons();
    XFcCore::resetControlMappings();
}


//! Load and parse a level definition file.
INT GameScreen::loadLevel(INT aLevel) 
{ 
    INT result = mLevel->load(aLevel);
    mLevel->getStartXY(mX, mY);

    REAL r, g, b;
    mLevel->getPlaneColor(r, g, b);
    mPlane->colorize(r, g, b);
    
    return result;
}


//! Called just before the actual gameplay starts. Starts sounds etc.
void GameScreen::initGameLogic()
{
    mLogicTick = XFcCore::getTick();
    
    mScore = mApp->getScore();

    if (mApp->playSounds()) 
    {
        XFcAudio::setLooping(mBiplaneSound, 1);

        XFcAudio::play(mBiplaneSound);
        XFcAudio::setVolume(mBiplaneSound, REALf(0.3f));
    }
#ifdef XFC_PLATFORM_DESKTOPWINDOWS

    // Map keyboard 'A' and 'D' to rolling on windows.
    XFcCore::mapControlCode(XFCCL_FIRE1, 'A');
    XFcCore::mapControlCode(XFCCL_FIRE2, 'D');

    // Map ESC to FIRE3 = abort game.
    XFcCore::mapControlCode(XFCCL_FIRE3, 27);
#endif

#ifdef SP_SMARTPHONE_VERSION
	// Use numeric keys on smartphone.
    XFcCore::mapControlCode(XFCCL_LEFT, '4');
    XFcCore::mapControlCode(XFCCL_RIGHT, '6');
    XFcCore::mapControlCode(XFCCL_UP, '2');
    XFcCore::mapControlCode(XFCCL_DOWN, '8');
    XFcCore::mapControlCode(XFCCL_FIRE1, '5');
#endif
}


//! Play sound effect if sound is enabled.
void GameScreen::playSound(XFcAudioBuffer *mSound)
{
    if (mApp->playSounds()) XFcAudio::play(mSound);
}


//! Printer centered text string at given y coordinate.
void GameScreen::centerString(INT aY, const CHAR *aString)
{
    INT32 textWidth, textHeight;
    mPrinter->stringMetrics(aString, textWidth, textHeight);    
    mPrinter->print(mGL->getSecondary(), mCenterX - textWidth / 2, aY, 
                    aString, XFCBLEND_MUL, 0xff);
}


//! Called when a control key is pressed.
void GameScreen::onControlDown(INT32 aCode)
{
    if (mApp->getState() != SP_STATE_PLAYING) return;
    
    switch (aCode) 
    {
#ifndef SP_ANALOG_JOYSTICK
        case XFCCL_LEFT: 
            mKeys |= SP_LEFT;
            mWantedTiltZ = PI * 0.12f;
            break;    
        case XFCCL_UP: 
            mKeys |= (mApp->pilotControls() ? SP_DOWN : SP_UP);    
            mWantedAngleX = PI * (mApp->pilotControls() ? 0.12f : -0.12f);
            break;
        case XFCCL_RIGHT: 
            mKeys |= SP_RIGHT; 
            mWantedTiltZ = -PI * 0.12f;
            break;        
        case XFCCL_DOWN: 
            mKeys |= (mApp->pilotControls() ? SP_UP : SP_DOWN);    
            mWantedAngleX = PI * (mApp->pilotControls() ? -0.12f : 0.12f);
            break;
#endif
        case XFCCL_FIRE1:
            if (!(mKeys & SP_ROTATE_LEFT)) 
            {
                mKeys |= SP_ROTATE_LEFT;        
                mRoll++;
                mWantedAngleZ = REAL(mRoll) * PI / 4;
            }
            break;
        case XFCCL_FIRE2:     
            if (!(mKeys & SP_ROTATE_RIGHT)) 
            {
                mKeys |= SP_ROTATE_RIGHT; 
                mRoll--;   
                mWantedAngleZ = REAL(mRoll) * PI / 4;
            }
            break;

        // Make it possible to rotate using wheel controls.
        case XFCCL_WHEELDOWN:
            mKeys |= SP_ROTATE_LEFT;        
            mRoll++;    
           break;
        case XFCCL_WHEELUP:
            mKeys |= SP_ROTATE_RIGHT; 
            mRoll--;   
            break;           

        default:
            break;
    }

    mWantedAngleZ = REAL(mRoll) * PI / 4;
}


//! Called when a control key is released.
void GameScreen::onControlUp(INT32 aCode)
{
    switch (aCode) 
    {
#ifndef SP_ANALOG_JOYSTICK
        case XFCCL_LEFT: 
            mKeys &= ~SP_LEFT;  
            mWantedTiltZ = 0;                
            break;
        case XFCCL_UP:
            mKeys &= mApp->pilotControls() ? ~SP_DOWN : ~SP_UP;    
            mWantedAngleX = 0;
            break;
        case XFCCL_RIGHT:
            mKeys &= ~SP_RIGHT; 
            mWantedTiltZ = 0;
            break;
        case XFCCL_DOWN:
            mKeys &= mApp->pilotControls() ? ~SP_UP : ~SP_DOWN;            
            mWantedAngleX = 0;
            break;
#endif
        case XFCCL_FIRE1:     
            mKeys &= ~SP_ROTATE_LEFT;        
            break;
        case XFCCL_FIRE2:     
            mKeys &= ~SP_ROTATE_RIGHT; 
            break;
        case XFCCL_FIRE3:     
            mMisses = 1000; // Game Over            
            break;
        default:
            break;
    }
}


//! Called when keyboard key (for example alphanumeric) is pressed. Mostly used for debugging.
void GameScreen::onKeyDown(INT32 aCode)
{
    if (mApp->getState() != SP_STATE_PLAYING) return;

#ifdef SP_DEBUG    
    switch (aCode) 
    {
        // Theese are (can) only be used on the windows platform. 
        case 'B' : 
            mZ -= 20; 
            break;
        case 'F' : 
            mZ += 20; 
            break;    
        case 'P' :         
            saveGameState(XFCSTR("saved.bin"));
            mApp->setState(SP_STATE_PAUSE);
            break;
        case 'G' : // Game Over.
            mMisses = 100;
            return;
        case 'N' : // Jump to next level.
            mZ = mLevel->length() + 1;
            return;
        case 'Q' : // Quick quit.
            XFcCore::quit(); 
            break;            
        case 'S' : // Save game state.
            saveGameState(XFCSTR("saved.bin"));
            break;
        default:
            break;
    }
    mWantedAngleZ = REAL(mRoll) * PI / 4;
#endif
}


void GameScreen::onJoystickMoved(INT32 aX, INT32 aY)
{
#ifdef SP_ANALOG_JOYSTICK
    REAL ysign = (mApp->pilotControls() ? REALi(1) : REALi(-1));

    // Since we may be negating these values, make sure they fit within a 16 bit integer.
    if (aX < -32767) aX = -32767;
    if (aY < -32767) aY = -32767;
    
    mJoystickX = REALi(aX);
    mJoystickY = mApp->pilotControls() ? REALi(aY) : REALi(-aY);
    mWantedTiltZ = REALi(aX) / 32768 * (-PI * 0.12f);                
    mWantedAngleX = REALi(aY) / 32768 * (-PI * 0.12f) * ysign;                
#endif
}


//! Update game logic one tick.
void GameScreen::updateGameLogic()
{
    UINT i;
    Sprite *spr;

    // Don't update anything if we're on the loading screen.
    if (mApp->getState() == SP_STATE_LOADING) return;

    // Always move forward.

    mZ += FORWARD_SPEED * mLevel->getPlaneSpeed() / 128;

    // Count down time lefts for flashing and wobble.
    if (mFlashing > 0) mFlashing--;
    if (mCrash > 0) mCrash--;
    if (mShowMessage > 0) mShowMessage--;


    // Update speed in the vertical plane.
    if ((mKeys & SP_LEFT) && mSpeedX > -MAX_STRAFE_SPEED) mSpeedX -= STRAFE_ACCEL;
    if ((mKeys & SP_RIGHT) && mSpeedX < MAX_STRAFE_SPEED) mSpeedX += STRAFE_ACCEL;
    if ((mKeys & SP_DOWN) && mSpeedY > -MAX_STRAFE_SPEED) mSpeedY -= STRAFE_ACCEL;
    if ((mKeys & SP_UP) && mSpeedY < MAX_STRAFE_SPEED) mSpeedY += STRAFE_ACCEL;

    mSpeedX += STRAFE_ACCEL * mJoystickX / 32768;
    mSpeedY += STRAFE_ACCEL * mJoystickY / 32768;


    // Add constant wind effects.
    mSpeedX += mLevel->getWindMagnitude() * XFcMath::cosFast(mLevel->getWindDirection());
    mSpeedY += mLevel->getWindMagnitude() * XFcMath::sinFast(mLevel->getWindDirection());

    // Add sudden windgusts.
    if (mGustInProgress > 0) 
    {
        // mGustInProgress starts out at 50. make force 0-25 with max in middle of gust.
        REAL force = 25 - mGustInProgress;
        if (force < 0) force = -force;
        force = 25 - force;

        mSpeedX += force * mLevel->getWindGustFactor() * XFcMath::cosFast(mGustAngle) * REALf(0.004f);
        mSpeedY += force * mLevel->getWindGustFactor() * XFcMath::sinFast(mGustAngle) * REALf(0.004f);
        mGustInProgress--;
    }


    // Update plane position.
    mX += mSpeedX;
    mY += mSpeedY;

    // Make sure it's within bounds.
    if (mX > SP_LEVEL_MAX_XY) mX = SP_LEVEL_MAX_XY;
    if (mX < -SP_LEVEL_MAX_XY) mX = -SP_LEVEL_MAX_XY;
    
    if (mY > SP_LEVEL_MAX_XY) mY = SP_LEVEL_MAX_XY;
    if (mY < -SP_LEVEL_MAX_XY) mY = -SP_LEVEL_MAX_XY;


    // Crude simulation of air resistance.
    mSpeedX *= REALf(0.99f);
    mSpeedY *= REALf(0.99f);        


    // Update plane rotation.
    if (mWantedAngleZ > mCurrentAngleZ) mCurrentAngleZ += PI * ROTATION_SPEED;
    if (mWantedAngleZ < mCurrentAngleZ) mCurrentAngleZ -= PI * ROTATION_SPEED;
    
    if (mWantedAngleX > mCurrentAngleX) mCurrentAngleX += PI * ROTATION_SPEED;
    if (mWantedAngleX < mCurrentAngleX) mCurrentAngleX -= PI * ROTATION_SPEED;

    if (mWantedTiltZ > mCurrentTiltZ) mCurrentTiltZ += PI * ROTATION_SPEED;
    if (mWantedTiltZ < mCurrentTiltZ) mCurrentTiltZ -= PI * ROTATION_SPEED;


    // Do nothing else if we are not playing.
    if (mApp->getState() != SP_STATE_PLAYING) return;


    // Check collisions with hoops and bonus items.
    for (i = 0; i < mLevel->nrSprites(); i++)
    {        
        spr = mLevel->getSprite(i);

        // Skip the sprite handling if it had been disabled (hit before).
        if (!spr->isEnabled()) continue;

        REAL dZ = mZ - spr->getZ();

        // Early out: to far away?
        if (XFcMath::abs(dZ) > REALi(8)) continue;

        // Ok, we're close. Make some more accurate collision calculations.
        REAL dX = mX - spr->getX();    
        REAL dY = mY - spr->getY();    

        // Divide by 4 to avoid overflow (fixed point).
        dX = dX / 4;
        dY = dY / 4;
        REAL dist = XFcMath::sqrtFast(dX * dX + dY * dY);
        dist = dist * 4;


        if (spr->getType() == SP_SPRITE_BONUS) 
        {
            if (dist < REALi(8)) 
            {        
                mBonusInARow++;
                mScore += ((Bonus *)spr)->getValue() * mBonusInARow;

                // We dont need this one anymore. Remove from sprite list.
                mLevel->removeSprite(spr);

                playSound(mBonusSound);            
            }
            else
            {
                // We missed a bonus item. Reset mBonusInARow counter.
                mBonusInARow = 0;
            }

        }

        if (spr->getType() == SP_SPRITE_HOOP) 
        {
            Hoop *hoop = (Hoop *)spr;

            // Calculate roll in the interval -PI,PI.
            REAL roll = mCurrentAngleZ;
            while (roll >= 2 * PI) roll -= 2 * PI;
            while (roll < 0) roll += 2 * PI;
            if (roll > PI) roll -= PI;

            // Do the collision test only after the plane has actually passed the hoop
            // so that the player has a better chance to orient his plane correctly.
            if (dZ > 0) 
            {
                // Check allowed plane rotation for different hoops.
                REAL delta;
                switch (hoop->getOrientation()) 
                {   
                    case SP_HOOP_ANY: 
                        delta = 0; 
                        break;
                    case SP_HOOP_MINUS:
                        delta = MIN(roll, XFcMath::abs(PI - roll)); 
                        break;
                    case SP_HOOP_SLASH:
                        delta = XFcMath::abs(PI / 4 - roll); 
                        break;
                    case SP_HOOP_BAR:
                        delta = XFcMath::abs(PI / 2 - roll); 
                        break;
                    case SP_HOOP_BACKSLASH:
                        delta = XFcMath::abs(3 * PI / 4 - roll); 
                        break;
                    case SP_HOOP_PLUS:
                        delta = MIN(roll, XFcMath::abs(PI - roll));
                            
                        if (XFcMath::abs(PI / 2 - roll) < delta) 
                        {            
                            delta = XFcMath::abs(PI / 2 - roll); 
                        }
                        break;
                    case SP_HOOP_CROSS:
                        delta = MIN(XFcMath::abs(3 * PI / 4 - roll), 
                                    XFcMath::abs(PI / 4 - roll));
                        break;
                    default:
                        // Unknown hoop type... something is wrong.
                        XFCASSERT(0);
                }

                if (dist > ((hoop->getHoleDiameter() - PLANE_WIDTH) / 2) || delta > ANGLE_TOLERANCE) 
                {
                    // We just ran into a hoop, or missed it completely.
                    mMisses++;
                    mFlashing = MS_TO_TICKS(1500);

                    if (dist < ((HOOP_DIAMETER + PLANE_WIDTH) / 3))
                       {
                        // We hit the hoop. Start wobbling for 1.5s.
                        mCrash = MS_TO_TICKS(1500);
                        playSound(mCrashSound);

                        // Vibrate for a second, if supported. 
                        XFcVibrate::playNote(100, 100);
                    }

                }
                mRollAtLastHoop = mCurrentAngleZ;
                hoop->disable();
            }
        }
    }

    // Check if player has rotated more than 360 degrees since last hoop.
    REAL roll = mCurrentAngleZ - mRollAtLastHoop;
    if (roll < 0) roll = -roll;

    if (roll >= (2 * PI - PI / 32))
    {
        mRollAtLastHoop = mCurrentAngleZ;
        mScore += 100;
        mShowMessage = MS_TO_TICKS(500);
        mMessage = XFCSTR("ROLL BONUS!");
    }

    // Randomly initiate wind gusts.
    if (mLevel->getWindGustFactor() != 0) 
    {
        if (mRand->next() % 2000 < (3 + (UINT32)(mLevel->getWindGustFactor() * 32))) 
        {
            mGustInProgress = 25;
            mGustAngle = mRand->next();
        }
    }
}


//! Render the in game graphics and any overlays depending on current game state.
void GameScreen::render()
{
    UINT i;
    Sprite *spr;

    XFcGLSurface *fb;
    fb = mGL->getSecondary();

    mFrames++;

    // Calculate wind parameters as function of distance travelled.
    mLevel->updateWindParameters(mZ);

    // Update game logic.
    while (mLogicTick < XFcCore::getTick())
    {
        updateGameLogic();
        
        mLogicTick += 1000 / LOGIC_FPS;
    }
    
    mGL->beginRender(); 

    // Draw backdrop. skip status bar if game state = LOADING.
    mLevel->drawBackdrop(mGL, mX, mY, mApp->getState() == SP_STATE_LOADING ? 1 : 0);


    // Draw the hoop and bonus sprites.

    // Translate everyting towards the camera as we move forward.
    XFcMatrix4 worldMatrix;
    XFcMath::matrixIdentity(worldMatrix);
    XFcMath::matrixTranslate(worldMatrix, XFcVector3(0, 0, -mZ));
    mGL->setMatrix(XFCGLMAT_WORLD, worldMatrix);

    // Counterclockwise culling.
    mGL->setStateI(XFCGLRS_CULLING, XFCGLCULL_CCW);

    // No shading.
    mGL->setStateI(XFCGLRS_SHADING, XFCGLSHADE_MATTE); 

    for (i = 0; i < mLevel->nrSprites(); i++)
    {        
        spr = mLevel->getSprite(i);

        // Continue with next if sprite is behind the camera or too far away.
        REAL z = spr->getZ() - mZ;
        if (z < CAMERA_Z || z > 400) continue;

        mGL->setTexture(spr->getTexture());

        REAL size;
        if (spr->getType() == SP_SPRITE_HOOP) 
        {
            size = HOOP_DIAMETER;
        }
        else
        {
            size = BONUS_DIAMETER;
        }

        mGL->drawSprite3dBillboard(spr->getX() - mX, spr->getY() - mY, spr->getZ(), 
                                   size, size,        
                                   REALi(0), REALi(0),  
                                   REALi(1), REALi(1),  
                                   NULL, 0xffffffff);             
    }

    // Render cloud sprites. 
    mLevel->renderClouds(mGL, mX, mY, mZ);

    // Draw the plane.
    if (!(mFlashing > 0 && ((mFrames & 1) == 0))) 
    {

        // Create plane orientation matrix.

        XFcMatrix4 mat;
        
        // Make a constant Z rotation matrix (roll)
        XFcMath::matrixRotationZ(mat, mCurrentAngleZ);
        
        // This -PI / 2 constant rotation is done because the plane model
        // in the XFF file is rotated 90 degrees too much around the X axis.
        XFcMath::matrixRotateX(mat, -PI / 2);    

        // Add wobble effect
        REAL xWobble = REALf(0.051f);
        REAL yWobble = REALf(0.051f);

        if (mCrash) 
        {
            // Boost wobbling if we just crashed into a hoop.
            xWobble *= (1 + (mCrash * 16 / LOGIC_FPS));
            yWobble *= (1 + (mCrash * 16 / LOGIC_FPS));
        }
        
        // Apply final tilt and wobble rotation matrix. A bit messy, yes.
        XFcMatrix4 rotMatrix;        
        XFcQuaternion q;
        
        XFcMath::quaternionRotationXYZ(q, mCurrentAngleX + xWobble * XFcMath::sin(WOBBLE_SPEED * XFcCore::getTick()), 
                                       mCurrentAngleY - mCurrentTiltZ / 3 + 
                                       yWobble * XFcMath::cos(2 * WOBBLE_SPEED * XFcCore::getTick()),
                                       mCurrentTiltZ +
                                       0.08f * XFcMath::cos(1.0 * WOBBLE_SPEED * XFcCore::getTick()));                            
        
        XFcMath::matrixFromQuaternion(rotMatrix, q);

        mat *= rotMatrix;

        // Set world transformation used to render the plane mesh.
        mGL->setMatrix(XFCGLMAT_WORLD, mat);     
        
        // And finally, render the plane mesh if not in the LOADING state.
        if (mApp->getState() != SP_STATE_LOADING) 
        {
            mPlane->render();
        }
    }         


#if 0
    // Update wind indicator.
    if (mApp->getState() == SP_STATE_PLAYING) renderWindIndicator();
#endif

    // Render the graphics...
    mGL->endRender();

    // Draw status display on top of all.
    if (mApp->getState() == SP_STATE_PLAYING) updateStatusDisplay(fb);


    // Draw overlay text if GAMEOVER or LEVELCOMPLETE.

    CHAR tmpStr[32];
    switch (mApp->getState()) 
    {
        case SP_STATE_LEVELCOMPLETE:
            centerString(mCenterY - 25, XFCSTR("LEVEL"));
            centerString(mCenterY + 25, XFCSTR("COMPLETE"));
            break;

        case SP_STATE_GAMEOVER:
            centerString(mCenterY, XFCSTR("GAME OVER"));
            break;        

        case SP_STATE_PLAYING:


            if (mShowMessage)
            {
                centerString(mCenterY, XFCSTR("ROLL BONUS!"));
            }
            
            // Check if wee need to update game states.

            // Level finished?
            if (mZ > mLevel->length()) 
            {
                // Level the plane.
                mWantedAngleZ = REAL(mRoll & ~3) * PI / 4;        

                switch (mMisses) 
                {
                    case 0: 
                        mScore += 1000; 
                        break;
                    case 1: 
                        mScore += 500; 
                        break;
                    case 2: 
                        mScore += 100; 
                        break;
                    default:
                        break;
                }
                mApp->setScore(mScore);
                mApp->setState(SP_STATE_LEVELCOMPLETE);
            }
        
            // Too many misses?
            if (mMisses > SP_MAX_MISSES)
            {
                // Level the plane.
                mWantedAngleZ = REAL(mRoll & ~3) * PI / 4;
                mApp->setScore(mScore);
                mApp->setState(SP_STATE_GAMEOVER);
            }
            break;

        case SP_STATE_LOADING:
        {
            // Brighten up the background.
            fb->drawFilledRect(0, 0, XFcCore::getDeviceWidth(), XFcCore::getDeviceHeight(), 
                               0x90000000 | 0xffffff);        

            // Save current letterspacing.
            INT32 oldLetterSpacing = mPrinter->getLetterSpacing();

            // Draw loading screen text.
            XFcStringToolkit::format(tmpStr, 32, "LEVEL %d", mApp->currentLevel());
            centerString(mHeight / 4, tmpStr);
            
            // Decrease letterspacing to squeeze the charachters closer together.
            mPrinter->setLetterSpacing(0);
            centerString(7 * mHeight / 16, mLevel->getText());
            mPrinter->setLetterSpacing(oldLetterSpacing);

            centerString(3 * mHeight / 4, XFCSTR("GET READY!"));
            break;
        }
        default:
            break;
    }

#ifdef SP_DEBUG
    mFPS->tick();
#endif
}


//! Draws the status display on top of the game screen and the progress meter on the right side.
void GameScreen::updateStatusDisplay(XFcGLSurface *fb)
{
    // Draw status bar background. Simple gradient.
    fb->drawFilledRect(0, 0, XFcCore::getDeviceWidth(), 2, 0xffb0b0c0);
    INT i;
    for (i = 0; i < 20; i++)
    {
        UINT32 shade = REALi(0x20) + REALi(0xb0) * XFcMath::sinFast(PI*i/24);
        fb->drawFilledRect(0, 2 + i, XFcCore::getDeviceWidth(), 1, 
                           0xff001020 | (shade << 16) | (shade << 8) | (shade));    
    }
    fb->drawFilledRect(0, 22, XFcCore::getDeviceWidth(), 2, 0xff606060);

    CHAR tmpStr[32];
#ifdef SP_DEBUG
    // Draw FPS counter instead of score if SP_DEBUG defined.
    XFcStringToolkit::format(tmpStr, 32, "%3.3f", (float)(mFPS->getFPS()));
    XFcStringToolkit::format(tmpStr, 32, "%3.3f", (float)(mJoystickY));
#else
    XFcStringToolkit::format(tmpStr, 32, "SCORE: %d", (int)(mScore));
#endif
    // Save current letterspacing.
    INT32 letterSpacing = mPrinter->getLetterSpacing();

    // Decrease letterspacing to squeeze the charachters closer together.
    mPrinter->setLetterSpacing(-1);

    // Print score.
    mPrinter->print(fb, 3, 5, tmpStr, XFCBLEND_MUL, 0xff);

    // Draw misses as "filled knobs".
    CHAR *knob = "b";
    for (i = 0; i < 4; i++) {
        if (i >= mMisses) knob = "a";
        mPrinter->print(fb, XFcCore::getDeviceWidth() - 16 - 12 * i, 4, knob, XFCBLEND_MUL, 0xff);
    }

    mPrinter->setLetterSpacing(letterSpacing);

    // Draw progress meter.
    fb->drawFilledRect(mWidth - 6, 30, 4, mHeight - 36, 0x7f000000);    
    INT progress = (mHeight - REALi(36)) * (mZ / mLevel->length());
    fb->drawFilledRect(mWidth - 6, mHeight - 6 - progress, 4, 4, 0xfffffff0);    
}


#if 0
//! Renders the wind direction indicator at the bottom of the game screen.
void GameScreen::renderWindIndicator()
{
    if (mWindStrength == 0) return;

    // Pointer to vertex buffer.
    XFcGLTLVertex *v;

    // Lock vertex buffer, if fails, quit.
    v = (XFcGLTLVertex *)mVB->lock(0);
    XFCASSERT(v && "Vertex buffer locking failed.");
    
    REAL bottomY = XFcCore::getDeviceHeight() - 16;

    // Hardcoded windmeter vertices. 

    v[0].mX = mCenterX + 12 * XFcMath::cosFast(mWindDirection);           
    v[0].mY = bottomY - 12 * XFcMath::sinFast(mWindDirection);
    v[0].mRHW = 1;
    v[0].mDiffuseColor = 0xff800000;
    
    v[1].mX = mCenterX + 12 * XFcMath::cosFast(mWindDirection + 7 * PI / 8);           
    v[1].mY = bottomY - 12 * XFcMath::sinFast(mWindDirection + 7 * PI / 8);
    v[1].mRHW = 1;
    v[1].mDiffuseColor = 0xff800000;
    
    v[2].mX = mCenterX + 12 * XFcMath::cosFast(mWindDirection + 9 * PI / 8);           
    v[2].mY = bottomY - 12 * XFcMath::sinFast(mWindDirection + 9 * PI / 8);
    v[2].mRHW = 1;
    v[2].mDiffuseColor = 0xff800000;


    // Rotate according to wind direction.

    XFcMatrix4 windMatrix;
    XFcMath::matrixRotateZ(windMatrix, mWindDirection);
    mGL->setMatrix(XFCGLMAT_WORLD, windMatrix);

    mGL->setStateI(XFCGLRS_SHADING, XFCGLSHADE_MATTE); 
    mGL->setStateI(XFCGLRS_CULLING, XFCGLCULL_NONE);
    
    mGL->setTexture(NULL);    
    mGL->renderPrimitive(mVB, XFCGLPT_TRIANGLELIST, 0, 3, 0, 2, NULL);
    
    // Unlock vertex buffer.
    mVB->unlock();  
}
#endif


//! Save current game state to a file.
INT GameScreen::saveGameState(const CHAR *aFileName)
{
    XFcFile *file = XFcFile::open(aFileName, XFCSTR("wb"));

    if (file == NULL) return -1;

    file->writeINT32(mApp->currentLevel());
    file->writeINT32(mScore);
    file->writeINT32(mMisses);
    file->writeINT32(mRoll);
    file->writeINT32(mFlashing);
    file->writeINT32(mCrash);

    file->writeFLOAT32(mX);
    file->writeFLOAT32(mY);
    file->writeFLOAT32(mZ);

    file->writeINT32(0xff00ff00);

    file->close();
    return 1;
}


//! Load game state from a file.
INT GameScreen::loadGameState(const CHAR *aFileName)
{
    XFcFile *file = XFcFile::open(aFileName, XFCSTR("rb"));

    if (file == NULL) return -1;

    INT level  = file->readINT32();

    mScore     = file->readINT32();
    mMisses    = file->readINT32();
    mRoll      = file->readINT32();
    mFlashing  = file->readINT32();
    mCrash     = file->readINT32();

    mX = file->readFLOAT32();
    mY = file->readFLOAT32();
    mZ = file->readFLOAT32();

    INT32 end = file->readINT32();

    mWantedAngleZ = mCurrentAngleZ = REAL(mRoll) * PI / 4;

    file->close();
    return level;
}

