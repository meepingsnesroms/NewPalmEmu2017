/*! \file
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Primitive bitmap font printer class.
 * Needs some work (create instead of init; gl sprites instead
 * of the glsurface drawing currently in use.
 *
 * $Id: XFuPrinter.cpp,v 1.30 2003/08/12 13:34:08 lars Exp $
 * $Date: 2003/08/12 13:34:08 $
 * $Revision: 1.30 $
 */

#include <stdlib.h>
#include <xfcore/XFcCore.h>
#include <xfutil/XFuPrinter.h>
#include <xfcore/XFcPixelConverter.h>

#define TORGB16(r,g,b) (unsigned short)(((((r) >> 3) & 0x1f) << 11) | ((((g) >> 3) & 0x1f) << 6) | ((((b) >> 3) & 0x1f)))

XFuPrinter * XFuPrinter::create(const CHAR *aFname)
{
    return create(aFname,0,REALi(1),REALi(1));
}

XFuPrinter * XFuPrinter::create(const CHAR *aFname, INT32 aAlphamask)
{
    return create(aFname,aAlphamask,REALi(1),REALi(1));
}

XFuPrinter * XFuPrinter::create(const CHAR *aFname, INT32 aAlphamask, REAL aXScale, REAL aYScale)
{
    INT32 wid, ht;
    UINT8 *pal;
    UINT16 *pal16;
    UINT8 *pic;
    INT32 i;
    INT paletted;

    UINT16 alphamask = (UINT16)(XFCPC_X888_TO_55X5(aAlphamask));

    XFcImageLoader::loadImageInfo(aFname, &wid, &ht, NULL, &paletted);

    if (!paletted) return NULL; // TODO: create non-paletted version too
    if (wid == 0) return NULL;

    XFcImageLoader::loadImagePaletted(aFname, &pal, &pic);
    if (pal == NULL || pic == NULL)
    {
        delete[] pic;
        delete[] pal;
        return NULL;
    }

    pal16 = new UINT16[256];
    for (i = 0; i < 256; ++i)
        pal16[i] = TORGB16(pal[i * 3 + 0], pal[i * 3 + 1], pal[i * 3 + 2]);

    XFuPrinter *p = new XFuPrinter();

    p->mLetterSpacing = 2; // default letter spacing

    p->mMaxletter = ht / wid;
    p->mLetter = new XFcGLSurface *[p->mMaxletter];
    for (i = 0; i < p->mMaxletter; ++i)
    {
        INT32 j, l;
        int letterofs = i * wid * wid;
        INT32 ls = wid, rs = 0;
        for (j = 0, l = 0; j < wid; ++j)
        {
            INT32 k;
            for (k = 0; k < wid; ++k, ++l)
            {
                int c = pal16[pic[letterofs + l] & 0xff];
                if (c == alphamask)
                {
                }
                else
                {
                    if (rs < k) rs = k;
                    if (ls > k) ls = k;
                }
            }
        }
        int charwid = rs - ls + 1;
        if (charwid < 0)
        {
            charwid = 0; // empty character
            p->mLetter[i] = NULL;
        }
        else
        {
            XFcGLSurface *tSurface;
            tSurface = XFcGLSurface::create(charwid, wid);
            short *fb;
            tSurface->lock((void **)&fb);
            rs = wid - charwid;
            int m = 0, k;
            for (j = 0, l = ls; j < wid; ++j, l += rs)
            {
                for (k = 0; k < charwid; ++k,++l,++m)
                {
                    int c = pal16[pic[letterofs + l] & 0xff];
                    fb[m] = (INT16)c;
                }
            }
            tSurface->unlock();

            if (aXScale != REALi(1) || aYScale != REALi(1))
            {
                INT32 w = (INT32)(aXScale * (REAL)charwid);
                INT32 h = (INT32)(aYScale * (REAL)wid);
                XFcGLSurface *tSurface2 = XFcGLSurface::create(w,h);
                if (tSurface2)
                {
                    tSurface2->drawImage(tSurface,0,0,w,h);
                    delete tSurface;
                    tSurface = tSurface2;
                }
            }

            p->mLetter[i] = tSurface;
            p->mLetter[i]->setColorKey(aAlphamask);
            p->mLetter[i]->enableColorKey(1);
        }
    }

    p->mLineSpacing = (INT32)(aXScale * (REAL)wid);
    p->mLineHeight = (INT32)(aYScale * (REAL)wid);

    if (p->mLetter['0' - 33])
        p->mSpaceWidth = p->mLetter['0' - 33]->getWidth() / 2;
    else
        p->mSpaceWidth = p->mLineHeight / 2;

    delete[] pic;
    delete[] pal;
    delete[] pal16;
    return p;

}


