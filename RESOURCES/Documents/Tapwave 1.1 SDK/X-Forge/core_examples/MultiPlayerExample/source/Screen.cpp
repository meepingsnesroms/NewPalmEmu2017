/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Screen.cpp,v 1.6 2003/08/29 10:42:50 niko Exp $
 * $Date: 2003/08/29 10:42:50 $
 * $Revision: 1.6 $
 */

#include <xforge.h>
#include <xfutil/XFuPrinter.h>
#include <xfutil/XFuDynamicArray.h>

#include "Screen.h"
#include "Widget.h"
#include "UIImageFactory.h"


Screen::Screen() 
{   
    mApp = (MultiPlayerExample *)XFcCore::getApp(); 
    
    mWidth = XFcCore::getDeviceWidth();
    mHeight = XFcCore::getDeviceHeight();
    
    mCenterX = mWidth / 2;
    mCenterY = mHeight / 2;    

    // On screen button images.
    mBNSurf = UIImageFactory::createButton(150, 27, 0, 0);
    mBFSurf = UIImageFactory::createButton(150, 27, 0, 1);
    mBPSurf = UIImageFactory::createButton(150, 27, 1, 1);

    // Checkbox images.
    mCBCSurf = UIImageFactory::createCheckbox(150, 16, 1, 0);
    mCBUSurf = UIImageFactory::createCheckbox(150, 16, 0, 0);
    mCBCFSurf = UIImageFactory::createCheckbox(150, 16, 1, 1);
    mCBUFSurf = UIImageFactory::createCheckbox(150, 16, 0, 1);

    mWidgets = XFuDynamicArray<Widget *>::create();

    mActiveWidget = 0;
}


Screen::~Screen()
{
    delete mWidgets;
    delete mBNSurf;
    delete mBFSurf;
    delete mBPSurf;

    delete mCBCSurf;
    delete mCBUSurf;
    delete mCBCFSurf;
    delete mCBUFSurf;
}


void Screen::initRenderer()
{

    onActivate();

    if (mActiveWidget > (mWidgets->size() - 1))
        mActiveWidget = 0;

    while (!(mWidgets->get(mActiveWidget)->isVisible())) {
        mActiveWidget++;
        if (mActiveWidget > (mWidgets->size() - 1))
        {
            mActiveWidget = 0;
        }
    }
}

void Screen::deinitRenderer()
{
    
    XFcCore::resetScreenButtons();

    // Remove widgets.

    while (mWidgets->size()) 
    {
        delete mWidgets->get(0);
        mWidgets->remove(mWidgets->get(0));
    }       

    onDeactivate();
}


//! Add simple screen widget.
Widget * Screen::addWidget(INT aX, INT aY, INT aWidth, INT aHeight, const CHAR *aText, INT32 aScanCode, INT32 aWidgetType)
{
    Widget *w = new Widget(aX, aY, aWidth, aHeight, aText, aScanCode, aWidgetType);

    mWidgets->put(w);

    XFcRectangle rect;

    rect.mX = aX;
    rect.mY = aY;
    rect.mWidth = aWidth;
    rect.mHeight = aHeight;

    XFcCore::addScreenButton(rect, aScanCode);

    w->mEnabled = 1;
    w->mVisible = 1;

    if (aWidgetType == MPE_BUTTON_WIDGET) w->mState = MPE_BUTTON_NORMAL;
    else w->mState = MPE_CHECKBOX_UNCHECKED;

    return w;
}


