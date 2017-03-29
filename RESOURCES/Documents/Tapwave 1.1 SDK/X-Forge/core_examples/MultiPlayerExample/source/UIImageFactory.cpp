/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: UIImageFactory.cpp,v 1.1 2003/07/11 11:25:19 lars Exp $
 * $Date: 2003/07/11 11:25:19 $
 * $Revision: 1.1 $
 */

#include <xforge.h>
#include "UIImageFactory.h"


#define BUTTON_BG_COLOR             0xff8f8880
#define BUTTON_3D_LIGHT_COLOR       0xffe0e0e0
#define BUTTON_3D_DARK_COLOR        0xff404040
#define BUTTON_BORDER_WIDTH         2

#define CHECKBOX_BG_COLOR           0xff808080
#define CHECKBOX_CHECK_COLOR        0xfff0f0f0
#define CHECKBOX_3D_LIGHT_COLOR     0xffe0e0e0
#define CHECKBOX_3D_DARK_COLOR      0xff404040
#define CHECKBOX_BORDER_WIDTH       2

#define FOCUS_COLOR                 0xffe0e0e0
#define FOCUS_WIDTH                 1


XFcGLSurface * UIImageFactory::createButton(INT32 aWidth, INT32 aHeight, INT aIsPressed, INT aIsFocused)
{
    XFcGLSurface *surface = XFcGLSurface::create(aWidth, aHeight);
    drawButton(surface, aWidth, aHeight, aIsPressed, aIsFocused);
    return surface;
}


void UIImageFactory::drawButton(XFcGLSurface *aSurface, INT32 aWidth, INT32 aHeight, INT aIsPressed, INT aIsFocused)
{

    aSurface->drawFilledRect(0, 0, aWidth, aHeight, BUTTON_BG_COLOR); 
    aSurface->drawFilledRect(0, 0, aWidth, BUTTON_BORDER_WIDTH, aIsPressed ? BUTTON_3D_DARK_COLOR : BUTTON_3D_LIGHT_COLOR);
    aSurface->drawFilledRect(0, 0, BUTTON_BORDER_WIDTH, aHeight, aIsPressed ? BUTTON_3D_DARK_COLOR : BUTTON_3D_LIGHT_COLOR);
    aSurface->drawFilledRect(aWidth - BUTTON_BORDER_WIDTH, 0, BUTTON_BORDER_WIDTH, aHeight, aIsPressed ? BUTTON_3D_LIGHT_COLOR : BUTTON_3D_DARK_COLOR);
    aSurface->drawFilledRect(0, aHeight - BUTTON_BORDER_WIDTH, aWidth, BUTTON_BORDER_WIDTH, aIsPressed ? BUTTON_3D_LIGHT_COLOR : BUTTON_3D_DARK_COLOR);

    if (aIsFocused)
    {
        drawFocus(aSurface,
                  BUTTON_BORDER_WIDTH + 2,
                  BUTTON_BORDER_WIDTH + 2,
                  aWidth - (BUTTON_BORDER_WIDTH + 2),
                  aHeight - (BUTTON_BORDER_WIDTH + 2));
    }

}


XFcGLSurface * UIImageFactory::createCheckbox(INT32 aWidth, INT32 aHeight, INT aIsPressed, INT aIsFocused)
{
    XFcGLSurface *surface = XFcGLSurface::create(aWidth, aHeight);
    surface->setColorKey(0x0000ff);
    surface->enableColorKey(1);
    surface->drawFilledRect(0, 0, aWidth, aHeight, 0xff0000ff);
    drawCheckbox(surface, aWidth, aHeight, aIsPressed, aIsFocused);
    return surface;
}


void UIImageFactory::drawCheckbox(XFcGLSurface *aSurface, INT32 aWidth, INT32 aHeight, INT aIsChecked, INT aIsFocused)
{

    INT32 padding = 2;

    INT32 x1 = padding;
    INT32 y1 = padding;
    INT32 x2 = x1 + aHeight - (padding * 2);
    INT32 y2 = x1 + aHeight - (padding * 2);
    INT32 width = x2 - x1;
    INT32 height = y2 - y1;

    aSurface->drawFilledRect(x1, y1, width, height, CHECKBOX_BG_COLOR);
    aSurface->drawFilledRect(x1, y1, width, CHECKBOX_BORDER_WIDTH, aIsChecked ? CHECKBOX_3D_DARK_COLOR : CHECKBOX_3D_LIGHT_COLOR);
    aSurface->drawFilledRect(x1, y1, CHECKBOX_BORDER_WIDTH, height, aIsChecked ? CHECKBOX_3D_DARK_COLOR : CHECKBOX_3D_LIGHT_COLOR);
    aSurface->drawFilledRect(x2 - CHECKBOX_BORDER_WIDTH, y1, CHECKBOX_BORDER_WIDTH, height, aIsChecked ? CHECKBOX_3D_LIGHT_COLOR : CHECKBOX_3D_DARK_COLOR);
    aSurface->drawFilledRect(x1, y2 - CHECKBOX_BORDER_WIDTH, width, CHECKBOX_BORDER_WIDTH, aIsChecked ? CHECKBOX_3D_LIGHT_COLOR : CHECKBOX_3D_DARK_COLOR);

    if (aIsFocused)
    {
        drawFocus(aSurface,
                  0,
                  0,
                  aWidth,
                  aHeight);
    }

}


void UIImageFactory::drawFocus(XFcGLSurface *aSurface, INT32 aX1, INT32 aY1, INT32 aX2, INT32 aY2)
{
    INT32 width = aX2 - aX1;
    INT32 height = aY2 - aY1;
    aSurface->drawFilledRect(aX1, aY1, width, FOCUS_WIDTH, FOCUS_COLOR);
    aSurface->drawFilledRect(aX1, aY1, FOCUS_WIDTH, height, FOCUS_COLOR);
    aSurface->drawFilledRect(aX2 - FOCUS_WIDTH, aY1, FOCUS_WIDTH, height, FOCUS_COLOR);
    aSurface->drawFilledRect(aX1, aY2 - FOCUS_WIDTH, width, FOCUS_WIDTH, FOCUS_COLOR);
}

