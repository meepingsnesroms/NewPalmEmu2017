/*! \file
 * Screen.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Screen.h,v 1.3 2003/07/07 07:01:59 lars Exp $
 * $Date: 2003/07/07 07:01:59 $
 * $Revision: 1.3 $
 */

#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

class StuntPlane;


//! Screen class. This is basically just a wrapper for the XFcInput and XFcRenderer classes.
class Screen : public XFcInput, public XFcRenderer
{

public:
    //! Public constructor.
    Screen(XFcGL *aGL) 
    { 
        mApp = (StuntPlane *)XFcCore::getApp(); 
        mGL = aGL;

        mWidth = XFcCore::getDeviceWidth();
        mHeight = XFcCore::getDeviceHeight();

        mCenterX = mWidth / 2;
        mCenterY = mHeight / 2;    
    }

protected:
    // !Pointer to application. A StuntPlane in this case.
    StuntPlane *mApp;
    
    //! Pointer to graphics library.
    XFcGL *mGL;

    //! Screen dimensions.
    REAL mWidth, mHeight;

    //! Center of screen.
    REAL mCenterX, mCenterY;
};

#endif // !SCREEN_H_INCLUDED