INT32 XFuPrinter::print(XFcGLSurface *aTarget, XFcRectangle *aTargetRect, const CHAR *aText,
                        INT32 aBlendType, INT32 aBlendValue, XFcRectangle *aClipRect)
{
    XFCASSERT(aTarget);

    XFcRectangle rect;

    if (aTargetRect == NULL)
    {
        rect.mX = 0;
        rect.mY = 0;
        rect.mWidth = aTarget->getWidth();
        rect.mHeight = aTarget->getHeight();
    }
    else
    {
        rect = *aTargetRect;
    }

    // Find longest word
    INT32 i, j, longest = 0;
    i = 0;
    j = 0;
    while (aText[i] != 0)
    {
        i++;
        j++;
        if (aText[i] == ' ')
        {
            if (longest < j)
                longest = j;
            j = 0;
        }
    }

    if (longest < j)
        longest = j;

    CHAR * temp = new CHAR[longest + 1];

    if (temp == NULL)
        return 0;
    
    INT32 ofsx, ofsy;
    ofsx = rect.mX;
    ofsy = rect.mY;
    i = 0;
    do
    {
        if (aText[i] == ' ')
        {
            // Only advance cursor if not at the start of line.
            if (ofsx != rect.mX)
            {
                ofsx += mSpaceWidth + mLetterSpacing;
            }
            i++;
        }
        else if (aText[i] == '\n')
        {
            ofsx = rect.mX;
            ofsy += mLineSpacing;
            i++;
        }
        else
        {
            j = 0;
            while (aText[i] != 0 && aText[i] != ' ' && aText[i] != '\n')
            {
                temp[j] = aText[i];
                i++;
                j++;
            }
            temp[j] = 0;

            INT32 tx, ty;
            stringMetrics(temp, tx, ty);

            if (tx + ofsx > (rect.mX + rect.mWidth) && ofsx != rect.mX)
            {
                ofsx = rect.mX;
                ofsy += mLineSpacing;
            }

            print(aTarget, ofsx, ofsy, temp, aBlendType, aBlendValue, aClipRect);

            ofsx += tx;
        }

    }
    while (aText[i] != 0);

    delete[] temp;
    
    return ofsy - rect.mY + mLineHeight;
}


void XFuPrinter::print(XFcGLSurface *aTarget, INT32 aX, INT32 aY, const CHAR *aText,
                       INT32 aBlendType, INT32 aBlendValue, XFcRectangle *aClipRect)
{
    if ((aTarget != NULL) && (aText != NULL))
    {
        unsigned char *p = (unsigned char *)aText;
        int xo = 0;
        INT32 i;

        INT32 yMax = 0, xMax = 0;
        INT32 h = mLineHeight;

        if (aClipRect)
        {
            yMax = aClipRect->mY + aClipRect->mHeight;
            xMax = aClipRect->mX + aClipRect->mWidth;
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
                        if (mLetter[i] != NULL)
                        {
                            INT32 w = mLetter[i]->getWidth();
                            INT32 xp = aX + xo;
                            if (aClipRect == NULL)
                            {
                                aTarget->drawImageBlend(
                                    mLetter[i], xp, aY,
                                    aBlendType, aBlendValue);
                            }
                            else
                            {
                                XFcRectangle srcRect;
                                srcRect.mX = aClipRect->mX - xp;
                                srcRect.mY = aClipRect->mY - aY;
                                INT32 endX = xMax - xp;
                                INT32 endY = yMax - aY;

                                if (srcRect.mX < w && endX >= 0 &&
                                    srcRect.mY < h && endY >= 0)
                                {
                                    if (srcRect.mX < 0) srcRect.mX = 0;
                                    if (srcRect.mY < 0) srcRect.mY = 0;
                                    if (endX > w) endX = w;
                                    if (endY > h) endY = h;
                                    srcRect.mWidth = endX - srcRect.mX;
                                    srcRect.mHeight = endY - srcRect.mY;
                                    aTarget->drawImageBlend(
                                        mLetter[i], xp + srcRect.mX, aY + srcRect.mY, srcRect,
                                        aBlendType, aBlendValue);
                                }
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
}


void XFuPrinter::stringMetrics(const CHAR *aText, INT32 &aWidth, INT32 &aHeight)
{
    if (this == NULL) return;
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
                    if (mLetter[i])
                        xo += mLetter[i]->getWidth();
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


INT32 XFuPrinter:: getCharWidth(CHAR aChar)
{
    INT32 i = (INT32)(((UINT8)aChar) - 33);
    if (aChar == 32)
        return mSpaceWidth;
    else if (i < 0 || i >= mMaxletter || mLetter[i] == NULL)
        return 0;
    else
        return mLetter[i]->getWidth();
}


void XFuPrinter::setLetterSpacing(INT32 aSpacing)
{
    mLetterSpacing = aSpacing;
}


INT32 XFuPrinter::getLetterSpacing()
{
    return mLetterSpacing;
}


void XFuPrinter::setLineSpacing(INT32 aSpacing)
{
    mLineSpacing = aSpacing;
}


INT32 XFuPrinter::getLineSpacing()
{
    return mLineSpacing;
}


INT32 XFuPrinter::getLineHeight()
{
    return mLineHeight;
}


void XFuPrinter::setSpaceWidth(INT32 aSpacing)
{
    mSpaceWidth = aSpacing;
}


XFuPrinter::~XFuPrinter()
{
    int i;
    if (mLetter)
    {
        for (i = 0; i < mMaxletter; ++i)
            delete mLetter[i];
    }
    delete[] mLetter;
}


XFuPrinter::XFuPrinter()
{
    mLetter = NULL;
}

