/*! \file
* SplashScreen.h <br>
* Copyright 2003 Fathammer Ltd
*
* $Id: SplashScreen.h,v 1.1 2003/07/09 14:15:56 lars Exp $
* $Date: 2003/07/09 14:15:56 $
* $Revision: 1.1 $
*/

#ifndef SPLASH_H_INCLUDED
#define SPLASH_H_INCLUDED


//! This is the splashscreen, showing X-Forge logo.
class SplashScreen : public Screen
{
public:
    //! Static constructor.
    static SplashScreen * create(XFcGL *aGL);

    ~SplashScreen();
    
// Inherited from XFcInput:

    //! Called when other key pressed.
    virtual void onKeyDown(INT32 aCode);

    //! Called on pointer down (screen tapped).
    virtual void onPointerDown(INT32 aX, INT32 aY);

// Inherited from XFcRenderer:

    //! Renders the game graph.
    virtual void render();

    //! Called when this class is set as active renderer.
    virtual void initRenderer();

    //! Called when another class is set as active renderer.
    virtual void deinitRenderer();

private:
    //! Private constructor.
    SplashScreen(XFcGL *aGL);

    //! Splash screen surface.
    XFcGLSurface *mSplash;        
};

#endif // !SPLASH_H_INCLUDED
