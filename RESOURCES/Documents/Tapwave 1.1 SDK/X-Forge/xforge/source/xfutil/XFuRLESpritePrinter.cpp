/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Primitive RLESprite font printer class.
 * Needs some work (create instead of init; gl sprites instead
 * of the glsurface drawing currently in use.
 * 
 * $Id: XFuRLESpritePrinter.cpp,v 1.11 2003/08/12 13:34:08 lars Exp $
 * $Date: 2003/08/12 13:34:08 $
 * $Revision: 1.11 $
 */

#include <stdlib.h>
#include <xfcore/XFcCore.h>
#include <xfutil/XFuPrinter.h>
#include <xfutil/XFuRLESpritePrinter.h>
#include <xfcore/XFcPixelConverter.h>


XFuRLESpritePrinter * XFuRLESpritePrinter::create(const CHAR *aFname) 
{
    return create(aFname,0xff000000,0x00000000,REALi(1),REALi(1));
}

XFuRLESpritePrinter * XFuRLESpritePrinter::create(const CHAR *aFname, UINT32 aBaseMask, UINT32 aBaseColor)
{
    return create(aFname,aBaseMask,aBaseColor,REALi(1),REALi(1));
}

XFuRLESpritePrinter * XFuRLESpritePrinter::create(const CHAR *aFname, UINT32 aBaseMask, UINT32 aBaseColor, REAL aXScale, REAL aYScale)
{
    INT32 wid, ht;
    INT32 i;

    XFcGLSurface *img = XFcImageLoader::load(aFname,XFCGF_A8R8G8B8);
    if (img == NULL) return NULL;

    XFuRLESpritePrinter *p = new XFuRLESpritePrinter();

    if (p == NULL)
    {
        delete img;
        return NULL;
    }

    p->mLetterSpacing = 2; // default letter spacing

    wid = img->getWidth();
    ht = img->getHeight();

    p->mLineSpacing = (INT32)(aXScale * (REAL)wid);
    p->mLineHeight = (INT32)(aYScale * (REAL)wid);

    p->mMaxletter = ht / wid;
    p->mLetterSprite = new XFcRLESprite *[p->mMaxletter];

    if (p->mLetterSprite == NULL)
    {
        delete img;
        delete p;
        return NULL;
    }

    XFcGLSurface *tImg = XFcGLSurface::create(wid,wid,XFCGF_A8R8G8B8);

    if (tImg == NULL)
    {
        delete img;
        delete p;
        return NULL;
    }

    // init to NULL so that delete wouldn't fail if creation fails
    for (i = 0; i < p->mMaxletter; ++i)
        p->mLetterSprite[i] = NULL;

    UINT32 *pic;
    INT32 pitch = img->lock((void **)(&pic));
    if (pitch == 0)
    {
        delete tImg;
        delete img;
        delete p;
        return NULL;
    }

    pitch /= 4;
    for (i = 0; i < p->mMaxletter; ++i)
    {
        INT32 letterofs = i * wid * pitch;

        UINT32 *fb;
        INT32 tPitch = tImg->lock((void **)&fb);
        if (tPitch == 0)
        {
            delete tImg;
            img->unlock();
            delete img;
            delete p;
            return NULL;
        }
        tPitch /= 4;

        INT32 j,k;
        for (j = 0; j < wid; j++)
        {
            for (k = 0; k < wid; k++) 
            {
                fb[j*tPitch + k] = pic[letterofs + j*pitch + k];
            }
        }

        tImg->unlock();

        if (aXScale != REALi(1) || aYScale != REALi(1))
        {
            XFcGLSurface *tImg2 = XFcGLSurfaceToolkit::resampleSurface(tImg,aXScale,aYScale);
            if (tImg2)
                p->mLetterSprite[i] = XFcRLESprite::create(tImg2, aBaseMask, aBaseColor);
            delete tImg2;
        }
        else
            p->mLetterSprite[i] = XFcRLESprite::create(tImg, aBaseMask, aBaseColor);

        if (p->mLetterSprite[i] == NULL)
        {
            delete tImg;
            img->unlock();
            delete img;
            delete p;
            return NULL;
        }
        if (p->mLetterSprite[i]->getWidth() == 0)
        {
            delete p->mLetterSprite[i];
            p->mLetterSprite[i] = NULL;
        }
        else
        {
            p->mLetterSprite[i]->setXOffset(0);
        }
    }
    img->unlock();
    delete tImg;
    delete img;

    if (p->mLetterSprite['0' - 33])
        p->mSpaceWidth = p->mLetterSprite['0' - 33]->getWidth() / 2;
    else
        p->mSpaceWidth = p->mLineHeight / 2;

    return p;

}


void XFuRLESpritePrinter::print(XFcGLSurface *aTarget, INT32 aX, INT32 aY, const CHAR *aText,
                                INT32 aBlendType, INT32 /*aBlendValue*/, XFcRectangle *aClipRect)
{
    if (this == NULL) return;
    unsigned char *p = (unsigned char *)aText;
    int xo = 0;
    INT32 i;

    XFcRectangle tRect;
    if (aClipRect == NULL)
    {
        tRect.mX = 0;
        tRect.mY = 0;
        tRect.mWidth = aTarget->getWidth();
        tRect.mHeight = aTarget->getHeight();
        aClipRect = &tRect;
    }

    while (*p)
    {
        if (*p == 32)
        {
            xo += mSpaceWidth + mLetterSpacing;
        }
        else
        {
            if (*p == '\n')
            {
                xo = 0;
                aY += mLineSpacing;
            }
            else
            {
                i = ((UINT8)*p) - 33;
                if (i >= 0 && i < mMaxletter)
                {
                    if (mLetterSprite[i] != NULL)
                    {
                        INT32 w = mLetterSprite[i]->getWidth();
                        INT32 xp = aX + xo;
                        switch (aBlendType)
                        {
                            case XFCBLEND_NONE:
                                mLetterSprite[i]->blit(aTarget,aClipRect,xp,aY);
                                break;
                            case XFCBLEND_MUL:
                                mLetterSprite[i]->blitMultiplicative(aTarget,aClipRect,xp,aY);
                                break;
                            case XFCBLEND_ADD:
                                mLetterSprite[i]->blitAdditive(aTarget,aClipRect,xp,aY);
                                break;
                            default:
                                mLetterSprite[i]->blit(aTarget,aClipRect,xp,aY);
                                break;
                        }
                        xo += w;
                    }
                    xo += mLetterSpacing;
                }
            }
        }
        ++p;
    }
}


void XFuRLESpritePrinter::stringMetrics(const CHAR *aText, INT32 &aWidth, INT32 &aHeight)
{
    if (aText == NULL)
    {
        aHeight = 0;
        aWidth = 0;
        return;
    }
    unsigned char *p = (unsigned char *)aText;
    int xo = 0, y = 0;
    int maxx = 0;
    INT32 i;
    while (*p)
    {
        if (*p == 32)
        {
            xo += mSpaceWidth;
            if (maxx < xo) maxx = xo;
            xo += mLetterSpacing;
        }
        else
        {
            if (*p == '\n')
            {
                xo = 0;
                y += mLineSpacing;
            }
            else
            {
                i = ((UINT8)*p) - 33;
                if ( i >= 0 && i < mMaxletter )
                {
                    if (mLetterSprite[i])
                        xo += mLetterSprite[i]->getWidth();
                    if (maxx < xo) maxx = xo;
                    xo += mLetterSpacing;
                }
            }
        }

        ++p;

    }
    y += mLineHeight;
    aHeight = y;
    aWidth = maxx;
}


INT32 XFuRLESpritePrinter:: getCharWidth(CHAR aChar)
{
    INT32 i = (INT32)(((UINT8)aChar) - 33);
    if (aChar == 32)
        return mSpaceWidth;
    else if (i < 0 || i >= mMaxletter || mLetterSprite[i] == NULL)
        return 0;
    else
        return mLetterSprite[i]->getWidth();
}


XFuRLESpritePrinter::~XFuRLESpritePrinter() 
{
    int i;
    if (mLetterSprite)
    {
        for (i = 0; i < mMaxletter; ++i)
            delete mLetterSprite[i];
    }
    delete[] mLetterSprite;
}


XFuRLESpritePrinter::XFuRLESpritePrinter()
{
    mLetterSprite = NULL;
}