//! Draw the widgets.
void Screen::drawWidgets()
{
    XFcGLSurface *fb, *surf = NULL;
    Widget *w;

    fb = mGL->getSecondary();

    UINT i;
    for (i = 0; i < mWidgets->size(); i++) 
    {   
        w = mWidgets->get(i);

        if (!w->isVisible()) continue;

        if (w->getType() == MPE_BUTTON_WIDGET) 
        {
            INT state = w->mState;

            if (i == mActiveWidget) state = MPE_BUTTON_FOCUSED;

            switch (state) 
            {
                case MPE_BUTTON_NORMAL: surf = mBNSurf; break;
                case MPE_BUTTON_PRESSED: surf = mBPSurf; break;
                case MPE_BUTTON_FOCUSED: surf = mBFSurf; break;
                default:
                    XFCASSERT(0);
            }
    
            fb->drawImage(surf, w->mX, w->mY);

            INT textWidth, textHeight;
            mPrinter->stringMetrics(w->mText, textWidth, textHeight);

            mPrinter->print(fb, w->mX + (w->mWidth - textWidth) / 2, 
                            w->mY + (w->mHeight - textHeight) / 2,
                            w->mText);
        }
        else 
        {
            INT state = w->mState;
            if (i == mActiveWidget) 
            {
                if (state == MPE_CHECKBOX_UNCHECKED) state = MPE_CHECKBOX_UNCHECKED_FOCUS;
                if (state == MPE_CHECKBOX_CHECKED) state = MPE_CHECKBOX_CHECKED_FOCUS;
            }

            switch (state) 
            {
                case MPE_CHECKBOX_UNCHECKED: surf = mCBUSurf; break;
                case MPE_CHECKBOX_CHECKED: surf = mCBCSurf; break;
                case MPE_CHECKBOX_UNCHECKED_FOCUS: surf = mCBUFSurf; break;
                case MPE_CHECKBOX_CHECKED_FOCUS: surf = mCBCFSurf; break;
                default:
                    XFCASSERT(0);
            }        
            fb->drawImage(surf, w->mX, w->mY);

            INT textWidth, textHeight;
            mPrinter->stringMetrics(w->mText, textWidth, textHeight);

            mPrinter->print(fb, w->mX + 20,
                            w->mY + (w->mHeight - textHeight) / 2,
                            w->mText);
        }
    }
}


//! Called when a control key is pressed.
void Screen::onControlDown(INT32 aCode)
{
    switch (aCode)
    {
        case XFCCL_UP:
            do {
                if (mActiveWidget == 0) mActiveWidget = mWidgets->size() - 1;
                else mActiveWidget--;
            } while (!(mWidgets->get(mActiveWidget)->isVisible()));
            break;

        case XFCCL_DOWN:
            do {
                mActiveWidget++;
                if (mActiveWidget > (mWidgets->size() - 1)) mActiveWidget = 0;
            } while (!(mWidgets->get(mActiveWidget)->isVisible()));
            break;
        case XFCCL_FIRE1:
            onWidgetActivate(mWidgets->get(mActiveWidget)); 
            break;
    }
}


//! Called when a control key is released.
void Screen::onControlUp(INT32 aCode)
{
    switch (aCode)
    {
        case XFCCL_FIRE1:
            onWidgetDeactivate(mWidgets->get(mActiveWidget)); 
            break;
    }
}


//! Called when a key (including virtual screen keys) is pressed.
void Screen::onKeyDown(INT32 aCode)
{
    Widget *w;
    UINT i;

    
    for (i = 0; i < mWidgets->size(); i++) 
    {
        w = mWidgets->get(i);
        
        if (!(w->mEnabled && w->mVisible)) continue;

        if (aCode == w->mScanCode)
        {
            onWidgetActivate(w);
        }
    }
}   


//! Called to activate a widget.
void Screen::onWidgetActivate(Widget *w)
{
    if (w->getType() == MPE_BUTTON_WIDGET)
    {            
        w->mState = MPE_BUTTON_PRESSED;
    }
    else
    {
        if (w->mState == MPE_CHECKBOX_UNCHECKED)
            w->mState = MPE_CHECKBOX_UNCHECKED_FOCUS;
        else
            w->mState = MPE_CHECKBOX_CHECKED_FOCUS;
    }
}


//! Called when a key (including virtual screen keys) is released.
void Screen::onKeyUp(INT32 aCode)
{
    Widget *w;
    UINT i;
    for (i = 0; i < mWidgets->size(); i++) 
    {
        w = mWidgets->get(i);
        
        if (!(w->mEnabled && w->mVisible)) continue;

        if (aCode == w->mScanCode)
        {
            onWidgetDeactivate(w);
        }
    }
}


//! Called to deactivate a widget.
void Screen::onWidgetDeactivate(Widget *w)
{
    if (w->getType() == MPE_BUTTON_WIDGET)
    {            
        onButtonPressed(w->mScanCode);
        w->mState = MPE_BUTTON_NORMAL;
    }
    else
    {
        if (w->mState == MPE_CHECKBOX_UNCHECKED_FOCUS)
        {
            w->mState = MPE_CHECKBOX_CHECKED;
        }
        else 
        {
            w->mState = MPE_CHECKBOX_UNCHECKED;
        }
    }
}

//! Update the widgets of this screen.
void Screen::render()
{
    drawWidgets();   
}