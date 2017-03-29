/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Widget.h,v 1.1 2003/07/11 11:25:19 lars Exp $
 * $Date: 2003/07/11 11:25:19 $
 * $Revision: 1.1 $
 */

#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED


enum WIDGET_TYPE
{
    MPE_BUTTON_WIDGET,
    MPE_CHECKBOX_WIDGET
};


enum BUTTON_STATE
{
    MPE_BUTTON_NORMAL,
    MPE_BUTTON_FOCUSED,
    MPE_BUTTON_PRESSED
};


enum CHECKBOX_STATE
{
    MPE_CHECKBOX_UNCHECKED,
    MPE_CHECKBOX_CHECKED,
    MPE_CHECKBOX_UNCHECKED_FOCUS,
    MPE_CHECKBOX_CHECKED_FOCUS
};


class Widget
{

public:

    Widget(INT aX, INT aY, INT aWidth, INT aHeight, const CHAR *aText, INT32 aScanCode, INT32 aType)
    {
        mX = aX;
        mY = aY;
        mWidth = aWidth;
        mHeight = aHeight;
        mText = aText;
        mScanCode = aScanCode;
        mType = aType;
        mState = MPE_BUTTON_NORMAL;

    }

    void setEnabled(INT aEnabled) { mEnabled = aEnabled; }
    void setVisible(INT aVisible) { mVisible = aVisible; }
    void setText(const CHAR *aText) { mText = aText; }
    
    INT isVisible() { return mVisible; }    

    INT getType() { return mType; }
    INT getState() { return mState; }


    ~Widget() {};


    //! Top corner.
    INT mX, mY;

    INT mWidth, mHeight;

    INT32 mState;

    const CHAR *mText;

    INT32 mScanCode;

    INT mType, mVisible, mEnabled;
};

#endif //! WIDGET_H_INCLUDED

