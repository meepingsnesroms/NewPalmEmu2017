/*!
  \Buffers * Screen.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Screen.h,v 1.7 2003/08/28 14:25:04 niko Exp $
 * $Date: 2003/08/28 14:25:04 $
 * $Revision: 1.7 $
 */

#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

class XFuPrinter;
class MultiPlayerExample;
class Widget;
template<class T> class XFuDynamicArray;



/*! Screen class. This is basically just a wrapper for 
 *  the XFcInput and XFcRenderer classes, whith some
 *  very basic UI widget functionality.
 */
class Screen : public XFcInput, public XFcRenderer
{

public:
    //! Public constructor.

    Screen();

    virtual ~Screen();

    virtual void render();

    virtual void initRenderer();
    virtual void deinitRenderer();

    virtual void onActivate() {}
    virtual void onDeactivate() {}

    virtual void onTick(){}

    Widget * addWidget(INT aX, INT aY, INT aWidth, INT aHeight, 
                       const CHAR *aText, INT32 aScanCode, INT32 mType);

    virtual void onKeyDown(INT32 aCode);
    virtual void onKeyUp(INT32 aCode);
    virtual void onControlDown(INT32 aCode);
    virtual void onControlUp(INT32 aCode);

    void onWidgetActivate(Widget *w);
    void onWidgetDeactivate(Widget *w);

    //! Called when a button widget is pressed.
    virtual void onButtonPressed(INT32 /*aButton */) {};

protected:
    
    //! Draw all widgets.
    void drawWidgets();

    //! Pointer to application.
    MultiPlayerExample *mApp;
    
    //! Pointer to graphics library.
    XFcGL *mGL;

    //! Screen dimensions.
    REAL mWidth, mHeight;

    //! Center of screen.
    REAL mCenterX, mCenterY;

    //! Button images.
    XFcGLSurface *mBNSurf, *mBFSurf, *mBPSurf;

    // Checkbox images.
    XFcGLSurface *mCBCSurf, *mCBUSurf, *mCBCFSurf, *mCBUFSurf;

    //! List of screen widgets.
    XFuDynamicArray<Widget *> *mWidgets;

    //! Pointer to global printer object.
    XFuPrinter *mPrinter;

    UINT mActiveWidget;
};

#endif // !SCREEN_H_INCLUDED
