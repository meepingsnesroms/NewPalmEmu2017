/*! \file
* Menuscreen.h <br>
* Copyright 2003 Fathammer Ltd
*
* $Id: MenuScreen.h,v 1.7 2003/07/11 10:02:34 lars Exp $
* $Date: 2003/07/11 10:02:34 $
* $Revision: 1.7 $
*/

#ifndef MENUSCREEN_H_INCLUDED
#define MENUSCREEN_H_INCLUDED

//! Virtual screen button scan codes.
enum SP_SCREEN_BUTTONS
{
    SP_FIRST_BUTTON = 10000,
    SP_SECOND_BUTTON,
    SP_THIRD_BUTTON,
    SP_FOURTH_BUTTON,
    SP_FIFTH_BUTTON
};

#define SP_MENUSCREEN       0
#define SP_OPTIONSCREEN     1

class XFuPrinter;
class GameScreen;
class StuntPlane;


//! This is the screen for showing splashscreens, menus, highscore etc.
class MenuScreen : public Screen
{
public:
    //! Static constructor.
    static MenuScreen * create(XFcGL *aGL, XFuPrinter *aPrinter);

    ~MenuScreen();
    
// Inherited from XFcInput:

    //! Callback: control pressed.
    virtual void onControlDown(INT32 aCode);

    //! Called when other key pressed.
    virtual void onKeyUp(INT32 aCode);

    //! Called on pointer down (screen tapped).
    virtual void onPointerUp(INT32 aX, INT32 aY);

    //! Called on pointer down (screen tapped).
    virtual void onPointerDown(INT32 aX, INT32 aY);

// Inherited from XFcRenderer:

    //! Renders the game graph.
    virtual void render();

    //! Called when this class is set as active renderer.
    virtual void initRenderer();

    //! Called when another class is set as active renderer.
    virtual void deinitRenderer();

    //! Returns true is a savegame file was found.
    INT savedGameFound() { return mSavedGameFound; }

private:
    //! Private constructor.
    MenuScreen(XFcGL *aGL);

    //! Handle main menu key events.
    void mainMenuKeyDown(INT32 aCode);

    //! Handle options menu key events.
    void optionMenuKeyDown(INT32 aCode);

    //! Handle main menu item selection.
    void handleMainMenuSelection(INT32 aCode);

    //! Handle option menu item selection.
    void handleOptionMenuSelection(INT32 aCode);

    //! Renders the main menu text and logo.
    void renderMainMenu();
    
    //! Renders the option screen text and logo.
    void renderOptions();

    //! Renders the highscore screen text and logo.
    void renderHighScore();

    //! Printer centered text string at given y coordinate.
    void drawString(INT aX, INT aY, const CHAR *aString, INT aInv);

    //! Create onscreen virtual buttons for main/option menus.
    void createScreenButtons(INT aScreen);

    //! Menu text printer class.
    XFuPrinter *mPrinter;

    //! Menu background surface.
    XFcGLSurface *mBackSurf;        

    //! Menu logo surface.
    XFcGLSurface *mLogo;        

    //! Vertex buffer for rendering the menuscreen sunflares.
    XFcGLVertexBuffer *mVB;

    //! Current rotation angle of the sun flares effect.
    REAL mAngle;

    //! Position of the menu selection knobs.
    INT mMenuKnobPos;

    //! Position of the options menu selection knobs.
    INT mOptionKnobPos;

    //! Indicates that a saved game file has been found.
    INT mSavedGameFound;

    //! Time when last frame was rendered in milliseconds.
    INT32 mLastTick;

    //! Used to avoid interference between pointer events and virtual screen buttons.
    INT mLockPointer;

    //! Credits scroller position.
    REAL mScrollerY;
};

#endif // !MENUSCREEN_H_INCLUDED
