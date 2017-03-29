
/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: UIImageFactory.h,v 1.1 2003/07/11 11:25:19 lars Exp $
 * $Date: 2003/07/11 11:25:19 $
 * $Revision: 1.1 $
 */

#ifndef UIIMAGEFACTORY_H_INCLUDED
#define UIIMAGEFACTORY_H_INCLUDED

class UIImageFactory
{

public:

    //! Creates an image for a button in the specified state
    static XFcGLSurface * createButton(INT32 aWidth, INT32 aHeight, INT aIsPressed, INT aIsFocused);

    //! Creates an image for a checkbox in the specified state
    static XFcGLSurface * createCheckbox(INT32 aWidth, INT32 aHeight, INT aIsChecked, INT aIsFocused);

    static void drawButton(XFcGLSurface *aSurface, INT32 aWidth, INT32 aHeight, INT aIsPressed, INT aIsFocused);
    static void drawCheckbox(XFcGLSurface *aSurface, INT32 aWidth, INT32 aHeight, INT aIsChecked, INT aIsFocused);
    static void drawFocus(XFcGLSurface *aSurface, INT32 aX1, INT32 aY1, INT32 aX2, INT32 aY2);

};

#endif // !UIIMAGEFACTORY_H_INCLUDED

