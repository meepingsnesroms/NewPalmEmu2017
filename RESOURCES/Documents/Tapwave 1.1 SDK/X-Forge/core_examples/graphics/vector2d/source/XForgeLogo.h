/*!
 * \file
 * X-Forge <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Renders X-Forge logo using XFcPrimitiveTranslator.
 *
 * $Id: XForgeLogo.h,v 1.1 2003/10/16 12:47:44 kkallio Exp $
 * $Date: 2003/10/16 12:47:44 $
 * $Revision: 1.1 $
 */

#ifndef XFORGELOGO_H_INCLUDED
#define XFORGELOGO_H_INCLUDED

class XForgeLogo
{
public:
    XForgeLogo();
    virtual ~XForgeLogo();
    void render(XFcGLSurface *aSurface);
    void setZoom(REAL aZoom);
    void setFade(UINT32 aFadeColor, INT32 aFade);
    UINT32 calculateFade(UINT32 aColor);

protected:
    REAL mZoom;
    INT32 mFade;
    UINT32 mFadeColor;
    XFcMatrix3 mTransformation;
};

#endif // !XFORGELOGO_H_INCLUDED
