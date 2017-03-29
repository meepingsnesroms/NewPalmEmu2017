/*!
 * \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFcPrimitiveDrawFiller defines a base class for fillers used by XFcPrimitiveDraw.
 *
 * $Id: XFcPrimitiveDrawFiller.h,v 1.3 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.3 $
 */

#ifndef XFC_CORE_XFCPRIMITIVEDRAWFILLER_H_INCLUDED
#define XFC_CORE_XFCPRIMITIVEDRAWFILLER_H_INCLUDED

//! A base class that defines interface for fillers that are used by XFcPrimitiveDraw
class XFcPrimitiveDrawFiller
{
public:
    //! Initializes the filler for rendering.
    /*! This should be called before calling fill() for the first filled span.
     */
    virtual void initFill() = 0;

    //! Deinitializes the filler after rendering.
    /*! This should be called after calling fill() for the last filled span.
     */
    virtual void deinitFill() = 0;

    //! Fills aLength A8R8G8B8 pixels to a scanline.
    //! param aXStart the starting position on the scanline
    //! param aXEnd the ending position on the scanline
    //! param aY the y position of the scanline
    //! param aScanline the start of the scanline
    virtual void fill(INT32 aXStart, INT32 aXEnd, INT32 aY, UINT32 *aScanline) = 0;
};

#endif // !XFC_CORE_XFCPRIMITIVEDRAWFILLER_H_INCLUDED

