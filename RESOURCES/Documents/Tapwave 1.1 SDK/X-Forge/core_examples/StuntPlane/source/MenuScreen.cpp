/*! \file
 * MenuScreen.cpp <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: MenuScreen.cpp,v 1.14 2003/08/07 08:10:11 lars Exp $
 * $Date: 2003/08/07 08:10:11 $
 * $Revision: 1.14 $
 */

#include <xforge.h>
#include <xfutil/XFuPrinter.h>

#include "Screen.h"
#include "MenuScreen.h"
#include "StuntPlane.h"


// Flare effect defs.
#define NR_TRIANGLES     16
#define TRIANGLE_WIDTH   20


// Credit screen text.
#define NR_STRINGS 35

const CHAR * const endScreenText[NR_STRINGS] = 
{
    "STUNTPLANE", 
//    "CORE EXAMPLE", 
    NULL, 
    NULL,
    "PRODUCER:",
    "   ANSU KUNNAS",
    NULL,
    "DESIGN:",
    "   JANI KAHRAMA",
    NULL,
    "EXEC PRODUCER",
    "   ARTO ASTALA",
    NULL,
    "PROGRAMMING:", 
    "   LARS ANDERSSON", 
    NULL,
    "ARTWORK:",
    "   JANI KAHRAMA",
    NULL,
    "MUSIC COMPOSER:",
    "   KAI-EERIK KOMPPA",
    NULL,
    "SOUND EFFECTS:",
    "   VILLE VATEN",
    NULL,
    "LEVEL DESIGN:",
    "   SARA KAPLI",
    NULL,
    "SUPPORT:",
    "   JARI KOMPPA",
    NULL,
    NULL,
    "COPYRIGHT",
    "FATHAMMER OY",
    "2003"
};


//! Static constructor.
MenuScreen * MenuScreen::create(XFcGL *aGL, XFuPrinter *aPrinter)
{
    MenuScreen *m = new MenuScreen(aGL);
    XFCASSERT(m);

    m->mVB = XFcGLVertexBuffer::create(XFCGL_LVERTEX, sizeof(XFcGLLVertex), 3 * NR_TRIANGLES);
    XFCASSERT(m->mVB);

    m->mPrinter = aPrinter;
    return m;
}


MenuScreen::MenuScreen(XFcGL *aGL) : Screen(aGL)
{
    mAngle = 0;
    mMenuKnobPos = 0;
    mOptionKnobPos = 0;
    mSavedGameFound = 0;
    mLockPointer = 0;

    mVB = NULL;
    mBackSurf = NULL;
    mLogo = NULL;

    mScrollerY = XFcCore::getDeviceHeight();
}


MenuScreen::~MenuScreen()
{
    delete mVB;
    mVB = NULL;
}


