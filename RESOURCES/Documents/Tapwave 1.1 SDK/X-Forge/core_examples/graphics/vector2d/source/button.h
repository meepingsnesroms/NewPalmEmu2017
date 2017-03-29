/*!
 * \file
 * X-Forge <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Renders a buttonusing XFcPrimitiveTranslator.
 *
 * $Id: button.h,v 1.1 2003/10/16 12:47:44 kkallio Exp $
 * $Date: 2003/10/16 12:47:44 $
 * $Revision: 1.1 $
 */

#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

class XFcPrimitiveDrawLinearGradientFiller;
class XFcPrimitiveDrawRadialGradientFiller;

class button
{
public:
    button(REAL aXPos, REAL aYPos, REAL aRadius);
    virtual ~button();
    void render(XFcGLSurface *aSurface);
    void setPressed(INT aState);

protected:
    UINT32 calculateBrightness(UINT32 aColor);

    INT32 mBrightness;
    XFcMatrix3 mTransformation;
    INT mPressed;

    XFcPrimitiveDrawRadialGradientFiller *mRadialFillerA;
    XFcPrimitiveDrawRadialGradientFiller *mRadialFillerB;
    XFcPrimitiveDrawLinearGradientFiller *mLinearFiller;
};

#endif // !BUTTON_H_INCLUDED