//! Called when this screen is set as current renderer.
void MenuScreen::initRenderer()
{

#ifdef SP_TAPWAVE_VERSION
    // Load menu screen background surface.
    mBackSurf = XFcImageLoader::load(XFCSTR("menuscreen.pcx"));
    XFCASSERT(mBackSurf);

#else
    XFcGLSurface *tmpSurf;
    
    // Load menu screen background surface.
    tmpSurf = XFcImageLoader::load(XFCSTR("menuscreen.pcx"));
    XFCASSERT(tmpSurf);

    // Rescale it to current display resolution.
    mBackSurf = XFcGLSurfaceToolkit::resampleSurface(tmpSurf, mWidth / 176, mHeight / 220);
    delete tmpSurf;

    // Load menu screen logo surface.
    mLogo = XFcImageLoader::load(XFCSTR("stunt_logo.pcx"));
    XFCASSERT(mLogo);

    // Rescale it.
//    mLogo = XFcGLSurfaceToolkit::resampleSurface(tmpSurf, mWidth / 176, mHeight / 220);
//    delete tmpSurf;

    // Enable colorkeying for logo surface.
    mLogo->enableColorKey(1);
    mLogo->setColorKey(0xff00ff00);
#endif

    // Define viewport: use all of the screen.
    XFcGLViewport vp;
    vp.mXScreenOffset = 0;
    vp.mYScreenOffset = 0;
    vp.mAreaWidth = XFcCore::getDeviceWidth();
    vp.mAreaHeight = XFcCore::getDeviceHeight();
    vp.mMinZ = REALf(0.0f);
    vp.mMaxZ = REALf(1.0f);
    mGL->setViewport(vp);

    // Camera matrix: place it at (170,140,-16) looking straight along the Z-axis.
    XFcMatrix4 cameraMatrix;
    XFcMath::matrixLookAt(cameraMatrix, 
                          XFcVector3(170, 140, -60), 
                          XFcVector3(170, 140, 0), 
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

    // Set world transformation matrix.
    XFcMatrix4 worldMatrix;
    XFcMath::matrixIdentity(worldMatrix);
    mGL->setMatrix(XFCGLMAT_WORLD, worldMatrix);

    // check if a saved game exists.
    if (XFcFile::fileExists(XFCSTR("saved.bin"))) 
    {
        mSavedGameFound = 1;
    }
    else 
    {
        mSavedGameFound = 0;
    }

    createScreenButtons(SP_MENUSCREEN);

    mLastTick = XFcCore::getTick();
}


//! Called when another screen is set as current renderer.
void MenuScreen::deinitRenderer()
{
    delete mBackSurf;
    mBackSurf = NULL;
    delete mLogo;
    mLogo = NULL;
}


//! This gets called on control key down if in main menu mode.
void MenuScreen::mainMenuKeyDown(INT32 aCode)
{
    switch (aCode) 
    {
        // Move knob up.
        case XFCCL_WHEELUP:
        case XFCCL_UP:
            mMenuKnobPos--;
            if (mMenuKnobPos < 0) mMenuKnobPos = 4;
            break;
            
        // Move knob down.
        case XFCCL_WHEELDOWN:
        case XFCCL_DOWN:
            mMenuKnobPos++;
            if (mMenuKnobPos > 4) mMenuKnobPos = 0;
            break;  
                    
        // Menu item selected?
        case XFCCL_FIRE1:
        case XFCCL_FIRE7:
            // Yes, make something happen.
            handleMainMenuSelection(mMenuKnobPos + SP_FIRST_BUTTON);
            break;

        default:
            break;
    }        
}


//! Handle main menu item selection.
void MenuScreen::handleMainMenuSelection(INT32 aCode) 
{
    switch (aCode) 
    {   
        // Start new game?
        case SP_FIRST_BUTTON: 
            mApp->setLevel(0);
            mApp->setState(SP_STATE_NEXTLEVEL); 
            break; 

        // Continue saved game?
        case SP_SECOND_BUTTON: 
            mApp->setState(SP_STATE_CONTINUE); 
            break; 

        // Go to options Screen?
        case SP_THIRD_BUTTON: 
            createScreenButtons(SP_OPTIONSCREEN);
            mApp->setState(SP_STATE_OPTIONS); 
            break;

        // Show Highscore?
        case SP_FOURTH_BUTTON: 
            mApp->setState(SP_STATE_SHOWSCORE); 
            break;

        // Quit?    
        case SP_FIFTH_BUTTON: 
            mPrinter->setLetterSpacing(-1);
            mApp->setState(SP_STATE_CREDITS); 
            break; 
                        
        default:
            break;
    }
}


//! This gets called on control key down if in options menu mode.
void MenuScreen::optionMenuKeyDown(INT32 aCode)
{
    switch (aCode) 
    {   
        case XFCCL_WHEELUP:
        case XFCCL_UP:
            mOptionKnobPos--;
            if (mOptionKnobPos < 0) mOptionKnobPos = 3;
            break;
        case XFCCL_WHEELDOWN:
        case XFCCL_DOWN:
            mOptionKnobPos++;
            if (mOptionKnobPos > 3) mOptionKnobPos = 0;
            break;            
        case XFCCL_FIRE1:
        case XFCCL_FIRE7:            
            handleOptionMenuSelection(mOptionKnobPos + SP_FIRST_BUTTON);
            break;

        default:        
            break;
    }
}


//! Handle option menu item selection.
void MenuScreen::handleOptionMenuSelection(INT32 aCode) 
{
    switch (aCode) 
    {   
        // Toggle menu music on/off?
        case SP_FIRST_BUTTON:    
            mApp->toggleMusic();
            break; 

        // Toggle ingame sound effects on/off?
        case SP_SECOND_BUTTON:                
            mApp->toggleSound();                    
            break; 

        // Toggle pilot mode?
        case SP_THIRD_BUTTON:    
            mApp->togglePilotMode();
            break;

        // Return to main menu?
        case SP_FOURTH_BUTTON:    
            createScreenButtons(SP_MENUSCREEN);
            mApp->setState(SP_STATE_MENU); 
            break; 
           
        default:
            break;
    }
}


//! Called when a control key is pressed.
void MenuScreen::onControlDown(INT32 aCode)
{
    switch (mApp->getState())
    {

        // Check if we are in the main menu.
        case SP_STATE_MENU:
            mainMenuKeyDown(aCode);        
            break;
        // Check if we are in the options menu.
        case SP_STATE_OPTIONS:
            optionMenuKeyDown(aCode);        
            break;
        case SP_STATE_SHOWSCORE:
            mApp->setState(SP_STATE_MENU);
            break;
        case SP_STATE_CREDITS:
            mApp->setState(SP_STATE_QUIT);
            break;
        default:
            break;
    }
}


//! Called when a control key is pressed.
void MenuScreen::onKeyUp(INT32 aCode)
{
    // Only handle virtual screen buttons here.
    if (aCode < SP_FIRST_BUTTON) return;

    if (mLockPointer) 
    {
        mLockPointer = 0;
        return;
    }

    switch (mApp->getState())
    {
        case SP_STATE_MENU:
            handleMainMenuSelection(aCode);
            break;
        case SP_STATE_OPTIONS:
            handleOptionMenuSelection(aCode);
            break;
        case SP_STATE_SHOWSCORE:
            mApp->setState(SP_STATE_MENU);
            break;
        case SP_STATE_CREDITS:
            mApp->setState(SP_STATE_QUIT);
            break;
        default:
            break;
    }
}


//! Called when pointer is released.
void MenuScreen::onPointerUp(INT32 /*aX*/, INT32 /*aY*/)
{
}

//! Called when pointer is tapped.
void MenuScreen::onPointerDown(INT32 /*aX*/, INT32 /*aY*/)
{
    if (mApp->getState() == SP_STATE_SHOWSCORE) 
    {
        mApp->setState(SP_STATE_MENU);
        mLockPointer = 1;
    }
    if (mApp->getState() == SP_STATE_CREDITS) 
    {
        mApp->setState(SP_STATE_QUIT);
        mLockPointer = 1;
    }

}


//! Create onscreen virtual buttons for main/option menus.
void MenuScreen::createScreenButtons(INT aScreen)
{
    XFcRectangle rect;

    INT ySize = mHeight - mHeight / 4;
    INT y = mHeight / 4;

    INT items;
    if (aScreen == SP_MENUSCREEN) items = 6;
    else items = 5;
    
    INT yRowSpace = ySize / items;
    y += yRowSpace / 2;

#ifdef SP_TAPWAVE_VERSION
    // Menuscreen layout is a bit different in Tapwave version.
    if (aScreen == SP_MENUSCREEN) y = 32;
    yRowSpace /= 2;
#endif

    XFcCore::resetScreenButtons();

    INT i;
    INT scanCode = SP_FIRST_BUTTON;
    for (i = 0; i < items; i++) 
    { 
        // Create button.
        rect.mX = 0;
        rect.mY = y + i * yRowSpace;
        rect.mWidth = mWidth;
        rect.mHeight = 20;
        XFcCore::addScreenButton(rect, scanCode + i);
    }
}


//! Printer centered text string at given y coordinate.
void MenuScreen::drawString(INT aX, INT aY, const CHAR *aString, INT aInv)
{
    mPrinter->print(mGL->getSecondary(), aX, aY, aString, 
                    aInv ? XFCBLEND_INVMUL : XFCBLEND_MUL, 0xff);
}


//! The menuscreen renderer.
void MenuScreen::render()
{
    XFcGLSurface *fb;        

    // ask GL for the secondary buffer.
    fb = mGL->getSecondary();

    // draw background image
    fb->drawImage(mBackSurf, 0, 0, XFcCore::getDeviceWidth(),
                  XFcCore::getDeviceHeight());


    mGL->beginRender();

    // Render a set of rotating sunrays.

    mAngle += XFcCore::getTick() * REALf(0.00001f);
    XFcGLLVertex *v = (XFcGLLVertex *)mVB->lock(0);
    
    REAL angle = XFcCore::getTick() * REALf(0.00015f);

    INT i;
    for (i = 0; i < NR_TRIANGLES; i++)
    {
        // Center vertex.
        v[0].mX = REALi(FLARE_CENTER_X);           
        v[0].mY = REALi(FLARE_CENTER_Y);
        v[0].mZ = 100;
        v[0].mDiffuseColor = 0x40ffffff;

        // Perimeter vertices.
        v[1].mX = FLARE_CENTER_X + FLARE_RADIUS * XFcMath::cos(angle);           
        v[1].mY = FLARE_CENTER_Y + FLARE_RADIUS * XFcMath::sin(angle);           
        v[1].mZ = 100;

        v[2].mX = REALi(FLARE_CENTER_X) + FLARE_RADIUS * XFcMath::cos(angle + PI / 20);           
        v[2].mY = REALi(FLARE_CENTER_Y) + FLARE_RADIUS * XFcMath::sin(angle + PI / 20);           
        v[2].mZ = REALi(100);

        REAL sinus = XFcMath::sin(angle);

        if (sinus > REALf(0.1f)) 
        {
            // Above horizeon, alpha = 0x60
            v[1].mDiffuseColor = 0x30777797;        
        }
        else if (sinus < -REALf(0.3f)) 
        {
            // Below horizon, alpha = 0
            v[0].mDiffuseColor = 0x0;        
            v[1].mDiffuseColor = 0x0;        
        } 
        else 
        {
            // Just on the horizon, make smooth transfer of alpha.
            UINT32 alpha = (sinus + REALf(0.3f)) * (REALi(0x60) / REALf(0.4f));

            v[0].mDiffuseColor = 0x00ffffff | (alpha << 23);        
            v[1].mDiffuseColor = 0x00777797 | (alpha << 24);        
        }        

        v[2].mDiffuseColor = v[1].mDiffuseColor;

        // Next triangle.
        v += 3;
        angle += 2 * PI / NR_TRIANGLES;
        while (angle > 2 * PI) angle -= 2 * PI;
    }
    
    // Use additive alpha blending.
    mGL->setStateI(XFCGLRS_ALPHABLEND, 1);   
    mGL->setStateI(XFCGLRS_SRCBLEND, XFCBLEND_ONE);
    mGL->setStateI(XFCGLRS_TGTBLEND, XFCBLEND_ONE);

    // Enable Gouraud shading.
    mGL->setStateI(XFCGLRS_SHADING, XFCGLSHADE_GOURAUD); 
    mGL->setStateI(XFCGLRS_CULLING, XFCGLCULL_NONE);
    
    // No texturing.
    mGL->setTexture(NULL);
    
    // Draw the triangles.
    mGL->renderPrimitive(mVB, XFCGLPT_TRIANGLELIST, 0, NR_TRIANGLES * 3, 0, NR_TRIANGLES * 3 - 1, NULL);
    
    mGL->setStateI(XFCGLRS_ALPHABLEND, 0);   

    // Unlock vertex buffer.
    mVB->unlock();  
    
    mGL->endRender();


    CHAR tmpStr[32];        
    REAL y = mScrollerY;
    REAL centerX;

    // Render different things on top depending on which state we are in.
    switch (mApp->getState()) 
    {
        case SP_STATE_MENU: 
        {
            // Just rescale the logo to appropriate dimensions. For a real
            // game we should either use different versions of the graphics for
            // different resolutions, or use the XFcGLSurfaceToolkit to make
            // a more accurate rescaling.

            // Reserve 1/4 of the screen height for the logo.
            INT ySize = mHeight - mHeight / 4;
            INT y = mHeight / 4;
            INT yRowSpace = ySize / 6;

            y += yRowSpace / 2;

#ifndef SP_TAPWAVE_VERSION
            fb->drawImage(mLogo,(mWidth - mLogo->getWidth()) / 2, mHeight / 16);
            centerX = mCenterX;
#else
            // Use a slightly different menu layout for tapwaves.
            y = 32;
            yRowSpace /= 2;
            centerX = 390;
#endif

            drawString(centerX - 60, y, XFCSTR("NEW GAME"), 0);

            if (mSavedGameFound)
            {
                drawString(centerX - 65, y + yRowSpace, XFCSTR("CONTINUE"), 0);
            }
            else        
            {
                drawString(centerX - 65, y + yRowSpace, XFCSTR("CONTINUE"), 1);
            }

            drawString(centerX - 65, y + 2 * yRowSpace, XFCSTR("OPTIONS"), 0);

            drawString(centerX - 65, y + 3 * yRowSpace, XFCSTR("HISCORE"), 0);

            drawString(centerX - 65, y + 4 * yRowSpace, XFCSTR("QUIT"), 0);

            // Print the knob. 'a' is a special "knob" character in the font bitmap.
            drawString(centerX - 83, y + mMenuKnobPos * yRowSpace, XFCSTR("a"), 0);

#ifdef SP_SMARTPHONE_VERSION
            drawString(mWidth - 70, mHeight - 20, XFCSTR("(DEMO)"), 0);
#endif
            break;
        }
        case SP_STATE_OPTIONS:
        {
            // reserve 1/4 of the screen height for the logo.
            INT ySize = mHeight - mHeight / 4;
            INT y = mHeight / 4;
            INT yRowSpace = ySize / 5;

            y += yRowSpace / 2;

#ifdef SP_TAPWAVE_VERSION
            yRowSpace /= 2;
            centerX = 390;
#endif

            drawString(mCenterX - 44, XFcCore::getDeviceHeight() / 8, XFCSTR("OPTIONS"), 0);

            drawString(20, y, XFCSTR("MUSIC:"), 1);
            drawString(mWidth - 42, y, mApp->playMusic() ? XFCSTR("ON") : XFCSTR("OFF"), 1);
            
            drawString(20, y + yRowSpace, XFCSTR("SOUND FX:"), 0);
            drawString(mWidth - 42, y + yRowSpace, mApp->playSounds() ? XFCSTR("ON") : XFCSTR("OFF"), 0);
            
            drawString(20, y + 2 * yRowSpace, XFCSTR("PILOT:"), 1);
            drawString(mWidth - 42, y + 2 * yRowSpace, mApp->pilotControls() ? XFCSTR("ON") : XFCSTR("OFF"), 1);
            
            drawString(20, y + 3 * yRowSpace, XFCSTR("BACK"), 0);

            // 'a' is a special "knob" character in the font bitmap.
            drawString( 2, y + mOptionKnobPos * yRowSpace, XFCSTR("a"), 0);
            break;
        }            

        case SP_STATE_SHOWSCORE:
        {
            // Show current highscore.
            drawString(mCenterX - 56, mCenterY - 20, XFCSTR("HIGHSCORE"), 0);

            XFcStringToolkit::format(tmpStr, 32, "%d", mApp->getHighscore());
            INT32 textWidth, textHeight;
            mPrinter->stringMetrics(tmpStr, textWidth, textHeight);    
                
            drawString(mCenterX - textWidth / 2, mCenterY + 20, tmpStr, 0);
            break;
        }
        case SP_STATE_HIGHSCORE:
        {
            // New highscore.
            drawString(mCenterX - 80, mCenterY - 20, XFCSTR("NEW HIGHSCORE!"), 0);

            XFcStringToolkit::format(tmpStr, 32, "%d", mApp->getHighscore(), 0);
            INT32 textWidth, textHeight;
            mPrinter->stringMetrics(tmpStr, textWidth, textHeight);    

            drawString(mCenterX - textWidth / 2, mCenterY + 20, tmpStr, 0);
            
            break;
        }
        case SP_STATE_GAMECOMPLETE:
            // All levels finished...
            drawString(mCenterX - 60, mCenterY, XFCSTR("WELL DONE!"), 0);
            break;

        case SP_STATE_CREDITS:
            // Draw vertical scroller.
            y + mScrollerY;
            for (i = 0; i < NR_STRINGS; i++) 
            {
                if (endScreenText[i] != NULL && y > - 20) 
                {
                    drawString(5, y, endScreenText[i], endScreenText[i][0] == ' ' ? 1 : 0);
                }                
                y += 24;
                if (y > XFcCore::getDeviceHeight()) break;
            }
            // Scroll up...
            mScrollerY -= ((XFcCore::getTick() - mLastTick) * 0.05f);
            break;

        default:
            break;
    }

    mLastTick = XFcCore::getTick();
}


